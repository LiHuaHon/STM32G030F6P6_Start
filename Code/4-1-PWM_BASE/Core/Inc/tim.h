/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    tim.h
  * @brief   This file contains all the function prototypes for
  *          the tim.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#ifndef __TIM_H__
#define __TIM_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern TIM_HandleTypeDef htim16;

/* USER CODE BEGIN Private defines */

//定时器14
#define TIM16_PERIOD_MS    (500)//500ms定时器
#define TIM16_PERIOD_COUNT    (TIM16_PERIOD_MS*100)

//定时器时钟源TIMxCLK = 2 * APB1_CLK (2*144)
//				如果APB1_CLK = 288MHz = TIMxCLK
//				否则TIMxCLK=APB1_CLK * 2
// 设定定时器频率为=TIMxCLK/(72)=1MHz
// 频率1(TIMxCLK=72MHZ)=TIMxCLK/(720)=100KHz
// 频率2(crm_clocks_freq_struct.apb2_freq * 2 =288MHZ)=TIMxCLK/(2880)=100KHz
#define BASIC_PRESCALER_COUNT   (640)//64Mhz

/* USER CODE END Private defines */

void MX_TIM16_Init(void);

/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __TIM_H__ */

