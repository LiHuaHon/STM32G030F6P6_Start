#include ".\SYSTEM\sys\sys.h"
#include <stdlib.h>

extern __IO uint16_t USART_RX_STA;         		//接收状态标记	
//阻塞从串口获取字符
char My_getchar(void){
		USART_RX_STA=0;//重新接收
		while(1)
		if(USART_RX_STA&0x8000)
		{					   
			USART_RX_STA=0;
			break;
		}
		
		return USART_RX_BUF[0];
}
//阻塞从串口获取字符串
void My_getstring(char* returnData){
		uint16_t len;
		USART_RX_STA=0;//重新接收
		while(1)
		if(USART_RX_STA&0x8000)
		{					   
			len=USART_RX_STA&0x3fff;//得到此次接收到的数据长度
			USART_RX_STA=0;
			break;
		}
		get_data_str((char*)USART_RX_BUF,0,len,returnData);
}
//从指定数组中挑选字符串并返回
void get_data_str(char* dataAddress, uint16_t dataStartBit, uint16_t dataEndBit, char* returnData){
	uint16_t tempdata=0;
	uint16_t i;
	for(i=0; i<dataEndBit-dataStartBit; i++)
	{	
		tempdata=*(dataAddress+dataStartBit+i);
		returnData[i]=tempdata;
	}
}

