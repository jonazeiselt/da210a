/*
 * ArduinoDue.h
 *
 * Created: 2017-04-23 12:12:25
 * Author: Jonas Eiselt
 */ 


#ifndef ARDUINODUE_H_
#define ARDUINODUE_H_

void pinMode(int pin, int mode);

void digitalWrite(int pin, int value);

uint32_t digitalRead(int pin);

#endif /* ARDUINODUE_H_ */