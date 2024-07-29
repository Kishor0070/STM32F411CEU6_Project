/*
 * custom_systick.h
 *
 *  Created on: Jul 22, 2024
 *      Author: bhadula.kishor
 */

#ifndef CUSTOM_SYSTICK_H_
#define CUSTOM_SYSTICK_H_

#include "stm32f411xe.h"
#include "core_cm4.h"
#include "stdbool.h"
#include <stdint.h>

// This counter will count until at max 2 seconds then will start again...



void systick_init(void);
void task_50ms(void);
void task_100ms(void);


#endif /* CUSTOM_SYSTICK_H_ */
