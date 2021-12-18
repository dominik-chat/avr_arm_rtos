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
#define PROC_CNT 2 // Process count
#define ALL_PROC_CNT (PROC_CNT+1) // Process count + idle

#define SVC_TYPE_SLEEP	0

extern uint32_t proc_init(uint32_t stack_pointer, void *cor_address);
extern void proc_start(uint32_t cor);
extern void ctx_swap(uint32_t *curr_cor, uint32_t next_cor);
extern void timer0_int_handler(void);
extern void svc_sleep(uint32_t ticks);


typedef struct
{
	uint32_t sp;
	uint32_t sleep_ctr;
}process_data;

process_data proc[ALL_PROC_CNT];
uint8_t pid_curr = 0;


void proc_create(void *proc_address)
{
	static uint8_t proc_ctr = 0;

	proc[proc_ctr].sp = proc_init((STACK_BASE - (proc_ctr*STACK_SIZE*4)), proc_address);
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

	if (pid_curr != pid_prev)
	{
		ctx_swap(&proc[pid_prev].sp, proc[pid_curr].sp);
	}
}

void proc_run(uint8_t proc_number)
{
	proc_start(proc[proc_number].sp);
}

void proc_sleep(uint32_t ticks)
{
	svc_sleep(ticks);
}

void syscall_sleep(uint32_t ticks)
{
	proc[pid_curr].sleep_ctr = ticks;
	resched();
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

void svc_callback(uint32_t argument, uint8_t type)
{
	if(type == SVC_TYPE_SLEEP)
	{
		syscall_sleep(argument);
	}
}

void timer0_callback(void)
{
	for(uint8_t i = 0; i < PROC_CNT; i++)
	{
		if(proc[i].sleep_ctr > 0)
		{
			proc[i].sleep_ctr--;
		}
	}

	resched();

	T0IR = mMR0_INTERRUPT;
	VICVectAddr = 0x00;
}
