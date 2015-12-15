/*
 * hal.c
 *
 * Created: 15.12.2015 11:51:32
 *  Author: Raphael Lauber
 */ 

#include "hal.h"
#include "flinklib.h"
#include "flink.h"
#include "types.h"
#include "valid.h"


// Communication bus
typedef struct flink_bus_ops FlinkBus  ;
FlinkBus* mFlinkBus;


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
	// TODO: Code is missing
// 	int res = 0;
// 	ssize_t write_size = 0;
// 	ioctl_container_t ioctl_arg;
// 	ioctl_arg.subdevice = subdev->id;
// 	ioctl_arg.offset    = offset;
// 	ioctl_arg.size      = size;
// 	ioctl_arg.data      = wdata;
// 	
// 	// Check data pointer
// 	if(wdata == NULL) {
// 		flink_error(FLINK_ENULLPTR);
// 		return EXIT_ERROR;
// 	}
// 	
// 	// Check flink subdevice structure
// 	if(!validate_flink_subdev(subdev)) {
// 		flink_error(FLINK_EINVALDEV);
// 		return EXIT_ERROR;
// 	}
// 	
// 	// write data to device
// 	write_size = flink_ioctl(subdev->parent, SELECT_AND_WRITE, &ioctl_arg);
// 	if(write_size == -1) {
// 		libc_error();
// 		return EXIT_ERROR;
// 	}
// 	
	return 0;
}

//void flink_device_init(struct flink_device* fdev, struct flink_bus_ops* bus_ops, struct module* mod) {
void flink_device_init(struct flink_bus_ops* bus_ops) {
	mFlinkBus = bus_ops;
}

