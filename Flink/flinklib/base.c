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
 *  fLink userspace library lite, base functionality               *
 *                                                                 *
 *******************************************************************/
 
/** @file base.c
 *  @brief Contains the base functionality for flink.
 *
 *  Contains functions to initialize, add and remove flink devices
 *  and subdevices
 *
 *  @author Martin Züger
 *  @author Urs Graf
 *  @author Raphael Lauber
 */

#include "flinklib.h"
#include "flink_core.h"
#include "flink.h"
#include "valid.h"

#include <avr/io.h>
#include <stdlib.h>
#include <string.h>

static flink_dev* m_fedv;

/*******************************************************************
 *                                                                 *
 *  Internal (private) methods                                     *
 *                                                                 *
 *******************************************************************/

/**
 * @brief Read number of subdevices from flink device.
 * 
 * @param dev: Private data structure to read
 * @return int: Number of flink devices or -1 in case of error.
 */
uint8_t read_nof_subdevices(flink_dev* fdev) {
	uint8_t n = 0;
	
	n = fdev->nof_subdevices;
	return n;
}

/**
 * @brief Read header of all subdevices and update flink device.
 * 
 * @param dev: Private data structure to update
 * @return int: number of subdevices read, or -1 in case of error.
 */
static int get_subdevices(flink_dev* fdev) {
	flink_subdev* subdev = NULL;
	flink_subdev* src;
	int i = 0;
	
	if(!validate_flink_dev(fdev)) {
		return EXIT_ERROR;
	}
	
	// Allocate memory
	fdev->subdevices = calloc(fdev->nof_subdevices, sizeof(flink_subdev));
	if(fdev->subdevices == NULL) { // allocation failed
		fdev->nof_subdevices = 0;
		return EXIT_ERROR;
	}
	
	// Fill up all information
	for(i = 0; i < fdev->nof_subdevices; i++) { // for each subdevice
		subdev = fdev->subdevices + i;
		subdev->id = i;
		
		src = flink_core_get_subdevice_by_id(fdev, i);
		if(src == NULL) {
			return EINVAL;
		}
			
		memcpy(subdev, src, sizeof(flink_subdev));	// transfer subdevice
		fdev->subdevices->parent = fdev;
		
	} // for
	
	return 0;
}

/*******************************************************************
 *                                                                 *
 *  Public methods                                                 *
 *                                                                 *
 *******************************************************************/

/**
 * @brief Opens a flink device file
 * @return flink_dev*: Pointer to the opened flink device or NULL in case of error.
 */
flink_dev* flink_open() {

	// Allocate memory for private data structure
 	m_fedv = malloc(sizeof(flink_dev));

	// Initialize structure
	flink_core_open(m_fedv);

	if(get_subdevices(m_fedv) < 0) { // reading subdevices failed
		return 0;
	}
	
	return m_fedv;
}


/**
 * @brief Close an open flink device
 * @param dev: device to close.
 * @return int: 0 on success, -1 in case of failure.
 */
int flink_close(flink_dev* dev) {
	
	if(!validate_flink_dev(dev)) {
		return EXIT_ERROR;
	}
	
	if(dev->subdevices) {
		free(dev->subdevices);
	}
	
	free(dev);
	return EXIT_SUCCESS;
}


/**
 * @brief Returns the number of subdevices of a fink device.
 * @param dev: Device to read
 * @return int: Number of flink devices or -1 in case of error.
 */
int flink_get_nof_subdevices(flink_dev* dev) {
	
	if(!validate_flink_dev(dev)) {
		return EXIT_ERROR;
	}
	
	return dev->nof_subdevices;
}


/**
 * @brief Reset a flink subdevice.
 * @param subdev: Subdevice to reset
 * @return int: 0 on success, else -1.
 */
int flink_subdevice_reset(flink_subdev* subdev) {
	uint32_t offset = CONFIG_OFFSET;
	uint8_t reset = 1;
	//
	if(!validate_flink_subdev(subdev)) {
		return EXIT_ERROR;
	}
	
	if(flink_write_bit(subdev, offset, RESET_BIT, &reset)) {
		return EXIT_ERROR;
	}
	return EXIT_SUCCESS;
}


/**
 * @brief Select a flink subdevice for further operations.
 * @param subdev: Subdevice to select.
 * @param exclusive: Block access to this subdevice for other processes.
 * @return int: 0 on success, else -1.
 */
int flink_subdevice_select(flink_subdev* subdev, uint8_t exclusive) {
	
	if(exclusive) {
		return flink_select_subdevice(m_fedv, subdev->id, 1);
	}else{
		return flink_select_subdevice(m_fedv, subdev->id, 0);
	}

}

/**
 * @brief Find subdevice of a device with a given id.
 * @param dev: Device to search.
 * @param subdev_id: Id of subdevice.
 * @return flink_subdev*: Pointer to the subdevice or NULL in case of error.
 */
flink_subdev* flink_get_subdevice_by_id(flink_dev* dev, uint8_t subdev_id) {
	
	// Check flink device structure
	if(!validate_flink_dev(dev)) {
		return NULL;
	}

	// Check subdevice id
	if(subdev_id > dev->nof_subdevices) {
		return NULL;
	}
	
	return dev->subdevices + subdev_id;
}

/**
 * @brief Find subdevice of a device with a given unique id.
 * @param dev: Device to search.
 * @param unique_id: Unique id of subdevice.
 * @return flink_subdev*: Pointer to the subdevice or NULL in case of error.
 */
flink_subdev* flink_get_subdevice_by_unique_id(flink_dev* dev, uint8_t unique_id) {
	flink_subdev* subdev = dev->subdevices;

	// Check flink device structure
	if(!validate_flink_dev(dev)) {
		return NULL;
	}

	while(subdev != NULL) {
		if(subdev->unique_id == unique_id) {
			//return dev->subdevices;	// Bug?
			return subdev;
		}
		subdev = subdev + 1;
	}
	return NULL;
}

/**
 * @brief Get the id of a subdevice.
 * @param subdev: The subdevice.
 * @return uint8_t: Id of the subdevice.
 */
uint8_t flink_subdevice_get_id(flink_subdev* subdev) {
	return subdev->id;
}

/**
 * @brief Get the function of a subdevice.
 * @param subdev: The subdevice.
 * @return uint16_t: Returns the function id.
 */
uint16_t flink_subdevice_get_function(flink_subdev* subdev) {
	return subdev->function_id;
}

/**
 * @brief Get the subfunction of a subdevice.
 * @param subdev: The subdevice.
 * @return uint8_t: Returns the subfunction id.
 */
uint8_t flink_subdevice_get_subfunction(flink_subdev* subdev) {
	return subdev->sub_function_id;
}

/**
 * @brief Get the function version of a subdevice.
 * @param subdev: The subdevice.
 * @return uint8_t: Returns the function version.
 */
uint8_t flink_subdevice_get_function_version(flink_subdev* subdev) {
	return subdev->function_version;
}

/**
 * @brief Get the base address of a subdevice.
 * @param subdev: The subdevice.
 * @return uint32_t: Returns the base address.
 */
uint32_t flink_subdevice_get_baseaddr(flink_subdev* subdev) {
	return subdev->base_addr;
}

/**
 * @brief Get the memory size of a subdevice.
 * @param subdev: The subdevice.
 * @return uint32_t: Returns the memory size.
 */
uint32_t flink_subdevice_get_memsize(flink_subdev* subdev) {
	return subdev->mem_size;
}

/**
 * @brief Get the number of channels of a subdevice.
 * @param subdev: The subdevice.
 * @return uint32_t: Returns the number of channels.
 */
uint32_t flink_subdevice_get_nofchannels(flink_subdev* subdev) {
	return subdev->nof_channels;
}

/**
 * @brief Get the unique id of a subdevice.
 * @param subdev: The subdevice.
 * @return uint32_t: Returns the unique id.
 */
uint32_t flink_subdevice_get_unique_id(flink_subdev* subdev) {
	return subdev->unique_id;
}
