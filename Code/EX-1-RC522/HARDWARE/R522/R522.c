#include ".\HARDWARE\R522\R522.h"

char RC522_Read_ID_Once(char *cardID)
{
    uint8_t card_type[2];//卡片类型，2字节
    uint8_t card_ID[5];//卡序列号
    uint8_t statusRt;
    PcdAntennaOn();
    statusRt = PcdRequest(PICC_REQIDL, card_type);//寻未进入休眠的卡
    if(statusRt == MI_OK) { //寻卡成功
//        printf("寻卡成功\r\n");
        if( PcdAnticoll (card_ID) == MI_OK) { //防冲撞成功
             if(PcdSelect(card_ID) == MI_OK) {
//                printf("\r\n 选卡成功\r\n");
                if(PcdHalt() == MI_OK) {
//                printf("\r\n 读取成功\r\n");
 									sprintf ( cardID, "%c%c%c%c", card_ID [ 0 ], card_ID [ 1 ], card_ID [ 2 ], card_ID [ 3 ] );
									return  MI_OK;
                }
            }
        }
    }
		return  MI_ERR;
}
/* 函数名：RC522_Init
 * 描述  ：初始化RC522配置
 * 输入  ：无
 * 返回  : 无
 * 调用  ：外部调用              */
void RC522_Init ( void )
{
    __HAL_SPI_ENABLE(&hspi1);                    //使能SPI1
    RC522_Reset_Disable();	      //将RST置高，启动内部复位阶段；
    RC522_CS_Disable();
    PcdReset();                  //复位RC522

    PcdAntennaOff();              //关闭天线
    HAL_Delay(1);
    PcdAntennaOn();               //打开天线

    M500PcdConfigISOType (); //设置工作方式
}

/**
  * @Name    RC522_GPIO_Init
  * @brief   初始化RC522 GPIO引脚
  * @param   None
  * @retval
  * @author  NameisBoy
  * @Data    2020-09-04
 **/
//void RC522_GPIO_Init(void)
//{

//    GPIO_InitTypeDef GPIO_Initure;

//    __HAL_RCC_GPIOA_CLK_ENABLE();       //使能GPIOB时钟
//    __HAL_RCC_GPIOG_CLK_ENABLE();       //使能GPIOB时钟


//    GPIO_Initure.Pin=GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
//    GPIO_Initure.Mode=GPIO_MODE_AF_PP;              //复用推挽输出
//    GPIO_Initure.Pull=GPIO_PULLUP;                  //上拉
//    GPIO_Initure.Speed=GPIO_SPEED_FAST;             //快速
//    GPIO_Initure.Alternate=GPIO_AF5_SPI1;           //复用为SPI1
//    HAL_GPIO_Init(GPIOA,&GPIO_Initure);


//    GPIO_Initure.Pin=GPIO_PIN_6|GPIO_PIN_7;
//    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;              //片选NSS RES初始化
//    GPIO_Initure.Pull=GPIO_PULLUP;                  //上拉
//    GPIO_Initure.Speed=GPIO_SPEED_FAST;             //快速

//    HAL_GPIO_Init(GPIOG,&GPIO_Initure);

//}
/* 函数名：PcdRese
 * 描述  ：复位RC522
 * 输入  ：无
 * 返回  : 无
 * 调用  ：外部调用              */
void PcdReset ( void )
{
    RC522_Reset_Disable();
    HAL_Delay (10);
    RC522_Reset_Enable();
    HAL_Delay (10);
    RC522_Reset_Disable();
    WriteRawRC ( CommandReg, 0x0f );

    while ( ReadRawRC ( CommandReg ) & 0x10 );
    HAL_Delay ( 1 );
    WriteRawRC ( ModeReg, 0x3D );                //定义发送和接收常用模式 和Mifare卡通讯，CRC初始值0x6363
    WriteRawRC ( TReloadRegL, 30 );              //16位定时器低位
    WriteRawRC ( TReloadRegH, 0 );			     //16位定时器高位
    WriteRawRC ( TModeReg, 0x8D );				 //定义内部定时器的设置
    WriteRawRC ( TPrescalerReg, 0x3E );			 //设置定时器分频系数
    WriteRawRC ( TxAutoReg, 0x40 );				 //调制发送信号为100%ASK
}

/* 函数名：SPI_RC522_SendByte
 * 描述  ：向RC522发送1 Byte 数据
 * 输入  ：TxData
，要发送的数据
 * 返回  : RC522返回的数据
 * 调用  ：内部调用                 */
uint8_t SPI_RC522_SendByte ( uint8_t TxData )
{
    uint8_t Rxdata=0;
    HAL_SPI_TransmitReceive(&hspi1,&TxData,&Rxdata,1, 1000);
    return Rxdata;
}


/* 函数名：ReadRawRC
 * 描述  ：读RC522寄存器
 * 输入  ：ucAddress，寄存器地址
 * 返回  : 寄存器的当前值
 * 调用  ：内部调用                 */
uint8_t ReadRawRC ( uint8_t ucAddress )
{
    uint8_t ucAddr, ucReturn;
    ucAddr = ( ( ucAddress << 1 ) & 0x7E ) | 0x80;

    RC522_CS_Enable();
    SPI_RC522_SendByte ( ucAddr );
    ucReturn = SPI_RC522_ReadByte ();
    RC522_CS_Disable();
    return ucReturn;
}


/* 函数名：WriteRawRC
* 描述  ：写RC522寄存器
* 输入  ：ucAddress，寄存器地址  、 ucValue，写入寄存器的值
* 返回  : 无
* 调用  ：内部调用   */
void WriteRawRC ( uint8_t ucAddress, uint8_t ucValue )
{
    uint8_t ucAddr;
    ucAddr = ( ucAddress << 1 ) & 0x7E;

    RC522_CS_Enable();
    SPI_RC522_SendByte ( ucAddr );
    SPI_RC522_SendByte ( ucValue );
    RC522_CS_Disable();
}

/* 函数名：M500PcdConfigISOType
 * 描述  ：设置RC522的工作方式
 * 输入  ：ucType，工作方式
 * 返回  : 无
 * 调用  ：外部调用        */
void M500PcdConfigISOType (  void )
{
    ClearBitMask ( Status2Reg, 0x08 );
    WriteRawRC ( ModeReg, 0x3D );//3F
    WriteRawRC ( RxSelReg, 0x86 );//84
    WriteRawRC ( RFCfgReg, 0x7F );   //4F
    WriteRawRC ( TReloadRegL, 30 );//tmoLength);// TReloadVal = 'h6a =tmoLength(dec)
    WriteRawRC ( TReloadRegH, 0 );
    WriteRawRC ( TModeReg, 0x8D );
    WriteRawRC ( TPrescalerReg, 0x3E );
    HAL_Delay	   ( 1 );
//		PcdAntennaOn ();//开天线
}

/*
 * 函数名：SetBitMask
 * 描述  ：对RC522寄存器置位
 * 输入  ：ucReg，寄存器地址
 *         ucMask，置位值
 * 返回  : 无
 * 调用  ：内部调用
 */
void SetBitMask ( uint8_t ucReg, uint8_t ucMask )
{
    uint8_t ucTemp;

    ucTemp = ReadRawRC ( ucReg );
    WriteRawRC ( ucReg, ucTemp | ucMask );         // set bit mask
}

/* 函数名：ClearBitMask
 * 描述  ：对RC522寄存器清位
 * 输入  ：ucReg，寄存器地址
 *         ucMask，清位值
 * 返回  : 无
 * 调用  ：内部调用           */
void ClearBitMask ( uint8_t ucReg, uint8_t ucMask )
{
    uint8_t ucTemp;
    ucTemp = ReadRawRC ( ucReg );

    WriteRawRC ( ucReg, ucTemp & ( ~ ucMask) );  // clear bit mask

}

/* 函数名：PcdAntennaOn
 * 描述  ：开启天线
 * 输入  ：无
 * 返回  : 无
 * 调用  ：内部调用            */
void PcdAntennaOn ( void )
{
    uint8_t uc;
    uc = ReadRawRC ( TxControlReg );
    if ( ! ( uc & 0x03 ) )
        SetBitMask(TxControlReg, 0x03);

}

/* 函数名：PcdAntennaOff
 * 描述  ：开启天线
 * 输入  ：无
 * 返回  : 无
 * 调用  ：内部调用             */
void PcdAntennaOff ( void )
{
    ClearBitMask ( TxControlReg, 0x03 );
}

void ShowID(uint16_t x,uint16_t y, uint8_t *p, uint16_t charColor, uint16_t bkColor)  //显示卡的卡号，以十六进制显示
{
    uint8_t num[9];
    printf("ID>>>%s\r\n", num);

}

/* 函数名：PcdComMF522
 * 描述  ：通过RC522和ISO14443卡通讯
 * 输入  ：ucCommand，RC522命令字
 *         pInData，通过RC522发送到卡片的数据
 *         ucInLenByte，发送数据的字节长度
 *         pOutData，接收到的卡片返回数据
 *         pOutLenBit，返回数据的位长度
 * 返回  : 状态值
 *         = MI_OK，成功
 * 调用  ：内部调用              */
char PcdComMF522 ( uint8_t ucCommand, uint8_t * pInData, uint8_t ucInLenByte, uint8_t * pOutData, uint32_t * pOutLenBit )
{
    char cStatus = MI_ERR;
    uint8_t ucIrqEn   = 0x00;
    uint8_t ucWaitFor = 0x00;
    uint8_t ucLastBits;
    uint8_t ucN;
    uint32_t ul;
    switch ( ucCommand )
    {
    case PCD_AUTHENT:		//Mifare认证
        ucIrqEn   = 0x12;		//允许错误中断请求ErrIEn  允许空闲中断IdleIEn
        ucWaitFor = 0x10;		//认证寻卡等待时候 查询空闲中断标志位
        break;

    case PCD_TRANSCEIVE:		//接收发送 发送接收
        ucIrqEn   = 0x77;		//允许TxIEn RxIEn IdleIEn LoAlertIEn ErrIEn TimerIEn
        ucWaitFor = 0x30;		//寻卡等待时候 查询接收中断标志位与 空闲中断标志位
        break;

    default:
        break;

    }
    WriteRawRC ( ComIEnReg, ucIrqEn | 0x80 );		//IRqInv置位管脚IRQ与Status1Reg的IRq位的值相反
    ClearBitMask ( ComIrqReg, 0x80 );			//Set1该位清零时，CommIRqReg的屏蔽位清零
    WriteRawRC ( CommandReg, PCD_IDLE );		//写空闲命令
    SetBitMask ( FIFOLevelReg, 0x80 );			//置位FlushBuffer清除内部FIFO的读和写指针以及ErrReg的BufferOvfl标志位被清除
    for ( ul = 0; ul < ucInLenByte; ul ++ )
        WriteRawRC ( FIFODataReg, pInData [ ul ] );    		//写数据进FIFOdata
    WriteRawRC ( CommandReg, ucCommand );					//写命令
    if ( ucCommand == PCD_TRANSCEIVE )
        SetBitMask(BitFramingReg,0x80);  				//StartSend置位启动数据发送 该位与收发命令使用时才有效
    ul = 1000;//根据时钟频率调整，操作M1卡最大等待时间25ms
    do 														//认证 与寻卡等待时间
    {
        ucN = ReadRawRC ( ComIrqReg );							//查询事件中断
        ul --;
    } while ( ( ul != 0 ) && ( ! ( ucN & 0x01 ) ) && ( ! ( ucN & ucWaitFor ) ) );		//退出条件i=0,定时器中断，与写空闲命令
    ClearBitMask ( BitFramingReg, 0x80 );					//清理允许StartSend位
    if ( ul != 0 )
    {
        if ( ! (( ReadRawRC ( ErrorReg ) & 0x1B )) )			//读错误标志寄存器BufferOfI CollErr ParityErr ProtocolErr
        {
            cStatus = MI_OK;
            if ( ucN & ucIrqEn & 0x01 )					//是否发生定时器中断
                cStatus = MI_NOTAGERR;

            if ( ucCommand == PCD_TRANSCEIVE )
            {
                ucN = ReadRawRC ( FIFOLevelReg );			//读FIFO中保存的字节数
                ucLastBits = ReadRawRC ( ControlReg ) & 0x07;	//最后接收到得字节的有效位数

                if ( ucLastBits )
                    * pOutLenBit = ( ucN - 1 ) * 8 + ucLastBits;   	//N个字节数减去1（最后一个字节）+最后一位的位数 读取到的数据总位数
                else
                    * pOutLenBit = ucN * 8;   					//最后接收到的字节整个字节有效
                if ( ucN == 0 )
                    ucN = 1;
                if ( ucN > MAXRLEN )
                    ucN = MAXRLEN;
                for ( ul = 0; ul < ucN; ul ++ )
                    pOutData [ ul ] = ReadRawRC ( FIFODataReg );
            }
        }
        else
            cStatus = MI_ERR;
    }
    SetBitMask ( ControlReg, 0x80 );           // stop timer now
    WriteRawRC ( CommandReg, PCD_IDLE );

    return cStatus;
}


/* 函数名：PcdRequest
 * 描述  ：寻卡
 * 输入  ：ucReq_code，寻卡方式
 *                     = 0x52，寻感应区内所有符合14443A标准的卡
 *                     = 0x26，寻未进入休眠状态的卡
 *         pTagType，卡片类型代码
 *                   = 0x4400，Mifare_UltraLight
 *                   = 0x0400，Mifare_One(S50)
 *                   = 0x0200，Mifare_One(S70)
 *                   = 0x0800，Mifare_Pro(X))
 *                   = 0x4403，Mifare_DESFire
 * 返回  : 状态值
 *         = MI_OK，成功
 * 调用  ：外部调用            */
char PcdRequest ( uint8_t ucReq_code, uint8_t * pTagType )
{
    char cStatus;
    uint8_t ucComMF522Buf [ MAXRLEN ];
    uint32_t ulLen;

    ClearBitMask ( Status2Reg, 0x08 );	//清理指示MIFARECyptol单元接通以及所有卡的数据通信被加密的情况
    WriteRawRC ( BitFramingReg, 0x07 );	//	发送的最后一个字节的 七位
    SetBitMask ( TxControlReg, 0x03 );	//TX1,TX2管脚的输出信号传递经发送调制的13.56的能量载波信号

    ucComMF522Buf [ 0 ] = ucReq_code;		//存入 卡片命令字

    cStatus = PcdComMF522 ( PCD_TRANSCEIVE,	ucComMF522Buf, 1, ucComMF522Buf, & ulLen );	//寻卡

    if ( ( cStatus == MI_OK ) && ( ulLen == 0x10 ) )	//寻卡成功返回卡类型
    {
        * pTagType = ucComMF522Buf [ 0 ];
        * ( pTagType + 1 ) = ucComMF522Buf [ 1 ];
    }

    else
        cStatus = MI_ERR;

    return cStatus;
}

/* 函数名：PcdAnticoll
 * 描述  ：防冲撞
 * 输入  ：pSnr，卡片序列号，4字节
 * 返回  : 状态值
 *         = MI_OK，成功
 * 调用  ：外部调用           */
char PcdAnticoll ( uint8_t * pSnr )
{
    char cStatus;
    uint8_t uc, ucSnr_check = 0;
    uint8_t ucComMF522Buf [ MAXRLEN ];
    uint32_t ulLen;

    ClearBitMask ( Status2Reg, 0x08 );		//清MFCryptol On位 只有成功执行MFAuthent命令后，该位才能置位
    WriteRawRC ( BitFramingReg, 0x00);		//清理寄存器 停止收发
    ClearBitMask ( CollReg, 0x80 );			//清ValuesAfterColl所有接收的位在冲突后被清除

    ucComMF522Buf [ 0 ] = 0x93;	//卡片防冲突命令
    ucComMF522Buf [ 1 ] = 0x20;

    cStatus = PcdComMF522 ( PCD_TRANSCEIVE, ucComMF522Buf, 2, ucComMF522Buf, & ulLen);//与卡片通信

    if ( cStatus == MI_OK)		//通信成功
    {
        for ( uc = 0; uc < 4; uc ++ )
        {
            * ( pSnr + uc )  = ucComMF522Buf [ uc ];			//读出UID
            ucSnr_check ^= ucComMF522Buf [ uc ];
        }

        if ( ucSnr_check != ucComMF522Buf [ uc ] )
            cStatus = MI_ERR;
    }
    SetBitMask ( CollReg, 0x80 );

    return cStatus;
}

/* 函数名：PcdSelect
 * 描述  ：选定卡片
 * 输入  ：pSnr，卡片序列号，4字节
 * 返回  : 状态值
 *         = MI_OK，成功
 * 调用  ：外部调用         */
char PcdSelect ( uint8_t * pSnr )
{
    char ucN;
    uint8_t uc;
    uint8_t ucComMF522Buf [ MAXRLEN ];
    uint32_t  ulLen;

    ucComMF522Buf [ 0 ] = PICC_ANTICOLL1;
    ucComMF522Buf [ 1 ] = 0x70;
    ucComMF522Buf [ 6 ] = 0;

    for ( uc = 0; uc < 4; uc ++ )
    {
        ucComMF522Buf [ uc + 2 ] = * ( pSnr + uc );
        ucComMF522Buf [ 6 ] ^= * ( pSnr + uc );
    }

    CalulateCRC ( ucComMF522Buf, 7, & ucComMF522Buf [ 7 ] );
    ClearBitMask ( Status2Reg, 0x08 );
    ucN = PcdComMF522 ( PCD_TRANSCEIVE, ucComMF522Buf, 9, ucComMF522Buf, & ulLen );

    if ( ( ucN == MI_OK ) && ( ulLen == 0x18 ) )
        ucN = MI_OK;
    else
        ucN = MI_ERR;

    return ucN;
}

/* 函数名：CalulateCRC
 * 描述  ：用RC522计算CRC16
 * 输入  ：pIndata，计算CRC16的数组
 *         ucLen，计算CRC16的数组字节长度
 *         pOutData，存放计算结果存放的首地址
 * 返回  : 无
 * 调用  ：内部调用              */
void CalulateCRC ( uint8_t * pIndata, uint8_t ucLen, uint8_t * pOutData )
{
    uint8_t uc, ucN;

    ClearBitMask(DivIrqReg,0x04);
    WriteRawRC(CommandReg,PCD_IDLE);
    SetBitMask(FIFOLevelReg,0x80);

    for ( uc = 0; uc < ucLen; uc ++)
        WriteRawRC ( FIFODataReg, * ( pIndata + uc ) );

    WriteRawRC ( CommandReg, PCD_CALCCRC );
    uc = 0xFF;

    do {
        ucN = ReadRawRC ( DivIrqReg );
        uc --;
    }
    while ( ( uc != 0 ) && ! ( ucN & 0x04 ) );

    pOutData [ 0 ] = ReadRawRC ( CRCResultRegL );
    pOutData [ 1 ] = ReadRawRC ( CRCResultRegM );

}

/* 函数名：PcdAuthState
 * 描述  ：验证卡片密码
 * 输入  ：ucAuth_mode，密码验证模式
 *                     = 0x60，验证A密钥
 *                     = 0x61，验证B密钥
 *         uint8_t ucAddr，块地址
 *         pKey，密码
 *         pSnr，卡片序列号，4字节
 * 返回  : 状态值
 *         = MI_OK，成功
 * 调用  ：外部调用          */
char PcdAuthState ( uint8_t ucAuth_mode, uint8_t ucAddr, uint8_t * pKey, uint8_t * pSnr )
{
    char cStatus;
    uint8_t uc, ucComMF522Buf [ MAXRLEN ];
    uint32_t ulLen;

    ucComMF522Buf [ 0 ] = ucAuth_mode;
    ucComMF522Buf [ 1 ] = ucAddr;

    for ( uc = 0; uc < 6; uc ++ )
        ucComMF522Buf [ uc + 2 ] = * ( pKey + uc );

    for ( uc = 0; uc < 6; uc ++ )
        ucComMF522Buf [ uc + 8 ] = * ( pSnr + uc );

    cStatus = PcdComMF522 ( PCD_AUTHENT, ucComMF522Buf, 12, ucComMF522Buf, & ulLen );

    if ( ( cStatus != MI_OK ) || ( ! ( ReadRawRC ( Status2Reg ) & 0x08 ) ) ) {
        cStatus = MI_ERR;
    }

    return cStatus;
}

/* 函数名：PcdWrite
 * 描述  ：写数据到M1卡一块
 * 输入  ：uint8_t ucAddr，块地址
 *         pData，写入的数据，16字节
 * 返回  : 状态值
 *         = MI_OK，成功
 * 调用  ：外部调用           */
char PcdWrite ( uint8_t ucAddr, uint8_t * pData )
{
    char cStatus;
    uint8_t uc, ucComMF522Buf [ MAXRLEN ];
    uint32_t ulLen;

    ucComMF522Buf [ 0 ] = PICC_WRITE;
    ucComMF522Buf [ 1 ] = ucAddr;

    CalulateCRC ( ucComMF522Buf, 2, & ucComMF522Buf [ 2 ] );

    cStatus = PcdComMF522 ( PCD_TRANSCEIVE, ucComMF522Buf, 4, ucComMF522Buf, & ulLen );

    if ( ( cStatus != MI_OK ) || ( ulLen != 4 ) || ( ( ucComMF522Buf [ 0 ] & 0x0F ) != 0x0A ) )
        cStatus = MI_ERR;

    if ( cStatus == MI_OK )
    {
        memcpy(ucComMF522Buf, pData, 16);
        for ( uc = 0; uc < 16; uc ++ )
            ucComMF522Buf [ uc ] = * ( pData + uc );

        CalulateCRC ( ucComMF522Buf, 16, & ucComMF522Buf [ 16 ] );

        cStatus = PcdComMF522 ( PCD_TRANSCEIVE, ucComMF522Buf, 18, ucComMF522Buf, & ulLen );

        if ( ( cStatus != MI_OK ) || ( ulLen != 4 ) || ( ( ucComMF522Buf [ 0 ] & 0x0F ) != 0x0A ) )
            cStatus = MI_ERR;

    }

    return cStatus;

}

/* 函数名：PcdRead
 * 描述  ：读取M1卡一块数据
 * 输入  ：uint8_t ucAddr，块地址
 *         pData，读出的数据，16字节
 * 返回  : 状态值
 *         = MI_OK，成功
 * 调用  ：外部调用             */
char PcdRead ( uint8_t ucAddr, uint8_t * pData )
{
    char cStatus;
    uint8_t uc, ucComMF522Buf [ MAXRLEN ];
    uint32_t ulLen;

    ucComMF522Buf [ 0 ] = PICC_READ;
    ucComMF522Buf [ 1 ] = ucAddr;

    CalulateCRC ( ucComMF522Buf, 2, & ucComMF522Buf [ 2 ] );

    cStatus = PcdComMF522 ( PCD_TRANSCEIVE, ucComMF522Buf, 4, ucComMF522Buf, & ulLen );

    if ( ( cStatus == MI_OK ) && ( ulLen == 0x90 ) )
    {
        for ( uc = 0; uc < 16; uc ++ )
            * ( pData + uc ) = ucComMF522Buf [ uc ];
    }

    else
        cStatus = MI_ERR;

    return cStatus;

}

/* 函数名：PcdHalt
 * 描述  ：命令卡片进入休眠状态
 * 输入  ：无
 * 返回  : 状态值
 *         = MI_OK，成功
 * 调用  ：外部调用        */
char PcdHalt( void )
{
    uint8_t ucComMF522Buf [ MAXRLEN ];
    uint32_t  ulLen;

    ucComMF522Buf [ 0 ] = PICC_HALT;
    ucComMF522Buf [ 1 ] = 0;

    CalulateCRC ( ucComMF522Buf, 2, & ucComMF522Buf [ 2 ] );
    PcdComMF522 ( PCD_TRANSCEIVE, ucComMF522Buf, 4, ucComMF522Buf, & ulLen );

    return MI_OK;
}


