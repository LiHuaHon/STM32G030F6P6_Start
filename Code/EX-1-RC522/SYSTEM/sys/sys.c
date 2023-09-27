#include ".\SYSTEM\sys\sys.h"
#include <stdlib.h>

extern __IO uint16_t USART_RX_STA;         		//����״̬���	
//�����Ӵ��ڻ�ȡ�ַ�
char My_getchar(void){
		USART_RX_STA=0;//���½���
		while(1)
		if(USART_RX_STA&0x8000)
		{					   
			USART_RX_STA=0;
			break;
		}
		
		return USART_RX_BUF[0];
}
//�����Ӵ��ڻ�ȡ�ַ���
void My_getstring(char* returnData){
		uint16_t len;
		USART_RX_STA=0;//���½���
		while(1)
		if(USART_RX_STA&0x8000)
		{					   
			len=USART_RX_STA&0x3fff;//�õ��˴ν��յ������ݳ���
			USART_RX_STA=0;
			break;
		}
		get_data_str((char*)USART_RX_BUF,0,len,returnData);
}
//��ָ����������ѡ�ַ���������
void get_data_str(char* dataAddress, uint16_t dataStartBit, uint16_t dataEndBit, char* returnData){
	uint16_t tempdata=0;
	uint16_t i;
	for(i=0; i<dataEndBit-dataStartBit; i++)
	{	
		tempdata=*(dataAddress+dataStartBit+i);
		returnData[i]=tempdata;
	}
}

