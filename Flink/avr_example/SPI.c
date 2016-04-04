/*! \brief		SPI library.
 *	\details	Contains methods for SPI communication.
 *	\author		Raphael Lauber, NTB
 *	\date		01.12.2015
 */


#include "SPI.h"
#include "board.h"
#include <avr/io.h>
#include <util/delay.h>

// Private prototypes
void bbSendByte(uint8_t);
void bbSendBit(uint8_t);
uint8_t bbReadBit();
uint8_t bbReadByte();


//! Transfer len-Bytes of data using SPI. /SS is set to low during transmission.
/*!
    \param data Pointer to the address where the to be send data are stored.
    \param len Number of bytes to be send.
    \sa SPI_Read()
*/
void SPI_Write(uint8_t *data, uint8_t len) {
	
	uint8_t i;
	
	#ifndef _USE_BB_SPI
		PORTB &= ~(1 << SPI_SS);	// SS low
	
		for(i = 0; i < len; i++) {
			SPDR = *(data + i);
			while(!(SPSR & (1 << SPIF)));	// wait until transmission finished
		} // for
	
		PORTB |= (1 << SPI_SS);	// SS high
	
	#else
	
		PORTB &= ~(1 << SPI_SS);	// SS low
	
		for(i = 0; i < len; i++) {
			if (i>0 && i%4==0) {
				PORTB |= (1 << SPI_SS);		// SS high
				_delay_us(1);
				PORTB &= ~(1 << SPI_SS);	// SS low
			}
			bbSendByte(*(data + i));
		} // for
	
		PORTB |= (1 << SPI_SS);	// SS high
		
	#endif
} // SPI_Write

//! Read len-Bytes of data using SPI. /SS is NOT set.
/*!
    \param data Pointer to the address where the data to be stored.
    \param len Number of bytes to be send.
    \sa SPI_Write()
*/
void SPI_Read(uint8_t *data, uint8_t len) {
	
	uint8_t i;
	
	#ifndef _USE_BB_SPI
	
		PORTB &= ~(1 << SPI_SS);	// SS low
	
		for(i = 0; i < len; i++) {
			SPDR = 0;
			while(!(SPSR & (1 << SPIF)));	// wait until new data arrived
			*(data + i) = SPDR;
		} // for
	
		PORTB |= (1 << SPI_SS);	// SS high
	
	#else
	
		PORTB |= (1 << SPI_SCLK);	// Clock high
		PORTB &= ~(1 << SPI_SS);	// SS low
	
		for(i = 0; i < len; i++) {
			*(data + i) = bbReadByte();
		} // for
	
		PORTB |= (1 << SPI_SS);	// SS high
		
	#endif
	
} // SPI_Read

void SPI_WriteRead(uint8_t *dataSend, uint8_t lenSend, uint8_t *dataRead, uint8_t lenRead) {
	
	volatile uint8_t i;
	
	#ifndef _USE_BB_SPI
	
		PORTB &= ~(1 << SPI_SS);	// SS low

		// Write Address	
		for(i = 0; i < lenSend; i++) {
			SPDR = *(dataSend + i);
			while(!(SPSR & (1 << SPIF)));	// wait until transmission finished
		} // for
	
		PORTB &= ~(1 << SPI_MOSI);	// MOSI low
 		PORTB |= (1 << SPI_SS);		// SS high
 		_delay_us(1);
 		PORTB &= ~(1 << SPI_SS);	// SS low
	
		// Read
		for(i = 0; i < lenRead; i++) {
			SPDR = 0;
			while(!(SPSR & (1 << SPIF)));	// wait until new data arrived
			*(dataRead + i) = SPDR;
			dataRi[i] = *(dataRead + i);
		} // for
	
		PORTB |= (1 << SPI_SS);		// SS high
	
	#else
	
		PORTB &= ~(1 << SPI_SS);	// SS low
		
		// Write Address
		for(i = 0; i < lenSend; i++) {
			bbSendByte(*(dataSend + i));
		} // for
		
		PORTB |= (1 << SPI_SS);		// SS high
		_delay_us(1);
		PORTB |= (1 << SPI_SCLK);	// Clock high
		PORTB &= ~(1 << SPI_SS);	// SS low
	
		// Read
		for(i = 0; i < lenRead; i++) {
			*(dataRead + i) = bbReadByte();
		} // for
	
		PORTB |= (1 << SPI_SS);		// SS high
	#endif
	
	
} // SPI_Read

//! SPI Bit-Bang low level driver. Performs one clock cycle and sets the data line.
/*!
    \param set Pointer to the address where the to be send data are stored.
    \sa bbReadBit(), bbSendByte(), bbReadByte()
*/
void bbSendBit(uint8_t set){
	
	uint8_t del = 0;
	PORTB &= ~(1 << SPI_SCLK);		// Clock low
	for(del = 0; del < 4; del++) asm volatile ("nop");
	// set high/low
	if(set) {
		PORTB |= (1 << SPI_MOSI);			
	} else {
		PORTB &= ~(1 << SPI_MOSI);		
	}
	PORTB |= (1 << SPI_SCLK);		// Clock high

} // bbSendBit

//! SPI Bit-Bang low level driver. Performs one clock cycle and reads the data line.
/*!
    \return Data line state, 1=high, 0=low
    \sa bbSendBit(), bbSendByte(), bbReadByte()
*/
uint8_t bbReadBit() {
	
	uint8_t del = 0;
	uint8_t val = 0;
	PORTB |= (1 << SPI_SCLK);		// Clock high
	for(del = 0; del < 4; del++) asm volatile ("nop");
	val = (PINB & (1 << SPI_MISO)) >> SPI_MISO;
	PORTB &= ~(1 << SPI_SCLK);		// Clock low
	return val;

} // bbReadBit

//! SPI Bit-Bang low level driver. Transmits 8 bit of data, SS is not handled.
/*!
    \param byte Data byte to transmit.
    \sa bbReadBit(), bbSendBit(), bbReadByte()
*/
void bbSendByte(uint8_t byte) {
	
	bbSendBit((byte & 0x80) >> 7);
	bbSendBit((byte & 0x40) >> 6);
	bbSendBit((byte & 0x20) >> 5);
	bbSendBit((byte & 0x10) >> 4);
	bbSendBit((byte & 0x08) >> 3);
	bbSendBit((byte & 0x04) >> 2);
	bbSendBit((byte & 0x02) >> 1);
	bbSendBit((byte & 0x01));
	PORTB &= ~(1 << SPI_MOSI);		// MOSI low
	PORTB &= ~(1 << SPI_SCLK);		// Clock low
	
} // bbSendByte

//! SPI Bit-Bang low level driver. Reads 8 bit data, SS is not handled.
/*!
    \return Read byte of data.
    \sa bbReadBit(), bbSendByte(), bbSendByte()
*/
uint8_t bbReadByte() {
	
	uint8_t val = 0;
	
	PORTB &= ~(1 << SPI_SCLK);		// Clock low
	val |= (bbReadBit() << 7);
	val |= (bbReadBit() << 6);
	val |= (bbReadBit() << 5);
	val |= (bbReadBit() << 4);
	val |= (bbReadBit() << 3);
	val |= (bbReadBit() << 2);
	val |= (bbReadBit() << 1);
	val |= bbReadBit();
	return val;
	
} // bbReadByte