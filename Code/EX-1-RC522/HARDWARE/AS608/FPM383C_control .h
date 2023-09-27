#ifndef __FPM383C_CONTORL_H
#define	__FPM383C_CONTORL_H
#include ".\SYSTEM\sys\sys.h"


#define FMP383C_SLEEP  HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_12)//模块睡眠检测位

#define PWM_START HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1);//
#define PWM_STOP HAL_TIM_PWM_Stop(&htim3,TIM_CHANNEL_1);
#define CLOSE_DOOR()  {	__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,6500);HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET);}
#define OPEN_DOOR()  	{	__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,6800);HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET); }
//extern u8 warning;//系统警告数
extern u8 REpassword[6];//系统密码

u8 FPM_Connect(void);
u8 AutoControl_FR(void);
void FPM383C_Work(void);
void Password_Menu(void) ;
void OLED_Show_Message(void);
void AutoAdd_FR(void);
void Clean_FR(void);
void AutoCompare_FR(void);         
u8 Password_Check(u8 *CKP);


#endif /* __FPM383C_CONTORL_H */
