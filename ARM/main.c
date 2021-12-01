#include "stdint.h"
#include "lpc21xx.h"

#define COR_A_STACK_BASE 0x40004000
#define COR_B_STACK_BASE 0x40003F80

extern uint32_t cor_init(uint32_t stack_pointer, void *cor_address);
extern void cor_start(uint32_t cor);
extern void ctx_swap(uint32_t *current_cor, uint32_t next_cor);


uint32_t cor_A_sp;
uint32_t cor_B_sp;

/* This is a function to simplify cor_* corutines */
void delay(void){
	for(unsigned int uiDelayCounter = 0; uiDelayCounter < 500000; uiDelayCounter++){}
}

/* This is a function to simplify cor_* corutines */
void pin_toggle(uint8_t pin_nr){
	uint32_t mask = (1 << pin_nr);
        if((IO1PIN & mask) != 0) IO1CLR = mask; else IO1SET = mask;
}

/* This is a function to simplify main */
void pin_init(void){
	IO1DIR = 0x30000;
}

void cor_A(void)
{
	while(1)
	{
		pin_toggle(16);
        delay();

		ctx_swap(&cor_A_sp, cor_B_sp);
	}
}

void cor_B(void)
{
	while(1)
	{
		pin_toggle(17);
        delay();

		ctx_swap(&cor_B_sp, cor_A_sp);
	}
}

uint32_t pc_cor_A = (uint32_t)cor_A;
uint32_t pc_cor_B = (uint32_t)cor_B;

int main()
{
	InitPLL(5, PLLCFG_P_2_bm);
	InitMAM(4);

	pin_init();

	cor_A_sp = cor_init(COR_A_STACK_BASE, (void *)cor_A);
	cor_B_sp = cor_init(COR_B_STACK_BASE, (void *)cor_B);
	cor_start(cor_A_sp);
}
