#include ".\HARDWARE\USERSAVE\USERSAVE.h"
UserData Admin[MAX_ADMIN];
UserData User[MAX_USER];
void User_DataInit(void){
		uint16_t i;
    for (i = 0; i < MAX_USER; i++) {
        u32_Tun_u8(User[i].userId,0x00000000);
    }
		User_UserCreate(u8_Tun_u32(Admin[0].userId),"Admin");
}
void User_CreateAdmin(uint8_t admin, uint32_t adminID){
    Admin[admin].userId[0]= (adminID >> 24) & 0xFF;
    Admin[admin].userId[1]= (adminID >> 16) & 0xFF;
    Admin[admin].userId[2]= (adminID >> 8) & 0xFF;
    Admin[admin].userId[3]= (adminID >> 0) & 0xFF;
}
//�벻Ҫ��������û���������  User_UserCreate
uint8_t User_UserCreate(uint32_t userID,char* userName){

		uint8_t userNum;
		userNum=User_GetUserNum();
		return User_CreateTempUser(userNum,userID,userName);
}
uint8_t User_CreateTempUser(uint8_t userNum, uint32_t userID,char* userName){
    uint8_t returnCode=CODE_USER_OK;
    returnCode=User_Find(userID);//�����Ƿ��ظ� ���ҵ����û�ID �������û����uint8_t user
    if(returnCode!=CODE_USER_OK){
        return returnCode;//����ظ�
    }else if(strlen(userName)>8){
				returnCode=CODE_USER_CE;
        return returnCode;//����4���� 1������2���ֽ�
		};
    User[userNum].userId[0]= (userID >> 24) & 0xFF;
    User[userNum].userId[1]= (userID >> 16) & 0xFF;
    User[userNum].userId[2]= (userID >> 8) & 0xFF;
    User[userNum].userId[3]= (userID >> 0) & 0xFF;
    sprintf(User[userNum].userCN_name,"%s", userName);
    return returnCode;
}
uint32_t u8_Tun_u32(const uint8_t* u8data){
    uint32_t returnValue = 0;
    returnValue+=u8data[0]<<24;
    returnValue+=u8data[1]<<16;
    returnValue+=u8data[2]<<8;
    returnValue+=u8data[3]<<0;
    return returnValue;
}
void u32_Tun_u8(uint8_t* u8data,uint32_t u32data){
    u8data[0]=(u32data>>24)&0xFF;
    u8data[1]=(u32data>>16)&0xFF;
    u8data[2]=(u32data>>8)&0xFF;
    u8data[3]=(u32data>>0)&0xFF;
}
uint8_t User_Find(uint32_t userID){
    uint8_t i;
    uint8_t returnCode=CODE_USER_OK;
    for (i = 0; i < MAX_USER; ++i) {
        if(u8_Tun_u32 (User[i].userId)==userID){
          returnCode=CODE_USER_AS;
          break;
        }
    }
    return returnCode;
}
//listModeΪ��ʾ��ʽ
void User_List_All(uint8_t listMode){
    uint8_t i;
    uint32_t data;
    char str[12];
    for (i = 0; i < MAX_USER; ++i) {
        data=u8_Tun_u32 (User[i].userId);
        if(data==0X00){
            break;
        }else
        if(listMode==MODLE_ONLY_ID){
            printf("\n\rUSER:%d ID:%08X\n\r",i,data);
        }else if(listMode==MODLE_ONLY_NAME){
            printf("%s",User[i].userCN_name);
        }else if(listMode==MODLE_ID_AND_NAME){
					strcpy(str,User[i].userCN_name);
					printf("���:%d �û�ID:%08X �û���:%s\n\r",i,data,User[i].userCN_name);
        }
    }
}
uint8_t User_Delete(uint8_t user){//userΪĿǰ�����
    uint8_t returnCode=CODE_USER_OK;
    if(u8_Tun_u32(User[user].userId)==0X00){
        returnCode=CODE_USER_NE;//�û�������
        return returnCode;
    }
    User[user].userId[0]=0X00;
    User[user].userId[1]=0X00;
    User[user].userId[2]=0X00;
    User[user].userId[3]=0X00;
		User_ResetList();
		return returnCode;

}

//�����û��� ����һ���ж����û�
uint8_t User_GetUserNum(void){
	uint8_t i;
	User_ResetList();
	for (i = 0; i < MAX_USER; ++i) {
        if(u8_Tun_u32 (User[i].userId)==0x00){
					return i;
        }
    }
	return 0;
}
void User_ResetList(void){//���������û��б� ȥ���м��USER X:00000000
    uint8_t i=0,j=0;
    uint32_t temp1_u32[MAX_USER]={0};
    for (i = 0; i < MAX_USER; i++) {
        temp1_u32[i]=u8_Tun_u32(User[i].userId);
    }
//    ת��Ϊ32������洢 ֱ�ӱȽ������Ƿ�Ϊ0
    for (i = 0; i < MAX_USER; i++) {
        if (temp1_u32[i]==0X00) {//�ҵ��հ�ID
            for (j = i + 1; j < MAX_USER; j++) {
                if (temp1_u32[j]!=0X00) {
									
										sprintf(User[i].userCN_name,"%s",User[j].userCN_name);//�滻������
                    temp1_u32[i]=temp1_u32[j];
                    temp1_u32[j]=0;
                    break;
                }
            }
        }
    }
    for (i = 0; i < MAX_USER; i++) {
        u32_Tun_u8(User[i].userId,temp1_u32[i]);
    }
}
//�����ַ���ת��Ϊ�޷����ַ���
uint8_t str_to_u8(char *str){
    uint8_t i;
    uint8_t returnNum=0;
    for (i = 0; i < MAX_USER; ++i) {
        if(*str==0){
            break;
        }
        if(i>0){
            returnNum*=10;
        }
        if(*str>='0' && *str<='9'&&*str!=' '){
            returnNum+=(*str++-'0');
        }
        else return MAX_USER+1;//����������������
    }
    return returnNum;
}






