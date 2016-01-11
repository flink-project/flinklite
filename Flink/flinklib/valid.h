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
 *  fLink userspace library lite lite, validation functions        *
 *                                                                 *
 *******************************************************************/

/** @file valid.h
 *  @brief Contains validation functions for flink.
 *
 *  @author Martin Züger
 */

#ifndef FLINKLIB_VALID_H_
#define FLINKLIB_VALID_H_

#include "types.h"

int validate_flink_dev(flink_dev* dev);
int validate_flink_subdev(flink_subdev* subdev);

#endif // FLINKLIB_VALID_H_
