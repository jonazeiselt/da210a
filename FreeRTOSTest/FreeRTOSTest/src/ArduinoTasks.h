/*
 * ArduinoTasks.h
 *
 * Created: 2016-12-14
 * Author: Axel Lundberg and Jonas Eiselt
 *
 * Modified: Jonas Eiselt
 */ 


#ifndef ARDUINOTASKS_H_
#define ARDUINOTASKS_H_

#define LED_RX 73

#define TASK_LED_STACK_SIZE     (1024/sizeof(portSTACK_TYPE))
#define TASK_LED_STACK_PRIORITY     (1)

#define TASK_BLINK_STACK_SIZE     (1024/sizeof(portSTACK_TYPE))
#define TASK_BLINK_STACK_PRIORITY     (2)

#define TASK_BUTTON_STACK_SIZE     (1024/sizeof(portSTACK_TYPE))
#define TASK_BUTTON_STACK_PRIORITY     (3)

void task_led(void *pvParameters);

void task_blink(void *pvParameters);

void task_button(void *pvParameters);

#endif /* ARDUINOTASKS_H_ */