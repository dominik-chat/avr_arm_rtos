.global pc_swap
.global cor_start

.section  .text

pc_swap:
	str	lr, [r0]	//Save return address to first argument pointer
	mov	lr, r1		//Copy second argument to link register
	bx	lr		//Jump to PC value of second argument

cor_start:
	mov	lr, r0		//Copy target function address to link register
	bx	lr		//Jump to target function
