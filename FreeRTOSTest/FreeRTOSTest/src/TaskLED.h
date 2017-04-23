/*
 * TaskLED.h
 *
 * Created: 2016-12-14
 * Author: Axel Lundberg and Jonas Eiselt
 */ 


#ifndef TASKLED_H_
#define TASKLED_H_

#define LED0_GPIO 10

#define TASK_LED_STACK_SIZE     (1024/sizeof(portSTACK_TYPE))
#define TASK_LED_STACK_PRIORITY     (1)

void task_led(void *pvParameters);

#endif /* TASKLED_H_ */