#include "ws2812b.h"
#include "tim.h"
//��л Դ���� https://blog.csdn.net/qq_62078117/article/details/129911651?spm=1001.2101.3001.6650.2&utm_medium=distribute.pc_relevant.none-task-blog-2%7Edefault%7EYuanLiJiHua%7EPosition-2-129911651-blog-127753239.235%5Ev38%5Epc_relevant_sort_base1&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2%7Edefault%7EYuanLiJiHua%7EPosition-2-129911651-blog-127753239.235%5Ev38%5Epc_relevant_sort_base1&utm_relevant_index=5 
//����~O'Connor
/*Some Static Colors------------------------------*/
const RGB_Color_TypeDef RED      = {255,0,0};   //��ʾ��ɫRGB����
const RGB_Color_TypeDef ORANGE   = {127,106,0};
const RGB_Color_TypeDef YELLOW   = {127,216,0};
const RGB_Color_TypeDef GREEN    = {0,255,0};
const RGB_Color_TypeDef CYAN	 = {0,255,255};
const RGB_Color_TypeDef BLUE     = {0,0,255};
const RGB_Color_TypeDef PURPLE	 = {238,130,238};
const RGB_Color_TypeDef BLACK    = {0,0,0};
const RGB_Color_TypeDef WHITE    = {255,255,255};
const RGB_Color_TypeDef MAGENTA  = {255,0,220};

 
/*��ά����������PWM������飬ÿһ��24��
���ݴ���һ��LED�����һ��24��0����RESET��*/
uint32_t Pixel_Buf[Pixel_NUM+1][24];       
 
/*
���ܣ��趨����RGB LED����ɫ���ѽṹ����RGB��24BITת��Ϊ0���1��
������LedIdΪLED��ţ�Color���������ɫ�ṹ��
*/
void RGB_SetColor(uint8_t LedId,RGB_Color_TypeDef Color)
{
	uint8_t i; 
	if(LedId > Pixel_NUM)return; //avoid overflow ��ֹд��ID����LED����
	
	for(i=0;i<8;i++) Pixel_Buf[LedId][i]   = ( (Color.G & (1 << (7 -i)))? (CODE_1):CODE_0 );//����ĳһ��0~7ת�����G
	for(i=8;i<16;i++) Pixel_Buf[LedId][i]  = ( (Color.R & (1 << (15-i)))? (CODE_1):CODE_0 );//����ĳһ��8~15ת�����R
	for(i=16;i<24;i++) Pixel_Buf[LedId][i] = ( (Color.B & (1 << (23-i)))? (CODE_1):CODE_0 );//����ĳһ��16~23ת�����B
}

/*
���ܣ����һ��װ��24��0�����24������ռ�ձ�Ϊ0��PWM������Ϊ���reset��ʱ��������ʱ��Ϊ24*1.2=30us > 24us(Ҫ�����24us)
*/
void Reset_Load(void)
{
	uint8_t i;
	for(i=0;i<24;i++)
	{
		Pixel_Buf[Pixel_NUM][i] = 0;
	}
}
 
/*
���ܣ���������
������(&htim1)��ʱ��1��(TIM_CHANNEL_2)ͨ��2��((uint32_t *)Pixel_Buf)���������飬
			(Pixel_NUM+1)*24)���͸����������������
*/
void RGB_SendArray(void)
{//��ʱ��1 ͨ��1 PA8
	HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, (uint32_t *)Pixel_Buf,(Pixel_NUM+1)*24);
}
 
/*
���ܣ���ʾ��ɫ
������Pixel_LenΪ��ʾLED����
*/
void RGB_RED(uint16_t Pixel_Len)
{
	uint16_t i;
	for(i=0;i<Pixel_Len;i++)//����Ӧ����LEDд���ɫ
	{
		RGB_SetColor(i,RED);
	}
	Reset_Load();
	RGB_SendArray();
}
 
/*
���ܣ���ʾ��ɫ
������Pixel_LenΪ��ʾLED����
*/
void RGB_GREEN(uint16_t Pixel_Len)
{
	uint16_t i;
	for(i=0;i<Pixel_Len;i++)//����Ӧ����LEDд����ɫ
	{
		RGB_SetColor(i,GREEN);
	}
	Reset_Load();
	RGB_SendArray();
}
 
/*
���ܣ���ʾ��ɫ
������Pixel_LenΪ��ʾLED����
*/
void RGB_BLUE(uint16_t Pixel_Len)
{
	uint16_t i;
	for(i=0;i<Pixel_Len;i++)//����Ӧ����LEDд����ɫ
	{
		RGB_SetColor(i,BLUE);
	}
	Reset_Load();
	RGB_SendArray();
}
 
/*
���ܣ���ʾ��ɫ
������Pixel_LenΪ��ʾLED����
*/
void RGB_WHITE(uint16_t Pixel_Len)
{
	uint16_t i;
	for(i=0;i<Pixel_Len;i++)//����Ӧ����LEDд���ɫ
	{
		RGB_SetColor(i,WHITE);
	}
	Reset_Load();
	RGB_SendArray();
}
 
//Ҳ���Լ������������ɫ������ɫ�仯������

/*******************************************************************************/
/*									��Ӳ���									   */

//��ʾָ����ɫ
void rgb_show(uint32_t Pixel_Len, RGB_Color_TypeDef rgb)
{
	uint16_t i;
	for(i=0;i<Pixel_Len;i++)
	{
		RGB_SetColor(i,rgb);
	}
	Reset_Load();
	RGB_SendArray();
}

//��ɫѭ��ת��
RGB_Color_TypeDef Wheel(uint8_t WheelPos)
{
	RGB_Color_TypeDef rgb;
	WheelPos = 255 - WheelPos;
	if (WheelPos < 85)
	{
		rgb.R = 255 - WheelPos * 3;
		rgb.G = 0;
		rgb.B = WheelPos * 3;
		return rgb;
	}
	if (WheelPos < 170)
	{
		WheelPos -= 85;
		rgb.R = 0;
		rgb.G = WheelPos * 3;
		rgb.B = 255 - WheelPos * 3;
		return rgb;
	}
	WheelPos -= 170;
	rgb.R = WheelPos * 3;
	rgb.G = 255 - WheelPos * 3;
	rgb.B = 0;
	return rgb;
}

//�ʺ������
void rainbow(uint8_t wait)
{
	uint32_t timestamp = HAL_GetTick();
	uint16_t i;
	static uint8_t j;
	static uint32_t next_time = 0;

	uint32_t flag = 0;
	if (next_time < wait)
	{
		if ((uint64_t)timestamp + wait - next_time > 0)
			flag = 1;
	}
	else if (timestamp > next_time)
	{
		flag = 1;
	}
	if (flag)    // && (timestamp - next_time < wait*5))
	{
		j++;
		next_time = timestamp + wait;
		for (i = 0; i < Pixel_NUM; i++)
		{
			RGB_SetColor(i, Wheel((i + j) & 255));
		}
		HAL_Delay(wait);
	}
	Reset_Load();
	RGB_SendArray();
}

//�ʺ����ת
void rainbowCycle(uint8_t wait)
{
	uint32_t timestamp = HAL_GetTick();
	uint16_t i;
	static uint8_t j;
	static uint32_t next_time = 0;

	static uint8_t loop = 0;
	if (loop == 0)
		next_time = timestamp;
	loop = 1;    //�״ε��ó�ʼ��

	if ((timestamp > next_time))    // && (timestamp - next_time < wait*5))
	{
		j++;
		next_time = timestamp + wait;
		for (i = 0; i < Pixel_NUM; i++)
		{
			RGB_SetColor(i, Wheel(((i * 256 / (Pixel_NUM)) + j) & 255));
		}
	}
	RGB_SendArray();
}


uint8_t rainbow_change_flag = 0;
void led_loop(void)
{
	int i;
	rgb_show(8, BLACK);		HAL_Delay(300);
	for(i = 1; i <= 8 ;i++) {	//��
		rgb_show(i, RED);		
		HAL_Delay(50);		
	}
	for(i = 1; i <= 8 ;i++) {	//��
		rgb_show(i, ORANGE);		
		HAL_Delay(50);		
	}
	for(i = 1; i <= 8 ;i++) {	//��
		rgb_show(i, YELLOW);		
		HAL_Delay(50);		
	}
	for(i = 1; i <= 8 ;i++) {	//��
		rgb_show(i, GREEN);		
		HAL_Delay(50);		
	}
	for(i = 1; i <= 8 ;i++) {	//��
		rgb_show(i, CYAN);		
		HAL_Delay(50);		
	}
	for(i = 1; i <= 8 ;i++) {	//��
		rgb_show(i, BLUE);		
		HAL_Delay(50);		
	}
	for(i = 1; i <= 8 ;i++) {	//��
		rgb_show(i, PURPLE);		
		HAL_Delay(50);		
	}
	
	while(1) {
		if(!rainbow_change_flag)
			rainbow(5);
		else 
			rainbowCycle(2);
	}
	
}







