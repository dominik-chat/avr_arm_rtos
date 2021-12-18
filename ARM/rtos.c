#include "rtos.h"
#include "lpc21xx.h"


#define mCOUNTER_ENABLE			1
#define mINTERRUPT_ON_MR0		1
#define mRESET_ON_MR0			(1<<1)
#define mMR0_INTERRUPT			1
#define VIC_TIMER0_CHANNEL_NR		4
#define mIRQ_SLOT_ENABLE		(1<<5)

#define STACK_BASE 0x40004000 // Base stack address - must be word aligned
#define STACK_SIZE 128 // Stack size for process - in 4 byte words
#define PROC_CNT 3 // Process count
#define SEM_CNT 2 //Semaphores count

#define SEM_NONE -1

#define SVC_TYPE_SEM_TAKE	1
#define SVC_TYPE_SEM_GIVE	2

extern uint32_t proc_init(uint32_t stack_pointer, void *cor_address);
extern void proc_start(uint32_t cor);
extern void ctx_swap(uint32_t *curr_cor, uint32_t next_cor);
extern void timer0_int_handler(void);
extern void svc_sem_take(uint8_t sem_nr);
extern void svc_sem_give(uint8_t sem_nr);


typedef struct
{
	uint32_t sp;
	int8_t sem_idx;
}process_data;

process_data proc[PROC_CNT];
uint8_t pid_curr = 0;
int8_t sem[SEM_CNT];


void proc_create(void *proc_address)
{
	static uint8_t proc_ctr = 0;

	proc[proc_ctr].sp = proc_init((STACK_BASE - (proc_ctr*STACK_SIZE*4)), proc_address);
	proc[proc_ctr].sem_idx = SEM_NONE;

	proc_ctr++;
}

void proc_run(uint8_t proc_number)
{
	proc_start(proc[proc_number].sp);
}

void sem_take(uint8_t sem_nr)
{
	svc_sem_take(sem_nr);
}

void sem_give(uint8_t sem_nr)
{
	svc_sem_give(sem_nr);
}

void proc_interrupts_init(unsigned int uiPeriod)
{
	VICIntEnable |= (0x1 << VIC_TIMER0_CHANNEL_NR);
	VICVectCntl0  = mIRQ_SLOT_ENABLE | VIC_TIMER0_CHANNEL_NR;
	VICVectAddr0  = (unsigned long)timer0_int_handler;

	T0MR0 = 3 * uiPeriod;
	T0MCR |= (mINTERRUPT_ON_MR0 | mRESET_ON_MR0);

	T0TCR |=  mCOUNTER_ENABLE;
}

void proc_resume(uint8_t pid_next)
{
	uint8_t pid_prev = pid_curr;

	if(pid_curr != pid_next)
	{
		pid_curr = pid_next;
		ctx_swap(&proc[pid_prev].sp, proc[pid_next].sp);
	}
}

void resched()
{
	uint8_t pid_next = pid_curr;

	do
	{
		pid_next = (pid_next+1) % PROC_CNT;
	} while(proc[pid_next].sem_idx != SEM_NONE);

	proc_resume(pid_next);
}

void syscall_sem_take(uint8_t sem_nr)
{
	if(sem[sem_nr] == 1)
	{
		sem[sem_nr] = 0;
		proc[pid_curr].sem_idx = SEM_NONE;
	}
	else
	{
		proc[pid_curr].sem_idx = sem_nr;
		resched();
	}
}

void syscall_sem_give(uint8_t sem_nr)
{
	for(uint8_t i = 0; i < PROC_CNT; i++)
	{
		if (proc[i].sem_idx == sem_nr)
		{
			proc[i].sem_idx = SEM_NONE;
			proc_resume(i);
			return;
		}
	}

	sem[sem_nr] = 1;
}

void svc_callback(uint32_t argument, uint8_t type)
{
	switch(type)
	{
	case SVC_TYPE_SEM_TAKE:
		syscall_sem_take((uint8_t)argument);
		break;
	case SVC_TYPE_SEM_GIVE:
		syscall_sem_give((uint8_t)argument);
		break;
	}
}

void timer0_callback(void)
{
	resched();

	T0IR = mMR0_INTERRUPT;
	VICVectAddr = 0x00;
}
