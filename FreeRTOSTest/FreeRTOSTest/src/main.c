/**
* Author Jonas Eiselt
* Created 2017-04-20
*/

#include <asf.h>
#include "consoleFunctions.h"
#include "ArduinoTasks.h"

/* http://asf.atmel.com/docs/latest/sam.drivers.usart.usart_synchronous_example.sam3u_ek/html/sam_pio_quickstart_use_case_2.html */
void configure_button();

int main(void)
{
	/* Insert system clock initialization code here (sysclk_init()). */
	sysclk_init();
	board_init();

	/* Initialize console UART */
	configure_console();
	
	pio_set_output(PIOA, PIO_PA19, LOW, DISABLE, ENABLE);
	
	/* Initialize button with its own interrupt */
	configure_button();
		
	/* Print demo information on the terminal*/
	printf("-- FreeRTOS Exemple – Tasks --\n\r");
	printf("-- %s\n\r", BOARD_NAME);
	printf("-- Compiled: %s %s --\n\r", __DATE__, __TIME__);
		
	/* Create task with blinking TX-LED */
	if (xTaskCreate(vLEDTask, "Blink RX task", STACK_SIZE, NULL, 1, NULL) != pdPASS)
	{
		printf("Failed to create test led task\r\n");
	}

	/* Create task with blinking LED */
	if (xTaskCreate(vBlinkTask, "Blink led task", STACK_SIZE, NULL, 2, NULL) != pdPASS)
	{
		printf("Failed to create test blink task\r\n");
	}

// 	/* Create task which reads button */
// 	if (xTaskCreate(vReadTask, "Read button task", STACK_SIZE, NULL, 3, NULL) != pdPASS)
// 	{
// 		printf("Failed to create test button task\r\n");
// 	}
	
	/* Start the FreeRTOS scheduler running all tasks indefinitely*/
	vTaskStartScheduler();

	/* The program should only end up here if there isn't enough memory to create the idle task */
	while (1);
}

void configure_button()
{
	pio_set_input(PIOA, PIO_PA16, PIO_PULLUP);
	pio_handler_set(PIOA, ID_PIOA, PIO_PA16, PIO_IT_EDGE, vButtonInterruptHandler);
	pio_enable_interrupt(PIOA, PIO_PA16);
	NVIC_EnableIRQ(PIOA_IRQn);
}
