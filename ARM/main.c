#include "stdint.h"
#include "lpc21xx.h"

extern void pc_swap(uint32_t *current_cor, uint32_t next_cor);
extern void cor_start(uint32_t cor);


uint32_t pc_cor_A;
uint32_t pc_cor_B;

void cor_A(void)
{
	while(1)
	{
		IO1SET = 0x10000;
		pc_swap(&pc_cor_A, pc_cor_B);
	}
}

void cor_B(void)
{
	while(1)
	{
		IO1CLR = 0x10000;
		pc_swap(&pc_cor_B, pc_cor_A);
	}
}

uint32_t pc_cor_A = (uint32_t)cor_A;
uint32_t pc_cor_B = (uint32_t)cor_B;

int main()
{
	InitPLL(5, PLLCFG_P_2_bm);
	InitMAM(4);

	IO1DIR = 0x10000;

	cor_start(pc_cor_A);
}
