/*
 * isr.h
 *
 *  Created on: 30.01.2020
 *      Author: pbuczek
 */

#ifndef MAIN_ISR_H_
#define MAIN_ISR_H_

// FreeRTOS kernel
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>

void configureISR(QueueHandle_t switchQueue, TaskHandle_t eventDrivenTask, unsigned int modifiedHalfFlashDurationIsr);
void gpioPortJIsr(void);


#endif /* MAIN_ISR_H_ */
