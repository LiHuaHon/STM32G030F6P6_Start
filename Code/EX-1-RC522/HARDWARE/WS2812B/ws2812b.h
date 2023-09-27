#ifndef __WS2812B_H__
#define __WS2812B_H__
 
#include "main.h"
 
//鸣谢 源代码 https://blog.csdn.net/qq_62078117/article/details/129911651?spm=1001.2101.3001.6650.2&utm_medium=distribute.pc_relevant.none-task-blog-2%7Edefault%7EYuanLiJiHua%7EPosition-2-129911651-blog-127753239.235%5Ev38%5Epc_relevant_sort_base1&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2%7Edefault%7EYuanLiJiHua%7EPosition-2-129911651-blog-127753239.235%5Ev38%5Epc_relevant_sort_base1&utm_relevant_index=5 
//作者~O'Connor

/*这里是上文计算所得CCR的宏定义*/
//因为PWM频率F需要为800KHz，
//APB时钟频率固定为64MHz 根据Fpwm=Fclk / (arr+1)(psc+1) psc=89时 为800KHZ （TIM1定时器）
//计算出PWM0码的CCR值为：0.32 × （89+1）≈ 29 需要小于这个数
//计算出CODE_1 PWM1码的CCR值为：0.64 × （89+1）≈ 58 需要大于这个数
#define CODE_1       (80)       //1码定时器计数次数
#define CODE_0       (10)       //0码定时器计数次数
/*建立一个定义单个LED三原色值大小的结构体*/
typedef struct
{
	uint8_t R;
	uint8_t G;
	uint8_t B;
}RGB_Color_TypeDef;
 
extern const RGB_Color_TypeDef RED;   //显示红色RGB数据
extern const RGB_Color_TypeDef ORANGE;
extern const RGB_Color_TypeDef YELLOW;
extern const RGB_Color_TypeDef GREEN;
extern const RGB_Color_TypeDef CYAN;
extern const RGB_Color_TypeDef BLUE;
extern const RGB_Color_TypeDef PURPLE;
extern const RGB_Color_TypeDef BLACK;
extern const RGB_Color_TypeDef WHITE;
extern const RGB_Color_TypeDef MAGENTA;

#define Pixel_NUM 1  //LED数量宏定义，这里我使用一个LED，（单词pixel为像素的意思）
 
void RGB_SetColor(uint8_t LedId,RGB_Color_TypeDef Color);//给一个LED装载24个颜色数据码（0码和1码）
void Reset_Load(void); //该函数用于将数组最后24个数据变为0，代表RESET_code
void RGB_SendArray(void);          //发送最终数组
void RGB_RED(uint16_t Pixel_Len);  //显示红灯
void RGB_GREEN(uint16_t Pixel_Len);//显示绿灯
void RGB_BLUE(uint16_t Pixel_Len); //显示蓝灯
void RGB_WHITE(uint16_t Pixel_Len);//显示白灯
void rainbow(uint8_t wait);
void rgb_show(uint32_t Pixel_Len, RGB_Color_TypeDef rgb);
void led_loop(void);
 
#endif

