.global cor_init
.global cor_start
.global ctx_swap


.section  .text


cor_init:
	mov	r2, sp		//Save old stack
	mov	sp, r0		//Change to new stack

	push	{r1}		//Push corutine address to stack
	push	{r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12}	//Push all context to stack

	mov	r0, sp		//Save stack pointer after push
	mov	sp, r2		//Restore old stack
	bx	lr		//Return

cor_start:
	mov	sp, r0		//Copy target function address to stack pointer

	pop	{r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12}	//Pop all context from stack
	pop	{lr}		//Get branch address from stack

	bx	lr		//Jump to target function

ctx_swap:
	push	{lr}		//Store return address on old stack
	push	{r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12}	//Push all context to stack
	str	sp, [r0]	//Save old SP to r0 address

	mov	sp, r1		//Set sp to new address
	pop	{r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12}	//Pop all context from stack
	pop	{lr}		//Get return address from new stack

	bx	lr		//Return
