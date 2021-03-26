#ifndef RTOS_H_
#define RTOS_H_

#include <avr/io.h> //uint + isr
#include <avr/interrupt.h>

void proc_create(void *proc_address);

void resched();

void proc_run(uint8_t proc_number);


#endif /* RTOS_H_ */
