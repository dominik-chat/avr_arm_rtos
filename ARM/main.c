#include "stdint.h"
#include "lpc21xx.h"

#include "rtos.h"


/* This is a function to simplify proc_* procedures */
void pin_toggle(uint8_t pin_nr){
	uint32_t mask = (1 << pin_nr);
        if((IO1PIN & mask) != 0) IO1CLR = mask; else IO1SET = mask;
}

/* This is a function to simplify main */
void pin_init(void){
	IO1DIR = 0x30000;
}

void process_A(void)
{
	static uint32_t ctr = 0;

	while(1)
	{
		if (ctr==12500)
		{
			sem_give(0);
		}
		else if(ctr==25000)
		{
			sem_give(1);
			ctr=0;
		}
		ctr++;
	}
}

void process_B(void)
{
	while(1)
	{
		sem_take(0);
		pin_toggle(16);
	}
}

void process_C(void)
{
	while(1)
	{
		sem_take(1);
		pin_toggle(17);
	}
}

int main()
{
	pin_init();

	proc_create(process_A);
	proc_create(process_B);
	proc_create(process_C);

	proc_interrupts_init(1000);
	proc_run(0);
}
