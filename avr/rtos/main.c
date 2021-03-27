#include "rtos.h"

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
		PORTD ^= 0x10;
	}
}

void process_D(void)
{
	while(1)
	{
		sem_take(1);
		PORTD ^= 0x80;
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
	proc_create(process_C);
	proc_create(process_D);
	proc_create(process_idle);
	
	proc_run(0);
}

