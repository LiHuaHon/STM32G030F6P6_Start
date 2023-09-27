/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"	
#include <string.h>
#include <stdlib.h>
#include "i2c.h"
#include "spi.h"
#include "usart.h"
#include "gpio.h"
#include ".\SYSTEM\sys\sys.h"
#include ".\HARDWARE\24CXX\24cxx.h" 
#include ".\HARDWARE\R522\R522.h"
#include ".\HARDWARE\USERSAVE\USERSAVE.h"
#include ".\HARDWARE\SHOW\SHOW.h"
#include ".\HARDWARE\CONTROL\CONTROL.h"
#include ".\HARDWARE\UARTSERVO\uartservo.h"
#include ".\HARDWARE\WS2812B\ws2812b.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define R522_NSS_Pin GPIO_PIN_4
#define R522_NSS_GPIO_Port GPIOA
#define R522_RES_Pin GPIO_PIN_5
#define R522_RES_GPIO_Port GPIOA

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
