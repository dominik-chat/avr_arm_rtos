.global swap

swap:
	ldr	r2, [r0]
	ldr	r3, [r1]
	str	r3, [r0]
	str	r2, [r1]
	bx	lr
