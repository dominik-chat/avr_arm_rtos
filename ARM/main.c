#include "stdint.h"
#include "lpc21xx.h"

#include "rtos.h"

/* This is a function to simplify proc_* procedures */
void delay(void){
	for(unsigned int uiDelayCounter = 0; uiDelayCounter < 500000; uiDelayCounter++){}
}

/* This is a function to simplify proc_* procedures */
void pin_toggle(uint8_t pin_nr){
	uint32_t mask = (1 << pin_nr);
        if((IO1PIN & mask) != 0) IO1CLR = mask; else IO1SET = mask;
}

/* This is a function to simplify main */
void pin_init(void){
	IO1DIR = 0x30000;
}


void proc_A(void)
{
	while(1)
	{
		pin_toggle(16);
		delay();

		yield();
	}
}

void proc_B(void)
{
	while(1)
	{
		pin_toggle(17);
		delay();

		yield();
	}
}

int main()
{
	InitPLL(5, PLLCFG_P_2_bm);
	InitMAM(4);

	pin_init();

	proc_create(proc_A);
	proc_create(proc_B);

	proc_run(0);
}
