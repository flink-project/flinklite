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
 *  @brief Function prototypes for core module.
 *
 *  @author Raphael Lauber
 */

#ifndef FLINK_CORE_H_
#define FLINK_CORE_H_

// ############ Forward declarations ############
struct flink_private_data;


int flink_core_open(flink_dev*);
flink_subdev* flink_core_get_subdevice_by_id(flink_dev*, uint8_t);
int flink_select_subdevice(flink_dev*, uint8_t, uint8_t);

#endif /* FLINK_CORE_H_ */