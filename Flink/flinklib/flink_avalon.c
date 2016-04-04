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
 *  NIOS II Avalon bus communication module                        *
 *                                                                 *
 *******************************************************************/

/** @file flink_avalon.c
 *  @brief Provides the communication over the Avalon bus.
 *
 *  @author Raphael Lauber
 */

#include "types.h"
#include "flink.h"
#include "hal.h"
#include "list.h"
#include "flink_core.h"
#include "flink_avalon.h"
#ifdef AVALON
//	#include "io.h"
#endif 

#include <stdlib.h>
#include <stdint.h>
//#include <system.h>

uint8_t avalon_read8(uint32_t addr) {
	// 8 bit transfers not supported in flink avalon
	return -1;
}

uint16_t avalon_read16(uint32_t addr) {
	// 8 bit transfers not supported in flink avalon
	return -1;
}

uint32_t avalon_read32(uint32_t addr) {

	uint32_t val = 0;
	#ifdef AVALON
		//val = IORD(addr,0); //_32DIRECT(addr, 0);
	#endif 
	return val;
}

int avalon_write8(uint32_t addr, uint8_t val) {
	// 8 bit transfers not supported in flink avalon
 	return -1;
}

int avalon_write16(uint32_t addr, uint16_t val) {
	// 8 bit transfers not supported in flink avalon
	return -1;
}

int avalon_write32(uint32_t addr, uint32_t val) {
	#ifdef AVALON
	//IOWR(addr,0,val); //_32DIRECT(addr,0,val);
	#endif 
	return 0;
}

uint32_t avalon_address_space_size(flink_dev* fdev) {
	 return MAX_ADDRESS_SPACE;
}

struct flink_bus_ops avalon_bus_ops = {
	.read8              = avalon_read8,
	.read16             = avalon_read16,
	.read32             = avalon_read32,
	.write8             = avalon_write8,
	.write16            = avalon_write16,
	.write32            = avalon_write32,
	.address_space_size = avalon_address_space_size,
};

