/*
* ArduinoTasks.c
*
* Created: 2016-12-14
* Author: Jonas Eiselt
*
* Further reading: Mastering the FreeRTOS Real Time Kernel: A Hands-On Tutorial Guide by Richard Barry
*/

#include <asf.h>
#include <inttypes.h>
#include "ArduinoDue.h"
#include "ArduinoTasks.h"

static xSemaphoreHandle xBinarySemaphore;

/**
*  This tasks makes the on-board LED blink every second
*/
void vLEDTask(void *pvParameters)
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

void vBlinkTask(void *pvParameters)
{
	portTickType xLastWakeTime;
	const portTickType xTimeIncrement = 500;
	
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

void vReadTask(void *pvParameters)
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

/* p. 22 in Mastering the FreeRTOS Real Time Kernel */
void vButtonTask(void *pvParameters)
{
	pio_set_output(PIOA, PIO_PA19, LOW, DISABLE, ENABLE);
	while (1)
	{
		xSemaphoreTake(xBinarySemaphore, portMAX_DELAY);

		/* Button pressed! */
		pio_toggle_pin(PIO_PA19);
		printf("Button pressed!");
	}
}

/*
 * Interrupt handler (p. 200)
 * http://asf.atmel.com/docs/latest/sam.drivers.usart.usart_synchronous_example.sam3u_ek/html/sam_pio_quickstart_use_case_2.html
 */
void vButtonInterruptHandler(const uint32_t id, const uint32_t index)
{
	if ((id == ID_PIOA) && (index == PIO_PA16))
	{
		if (pio_get(PIOA, PIO_TYPE_PIO_INPUT, PIO_PA16))
		{
			pio_clear(PIOA, PIO_PA19); // pin 42
		}
		else
		{
			pio_set(PIOA, PIO_PA19);
		}
	}
}