/*******************************************************************
 *   _________     _____      _____    ____  _____    ___  ____    *
 *  |_   ___  |  |_   _|     |_   _|  |_   \|_   _|  |_  ||_  _|   *
 *    | |_  \_|    | |         | |      |   \ | |      | |_/ /     *
 *    |  _|        | |   _     | |      | |\ \| |      |  __'.     *
 *   _| |_        _| |__/ |   _| |_    _| |_\   |_    _| |  \ \_   *
 *  |_____|      |________|  |_____|  |_____|\____|  |____||____|  *
 *                                                                 *
 *******************************************************************
 *                                                                 *
 *  SPI bus communication module                                   *
 *                                                                 *
 *******************************************************************/

/** @file flink_spi.c
 *  @brief Provides the communication over SPI to the FPGA.
 *
 *  @author ?
 *  @author Raphael Lauber
 */

#include "../types.h"
#include "../flink.h"
#include "../hal.h"
#include "../list.h"
#include "../flink_core.h"
#include "flink_spi.h"

uint8_t mSPIAdr[8];
uint8_t mSPIData[4];

uint8_t spi_read8(uint32_t addr) {
	// 8 bit transfers not supported in flink spi
	return -1;
}

uint16_t spi_read16(uint32_t addr) {
	// 8 bit transfers not supported in flink spi
	return -1;
}

uint32_t spi_read32(uint32_t addr) {

	uint32_t val;

	mSPIAdr[0] = (addr & 0xff000000)  >> 24;
	mSPIAdr[1] = (addr & 0x00ff0000)  >> 16;
	mSPIAdr[2] = (addr & 0x0000ff00)  >> 8;
	mSPIAdr[3] = (addr & 0x000000ff);

	//SPI_WriteRead(mSPIAdr,4,mSPIData,4);
	val = ((uint32_t)mSPIData[0] << 24) | ((uint32_t)mSPIData[1] << 16) | ((uint32_t)mSPIData[2] << 8) | (mSPIData[3]);


	return val;
}

int spi_write8(uint32_t addr, uint8_t val) {
	// 8 bit transfers not supported in flink spi
 	return -1;
}

int spi_write16(uint32_t addr, uint16_t val) {
	// 8 bit transfers not supported in flink spi
	return -1;
}

int spi_write32(uint32_t addr, uint32_t val) {

	mSPIAdr[0] = (addr & 0xff000000)  >> 24;
	mSPIAdr[0] |= 0x80;	// set write bit
	mSPIAdr[1] = (addr & 0x00ff0000)  >> 16;
	mSPIAdr[2] = (addr & 0x0000ff00)  >> 8;
	mSPIAdr[3] = (addr & 0x000000ff);
	
	mSPIAdr[4] = (val & 0xff000000)  >> 24;
	mSPIAdr[5] = (val & 0x00ff0000)  >> 16;
	mSPIAdr[6] = (val & 0x0000ff00)  >> 8;
	mSPIAdr[7] = (val & 0x000000ff);
	
	//SPI_Write(mSPIAdr,8);
	
	return 0;
}

uint32_t spi_address_space_size(flink_dev* fdev) {
	 return MAX_ADDRESS_SPACE;
}
 
struct flink_bus_ops spi_bus_ops = {
	.read8              = spi_read8,
	.read16             = spi_read16,
	.read32             = spi_read32,
	.write8             = spi_write8,
	.write16            = spi_write16,
	.write32            = spi_write32,
	.address_space_size = spi_address_space_size,
};

