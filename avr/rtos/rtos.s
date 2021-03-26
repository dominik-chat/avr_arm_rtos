.global pc_swap
.global cor_start

pc_swap:
	mov r30, r24 ; Skopiowanie pierwszego argumentu do rejestru Z
	mov r31, r25
	pop r25 ; Zrzucenie ze stosu adresu powrotu do starej funkcji
	pop r24
	std Z+0, r24 ; Zapisanie adresu powrotu pod wskazany adres w pami�eci RAM
	std Z+1, r25
	push r22 ; Od�o�zenie na stosie adresu nowej funkcji
	push r23
	ret ; Nadpisanie licznika programu

cor_start:
	pop r1 ; Usuni�ecie ze stosu zb�ednego adresu powrotu
	pop r1
	clr r1
	push r24 ; Od�o�zenie na stosie adresu nowej funkcji
	push r25
ret ; Nadpisanie licznika programu