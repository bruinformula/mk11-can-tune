/*
 * constants.h
 *
 *  Created on: Aug 6, 2025
 *      Author: ishanchitale
 */

#ifndef INC_CONSTANTS_H_
#define INC_CONSTANTS_H_

#define MICROCONTROLLER_ID 0xEC
#define PARAMETER_TUNE_REQUEST 0x01
#define PARAMETER_TUNE_ACCEPT 0x02
#define PARAMETER_TUNE_REJECT 0x03

typedef struct TUNABLE_CONSTANTS {
	float MIN_TORQUE;
	float MAX_TORQUE;
	float REGEN_BASELINE_TORQUE;
	float REGEN_MAX_TORQUE;
};

#endif /* INC_CONSTANTS_H_ */
