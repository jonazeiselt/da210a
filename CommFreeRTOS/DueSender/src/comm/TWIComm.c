/**
* TWIComm.c
*
* Created: 2017-05-11 09:59:55
* Author: Jonas Eiselt
*/

#include <asf.h>
#include "comm/TWIComm.h"

static uint8_t tx_buffer[TX_DATA_LENGTH] = {};
static uint8_t rx_buffer[RX_DATA_LENGTH] = {};

twi_package_t tx_packet;
twi_package_t rx_packet;

void twi_init()
{
	/* Initializes TWI master options */
	twi_master_options_t opt;
	opt.speed = TWI_SPEED;
	
	/* Initializes the TWI master driver */
	if (twi_master_setup(TWI_PORT, &opt) == TWI_SUCCESS)
	{
		printf("Master initialized\r\n");
	}
}

void twi_send_packet(uint8_t request_byte, uint8_t recipient_addr)
{
	printf("Sending: %d\r\n", request_byte);
	tx_buffer[0] = request_byte;
	
	tx_packet.addr[0] = 0;							// TWI slave memory address data MSB
	tx_packet.addr[1] = 0;							// TWI slave memory address data LSB
	tx_packet.addr_length = 0;						// TWI slave memory address data size
	tx_packet.chip = recipient_addr;				// TWI slave bus address
	tx_packet.buffer = (void*) tx_buffer;			// transfer data source buffer
	tx_packet.length = TX_DATA_LENGTH;				// transfer data size (bytes)

	// Performs a multi-byte write access then check the result.
	// while(twi_master_write(TWI_PORT, &tx_packet) != TWI_SUCCESS);
	uint32_t status = twi_master_write(TWI_PORT, &tx_packet);
	// printf("Status: %d\r\n", status);
}

void twi_request_packet(uint8_t recipient_addr)
{
	rx_packet.addr[0] = 0;							// TWI slave memory address data MSB
	rx_packet.addr[1] = 0;							// TWI slave memory address data LSB
	rx_packet.addr_length = 0;						// TWI slave memory address data size
	rx_packet.chip = recipient_addr;				// TWI slave bus address
	rx_packet.buffer = (void*) rx_buffer;			// transfer data source buffer
	rx_packet.length = RX_DATA_LENGTH;				// transfer data size (bytes)
	
	// Performs a multi-byte read access then check the result.
	while (twi_master_read(TWI_PORT, &rx_packet) != TWI_SUCCESS);
	// indicate();
	
	for (int i = 0; i < RX_DATA_LENGTH; i++)
	{
		if (recipient_addr == UNO_BUS_ADDR)
		{
			printf("Got from Uno: %d\r\n", rx_buffer[i]);
		}
		else
		{
			printf("Got from Due: %d\r\n", rx_buffer[i]);
		}
	}
}

Bool crane_init()
{
	twi_send_packet(0x20, UNO_BUS_ADDR);
	twi_request_packet(UNO_BUS_ADDR);

	/* Check received data */
	twi_check_data();
	twi_request_packet(UNO_BUS_ADDR);

	return true;
}

void twi_check_data()
{
	switch (rx_buffer[0])
	{
		case 0x10:
		/* Identification */
		twi_send_packet(0x21, UNO_BUS_ADDR);
		break;
		case 0x11:
		/* Postion relative to object */
		twi_send_packet(0x11, UNO_BUS_ADDR);
		break;
		case 0x12:
		/* Position relative to box-edge */
		twi_send_packet(0x12, UNO_BUS_ADDR);
		break;
		case 0x13:
		/* Max velocity (mm/s) */
		twi_send_packet(0x13, UNO_BUS_ADDR);
		break;
		case 0x14:
		/* Lift success */
		twi_send_packet(0x14, UNO_BUS_ADDR);
		break;
		case 0x15:
		/* Lift failed */
		twi_send_packet(0x15, UNO_BUS_ADDR);
		break;
		case 0x16:
		/* Return success */
		twi_send_packet(0x16, UNO_BUS_ADDR);
		break;
		case 0x17:
		/* Return failed */
		twi_send_packet(0x17, UNO_BUS_ADDR);
		break;
		case 0x18:
		/* Adjust position */
		twi_send_packet(0x18, UNO_BUS_ADDR);
		break;
		case 0x19:
		/* Cancel adjustment */
		twi_send_packet(0x19, UNO_BUS_ADDR);
		break;
		default:
		// Do nothing...
		break;
	}
}

void indicate()
{
	for (int i = 0; i < 10; i++)
	{
		gpio_toggle_pin(LED0_GPIO);
		delay_ms(100);
	}
}