/*
 * flink_axi.h
 *
 *  Created on: 26.05.2016
 *      Author: tinner
 */

#ifndef SRC_FLINK_AXI_H_
#define SRC_FLINK_AXI_H_

uint8_t axi_read8(uint32_t addr);

uint16_t axi_read16(uint32_t addr);

uint32_t axi_read32(uint32_t addr);

int axi_write8(uint32_t addr, uint8_t val);

int axi_write16(uint32_t addr, uint16_t val);

int axi_write32(uint32_t addr, uint32_t val);

uint32_t axi_address_space_size(flink_dev* fdev);

uint32_t axi_address_base_address(flink_dev* fdev);


struct flink_bus_ops axi_bus_ops = {
	.read8              = axi_read8,
	.read16             = axi_read16,
	.read32             = axi_read32,
	.write8             = axi_write8,
	.write16            = axi_write16,
	.write32            = axi_write32,
	.address_space_size = axi_address_space_size,
	.address_base_address = axi_address_base_address,
};


#endif /* SRC_FLINK_AXI_H_ */
