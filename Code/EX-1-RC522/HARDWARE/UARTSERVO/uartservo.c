#include ".\HARDWARE\UARTSERVO\uartservo.h"
//read_Servo_Angleһ��������һ������ĽǶ� ��read_Servo_Angle[0] ����0�Ŷ���Ƕ�
float read_Servo_Angle[10]={0};
/**
  * @brief  ���ʹ��ڶ��֡ͷ
  * @param  ��
  */

void UART_SendData(uint8_t sendData)
{      
  WRITE_REG(huart2.Instance->TDR,sendData);      
	while(__HAL_UART_GET_FLAG(&huart2,UART_FLAG_TXE)==RESET);//ѭ������,ֱ���������    
}
void UARTServo_FrameHead(void)
{
    UART_SendData((FSUS_PACK_REQUEST_HEADER>>8)&0xff);
    UART_SendData((FSUS_PACK_REQUEST_HEADER>>0)&0xff);
}
/**
  * @brief  ��ȡ����Ƕ� 
	*	@tips   ��Ҫ������ư�ʹ��
  * @param  servoId������ 
  */
void FSUS_READ_ANGLE(uint8_t servoId)
{
		int16_t temp=0;//�Ƕ�ת��
    UARTServo_FrameHead();//֡ͷ
    UART_SendData(FSUS_CMD_READ_ANGLE&0xff);//����ָ��Ƕ���ת
    UART_SendData(0x01);//�����1
		
    UART_SendData((servoId>>0)&0xff);//���ID
		
		temp=((FSUS_PACK_REQUEST_HEADER>>8)+(FSUS_PACK_REQUEST_HEADER>>0)+
    FSUS_CMD_READ_ANGLE+0x01+servoId);//����У���
    UART_SendData(temp&0xff);//����У���
		
}

/**
  * @brief  ���ô��ڶ���Ƕ�
  * @param  servoId������ angle�Ƕ�(����0.1) intervalִ��ʱ�� power����
  */
void FSUS_SetServoAngle(uint8_t servoId, float angle, uint16_t interval, uint16_t power)
{
		int16_t temp=angle*10;//�Ƕ�ת��
    UARTServo_FrameHead();//֡ͷ
    UART_SendData(FSUS_CMD_ROTATE&0xff);//����ָ��Ƕ���ת
    UART_SendData(0x07);//�����7
		
    UART_SendData((servoId>>0)&0xff);//���ID
		
    UART_SendData((temp>>0)&0xff);//�ȷ���λ
    UART_SendData((temp>>8)&0xff);//�ٷ���λ
		
    UART_SendData((interval>>0)&0xff);//�ȷ���λ
    UART_SendData((interval>>8)&0xff);//�ٷ���λ
		
    UART_SendData((power>>0)&0xff);//�ȷ���λ
    UART_SendData((power>>8)&0xff);//�ٷ���λ
		
		temp=((FSUS_PACK_REQUEST_HEADER>>8)+(FSUS_PACK_REQUEST_HEADER>>0)+
    FSUS_CMD_ROTATE+0x07+servoId
		+(temp>>8)+(temp>>0)+(interval>>0)+(interval>>8)+(power>>0)+(power>>8)
	  );//����У���
    UART_SendData(temp&0xff);//����У���
		
}

/**
  * @brief  ���ô��ڶ������ģʽ
  * @param  servoId������  power����
	* @tips ������ֹ��� power ����Ϊ0�����ߴ��ڹ������ޣ����չ������޴���	
  */
void FSUS_DAMPING(uint8_t servoId, uint16_t power)
{
		int16_t temp=0;
	
    UARTServo_FrameHead();//֡ͷ
    UART_SendData(FSUS_CMD_DAMPING&0xff);//����ָ������ģʽ
    UART_SendData(0x03);//�����3
		
    UART_SendData((servoId>>0)&0xff);//���ID
		
    UART_SendData((power>>0)&0xff);//�ȷ���λ
    UART_SendData((power>>8)&0xff);//�ٷ���λ
		
		temp=((FSUS_PACK_REQUEST_HEADER>>8)+(FSUS_PACK_REQUEST_HEADER>>0)+
    FSUS_CMD_DAMPING+0x03+servoId+(power>>0)+(power>>8));//����У���
	
    UART_SendData(temp&0xff);//����У���
		
}
/**
  * @brief  ���ֹͣģʽ����
  * @param  servoId������ 
  */
void FSUS_Stop(uint8_t servoId)
{
		uint16_t temp=0;
    UARTServo_FrameHead();//֡ͷ
    UART_SendData(FSUS_CMD_WHEEL&0xff);//����ָ��
    UART_SendData(0x06);//�����6
		
    UART_SendData((servoId>>0)&0xff);//���ID
		
    UART_SendData(00&0xff);
    UART_SendData(00&0xff);
    UART_SendData(00&0xff);
		
    UART_SendData(00&0xff);
    UART_SendData(00&0xff);
		
		temp=((FSUS_PACK_REQUEST_HEADER>>8)+(FSUS_PACK_REQUEST_HEADER>>0)+
    FSUS_CMD_WHEEL+0x06+servoId
	  );//����У���
    UART_SendData(temp&0xff);//����У���
		
}

/**
  * @brief  �����ʽģʽ����
  * @param  servo_id 	���ID  method 	ִ�з�ʽ&��ת���� speed ������ٶ�(��λ:��/s)  value ��ֵ
  */
void FSUS_WHEEL(uint8_t servoId,uint8_t method,uint16_t speed,uint16_t value)
{
		uint16_t temp=0;
    UARTServo_FrameHead();//֡ͷ
    UART_SendData(FSUS_CMD_WHEEL&0xff);//����ָ��
    UART_SendData(0x06);//�����6
		
    UART_SendData((servoId>>0)&0xff);//���ID
	
    UART_SendData((method>>0)&0xff);
	
    UART_SendData((speed>>0)&0xff);//�ȷ���λ
    UART_SendData((speed>>8)&0xff);//�ٷ���λ
		
    UART_SendData((value>>0)&0xff);//�ȷ���λ
    UART_SendData((value>>8)&0xff);//�ٷ���λ
		
		
		temp=((FSUS_PACK_REQUEST_HEADER>>8)+(FSUS_PACK_REQUEST_HEADER>>0)+
    FSUS_CMD_WHEEL+0x06+servoId+method
		+(speed>>8)+(speed>>0)+(value>>0)+(value>>8)
	  );//����У���
    UART_SendData(temp&0xff);//����У���
		
}

///**
//  * @brief  ���������ǰ�Ƕ�
//  * @param  NULL �޲������� 00���� 01���� FF����İ�
//  * @tip ���鶨ʱ����  
//  */

//int Angle_10;//ʮ���Ŵ�Ƕ�
//float tempAngle=0;
//u8 temp=0;
//uint8_t UARTServo_READ_Angle(void){
//	
//		QUEUE_DATA_TYPE *rx_data;	
//		rx_data = cbRead(&rx_queue);  /*�ӻ�������ȡ���ݣ����д���*/ 
//		temp=USART2_READ_HEADER();
//		if(temp==NULL)
//			return NULL;
//		else if(temp!=FSUS_DATA)//������Ǳ����ݰ��򷵻���Ӧ����
//			return temp;
//		
//		Angle_10=(*(rx_data->head+5)|*(rx_data->head+6)<<8);
//		tempAngle=(float)Angle_10;
//		
//		if(tempAngle>=1800.0){//��������Ƕ� ���Ǹ�����
//			tempAngle=0XFFFF-tempAngle;//�Ƕȱ仯
//			tempAngle=tempAngle*(-1.0);
//		}
//		read_Servo_Angle[*(rx_data->head+4)]=tempAngle/10.0;//�Ƕ����뵽��Ӧ�Ķ����
//		cbReadFinish(&rx_queue);//��ʹ�����
//		return 0;
//}
