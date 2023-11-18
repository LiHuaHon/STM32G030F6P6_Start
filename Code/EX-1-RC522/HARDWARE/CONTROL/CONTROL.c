#include ".\HARDWARE\CONTROL\CONTROL.h"
void Control_DelOneUser(void);
void Control_DelUser(void);

void Control_AddOneUser(void);

void Control_Menu(void){
  PcdAntennaOff();              //关闭天线
	CM:
	 switch(My_getchar()){
        case '1':
						
						printf("\n\r当前存在用户:%d 最大用户数量%d\n\r",User_GetUserNum(),MAX_USER);
						User_List_All(MODLE_ID_AND_NAME);
						printf("\n\r以上是已保存用户 \n\r");
            break;
				
        case '2':
						Control_DelOneUser();
            break;
				
//        case '3':
////						Control_DelUser();//别用这个了 BUG一堆
//            break;
				
        case '4':
						Control_AddOneUser();
            break;
				
        case 'D'://覆盖所有数据并重启
						printf("\n\r进入重置模式\n\r");
						if(My_getchar()=='Y'){
							printf("\n\r已执行\n\r");
							Control_ClearAT24CXX();
							HAL_Delay(1000);
							HAL_NVIC_SystemReset();
						}else
							printf("\n\r已退出\n\r");
            break;
				
        case '6':
            break;
				
        case '7':
            break;
				
        case '8':
            printf("\r\n正在保存并重启\r\n");
						Control_SaveUserToAT24CXX();
						HAL_Delay(1000);
						HAL_NVIC_SystemReset();
            break;
				
        default:
            printf("\r\n输入错误请重试\r\n");
    }
		goto CM;
}

void Control_DelOneUser(void){
		char entStr[20]={0};
		printf("\r\n请输入要删除的用户序号\r\n");
		My_getstring(entStr);
		
		if(str_to_u8(entStr)==0){
			printf("\n\r不能删除Adimin 已返回上一步\r\n\n\r");
		}
		
		if(User_Delete(str_to_u8(entStr))==CODE_USER_NE){
			printf("\r\n不存在:%s 已返回上一步\r\n",entStr);
		}else{
			printf("\r\n成功删除:%s 已返回上一步\r\n",entStr);
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
    printf("\r\n请输入要删除的用户序号用空格隔开\r\n如1 21 35删除当前序号1 21 35的用户\r\n");
		My_getstring(entStr);
    for(i=0;i<180;i++){//在这个循环中寻找单独字符串
			if(entStr[i]!=' '&&dataFlage==0){//寻找开始位
					dataFlage=1;
					dataStart=i;//标记数据起始位
			}else if((entStr[i]==' '||entStr[i]==0)&&dataFlage==1){
					dataFlage=(entStr[i]==0)?3:2;
					dataEnd=i;//标记数据结束位
			}
			if(dataFlage>=2){
				get_data_str(entStr,dataStart,dataEnd,tempStr);
				temp_u8=str_to_u8(tempStr);
				if(temp_u8>0 && temp_u8<=MAX_USER){ // 检查序号是否是有效的数字
						StempUser[k++]=temp_u8;
				}else if(temp_u8>MAX_USER){
						sprintf(EtempUser[j++],"%s",tempStr);
				}
				dataFlage=(dataFlage==3)?3:0;//完成一次数据转移
			}
			if(dataFlage==3){
				break;
			}
		}
		temp_u8=User_GetUserNum();
		for(i=0; i<k; i++){
			returnCode=User_Delete(StempUser[i]);
			if(returnCode==CODE_USER_OK){
				printf("删除序号:%d 成功 已删除:%s\n\r",StempUser[i],User[StempUser[i]].userCN_name);
			}else {
				printf("删除序号:%d 失败\n\r",StempUser[i]);
			}
		}
		User_ResetList();
		printf("返回上一步\n\r\n\r\n\r\n\r\n\r");

}
void Control_AddOneUser(void){
		char cid[20]={0};
		char entStr[20]={0};
    printf("\r\n请稍等\r\n");
    PcdAntennaOff();              //关闭天线
    HAL_Delay(1);
    PcdAntennaOn();               //打开天线
    printf("\r\n请放置卡至模块上");
		while(1)
		if(RC522_Read_ID_Once(cid)==MI_OK){
			printf ("\r\n读取到的卡ID为:%02X%02X%02X%02X\r\n", cid [ 0 ], cid [ 1 ], cid [ 2 ], cid [ 3 ] );
			break;
		}	
    printf("\r\n请输入用户名(不超过4个字)\r\n");
		My_getstring(entStr);
		if(User_UserCreate(u8_Tun_u32((uint8_t*)cid),entStr)==CODE_USER_OK)
		{
			printf("\r\n成功 返回上一步\r\n");
		}else{
			printf("\r\n创建失败 用户可能已存在 返回上一步\r\n");
		}
}

void Control_ClearAllUser(void){
    printf("\r\n请注意\r\n");
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
	uint8_t userNum=User_GetUserNum();//获取当前用户数
	printf("擦除用户数%d\r\n",userNum);
	
	for(i=0;i<userNum;i++){
		printf("进度%.1f\r\n",((float)i/userNum)*100);
		AT24CXX_WriteOneByte(i,0xFF);
	}
	printf("手动擦除完成\r\n");
	AT24CXX_WriteOneByte(0,userNum);//存入用户数
	
	for(i=0;i<userNum;i++){
		num=0;//校验重新计数
		for(inC=0;inC<(USER_ID_LENTH);inC++){//存入用户卡号
			tempData=User[i].userId[inC];
			num+=tempData;
			AT24CXX_WriteOneByte(1+i*13+inC,tempData);//1校验和/或者一开始的用户数的地址开始存起
		}
		
		for(inC=0;inC<(USER_ID_NAME);inC++){//存入用户名
			tempData=User[i].userCN_name[inC];
			num+=tempData;
			AT24CXX_WriteOneByte(1+i*13+USER_ID_LENTH+inC,tempData);
		}
		AT24CXX_WriteOneByte(1+i*13+USER_ID_LENTH+USER_ID_NAME,num);//写入校验和
	}
	printf("用户已保存\r\n");
//	Printf_AT24CXX(0X00,1+userNum*13);
	
}
//函数简解 Control_ReadUserFormAT24CXX
//返回值 读取at24cxx地址0的一个字节的数据
//情况1:0XFF->新AT24CXX芯片 
//情况2: 返回值0X01 新系统 (用户只有管理员)
//情况3: 返回值大于0X01 返回存储的用户数(含管理员) 
//情况4: 返回值等于0X00 这种情况是不被允许的 因为进入系统设置页面必须要有管理员 
//当返回值的情况为 情况1和情况4时 代码会将存储与系统内的Admin[MAX_ADMIN]组的第0号管理员其信息复制至 User[MAX_USER] 的0号用户中 充当用户管理员
uint8_t Control_ReadUserFormAT24CXX(void){
	uint8_t tempID[USER_ID_LENTH];
	uint8_t tempName[USER_ID_NAME];
	uint8_t num;
	uint8_t tempData;
	uint16_t j,inC=0;	
	int16_t i=0;
	uint8_t userNum=AT24CXX_ReadOneByte(0);//获取当前用户数
	
//	Printf_AT24CXX(0X00,1+userNum*13);
	
	if(userNum==0xff||userNum==0x00){//异常处理
//		printf("异常状态=%d\r\n",userNum);
		User_DataInit();
		AT24CXX_WriteOneByte(0,User_GetUserNum());//写入当前用户数
		Control_SaveUserToAT24CXX();//存入用户
	}else{
			for(i=0;i<userNum;i++){
				num=0;//校验重新计数
				for(inC=0;inC<(USER_ID_LENTH);inC++){//读取用户卡号
					tempID[inC]=AT24CXX_ReadOneByte(1+i*13+inC);
					tempData=tempID[inC];
					num+=tempData;
				}
				for(inC=0;inC<(USER_ID_NAME);inC++){//读取用户名
					tempName[inC]=AT24CXX_ReadOneByte(1+i*13+inC+USER_ID_LENTH);
					tempData=tempName[inC];
					num+=tempData;
				}
				if(num==AT24CXX_ReadOneByte(1+i*13+USER_ID_LENTH+USER_ID_NAME)){//判断校验和
						for(j=0;j<(USER_ID_LENTH);j++){//读入用户
							User[i].userId[j]=tempID[j];
						}
						for(j=0;j<(USER_ID_NAME);j++){
							User[i].userCN_name[j]=tempName[j];
						}
//					printf("读取到用户ID=%8X NAME=%s\r\n",u8_Tun_u32(tempID),tempName);
				}else{
//					printf("错误数据在%2X~%2X之间\r\n",1+i*13+inC,1+i*13+USER_ID_LENTH+USER_ID_NAME);
				}
			}
	}
	return userNum;
//	AT24CXX_WriteOneByte(0,User_GetUserNum());//写入当前用户数
//	for(i=0;i<userNum;i++){
//		printf("进度%.1f\r\n",((float)i/userNum)*100);
//		AT24CXX_WriteOneByte(i,0xFF);
//	}
//	printf("手动擦除完成\r\n");
//	AT24CXX_WriteOneByte(0,userNum);//存入用户数
//	
//	for(i=0;i<userNum;i++){
//		num=0;//校验重新计数
//		for(inC=0;inC<(USER_ID_LENTH);inC++){//存入用户卡号
//			tempData=User[i].userId[inC];
//			num+=tempData;
//			AT24CXX_WriteOneByte(1+i*13+inC,tempData);//1校验和/或者一开始的用户数的地址开始存起
//		}
//		
//		for(inC=0;inC<(USER_ID_NAME);inC++){//存入用户名
//			tempData=User[i].userCN_name[inC];
//			num+=tempData;
//			AT24CXX_WriteOneByte(1+i*13+USER_ID_LENTH+inC,tempData);
//		}
//		AT24CXX_WriteOneByte(1+i*13+USER_ID_LENTH+USER_ID_NAME,num);//写入校验和
//	}
}
void Control_ClearAT24CXX(void){
	uint16_t i;
	printf("\r\n删除地址%d 删除完毕会自动重启 请稍后\r\n",MAX_USER*15);
	for(i=0;i<MAX_USER*15;i++){
		AT24CXX_WriteOneByte(i,0XFF);
	}
	Printf_AT24CXX(0X00,MAX_USER*15);
	
}












