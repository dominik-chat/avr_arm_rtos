.global proc_init
.global proc_start
.global ctx_swap
.global timer0_int_handler
.extern timer0_callback

.set	VICVectAddr,	0xFFFFF030
.set	T0IR,		0xE0004000
.set	MODE_SYS,	0xDF		//System mode, irq disabled, fiq disabled
.set	MODE_USER,	0x50		//User mode, irq enabled, fiq disabled

.section  .text


//r0 - *cur_sp, r1 - new_sp
ctx_swap:
	mrs	r3, CPSR	//save exception cpsr
	mrs	r2, SPSR	//get old spsr

	msr	CPSR, MODE_SYS	//switch to sys mode
	push	{r2, lr}	//save SPSR and lr to user stack
	str	sp, [r0]	//save current sp to pointer

	mov	sp, r1		//set new user stack
	pop	{r2, lr}	//pop new SPSR, lr from user stack
	msr	CPSR, r3	//return to exception mode

	msr	SPSR, r2	//SPSR is updated with new one

	bx lr

//r0 - sp
proc_start:
	mov	sp, r0

	pop	{r1, lr}	//CPSR and dummy lr
	pop	{lr}		//PC
	msr	CPSR, r1	//set CPSR
	pop	{r0-r12}	//pop gp regs

	bx	lr

//r0 - sp, r1 - cor_addr
proc_init:
	mov	r2, sp		//save stack
	mov	sp, r0		//switch to new stack

	push	{r0-r12}
	ldr	r3, =MODE_USER	//set to clean cpsr user mode, irq enabled
	push	{r1}
	push	{r3, lr}

	mov	r0, sp		//return sp
	mov	sp, r2		//restore old stack
	bx	lr


//This handler is a prepare stage for timer0_callback.
//Handler pushes all user regs and lr to user stack
//Calls timer0_callback (in IRQ MODE)
//Pops all user regs and lr from user stack
timer0_int_handler:
	sub	lr, lr, #4	//prepare lr
	push	{lr}		//push lr to IRQ stack

//switch to user mode stack
	stmfd	sp, {sp}^	//push user sp to irq stack
	nop			//nop required after accessing banked registers
	sub	sp, sp, #4	//writeback does not work, decrement manually
	pop	{lr}		//switch to user stack

	stmfd	lr!, {r0-r12}	//store all gp regs to user stack
	pop	{r0}		//old pc, stored at beginning of function
	str	r0, [lr, #-4]!	//store pc to user stack

//update user stack pointer
	push	{lr}
	ldmfd	sp, {sp}^	//writeback does not work
	nop			//nop required after accessing banked registers
	add	sp, sp, #4	//increment sp manually

//user stack after
//r0,r1,r2,...,r12, pc
//		    ^user stack pointer

	bl	timer0_callback

//switch to user mode stack
	stmfd	sp, {sp}^	//push user sp to irq stack
	nop			//nop required after accessing banked registers
	sub	sp, sp, #4	//writeback does not work, decrement manually
	pop	{lr}		//switch to user stack

	ldr	r0, [lr], #4	//load new pc
	push	{r0}		//store new pc to irq stack
	ldmfd	lr!, {r0-r12}	//load all gp regs from user stack

//update user stack pointer
	push	{lr}
	ldmfd	sp, {sp}^	//writeback does not work
	nop			//nop required after accessing banked registers
	add	sp, sp, #4	//increment sp manually

	ldmfd	sp!, {pc}^	//return to user mode with new pc
