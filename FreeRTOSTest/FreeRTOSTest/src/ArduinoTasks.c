/*
 * ArduinoTasks.c
 *
 * Created: 2016-12-14
 * Author: Axel Lundberg and Jonas Eiselt
 *
 * Code from assignment (Laboration 1601f)
 *
 * Modified: Jonas Eiselt
 */ 

#include <asf.h>
#include <inttypes.h>
#include "ArduinoDue.h"
#include "ArduinoTasks.h"

/**
 *  This tasks makes the on-board LED blink every second
 */
void task_led(void *pvParameters)
{
	portTickType xLastWakeTime;
    const portTickType xTimeIncrement = 500;
    
	xLastWakeTime = xTaskGetTickCount(); /* Initialize the xLastWakeTime variable with the current time. */
   
	pinMode(LED_RX, 1);
    
    uint32_t toggle = 1;
    while (1)
    {
	    vTaskDelayUntil(&xLastWakeTime, xTimeIncrement); /* Wait for the next cycle. */
	    
	    if (toggle == 1)
	    {
		    toggle = 0;
	    }
	    else
	    {
		    toggle = 1;
	    }
	    digitalWrite(LED_RX, toggle);
    }
}

void task_blink(void *pvParameters)
{
	portTickType xLastWakeTime;
	const portTickType xTimeIncrement = 500; /* 1000 ms in between */
	
	xLastWakeTime = xTaskGetTickCount(); 
	
	pinMode(23, 1);
	
	uint32_t toggle = 0;
	while (1)
	{
		vTaskDelayUntil(&xLastWakeTime, xTimeIncrement); /* Wait for the next cycle. */
		
		if (toggle == 1)
		{
			toggle = 0;
		}
		else 
		{
			toggle = 1;
		}
		digitalWrite(23, toggle);
	}
}

void task_button(void *pvParameters) 
{
	portTickType xLastWakeTime;
	const portTickType xTimeIncrement = 4000; /* The bigger value, the bigger latency */ 
	
	xLastWakeTime = xTaskGetTickCount(); /* Initialize the xLastWakeTime variable with the current time. */
	
	pinMode(24, 1); // 1 = output, 0 = input
	pinMode(31, 0); 
	
	while (1)
	{
		vTaskDelayUntil(&xLastWakeTime, xTimeIncrement); /* Wait for the next cycle. */
		
		uint32_t buttonValue = digitalRead(31);
		printf("Button value: %d\r\n", buttonValue);
		
		if (buttonValue == 1)
		{
			digitalWrite(24, 1);
		}
		else
		{
			digitalWrite(24, 0);
		}
	}
}