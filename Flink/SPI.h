/*! \brief		Header for SPI.c.
 *	\details	Header for SPI communication library.
 *	\author		Raphael Lauber, NTB
 *	\date		01.12.2015
 */


#ifndef SPI_H_
#define SPI_H_

#include <avr/io.h>

/* Prototypes */
void SPI_Write(uint8_t*, uint8_t);
void SPI_Read(uint8_t*, uint8_t);
void SPI_WriteRead(uint8_t*, uint8_t, uint8_t*, uint8_t);

#endif /* SPI_H_ */