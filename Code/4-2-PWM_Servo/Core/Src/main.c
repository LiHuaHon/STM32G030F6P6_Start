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

////��ʱ��14
//#define TIM14_PERIOD_MS    (20)//20ms��ʱ�� ->50HZ
//#define TIM14_PERIOD_COUNT    (TIM14_PERIOD_MS*100)

////��ʱ��ʱ��ԴTIMxCLK = 2 * APB1_CLK (2*144)
////				���APB1_CLK = 288MHz = TIMxCLK
////				����TIMxCLK=APB1_CLK * 2
//// �趨��ʱ��Ƶ��Ϊ=TIMxCLK/(72)=1MHz
//// Ƶ��1(TIMxCLK=72MHZ)=TIMxCLK/(720)=100KHz
//// Ƶ��2(crm_clocks_freq_struct.apb2_freq * 2 =288MHZ)=TIMxCLK/(2880)=100KHz
//#define BASIC_PRESCALER_COUNT   (640)//64Mhz


/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

#define USER_KEY    HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_7)  //KEY����PA7

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
  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);   //PA4��Ӧ���ŵ�
  HAL_TIM_PWM_Start(&htim14,TIM_CHANNEL_1);//����PWMͨ��1 
	//ʹ�ö�ʱ��14 PB1 ���PWM���ƶ��
	/*
		����ʾ��
		
		PB1->���PWM�ź������
		
		VCC->�������
		
		GND->�������
	
	*/
  /* USER CODE END 2 */
	TIM14->CCR1=(60.F/100.F)*(TIM14_PERIOD_COUNT*0.975f-TIM14_PERIOD_COUNT*0.875f); //������0.5~2.5ms֮��
	while(1);	
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
		
    /* USER CODE BEGIN 3 */
		if(USART_RX_STA&0x8000)
		{					   
			uint16_t pwm_vaule=0;
			len=USART_RX_STA&0x3fff;//�õ��˴ν��յ������ݳ���
			if(len==1){
				pwm_vaule=(USART_RX_BUF[len-1]-'0');//������յ����� 16 ���Ӧ���� ����1��-��0����*10 +����6��-��0����= 1*10+6=16	
			}else if(len==2){
				pwm_vaule=(USART_RX_BUF[len-2]-'0')*10+(USART_RX_BUF[len-1]-'0');//������յ����� 16 ���Ӧ���� ����1��-��0����*10 +����6��-��0����= 1*10+6=16
			}else if(len==3){
				pwm_vaule=(USART_RX_BUF[len-3]-'0')*100+(USART_RX_BUF[len-2]-'0')*10+(USART_RX_BUF[len-1]-'0');//������յ����� 16 ���Ӧ���� ����1��-��0����*10 +����6��-��0����= 1*10+6=16
			}else{
				printf("\r\n���������\r\n");
				USART_RX_STA=0;
				continue;
			}
			if(pwm_vaule>100){
				printf("\r\n���������\r\n");
			}
			TIM14->CCR1=(pwm_vaule/100.F)*(TIM14_PERIOD_COUNT*0.975f-TIM14_PERIOD_COUNT*0.875f); //������0.5~2.5ms֮��
			
			printf("\r\n������ռ�ձ�Ϊ:%d\r\n",pwm_vaule);
			USART_RX_STA=0;
		}else// ��114514����仰��������Э���������֮��
		{
			times++;
			if(times%5000==0)
			{
				printf("\r\nSTM32G030F6P6��Сϵͳ�� PWM���ʵ��\r\n");
			}
			if(times%200==0)printf("����Ҫ���Ƶ�����ռ�ձ�0~100,��ASCII�뷢��(��Ҫ��ѡ16���Ʒ���),���»س�������\r\n");  
			if(times%30==0){//��˸LED,��ʾϵͳ��������.
					if(x==0){
						HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET);   //PA4��Ӧ���Ÿ�
						x=1;
					}else{
						HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);   //PA4��Ӧ���ŵ�
						x=0;
					}
			}
			HAL_Delay(10);   
		} 
		t=KEY_Scan(0);		//�õ���ֵ
		if(t==USER_KEY_PRES){
			printf("\r\nKEY�������� \r\n");
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

//����������
//���ذ���ֵ
//mode:0,��֧��������;1,֧��������;
//����ֵ��
//0��û���κΰ�������
//USER_KEY_PRES��USER_KEY����

uint8_t KEY_Scan(uint8_t mode)
{	 
	static uint8_t key_up=1;//�������ɿ���־
	if(mode)key_up=1;  //֧������		  
	if(key_up&&(USER_KEY==0))
	{
		HAL_Delay(10);//ȥ���� 
		key_up=0;
		if(USER_KEY==0)return USER_KEY_PRES;
	}else if(USER_KEY==1)key_up=1; 	     
	return 0;// �ް�������
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
