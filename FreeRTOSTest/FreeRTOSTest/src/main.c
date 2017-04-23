/**
* Author Jonas Eiselt
* Created 2017-04-20
*/

#include <asf.h>
#include "consoleFunctions.h"
#include "ArduinoTasks.h"

int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */
	sysclk_init();
	board_init();

	/* Initialise console UART */
	configure_console();

	/* Print demo information on the terminal*/
	printf("-- FreeRTOS Exemple – Tasks --\n\r");
	printf("-- %s\n\r", BOARD_NAME);
	printf("-- Compiled: %s %s --\n\r", __DATE__, __TIME__);
	
	/* Create task with blinking TX-LED */
	if (xTaskCreate(task_led, (const signed char * const) "LED", TASK_LED_STACK_SIZE, NULL, TASK_LED_STACK_PRIORITY, NULL) != pdPASS)
	{
		printf("Failed to create test led task\r\n");
	}

	/* Create task with blinking LED */
	if (xTaskCreate(task_blink, (const signed char * const) "BLINK", TASK_BLINK_STACK_SIZE, NULL, TASK_BLINK_STACK_PRIORITY, NULL) != pdPASS)
	{
		printf("Failed to create test blink task\r\n");
	}

	/* Create task which reads button */
	if (xTaskCreate(task_button, (const signed char * const) "BUTTON", TASK_BUTTON_STACK_SIZE, NULL, TASK_BUTTON_STACK_PRIORITY, NULL) != pdPASS)
	{
		printf("Failed to create test button task\r\n");
	}

	/* Start the FreeRTOS scheduler running all tasks indefinitely*/
	vTaskStartScheduler();

	/* The program should only end up here if there isn’t enough memory to create the idle task */
	while (1);
}
