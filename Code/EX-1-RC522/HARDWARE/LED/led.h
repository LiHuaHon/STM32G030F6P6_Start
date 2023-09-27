#ifndef __LED_H
#define __LED_H
#include "sys.h"
#include "ALLHeader.h"

#define LED_OP_ON		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET);
#define LED_ER_ON		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);//这两个灯基本没什么用
#define LED_SY_ON		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15, GPIO_PIN_SET);//这两个灯基本没什么用

#define LED_OP_OFF		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET);
#define LED_ER_OFF		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
#define LED_SY_OFF		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15, GPIO_PIN_RESET);

void LED_Init(void);//初始化


#endif
