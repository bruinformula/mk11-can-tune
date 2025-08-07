/*
 * constants.h
 *
 *  Created on: Aug 6, 2025
 *      Author: ishanchitale
 */

#ifndef INC_TUNING_H_
#define INC_TUNING_H_

#include "can.h"

#define FLASH_PARAMETER_ADDR ((uint32_t)0x0803F800)
#define FLASH_PARAMETER_PAGE ((FLASH_PARAMETER_ADDR - FLASH_BASE) / FLASH_PAGE_SIZE)

typedef struct {
	float MIN_TORQUE;
	float MAX_TORQUE;
	float REGEN_BASELINE_TORQUE;
	float REGEN_MAX_TORQUE;
} TUNABLE_PARAMETERS;

void sendParameterTuneRequest_dummy(CAN_CONTEXT* c);

void saveParametersToFlash(TUNABLE_PARAMETERS* data);
void loadParameterFromFlash(TUNABLE_PARAMETERS* data);
void clearParametersFromFlash();


#endif /* INC_TUNING_H_ */
