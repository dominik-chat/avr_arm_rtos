#ifndef RTOS_H_
#define RTOS_H_

#include "stdint.h"

/* system mode functions (before multitasking) */
void proc_create(void *proc_address);

void proc_run(uint8_t proc_number);

void proc_interrupts_init(unsigned int uiPeriod);

/* user mode functions (during multitasking) */
void proc_sleep(uint32_t ticks);

void sem_take(uint8_t sem_nr);

void sem_give(uint8_t sem_nr);

#endif /* RTOS_H_ */
