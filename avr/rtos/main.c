#include <avr/io.h>
#define  F_CPU 2000000UL
#include <util/delay.h>

#define COR_A_STACK_BASE 0x120
#define COR_B_STACK_BASE 0x140

extern uint16_t cor_init( uint16_t stack_pointer, uint16_t *cor_address);
extern void cor_start(uint16_t cor);
extern void ctx_swap(uint16_t *current_cor, uint16_t next_cor);

uint16_t cor_A_sp;
uint16_t cor_B_sp;

void cor_A(void)
{
	while(1)
	{
		PORTD ^= 0x10;
		_delay_ms(250);
		
		ctx_swap(&cor_A_sp,cor_B_sp);
	}
}

void cor_B(void)
{
	while(1)
	{
		PORTD ^= 0x80;
		_delay_ms(250);
		
		ctx_swap(&cor_B_sp,cor_A_sp);		
	}
}

int main(void)
{
	DDRD = 0x90;

	cor_A_sp = cor_init(COR_A_STACK_BASE, (void *)cor_A);
	cor_B_sp = cor_init(COR_B_STACK_BASE, (void *)cor_B);
	cor_start(cor_A_sp);
}

