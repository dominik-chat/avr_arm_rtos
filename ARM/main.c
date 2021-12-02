#include "stdint.h"
#include "lpc21xx.h"

#include "rtos.h"


#define mCOUNTER_ENABLE			1
#define mINTERRUPT_ON_MR0		1
#define mRESET_ON_MR0			(1<<1)
#define mMR0_INTERRUPT			1
#define VIC_TIMER0_CHANNEL_NR	4
#define mIRQ_SLOT_ENABLE		(1<<5)


extern void timer0_int_handler(void);


/* This is a function to simplify proc_* procedures */
void delay(void){
	for(unsigned int uiDelayCounter = 0; uiDelayCounter < 25000; uiDelayCounter++){}
}

/* This is a function to simplify proc_* procedures */
void pin_toggle(uint8_t pin_nr){
	uint32_t mask = (1 << pin_nr);
        if((IO1PIN & mask) != 0) IO1CLR = mask; else IO1SET = mask;
}

/* This is a function to simplify main */
void pin_init(void){
	IO1DIR = 0x30000;
}


void proc_A(void)
{
	while(1)
	{
		pin_toggle(16);
		delay();
		delay();
	}
}

void proc_B(void)
{
	while(1)
	{
		pin_toggle(17);
		delay();
	}
}

void timer0_callback(void)
{
	resched();

	T0IR = mMR0_INTERRUPT;
	VICVectAddr = 0x00;
}

void timer_interrupts_init(unsigned int uiPeriod)
{
	VICIntEnable |= (0x1 << VIC_TIMER0_CHANNEL_NR);
	VICVectCntl0  = mIRQ_SLOT_ENABLE | VIC_TIMER0_CHANNEL_NR;
	VICVectAddr0  = (unsigned long)timer0_int_handler;

	T0MR0 = 15 * uiPeriod;
	T0MCR |= (mINTERRUPT_ON_MR0 | mRESET_ON_MR0);

	T0TCR |=  mCOUNTER_ENABLE;
}

int main()
{
	pin_init();

	proc_create(proc_A);
	proc_create(proc_B);

	timer_interrupts_init(1000);
	proc_run(0);
}
