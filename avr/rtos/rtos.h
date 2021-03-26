#ifndef RTOS_H_
#define RTOS_H_

#include <avr/io.h> //uint + isr
#include <avr/interrupt.h>

void proc_create(void *proc_address);

void proc_run(uint8_t proc_number);

void proc_sleep(uint16_t ticks);

void proc_interrupt_init();

#endif /* RTOS_H_ */
