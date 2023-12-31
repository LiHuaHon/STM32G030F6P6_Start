//#include "bsp_as608.h"

//uint64_t FPM383C_HEAR = 0xF11FE22EB66BA88A;             ///FPM383C帧头
//uint16_t FPM383C_HEARADD = 0x0473;             ///FPM383C帧头累计F1+1F+E2+2E+B6+6B+A8+8A

//u8 QUEUE_BIT =UART_QUEUE_22BIT;//默认22BIT

////uint16_t FalgeNums =0;      //指纹数

//void FPM383C_SendData(uint8_t data);


///**
//  * @brief  FPM383C串口向指纹模块传递数据
//  * @param  data;传输的数据
//  */
//void FPM383C_SendData(uint8_t data)
//{
//    WRITE_REG(QUEUE_USART.Instance->TDR,data);
//    while((__HAL_UART_GET_FLAG(&QUEUE_USART,UART_FLAG_TXE)==RESET));//等待数据发送完毕
//}

///**
//  * @brief  发送FPM383C帧头
//  * @param  无
//  */
//void FPM383C_FrameHead(void)
//{
//    FPM383C_SendData((FPM383C_HEAR>>56)&0xff);
//    FPM383C_SendData((FPM383C_HEAR>>48)&0xff);
//    FPM383C_SendData((FPM383C_HEAR>>40)&0xff);
//    FPM383C_SendData((FPM383C_HEAR>>32)&0xff);
//    FPM383C_SendData((FPM383C_HEAR>>24)&0xff);
//    FPM383C_SendData((FPM383C_HEAR>>16)&0xff);
//    FPM383C_SendData((FPM383C_HEAR>>8)&0xff);
//    FPM383C_SendData((FPM383C_HEAR>>0)&0xff);
//}

///**
//  * @brief  发送数据长度 帧头校验 密码
//  * @param  len:数据长度
//  * @retval 无
//  */
//void FPM383C_DataLenth(uint16_t len)
//{
//    FPM383C_SendData((len>>8)&0xff);//高八位
//    FPM383C_SendData((len>>0)&0xff);//低八位
//    len+=FPM383C_HEARADD;//帧头校验
//    len=~len;
//    len+=1;
//    FPM383C_SendData(len&0xff);//发送帧头

//    FPM383C_SendData(0x00&0xff);//密码默认00 00 00 00
//    FPM383C_SendData(0x00&0xff);
//    FPM383C_SendData(0x00&0xff);
//    FPM383C_SendData(0x00&0xff);
//}
///**
//  * @brief  发送指令
//  * @param  com:指令
//  * @retval 无
//  */
//void FPM383C_Command(uint16_t com)
//{
//    FPM383C_SendData((com>>8)&0xff);//高八位
//    FPM383C_SendData((com>>0)&0xff);//低八位
//}
///**
//  * @brief  发送指令参数
//  * @param pa指令参数 num参数个数
//  * @retval 无
//  */
//void FPM383C_ParamSet(uint32_t pa,uint8_t num)
//{
//    switch(num) {

//    case 1:
//        FPM383C_SendData((pa>>8)&0xff);
//        FPM383C_SendData((pa>>0)&0xff);
//        break;

//    case 2:
//        FPM383C_SendData((pa>>8)&0xff);
//        FPM383C_SendData((pa>>0)&0xff);
//        break;

//    case 3:
//        FPM383C_SendData((pa>>16)&0xff);
//        FPM383C_SendData((pa>>8)&0xff);
//        FPM383C_SendData((pa>>0)&0xff);
//        break;
//    case 4:
//        FPM383C_SendData((pa>>24)&0xff);
//        FPM383C_SendData((pa>>16)&0xff);
//        FPM383C_SendData((pa>>8)&0xff);
//        FPM383C_SendData((pa>>0)&0xff);
//        break;

//    default:
//        break;

//    }
//}
///**
//  * @brief  发送校验和
//  * @param  data;校验密码+命令+参数
//  * @retval 无
//  */
//void FPM383C_LasetCheck(uint8_t data)
//{
//    data=~data;
//    data+=1;
//    FPM383C_SendData((data>>0)&0xff);//低八位
//}
///**
//  * @brief  接收数据验证(22-26位)
//  * @param  无
//  * @retval 接收无误 0x00 有误返回错误代码
//  */
//uint8_t i=0;
//uint16_t sure=0;
//uint16_t heat=0;//帧头统计
//uint16_t check=0;//校验统计
//uint16_t Receive_Check(void)
//{
//    i=0;
//    sure=0;
//    heat=0;//帧头统计
//    check=0;//校验统计
//    QUEUE_DATA_TYPE *rx_data;

//    rx_data = cbRead(&rx_queue);  /*从缓冲区读取数据，进行处理*/

//    while(i<=9) {
//        heat+=((uint16_t )(*(rx_data->head+i)));
//        i++;
//    }
//    heat=~heat;
//    heat=heat+1;
//    heat=heat&0x00FF;//排除干扰

//    if(heat!=((uint16_t )(*(rx_data->head+10))))//帧头统计校验
//    {
//        cbReadFinish(&rx_queue);
//        return 0xff;
//    }

//    i=11;
//    while(i<=QUEUE_BIT-2) {
//        check+=((uint16_t )(*(rx_data->head+i)));//数据层校验
//        i++;
//    }

//    check=~check;
//    check=check+1;
//    check=check&0x00FF;//排除干扰
//    switch(QUEUE_BIT)
//    {
//    case UART_QUEUE_22BIT:
//        if(check!=((uint16_t )(*(rx_data->head+21))))//帧头统计校验
//        {
//            cbReadFinish(&rx_queue);
//            return 0xff;
//        }
//        break;
//    case UART_QUEUE_24BIT:
//        if(check!=((uint16_t )(*(rx_data->head+23))))//帧头统计校验
//        {
//            cbReadFinish(&rx_queue);
//            return 0xff;
//        }
//        break;
//    case UART_QUEUE_26BIT:
//        if(check!=((uint16_t )(*(rx_data->head+25))))//帧头统计校验
//        {
//            cbReadFinish(&rx_queue);
//            return 0xff;
//        }
//        break;

//    }
//    //检查无误返回确认吗
//    sure=((uint16_t )(*(rx_data->head+20)));
//    cbReadFinish(&rx_queue);    /*使用完数据必须调用cbReadFinish更新读指针*/
//    return sure;
//}
///**
//  * @brief  指纹数据验证(28位)
//  * @param  ID匹配指纹号 RS匹配结果
//  * @retval 接收无误 0x00 有误返回错误代码
//  */
//uint8_t j=0;
//uint16_t F_sure=0;
//uint16_t F_head=0;//帧头统计
//uint16_t F_check=0;//校验统计
//uint16_t Finger_Check(uint16_t* ID,uint16_t* RS)
//{
//    j=0;
//    F_sure=0;
//    F_head=0;//帧头统计
//    F_check=0;//校验统计
//    QUEUE_DATA_TYPE *rx_data;

//    rx_data = cbRead(&rx_queue);  /*从缓冲区读取数据，进行处理*/

//    while(j<=9) {
//        F_head+=((uint16_t )(*(rx_data->head+j)));
//        j++;
//    }
//    F_head=~F_head;
//    F_head=F_head+1;
//    F_head=F_head&0x00FF;//排除干扰

//    if(F_head!=((uint16_t )(*(rx_data->head+10))))//帧头统计校验
//    {
//        cbReadFinish(&rx_queue);
////			*RS=0;
//        return 0xff;
//    }

//    j=11;
//    while(j<=26) {
//        F_check+=((uint16_t )(*(rx_data->head+j)));//数据层校验
//        j++;
//    }

//    F_check=~F_check;
//    F_check=F_check+1;
//    F_check=F_check&0x00FF;//排除干扰

//    if(F_check!=((uint16_t )(*(rx_data->head+27))))//帧头统计校验
//    {
//        cbReadFinish(&rx_queue);
//        return 0xff;
//    }
//    //检查无误返回确认吗
//    F_sure=((uint16_t )(*(rx_data->head+20)));

//    if(F_sure==0X00) {

//        *RS=((uint16_t )(*(rx_data->head+22)));
//        *ID=((uint16_t )(*(rx_data->head+26)));
//        cbReadFinish(&rx_queue);    /*使用完数据必须调用cbReadFinish更新读指针*/
//        return F_sure;

//    } else {

//        cbReadFinish(&rx_queue);
//        return F_sure;

//    }

//}
///**
//  * @brief  指纹注册数据验证(26位)
//  * @param  ORDER次数
//  * @retval 确认码
//  */
//uint16_t Receive_REGCheck(uint16_t* percentage)
//{

//    uint8_t i=0;
//    uint16_t sure=0;
//    uint16_t heat=0;//帧头统计
//    uint16_t check=0;//校验统计
//    QUEUE_DATA_TYPE *rx_data;

//    rx_data = cbRead(&rx_queue);  /*从缓冲区读取数据，进行处理*/

//    while(i<=9) {
//        heat+=((uint16_t )(*(rx_data->head+i)));
//        i++;
//    }
//    heat=~heat;
//    heat=heat+1;
//    heat=heat&0x00FF;//排除干扰

//    if(heat!=((uint16_t )(*(rx_data->head+10))))//帧头统计校验
//    {
//        cbReadFinish(&rx_queue);
//        return 0xff;
//    }

//    i=11;
//    while(i<=QUEUE_BIT-2) {
//        check+=((uint16_t )(*(rx_data->head+i)));//数据层校验
//        i++;
//    }

//    check=~check;
//    check=check+1;
//    check=check&0x00FF;//排除干扰

//    *percentage=((uint16_t )(*(rx_data->head+24)));//赋值进度
//    if(*percentage>=0X65) {
//        *percentage=0;
//    }
//    //检查无误返回确认吗
//    sure=((uint16_t )(*(rx_data->head+20)));
//    cbReadFinish(&rx_queue);    /*使用完数据必须调用cbReadFinish更新读指针*/
//    return sure;
//}
///**
//  * @brief  控制LED灯光
//  * @param  mod 控制模式 col灯光颜色
//			pwm模式下 pr1最大占空比 pr2最小占空比 pr3变化速率 范围均为0~100
//			闪烁模式下 pr1点亮时长 pr2 熄灭时长 pr3 闪烁次数 时长单位ms 范围0~100
//			详细参见FPM383C用户手册V1.2----5.31
//  * @retval 检测函数指纹该返回的数据需要22BIT
//  */
//void FPM383C_LED(uint8_t mod,uint8_t col,uint8_t pr1,uint8_t pr2,uint8_t pr3)
//{
//    FPM383C_FrameHead();
//    FPM383C_DataLenth(0x000C);
//    FPM383C_Command(0x020f);//命令 控制灯光

//    FPM383C_SendData(mod&0xff);
//    FPM383C_SendData(col&0xff);
//    FPM383C_SendData(pr1&0xff);
//    FPM383C_SendData(pr2&0xff);
//    FPM383C_SendData(pr3&0xff);

//    FPM383C_LasetCheck(0x02+0x0f+mod+col+pr1+pr2+pr3);

//    QUEUE_BIT=UART_QUEUE_22BIT;//检测数据22BIT
//}


///**
//  * @brief  心跳指令(22位)
//  * @param  无
//  * @retval 无
//  */
//void FPM383C_Heart(void)
//{
//    FPM383C_FrameHead();
//    FPM383C_DataLenth(0x0007);
//    FPM383C_Command(0x0303);//命令 心跳

//    FPM383C_LasetCheck(0x03+0x03);

//    QUEUE_BIT=UART_QUEUE_22BIT;//检测数据22BIT
//}

///**
//  * @brief  休眠模式(22位)
//  * @param  无
//  * @retval 无
//  */
//void FPM383C_Sleep(void)
//{
//    FPM383C_FrameHead();
//    FPM383C_DataLenth(0x0008);
//    FPM383C_Command(0x020C);//命令 休眠

//    FPM383C_SendData(0x00);//模式

//    FPM383C_LasetCheck(0x02+0x0C+0x00);

//    QUEUE_BIT=UART_QUEUE_22BIT;//检测数据22BIT
//}


///**
//  * @brief  指纹匹配同步(28位)
//  * @param  无
//  * @retval 无
//  */
//void FPM383C_Matching(void)
//{
//    FPM383C_FrameHead();
//    FPM383C_DataLenth(0x0007);
//    FPM383C_Command(0x0123);//命令 匹配同步

//    FPM383C_LasetCheck(0x01+0x23);

//    QUEUE_BIT=UART_QUEUE_28BIT;//检测数据28BIT
//}
///**
//  * @brief  清除所有指纹(22位)
//  * @param  无
//  * @retval 无
//  */
//void FPM383C_CL(void)
//{
//    FPM383C_FrameHead();
//    FPM383C_DataLenth(0x000A);
//    FPM383C_Command(0x0131);//命令 清除指纹

//    FPM383C_SendData(0x01);
//    FPM383C_SendData((0x0001>>8)&0xff);//高八位
//    FPM383C_SendData((0x0001>>0)&0xff);//低八位
//    FPM383C_SendData(0xCC);

//    QUEUE_BIT=UART_QUEUE_22BIT;//检测数据28BIT
//}
///**
//  * @brief  自动注册(26位)
//  * @param  mod 是否需要手指抬起 x按压次数
//  * @retval 无
//  */
//void FPM383C_AutoREG(uint8_t mod,uint8_t x)
//{
//    FPM383C_FrameHead();
//    FPM383C_DataLenth(0x000B);
//    FPM383C_Command(0x0118);

//    FPM383C_SendData(mod&0xff);
//    FPM383C_SendData(x&0xff);
//    FPM383C_SendData(0xff);
//    FPM383C_SendData(0xff);

//    FPM383C_LasetCheck(0x01+0x18+mod+x+0xff+0xff);

//    QUEUE_BIT=UART_QUEUE_26BIT;//检测数据26BIT
//}

///**
//  * @brief  获取指纹数(24位)
//  * @param  无
//  * @retval 指纹数
//  */
//u8 FPM383C_NumFinger()
//{
//    QUEUE_DATA_TYPE *rx_data;
//    u8 NUM;
//    FPM383C_FrameHead();
//    FPM383C_DataLenth(0x0007);
//    FPM383C_Command(0x0203);

//    FPM383C_LasetCheck(0x02+0x03);

//    QUEUE_BIT=UART_QUEUE_24BIT;//检测数据24BIT



//    delay_ms(200);
//    rx_data = cbRead(&rx_queue);  /*从缓冲区读取数据，进行处理*/
//    NUM=((uint16_t )(*(rx_data->head+22)));
//    cbReadFinish(&rx_queue);    /*使用完数据必须调用cbReadFinish更新读指针*/
//    return NUM;
//}

///**
//  * @brief  显示错误信息OLED
//  * @param  ensure:确认码
//  * @retval 无
//  */
//void  OLED_ShowErrMessage( uint16_t  ensure)
//{
//    ensure&=0xff;
//    u8 num1=ensure/16;
//    u8 num2=ensure%16;

//    OLED_Clear();
//    OLED_ShowString(0,0,"ERROR:",16);

//    if(num1>9) {
//        switch(num1) {
//        case 10:
//            OLED_ShowChar(0,2,'A',16);
//            break;
//        case 11:
//            OLED_ShowChar(0,2,'B',16);
//            break;
//        case 12:
//            OLED_ShowChar(0,2,'C',16);
//            break;
//        case 13:
//            OLED_ShowChar(0,2,'D',16);
//            break;
//        case 14:
//            OLED_ShowChar(0,2,'E',16);
//            break;
//        case 15:
//            OLED_ShowChar(0,2,'F',16);
//            break;
//        }
//    } else {
//        OLED_ShowNum(0,2,num1,1,16);
//    }

//    if(num2>9) {
//        switch(num2) {
//        case 10:
//            OLED_ShowChar(8,2,'A',16);
//            break;
//        case 11:
//            OLED_ShowChar(8,2,'B',16);
//            break;
//        case 12:
//            OLED_ShowChar(8,2,'C',16);
//            break;
//        case 13:
//            OLED_ShowChar(8,2,'D',16);
//            break;
//        case 14:
//            OLED_ShowChar(8,2,'E',16);
//            break;
//        case 15:
//            OLED_ShowChar(8,2,'F',16);
//            break;
//        }
//    } else {
//        OLED_ShowNum(8,2,num2,1,16);
//    }


//}







/////*********************************************END OF FILE**********************/

