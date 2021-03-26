.global cor_init
.global cor_start
.global ctx_swap

.set _SP_L, 0x3D
.set _SP_H, 0x3E

.macro push_all_ctx
	push r0
	push r1
	push r2
	push r3
	push r4
	push r5
	push r6
	push r7
	push r8
	push r9
	push r10
	push r11
	push r12
	push r13
	push r14
	push r15
	push r16
	push r17
	push r28
	push r29
.endm

.macro pop_all_ctx
	pop r29
	pop r28
	pop r17
	pop r16
	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	pop r7
	pop r6
	pop r5
	pop r4
	pop r3
	pop r2
	pop r1
	pop r0
.endm

.macro clr_all_ctx
	ldi r18, 0x85
	push r18
	push r1
	push r18
	push r18
	push r18
	push r18
	push r18
	push r18
	push r18
	push r18
	push r18
	push r18
	push r18
	push r18
	push r18
	push r18
	push r18
	push r18
	push r18
	push r18
.endm

ctx_swap:
	push_all_ctx

	mov r30, r24 ; Z LSB
	mov r31, r25 ; Z MSB
	in r0, _SP_L
	std Z+0, r0
	in r0, _SP_H
	std Z+1, r0
	out _SP_L, r22
	out _SP_H, r23

	pop_all_ctx
ret

cor_start:
	out _SP_L, r24
	out _SP_H, r25
	pop_all_ctx
ret

cor_init:
	in r26, _SP_L
	in r27, _SP_H
	out _SP_L, r24
	out _SP_H, r25
	push r22
	push r23
	clr_all_ctx
	in r24, _SP_L
	in r25, _SP_H
	out _SP_L, r26
	out _SP_H, r27
ret