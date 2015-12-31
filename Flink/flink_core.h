/*
 * flink_core.h
 *
 * Created: 23.12.2015 11:50:23
 *  Author: Raphael Lauber
 */ 


#ifndef FLINK_CORE_H_
#define FLINK_CORE_H_

#include <avr/io.h>

int flink_core_open(struct flink_private_data*);
int flink_core_relase(struct flink_private_data*);
int flink_select_subdevice(struct flink_private_data*, uint8_t, uint8_t);


#endif /* FLINK_CORE_H_ */