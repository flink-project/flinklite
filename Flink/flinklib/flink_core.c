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
 *  flink userspace library lite, Core Module                      *
 *                                                                 *
 *******************************************************************/
 
/** @file flink_core.c
 *  @brief Core module for flink.
 *
 *  Contains functions to initialize, add and remove flink devices
 *  and subdevices
 *
 *  @author Martin Züger
 *  @author Urs Graf
 *  @author Raphael Lauber
 */
 
#include "types.h"
#include "flink.h"
#include "list.h"
#include "flink_core.h"
#include "flink_spi.h"
#include "hal.h"

#include <stdlib.h>
#include <string.h>

static unsigned int scan_for_subdevices(flink_dev* fdev);
//
static LIST_HEAD(device_list);

/**
 * @brief Allocate a flink_device structure.
 * @return flink_device*: Pointer to the new flink_device structure, or NULL on failure.
 */
flink_dev* flink_device_alloc(flink_dev* fdev) {
	//flink_dev* fdev = malloc(sizeof(flink_dev));
	if(fdev) {
		INIT_LIST_HEAD((&fdev->list));
	}
	return fdev;
}

/**
 * @brief Initialize a flink_device structure
 * @param fdev: The structure to initialize
 * @param bus_ops: The flink_bus_ops for this device, remember them when adding them to
 * system with flink_device_add().
 * @param mod: The kernel module this flink uses for hardware access.
 */
void flink_device_init(flink_dev* fdev, struct flink_bus_ops* bus_ops) {
	memset(fdev, 0, sizeof(*fdev));
	INIT_LIST_HEAD(&(fdev->list));
	INIT_LIST_HEAD(&(fdev->subdev_list));
	fdev->bus_ops = bus_ops;
}


int flink_core_open(flink_dev* fdev) {
	//fdev = flink_device_alloc();
	flink_set_bus(&spi_bus_ops);
	flink_device_init(fdev, &spi_bus_ops); // TODO: Use other bus_ops for other channel
	flink_device_add(fdev);	// creates device nodes
	return 0;
}


int flink_select_subdevice(flink_dev* fdev, uint8_t subdevice, uint8_t excl) {
	
	if(!subdevice) {
		fdev->current_subdevice = flink_core_get_subdevice_by_id(fdev, subdevice);
		return 0;
	}
	return UNKOWN_ERROR;
}

/**
 * @brief Add a flink device to the system, making it live immediately.
 * @param fdev: The flink device to add. 
 * @return int: A negative error code is returned on failure.
 */
int flink_device_add(flink_dev* fdev) {
	static unsigned int dev_counter = 0;
	
	if(fdev != NULL) {
		// Add device to list
		fdev->id = dev_counter++;
	    list_add(&(fdev->list), &device_list);
		// Scan for subdevices
		scan_for_subdevices(fdev);
		return fdev->id;
	}
	return UNKOWN_ERROR;
}

/**
 * scan_for_subdevices() - scan flink device for subdevices
 * @fdev: the flink device to scan
 *
 * Scans the device for available subdevices and adds them to
 * the device structure. The number of added subdevices is returned.
 */
static unsigned int scan_for_subdevices(flink_dev* fdev) {
	unsigned int subdevice_counter = 0;
	uint32_t current_address = 0;
	uint32_t last_address = current_address + fdev->bus_ops->address_space_size(fdev) - 1;
	uint32_t current_function = 0;
	uint32_t current_mem_size = 0;
	uint32_t total_mem_size = 0;
	flink_subdev* new_subdev;
	
	while(current_address < last_address && subdevice_counter < MAX_NOF_SUBDEVICES) {
		current_function = (fdev->bus_ops->read32(current_address + SUBDEV_FUNCTION_OFFSET));
		current_mem_size = fdev->bus_ops->read32(current_address + SUBDEV_SIZE_OFFSET);

		if(current_mem_size > MAIN_HEADER_SIZE + SUB_HEADER_SIZE) {
			// Create and initialize new subdevice
			new_subdev = flink_subdevice_alloc();
			flink_subdevice_init(new_subdev);
			new_subdev->function_id = (uint16_t)(current_function >> 16);
			new_subdev->sub_function_id = (uint8_t)((current_function >> 8) & 0xFF);
			new_subdev->function_version = (uint8_t)(current_function & 0xFF);
			new_subdev->base_addr = current_address;
			new_subdev->mem_size = current_mem_size;
			new_subdev->nof_channels = fdev->bus_ops->read32(current_address + SUBDEV_NOFCHANNELS_OFFSET);
			new_subdev->unique_id = fdev->bus_ops->read32(current_address + SUBDEV_UNIQUE_ID_OFFSET);
			
			// Add subdevice to flink device
			flink_subdevice_add(fdev, new_subdev);
			subdevice_counter++;
			
			// if subdevice is info subdevice -> read memory length
			if(new_subdev->function_id == INFO_FUNCTION_ID) {
				total_mem_size = fdev->bus_ops->read32(current_address + MAIN_HEADER_SIZE + SUB_HEADER_SIZE);
				last_address = total_mem_size - 1; //Todo: probably a bug in FlinkVHDL
			}

			// Increment address counter and reset temp variables
			current_address += current_mem_size;
			current_function = 0;
			current_mem_size = 0;
		}
		else {
			break;
		}
	}
	return subdevice_counter;
}


/**
 * @brief Allocate a flink_subdevice structure.
 * @return flink_subdevice*: Pointer to the new flink_subdevice structure, or NULL on failure.
 */
flink_subdev* flink_subdevice_alloc(void) {
	flink_subdev* fsubdev = malloc(sizeof(flink_subdev));
	if(fsubdev) {
		INIT_LIST_HEAD(&(fsubdev->list));
	}
	return fsubdev;
}

/**
 * @brief Initialize a flink_subdevice structure, making it ready to add to a flink_device
 * with flink_subdevice_add()
 * @param fsubdev: The structure to initialize
 */
void flink_subdevice_init(flink_subdev* fsubdev) {
	memset(fsubdev, 0, sizeof(*fsubdev));
	INIT_LIST_HEAD(&(fsubdev->list));
}

/**
 * @brief Add a flink subdevice to flink device.
 * @param fdev: The flink device to which the subdevice is added. 
 * @param @fsubdev: The flink subdevice to add. 
 * @return int: A negative error code is returned on failure.
 */
int flink_subdevice_add(flink_dev* fdev, flink_subdev* fsubdev) {
	if(fdev != NULL && fsubdev != NULL) {
		// Define subdevice id
		fsubdev->id = fdev->nof_subdevices++;
		
		// Set parent pointer
		fsubdev->parent = fdev;
		
		// Add subdevice to device
		list_add(&(fsubdev->list), &(fdev->subdev_list));
		return fsubdev->id;
	}
	return UNKOWN_ERROR;
}

/**
 * @brief Get a flink subdevice by its id.
 * @param fdev: The flink device containing the desired flink_subdevice. 
 * @param id: The id of the flink device. 
 * @return flink_subdevice*: Returns the flink_subdevice structure with the given id. 
 * NULL is returned if no subdevice is found with the given id.
 */
flink_subdev* flink_core_get_subdevice_by_id(flink_dev* fdev, uint8_t id) {
	if(fdev != NULL) {
		flink_subdev* subdev;
		
		list_for_each_entry(subdev, &(fdev->subdev_list), list) {
			if(subdev->id == id) {
				return subdev;
			}
		}
	}
	return NULL;
}
