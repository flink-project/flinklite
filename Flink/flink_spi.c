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

//#include <linux/init.h>
//#include <linux/module.h>
//#include <linux/ioctl.h>
//#include <linux/fs.h>
//#include <linux/device.h>
//#include <linux/err.h>
//#include <linux/list.h>
//#include <linux/errno.h>
//#include <linux/mutex.h>
//#include <linux/slab.h>
//#include <linux/compat.h>
//#include <linux/spi/spi.h>
//#include <linux/delay.h>
//#include <asm/uaccess.h>

#include "flink.h"
#include "SPI.h"
#include "types.h"
#include "hal.h"
#include <avr/io.h>
#include <util/delay.h>

//#define DBG
// #define BUFSIZE 32
// #define THIS_MODULE "SPI"
// #define MODULE_NAME THIS_MODULE->name

//void list;	// TODO: linux/list.h?
uint8_t mSPIAdr[8];
uint8_t mSPIData[4];

// ############ Module Parameters ############
//static unsigned int dev_mem_length = MAX_ADDRESS_SPACE;

/// @brief SPI bus data
// struct spi_data {
// 	//spinlock_t			spi_lock;
// 	struct spi_device*	spi;
// 	u32*				txBuf;	// byte ordering in memory is platform specific
// 	u32*				rxBuf;
// 	unsigned long 		mem_size; // memory size of flink device including all subdevices
// };

// struct spi_transfer	t1 = {.len = 4,}, t2 = {.len = 4,}, r1 = {.len = 4,};
// struct spi_message m1,m2;
//static LIST_HEAD(device_list);

// ############ Bus communication functions ############
// u8 spi_read8(struct flink_device* fdev, u32 addr) {
// 	  #pragma message("8 bit transfers not supported in flink spi");
// 	return 0;
// }

// u16 spi_read16(struct flink_device* fdev, u32 addr) {
// 	#pragma message("16 bit transfers not supported in flink spi");
// 	return 0;
// }

u32 spi_read32(u32 addr) {
	//ssize_t	status = 0;
	// TODO: Extract data from fdev->bus_data
	// TODO: spi_data.txBuf/rxBuf = u32
	//struct spi_data* data = (struct spi_data*)fdev->bus_data;
	u32 val;
	//spi_message_init(&m1);
	//spi_message_init(&m2);
	mSPIAdr[0] = (addr & 0xff000000)  >> 24;
	mSPIAdr[1] = (addr & 0x00ff0000)  >> 16;
	mSPIAdr[2] = (addr & 0x0000ff00)  >> 8;
	mSPIAdr[3] = (addr & 0x000000ff);
	// TODO: bus_data has datatype void*, whats about address increment and data length?
// 	mSPIData[0] = ((uint32_t)fdev->bus_data & 0xff000000)  >> 24;
// 	mSPIData[1] = ((uint32_t)fdev->bus_data & 0x00ff0000)  >> 16;
// 	mSPIData[2] = ((uint32_t)fdev->bus_data & 0x0000ff00)  >> 8;
// 	mSPIData[3] = ((uint32_t)fdev->bus_data & 0x000000ff);
	//t1.tx_buf = data->txBuf;
	//*data->txBuf = addr;
	//r1.rx_buf = data->rxBuf;
	//spi_message_add_tail(&t1, &m1);
	//spi_message_add_tail(&r1, &m2);
	//status = spi_sync(data->spi, &m1);
	//status = spi_sync(data->spi, &m2);
	//val = *data->rxBuf;
	SPI_WriteRead(mSPIAdr,4,mSPIData,4);
	val = ((u32)mSPIData[0] << 24) | ((u32)mSPIData[1] << 16) | ((u32)mSPIData[2] << 8) | (mSPIData[3]);
	//printk(KERN_DEBUG "[%s] read from addr: 0x%x\n", MODULE_NAME, (u32)*data->txBuf);
	//printk(KERN_DEBUG "[%s] read: 0x%x\n", MODULE_NAME, val);
	return val;
}

// int spi_write8(struct flink_device* fdev, u32 addr, u8 val) {
// 	#pragma message("8 bit transfers not supported in flink spi");
// 	return -1;
// }

// int spi_write16(struct flink_device* fdev, u32 addr, u16 val) {
// 	#pragma message("8 bit transfers not supported in flink spi");
// 	return -1;
// }

int spi_write32(u32 addr, u32 val) {
	//ssize_t	status = 0;
	// TODO: Extract data from fdev->bus_data
	//struct spi_data* data = (struct spi_data*)fdev->bus_data;
	//spi_message_init(&m1);
	//spi_message_init(&m2);
	mSPIAdr[0] = (addr & 0xff000000)  >> 24;
	mSPIAdr[0] |= 0x80;	// set write bit
	mSPIAdr[1] = (addr & 0x00ff0000)  >> 16;
	mSPIAdr[2] = (addr & 0x0000ff00)  >> 8;
	mSPIAdr[3] = (addr & 0x000000ff);
	// TODO: bus_data has datatype void*, whats about address increment and data length?
	mSPIAdr[4] = (val & 0xff000000)  >> 24;
	mSPIAdr[5] = (val & 0x00ff0000)  >> 16;
	mSPIAdr[6] = (val & 0x0000ff00)  >> 8;
	mSPIAdr[7] = (val & 0x000000ff);
	//t1.tx_buf = data->txBuf;
	//*data->txBuf = addr | 0x80000000;	// set write bit
	//t2.tx_buf = data->txBuf + 1;
	//*(data->txBuf + 1) = val;
	//spi_message_add_tail(&t1, &m1);
	//spi_message_add_tail(&t2, &m2);
	//status = spi_sync(data->spi, &m1);
	//status = spi_sync(data->spi, &m2);
	SPI_Write(mSPIAdr,8);
	//printk(KERN_DEBUG "[%s] write to addr: 0x%x\n", MODULE_NAME, *data->txBuf);
	//printk(KERN_DEBUG "[%s] write: 0x%x\n", MODULE_NAME, *(data->txBuf+1));
	return 0;
}

// u32 spi_address_space_size(struct flink_device* fdev) {
// 	struct spi_data* data = (struct spi_data*)fdev->bus_data;
// 	return (u32)(data->mem_size);
// }
// 
 struct flink_bus_ops spi_bus_ops = {
// 	.read8              = spi_read8,
// 	.read16             = spi_read16,
 	.read32             = spi_read32,
// 	.write8             = spi_write8,
// 	.write16            = spi_write16,
 	.write32            = spi_write32
// 	.address_space_size = spi_address_space_size
 };
 
 void flink_spi_init() {
	 flink_device_init(&spi_bus_ops);
 }

// ############ Driver probe and release functions ############
// static int flink_spi_probe(struct spi_device *spi) {
// 	struct flink_device* fdev;
// 	struct spi_data* spiData;
// 
// 	#if defined(DBG)
// 		//printk(KERN_DEBUG "[%s] Run probe\n", MODULE_NAME);
// 	#endif
// 
// 	//spiData = kzalloc(sizeof(*spiData), GFP_KERNEL);	// Allocate driver data
// 	spiData = malloc(sizeoff(*spiData));
// 
// 	if (!spiData) return -1;//-ENOMEM;
// 	// Initialize the driver data
// 	spiData->spi = spi;
// 	//spin_lock_init(&spiData->spi_lock);
// 
// 	spi_set_drvdata(spi, spiData);
// 
// 	spiData->mem_size = dev_mem_length;
// 	spiData->txBuf = malloc(BUFSIZE);	//kmalloc(BUFSIZE, GFP_KERNEL);	// Allocate buffers
// 	spiData->rxBuf = malloc(BUFSIZE); 	//kmalloc(BUFSIZE, GFP_KERNEL);
// 	if (!spiData->txBuf || !spiData->rxBuf) {
// 		kfree(spiData);
// 		return -1;//-ENOMEM;
// 	}
// 
// 	fdev = flink_device_alloc();
// 	flink_device_init(fdev, &spi_bus_ops, THIS_MODULE);
// 	fdev->bus_data = spiData;
// 	flink_device_add(fdev);	// creates device nodes
// 
// 	return 0;
// }

// static int flink_spi_remove(struct spi_device *spi) {
// 	struct spi_data* spiData = spi_get_drvdata(spi);
// 	struct flink_device* fdev;
// 	struct flink_device* fdev_next;
// 
// 	#if defined(DBG)
// 		//printk(KERN_DEBUG "[%s] Run remove\n", MODULE_NAME);
// 	#endif
// 
// 	list_for_each_entry_safe(fdev, fdev_next, flink_get_device_list(), list) {
// 		if(fdev->appropriated_module == THIS_MODULE) {
// 			flink_device_remove(fdev);
// 			flink_device_delete(fdev);
// 		}
// 	}
// 
// 	/* make sure ops on existing fds can abort cleanly */
// 	//spin_lock_irq(&spiData->spi_lock);
// 	spiData->spi = NULL;
// 	spi_set_drvdata(spi, NULL);
// 	//spin_unlock_irq(&spiData->spi_lock);
// 	kfree(spiData->txBuf);
// 	kfree(spiData->rxBuf);
// 	kfree(spiData);
// 
// 	return 0;
// }

// ############ Data structures for spi driver ############
// static struct spi_driver flink_spi_driver = {
// 	.driver = {
// 		.name =	"flink_spi",
// 		.owner = THIS_MODULE,
// 	},
// 	.probe = flink_spi_probe,
// 	.remove = __exit_p(flink_spi_remove),
// };

