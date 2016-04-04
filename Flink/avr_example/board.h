/*! \brief		Header for board.c.
 *	\details	Header for Hardware configuration file.
 *	\author		Raphael Lauber, NTB
 *	\date		01.12.2015
 */

#ifndef BOARD_H_
#define BOARD_H_

/* Use BitBang driver instead of the SPI Machine */
#define _USE_BB_SPI

/* Pins */
#define SPI_SS		PB0
#define SPI_SCLK	PB1
#define SPI_MOSI	PB2
#define SPI_MISO	PB3

#define LED			PA0

/* Board Clock */
#define F_CPU		8000000

/* Prototypes */
void initBoard(void);


#endif /* BOARD_H_ */