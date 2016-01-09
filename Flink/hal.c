/*
 * hal.c
 *
 * Created: 15.12.2015 11:51:32
 *  Author: Raphael Lauber
 */ 

#include "types.h"
#include "hal.h"
#include "flinklib.h"
#include "flink.h"
#include "valid.h"
#include "list.h"
#include <avr/io.h>
#include <stdarg.h>
#include <stdlib.h>

// Communication bus
typedef struct flink_bus_ops FlinkBus ;
FlinkBus* mFlinkBus;

void flink_set_bus(struct flink_bus_ops* bus_channel) {
	mFlinkBus = bus_channel;
}

/**
 * @brief Read a single bit from a flink subdevice
 * @param subdev: Subdevice to read from.
 * @param offset: Read offset, relative to the subdevice base address.
 * @param bit: Bit number to read in the byte given by offset.
 * @param rdata: Pointer to a buffer where the bit read should be written
 * @return int: 0 on succes, else -1.
 */
int flink_read_bit(flink_subdev* subdev, uint32_t offset, uint8_t bit, void* rdata) {

	uint32_t temp;
	
 	// Check data pointer
 	if(rdata == NULL) {
// 		flink_error(FLINK_ENULLPTR);
 		return EXIT_ERROR;
 	}
// 	
 	// Check flink subdevice structure
 	if(!validate_flink_subdev(subdev)) {
// 		flink_error(FLINK_EINVALDEV);
 		return EXIT_ERROR;
 	}

	 temp = mFlinkBus->read32(subdev->base_addr + offset);
	 *((uint32_t*)rdata) = ((temp & (1 << bit)) != 0);
	 
	return EXIT_SUCCESS;
}

/**
 * @brief Write a single bit to a flink subdevice
 * @param subdev: Subdevice to write to.
 * @param offset: Write offset, relative to the subdevice base address.
 * @param bit: Bit number to write in the byte given by offset.
 * @param wdata: Bit to write, a value of nonzero sets the bit, 0 clears the bit
 * @return int
 */
int flink_write_bit(flink_subdev* subdev, uint32_t offset, uint8_t bit, void* wdata) {
	
	uint32_t temp;

 	// Check data pointer
 	if(wdata == NULL) {
// 		flink_error(FLINK_ENULLPTR);
 		return EXIT_ERROR;
 	}
// 	
 	// Check flink subdevice structure
 	if(!validate_flink_subdev(subdev)) {
// 		flink_error(FLINK_EINVALDEV);
 		return EXIT_ERROR;
 	}
	 
	temp = mFlinkBus->read32(subdev->base_addr + offset);
	if(*((uint8_t*)wdata) != 0) { // set bit
		temp |= (1 << bit);
	}
	else { // clear bit
		temp &= ~(1 << bit);
	}
	mFlinkBus->write32(subdev->base_addr + offset, temp);
	
	return EXIT_SUCCESS;
}


size_t flink_write(flink_subdev* subdev, uint32_t offset, uint8_t size, void* wdata) {
	
 	// Check data pointer
 	if(wdata == NULL) {
// 		flink_error(FLINK_ENULLPTR);
 		return EXIT_ERROR;
 	}
// 	
 	// Check flink subdevice structure
 	if(!validate_flink_subdev(subdev)) {
// 		flink_error(FLINK_EINVALDEV);
 		return EXIT_ERROR;
 	}
 	
	if (offset > subdev->mem_size) {
		return -1;
	}
	switch(size) {
		case 1: {
			// 8 Bit not supported
			return -1;
		}
		case 2: {
			// 16 Bit not supported
			return -1;
		}
		case 4: {
			mFlinkBus->write32(subdev->base_addr + offset, *((uint32_t*)wdata));
			return sizeof(*((uint32_t*)wdata));
		}
		default:
		return -1;
	}
	return 0;
}

/**
 * @brief Read from a flink subdevice.
 * @param subdev: Subdevice to read from.
 * @param offset: Read offset, relative to the subdevice base address.
 * @param size: Nof bytes to read.
 * @param rdata: Pointer to a buffer where the read bytes are written to.
 * @return ssize_t: Nof bytes read from the subdevcie or a negative error code.
 */
size_t flink_read(flink_subdev* subdev, uint32_t offset, uint8_t size, void* rdata) {
// 	int res = 0;
// 	ssize_t read_size = 0;
// 	ioctl_container_t ioctl_arg;
// 	ioctl_arg.subdevice = subdev->id;
// 	ioctl_arg.offset    = offset;
// 	ioctl_arg.size      = size;
// 	ioctl_arg.data      = rdata;
// 	
	// Check data pointer
	if(rdata == NULL) {
//		flink_error(FLINK_ENULLPTR);
		return EXIT_ERROR;
	}
	
	// Check flink subdevice structure
	if(!validate_flink_subdev(subdev)) {
//		flink_error(FLINK_EINVALDEV);
		return EXIT_ERROR;
	}
// 
			
			if (offset > subdev->mem_size) {
				return -1;
			}
			switch(size) {
				case 1: {
					// 8 Bit data not supported
					return -1;
				}
				case 2: {
					// 16 Bit data not supported
					return -1;
				}
				case 4: {
					*((uint32_t*)rdata) = mFlinkBus->read32(subdev->base_addr + offset);
					return sizeof(*((uint32_t*)rdata));
				}
				default:
				return -1;
			}
	
	return 0;
}