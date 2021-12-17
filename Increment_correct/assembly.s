.global increment

increment:
	push	{fp}
	ldrb	fp, [r0]
	add	fp, fp, #1
	strb	fp, [r0]
	pop	{fp}
	bx	lr
