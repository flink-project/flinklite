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
 *  flink userspace library lite, subdevice function "digital I/O" *
 *                                                                 *
 *******************************************************************/
 
/** @file dio.c
 *  @brief flink userspace library, subdevice function "digital I/O".
 *
 *  Contains the high-level functions for a flink subdevice
 *  which realizes the function "digital I/O".
 *
 *  @author Martin Züger
 *  @author Raphael Lauber
 */

#include "flinklib.h"
#include "types.h"
#include "hal.h"

#include <avr/io.h>

/**
 * @brief Configures a channel as input or output
 * @param subdev: Subdevice containing the channel.
 * @param channel: Channel number.
 * @param output: Value, a value of nonzero configures the channel as output.
 * @return int: 0 on success, -1 in case of failure.
 */
int flink_dio_set_direction(flink_subdev* subdev, uint32_t channel, uint8_t output) {
	uint32_t offset;
	uint8_t bit;
	
	offset = HEADER_SIZE + SUBHEADER_SIZE + (channel / (REGISTER_WITH * 8)) * REGISTER_WITH;
	
	bit = channel % (REGISTER_WITH * 8);
	
	if(flink_write_bit(subdev, offset, bit, &output)) {
		return EXIT_ERROR;
	}
	return EXIT_SUCCESS;
}

/**
 * @brief Sets a output channel to a value
 * @param subdev: Subdevice containing the channel.
 * @param channel: Channel number.
 * @param output: A value of nonzero sets the channel.
 * @return int: 0 on success, -1 in case of failure.
 */
int flink_dio_set_value(flink_subdev* subdev, uint32_t channel, uint8_t value) {
	uint32_t offset;
	uint8_t bit;
	uint8_t val = (value != 0);
	
	offset = HEADER_SIZE + SUBHEADER_SIZE + subdev->nof_channels / (REGISTER_WITH * 8) + channel / (REGISTER_WITH * 8);
	if(subdev->nof_channels % (REGISTER_WITH * 8) != 0) offset += 4;
	bit = channel % (REGISTER_WITH * 8);
	
	if(flink_write_bit(subdev, offset, bit, &val)) {
		return EXIT_ERROR;
	}
	return EXIT_SUCCESS;
}

/**
 * @brief Reads an input channel
 * @param subdev: Subdevice containing the channel.
 * @param channel: Channel number.
 * @param value: Contains a value of nonzero if the input is set.
 * @return int: 0 on success, -1 in case of failure.
 */
int flink_dio_get_value(flink_subdev* subdev, uint32_t channel, uint8_t* value) {
	uint32_t offset;
	uint8_t bit;
	
	offset = HEADER_SIZE + SUBHEADER_SIZE + subdev->nof_channels / (REGISTER_WITH * 8) + channel / (REGISTER_WITH * 8);
	if(subdev->nof_channels % (REGISTER_WITH * 8) != 0) offset += 4;
	bit = channel % (REGISTER_WITH * 8);
	
	if(flink_read_bit(subdev, offset, bit, value)) {
		return EXIT_ERROR;
	}
	return EXIT_SUCCESS;
}
