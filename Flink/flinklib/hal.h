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
 *  flink userspace library lite, HAL prototypes                   *
 *                                                                 *
 *******************************************************************/
 
/** @file hal.c
 *  @brief Binding between communication drivers and hardware driver.
 *
 *  @author Raphael Lauber
 */

#ifndef HAL_H_
#define HAL_H_


#include "flinklib.h"

void flink_set_bus(struct flink_bus_ops*);
int flink_read_bit(flink_subdev*, uint32_t, uint8_t, void*);
int flink_write_bit(flink_subdev*, uint32_t, uint8_t, void*);


#endif /* HAL_H_ */