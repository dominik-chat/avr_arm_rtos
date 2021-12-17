.global increment

increment:
	ldrb	fp, [r0]
	add	fp, fp, #1
	strb	fp, [r0]
	bx	lr
