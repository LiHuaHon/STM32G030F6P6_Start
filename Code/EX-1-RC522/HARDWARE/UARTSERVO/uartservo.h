#ifndef __UARTSERVO_H
#define	__UARTSERVO_H
#include "main.h"

#define 	FSUS_UART		USART1 //串口舵机帧头

#define 	FSUS_CMD_WHEEL			0x07 // 转轮模式
#define 	FSUS_CMD_ROTATE				0X08 //角度模式
#define 	FSUS_CMD_DAMPING			0X09 // 阻尼模式
#define		FSUS_CMD_READ_ANGLE   0X0A //读取角度
#define 	FSUS_PACK_REDE_HEADER		0x051C //响应帧头
#define 	FSUS_PACK_REQUEST_HEADER		0x124c //串口舵机帧头

#define 	WHEEL_Anticlockwise		0x00 //逆时针旋转
#define 	WHEEL_Clockwise		0x80 //顺时针旋转
#define 	WHEEL_MOD_Stop		0x00 //停止旋转
#define 	WHEEL_MOD_Run		0x01 //持续旋转
#define 	WHEEL_MOD_CircleValue		0x02 //持续旋转value圈
#define 	WHEEL_MOD_MSValue		0x03 //持续旋转valueMS

void FSUS_READ_ANGLE(uint8_t servoId);
void FSUS_Stop(uint8_t servoId);
void UARTServo_FrameHead(void);
void UARTServo_SendData(uint8_t data);
void FSUS_SetServoAngle(uint8_t servoId, float angle, uint16_t interval, uint16_t power);

void UARTServo_DEBUGE(uint8_t CMD,uint8_t DATA1,uint8_t DATA2 ,uint8_t DATA3);
void FSUS_WHEEL(uint8_t servoId,uint8_t method,uint16_t speed,uint16_t value);
void FSUS_DAMPING(uint8_t servoId, uint16_t power);

uint8_t UARTServo_READ_Angle(void);
	
#endif 
