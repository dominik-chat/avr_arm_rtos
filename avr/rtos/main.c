#define  F_CPU 16000000UL
#include <util/delay.h>

#include "rtos.h"

void proc_A(void)
{
	while(1)
	{
		PORTD ^= 0x10;
		_delay_ms(125);
	}
}

void proc_B(void)
{
	while(1)
	{
		PORTD ^= 0x80;
		_delay_ms(250);	
	}
}

void timer_interrupts_init()
{
	// ustawienie prescalera na 64 i tryb CTC
	TCCR1B = (1<<CS10) | (1<<CS11) | (1<<WGM12);
	// wartosc rejestru compare
	OCR1A = 249;
	// wyczyszczenie flagi przerwania
	TIFR1 = (1<<OCF1A);
	// odblokowanie przerwania dla OCR1
	TIMSK1 = (1<<OCIE1A);
}

ISR( TIMER1_COMPA_vect )
{
	resched();
}

int main(void)
{
	DDRD = 0x90;
	timer_interrupts_init();

	proc_create(proc_A);
	proc_create(proc_B);
	
	proc_run(0);
}

