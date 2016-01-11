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
 *  fLink userspace library lite, validation functions             *
 *                                                                 *
 *******************************************************************/

/** @file valid.c
 *  @brief Contains validation functions for flink.
 *
 *  @author Martin Züger
 */

#include "valid.h"

/**
 * @brief Checks if flink device was opened.
 * @param dev: flink device.
 * @return int: 1 if valid, 0 if not valid.
 */
int validate_flink_dev(flink_dev* dev) {
	if(dev != 0) {
		return 1; // device struct valid
	}
	return 0;
}

/**
 * @brief Checks if flink subdevice belongs to the device.
 * @param dev: flink subdevice.
 * @return int: 1 if valid, 0 if not valid.
 */
int validate_flink_subdev(flink_subdev* subdev) {
	if(subdev->parent) {
		return 1; // subdevice struct valid
	}
	return 0;
}
