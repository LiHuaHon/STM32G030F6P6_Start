#ifndef __24CXX_H
#define __24CXX_H
#include "main.h"   

//Mini STM32������
//24CXX��������(�ʺ�24C01~24C16,24C32~256δ��������!�д���֤!)
//����ԭ��@ALIENTEK
//2010/6/10
//V1.2

#define AT24C01		127
#define AT24C02		255
#define AT24C04		511
#define AT24C08		1023
#define AT24C16		2047
#define AT24C32		4095
#define AT24C64	    8191
#define AT24C128	16383
#define AT24C256	32767  
//Mini STM32������ʹ�õ���24c02�����Զ���EE_TYPEΪAT24C02
#define EE_TYPE AT24C256
					  
uint8_t AT24CXX_ReadOneByte(uint16_t ReadAddr);							//ָ����ַ��ȡһ���ֽ�
void AT24CXX_WriteOneByte(uint16_t WriteAddr,uint8_t DataToWrite);		//ָ����ַд��һ���ֽ�
void AT24CXX_WriteLenByte(uint16_t WriteAddr,uint32_t DataToWrite,uint8_t Len);//ָ����ַ��ʼд��ָ�����ȵ�����
uint32_t AT24CXX_ReadLenByte(uint16_t ReadAddr,uint8_t Len);					//ָ����ַ��ʼ��ȡָ����������
void AT24CXX_Write(uint16_t WriteAddr,uint8_t *pBuffer,uint16_t NumToWrite);	//��ָ����ַ��ʼд��ָ�����ȵ�����
void AT24CXX_Read(uint16_t ReadAddr,uint8_t *pBuffer,uint16_t NumToRead);   	//��ָ����ַ��ʼ����ָ�����ȵ�����

uint8_t AT24CXX_Check(void);  //�������
void AT24CXX_Init(void); //��ʼ��IIC
#endif















