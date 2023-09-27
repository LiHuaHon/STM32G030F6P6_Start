#ifndef __MYIIC_H
#define __MYIIC_H
#include "sys.h"
   	   		   
//IO��������
#define SDA_IN()  {GPIOA->MODER&=~(3<<(4*2));GPIOA->MODER|=GPIO_MODE_IN<<(4*2);}
#define SDA_OUT() {GPIOA->MODER&=~(3<<(4*2));GPIOA->MODER|=GPIO_MODE_OUT<<(4*2);}

//IO��������	 
#define IIC_SCL(x)   	 (x?PAout(PIN5,HIGT):PAout(PIN5,LOW)) //SCL
#define IIC_SDA(x)     (x?PAout(PIN4,HIGT):PAout(PIN4,LOW)) //SDA	 
#define READ_SDA()  (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4))

//IIC���в�������
void IIC_Init(void);                //��ʼ��IIC��IO��				 
void IIC_Start(void);				//����IIC��ʼ�ź�
void IIC_Stop(void);	  			//����IICֹͣ�ź�
void IIC_Send_Byte(u8 txd);			//IIC����һ���ֽ�
u8 IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
u8 IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void IIC_Ack(void);					//IIC����ACK�ź�
void IIC_NAck(void);				//IIC������ACK�ź�

void IIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 IIC_Read_One_Byte(u8 daddr,u8 addr);	  

#endif
















