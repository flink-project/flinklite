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
 *  flink userspace library lite, base prototypes                  *
 *                                                                 *
 *******************************************************************/
 
/** @file flink.c
 *  @brief Base function prototypes and data structures.
 *
 *  @author Martin Züger
 *  @author Urs Graf
 *  @author Raphael Lauber
 */

#ifndef FLINK_H_
#define FLINK_H_

#include "list.h"
#include "types.h"

// ############ flink error numbers ############
#define UNKOWN_ERROR	-1
#define EINVAL          22

// ############ Forward declarations ############
struct flink_dev;

// ############ flink bus operations ############

// @brief Functions to communicate with various bus communication modules
struct flink_bus_ops {
	uint8_t  (*read8)(uint32_t addr);				// read 1 byte
	uint16_t (*read16)(uint32_t addr);				// read 2 bytes
	uint32_t (*read32)(uint32_t addr);			/// read 4 bytes
	int (*write8)(uint32_t addr, uint8_t val);		// write 1 byte
	int (*write16)(uint32_t addr, uint16_t val);	// write 2 bytes
	int (*write32)(uint32_t addr, uint32_t val);						// write 4 bytes
	uint32_t (*address_space_size)(flink_dev*);							// get address space size
};

// ############ flink subdevice ############
#define MAX_NOF_SUBDEVICES 256

// ############ Public functions ############
flink_dev*		flink_device_alloc(flink_dev* fdev);
void            flink_device_init(flink_dev* fdev, struct flink_bus_ops* bus_ops);
int             flink_device_add(flink_dev* fdev);

flink_subdev*	flink_subdevice_alloc(void);
void			flink_subdevice_init(flink_subdev* fsubdev);
int				flink_subdevice_add(flink_dev* fdev, flink_subdev* fsubdev);

// ############ Constants ############
#define MAX_ADDRESS_SPACE 0x10000	// Maximum address space for a flink device

// Memory addresses and offsets
#define MAIN_HEADER_SIZE			16		// byte
#define SUB_HEADER_SIZE				16		// byte
#define SUBDEV_FUNCTION_OFFSET		0x0000	// byte
#define SUBDEV_SIZE_OFFSET			0x0004	// byte
#define SUBDEV_NOFCHANNELS_OFFSET	0x0008	// byte
#define SUBDEV_UNIQUE_ID_OFFSET		0x000C	// byte
#define SUBDEV_STATUS_OFFSET		0x0010	// byte
#define SUBDEV_CONFIG_OFFSET		0x0014	// byte

// Types
#define INFO_FUNCTION_ID			0x00

#endif /* FLINK_H_ */
