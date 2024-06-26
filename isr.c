/*
 * isr.c
 *
 *  Created on: 30.01.2020
 *      Author: pbuczek
 */

#include <stdint.h>
#include <inc/tm4c1294ncpdt.h>  // board parameterization

// FreeRTOS kernel
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>

// project specific interrupt service routines (ISR)
#include "isr.h"

static QueueHandle_t switchQueue_;
static TaskHandle_t eventDrivenTask_;
static unsigned int modifiedHalfFlashDurationIsr_;

void configureISR(QueueHandle_t switchQueue, TaskHandle_t eventDrivenTask, unsigned int modifiedHalfFlashDurationIsr) {

    switchQueue_ = switchQueue;
    eventDrivenTask_ = eventDrivenTask;
    modifiedHalfFlashDurationIsr_ = modifiedHalfFlashDurationIsr;

}

void gpioPortJIsr(void) {

    // save the interrupt source
    uint32_t mis = GPIO_PORTJ_AHB_MIS_R;

    // clear the interrupt bits
    GPIO_PORTJ_AHB_ICR_R = mis;

    /**
     *  The xHigherPriorityTaskWoken parameter must be initialized to pdFALSE as
     *  it will get set to pdTRUE inside the interrupt safe API function if a
     *  context switch is required.
     */
    BaseType_t xHigherPriorityTaskWoken0 = pdFALSE;
    BaseType_t xHigherPriorityTaskWoken1 = pdFALSE;

    // check if the button at pin 1 generated the interrupt
    // if (...) {
        // add element modifiedHalfFlashDurationIsr_ to the queue switchQueue_
        // use xHigherPriorityTaskWoken0 variable to properly call vTaskNotifyGiveFromISR below
        // ...
    //}


    /**
     * Notify (wake up) the event processing task (eventDrivenTask_)
     */

    /**
     *  Send a notification directly to the task to which interrupt processing is
     *  being deferred.
     *  eventDrivenTask_ - the handle of the task to which the notification
     *  is being sent. The handle was saved when the task was created.
     */
    // use xHigherPriorityTaskWoken1 variable to properly call vTaskNotifyGiveFromISR below
    // ...

    /* Pass the xHigherPriorityTaskWoken value into portYIELD_FROM_ISR(). If
    xHigherPriorityTaskWoken was set to pdTRUE inside vTaskNotifyGiveFromISR()
    then calling portYIELD_FROM_ISR() will request a context switch. If
    xHigherPriorityTaskWoken is still pdFALSE then calling
    portYIELD_FROM_ISR() will have no effect. The implementation of
    portYIELD_FROM_ISR() used by the Windows port includes a return statement,
    which is why this function does not explicitly return a value. */
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken0 | xHigherPriorityTaskWoken1);

}
