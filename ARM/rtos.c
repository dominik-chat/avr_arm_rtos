#include "rtos.h"


#define STACK_BASE 0x40004000 // Base stack address - must be word aligned
#define STACK_SIZE 128 // Stack size for process - in 4 byte words
#define PROC_CNT 2 // Process count


extern uint32_t proc_init(uint32_t stack_pointer, void *cor_address);
extern void proc_start(uint32_t cor);
extern void ctx_swap(uint32_t *curr_cor, uint32_t next_cor);


uint32_t proc[PROC_CNT];
uint8_t pid_curr = 0;


void proc_create(void *proc_address)
{
	static uint8_t proc_ctr = 0;
	proc[proc_ctr] = proc_init((STACK_BASE - (proc_ctr*STACK_SIZE*4)), proc_address);
	proc_ctr++;
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
