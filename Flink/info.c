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
 *  flink userspace library, subdevice function "info"      *
 *                                                                 *
 *******************************************************************/
 
/** @file info.c
 *  @brief flink userspace library, subdevice function "info".
 *
 *  Contains the high-level functions for a flink subdevice
 *  which realizes the function "info".
 *
 *  @author Urs Graf
 */

#include "flinklib.h"
#include "types.h"
//#include "error.h"
//#include "log.h"
#include <avr/io.h>
#include <string.h>

/**
 * @brief Reads the description field of an info subdevice
 * @param subdev: Subdevice.
 * @param desc: String containing the description.
 * @return int: 0 on success, -1 in case of failure.
 */
int flink_info_get_description(flink_subdev* subdev, char* desc) {
	uint32_t offset;
	char tmp[4];
	int i;
	
	//dbg_print("Reading description from info subdevice with id %d\n", subdev->id);
	
	offset = HEADER_SIZE + SUBHEADER_SIZE + REGISTER_WITH;
	for(i = 0; i < INFO_DESC_SIZE; i += 4, offset += 4, desc += 4) {
		if(flink_read(subdev, offset, 4, desc) != REGISTER_WITH) {
			//libc_error();
			return EXIT_ERROR;
		}
		//dbg_print("\t 0x%x\n", be16toh(*(uint32_t*)desc));
		// Bring data in correct order
		memcpy(tmp, desc, 4);
		memcpy(desc, tmp+3, 1);
		memcpy(desc+1, tmp+2, 1);
		memcpy(desc+2, tmp+1, 1);
		memcpy(desc+3, tmp, 1);			
	}
	return EXIT_SUCCESS;
}
