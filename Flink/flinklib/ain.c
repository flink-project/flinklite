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
 *  flink userspace library lite, subdevice function "analog input"*
 *                                                                 *
 *******************************************************************/
 
/** @file ain.c
 *  @brief flink userspace library, subdevice function "analog input".
 *
 *  Contains the high-level functions for a flink subdevice
 *  which realizes the function "analog input".
 *
 *  @author Martin Züger
 *  @author Raphael Lauber
 */

#include "flinklib.h"
#include "types.h"

#include <avr/io.h>

/**
 * @brief Reads the resolution of a analog input subdevice
 * @param subdev: Subdevice.
 * @param resolution: Contains the resolution in number of resolvable steps.
 * @return int: 0 on success, -1 in case of failure.
 */
int flink_analog_in_get_resolution(flink_subdev* subdev, uint32_t* resolution){
	uint32_t offset;
	offset = HEADER_SIZE + SUBHEADER_SIZE;
	
	if(flink_read(subdev, offset, REGISTER_WITH, resolution) != REGISTER_WITH) {
		return EXIT_ERROR;
	}
	return EXIT_SUCCESS;
}

/**
 * @brief Reads an analog input channel
 * @param subdev: Subdevice containing the channel.
 * @param channel: Channel number.
 * @param value: Contains the digitized value of the channel input.
 * @return int: 0 on success, -1 in case of failure.
 */
int flink_analog_in_get_value(flink_subdev* subdev, uint32_t channel, uint32_t* value){
	uint32_t offset;
	
	offset = HEADER_SIZE + SUBHEADER_SIZE + ANALOG_INPUT_FIRST_VALUE_OFFSET + channel*REGISTER_WITH;
	
	if(flink_read(subdev, offset, REGISTER_WITH, value) != REGISTER_WITH) {
		//libc_error();
		return EXIT_ERROR;
	}
	return EXIT_SUCCESS;
}
