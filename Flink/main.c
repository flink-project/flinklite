/*
 * Flink.c
 *
 * Created: 01.12.2015 11:08:03
 * Author : Raphael Lauber
 */ 

#include "board.h"
#include "SPI.h"
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    uint8_t data[8];
	uint8_t val[4];
	static uint8_t dataR[200];
	uint8_t i;
	
	initBoard();
	asm volatile ("nop");
	
	// Configure GPIO as output
 	data[0]  = 0x80;
 	data[1]  = 0x00;
 	data[2]  = 0x01;
 	data[3]  = 0xa0;
 	data[4]  = 0x00;
 	data[5]  = 0x00;
 	data[6]  = 0x00;
 	data[7]  = 0x0c;
 	SPI_Write(data, 8);
		 
    while (1) 
    {
		PORTA = (PINA & 0x01)^0x01;	// Toggle LED
		_delay_ms(500);
		
		// Read Range
		for (i = 0; i < 0x40 ; i+=0x04) {
			data[0] = 0x00;	// Read
			data[1] = 0x00;
			data[2] = 0x01;
			data[3] = 0x80 + i;
		
			SPI_WriteRead(data, 4, (dataR + i), 4);
			_delay_us(10);
		} // for

		// Read GPIO
		data[0]  = 0x00;
  		data[1]  = 0x00;
  		data[2]  = 0x01;
  		data[3]  = 0xa4;
		SPI_WriteRead(data, 4, val, 4);
		
		// Set GPIO
  		data[0]  = 0x80;
 		data[1]  = 0x00;
 		data[2]  = 0x01;
 		data[3]  = 0xa4;
 		data[4]  = 0x00;
 		data[5]  = 0x00;
 		data[6]  = 0x00;
 		data[7]  = ((val[3] & 0x3) << 2) | (val[3] & 0x3);
 		SPI_Write(data, 8);
		
    }
}

