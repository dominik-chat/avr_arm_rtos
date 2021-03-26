.global cor_init
.global cor_start
.global sp_swap

.set _SP_L, 0x3D
.set _SP_H, 0x3E

sp_swap:
	mov r30, r24 ; Z LSB
	mov r31, r25 ; Z MSB
	in r0, _SP_L
	std Z+0, r0
	in r0, _SP_H
	std Z+1, r0
	out _SP_L, r22
	out _SP_H, r23
ret

cor_start:
	out _SP_L, r24
	out _SP_H, r25
ret

cor_init:
	in r26, _SP_L
	in r27, _SP_H
	out _SP_L, r24
	out _SP_H, r25
	push r22
	push r23
	in r24, _SP_L
	in r25, _SP_H
	out _SP_L, r26
	out _SP_H, r27
ret