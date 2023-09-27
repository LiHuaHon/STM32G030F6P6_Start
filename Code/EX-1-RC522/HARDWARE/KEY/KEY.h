#ifndef __KEY_H
#define __KEY_H
#include "sys.h"

#define KEY0_UP  HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0)//��ȡ����0
#define KEY1_CE  HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2)//��ȡ����1
#define KEY2_DN  HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_7)//��ȡ����2
#define KEY4_CL  HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8)//��ȡ����2
#define KEY3_OP  HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3)//��ȡ����3
 
#define FPM383C_WK  HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_12)//��ȡ����3

#define KEY0_PRES_UP	 1		//KEY0  
#define KEY1_PRES_CE 2		//KEY1 
#define KEY2_PRES_DN	 3		//KEY2 
#define KEY3_PRES_OP	 4		//KEY3 
#define KEY4_PRES_CL	 5		//KEY3 

u8 KEY_Scan(u8 mode);  	//����ɨ�躯��					  

u8 KEY_Mode(void);  
#endif

















