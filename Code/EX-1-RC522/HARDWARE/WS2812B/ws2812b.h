#ifndef __WS2812B_H__
#define __WS2812B_H__
 
#include "main.h"
 
//��л Դ���� https://blog.csdn.net/qq_62078117/article/details/129911651?spm=1001.2101.3001.6650.2&utm_medium=distribute.pc_relevant.none-task-blog-2%7Edefault%7EYuanLiJiHua%7EPosition-2-129911651-blog-127753239.235%5Ev38%5Epc_relevant_sort_base1&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2%7Edefault%7EYuanLiJiHua%7EPosition-2-129911651-blog-127753239.235%5Ev38%5Epc_relevant_sort_base1&utm_relevant_index=5 
//����~O'Connor

/*���������ļ�������CCR�ĺ궨��*/
//��ΪPWMƵ��F��ҪΪ800KHz��
//APBʱ��Ƶ�ʹ̶�Ϊ64MHz ����Fpwm=Fclk / (arr+1)(psc+1) psc=89ʱ Ϊ800KHZ ��TIM1��ʱ����
//�����PWM0���CCRֵΪ��0.32 �� ��89+1���� 29 ��ҪС�������
//�����CODE_1 PWM1���CCRֵΪ��0.64 �� ��89+1���� 58 ��Ҫ���������
#define CODE_1       (80)       //1�붨ʱ����������
#define CODE_0       (10)       //0�붨ʱ����������
/*����һ�����嵥��LED��ԭɫֵ��С�Ľṹ��*/
typedef struct
{
	uint8_t R;
	uint8_t G;
	uint8_t B;
}RGB_Color_TypeDef;
 
extern const RGB_Color_TypeDef RED;   //��ʾ��ɫRGB����
extern const RGB_Color_TypeDef ORANGE;
extern const RGB_Color_TypeDef YELLOW;
extern const RGB_Color_TypeDef GREEN;
extern const RGB_Color_TypeDef CYAN;
extern const RGB_Color_TypeDef BLUE;
extern const RGB_Color_TypeDef PURPLE;
extern const RGB_Color_TypeDef BLACK;
extern const RGB_Color_TypeDef WHITE;
extern const RGB_Color_TypeDef MAGENTA;

#define Pixel_NUM 1  //LED�����궨�壬������ʹ��һ��LED��������pixelΪ���ص���˼��
 
void RGB_SetColor(uint8_t LedId,RGB_Color_TypeDef Color);//��һ��LEDװ��24����ɫ�����루0���1�룩
void Reset_Load(void); //�ú������ڽ��������24�����ݱ�Ϊ0������RESET_code
void RGB_SendArray(void);          //������������
void RGB_RED(uint16_t Pixel_Len);  //��ʾ���
void RGB_GREEN(uint16_t Pixel_Len);//��ʾ�̵�
void RGB_BLUE(uint16_t Pixel_Len); //��ʾ����
void RGB_WHITE(uint16_t Pixel_Len);//��ʾ�׵�
void rainbow(uint8_t wait);
void rgb_show(uint32_t Pixel_Len, RGB_Color_TypeDef rgb);
void led_loop(void);
 
#endif

