#ifndef __KEY_H
#define __KEY_H
#include "sys.h"

#define KEY0_UP  HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0)//读取按键0
#define KEY1_CE  HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2)//读取按键1
#define KEY2_DN  HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_7)//读取按键2
#define KEY4_CL  HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8)//读取按键2
#define KEY3_OP  HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3)//读取按键3
 
#define FPM383C_WK  HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_12)//读取按键3

#define KEY0_PRES_UP	 1		//KEY0  
#define KEY1_PRES_CE 2		//KEY1 
#define KEY2_PRES_DN	 3		//KEY2 
#define KEY3_PRES_OP	 4		//KEY3 
#define KEY4_PRES_CL	 5		//KEY3 

u8 KEY_Scan(u8 mode);  	//按键扫描函数					  

u8 KEY_Mode(void);  
#endif

















