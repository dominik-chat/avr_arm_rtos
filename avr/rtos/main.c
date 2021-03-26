#define  F_CPU 16000000UL
#include <util/delay.h>

#include "rtos.h"

void process_A(void)
{
	while(1)
	{
		PORTD ^= 0x10;
		proc_sleep(500);
	}
}

void process_B(void)
{
	while(1)
	{
		PORTD ^= 0x80;
		proc_sleep(250);	
	}
}

void process_idle(void)
{
	while(1)
	{
		
	}
}

int main(void)
{
	DDRD = 0x90;
	
	proc_interrupt_init();

	proc_create(process_A);
	proc_create(process_B);
	proc_create(process_idle);
	
	proc_run(0);
}

