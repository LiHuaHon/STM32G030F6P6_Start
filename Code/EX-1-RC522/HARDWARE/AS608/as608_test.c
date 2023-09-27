///**
//  ******************************************************************************
//  * @file    bsp_as608.c
//  * @author  fire
//  * @version V1.0
//  * @date    2013-xx-xx
//  * @brief   ָ��ʶ��ģ��ʵ��
//  ******************************************************************************
//  * @attention
//  *
//  * ʵ��ƽ̨:Ұ��STM32 F103-�Ե� ������
//  * ��̳    :http://www.firebbs.cn
//  * �Ա�    :https://fire-stm32.taobao.com
//  *
//  ******************************************************************************
//  */
//#include "as608_test.h"
////#include "oled.h"

//extern uint8_t TouchOut_int_flag;

// /**
//  * @brief  ָ�����
//  * @param  ��
//  * @retval ��
//  */
//void Show_Message(void)
//{
//  printf("������ָ�����ָ����������봰�ڰ��س������ٷ���ָ�����\r\n");
//  printf("   ָ��   ------      ���� \r\n");
//  printf("    1     ------    ����ָ�� \r\n");
//  printf("    2     ------    �Ա�ָ�� \r\n");
//  printf("    3     ------    ɾ��ָ���û�ָ��\r\n");
//  printf("    4     ------    ���ָ�ƿ�\r\n");
//  printf("    5     ------    �Զ�ע��ָ��\r\n");
//}

// /**
//  * @brief  �û�ָ�����
//  * @param  ��
//  * @retval ��
//  */
//void UserShow_Message(void)
//{
//  printf("������ָ�����ָ����������봰�ڰ��س������ٷ���ָ�����\r\n");
//  printf("   ָ��   ------      ���� \r\n");
//  printf("    1    ------    �Զ�ע��ָ��\r\n");
//  printf("    2     ------    �Ա�ָ�� \r\n");
//  printf("    3     ------    ���ָ�ƿ�\r\n");
//}
// /**
//  * @brief  OLED�û�ָ�����
//  * @param  ��
//  * @retval ��
//  */
//void OLED_Show_Message(void)
//{
//	ZhuCheZiWen();
//}

///**
//  * @brief  ָ��ģ�����
//  * @param  ��
//  * @retval ��
//  */
//void  FR_Task(void)
//{
//  u8   ch;
//  scanf("%c",&ch);
//
//  printf("���յ��ַ���%c\r\n",ch);
//  switch(ch)
//  {
//    case '1':
//      Add_FR();                                    /*����ָ��*/
//		  Show_Message();
//    break;
//
//		case '2':
//      Compare_FR();                                /*�ȶ�ָ��*/
//		  Show_Message();
//    break;

//    case '3':
//      Del_FR();                                    /*ɾ��ָ���û�ָ��*/
//		  Show_Message();
//    break;
//
//    case '4':
//      Clean_FR();                                  /*���ָ�ƿ�*/
//		  Show_Message();
//    break;
//
//		case '5':
//      Auto_FR();                                  /*���ָ�ƿ�*/

//    break;
//
//
//    default:
//      /* �������ָ��ָ���ַ�����ӡ��ʾ��Ϣ */
//		  printf("������Ϸ�ָ�\r\n\r\n");
//      Show_Message();
//    break;
//  }
//  return;
//}

///**
//  * @brief  �û�ָ��ģ�����
//  * @param  ��
//  * @retval ��
//  */
//void  UserFR_Task(void)
//{
//  u8   ch;
//  scanf("%c",&ch);
//  printf("���յ��ַ���%c\r\n",ch);
//  switch(ch)
//  {
//    case '1':
//      Auto_FR();                                      /*����ָ��*/
//    break;
//
//		case '2':
//      Compare_FR();                                /*�ȶ�ָ��*/
//		  Show_Message();
//    break;
//
//    case '4':
//      Clean_FR();                                  /*���ָ�ƿ�*/
//		  Show_Message();
//    break;
//
//
//    default:
//      /* �������ָ��ָ���ַ�����ӡ��ʾ��Ϣ */
//		  printf("������Ϸ�ָ�\r\n\r\n");
//      Show_Message();
//    break;
//  }
//  return;
//}


///**
//  * @brief  �����ָ��ģ���ͨ��
//  * @param  ��
//  * @retval ��
//  */
//void  Connect_Test(void)
//{
//	u8 ok=0;
//	while(ok==0)
//  if(PS_Connect(&AS608_Addr))                      /*��AS608����ͨ��*/
//  {
//		delay_ms(500);
//    printf("δ��⵽ָ��ģ�飬�������ӣ�����\r\n");
//  }
//  else
//  {
//	printf("��ʼ�����\n\r");
//	printf("ͨѶ�ɹ�\r\n");
//	Show_Message();
//	ok=1;
//  }
//}

///**
//  * @brief  �Զ�ע��ָ��
//  * @param  ��
//  * @retval ��
//  */
//void Auto_FR(void)
//{
//  uint16_t  sure;
//  printf("�������ָ��ָ�ƴ�������\r\n\r\n");
//  sure=PS_Enroll();
//  if(sure == 0x00)
//  {
//		printf ("ע��ɹ�\r\n\r\n");
//  }
//	else
//	{
//	  ShowErrMessage(sure);
//	}
//
//}



///**
//  * @brief  ¼ָ��
//  * @param  ��
//  * @retval ��
//  */
//void  Add_FR(void)
//{
//  uint16_t  i,j,sure,ID;
//
//  i=j=0;
//
//  while(1)
//  {
//    switch (j)
//    {
//      case 0:                            /*ִ�е�1��*/
//
//        i++;
//
//        printf("******����밴��ָ******\r\n");
//
//        sure=PS_GetImage();              /*¼��ͼ��*/
//        if(sure == 0x00)
//        {
//          sure=PS_GenChar(CHAR_BUFFER1);  /*��������1*/
//          if(sure==0x00)
//          {
//				    printf("����ָ��1����������\r\n");
//						pull_data_from_queue();
//            sure=PS_HighSpeedSearch(CHAR_BUFFER1,0,PS_MAXNUM,&ID);
//            if(sure==0x00)
//            {
//             printf ("ָ���Ѵ��ڣ�ָ��ID��%d������\r\n\r\n",ID);
//
//             return ;
//            }
//            else
//            {
//              i=0;
//              j=1;                   /*��ת����2��*/
//             }
//           }
//				 else
//				 {
//					 ShowErrMessage(sure);
//				 }
//        }
//			  else
//			  {
//				  ShowErrMessage(sure);
//			  }
//      break;


//      case 1:
//
//        i++;
//
//        printf("******������ٰ�һ����ָ******\r\n");
//
//        sure=PS_GetImage();
//        if(sure==0x00)
//        {
//          sure=PS_GenChar(CHAR_BUFFER2);  /*��������2*/
//          if(sure==0x00)
//          {
//				    printf("����ָ��2����������\r\n");
//            i=0;
//            j=2;                   /*��ת����3��*/
//          }
//				  else
//				  {
//					  ShowErrMessage(sure);
//				  }

//         }
//			   else
//			   {
//			   ShowErrMessage(sure);
//         }
//       break;

//
//       case 2:
//
//         printf("���ڶԱ����������ָ��\r\n");
//
//         sure=PS_Match();                /*��ȷ�ȶ���öָ������*/
//         if(sure==0x00)
//         {
//				   printf("����ָ�ƶԱȳɹ�������\r\n");
//
//           j=3;                         /*��ת����4��*/
//         }
//         else
//         {
//           printf("�Ա�ʧ�ܣ�������¼��ָ�ƣ�����\r\n");
//           ShowErrMessage(sure);
//           i=0;
//           j=0;
//         }
//
//       break;
//
//
//       case 3:
//
//         printf("��������ָ��ģ��\r\n");
//
//         sure=PS_RegModel();            /*�ϲ�����������ģ�壩*/
//         if(sure==0x00)
//         {
//           printf("����ָ��ģ��ɹ�������\r\n");
//           j=4;                        /*��ת����5��*/
//         }
//         else
//        {
//         j =0;
//         ShowErrMessage(sure);
//        }
//
//       break;
//

//       case 4:
//
//         do
//         {
//           printf ("******���������洢ID����ΧΪ0---239******\r\n");
//
//           ID=1;
//         }while(!(ID<PS_MAXNUM));
//
//         sure=PS_StoreChar(CHAR_BUFFER2,ID);  /*����ģ��*/
//         if(sure==0x00)
//         {
//           printf("¼��ָ��ģ��ɹ�������\r\n\r\n");
//
//           return ;
//         }
//         else
//         {
//           j =0;
//           ShowErrMessage(sure);
//         }
//       break;
//      }
//
//      delay_ms(1000);
//
//      if(i==4)                       /*����4��û�а���ָ���˳�*/
//      {
//        printf("¼ָ��ʧ�ܣ�\r\n\r\n\r\n");

//        break;
//      }
//  }
//}


///**
//  * @brief  �ȶ�ָ�ƣ�ʶ��ָ�ƣ�
//  * @param  ��
//  * @retval ��
//  */
//void Compare_FR(void)
//{
//  uint16_t  ID=0;                    /*��ʼ��IDֵ*/
//  uint16_t  sure;
//
//  printf("******����Ա�ָ�ƣ��밴��ָ******\r\n");

//  sure=PS_GetImage();
//  if(sure == 0x00)
//  {
//    sure=PS_GenChar(CHAR_BUFFER1);    /*��������1*/
//    if(sure==0x00)
//    {
//			/*��������ָ�ƿ�*/
//      sure=PS_HighSpeedSearch(CHAR_BUFFER1,0,PS_MAXNUM,&ID);
//      if(sure==0x00)
//      {
//        printf ("�Ա�ָ�Ƴɹ���ָ��ID��%d������\r\n\r\n",ID);
//      }
//      else
//      {
//			ShowErrMessage(sure);
//			}
//    }
//    else
//    {
//      ShowErrMessage(sure);
//    }
//  }
//	else
//	{
//	  ShowErrMessage(sure);
//	}
//
//}



///**
//  * @brief  ���ָ�ƿ�
//  * @param  ��
//  * @retval ��
//  */
//void Clean_FR(void)
//{
//	uint16_t  sure;
//	u8   ch;
//	printf("���ָ�ƿ����Ҫ����¼������ָ�������ȷ��\r\n");
//	printf("����1ȷ��2ȡ��\r\n");
//  scanf("%c",&ch);
//  printf("���յ��ַ���%c\r\n",ch);
//	if(ch == 1)
//	{
//		sure=PS_Empty();
//		if(sure == 0x00)
//		{
//				printf("���ָ�ƿ�ɹ�������\r\n\r\n");
//		}
//		else
//		{
//				ShowErrMessage(sure);
//		}
//	}
//}


///**
//  * @brief  ɾ��ָ���û�ָ��
//  * @param  ��
//  * @retval ��
//  */
//void Del_FR(void)
//{
//	uint32_t  ID;
//	uint16_t  sure;
//
//	printf("ɾ��ָ���û�ID\r\n");
//
//	do
//	{
//		printf("******���������洢ID����ΧΪ0��239******\r\n");
//		ID=GET_NUM();
//	}while(!(ID<PS_MAXNUM));         /*����ID���ܳ���ָ��ģ���������*/
//
//	sure=PS_DeletChar(ID,1);         /*ɾ��ָ���û���ָ��ģ��*/
//
//	if(sure == 0x00)
//	{
//		printf("ɾ��ָ���û�ָ�Ƴɹ�������\r\n\r\n");
//	}
//	else
//	{
//		ShowErrMessage(sure);
//	}
//}


///*********************************************END OF FILE**********************/