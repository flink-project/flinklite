/*! \brief		Hardware releated methods.
 *	\details	Contains Hardware initialization and definition stuff.
 *	\author		Raphael Lauber, NTB
 *	\date		01.12.2015
 */

#include <avr/io.h>
#include "board.h"

//! Initializations of the Hardware (GPIOs,...).
void initBoard(void) {
	
	/* GPIO */
	// Set outputs
	DDRB = ((1 << SPI_SS) | (1 << SPI_SCLK) | (1 << SPI_MOSI));
	DDRA = (1 << LED);
	
	/* SPI */
	#ifndef _USE_BB_SPI
		// Bit 7 - SPIE:	SPI Interrupt Enable
		// Bit 6 - SPE:		SPI Enable
		// Bit 5 - DORD:	Data Order
		// Bit 4 - MSTR:	Master/Slave Select
		// Bit 3 - CPOL:	Clock Polarity
		// Bit 2 - CPHA:	Clock Phase
		// Bits 1, 0 - SPR1, SPR0: SPI Clock Rate Select 1 and 0 (SPR1 = f_osc/64)
		// Bits 1, 0 - SPR1, SPR0: SPI Clock Rate Select 1 and 0 (SPI2X & SPR0 = f_osc/8)
 		SPCR = ((1 << SPE) | (1 << MSTR) | (1 << SPR0));
 		SPSR |= (1 << SPI2X);
	#endif
	PORTB |= (1 << SPI_SS);		// chip select high
	
	
} // initBoard