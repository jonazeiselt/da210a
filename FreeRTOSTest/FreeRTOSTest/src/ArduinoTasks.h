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

#define LED0_GPIO 10

#define TASK_LED_STACK_SIZE     (1024/sizeof(portSTACK_TYPE))
#define TASK_LED_STACK_PRIORITY     (1)

#define TASK_BLINK_STACK_SIZE     (1024/sizeof(portSTACK_TYPE))
#define TASK_BLINK_STACK_PRIORITY     (2)

void task_led(void *pvParameters);

void task_blink(void *pvParameters);

#endif /* ARDUINOTASKS_H_ */