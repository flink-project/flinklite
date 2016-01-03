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
//
////#include "stdint.h"
//#include "flinklib.h"
//#include "flink.h"
#include "list.h"
#include <avr/io.h>

// ############ Device handles ############
typedef struct _flink_dev    flink_dev;
typedef struct _flink_subdev flink_subdev;
typedef struct _flink_private_data flink_private_data;

struct _flink_dev {
	struct list_head		list;			/// Linked list of all devices
	uint8_t					id;				/// Identifies a device
	uint8_t					nof_subdevices;	/// Number of subdevices
	flink_subdev*			subdevices;		/// Linked list of all subdevices of a device
	struct flink_bus_ops*	bus_ops;		/// Pointer to structure defining the bus operation functions of this device
};

struct _flink_subdev {
	uint8_t				id;					/// Identifies a subdevice within a device
	uint16_t			function_id;		/// Identifies the function of the subdevice
	uint8_t				sub_function_id;	/// Identifies the subtype of the subdevice
	uint8_t				function_version;	/// Version of the function
	uint32_t			base_addr;			/// Base address (logical)
	uint32_t			mem_size;			/// Address space size
	uint32_t			nof_channels;		/// Number of channels
	uint32_t			unique_id;			/// Unique id, must be unique for a certain subdevice
	struct list_head    list;				/// Linked list of all subdevices of a device
	flink_dev*			parent;				/// The device this subdevice belongs to
};

struct _flink_private_data {
	flink_dev*    fdev;
	flink_subdev* current_subdevice;
};

#endif // FLINKLIB_TYPES_H_
