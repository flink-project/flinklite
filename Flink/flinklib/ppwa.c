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
 *  flink userspace library lite, subdevice function "ppwa"        *
 *                                                                 *
 *******************************************************************/
 
/** @file ppwa.c
 *  @brief flink userspace library, subdevice function "ppwa".
 *
 *  Contains the high-level functions for a flink subdevice
 *  which realizes the function "ppwa".
 *
 *  @author Urs Graf
  * @author Raphael Lauber
 */

#include "flinklib.h"
#include "types.h"

/**
 * @brief Reads the base clock of a PPWA subdevice
 * @param subdev: Subdevice.
 * @param frequency: Contains the base clock in Hz.
 * @return int: 0 on success, -1 in case of failure.
 */
int flink_ppwa_get_baseclock(flink_subdev* subdev, uint32_t* frequency) {
	
	uint32_t offset;
	
	offset = HEADER_SIZE + SUBHEADER_SIZE;
	
	if(flink_read(subdev, offset, REGISTER_WITH, frequency) != REGISTER_WITH) {
		return EXIT_ERROR;
	}
	return EXIT_SUCCESS;
}

/**
 * @brief Reads the PPWA period
 * @param subdev: Subdevice.
 * @param channel: Channel number.
 * @param period: Contains the period of the PPWA signal in multiples of the base clock.
 * @return int: 0 on success, -1 in case of failure.
 */
int flink_ppwa_get_period(flink_subdev* subdev, uint32_t channel, uint32_t* period) {
	
	uint32_t offset;
	
	offset = HEADER_SIZE + SUBHEADER_SIZE + PPWA_FIRSTPPWA_OFFSET + REGISTER_WITH * channel;
	
	if(flink_read(subdev, offset, REGISTER_WITH, period) != REGISTER_WITH) {
		return EXIT_ERROR;
	}
	return EXIT_SUCCESS;
}

/**
 * @brief Reads the PPWA hightime
 * @param subdev: Subdevice.
 * @param channel: Channel number.
 * @param hightime: Contains the hightime of the PPWA signal in multiples of the base clock.
 * @return int: 0 on success, -1 in case of failure.
 */
int flink_ppwa_get_hightime(flink_subdev* subdev, uint32_t channel, uint32_t* hightime) {
	
	uint32_t offset;
		
	offset = HEADER_SIZE + SUBHEADER_SIZE + PPWA_FIRSTPPWA_OFFSET + subdev->nof_channels * REGISTER_WITH + REGISTER_WITH * channel;
	
	if(flink_read(subdev, offset, REGISTER_WITH, hightime) != REGISTER_WITH) {
		return EXIT_ERROR;
	}
	return EXIT_SUCCESS;
}
