//#include "bsp_as608.h"

//uint64_t FPM383C_HEAR = 0xF11FE22EB66BA88A;             ///FPM383C֡ͷ
//uint16_t FPM383C_HEARADD = 0x0473;             ///FPM383C֡ͷ�ۼ�F1+1F+E2+2E+B6+6B+A8+8A

//u8 QUEUE_BIT =UART_QUEUE_22BIT;//Ĭ��22BIT

////uint16_t FalgeNums =0;      //ָ����

//void FPM383C_SendData(uint8_t data);


///**
//  * @brief  FPM383C������ָ��ģ�鴫������
//  * @param  data;���������
//  */
//void FPM383C_SendData(uint8_t data)
//{
//    WRITE_REG(QUEUE_USART.Instance->TDR,data);
//    while((__HAL_UART_GET_FLAG(&QUEUE_USART,UART_FLAG_TXE)==RESET));//�ȴ����ݷ������
//}

///**
//  * @brief  ����FPM383C֡ͷ
//  * @param  ��
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
//  * @brief  �������ݳ��� ֡ͷУ�� ����
//  * @param  len:���ݳ���
//  * @retval ��
//  */
//void FPM383C_DataLenth(uint16_t len)
//{
//    FPM383C_SendData((len>>8)&0xff);//�߰�λ
//    FPM383C_SendData((len>>0)&0xff);//�Ͱ�λ
//    len+=FPM383C_HEARADD;//֡ͷУ��
//    len=~len;
//    len+=1;
//    FPM383C_SendData(len&0xff);//����֡ͷ

//    FPM383C_SendData(0x00&0xff);//����Ĭ��00 00 00 00
//    FPM383C_SendData(0x00&0xff);
//    FPM383C_SendData(0x00&0xff);
//    FPM383C_SendData(0x00&0xff);
//}
///**
//  * @brief  ����ָ��
//  * @param  com:ָ��
//  * @retval ��
//  */
//void FPM383C_Command(uint16_t com)
//{
//    FPM383C_SendData((com>>8)&0xff);//�߰�λ
//    FPM383C_SendData((com>>0)&0xff);//�Ͱ�λ
//}
///**
//  * @brief  ����ָ�����
//  * @param paָ����� num��������
//  * @retval ��
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
//  * @brief  ����У���
//  * @param  data;У������+����+����
//  * @retval ��
//  */
//void FPM383C_LasetCheck(uint8_t data)
//{
//    data=~data;
//    data+=1;
//    FPM383C_SendData((data>>0)&0xff);//�Ͱ�λ
//}
///**
//  * @brief  ����������֤(22-26λ)
//  * @param  ��
//  * @retval �������� 0x00 ���󷵻ش������
//  */
//uint8_t i=0;
//uint16_t sure=0;
//uint16_t heat=0;//֡ͷͳ��
//uint16_t check=0;//У��ͳ��
//uint16_t Receive_Check(void)
//{
//    i=0;
//    sure=0;
//    heat=0;//֡ͷͳ��
//    check=0;//У��ͳ��
//    QUEUE_DATA_TYPE *rx_data;

//    rx_data = cbRead(&rx_queue);  /*�ӻ�������ȡ���ݣ����д���*/

//    while(i<=9) {
//        heat+=((uint16_t )(*(rx_data->head+i)));
//        i++;
//    }
//    heat=~heat;
//    heat=heat+1;
//    heat=heat&0x00FF;//�ų�����

//    if(heat!=((uint16_t )(*(rx_data->head+10))))//֡ͷͳ��У��
//    {
//        cbReadFinish(&rx_queue);
//        return 0xff;
//    }

//    i=11;
//    while(i<=QUEUE_BIT-2) {
//        check+=((uint16_t )(*(rx_data->head+i)));//���ݲ�У��
//        i++;
//    }

//    check=~check;
//    check=check+1;
//    check=check&0x00FF;//�ų�����
//    switch(QUEUE_BIT)
//    {
//    case UART_QUEUE_22BIT:
//        if(check!=((uint16_t )(*(rx_data->head+21))))//֡ͷͳ��У��
//        {
//            cbReadFinish(&rx_queue);
//            return 0xff;
//        }
//        break;
//    case UART_QUEUE_24BIT:
//        if(check!=((uint16_t )(*(rx_data->head+23))))//֡ͷͳ��У��
//        {
//            cbReadFinish(&rx_queue);
//            return 0xff;
//        }
//        break;
//    case UART_QUEUE_26BIT:
//        if(check!=((uint16_t )(*(rx_data->head+25))))//֡ͷͳ��У��
//        {
//            cbReadFinish(&rx_queue);
//            return 0xff;
//        }
//        break;

//    }
//    //������󷵻�ȷ����
//    sure=((uint16_t )(*(rx_data->head+20)));
//    cbReadFinish(&rx_queue);    /*ʹ�������ݱ������cbReadFinish���¶�ָ��*/
//    return sure;
//}
///**
//  * @brief  ָ��������֤(28λ)
//  * @param  IDƥ��ָ�ƺ� RSƥ����
//  * @retval �������� 0x00 ���󷵻ش������
//  */
//uint8_t j=0;
//uint16_t F_sure=0;
//uint16_t F_head=0;//֡ͷͳ��
//uint16_t F_check=0;//У��ͳ��
//uint16_t Finger_Check(uint16_t* ID,uint16_t* RS)
//{
//    j=0;
//    F_sure=0;
//    F_head=0;//֡ͷͳ��
//    F_check=0;//У��ͳ��
//    QUEUE_DATA_TYPE *rx_data;

//    rx_data = cbRead(&rx_queue);  /*�ӻ�������ȡ���ݣ����д���*/

//    while(j<=9) {
//        F_head+=((uint16_t )(*(rx_data->head+j)));
//        j++;
//    }
//    F_head=~F_head;
//    F_head=F_head+1;
//    F_head=F_head&0x00FF;//�ų�����

//    if(F_head!=((uint16_t )(*(rx_data->head+10))))//֡ͷͳ��У��
//    {
//        cbReadFinish(&rx_queue);
////			*RS=0;
//        return 0xff;
//    }

//    j=11;
//    while(j<=26) {
//        F_check+=((uint16_t )(*(rx_data->head+j)));//���ݲ�У��
//        j++;
//    }

//    F_check=~F_check;
//    F_check=F_check+1;
//    F_check=F_check&0x00FF;//�ų�����

//    if(F_check!=((uint16_t )(*(rx_data->head+27))))//֡ͷͳ��У��
//    {
//        cbReadFinish(&rx_queue);
//        return 0xff;
//    }
//    //������󷵻�ȷ����
//    F_sure=((uint16_t )(*(rx_data->head+20)));

//    if(F_sure==0X00) {

//        *RS=((uint16_t )(*(rx_data->head+22)));
//        *ID=((uint16_t )(*(rx_data->head+26)));
//        cbReadFinish(&rx_queue);    /*ʹ�������ݱ������cbReadFinish���¶�ָ��*/
//        return F_sure;

//    } else {

//        cbReadFinish(&rx_queue);
//        return F_sure;

//    }

//}
///**
//  * @brief  ָ��ע��������֤(26λ)
//  * @param  ORDER����
//  * @retval ȷ����
//  */
//uint16_t Receive_REGCheck(uint16_t* percentage)
//{

//    uint8_t i=0;
//    uint16_t sure=0;
//    uint16_t heat=0;//֡ͷͳ��
//    uint16_t check=0;//У��ͳ��
//    QUEUE_DATA_TYPE *rx_data;

//    rx_data = cbRead(&rx_queue);  /*�ӻ�������ȡ���ݣ����д���*/

//    while(i<=9) {
//        heat+=((uint16_t )(*(rx_data->head+i)));
//        i++;
//    }
//    heat=~heat;
//    heat=heat+1;
//    heat=heat&0x00FF;//�ų�����

//    if(heat!=((uint16_t )(*(rx_data->head+10))))//֡ͷͳ��У��
//    {
//        cbReadFinish(&rx_queue);
//        return 0xff;
//    }

//    i=11;
//    while(i<=QUEUE_BIT-2) {
//        check+=((uint16_t )(*(rx_data->head+i)));//���ݲ�У��
//        i++;
//    }

//    check=~check;
//    check=check+1;
//    check=check&0x00FF;//�ų�����

//    *percentage=((uint16_t )(*(rx_data->head+24)));//��ֵ����
//    if(*percentage>=0X65) {
//        *percentage=0;
//    }
//    //������󷵻�ȷ����
//    sure=((uint16_t )(*(rx_data->head+20)));
//    cbReadFinish(&rx_queue);    /*ʹ�������ݱ������cbReadFinish���¶�ָ��*/
//    return sure;
//}
///**
//  * @brief  ����LED�ƹ�
//  * @param  mod ����ģʽ col�ƹ���ɫ
//			pwmģʽ�� pr1���ռ�ձ� pr2��Сռ�ձ� pr3�仯���� ��Χ��Ϊ0~100
//			��˸ģʽ�� pr1����ʱ�� pr2 Ϩ��ʱ�� pr3 ��˸���� ʱ����λms ��Χ0~100
//			��ϸ�μ�FPM383C�û��ֲ�V1.2----5.31
//  * @retval ��⺯��ָ�Ƹ÷��ص�������Ҫ22BIT
//  */
//void FPM383C_LED(uint8_t mod,uint8_t col,uint8_t pr1,uint8_t pr2,uint8_t pr3)
//{
//    FPM383C_FrameHead();
//    FPM383C_DataLenth(0x000C);
//    FPM383C_Command(0x020f);//���� ���Ƶƹ�

//    FPM383C_SendData(mod&0xff);
//    FPM383C_SendData(col&0xff);
//    FPM383C_SendData(pr1&0xff);
//    FPM383C_SendData(pr2&0xff);
//    FPM383C_SendData(pr3&0xff);

//    FPM383C_LasetCheck(0x02+0x0f+mod+col+pr1+pr2+pr3);

//    QUEUE_BIT=UART_QUEUE_22BIT;//�������22BIT
//}


///**
//  * @brief  ����ָ��(22λ)
//  * @param  ��
//  * @retval ��
//  */
//void FPM383C_Heart(void)
//{
//    FPM383C_FrameHead();
//    FPM383C_DataLenth(0x0007);
//    FPM383C_Command(0x0303);//���� ����

//    FPM383C_LasetCheck(0x03+0x03);

//    QUEUE_BIT=UART_QUEUE_22BIT;//�������22BIT
//}

///**
//  * @brief  ����ģʽ(22λ)
//  * @param  ��
//  * @retval ��
//  */
//void FPM383C_Sleep(void)
//{
//    FPM383C_FrameHead();
//    FPM383C_DataLenth(0x0008);
//    FPM383C_Command(0x020C);//���� ����

//    FPM383C_SendData(0x00);//ģʽ

//    FPM383C_LasetCheck(0x02+0x0C+0x00);

//    QUEUE_BIT=UART_QUEUE_22BIT;//�������22BIT
//}


///**
//  * @brief  ָ��ƥ��ͬ��(28λ)
//  * @param  ��
//  * @retval ��
//  */
//void FPM383C_Matching(void)
//{
//    FPM383C_FrameHead();
//    FPM383C_DataLenth(0x0007);
//    FPM383C_Command(0x0123);//���� ƥ��ͬ��

//    FPM383C_LasetCheck(0x01+0x23);

//    QUEUE_BIT=UART_QUEUE_28BIT;//�������28BIT
//}
///**
//  * @brief  �������ָ��(22λ)
//  * @param  ��
//  * @retval ��
//  */
//void FPM383C_CL(void)
//{
//    FPM383C_FrameHead();
//    FPM383C_DataLenth(0x000A);
//    FPM383C_Command(0x0131);//���� ���ָ��

//    FPM383C_SendData(0x01);
//    FPM383C_SendData((0x0001>>8)&0xff);//�߰�λ
//    FPM383C_SendData((0x0001>>0)&0xff);//�Ͱ�λ
//    FPM383C_SendData(0xCC);

//    QUEUE_BIT=UART_QUEUE_22BIT;//�������28BIT
//}
///**
//  * @brief  �Զ�ע��(26λ)
//  * @param  mod �Ƿ���Ҫ��ָ̧�� x��ѹ����
//  * @retval ��
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

//    QUEUE_BIT=UART_QUEUE_26BIT;//�������26BIT
//}

///**
//  * @brief  ��ȡָ����(24λ)
//  * @param  ��
//  * @retval ָ����
//  */
//u8 FPM383C_NumFinger()
//{
//    QUEUE_DATA_TYPE *rx_data;
//    u8 NUM;
//    FPM383C_FrameHead();
//    FPM383C_DataLenth(0x0007);
//    FPM383C_Command(0x0203);

//    FPM383C_LasetCheck(0x02+0x03);

//    QUEUE_BIT=UART_QUEUE_24BIT;//�������24BIT



//    delay_ms(200);
//    rx_data = cbRead(&rx_queue);  /*�ӻ�������ȡ���ݣ����д���*/
//    NUM=((uint16_t )(*(rx_data->head+22)));
//    cbReadFinish(&rx_queue);    /*ʹ�������ݱ������cbReadFinish���¶�ָ��*/
//    return NUM;
//}

///**
//  * @brief  ��ʾ������ϢOLED
//  * @param  ensure:ȷ����
//  * @retval ��
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
