#ifndef __BSP_AS608_H_
#define	__BSP_AS608_H_


#define UART_QUEUE_22BIT 	22				//串口接收数据所需位数
#define UART_QUEUE_24BIT		24
#define UART_QUEUE_26BIT		26
#define UART_QUEUE_28BIT		28

extern u8 QUEUE_BIT;   //检测位数


extern uint64_t FPM383C_HEAR;

extern	u8 TC_Tik ;
extern	u8  FingerFalge;
extern uint16_t  FalgeNums ;      //指纹数

void  OLED_ShowErrMessage(uint16_t  ensure);
void FPM383C_SendData(uint8_t data);
void FPM383C_FrameHead(void);
void FPM383C_DataLenth(uint16_t len);
void FPM383C_Command(uint16_t com);
void FPM383C_ParamSet(uint32_t pa,uint8_t num);
void FPM383C_LasetCheck(uint8_t data);
void FPM383C_LED(uint8_t mod,uint8_t col,uint8_t pr1,uint8_t pr2,uint8_t pr3);
void FPM383C_Heart(void);
uint16_t Receive_Check(void);
void	FPM383C_CL(void);
void FPM383C_Matching(void);
void FPM383C_AutoREG(uint8_t mod,uint8_t x);
uint16_t Finger_Check(uint16_t* ID,uint16_t* RS);
u8 FPM383C_NumFinger(void);
void FPM383C_Sleep(void);
uint16_t Receive_REGCheck(uint16_t* percentage);
#endif



