/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 STMicroelectronics.
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
#include "cmsis_os.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "string.h"
#include "stdio.h"
#include <string.h>
#include "myTypes.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
#define R_BUFF_LEN 32
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint8_t count = 0;					//к-ть нати�?кать
uint8_t btn_cur = 0;				//поточне значенн�? кнопки
uint8_t btn_prev = 0; 				//попереднє значенн�? кнопки
uint8_t active_brightness = 50;		//активна �?�?краві�?ть
uint8_t off_brightness = 0;			//вимкнена �?�?краві�?ть

volatile uint8_t counter = 0;		//рахівник на колбеці У�?РТ
volatile uint8_t buff[16] = { 0, };   //буфер дл�? збереженн�? введеної інформації value
volatile uint8_t value = 0;	//змінна в котру запи�?ують байт інформаціїї з терміналу
volatile uint8_t flag = 0; //флаг дл від�?лідковуванн�? введенн�? команд в термінал

int str[255] = { 0, };					//ма�?ив де зберігають�?�? введені дані з ьерміналу


//uint8_t tipe_str = 0;
//uint8_t buff[R_BUFF_LEN];
//uart_ring_buff_t uart_ring;
//
//uint8_t tstring[255];
//uint8_t rstring[R_BUFF_LEN + 1];
//char string[8];


extern UART_HandleTypeDef huart3;
extern DMA_HandleTypeDef hdma_usart3_tx;
extern DMA_HandleTypeDef hdma_usart3_rx;

//typedef struct
//{
//	uint8_t active_brightness;
//	uint8_t off_brightness;
//} QUEUE_t;

void ring_init(uart_ring_buff_t * uart_ring, uint8_t * buff, uint16_t buff_size);
void ring_clear(uart_ring_buff_t * uart_ring);
void ring_putchar(uart_ring_buff_t * uart_ring, uint8_t ch);
uint8_t ring_getchar(uart_ring_buff_t * uart_ring);
uint8_t ring_get_message(uart_ring_buff_t * uart_ring, uint8_t * string);
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void MX_FREERTOS_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

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
  MX_DMA_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_USART3_UART_Init();
  /* USER CODE BEGIN 2 */
  //ring_init(&uart_ring, buff, sizeof(buff) / sizeof(buff[0]) ); // Initialize UART receiver ring buffer.
 // sprintf((char*)tstring,"PRINT BRIGHTNESS FOR LED In range from 0 to 100->>>>!\r\n");
  //HAL_UART_Transmit_IT(&huart3,tstring,strlen((char*)tstring));
 // HAL_UART_Receive_IT(&huart3,uart_ring.buffer,1);						 // Start UART receiver in the non blocking mode

	setvbuf(stdin, NULL, _IONBF, 0); // определение нулевого буфера
	printf("PRINT BRIGHTNESS FOR LED In range from 0 to 100->>>>!\r\n");
	HAL_UART_Receive_IT(&huart3, &value, 1); //запу�?каем UART по прерыванию

	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);


  /* USER CODE END 2 */

  /* Call init function for freertos objects (in freertos.c) */
  MX_FREERTOS_Init();

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	while (1)
	{
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
//		if (flag == 1)
//		{
//			sscanf(&buff[0], "%d", &str[0]);
//			if ((str[0] > 100) || (str[0] < 0))
//			{
//				printf("Error. Please enter correct value!\r\n");
//			}
//			else
//			{
//				active_brightness = str[0];
//				printf("You enter %d value\r\n", active_brightness);
//				printf(
//						"PRINT BRIGHTNESS FOR LED In range from 0 to 100->>>>!\r\n");
//			}
//			flag = 0;
//		}

//		btn_cur = HAL_GPIO_ReadPin(BUTTON_EXTI_GPIO_Port, BUTTON_EXTI_Pin);
//		switch (count)
//		{
//		case 0:
//		{
//			TIM2->CCR1 = off_brightness;
//			TIM2->CCR2 = off_brightness;
//		}
//			break;
//		case 1:
//		{
//			TIM2->CCR1 = active_brightness;
//			TIM2->CCR2 = off_brightness;
//
//		}
//			break;
//		case 2:
//		{
//			TIM2->CCR1 = off_brightness;
//			TIM2->CCR2 = active_brightness;
//		}
//			break;
//		case 3:
//		{
//			TIM2->CCR1 = active_brightness;
//			TIM2->CCR2 = active_brightness;
//		}
//			break;
//		}
//		HAL_Delay(5);
//		btn_prev = btn_cur;
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
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 180;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM6 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM6) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

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
