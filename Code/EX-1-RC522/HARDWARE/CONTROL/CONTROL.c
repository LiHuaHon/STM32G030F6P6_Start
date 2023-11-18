#include ".\HARDWARE\CONTROL\CONTROL.h"
void Control_DelOneUser(void);
void Control_DelUser(void);

void Control_AddOneUser(void);

void Control_Menu(void){
  PcdAntennaOff();              //�ر�����
	CM:
	 switch(My_getchar()){
        case '1':
						
						printf("\n\r��ǰ�����û�:%d ����û�����%d\n\r",User_GetUserNum(),MAX_USER);
						User_List_All(MODLE_ID_AND_NAME);
						printf("\n\r�������ѱ����û� \n\r");
            break;
				
        case '2':
						Control_DelOneUser();
            break;
				
//        case '3':
////						Control_DelUser();//��������� BUGһ��
//            break;
				
        case '4':
						Control_AddOneUser();
            break;
				
        case 'D'://�����������ݲ�����
						printf("\n\r��������ģʽ\n\r");
						if(My_getchar()=='Y'){
							printf("\n\r��ִ��\n\r");
							Control_ClearAT24CXX();
							HAL_Delay(1000);
							HAL_NVIC_SystemReset();
						}else
							printf("\n\r���˳�\n\r");
            break;
				
        case '6':
            break;
				
        case '7':
            break;
				
        case '8':
            printf("\r\n���ڱ��沢����\r\n");
						Control_SaveUserToAT24CXX();
						HAL_Delay(1000);
						HAL_NVIC_SystemReset();
            break;
				
        default:
            printf("\r\n�������������\r\n");
    }
		goto CM;
}

void Control_DelOneUser(void){
		char entStr[20]={0};
		printf("\r\n������Ҫɾ�����û����\r\n");
		My_getstring(entStr);
		
		if(str_to_u8(entStr)==0){
			printf("\n\r����ɾ��Adimin �ѷ�����һ��\r\n\n\r");
		}
		
		if(User_Delete(str_to_u8(entStr))==CODE_USER_NE){
			printf("\r\n������:%s �ѷ�����һ��\r\n",entStr);
		}else{
			printf("\r\n�ɹ�ɾ��:%s �ѷ�����һ��\r\n",entStr);
		}
		User_ResetList();
}

void Control_DelUser(void){
	
		char entStr[180]={0};
    char tempStr[30]={0};
    uint8_t temp_u8=0,returnCode;
    uint8_t StempUser[MAX_USER];
    char EtempUser[MAX_USER][20];
		
    uint16_t i, j=0, k=0,dataStart=0,dataEnd=0,dataFlage=0;
    printf("\r\n������Ҫɾ�����û�����ÿո����\r\n��1 21 35ɾ����ǰ���1 21 35���û�\r\n");
		My_getstring(entStr);
    for(i=0;i<180;i++){//�����ѭ����Ѱ�ҵ����ַ���
			if(entStr[i]!=' '&&dataFlage==0){//Ѱ�ҿ�ʼλ
					dataFlage=1;
					dataStart=i;//���������ʼλ
			}else if((entStr[i]==' '||entStr[i]==0)&&dataFlage==1){
					dataFlage=(entStr[i]==0)?3:2;
					dataEnd=i;//������ݽ���λ
			}
			if(dataFlage>=2){
				get_data_str(entStr,dataStart,dataEnd,tempStr);
				temp_u8=str_to_u8(tempStr);
				if(temp_u8>0 && temp_u8<=MAX_USER){ // �������Ƿ�����Ч������
						StempUser[k++]=temp_u8;
				}else if(temp_u8>MAX_USER){
						sprintf(EtempUser[j++],"%s",tempStr);
				}
				dataFlage=(dataFlage==3)?3:0;//���һ������ת��
			}
			if(dataFlage==3){
				break;
			}
		}
		temp_u8=User_GetUserNum();
		for(i=0; i<k; i++){
			returnCode=User_Delete(StempUser[i]);
			if(returnCode==CODE_USER_OK){
				printf("ɾ�����:%d �ɹ� ��ɾ��:%s\n\r",StempUser[i],User[StempUser[i]].userCN_name);
			}else {
				printf("ɾ�����:%d ʧ��\n\r",StempUser[i]);
			}
		}
		User_ResetList();
		printf("������һ��\n\r\n\r\n\r\n\r\n\r");

}
void Control_AddOneUser(void){
		char cid[20]={0};
		char entStr[20]={0};
    printf("\r\n���Ե�\r\n");
    PcdAntennaOff();              //�ر�����
    HAL_Delay(1);
    PcdAntennaOn();               //������
    printf("\r\n����ÿ���ģ����");
		while(1)
		if(RC522_Read_ID_Once(cid)==MI_OK){
			printf ("\r\n��ȡ���Ŀ�IDΪ:%02X%02X%02X%02X\r\n", cid [ 0 ], cid [ 1 ], cid [ 2 ], cid [ 3 ] );
			break;
		}	
    printf("\r\n�������û���(������4����)\r\n");
		My_getstring(entStr);
		if(User_UserCreate(u8_Tun_u32((uint8_t*)cid),entStr)==CODE_USER_OK)
		{
			printf("\r\n�ɹ� ������һ��\r\n");
		}else{
			printf("\r\n����ʧ�� �û������Ѵ��� ������һ��\r\n");
		}
}

void Control_ClearAllUser(void){
    printf("\r\n��ע��\r\n");
}
void Printf_AT24CXX(uint16_t StartAdder,uint16_t ReadLenth){
	
	uint16_t i;
	
	printf("\r\n<<DEBUG-AT24CXX-PRINT Adder=%d Lenth=%d>>",StartAdder,ReadLenth);
	for(i=0;i<ReadLenth;i++){
		printf("\r\nADDER=%d \t%2X ",StartAdder+i,AT24CXX_ReadOneByte(StartAdder+i));
	}
	printf("\r\n<<DEBUG-AT24CXX-PRINT END>>\r\n");
}

void Control_SaveUserToAT24CXX(void){
	uint8_t num;
	uint8_t tempData;
	uint16_t i=0,inC=0;	
	uint8_t userNum=User_GetUserNum();//��ȡ��ǰ�û���
	printf("�����û���%d\r\n",userNum);
	
	for(i=0;i<userNum;i++){
		printf("����%.1f\r\n",((float)i/userNum)*100);
		AT24CXX_WriteOneByte(i,0xFF);
	}
	printf("�ֶ��������\r\n");
	AT24CXX_WriteOneByte(0,userNum);//�����û���
	
	for(i=0;i<userNum;i++){
		num=0;//У�����¼���
		for(inC=0;inC<(USER_ID_LENTH);inC++){//�����û�����
			tempData=User[i].userId[inC];
			num+=tempData;
			AT24CXX_WriteOneByte(1+i*13+inC,tempData);//1У���/����һ��ʼ���û����ĵ�ַ��ʼ����
		}
		
		for(inC=0;inC<(USER_ID_NAME);inC++){//�����û���
			tempData=User[i].userCN_name[inC];
			num+=tempData;
			AT24CXX_WriteOneByte(1+i*13+USER_ID_LENTH+inC,tempData);
		}
		AT24CXX_WriteOneByte(1+i*13+USER_ID_LENTH+USER_ID_NAME,num);//д��У���
	}
	printf("�û��ѱ���\r\n");
//	Printf_AT24CXX(0X00,1+userNum*13);
	
}
//������� Control_ReadUserFormAT24CXX
//����ֵ ��ȡat24cxx��ַ0��һ���ֽڵ�����
//���1:0XFF->��AT24CXXоƬ 
//���2: ����ֵ0X01 ��ϵͳ (�û�ֻ�й���Ա)
//���3: ����ֵ����0X01 ���ش洢���û���(������Ա) 
//���4: ����ֵ����0X00 ��������ǲ�������� ��Ϊ����ϵͳ����ҳ�����Ҫ�й���Ա 
//������ֵ�����Ϊ ���1�����4ʱ ����Ὣ�洢��ϵͳ�ڵ�Admin[MAX_ADMIN]��ĵ�0�Ź���Ա����Ϣ������ User[MAX_USER] ��0���û��� �䵱�û�����Ա
uint8_t Control_ReadUserFormAT24CXX(void){
	uint8_t tempID[USER_ID_LENTH];
	uint8_t tempName[USER_ID_NAME];
	uint8_t num;
	uint8_t tempData;
	uint16_t j,inC=0;	
	int16_t i=0;
	uint8_t userNum=AT24CXX_ReadOneByte(0);//��ȡ��ǰ�û���
	
//	Printf_AT24CXX(0X00,1+userNum*13);
	
	if(userNum==0xff||userNum==0x00){//�쳣����
//		printf("�쳣״̬=%d\r\n",userNum);
		User_DataInit();
		AT24CXX_WriteOneByte(0,User_GetUserNum());//д�뵱ǰ�û���
		Control_SaveUserToAT24CXX();//�����û�
	}else{
			for(i=0;i<userNum;i++){
				num=0;//У�����¼���
				for(inC=0;inC<(USER_ID_LENTH);inC++){//��ȡ�û�����
					tempID[inC]=AT24CXX_ReadOneByte(1+i*13+inC);
					tempData=tempID[inC];
					num+=tempData;
				}
				for(inC=0;inC<(USER_ID_NAME);inC++){//��ȡ�û���
					tempName[inC]=AT24CXX_ReadOneByte(1+i*13+inC+USER_ID_LENTH);
					tempData=tempName[inC];
					num+=tempData;
				}
				if(num==AT24CXX_ReadOneByte(1+i*13+USER_ID_LENTH+USER_ID_NAME)){//�ж�У���
						for(j=0;j<(USER_ID_LENTH);j++){//�����û�
							User[i].userId[j]=tempID[j];
						}
						for(j=0;j<(USER_ID_NAME);j++){
							User[i].userCN_name[j]=tempName[j];
						}
//					printf("��ȡ���û�ID=%8X NAME=%s\r\n",u8_Tun_u32(tempID),tempName);
				}else{
//					printf("����������%2X~%2X֮��\r\n",1+i*13+inC,1+i*13+USER_ID_LENTH+USER_ID_NAME);
				}
			}
	}
	return userNum;
//	AT24CXX_WriteOneByte(0,User_GetUserNum());//д�뵱ǰ�û���
//	for(i=0;i<userNum;i++){
//		printf("����%.1f\r\n",((float)i/userNum)*100);
//		AT24CXX_WriteOneByte(i,0xFF);
//	}
//	printf("�ֶ��������\r\n");
//	AT24CXX_WriteOneByte(0,userNum);//�����û���
//	
//	for(i=0;i<userNum;i++){
//		num=0;//У�����¼���
//		for(inC=0;inC<(USER_ID_LENTH);inC++){//�����û�����
//			tempData=User[i].userId[inC];
//			num+=tempData;
//			AT24CXX_WriteOneByte(1+i*13+inC,tempData);//1У���/����һ��ʼ���û����ĵ�ַ��ʼ����
//		}
//		
//		for(inC=0;inC<(USER_ID_NAME);inC++){//�����û���
//			tempData=User[i].userCN_name[inC];
//			num+=tempData;
//			AT24CXX_WriteOneByte(1+i*13+USER_ID_LENTH+inC,tempData);
//		}
//		AT24CXX_WriteOneByte(1+i*13+USER_ID_LENTH+USER_ID_NAME,num);//д��У���
//	}
}
void Control_ClearAT24CXX(void){
	uint16_t i;
	printf("\r\nɾ����ַ%d ɾ����ϻ��Զ����� ���Ժ�\r\n",MAX_USER*15);
	for(i=0;i<MAX_USER*15;i++){
		AT24CXX_WriteOneByte(i,0XFF);
	}
	Printf_AT24CXX(0X00,MAX_USER*15);
	
}












