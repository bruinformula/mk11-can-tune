/*
 * tuning.c
 *
 *  Created on: Aug 6, 2025
 *      Author: ishanchitale
 */

#include "tuning.h"
#include "stm32l4xx_hal.h"
#include "string.h"

float bytes_to_float(uint8_t b0, uint8_t b1, uint8_t b2, uint8_t b3) {
	float f;
	char b[4] = {b3, b2, b1, b0};
	memcpy(&f, &b, sizeof(f));
	return f;
}

int parametersTuned = 0;
void sendParameterTune_dummy(CAN_CONTEXT* c) {
	  c->TxHeader.IDE = CAN_ID_STD;
	  c->TxHeader.StdId = PARAMETER_TUNE_ID;
	  c->TxHeader.RTR = CAN_RTR_DATA;
	  c->TxHeader.DLC = 7;

	  c->TxData[0] = MICROCONTROLLER_ID;
	  c->TxData[1] = PARAMETER_TUNE_DATA;

	  // Some Random Values
	  c->TxData[3] = 0x42;
	  c->TxData[4] = 0x87;
	  c->TxData[5] = 0xCC;
	  c->TxData[6] = 0xCD;

	  c->TxData[2] = MIN_TORQUE_ID;
	  HAL_CAN_AddTxMessage(&hcan1, &(c->TxHeader), c->TxData, &(c->TxMailbox));
	  HAL_Delay(1000);

	  c->TxData[2] = MAX_TORQUE_ID;
	  HAL_CAN_AddTxMessage(&hcan1, &(c->TxHeader), c->TxData, &(c->TxMailbox));
	  HAL_Delay(1000);

	  c->TxData[2] = REGEN_BASELINE_TORQUE_ID;
	  HAL_CAN_AddTxMessage(&hcan1, &(c->TxHeader), c->TxData, &(c->TxMailbox));
	  HAL_Delay(1000);

	  c->TxData[2] = REGEN_MAX_TORQUE_ID;
	  HAL_CAN_AddTxMessage(&hcan1, &(c->TxHeader), c->TxData, &(c->TxMailbox));
	  HAL_Delay(1000);
}

void parameterTuneRxHandler(CAN_CONTEXT* c, TUNABLE_PARAMETERS* params) {
	// TODO
	switch (c->RxData[1]) {
	case PARAMETER_TUNE_REQUEST:
		// TODO
		break;
	case PARAMETER_TUNE_DATA:
		parameterSetData(c, params);
		parametersTuned++;
		break;
	}
}

void parameterSetData(CAN_CONTEXT* c, TUNABLE_PARAMETERS* params) {
	// TODO: Abstract this slightly so the code isn't so repetitive
	switch (c->RxData[2]) {
	case MIN_TORQUE_ID:
		params->MIN_TORQUE = bytes_to_float(c->RxData[3], c->RxData[4], c->RxData[5], c->RxData[6]);
		break;
	case MAX_TORQUE_ID:
		params->MAX_TORQUE = bytes_to_float(c->RxData[3], c->RxData[4], c->RxData[5], c->RxData[6]);
		break;
	case REGEN_BASELINE_TORQUE_ID:
		params->REGEN_BASELINE_TORQUE = bytes_to_float(c->RxData[3], c->RxData[4], c->RxData[5], c->RxData[6]);
		break;
	case REGEN_MAX_TORQUE_ID:
		params->REGEN_MAX_TORQUE = bytes_to_float(c->RxData[3], c->RxData[4], c->RxData[5], c->RxData[6]);
		break;
	}
}

void saveParametersToFlash(TUNABLE_PARAMETERS* data) {
	HAL_FLASH_Unlock();

	__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP | FLASH_FLAG_OPERR |
								FLASH_FLAG_PGSERR | FLASH_FLAG_WRPERR |
								FLASH_FLAG_PROGERR);

	FLASH_EraseInitTypeDef eraseConfig = {
			.TypeErase = FLASH_TYPEERASE_PAGES,
			.Page = FLASH_PARAMETER_PAGE,
			.NbPages = 1
	};
	uint32_t PageError;
	HAL_FLASHEx_Erase(&eraseConfig, &PageError);

	uint64_t* src = (uint64_t*)data;
	for (uint32_t i = 0; i < sizeof(TUNABLE_PARAMETERS) / 8; i++) {
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, FLASH_PARAMETER_ADDR + i * 8, src[i]);
	}

	HAL_FLASH_Lock();
}

void loadParametersFromFlash(TUNABLE_PARAMETERS* data) {
    memcpy(data, (void *)FLASH_PARAMETER_ADDR, sizeof(TUNABLE_PARAMETERS));
}

void clearParameterFlash() {
	HAL_FLASH_Unlock();

	__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP | FLASH_FLAG_OPERR |
								FLASH_FLAG_PGSERR | FLASH_FLAG_WRPERR |
		                    	FLASH_FLAG_PROGERR);

	FLASH_EraseInitTypeDef eraseConfig = {
			.TypeErase = FLASH_TYPEERASE_PAGES,
			.Page = FLASH_PARAMETER_PAGE,
			.NbPages = 1
	};
	uint32_t PageError;
	HAL_FLASHEx_Erase(&eraseConfig, &PageError);

	HAL_FLASH_Lock();
}
