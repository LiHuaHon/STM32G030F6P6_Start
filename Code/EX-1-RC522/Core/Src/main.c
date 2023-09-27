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
#include "dma.h"
#include "i2c.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

// 代码版本 V0.1 可上线使用

#define FSUS_OPEN_ANGLE 5 	//修改开门和关门的角度
#define FSUS_CLOSE_ANGLE -30
#define FSUS_TIME_OPEN 400//修改开门和关门的时间 最慢1000MS->1S
#define FSUS_TIME_CLOSE 1000


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
 uint8_t TEXT_Buffer[]={0XF1,0XF2,0XF3,0XF4,0XFF,0X1F,0X2F,0X3F,0X4F};
#define SIZE sizeof(TEXT_Buffer)	

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	char cid[20]={0};
	uint8_t getSure=1;
	uint8_t timeOut=0;
	uint8_t len=0;
	uint8_t ledFlage=0;
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

	User_CreateAdmin(0,0XABCDEFFF);//一定要添加一个管理员
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_SPI1_Init();
  MX_USART1_UART_Init();
  MX_I2C2_Init();
  MX_USART2_UART_Init();
  MX_TIM1_Init();
  /* USER CODE BEGIN 2 */
	RC522_Init();
	while(AT24CXX_Check())//检测不到24c02
	{
		HAL_Delay(500);
		rgb_show(1,RED);	
		HAL_Delay(500);	
	}
	rgb_show(1, BLACK);	
	printf("\r\n开机读取代码=%2X\r\n",Control_ReadUserFormAT24CXX())	;
	FSUS_SetServoAngle(0,FSUS_CLOSE_ANGLE,1000,0);
	HAL_Delay(1000);
	FSUS_SetServoAngle(0,-15,500,0);
	HAL_Delay(500);
	FSUS_SetServoAngle(0,FSUS_CLOSE_ANGLE,1000,0);
	FSUS_Stop(0);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		if(USART_RX_STA&0x8000){
			char str[20]={0};
			rgb_show(1, WHITE);		
			len=USART_RX_STA&0x3fff;//得到此次接收到的数据长度
			get_data_str((char*)USART_RX_BUF,0,len,str);
			USART_RX_STA=0;
			if(strcmp("我要摇人",str)!=0){
				HAL_Delay(100);
				rgb_show(1, BLACK);		
				continue;
			}
			printf("\r\n请放置卡 5S后超时\r\n")	;
			while(1){
					HAL_Delay(100);
				
					if(ledFlage==1&&timeOut%2==0){
						rgb_show(1,CYAN);	
						ledFlage=0;
					}	else if (ledFlage==0&&timeOut%2==0){
						rgb_show(1,BLACK);	
						ledFlage=1;
					}
					
					if(timeOut++>=50){
						printf("\r\n超时 已退出\r\n");
						HAL_Delay(50);
						rgb_show(1,RED);	
						HAL_Delay(1000);
						rgb_show(1, BLACK);		
						timeOut=0;
						break;
					}else if(RC522_Read_ID_Once(cid)==MI_OK){
					printf ("\r\n读取到的卡ID为:%02X%02X%02X%02X\r\n", cid [ 0 ], cid [ 1 ], cid [ 2 ], cid [ 3 ] );
					getSure=User_Find(u8_Tun_u32((uint8_t*)cid));
					if(getSure==CODE_USER_AS){
							USART_RX_STA=0;
							Show_Menu();
							Control_Menu();
					}else if(getSure==CODE_USER_OK){
						printf ("\r\n用户不存在 已退出\r\n");
						HAL_Delay(500);
						timeOut=0;
						break;
					}else{
						printf ("\r\n未知错误 错误代码%x 已退出\r\n",getSure);
						timeOut=0;
						break;
					}
				}
			}
			USART_RX_STA=0;
		}else{
			if(RC522_Read_ID_Once(cid)==MI_OK){
				printf ("\r\n读取到的卡ID为:%02X%02X%02X%02X\r\n", cid [ 0 ], cid [ 1 ], cid [ 2 ], cid [ 3 ] );
				getSure=User_Find(u8_Tun_u32((uint8_t*)cid));
				if(getSure==CODE_USER_AS){
					printf ("\r\n用户存在 已经开锁\r\n");
					rgb_show(1, BLUE);		
					FSUS_SetServoAngle(0,FSUS_OPEN_ANGLE,FSUS_TIME_OPEN,0);
					HAL_Delay(FSUS_TIME_OPEN);
					FSUS_SetServoAngle(0,FSUS_CLOSE_ANGLE,FSUS_TIME_CLOSE,0);
					HAL_Delay(FSUS_TIME_CLOSE);
					FSUS_Stop(0);
					rgb_show(1, BLACK);		
					
				}else if(getSure==CODE_USER_OK){
					rgb_show(1, RED);		;
					HAL_Delay(1000);
					printf ("\r\n用户不存在\r\n");
					rgb_show(1, BLACK);		
				}else{
					rgb_show(1, RED);		;
					HAL_Delay(1000);
					printf ("\r\n未知错误 错误代码%x\r\n",getSure);
					rgb_show(1, BLACK);		
				}
				getSure=1;
			}
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
