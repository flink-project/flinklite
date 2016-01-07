/*
 * flink_core.c
 *
 * Created: 23.12.2015 11:50:37
 *  Author: Raphael Lauber
 */ 
 
#include "types.h"
#include "flink.h"
#include "list.h"
#include "flink_core.h"
#include "flink_spi.h"
#include "hal.h"
#include <avr/io.h>
#include <stdlib.h>
#include <string.h>

static unsigned int scan_for_subdevices(flink_dev* fdev);
//
static LIST_HEAD(device_list);
//static LIST_HEAD(loaded_if_modules);
//
///**
 //* @brief Allocate a flink_device structure.
 //* @return flink_device*: Pointer to the new flink_device structure, or NULL on failure.
 //*/
flink_dev* flink_device_alloc(void) {
	flink_dev* fdev = malloc(sizeof(flink_dev));
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


int flink_core_open(flink_private_data* pdata) {
	//struct flink_device* fdev = flink_get_device_by_cdev(i->i_cdev);
//	pdata = malloc(sizeof(flink_private_data));
//	memset(pdata, 0, sizeof(*pdata));
	//p_data->fdev = fdev;
	//f = p_data;
	//#if defined(DBG)
	//printk(KERN_DEBUG "[%s] Device node opened.", MODULE_NAME);
	//#endif
	pdata->fdev = flink_device_alloc(); // notwendig?
	flink_set_bus(&spi_bus_ops);
	flink_device_init(pdata->fdev, &spi_bus_ops); // TODO: Use other bus_ops for other channel
	//fdev->bus_data = spiData;
	flink_device_add(pdata->fdev);	// creates device nodes
	return 0;
}

//int flink_core_relase(struct flink_private_data* f) {
	//free(f);
	////#if defined(DBG)
	////printk(KERN_DEBUG "[%s] Device node closed.", MODULE_NAME);
	////#endif
	//return 0;
//}
//
//int flink_select_subdevice(struct flink_private_data* pdata, uint8_t subdevice, uint8_t excl) {
	////struct flink_private_data* pdata = (struct flink_private_data*)(f->private_data);
	//if(!subdevice) { //read_nof_subdevices =pdata != NULL && pdata->fdev != NULL) {
		////struct flink_dev* fdev = pdata->fdev;
		//pdata->current_subdevice = flink_core_get_subdevice_by_id(pdata->fdev, subdevice);
		//// TODO exclusive access
		//// 		#if defined(DBG)
		//// 		printk(KERN_DEBUG "[%s] Selecting subdevice %u", MODULE_NAME, subdevice);
		//// 		if(excl) printk(KERN_DEBUG "  -> exclusive");
		//// 		else printk(KERN_DEBUG "  -> not exclusive");
		//// 		#endif
		//return 0;
	//}
	//return UNKOWN_ERROR;
//}


/**
 * @brief Add a flink device to the system, making it live immediately.
 * @param fdev: The flink device to add. 
 * @return int: A negative error code is returned on failure.
 */
int flink_device_add(flink_dev* fdev) {
	static unsigned int dev_counter = 0;
	unsigned int nof_subdevices = 0;
	if(fdev != NULL) {
		// Add device to list
		fdev->id = dev_counter++;
	    list_add(&(fdev->list), &device_list);
		////#if defined(DBG)
		////	printk(KERN_DEBUG "[%s] Device with id '%u' added to device list.", MODULE_NAME, fdev->id);
		////#endif
		//
		// Scan for subdevices
		nof_subdevices = scan_for_subdevices(fdev);
		////#if defined(DBG)
		////	printk(KERN_DEBUG "[%s] %u subdevice(s) added to device #%u", MODULE_NAME, nof_subdevices, fdev->id);
		////#endif
		
		// Create device node
		//create_device_node(fdev);
		
		return fdev->id;
	}
	return UNKOWN_ERROR;
}
//
///**
 //* create_device_node() - creates a device node for a flink device
 //* @fdev: the flink device to create a device node for
 //*/
////static int create_device_node(struct flink_dev* fdev) {
	////static unsigned int dev_counter = 0;
	////int error = 0;
	//////dev_t dev;
	////
	////// Allocate, register and initialize char device
//// 	error = alloc_chrdev_region(&dev, dev_counter, 1, MODULE_NAME);
//// 	if(error) {
//// 		printk(KERN_ERR "[%s] Allocation of char dev region failed!", MODULE_NAME);
//// 		goto alloc_chardev_region_failed;
//// 	}
//// 	fdev->char_device = cdev_alloc();
//// 	if(fdev->char_device == NULL) {
//// 		//printk(KERN_ERR "[%s] Allocation of char dev failed!", MODULE_NAME);
//// 		goto cdev_alloc_failed;
//// 	}
//// 	cdev_init(fdev->char_device, &flink_fops);
//// 	fdev->char_device->owner = THIS_MODULE;
//// 	error = cdev_add(fdev->char_device, dev, 1);
//// 	if(error) {
//// 		printk(KERN_ERR "[%s] Adding the char dev to the system failed!", MODULE_NAME);
//// 		goto cdev_add_failed;
//// 	}
	////
	////// create device node
	////fdev->sysfs_device = device_create(sysfs_class, NULL, dev, NULL, "flink%u", dev_counter);
	////if(IS_ERR(fdev->sysfs_device)) {
		////printk(KERN_ERR "[%s] Creation of sysfs device failed!", MODULE_NAME);
		////goto device_create_failed;
	////}
	////
	////#if defined(DBG)
		////printk(KERN_DEBUG "[%s] Device node created: flink%u", MODULE_NAME, dev_counter);
	////#endif
	////
	////dev_counter++;
	////
	////return 0;
	////
	////// Cleanup on error
////device_create_failed:
	////cdev_del(fdev->char_device);
		////
////cdev_add_failed:
	////fdev->char_device = NULL;
////
////cdev_alloc_failed:
	////unregister_chrdev_region(dev, 1);
		////
////alloc_chardev_region_failed:
	////// nothing to do
		////
	////return error;
////}
//
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
	
	//#if defined(DBG)
	//	printk(KERN_DEBUG "[%s] Scanning device #%u for subdevices...", MODULE_NAME, fdev->id);
	//	printk(KERN_DEBUG "  -> Start address:      0x%x", current_address);
	//	printk(KERN_DEBUG "  -> Last valid address: 0x%x", last_address);
	//#endif
	while(current_address < last_address && subdevice_counter < MAX_NOF_SUBDEVICES) {
		current_function = (fdev->bus_ops->read32(current_address + SUBDEV_FUNCTION_OFFSET));
		current_mem_size = fdev->bus_ops->read32(current_address + SUBDEV_SIZE_OFFSET);

// 		#if defined(DBG)
// 			printk(KERN_DEBUG "[%s] subdevice size: 0x%x (current address: 0x%x)\n", MODULE_NAME, current_mem_size, current_address);
// 		#endif

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
// 				#if defined(DBG)
// 					printk(KERN_DEBUG "[%s] Info subdevice found: total memory length=0x%x", MODULE_NAME, total_mem_size);
// 				#endif
			}

			// Increment address counter and reset temp variables
			current_address += current_mem_size;
			current_function = 0;
			current_mem_size = 0;
		}
		else {
// 			#if defined(DBG)
// 				printk(KERN_ALERT "[%s] aborting\n", MODULE_NAME);
// 			#endif
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
// 		#if defined(DBG)
// 			printk(KERN_DEBUG "[%s] Subdevice with id '%u' added to device with id '%u'.", MODULE_NAME, fsubdev->id, fdev->id);
// 			printk(KERN_DEBUG "  -> Function:         0x%x/0x%x/0x%x", fsubdev->function_id, fsubdev->sub_function_id, fsubdev->function_version);
// 			printk(KERN_DEBUG "  -> Base address: 0x%x", fsubdev->base_addr);
// 			printk(KERN_DEBUG "  -> Size:         0x%x (%u bytes)", fsubdev->mem_size, fsubdev->mem_size);
// 			printk(KERN_DEBUG "  -> Nof Channels: %u", fsubdev->nof_channels);
// 			printk(KERN_DEBUG "  -> Unique id: 0x%x", fsubdev->unique_id);
// 		#endif
		
		// Register subdevice at interface module
		//if(fsubdev->register_hook != NULL) fsubdev->register_hook();
			
		return fsubdev->id;
	}
	return UNKOWN_ERROR;
}

/**
 * @brief Remove a flink subdevice from the parent device.
 * @param fsubdev: The flink subdevice to remove. 
 * @return int: A negative error code is returned on failure.
 */
int flink_subdevice_remove(flink_subdev* fsubdev) {
	if(fsubdev != NULL) {
		
		// Remove device from list
		list_del(&(fsubdev->list));
		//#if defined(DBG)
		//	printk(KERN_DEBUG "[%s] Subdevice with id '%u' removed from list.", MODULE_NAME, fsubdev->id);
		//#endif
		
		// Delete parent pointer
		fsubdev->parent = NULL;
			
		return 0;
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
		//#if defined(DBG)
		//	printk(KERN_DEBUG "[%s] Looking for subdevice with id '%u' in device %u...", MODULE_NAME, id, fdev->id);
		//#endif
		list_for_each_entry(subdev, &(fdev->subdev_list), list) {
			if(subdev->id == id) {
				//#if defined(DBG)
				//	printk(KERN_DEBUG "[%s] Subdevice with id '%u' found!", MODULE_NAME, id);
				//#endif
				return subdev;
			}
		}
		//#if defined(DBG)
		//	printk(KERN_DEBUG "[%s] No subdevice with id '%u' found!", MODULE_NAME, id);
		//#endif
	}
	return NULL;
}
