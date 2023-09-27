#ifndef __SYS_H
#define __SYS_H	
#include "main.h"
#include "stm32g0xx.h"
#define SYSTEM_SUPPORT_OS		0		//����ϵͳ�ļ����Ƿ�֧��UCOS
																	    
typedef uint32_t  u32;
typedef uint16_t u16;
typedef uint8_t  u8;
 
typedef volatile uint32_t  vu32;
typedef volatile uint16_t vu16;
typedef volatile uint8_t  vu8; 


#define GPIO_A 				0
#define GPIO_B 				1
#define GPIO_C				2

#define PIN0				1<<0
#define PIN1				1<<1
#define PIN2				1<<2
#define PIN3				1<<3
#define PIN4				1<<4
#define PIN5				1<<5
#define PIN6				1<<6
#define PIN7				1<<7
#define PIN8				1<<8
#define PIN9				1<<9
#define PIN10				1<<10
#define PIN11				1<<11
#define PIN12				1<<12
#define PIN13				1<<13
#define PIN14				1<<14
#define PIN15				1<<15 

#define GPIO_MODE_IN    	0		//��ͨ����ģʽ
#define GPIO_MODE_OUT		1		//��ͨ���ģʽ
#define GPIO_MODE_AF		2		//AF����ģʽ
#define GPIO_MODE_AIN		3		//ģ������ģʽ

#define GPIO_SPEED_LOW		0		//GPIO�ٶ�(����,3M)
#define GPIO_SPEED_MID		1		//GPIO�ٶ�(����,15M)
#define GPIO_SPEED_FAST		2		//GPIO�ٶ�(����,60M)
#define GPIO_SPEED_HIGH		3		//GPIO�ٶ�(����,80M)  

#define GPIO_PUPD_NONE		0		//����������
#define GPIO_PUPD_PU		1		//����
#define GPIO_PUPD_PD		2		//����
#define GPIO_PUPD_RES		3		//���� 

#define GPIO_OTYPE_PP		0		//�������
#define GPIO_OTYPE_OD		1		//��©��� 

#define FTIR 1	//�½��ش���
#define RTIR 2	//�����ش���

#define HIGT 1	
#define LOW 0	

//IO�ڲ���,ֻ�Ե�һ��IO��!
//ȷ��n��ֵС��16!
#define PAout(pin,status)   (status?((GPIOA->BSRR)|=pin):((GPIOA->BSRR)|=(pin<<16)))  //�ߵ�λ
#define PAin(pin)    ( (GPIOA->IDR|=pin)?1:0 )  //���� 


char My_getchar(void);
void My_getstring(char* returnData);
void get_data_str(char* dataAddress, uint16_t dataStartBit, uint16_t dataEndBit, char* returnData);

#endif
