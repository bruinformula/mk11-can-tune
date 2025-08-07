/*
 * tuning.c
 *
 *  Created on: Aug 6, 2025
 *      Author: ishanchitale
 */

#include "tuning.h"
#include "string.h"
#include "stm32l4xx_hal.h"

void sendParameterTuneRequest_dummy(CAN_CONTEXT* c) {
	  c->TxHeader.IDE = CAN_ID_STD;
	  c->TxHeader.StdId = PARAMETER_TUNE_ID;
	  c->TxHeader.RTR = CAN_RTR_DATA;
	  c->TxHeader.DLC = 2;

	  c->TxData[0] = MICROCONTROLLER_ID;
	  c->TxData[1] = PARAMETER_TUNE_REQUEST;

	  HAL_CAN_AddTxMessage(&hcan1, &(c->TxHeader), c->TxData, &(c->TxMailbox));
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
