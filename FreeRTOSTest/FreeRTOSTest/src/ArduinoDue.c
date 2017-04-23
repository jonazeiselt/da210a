/*
* ArduinoDue.c
*
* Created: 2017-04-23 12:12:10
* Author: Jonas Eiselt
*
* Modified code from Task1501f in Inbyggda system och signaler
* Further reading: p. 631 in datasheet for SAM3x/SAM3A Series
*/

#include <inttypes.h>
#include "ArduinoDue.h"

#define PIOA_BASE_ADDRESS 0x400E0E00U

uint32_t *const p_PIOA_PER = (uint32_t*) (PIOA_BASE_ADDRESS+0x0000U);	/* defines the address for enabling the parallel Input/output A register */
uint32_t *const p_PIOA_OER = (uint32_t*) (PIOA_BASE_ADDRESS+0x0010U);	/* defines the address for enabling the parallel output A register */
uint32_t *const p_PIOA_SODR = (uint32_t*) (PIOA_BASE_ADDRESS+0x0030U);	/* defines the address for setting the output pins of the A register */
uint32_t *const p_PIOA_CODR = (uint32_t*) (PIOA_BASE_ADDRESS+0x0034U);	/* defines the address for clearing the output pins of the A register  */
uint32_t *const p_PIOA_PDSR = (uint32_t*) (PIOA_BASE_ADDRESS+0x003CU);	/* defines the address for getting pin value of the A register  */

void pinMode(uint32_t pin, uint32_t mode)
{
	if (mode == 1)
	{
		switch (pin)
		{
			case 23:
			*p_PIOA_PER |= (1<<14); /* Aktiverar bit 14  */
			*p_PIOA_OER |= (1<<14); /* Gör bit 14 till en Output */
			break;
			case 24:
			*p_PIOA_PER |= (1<<15);
			*p_PIOA_OER |= (1<<15);
			break;
			case 31:
			*p_PIOA_PER |= (1<<7);
			*p_PIOA_OER |= (1<<7);
			break;
			case 73:
			*p_PIOA_PER |= (1<<21);
			*p_PIOA_OER |= (1<<21);
			break;
		}
	}
	else
	{
		/* Do nothing */
	}
}

void digitalWrite(uint32_t pin, uint32_t value)
{
	if (value == 1)
	{
		switch (pin)
		{
			case 23:
			*p_PIOA_SODR |= (1<<14);
			break;
			case 24:
			*p_PIOA_SODR |= (1<<15);
			break;
			case 31:
			*p_PIOA_SODR |= (1<<7);
			break;
			case 73:
			*p_PIOA_SODR |= (1<<21);
			break;
		}
	}
	else if (value == 0)
	{
		switch (pin)
		{
			case 23:
			*p_PIOA_CODR |= (1<<14);
			break;
			case 24:
			*p_PIOA_CODR |= (1<<15);
			break;
			case 31:
			*p_PIOA_CODR |= (1<<7);
			break;
			case 73:
			*p_PIOA_CODR |= (1<<21);
			break;
		}
	}
}

uint32_t digitalRead(uint32_t pin)
{
	uint32_t value = 0;
	switch (pin)
	{
		case 23:
		value = (*p_PIOA_PDSR) & (1<<14);
		break;
		case 24:
		value = (*p_PIOA_PDSR) & (1<<15);
		break;
		case 31:
		value = (*p_PIOA_PDSR) & (1<<7);
		break;
		case 73:
		value = (*p_PIOA_PDSR) & (1<<21);
		break;
	}
	
	if (value > 0)
	{
		value = 1;
	}
	return value;
}