#ifndef RTOS_H_
#define RTOS_H_

#include "stdint.h"

void proc_create(void *proc_address);

void yield();

void proc_run(uint8_t proc_number);


#endif /* RTOS_H_ */
