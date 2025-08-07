/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    can.h
  * @brief   This file contains all the function prototypes for
  *          the can.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CAN_H__
#define __CAN_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */
#define PARAMETER_TUNE_ID 0x1CF
#define MICROCONTROLLER_ID 0xE1
#define PARAMETER_TUNE_REQUEST 0x01
#define PARAMETER_TUNE_ACCEPT 0x02
#define PARAMETER_TUNE_REJECT 0x03
#define PARAMETER_TUNE_DATA 0x04
#define PARAMETER_TUNE_COMPLETE 0x05

#define MIN_TORQUE_ID 0x01
#define MAX_TORQUE_ID 0x02
#define REGEN_BASELINE_TORQUE_ID 0x03
#define REGEN_MAX_TORQUE_ID 0x04
/* USER CODE END Includes */

extern CAN_HandleTypeDef hcan1;

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void MX_CAN1_Init(void);

/* USER CODE BEGIN Prototypes */
typedef struct {
	HAL_StatusTypeDef status;

	uint32_t TxMailbox;
	CAN_TxHeaderTypeDef TxHeader;
	uint8_t TxData[8];

	CAN_RxHeaderTypeDef RxHeader;
	uint8_t RxData[8];
} CAN_CONTEXT;
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __CAN_H__ */

