//#include "FPM383C_control .h"
//#define SETwarning 10 //������
//u8 REpassword[6]= {0,0,0,0,0,0}; //ϵͳ����
//u8 warning=0;//ϵͳ������

//extern	u8 sec;
//extern	u8 time_s;
//extern u8 min_s;
//extern	u8 min;
//extern	u8 hou;
//extern u8 FPM_LED;

//void TimeRSET(void) {
//    sec=0;
//    min=0;
//    hou=0;
//}

// /**
//  * @brief  ���Ӳ���
//  * @retval �ɹ�����0;
//  */
//u8 FPM_Connect(void)
//{
//    u8 time=10;
//    u8 sure=1;
//    OLED_Clear();
//    OLED_ShowString(0,0,"Please wait",16);
//    while (sure)
//    {
//        FPM383C_Heart();
//        delay_ms(500);
//        sure=Receive_Check();
//        if(time==0) {
//            sure=0XFF;
//            OLED_ShowErrMessage	(sure);
//            delay_s(2);
//						OLED_Clear();
//            return 1;
//        }
//        time--;
//    }
//    OLED_Clear();
//    return 0;
//}
// /**
//  * @brief  ���ƽ���
//  * @param  ��
//  * @retval ��
//  */
//void OLEDShow_Page_1(void)
//{
//    OLED_ShowString(0,0,"Page 1",16);//��ʾASCII�ַ�����ֵ
//    OLED_ShowString(16,2,"REG Finger",16);//ע��ָ��
//    OLED_ShowString(16,4,"TEST Finger",16);//���ָ��
//    OLED_ShowString(16,6,"CL ALL Finger",16);//���ָ��

//}
//void OLEDShow_Page_2(void)
//{
//    OLED_ShowString(0,0,"Page 2",16);//��ʾASCII�ַ�����ֵ
//    OLED_ShowString(16,2,"CHA SafeLeve",16);
//    OLED_ShowString(16,4,"CHA Password",16);
//    OLED_ShowString(16,6,"ESP I2CTest ",16);

//}
//void OLEDShow_Page_3(void)
//{
//    OLED_ShowString(0,0,"Page 3",16);//��ʾASCII�ַ�����ֵ
//    OLED_ShowString(16,2,"Software V1.0",16);
//    OLED_ShowString(16,4,"BY-TP",16);
//}
///**
//  * @brief  �Զ����ָ��
//  * @param  ��
//  * @retval 0��֤ͨ�� 1��֤ʧ��
//  */
//u8 AutoControl_FR(void)
//{
//    u16 sure=1;
//    u16  ID=0;
//    u16  RS=0;
//    OLED_Clear();
//    OLED_ShowString(0,0,"System busy",16);
//    OLED_ShowString(0,2,"Please wait",16);
//    delay_ms(10);
//    FPM383C_Matching();
//    delay_ms(400);
//    sure=Finger_Check(&ID,&RS);

//    OLED_Clear();
//    OLED_ShowString(0,4,"ID:",16);
//    OLED_ShowString(0,6,"RS:",16);
//    OLED_ShowNum(24,4,ID,2,16);
//    OLED_ShowNum(24,6,RS,2,16);

//    if(RS>=1&&ID<40&&sure==0x00) {
//        OPEN_DOOR();
//        FPM383C_LED(1,1,1,1,1);
//        delay_s(2);
//        FPM383C_LED(3,6,64,10,50);//ģʽ ��ɫ ռ�ձ�1 ռ�ձ�2 �仯����
//        CLOSE_DOOR();
//        OLED_Clear();
//			  FPM_LED=1;
//			  warning=0;
//			
//				sure=FPM_Connect();
//				OLED_Clear();
//				if(sure!=0) {
//					return 1;
//				}
//				
//        return 0;

//    }
//    else if(sure==0x00) {
//        OLED_Clear();
//        OLED_ShowErrMessage	(sure);
//        FPM383C_LED(4,2,30,10,5);
//        delay_ms(2000);
//        FPM383C_LED(3,5,64,10,50);//ģʽ ��ɫ ռ�ձ�1 ռ�ձ�2 �仯����
//        OLED_Clear();
//			  warning++;
//        return 0;
//    }

//    OLED_Clear();
//    return 1;
//}

///**
//  * @brief  ����ָ�ƽ���ģʽ
//  * @param  ��
//  * @retval ��
//  */
//void FPM383C_Work(void) {
//	
//				u8 sure2=1;
//        u8 cs2=0;
//	 switch(KEY_Scan(0))
//		{
//				case KEY3_PRES_OP://���¿���
//					min_s=0;//�ص����¼�ʱ
//					OPEN_DOOR();
//					FPM383C_LED(1,1,1,1,1);
//					delay_s(2);
//					FPM383C_LED(3,6,64,10,50);//ģʽ ��ɫ ռ�ձ�1 ռ�ձ�2 �仯����
//					FPM_LED=1;
//					warning=0;
//					CLOSE_DOOR();
//					break;
//				
//				case KEY2_PRES_DN://���½�������ϵͳ
//				min_s=0;//�ص����¼�ʱ
//        OLED_Clear();
//        Password_Menu();//��������ִ�в˵�
//				while(sure2) {
//            cs2++;
//            FPM383C_Sleep();
//            delay_ms(200);
//            sure2=Receive_Check();//˯��;
//            if(cs2>=5)break;
//        }
//        OLED_Clear();
//				break;
//				
//				
//				default:
//						delay_ms(10);
//		}
//    if(warning>=SETwarning){//���泬��ֱ������
//       u8 sure3=1;
//       u8 cs3=0;
//			OLED_ShowString(0,0,"WARNING:",16);
//			OLED_ShowString(0,2,"SYS:",16);
//			OLED_ShowString(32,2,"LOCK    ",16);
//			OLED_ShowChar(98,6,':',16);
//			OLED_ShowChar(74,6,':',16);
//			OLED_ShowNum(64,0,warning,2,16);
//			
//			while(1){
//			if(KEY_Scan(0)==KEY3_PRES_OP){//���½���
//			warning=0;
//			break;
//			}
//			OLED_ShowNum(54,6,hou,2,16);
//			OLED_ShowNum(82,6,min,2,16);
//			OLED_ShowNum(108,6,sec,2,16);
//			};
//			while(sure3) {
//            cs3++;
//            FPM383C_Sleep();
//            delay_ms(200);
//            sure3=Receive_Check();//˯��;
//            if(cs3>=5)break;
//        }
//			
//		}else if(FMP383C_SLEEP==1) { //ģ�鱻����0
//        u8 sure1=1;
//        u8 cs1=0;		
//				min_s=0;//�ص����¼�ʱ
//        while(sure1) {

//            cs1++;
//            sure1=AutoControl_FR();
//            if(cs1>=5){
//							warning++;
//							break;
//						}
//        }
//        delay_ms(200);//����
//        sure1=1;
//        cs1=0;
//				
//        while(sure1) {
//            cs1++;
//            FPM383C_Sleep();
//            delay_ms(200);
//            sure1=Receive_Check();//˯��;
//            if(cs1>=5)break;
//        }
//				
//    }
//}

///**
//  * @brief  ��������ϵͳ ����������ȷ������û�����ϵͳ
//  * @param  ��
//  * @retval ��
//  */
//void Password_Menu(void)
//{

//    u8 temp=0;
//    u8 num=0;
//    u8 CKpassword[6]= {0};
//    u8 NumFlage=0;//����ͳ��λ

//    OLED_ShowString(0,0,"LodingMenu",16);//
//    OLED_ShowString(0,2,"EntPassword",16);//

//    OLED_ShowNum(95,6,num,1,16);
//    OLED_ShowChar(0*20+10,4,'-',16);
//    OLED_ShowChar(1*20+10,4,'-',16);
//    OLED_ShowChar(2*20+10,4,'-',16);
//    OLED_ShowChar(3*20+10,4,'-',16);
//    OLED_ShowChar(4*20+10,4,'-',16);
//    OLED_ShowChar(5*20+10,4,'-',16);
//    OLED_ShowChar(108,6,'<',16);

//    while(1) {
//        if(time_s>=360) {
//            time_s=0;
//            return;//��ʱ�ر�
//        }
//        switch((u8)KEY_Scan(0))
//        {
//        case KEY1_PRES_CE:
//            CKpassword[NumFlage]=num;
//            OLED_ShowNum(NumFlage*20+10,4,num,1,16);
//            if(NumFlage>=5) {	//����������Ѿ���6λ�����Խ�������ȶ�

//                OLED_ShowString(0,6,"SURE EntCE",16);
//                OLED_ShowChar(108,6,'<',16);

//                temp=KEY_Mode();//�������ȡ��������һ�� ����ȷ�Ͻ�������ȶԻ���
//                if(temp==KEY1_PRES_CE) {

//                    temp=Password_Check(CKpassword);//�����ݴ�����֤����

//                    if(temp==1) { //�����������ȷ��
//                        OLED_Clear();
//                        temp=0;
//                        time_s=0;
//                        OLED_Show_Message();
//                        OLED_Clear();
//                        return ;
//                    } else if(temp==0) { //�������
//                        OLED_Clear();
//                        OLED_ShowString(0,0,"PS ERROR",16);
//                        delay_ms(1000);
//                        OLED_Clear();
//                        return ;
//                    }
//                } else if(temp==KEY4_PRES_CL||temp==KEY0_PRES_UP||temp==KEY2_PRES_DN)
//                {
//                    temp=0;
//                    OLED_ShowString(0,6,"                ",16);
//                    OLED_ShowChar(108,6,'<',16);
//                    OLED_ShowNum(95,6,num,1,16);
//                }
//            } else {
//                NumFlage++;
//            }

//            break;

//        case	KEY2_PRES_DN:
//            if(num>0) {
//                num--;
//            }
//            OLED_ShowNum(95,6,num,1,16);
//            break;

//        case  KEY0_PRES_UP:
//            if(num<9) {
//                num++;
//            }
//            OLED_ShowNum(95,6,num,1,16);
//            break;

//        case KEY4_PRES_CL:

//            CKpassword[NumFlage]=num;
//            OLED_ShowChar(NumFlage*20+10,4,'-',16);
//            if(NumFlage<=0) {
//                temp=KEY_Mode();
//                if(temp==KEY4_PRES_CL) { //�������ȡ��ֱ�ӽ���������
//                    temp=0;
//                    OLED_Clear();
//                    return ;
//                }
//            } else {
//                NumFlage--;
//            }
//            break;

//        default:
//            delay_ms(10);
//            OLED_ShowChar(NumFlage*20+10,4,'+',16);
//        }
//    }
//}

//void  UserFR_OLED(u8 temp)
//{
//    switch(temp)
//    {
//    case 2:
//        AutoAdd_FR();                                      /*���ָ��*/
//        OLED_Clear();
//        OLED_ShowChar(0,temp%6,'>',16);//��ͷ
//        break;

//    case 4:
//				AutoCompare_FR();                                /*�ȶ�ָ��*/
//        OLED_Clear();
//        OLED_ShowChar(0,temp%6,'>',16);//��ͷ
//        break;

//    case 6:
//        Clean_FR();                                  /*���ָ�ƿ�*/
//        OLED_Clear();
//        OLED_ShowChar(0,temp%6,'>',16);//��ͷ
//        break;
//    default:
//        delay_ms(50);
//        break;
//    }
//    return;
//}
// /**
//  * @brief  ����tempչʾĿǰ���ڵ�ҳ��
//  * @param  ��
//  * @retval ��
//  */
//void OLEDShow_Page(u8 temp) {

//    if(temp<7) {
//        OLEDShow_Page_1();
//    } else if(temp>7&&temp<13) {
//        OLEDShow_Page_2();
//    } else if(temp>13) {
//        OLEDShow_Page_3();
//    }
//}

//void OLED_Show_Message(void)
//{
//    static u8 temp =2;
//    u8 temp1 =2;
//    OLED_Clear();
//    OLEDShow_Page(temp);
//    OLED_ShowChar(0,temp%6,'>',16);//��ͷ

//    while(1) {
//        OLEDShow_Page(temp);
//        switch((u8)KEY_Mode())
//        {
//        case KEY1_PRES_CE:
//            UserFR_OLED(temp);
////			return OK;
//            break;

//        case KEY0_PRES_UP:

//            if(temp%6==0) {
//                OLED_Clear();
//            }
//            else
//                OLED_ShowChar(0,temp%6,'>',16);//��ͷ
//            if(temp>2) {
//                temp-=2;
//            }
//            else
//            {
//                temp=18;
//            }
//            OLED_Clear();//�����ӻ���������ص���BUG����ϵͳ�ӳٻ�����
//            OLEDShow_Page(temp);
//            if(temp%6==0)
//                OLED_ShowChar(0,6,'>',16);//��ͷ
//            else
//                OLED_ShowChar(0,temp%6,'>',16);//��ͷ

//            break;

//        case KEY2_PRES_DN:

//            if(temp%6==0) {
//                OLED_Clear();
//            }
//            else
//                OLED_ShowChar(0,temp%6,'>',16);
//            if(temp<18) {
//                temp+=2;
//            }
//            else
//            {
//                temp=2;
//            }
//            OLED_Clear();//�����ӻ���������ص���BUG����ϵͳ�ӳٻ�����
//            OLEDShow_Page(temp);
//            if(temp%6==0)
//                OLED_ShowChar(0,6,'>',16);//��ͷ
//            else
//                OLED_ShowChar(0,temp%6,'>',16);//��ͷ

//            break;

//        case KEY4_PRES_CL:
//            OLED_Clear();


//            OLED_ShowString(0,0,"Ent CL",16);
//            OLED_ShowString(0,2,"Close menu ",16);
//            temp1=KEY_Mode();//�������ȡ��������һ�� ����ȷ�Ͻ�������ȶԻ���
//            if(temp1==KEY4_PRES_CL) {
//                return ;
//            }
//            break;

//        default:
//            delay_ms(10);
//        }
//    }
//}
//void Countdown(u8 time,u8 Line)
//{
//    OLED_ShowString(0,Line,"Countdown",16);
//    while(time>=1) {
//        OLED_ShowNum(80,Line,time--,2,16);
//        delay_s(1);
//    }
//}
///**
//  * @brief  �Զ�ע��ָ��
//  * @param  ��
//  * @retval ��
//  */

//void AutoAdd_FR(void)
//{

//    uint16_t  sure;
//    uint16_t percentage;
//    OLED_Clear();

//    sure=FPM_Connect();
//    if(sure!=0) {
//        return;
//    }
//    OLED_ShowString(0,0,"Put your finger",16);
//    OLED_ShowString(0,2,"on FPM",16);
//    Countdown(10,6) ;
//    OLED_Clear();
//    FPM383C_AutoREG(1,6);
//    OLED_ShowString(0,0,"Lift again and  push on FPM",16);
//    OLED_ShowString(0,4,"Until 100%",16);
//    OLED_ShowString(0,6,"Now PM>",16);
//    OLED_ShowString(58,6,"000",16);
//    OLED_ShowString(82,6,"%",16);
//    while(1) {
//        delay_ms(300);
//        sure=Receive_REGCheck(&percentage);
//        OLED_ShowNum(58,6,percentage,3,16);

//        if(percentage==0x64) { //¼�����
//            delay_s(1);
//            OLED_Clear();
//            OLED_ShowString(0,0,"Success",16);
//            delay_s(2);
//            break;
//        } else if(sure==0x0F) {
//            OLED_Clear();
//            OLED_ShowString(0,0,"Fingerprint already exists",16);
//            delay_s(2);
//            return ;
//        }

//    }

//}
///**
//  * @brief  ���ָ�Ʋ���
//  * @param  ��
//  * @retval ��
//  */
//void AutoCompare_FR(void)
//{
//		 u8 sure=1;
//     u8 cs=0;
//    OLED_Clear();
//    OLED_ShowString(0,0,"Put your finger",16);
//    OLED_ShowString(0,2,"on FPM",16);
//    Countdown(5,6) ;
//	
//    OLED_Clear();
//    OLED_ShowString(0,0,"System busy",16);
//    OLED_ShowString(0,2,"Please wait",16);
//		while(sure) {
//					cs++;
//					sure=AutoControl_FR();
//					if(cs>=5)break;
//		}
//}
///**
//  * @brief  ���ָ�ƿ�
//  * @param  ��
//  * @retval ��
//  */
//void Clean_FR(void)
//{
//    uint16_t  sure;
//    u8   temp=0;
//	
//			sure=FPM_Connect();
//				OLED_Clear();
//				if(sure!=0) {
//					return ;
//				}
//  OLED_Clear();
//	while(FMP383C_SLEEP==0)
//  {//ָ��˯�߻��޷���� ����Ҫ�ȱ�֤FPM���ڹ���״̬
//    OLED_ShowString(0,2,"FPM In sleep",16);
//    OLED_ShowString(0,4,"Pleace awaken ",16);
//	}
//	
//    OLED_Clear();
//    OLED_ShowChar(0,0,'=',16);
//    OLED_ShowString(36,0,"WARNING",16);
//    OLED_ShowChar(118,0,'=',16);
//    OLED_ShowString(0,2,"Clean FRLib ",16);
//    OLED_ShowString(0,4,"Pleace Press CE ",16);
//    OLED_ShowString(0,6,"Click 10",16);
//    OLED_ShowChar(74,6,'>',16);
//    OLED_ShowNum(104,6,0,2,16);
//    while(temp<=9) { //�жϵ������
//        if(KEY_Mode()==KEY1_PRES_CE) {
//            temp++;
//        }
//        else if(KEY_Mode()==KEY4_PRES_CL) {
//            return;
//        }
//        OLED_ShowNum(104,6,temp,2,16);
//    }
//    FPM383C_CL();
//    delay_ms(500);
//    sure=Receive_Check();

//    if(sure == 0x00)
//    {
//        OLED_Clear();
//        OLED_ShowString(36,2,"SUCCESS",16);
//        delay_ms(1000);
//    }
//    else
//    {
//        OLED_Clear();
//        OLED_ShowErrMessage(sure);
//        delay_ms(1000);
//    }

//}
///**
//  * @brief  ��������ģ����
//  * @param  ��
//  * @retval 0 �������  1��������
//  */
//u8 Password_Check(u8 *CKP)
//{
//    u8 i=0;
//    while(i<=5) {
//        if(REpassword[i]!=CKP[i])	{
//            warning+=5;//���벻һ�� 5������
//            return 0;//���벻һ��
//        }
//        i++;
//    }
//    return 1;
//    //����һ��
//}







