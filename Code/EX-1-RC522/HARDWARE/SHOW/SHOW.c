#include ".\HARDWARE\SHOW\SHOW.h"

void Show_Clear(){
	HAL_Delay(1);
	printf("\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r");
	HAL_Delay(1);
	printf("\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r");
}

void Show_Menu(void){
	Show_Clear();
	printf("\n\r门锁控制系统V1.0\n");
	printf("\n\r输入1 显示当前存储用户\n");
	printf("\n\r输入2 输入序号删除指定用户\n");
//	printf("\n\r输入3 批量输入序号删除用户\n");
	printf("\n\r输入4 添加单个用户\n");
//	printf("\n\r输入5 清空所有用户\n");
	printf("\n\r输入8 保存并重启系统\n\r");
}






