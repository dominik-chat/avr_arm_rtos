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
	while(1)
	{
		sem_give(0);
		proc_sleep(243);
	}
}

void process_B(void)
{
	while(1)
	{
		sem_give(1);
		proc_sleep(113);
	}
}

void process_C(void)
{
	while(1)
	{
		sem_take(0);
		pin_toggle(16);
	}
}

void process_D(void)
{
	while(1)
	{
		sem_take(1);
		pin_toggle(17);
	}
}

void process_idle(void)
{
	while(1)
	{

	}
}

int main()
{
	pin_init();

	proc_create(process_A);
	proc_create(process_B);
	proc_create(process_C);
	proc_create(process_D);
	proc_create(process_idle);

	proc_interrupts_init(1000);
	proc_run(0);
}
