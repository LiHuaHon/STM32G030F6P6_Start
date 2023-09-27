#include ".\HARDWARE\UARTSERVO\uartservo.h"
//read_Servo_Angle一个数代表一个舵机的角度 如read_Servo_Angle[0] 代表0号舵机角度
float read_Servo_Angle[10]={0};
/**
  * @brief  发送串口舵机帧头
  * @param  无
  */

void UART_SendData(uint8_t sendData)
{      
  WRITE_REG(huart2.Instance->TDR,sendData);      
	while(__HAL_UART_GET_FLAG(&huart2,UART_FLAG_TXE)==RESET);//循环发送,直到发送完毕    
}
void UARTServo_FrameHead(void)
{
    UART_SendData((FSUS_PACK_REQUEST_HEADER>>8)&0xff);
    UART_SendData((FSUS_PACK_REQUEST_HEADER>>0)&0xff);
}
/**
  * @brief  读取舵机角度 
	*	@tips   需要搭配控制板使用
  * @param  servoId舵机编号 
  */
void FSUS_READ_ANGLE(uint8_t servoId)
{
		int16_t temp=0;//角度转换
    UARTServo_FrameHead();//帧头
    UART_SendData(FSUS_CMD_READ_ANGLE&0xff);//发送指令角度旋转
    UART_SendData(0x01);//命令长度1
		
    UART_SendData((servoId>>0)&0xff);//舵机ID
		
		temp=((FSUS_PACK_REQUEST_HEADER>>8)+(FSUS_PACK_REQUEST_HEADER>>0)+
    FSUS_CMD_READ_ANGLE+0x01+servoId);//计算校验和
    UART_SendData(temp&0xff);//发送校验和
		
}

/**
  * @brief  设置串口舵机角度
  * @param  servoId舵机编号 angle角度(精度0.1) interval执行时间 power功率
  */
void FSUS_SetServoAngle(uint8_t servoId, float angle, uint16_t interval, uint16_t power)
{
		int16_t temp=angle*10;//角度转换
    UARTServo_FrameHead();//帧头
    UART_SendData(FSUS_CMD_ROTATE&0xff);//发送指令角度旋转
    UART_SendData(0x07);//命令长度7
		
    UART_SendData((servoId>>0)&0xff);//舵机ID
		
    UART_SendData((temp>>0)&0xff);//先发低位
    UART_SendData((temp>>8)&0xff);//再发高位
		
    UART_SendData((interval>>0)&0xff);//先发低位
    UART_SendData((interval>>8)&0xff);//再发高位
		
    UART_SendData((power>>0)&0xff);//先发低位
    UART_SendData((power>>8)&0xff);//再发高位
		
		temp=((FSUS_PACK_REQUEST_HEADER>>8)+(FSUS_PACK_REQUEST_HEADER>>0)+
    FSUS_CMD_ROTATE+0x07+servoId
		+(temp>>8)+(temp>>0)+(interval>>0)+(interval>>8)+(power>>0)+(power>>8)
	  );//计算校验和
    UART_SendData(temp&0xff);//发送校验和
		
}

/**
  * @brief  设置串口舵机阻尼模式
  * @param  servoId舵机编号  power功率
	* @tips 如果保持功率 power 设置为0，或者大于功率上限，则按照功率上限处理。	
  */
void FSUS_DAMPING(uint8_t servoId, uint16_t power)
{
		int16_t temp=0;
	
    UARTServo_FrameHead();//帧头
    UART_SendData(FSUS_CMD_DAMPING&0xff);//发送指令阻尼模式
    UART_SendData(0x03);//命令长度3
		
    UART_SendData((servoId>>0)&0xff);//舵机ID
		
    UART_SendData((power>>0)&0xff);//先发低位
    UART_SendData((power>>8)&0xff);//再发高位
		
		temp=((FSUS_PACK_REQUEST_HEADER>>8)+(FSUS_PACK_REQUEST_HEADER>>0)+
    FSUS_CMD_DAMPING+0x03+servoId+(power>>0)+(power>>8));//计算校验和
	
    UART_SendData(temp&0xff);//发送校验和
		
}
/**
  * @brief  舵机停止模式命令
  * @param  servoId舵机编号 
  */
void FSUS_Stop(uint8_t servoId)
{
		uint16_t temp=0;
    UARTServo_FrameHead();//帧头
    UART_SendData(FSUS_CMD_WHEEL&0xff);//发送指令
    UART_SendData(0x06);//命令长度6
		
    UART_SendData((servoId>>0)&0xff);//舵机ID
		
    UART_SendData(00&0xff);
    UART_SendData(00&0xff);
    UART_SendData(00&0xff);
		
    UART_SendData(00&0xff);
    UART_SendData(00&0xff);
		
		temp=((FSUS_PACK_REQUEST_HEADER>>8)+(FSUS_PACK_REQUEST_HEADER>>0)+
    FSUS_CMD_WHEEL+0x06+servoId
	  );//计算校验和
    UART_SendData(temp&0xff);//发送校验和
		
}

/**
  * @brief  舵机轮式模式控制
  * @param  servo_id 	舵机ID  method 	执行方式&旋转方向 speed 舵机角速度(单位:°/s)  value 数值
  */
void FSUS_WHEEL(uint8_t servoId,uint8_t method,uint16_t speed,uint16_t value)
{
		uint16_t temp=0;
    UARTServo_FrameHead();//帧头
    UART_SendData(FSUS_CMD_WHEEL&0xff);//发送指令
    UART_SendData(0x06);//命令长度6
		
    UART_SendData((servoId>>0)&0xff);//舵机ID
	
    UART_SendData((method>>0)&0xff);
	
    UART_SendData((speed>>0)&0xff);//先发低位
    UART_SendData((speed>>8)&0xff);//再发高位
		
    UART_SendData((value>>0)&0xff);//先发低位
    UART_SendData((value>>8)&0xff);//再发高位
		
		
		temp=((FSUS_PACK_REQUEST_HEADER>>8)+(FSUS_PACK_REQUEST_HEADER>>0)+
    FSUS_CMD_WHEEL+0x06+servoId+method
		+(speed>>8)+(speed>>0)+(value>>0)+(value>>8)
	  );//计算校验和
    UART_SendData(temp&0xff);//发送校验和
		
}

///**
//  * @brief  解析舵机当前角度
//  * @param  NULL 无参数解析 00正常 01错误 FF错误的包
//  * @tip 建议定时调用  
//  */

//int Angle_10;//十倍放大角度
//float tempAngle=0;
//u8 temp=0;
//uint8_t UARTServo_READ_Angle(void){
//	
//		QUEUE_DATA_TYPE *rx_data;	
//		rx_data = cbRead(&rx_queue);  /*从缓冲区读取数据，进行处理*/ 
//		temp=USART2_READ_HEADER();
//		if(temp==NULL)
//			return NULL;
//		else if(temp!=FSUS_DATA)//如果不是本数据包则返回相应的码
//			return temp;
//		
//		Angle_10=(*(rx_data->head+5)|*(rx_data->head+6)<<8);
//		tempAngle=(float)Angle_10;
//		
//		if(tempAngle>=1800.0){//超过这个角度 就是负数了
//			tempAngle=0XFFFF-tempAngle;//角度变化
//			tempAngle=tempAngle*(-1.0);
//		}
//		read_Servo_Angle[*(rx_data->head+4)]=tempAngle/10.0;//角度输入到对应的舵机中
//		cbReadFinish(&rx_queue);//包使用完毕
//		return 0;
//}
