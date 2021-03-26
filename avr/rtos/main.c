#include <avr/io.h>

extern void pc_swap(uint16_t *current_cor, uint16_t next_cor);
extern void cor_start(uint16_t cor);

uint16_t pc_cor_A;
uint16_t pc_cor_B;

void cor_A(void)
{
	while(1)
	{
		PORTD ^= 0x01;
		pc_swap(&pc_cor_A,pc_cor_B);
	}
}

void cor_B(void)
{
	while(1)
	{
		PORTD ^= 0x02;
		pc_swap(&pc_cor_B,pc_cor_A);
	}
}

uint16_t pc_cor_A = (uint16_t)cor_A;
uint16_t pc_cor_B = (uint16_t)cor_B;

int main(void)
{
	DDRD = 0x03;
	PORTD = 0x03;
	cor_start(pc_cor_A);
}
