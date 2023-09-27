#ifndef __USERSAVE_H
#define __USERSAVE_H
#include "main.h"

#define MAX_USER 50
#define MAX_ADMIN 2
#define USER_ID_LENTH 4
#define USER_ID_NAME 8

#define MODLE_ONLY_ID 0X01
#define MODLE_ONLY_NAME 0X02
#define MODLE_ID_AND_NAME 0X03

#define CODE_USER_OK 0X00
#define CODE_USER_ER 0X01 //错误
#define CODE_USER_NE 0X02 //not exist用户不存在
#define CODE_USER_AS 0X03 //are save用户存在
#define CODE_USER_CE 0X04 //中文名字错误
//typedef unsigned char uint8_t;
//typedef unsigned int uint16_t;
//typedef unsigned int uint32_t;
typedef struct
{
    uint8_t userId[USER_ID_LENTH];
    char userCN_name[USER_ID_NAME];
}UserData;

extern UserData Admin[MAX_ADMIN];
extern UserData User[MAX_USER];
extern UserData TempUser[MAX_USER];
uint8_t User_UserCreate(uint32_t userID,char* userName);//创建用户

void User_DataInit(void);
void User_List_All(uint8_t listMode);
//uint8_t User_DELuserID(uint32_t targetID,uint8_t userNum);
void User_CreateAdmin(uint8_t admin, uint32_t adminID);
uint8_t User_CreateTempUser(uint8_t user, uint32_t userID,char* userName);
uint8_t User_Find(uint32_t userID);
void User_ResetList(void);//重置列表 清除空用户
uint8_t User_Delete(uint8_t user);
uint8_t User_GetUserNum(void);
uint32_t u8_Tun_u32(const uint8_t* u8data);
void u32_Tun_u8(uint8_t* u8data,uint32_t u32data);
uint8_t str_to_u8(char *str);//数字字符串转化为无符号字符行
#endif 


