.global proc_init
.global proc_start
.global ctx_swap

.section  .text

ctx_swap:
	push	{lr}
	push	{r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12}
	str	sp, [r0]

	mov	sp, r1
	pop	{r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12}
	pop	{lr}

	bx lr

proc_start:
	mov	sp, r0

	pop	{r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12}
	pop	{lr}

	bx	lr

proc_init:
	mov	r2, sp
	mov	sp, r0

	push	{r1}
	push	{r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12}

	mov	r0, sp
	mov	sp, r2
	bx	lr
