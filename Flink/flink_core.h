/*
 * flink_core.h
 *
 * Created: 23.12.2015 11:50:23
 *  Author: Raphael Lauber
 */ 


#ifndef FLINK_CORE_H_
#define FLINK_CORE_H_

#include <avr/io.h>

//// ############ Forward declarations ############
struct flink_private_data;


int flink_core_open(flink_private_data*);
flink_subdev* flink_core_get_subdevice_by_id(flink_dev*, uint8_t);
//int flink_core_relase(struct flink_private_data*);
//int flink_select_subdevice(struct flink_private_data*, uint8_t, uint8_t);
//
//
#endif /* FLINK_CORE_H_ */