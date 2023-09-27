#include "KEY.h"
#include "delay.h"

u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//按键按松开标志
	if(mode)key_up=1;  //支持连按		  
	if(key_up&&(KEY0_UP==1||KEY1_CE==0||KEY2_DN ==0||KEY3_OP==0||KEY4_CL==0))
	{
		delay_ms(10);//去抖动 
		key_up=0;
		if(KEY0_UP==1)return KEY0_PRES_UP ;
		 if(KEY1_CE==0)return KEY1_PRES_CE ;
		 if(KEY2_DN==0)return KEY2_PRES_DN  ;
		 if(KEY3_OP==0)return KEY3_PRES_OP  ;
		 if(KEY4_CL==0)return KEY4_PRES_CL  ;
	}else if(KEY0_UP==0&&KEY1_CE==1&&KEY2_DN==1&&KEY3_OP==1&&KEY4_CL==1)key_up=1; 	     
	return 0;// 无按键按下

}
u8 KEY_Mode(void)
{	 
	while(1)
		 switch(KEY_Scan(0))
  {
			case KEY1_PRES_CE: 
			return KEY1_PRES_CE; 
		
			case KEY0_PRES_UP:             
			return KEY0_PRES_UP; 
			
			case KEY2_PRES_DN:				
			return KEY2_PRES_DN; 
			
			case KEY4_PRES_CL:		
			return KEY4_PRES_CL; 
			
			default:
				delay_ms(100);
  }
}




