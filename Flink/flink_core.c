/*
 * flink_core.c
 *
 * Created: 23.12.2015 11:50:37
 *  Author: Raphael Lauber
 */ 

#include "flinklib.h"
#include "flink.h"
#include "list.h"
#include "flink_core.h"
#include <avr/io.h>
#include <stdlib.h>
#include <string.h>

struct flink_subdev* flink_core_get_subdevice_by_id(struct flink_dev* fdev, uint8_t id);

/**
 * @brief Allocate a flink_device structure.
 * @return flink_device*: Pointer to the new flink_device structure, or NULL on failure.
 */
struct flink_dev* flink_device_alloc(void) {
	struct flink_dev* fdev = malloc(sizeof(flink_dev));
	if(fdev) {
		INIT_LIST_HEAD(&(fdev->list));
	}
	return fdev;
}

int flink_core_open(struct flink_private_data* pdata) {
	//struct flink_device* fdev = flink_get_device_by_cdev(i->i_cdev);
	struct flink_private_data* p_data = malloc(sizeof(struct flink_private_data));
	memset(p_data, 0, sizeof(*p_data));
	//p_data->fdev = fdev;
	//f = p_data;
	//#if defined(DBG)
	//printk(KERN_DEBUG "[%s] Device node opened.", MODULE_NAME);
	//#endif
	return 0;
}

int flink_core_relase(struct flink_private_data* f) {
	free(f);
	//#if defined(DBG)
	//printk(KERN_DEBUG "[%s] Device node closed.", MODULE_NAME);
	//#endif
	return 0;
}

int flink_select_subdevice(struct flink_private_data* pdata, uint8_t subdevice, uint8_t excl) {
	//struct flink_private_data* pdata = (struct flink_private_data*)(f->private_data);
	if(!subdevice) { //read_nof_subdevices =pdata != NULL && pdata->fdev != NULL) {
		//struct flink_dev* fdev = pdata->fdev;
		pdata->current_subdevice = flink_core_get_subdevice_by_id(pdata->fdev, subdevice);
		// TODO exclusive access
		// 		#if defined(DBG)
		// 		printk(KERN_DEBUG "[%s] Selecting subdevice %u", MODULE_NAME, subdevice);
		// 		if(excl) printk(KERN_DEBUG "  -> exclusive");
		// 		else printk(KERN_DEBUG "  -> not exclusive");
		// 		#endif
		return 0;
	}
	return UNKOWN_ERROR;
}

struct flink_subdev* flink_core_get_subdevice_by_id(struct flink_dev* fdev, uint8_t id) {
	if(fdev != NULL) {
		struct flink_subdev* subdev;
		//#if defined(DBG)
		//printk(KERN_DEBUG "[%s] Looking for subdevice with id '%u' in device %u...", MODULE_NAME, id, fdev->id);
		//#endif
		list_for_each_entry(subdev, &(fdev->subdevices), list) {
			if(subdev->id == id) {
				//#if defined(DBG)
				//printk(KERN_DEBUG "[%s] Subdevice with id '%u' found!", MODULE_NAME, id);
				//#endif
				return subdev;
			}
		}
		//#if defined(DBG)
		//printk(KERN_DEBUG "[%s] No subdevice with id '%u' found!", MODULE_NAME, id);
		//#endif
	}
	return NULL;
}

/**
 * @brief Add a flink device to the system, making it live immediately.
 * @param fdev: The flink device to add. 
 * @return int: A negative error code is returned on failure.
 */
int flink_device_add(struct flink_dev* fdev) {
	static unsigned int dev_counter = 0;
	unsigned int nof_subdevices = 0;
	if(fdev != NULL) {
		// Add device to list
		fdev->id = dev_counter++;
		list_add(&(fdev->list), &device_list);
		//#if defined(DBG)
		//	printk(KERN_DEBUG "[%s] Device with id '%u' added to device list.", MODULE_NAME, fdev->id);
		//#endif
		
		// Scan for subdevices
		nof_subdevices = scan_for_subdevices(fdev);
		//#if defined(DBG)
		//	printk(KERN_DEBUG "[%s] %u subdevice(s) added to device #%u", MODULE_NAME, nof_subdevices, fdev->id);
		//#endif
		
		// Create device node
		create_device_node(fdev);
		
		return fdev->id;
	}
	return UNKOWN_ERROR;
}

/**
 * create_device_node() - creates a device node for a flink device
 * @fdev: the flink device to create a device node for
 */
static int create_device_node(struct flink_dev* fdev) {
	static unsigned int dev_counter = 0;
	int error = 0;
	dev_t dev;
	
	// Allocate, register and initialize char device
	error = alloc_chrdev_region(&dev, dev_counter, 1, MODULE_NAME);
	if(error) {
		printk(KERN_ERR "[%s] Allocation of char dev region failed!", MODULE_NAME);
		goto alloc_chardev_region_failed;
	}
	fdev->char_device = cdev_alloc();
	if(fdev->char_device == NULL) {
		printk(KERN_ERR "[%s] Allocation of char dev failed!", MODULE_NAME);
		goto cdev_alloc_failed;
	}
	cdev_init(fdev->char_device, &flink_fops);
	fdev->char_device->owner = THIS_MODULE;
	error = cdev_add(fdev->char_device, dev, 1);
	if(error) {
		printk(KERN_ERR "[%s] Adding the char dev to the system failed!", MODULE_NAME);
		goto cdev_add_failed;
	}
	
	// create device node
	fdev->sysfs_device = device_create(sysfs_class, NULL, dev, NULL, "flink%u", dev_counter);
	if(IS_ERR(fdev->sysfs_device)) {
		printk(KERN_ERR "[%s] Creation of sysfs device failed!", MODULE_NAME);
		goto device_create_failed;
	}
	
	#if defined(DBG)
		printk(KERN_DEBUG "[%s] Device node created: flink%u", MODULE_NAME, dev_counter);
	#endif
	
	dev_counter++;
	
	return 0;
	
	// Cleanup on error
device_create_failed:
	cdev_del(fdev->char_device);
		
cdev_add_failed:
	fdev->char_device = NULL;

cdev_alloc_failed:
	unregister_chrdev_region(dev, 1);
		
alloc_chardev_region_failed:
	// nothing to do
		
	return error;
}

/**
 * scan_for_subdevices() - scan flink device for subdevices
 * @fdev: the flink device to scan
 *
 * Scans the device for available subdevices and adds them to
 * the device structure. The number of added subdevices is returned.
 */
static unsigned int scan_for_subdevices(struct flink_device* fdev) {
	unsigned int subdevice_counter = 0;
	uint32_t current_address = 0;
	uint32_t last_address = current_address + fdev->bus_ops->address_space_size(fdev) - 1;
	uint32_t current_function = 0;
	uint32_t current_mem_size = 0;
	uint32_t total_mem_size = 0;
	struct flink_subdevice* new_subdev;
	
	//#if defined(DBG)
	//	printk(KERN_DEBUG "[%s] Scanning device #%u for subdevices...", MODULE_NAME, fdev->id);
	//	printk(KERN_DEBUG "  -> Start address:      0x%x", current_address);
	//	printk(KERN_DEBUG "  -> Last valid address: 0x%x", last_address);
	//#endif
	while(current_address < last_address && subdevice_counter < MAX_NOF_SUBDEVICES) {
		current_function = (fdev->bus_ops->read32(fdev, current_address + SUBDEV_FUNCTION_OFFSET));
		current_mem_size = fdev->bus_ops->read32(fdev, current_address + SUBDEV_SIZE_OFFSET);

// 		#if defined(DBG)
// 			printk(KERN_DEBUG "[%s] subdevice size: 0x%x (current address: 0x%x)\n", MODULE_NAME, current_mem_size, current_address);
// 		#endif

		if(current_mem_size > MAIN_HEADER_SIZE + SUB_HEADER_SIZE) {
			// Create and initialize new subdevice
			new_subdev = flink_subdevice_alloc();
			flink_subdevice_init(new_subdev);
			new_subdev->function_id = (u16)(current_function >> 16);
			new_subdev->sub_function_id = (u8)((current_function >> 8) & 0xFF);
			new_subdev->function_version = (u8)(current_function & 0xFF);
			new_subdev->base_addr = current_address;
			new_subdev->mem_size = current_mem_size;
			new_subdev->nof_channels = fdev->bus_ops->read32(fdev, current_address + SUBDEV_NOFCHANNELS_OFFSET);
			new_subdev->unique_id = fdev->bus_ops->read32(fdev, current_address + SUBDEV_UNIQUE_ID_OFFSET);
			
			// Add subdevice to flink device
			flink_subdevice_add(fdev, new_subdev);
			subdevice_counter++;
			
			// if subdevice is info subdevice -> read memory length
			if(new_subdev->function_id == INFO_FUNCTION_ID) {
				total_mem_size = fdev->bus_ops->read32(fdev, current_address + MAIN_HEADER_SIZE + SUB_HEADER_SIZE);
				last_address = total_mem_size - 1;
				#if defined(DBG)
					printk(KERN_DEBUG "[%s] Info subdevice found: total memory length=0x%x", MODULE_NAME, total_mem_size);
				#endif
			}

			// Increment address counter and reset temp variables
			current_address += current_mem_size;
			current_function = 0;
			current_mem_size = 0;
		}
		else {
			#if defined(DBG)
				printk(KERN_ALERT "[%s] aborting\n", MODULE_NAME);
			#endif
			break;
		}
	}
	return subdevice_counter;
}
