/*
 * hal.h
 *
 * Created: 15.12.2015 11:51:18
 *  Author: Raphael Lauber
 */ 


#ifndef HAL_H_
#define HAL_H_

#include <avr/io.h>
#include "flinklib.h"

int flink_read_bit(flink_subdev*, uint32_t, uint8_t, void*);
int flink_write_bit(flink_subdev*, uint32_t, uint8_t, void*);

// ############ flink bus operations ############
/// @brief Functions to communicate with various bus communication modules
struct flink_bus_ops {
	//uint8_t  (*read8)(struct flink_device*, uint32_t addr);			/// read 1 byte
	//uint16_t (*read16)(struct flink_device*, uint32_t addr);			/// read 2 bytes
	uint32_t (*read32)(uint32_t addr);			/// read 4 bytes
	//int (*write8)(struct flink_device*, uint32_t addr, uint8_t val);		/// write 1 byte
	//int (*write16)(struct flink_device*, uint32_t addr, uint16_t val);	/// write 2 bytes
	int (*write32)(uint32_t addr, uint32_t val);	/// write 4 bytes
	//uint32_t (*address_space_size)(struct flink_device*);		/// get address space size
};

#endif /* HAL_H_ */