/*
 * flink_axi.c
 *
 *  Created on: 26.05.2016
 *      Author: tinner
 */

#include "xil_io.h"
#include "../flinklib.h"



uint32_t offset =  0;

uint8_t axi_read8(uint32_t addr) {
	return Xil_In8(offset + addr);
}

uint16_t axi_read16(uint32_t addr) {
	return Xil_In16(offset + addr);
}

uint32_t axi_read32(uint32_t addr) {
	return Xil_In32(offset + addr);
}

int axi_write8(uint32_t addr, uint8_t val) {
	Xil_Out8(offset + addr,val);
 	return  1;
}

int axi_write16(uint32_t addr, uint16_t val) {
	Xil_Out16(offset + addr,val);
	return 2;
}

int axi_write32(uint32_t addr, uint32_t val) {
	Xil_Out32(offset + addr,val);
	return 4;
}

uint32_t axi_address_space_size(flink_dev* fdev) {
	 return MAX_ADDRESS_SPACE;
}

void set_axi_base_address(uint32_t add){
	offset = add;
}
