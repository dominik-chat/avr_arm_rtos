.global inc

inc:
	ldrsb	r1, [r0]
	add	r1, r1, #1
	strb	r1, [r0]
	bx	lr
