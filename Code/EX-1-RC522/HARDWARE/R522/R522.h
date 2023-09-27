#ifndef __R522_H
#define __R522_H
#include "main.h"

//MF522�������
#define PCD_IDLE              0x00               //ȡ����ǰ����
#define PCD_AUTHENT           0x0E               //��֤��Կ
#define PCD_RECEIVE           0x08               //��������
#define PCD_TRANSMIT          0x04               //��������
#define PCD_TRANSCEIVE        0x0C               //���Ͳ���������
#define PCD_RESETPHASE        0x0F               //��λ
#define PCD_CALCCRC           0x03               //CRC����

//Mifare_One��Ƭ�������
#define PICC_REQIDL           0x26               //Ѱ��������δ��������״̬
#define PICC_REQALL           0x52               //Ѱ��������ȫ����
#define PICC_ANTICOLL1        0x93               //����ײ
#define PICC_ANTICOLL2        0x95               //����ײ
#define PICC_AUTHENT1A        0x60               //��֤A��Կ
#define PICC_AUTHENT1B        0x61               //��֤B��Կ
#define PICC_READ             0x30               //����
#define PICC_WRITE            0xA0               //д��
#define PICC_DECREMENT        0xC0               //�ۿ�
#define PICC_INCREMENT        0xC1               //��ֵ
#define PICC_RESTORE          0xC2               //�������ݵ�������
#define PICC_TRANSFER         0xB0               //���滺����������
#define PICC_HALT             0x50               //����

#define DEF_FIFO_LENGTH       64                 //FIFO size=64byte
#define MAXRLEN  18

//MF522�Ĵ�������

// PAGE 0
#define     RFU00                 0x00    
#define     CommandReg            0x01    
#define     ComIEnReg             0x02    
#define     DivlEnReg             0x03    
#define     ComIrqReg             0x04    
#define     DivIrqReg             0x05
#define     ErrorReg              0x06    
#define     Status1Reg            0x07    
#define     Status2Reg            0x08    
#define     FIFODataReg           0x09
#define     FIFOLevelReg          0x0A
#define     WaterLevelReg         0x0B
#define     ControlReg            0x0C
#define     BitFramingReg         0x0D
#define     CollReg               0x0E
#define     RFU0F                 0x0F
// PAGE 1     
#define     RFU10                 0x10
#define     ModeReg               0x11
#define     TxModeReg             0x12
#define     RxModeReg             0x13
#define     TxControlReg          0x14
#define     TxAutoReg             0x15
#define     TxSelReg              0x16
#define     RxSelReg              0x17
#define     RxThresholdReg        0x18
#define     DemodReg              0x19
#define     RFU1A                 0x1A
#define     RFU1B                 0x1B
#define     MifareReg             0x1C
#define     RFU1D                 0x1D
#define     RFU1E                 0x1E
#define     SerialSpeedReg        0x1F
// PAGE 2    
#define     RFU20                 0x20  
#define     CRCResultRegM         0x21
#define     CRCResultRegL         0x22
#define     RFU23                 0x23
#define     ModWidthReg           0x24
#define     RFU25                 0x25
#define     RFCfgReg              0x26
#define     GsNReg                0x27
#define     CWGsCfgReg            0x28
#define     ModGsCfgReg           0x29
#define     TModeReg              0x2A
#define     TPrescalerReg         0x2B
#define     TReloadRegH           0x2C
#define     TReloadRegL           0x2D
#define     TCounterValueRegH     0x2E
#define     TCounterValueRegL     0x2F
// PAGE 3      
#define     RFU30                 0x30
#define     TestSel1Reg           0x31
#define     TestSel2Reg           0x32
#define     TestPinEnReg          0x33
#define     TestPinValueReg       0x34
#define     TestBusReg            0x35
#define     AutoTestReg           0x36
#define     VersionReg            0x37
#define     AnalogTestReg         0x38
#define     TestDAC1Reg           0x39  
#define     TestDAC2Reg           0x3A   
#define     TestADCReg            0x3B   
#define     RFU3C                 0x3C   
#define     RFU3D                 0x3D   
#define     RFU3E                 0x3E   
#define     RFU3F		  		  0x3F

//��RC522ͨѶʱ���ص�M1��״̬
#define 	MI_OK                 0x26
#define 	MI_NOTAGERR           0xcc
#define 	MI_ERR                0xbb

//��MF522ͨѶʱ���صĴ������
#define	    SHAQU1                0X01
#define  	KUAI4	              0X04
#define 	KUAI7	              0X07
#define	    REGCARD	              0xa1
#define 	CONSUME	              0xa2
#define     READCARD	          0xa3
#define     ADDMONEY	          0xa4

//����0x00��ȡ����
#define SPI_RC522_ReadByte()	      SPI_RC522_SendByte(0xFF) 

#define          RC522_CS_Enable()         HAL_GPIO_WritePin( R522_NSS_GPIO_Port, R522_NSS_Pin,GPIO_PIN_RESET)//Ƭѡ
#define          RC522_CS_Disable()        HAL_GPIO_WritePin   ( R522_NSS_GPIO_Port, R522_NSS_Pin ,GPIO_PIN_SET)

#define          RC522_Reset_Enable()      HAL_GPIO_WritePin( R522_RES_GPIO_Port, R522_RES_Pin ,GPIO_PIN_RESET)//��λRST
#define          RC522_Reset_Disable()     HAL_GPIO_WritePin  ( R522_RES_GPIO_Port, R522_RES_Pin ,GPIO_PIN_SET)

uint8_t SPI_RC522_SendByte(uint8_t byte);
char RC522_Read_ID_Once(char *cardID);
uint8_t ReadRawRC(uint8_t ucAddress);
void WriteRawRC( uint8_t ucAddress,uint8_t ucValue);
void RC522_GPIO_Init(void);
void RC522_Handel(void);
void RC522_Init(void);                       //��ʼ��
void PcdReset(void);                       //��λ
void M500PcdConfigISOType(void);                    //������ʽ
char PcdRequest(uint8_t req_code,uint8_t * pTagType); //Ѱ��
char PcdAnticoll(uint8_t * pSnr);                   //����ײ

void PcdAntennaOn(void);                 //��������
void PcdAntennaOff(void);                 //�ر�����
void SetBitMask(uint8_t ucReg,uint8_t ucMask);
void ClearBitMask( uint8_t ucReg,uint8_t ucMask);
char PcdSelect(uint8_t * pSnr );            //ѡ��Ƭ
char PcdAuthState(uint8_t ucAuth_mode,uint8_t ucAddr,uint8_t * pKey,uint8_t * pSnr);                                              //��֤����
char PcdWrite(uint8_t ucAddr,uint8_t * pData);
char PcdRead(uint8_t ucAddr,uint8_t * pData);
void ShowID(uint16_t x,uint16_t y,uint8_t *p,uint16_t charColor,uint16_t bkColor);	 //��ʾ���Ŀ��ţ���ʮ��������ʾ
char PcdHalt(void);           //���Ƭ��������״̬
void CalulateCRC(uint8_t * pIndata,uint8_t ucLen,uint8_t * pOutData);
#endif
