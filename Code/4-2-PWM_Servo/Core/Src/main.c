/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

////定时器14
//#define TIM14_PERIOD_MS    (20)//20ms定时器 ->50HZ
//#define TIM14_PERIOD_COUNT    (TIM14_PERIOD_MS*100)

////定时器时钟源TIMxCLK = 2 * APB1_CLK (2*144)
////				如果APB1_CLK = 288MHz = TIMxCLK
////				否则TIMxCLK=APB1_CLK * 2
//// 设定定时器频率为=TIMxCLK/(72)=1MHz
//// 频率1(TIMxCLK=72MHZ)=TIMxCLK/(720)=100KHz
//// 频率2(crm_clocks_freq_struct.apb2_freq * 2 =288MHZ)=TIMxCLK/(2880)=100KHz
//#define BASIC_PRESCALER_COUNT   (640)//64Mhz


/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

#define USER_KEY    HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_7)  //KEY按键PA7

#define USER_KEY_PRES	1		//KEY  
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint8_t KEY_Scan(uint8_t mode);

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	uint8_t t=0;
 	uint8_t x=0;
	uint8_t len=0;
	uint16_t times=0;
	extern uint32_t tim_ms;
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_TIM14_Init();
	
  /* USER CODE BEGIN 2 */
  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);   //PA4对应引脚低
   HAL_TIM_PWM_Start(&htim14,TIM_CHANNEL_1);//开启PWM通道1 
	//使用定时器14 PB1 输出PWM控制舵机
	/*
		接线示意
		
		PB1->舵机PWM信号输入口
		
		VCC->舵机正极
		
		GND->舵机负极
	
	*/
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
		
    /* USER CODE BEGIN 3 */
		if(USART_RX_STA&0x8000)
		{					   
			uint16_t pwm_vaule=0;
			len=USART_RX_STA&0x3fff;//得到此次接收到的数据长度
			if(len==1){
				pwm_vaule=(USART_RX_BUF[len-1]-'0');//假设接收到的是 16 则对应的是 （‘1’-‘0’）*10 +（‘6’-‘0’）= 1*10+6=16	
			}else if(len==2){
				pwm_vaule=(USART_RX_BUF[len-2]-'0')*10+(USART_RX_BUF[len-1]-'0');//假设接收到的是 16 则对应的是 （‘1’-‘0’）*10 +（‘6’-‘0’）= 1*10+6=16
			}else if(len==3){
				pwm_vaule=(USART_RX_BUF[len-3]-'0')*100+(USART_RX_BUF[len-2]-'0')*10+(USART_RX_BUF[len-1]-'0');//假设接收到的是 16 则对应的是 （‘1’-‘0’）*10 +（‘6’-‘0’）= 1*10+6=16
			}else{
				printf("\r\n错误的输入\r\n");
				USART_RX_STA=0;
				continue;
			}
			if(pwm_vaule>100){
				printf("\r\n错误的输入\r\n");
			}
			TIM14->CCR1=(pwm_vaule/100.F)*(TIM14_PERIOD_COUNT*0.975f-TIM14_PERIOD_COUNT*0.875f); //限制在0.5~2.5ms之间
			
			printf("\r\n已设置占空比为:%d\r\n",pwm_vaule);
			USART_RX_STA=0;
		}else// “114514”这句话出至物理协会的林先生之手
		{
			times++;
			if(times%5000==0)
			{
				printf("\r\nSTM32G030F6P6最小系统板 PWM舵机实验\r\n");
			}
			if(times%200==0)printf("请输要控制的脉冲占空比0~100,以ASCII码发送(不要勾选16进制发送),按下回车键结束\r\n");  
			if(times%30==0){//闪烁LED,提示系统正在运行.
					if(x==0){
						HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET);   //PA4对应引脚高
						x=1;
					}else{
						HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);   //PA4对应引脚低
						x=0;
					}
			}
			HAL_Delay(10);   
		} 
		t=KEY_Scan(0);		//得到键值
		if(t==USER_KEY_PRES){
			printf("\r\nKEY按键按下 \r\n");
		}
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV1;
  RCC_OscInitStruct.PLL.PLLN = 8;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

//按键处理函数
//返回按键值
//mode:0,不支持连续按;1,支持连续按;
//返回值：
//0，没有任何按键按下
//USER_KEY_PRES，USER_KEY按下

uint8_t KEY_Scan(uint8_t mode)
{	 
	static uint8_t key_up=1;//按键按松开标志
	if(mode)key_up=1;  //支持连按		  
	if(key_up&&(USER_KEY==0))
	{
		HAL_Delay(10);//去抖动 
		key_up=0;
		if(USER_KEY==0)return USER_KEY_PRES;
	}else if(USER_KEY==1)key_up=1; 	     
	return 0;// 无按键按下
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
