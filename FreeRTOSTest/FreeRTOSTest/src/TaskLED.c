/*
 * TaskLED.c
 *
 * Created: 2016-12-14
 * Author: Axel Lundberg and Jonas Eiselt
 *
 * Code from assignment (Laboration 1601f)
 */ 

#include <asf.h>
#include "TaskLED.h"

/**
 *  This tasks makes the on-board LED blink every second
 */
void task_led(void *pvParameters)
{
    portTickType xLastWakeTime;
    const portTickType xTimeIncrement = 500;
    
	xLastWakeTime = xTaskGetTickCount(); /* Initialise the xLastWakeTime variable with the current time. */
    
	while (1) 
	{
        vTaskDelayUntil(&xLastWakeTime, xTimeIncrement); /* Wait for the next cycle. */
        gpio_toggle_pin(LED0_GPIO);
		
		printf("Hello\n");
    }
}