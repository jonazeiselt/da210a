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

#define STACK_SIZE     (1024/sizeof(portSTACK_TYPE))

void vLEDTask(void *pvParameters);

void vBlinkTask(void *pvParameters);

void vReadTask(void *pvParameters);

void vRedTask(void *pvParameters);

void vButtonTask(void *pvParameters);

void vButtonInterruptHandler(void);

#endif /* ARDUINOTASKS_H_ */