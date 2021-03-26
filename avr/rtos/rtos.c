#include "rtos.h"


#define STACK_BASE 0x8EE // Adres bazowy stosu korutyn
#define STACK_SIZE 128 // Rozmiar stosu
#define PROC_CNT 2 // Liczba procesów


extern uint16_t proc_init( uint16_t stack_pointer, uint16_t *cor_address);
extern void proc_start(uint16_t cor);
extern void ctx_swap(uint16_t *current_cor, uint16_t next_cor);


uint16_t proc[PROC_CNT]; 
uint8_t pid_curr = 0;


void proc_create(void *proc_address)
{
	static uint8_t proc_ctr = 0;
	proc[proc_ctr++] = proc_init((STACK_BASE - (proc_ctr*STACK_SIZE)), proc_address);
}

void resched()
{
	uint8_t pid_prev = pid_curr;
	pid_curr = (pid_curr+1)%PROC_CNT;
	ctx_swap(&proc[pid_prev], proc[pid_curr]);
}

void proc_run(uint8_t proc_number)
{
	proc_start(proc[proc_number]);
}
