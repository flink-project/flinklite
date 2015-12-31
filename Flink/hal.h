/*
 * hal.h
 *
 * Created: 15.12.2015 11:51:18
 *  Author: Raphael Lauber
 */ 


#ifndef HAL_H_
#define HAL_H_


#include "flinklib.h"
#include <avr/io.h>

int flink_read_bit(flink_subdev*, uint32_t, uint8_t, void*);
int flink_write_bit(flink_subdev*, uint32_t, uint8_t, void*);


#endif /* HAL_H_ */