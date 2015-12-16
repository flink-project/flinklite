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
 *  flink userspace library, subdevice type "counter"              *
 *                                                                 *
 *******************************************************************/
 
/** @file counter.c
 *  @brief flink userspace library, subdevice function "counter".
 *
 *  Contains the high-level functions for a flink subdevice
 *  which realizes the function "counter".
 *
 *  @author Martin Züger
 */

#include "flinklib.h"
#include "types.h"
//#include "error.h"
//#include "log.h"

int flink_counter_set_mode(flink_subdev* subdev, uint8_t mode) {
	// TODO
	//dbg_print("Not yet implemented!");
	return EXIT_ERROR;
}

int flink_counter_get_count(flink_subdev* subdev, uint32_t channel, uint32_t* data) {
	uint32_t offset;
		
	//dbg_print("Reading counter value from counter %d of subdevice %d\n", channel, subdev->id);
	
	offset = HEADER_SIZE + SUBHEADER_SIZE + REGISTER_WITH * channel;
	//dbg_print("  --> calculated offset is 0x%x!\n", offset);
	
	if(flink_read(subdev, offset, REGISTER_WITH, data) != REGISTER_WITH) {
		//libc_error();
		return EXIT_ERROR;
	}
	return EXIT_SUCCESS;
}
