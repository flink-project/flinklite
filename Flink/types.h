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
 *  flink userspace library, types                                 *
 *                                                                 *
 *******************************************************************/

/** @file types.h
 *  @brief Data structures for flink devices and subdevices.
 *
 *  @author Martin Züger
 *  @author Urs Graf
 */

#ifndef FLINKLIB_TYPES_H_
#define FLINKLIB_TYPES_H_

//#include "stdint.h"
//#include "flinklib.h"

typedef unsigned char u8;
typedef unsigned char uint8_t;
typedef unsigned char bool;
typedef unsigned long uint32_t;
typedef unsigned int u16;
typedef unsigned long u32;
typedef unsigned int uint16_t;

typedef struct _flink_dev flink_dev;
typedef struct _flink_subdev flink_subdev;

struct _flink_dev {
	//int            fd;					/// File descriptor of open flink device file
	uint8_t        nof_subdevices;		/// Number of subdevices
	flink_subdev*  subdevices;			/// Linked list of all subdevices of a device
};

struct _flink_subdev {
	uint8_t        id;					/// Identifies a subdevice within a device
	uint16_t       function_id;			/// Identifies the function of the subdevice
	uint8_t        sub_function_id;		/// Identifies the subtype of the subdevice
	uint8_t        function_version;	/// Version of the function
	uint32_t       base_addr;			/// Base address (logical)
	uint32_t       mem_size;			/// Address space size
	uint32_t       nof_channels;		/// Number of channels
	uint32_t       unique_id;			/// Unique id, must be unique for a certain subdevice
	flink_dev*     parent;				/// The device this subdevice belongs to
};

#endif // FLINKLIB_TYPES_H_
