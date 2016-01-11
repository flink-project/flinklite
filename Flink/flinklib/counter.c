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
 *  flink userspace library lite, subdevice type "counter"         *
 *                                                                 *
 *******************************************************************/
 
/** @file counter.c
 *  @brief flink userspace library, subdevice function "counter".
 *
 *  Contains the high-level functions for a flink subdevice
 *  which realizes the function "counter".
 *
 *  @author Martin Züger
 *  @author Raphael Lauber
 */

#include "flinklib.h"
#include "types.h"


int flink_counter_set_mode(flink_subdev* subdev, uint8_t mode) {
	// TODO Not implemented in flinklib
	return EXIT_ERROR;
}

int flink_counter_get_count(flink_subdev* subdev, uint32_t channel, uint32_t* data) {
	uint32_t offset;
		
	offset = HEADER_SIZE + SUBHEADER_SIZE + REGISTER_WITH * channel;
	
	if(flink_read(subdev, offset, REGISTER_WITH, data) != REGISTER_WITH) {
		return EXIT_ERROR;
	}
	return EXIT_SUCCESS;
}
