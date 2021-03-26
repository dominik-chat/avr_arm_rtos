#include "rtos.h"


#define STACK_BASE 0x8EE // Adres bazowy stosu korutyn
#define STACK_SIZE 128 // Rozmiar stosu
#define PROC_CNT 2 // Liczba procesów
#define ALL_PROC_CNT (PROC_CNT+1) //wszystkie procesy + idle


typedef struct
{
	uint16_t sp;
	uint16_t sleep_ctr;
}process_data;


extern uint16_t proc_init( uint16_t stack_pointer, uint16_t *cor_address);
extern void proc_start(uint16_t cor);
extern void ctx_swap(uint16_t *current_cor, uint16_t next_cor);
extern uint8_t int_disable(void);
extern void int_restore(uint8_t sreg);


process_data proc[ALL_PROC_CNT];
uint8_t pid_curr = 0;


void proc_create(void *proc_address)
{
	static uint8_t proc_ctr = 0;
	
	proc[proc_ctr].sp = proc_init((STACK_BASE - (proc_ctr*STACK_SIZE)), proc_address);
	proc[proc_ctr].sleep_ctr = 0;
	
	proc_ctr++;
}

void resched()
{
	uint8_t pid_prev = pid_curr;
	
	do 
	{
		pid_curr = (pid_curr+1) % ALL_PROC_CNT;
	} while(proc[pid_curr].sleep_ctr > 0);

	if (pid_prev != pid_curr) 
	{
		ctx_swap(&proc[pid_prev].sp, proc[pid_curr].sp);
	}
}
void proc_run(uint8_t proc_number)
{
	proc_start(proc[proc_number].sp);
}

void proc_sleep(uint16_t ticks)
{
	uint8_t sreg = int_disable();
	proc[pid_curr].sleep_ctr = ticks;
	resched();
	int_restore(sreg);
}

void proc_interrupt_init()
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

ISR(TIMER1_COMPA_vect)
{
	for(uint8_t i = 0; i < PROC_CNT; i++) 
	{ 
		if(proc[i].sleep_ctr > 0)
		{
			proc[i].sleep_ctr--; 
		}
	}
	
	resched();
}

