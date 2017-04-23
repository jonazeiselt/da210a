/*
 * ArduinoDue.h
 *
 * Created: 2017-04-23 12:12:25
 * Author: Jonas Eiselt
 *
 * Modified code from Task1501f in Inbyggda system och signaler
 */ 


#ifndef ARDUINODUE_H_
#define ARDUINODUE_H_

void pinMode(uint32_t pin, uint32_t mode);

void digitalWrite(uint32_t pin, uint32_t value);

uint32_t digitalRead(uint32_t pin);

#endif /* ARDUINODUE_H_ */