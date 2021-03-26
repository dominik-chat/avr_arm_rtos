#include <avr/io.h>
#define  F_CPU 2000000UL
#include <util/delay.h>

#include "rtos.h"

void proc_A(void)
{
	while(1)
	{
		PORTD ^= 0x10;
		_delay_ms(250);
		
		yield();
	}
}

void proc_B(void)
{
	while(1)
	{
		PORTD ^= 0x80;
		_delay_ms(250);
		
		yield();		
	}
}

int main(void)
{
	DDRD = 0x90;

	proc_create(proc_A);
	proc_create(proc_B);
	
	proc_run(0);
}

