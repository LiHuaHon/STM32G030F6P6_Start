///**
//  ******************************************************************************
//  * @file    bsp_as608.c
//  * @author  fire
//  * @version V1.0
//  * @date    2013-xx-xx
//  * @brief   指纹识别模块实验
//  ******************************************************************************
//  * @attention
//  *
//  * 实验平台:野火STM32 F103-霸道 开发板
//  * 论坛    :http://www.firebbs.cn
//  * 淘宝    :https://fire-stm32.taobao.com
//  *
//  ******************************************************************************
//  */
//#include "as608_test.h"
////#include "oled.h"

//extern uint8_t TouchOut_int_flag;

// /**
//  * @brief  指令解析
//  * @param  无
//  * @retval 无
//  */
//void Show_Message(void)
//{
//  printf("请输入指令，输入指令后请在输入窗口按回车键后再发送指令！！！\r\n");
//  printf("   指令   ------      功能 \r\n");
//  printf("    1     ------    添加指纹 \r\n");
//  printf("    2     ------    对比指纹 \r\n");
//  printf("    3     ------    删除指定用户指纹\r\n");
//  printf("    4     ------    清空指纹库\r\n");
//  printf("    5     ------    自动注册指纹\r\n");
//}

// /**
//  * @brief  用户指令解析
//  * @param  无
//  * @retval 无
//  */
//void UserShow_Message(void)
//{
//  printf("请输入指令，输入指令后请在输入窗口按回车键后再发送指令！！！\r\n");
//  printf("   指令   ------      功能 \r\n");
//  printf("    1    ------    自动注册指纹\r\n");
//  printf("    2     ------    对比指纹 \r\n");
//  printf("    3     ------    清空指纹库\r\n");
//}
// /**
//  * @brief  OLED用户指令解析
//  * @param  无
//  * @retval 无
//  */
//void OLED_Show_Message(void)
//{
//	ZhuCheZiWen();
//}

///**
//  * @brief  指纹模块操作
//  * @param  无
//  * @retval 无
//  */
//void  FR_Task(void)
//{
//  u8   ch;
//  scanf("%c",&ch);
//
//  printf("接收到字符：%c\r\n",ch);
//  switch(ch)
//  {
//    case '1':
//      Add_FR();                                    /*添加指纹*/
//		  Show_Message();
//    break;
//
//		case '2':
//      Compare_FR();                                /*比对指纹*/
//		  Show_Message();
//    break;

//    case '3':
//      Del_FR();                                    /*删除指定用户指纹*/
//		  Show_Message();
//    break;
//
//    case '4':
//      Clean_FR();                                  /*清空指纹库*/
//		  Show_Message();
//    break;
//
//		case '5':
//      Auto_FR();                                  /*清空指纹库*/

//    break;
//
//
//    default:
//      /* 如果不是指定指令字符，打印提示信息 */
//		  printf("请输入合法指令！\r\n\r\n");
//      Show_Message();
//    break;
//  }
//  return;
//}

///**
//  * @brief  用户指纹模块操作
//  * @param  无
//  * @retval 无
//  */
//void  UserFR_Task(void)
//{
//  u8   ch;
//  scanf("%c",&ch);
//  printf("接收到字符：%c\r\n",ch);
//  switch(ch)
//  {
//    case '1':
//      Auto_FR();                                      /*添加指纹*/
//    break;
//
//		case '2':
//      Compare_FR();                                /*比对指纹*/
//		  Show_Message();
//    break;
//
//    case '4':
//      Clean_FR();                                  /*清空指纹库*/
//		  Show_Message();
//    break;
//
//
//    default:
//      /* 如果不是指定指令字符，打印提示信息 */
//		  printf("请输入合法指令！\r\n\r\n");
//      Show_Message();
//    break;
//  }
//  return;
//}


///**
//  * @brief  检测与指纹模块的通信
//  * @param  无
//  * @retval 无
//  */
//void  Connect_Test(void)
//{
//	u8 ok=0;
//	while(ok==0)
//  if(PS_Connect(&AS608_Addr))                      /*与AS608串口通信*/
//  {
//		delay_ms(500);
//    printf("未检测到指纹模块，请检查连接！！！\r\n");
//  }
//  else
//  {
//	printf("初始化完成\n\r");
//	printf("通讯成功\r\n");
//	Show_Message();
//	ok=1;
//  }
//}

///**
//  * @brief  自动注册指纹
//  * @param  无
//  * @retval 无
//  */
//void Auto_FR(void)
//{
//  uint16_t  sure;
//  printf("请放置手指在指纹传感器上\r\n\r\n");
//  sure=PS_Enroll();
//  if(sure == 0x00)
//  {
//		printf ("注册成功\r\n\r\n");
//  }
//	else
//	{
//	  ShowErrMessage(sure);
//	}
//
//}



///**
//  * @brief  录指纹
//  * @param  无
//  * @retval 无
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
//      case 0:                            /*执行第1步*/
//
//        i++;
//
//        printf("******命令：请按手指******\r\n");
//
//        sure=PS_GetImage();              /*录入图像*/
//        if(sure == 0x00)
//        {
//          sure=PS_GenChar(CHAR_BUFFER1);  /*生成特征1*/
//          if(sure==0x00)
//          {
//				    printf("输入指纹1正常！！！\r\n");
//						pull_data_from_queue();
//            sure=PS_HighSpeedSearch(CHAR_BUFFER1,0,PS_MAXNUM,&ID);
//            if(sure==0x00)
//            {
//             printf ("指纹已存在，指纹ID：%d！！！\r\n\r\n",ID);
//
//             return ;
//            }
//            else
//            {
//              i=0;
//              j=1;                   /*跳转到第2步*/
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
//        printf("******命令：请再按一次手指******\r\n");
//
//        sure=PS_GetImage();
//        if(sure==0x00)
//        {
//          sure=PS_GenChar(CHAR_BUFFER2);  /*生成特征2*/
//          if(sure==0x00)
//          {
//				    printf("输入指纹2正常！！！\r\n");
//            i=0;
//            j=2;                   /*跳转到第3步*/
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
//         printf("正在对比两次输入的指纹\r\n");
//
//         sure=PS_Match();                /*精确比对两枚指纹特征*/
//         if(sure==0x00)
//         {
//				   printf("输入指纹对比成功！！！\r\n");
//
//           j=3;                         /*跳转到第4步*/
//         }
//         else
//         {
//           printf("对比失败，请重新录入指纹！！！\r\n");
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
//         printf("正在生成指纹模块\r\n");
//
//         sure=PS_RegModel();            /*合并特征（生成模板）*/
//         if(sure==0x00)
//         {
//           printf("生成指纹模块成功！！！\r\n");
//           j=4;                        /*跳转到第5步*/
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
//           printf ("******命令：请输入存储ID，范围为0---239******\r\n");
//
//           ID=1;
//         }while(!(ID<PS_MAXNUM));
//
//         sure=PS_StoreChar(CHAR_BUFFER2,ID);  /*储存模板*/
//         if(sure==0x00)
//         {
//           printf("录入指纹模块成功！！！\r\n\r\n");
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
//      if(i==4)                       /*超过4次没有按手指则退出*/
//      {
//        printf("录指纹失败！\r\n\r\n\r\n");

//        break;
//      }
//  }
//}


///**
//  * @brief  比对指纹（识别指纹）
//  * @param  无
//  * @retval 无
//  */
//void Compare_FR(void)
//{
//  uint16_t  ID=0;                    /*初始化ID值*/
//  uint16_t  sure;
//
//  printf("******命令：对比指纹，请按手指******\r\n");

//  sure=PS_GetImage();
//  if(sure == 0x00)
//  {
//    sure=PS_GenChar(CHAR_BUFFER1);    /*生成特征1*/
//    if(sure==0x00)
//    {
//			/*高速搜索指纹库*/
//      sure=PS_HighSpeedSearch(CHAR_BUFFER1,0,PS_MAXNUM,&ID);
//      if(sure==0x00)
//      {
//        printf ("对比指纹成功，指纹ID：%d！！！\r\n\r\n",ID);
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
//  * @brief  清空指纹库
//  * @param  无
//  * @retval 无
//  */
//void Clean_FR(void)
//{
//	uint16_t  sure;
//	u8   ch;
//	printf("清空指纹库后将需要重新录入所有指纹请谨慎确定\r\n");
//	printf("输入1确认2取消\r\n");
//  scanf("%c",&ch);
//  printf("接收到字符：%c\r\n",ch);
//	if(ch == 1)
//	{
//		sure=PS_Empty();
//		if(sure == 0x00)
//		{
//				printf("清空指纹库成功！！！\r\n\r\n");
//		}
//		else
//		{
//				ShowErrMessage(sure);
//		}
//	}
//}


///**
//  * @brief  删除指定用户指纹
//  * @param  无
//  * @retval 无
//  */
//void Del_FR(void)
//{
//	uint32_t  ID;
//	uint16_t  sure;
//
//	printf("删除指定用户ID\r\n");
//
//	do
//	{
//		printf("******命令：请输入存储ID，范围为0—239******\r\n");
//		ID=GET_NUM();
//	}while(!(ID<PS_MAXNUM));         /*输入ID不能超过指纹模块最大容量*/
//
//	sure=PS_DeletChar(ID,1);         /*删除指定用户的指纹模板*/
//
//	if(sure == 0x00)
//	{
//		printf("删除指定用户指纹成功！！！\r\n\r\n");
//	}
//	else
//	{
//		ShowErrMessage(sure);
//	}
//}


///*********************************************END OF FILE**********************/
