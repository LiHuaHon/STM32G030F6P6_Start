#include ".\HARDWARE\SHOW\SHOW.h"

void Show_Clear(){
	HAL_Delay(1);
	printf("\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r");
	HAL_Delay(1);
	printf("\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r");
}

void Show_Menu(void){
	Show_Clear();
	printf("\n\r��������ϵͳV1.0\n");
	printf("\n\r����1 ��ʾ��ǰ�洢�û�\n");
	printf("\n\r����2 �������ɾ��ָ���û�\n");
//	printf("\n\r����3 �����������ɾ���û�\n");
	printf("\n\r����4 ��ӵ����û�\n");
//	printf("\n\r����5 ��������û�\n");
	printf("\n\r����8 ���沢����ϵͳ\n\r");
}






