/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/*#include "moment_OL2_genC.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "rtwtypes.h"*/

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
uint8_t rxData[128];
int check = 0;
uint8_t rx_data_1[1];
float wheel_speed[4];
uint8_t rx_buffer[50];
uint8_t rx_index = 0;
uint8_t command;
float pwm[4];
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim4;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM3_Init(void);
static void MX_TIM4_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void PWM_3(int a, int b)
{
	if (a>0)
	{
	    __HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_1,0);
	    __HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_2,a);
	}
	else
	{
		__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_1,abs(a));
		__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_2,0);
	}
	if (b>0)
	{
		__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_3,0);
		__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_4,b);
    }
	else
	{
		__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_3,abs(b));
		__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_4,0);
	}
}
void PWM_4(int c, int d)
{
	if (c>0)
	{
	    __HAL_TIM_SetCompare(&htim4,TIM_CHANNEL_1,c);
	    __HAL_TIM_SetCompare(&htim4,TIM_CHANNEL_2,0);
	}
	else
	{
		__HAL_TIM_SetCompare(&htim4,TIM_CHANNEL_1,0);
		__HAL_TIM_SetCompare(&htim4,TIM_CHANNEL_2,abs(c));
	}
	if (d>0)
	{
		__HAL_TIM_SetCompare(&htim4,TIM_CHANNEL_3,d);
		__HAL_TIM_SetCompare(&htim4,TIM_CHANNEL_4,0);
	}
	else
	{
		__HAL_TIM_SetCompare(&htim4,TIM_CHANNEL_3,0);
		__HAL_TIM_SetCompare(&htim4,TIM_CHANNEL_4,abs(d));
	}
}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{

	if(huart->Instance == huart2.Instance)
	{
	    if (rx_data_1[0] == '\n')
	    {
	        char *token;
	        int wheel_index = 0;
	        token = strtok((char *)rx_buffer, ";");
	        while (token != NULL && wheel_index < 4)
	        {
	            wheel_speed[wheel_index++] = atof(token);
	            token = strtok(NULL, ";");
	        }
	        command = rx_buffer[0];

	        /*for (int i = 0; i < 4; i++)
	        {
	            if (wheel_speed[i] > 3.1416)
	            {
	                wheel_speed[i] = 3.1416;
	            }

	            if (wheel_speed[i] < -3.1416)
	            {
	                wheel_speed[i] = -3.1416;
	            }
	        }*/

	        pwm[0] = (wheel_speed[0]/11.5192)*999;
	        pwm[1] = (wheel_speed[1]/11.5192)*999;
	        pwm[2] = (wheel_speed[2]/11.5192)*999;
	        pwm[3] = (wheel_speed[3]/11.5192)*999;
	        PWM_3((int)pwm[0],(int)pwm[3]);
	        PWM_4((int)pwm[1],(int)pwm[2]);
	        //HAL_UART_Transmit(&huart2, (uint8_t *)wheel_speed, sizeof(wheel_speed), HAL_MAX_DELAY);
	        memset(rx_buffer, 0, 50);
	        rx_index = 0;
	        HAL_UART_Receive_IT(&huart2, rx_data_1, 1);
	    }
	    else
	    {
	        rx_buffer[rx_index++] = rx_data_1[0];
	        HAL_UART_Receive_IT(&huart2, rx_data_1, 1);
	    }

	    if (command == 'f')
	    {
	    	PWM_3(200,200);
	    	PWM_4(200,200);
	    	HAL_UART_Receive_IT(&huart2, rx_data_1, 1);
	    }
	    else if (command == 'b')
	    {
	    	PWM_3(-200,-200);
	    	PWM_4(-200,-200);
	    	HAL_UART_Receive_IT(&huart2, rx_data_1, 1);
	    }
	    else if (command == 'l')
	    {
	    	PWM_3(-200,200);
	    	PWM_4(200,-200);
	    	HAL_UART_Receive_IT(&huart2, rx_data_1, 1);
	    }
	    else if (command == 'r')
	    {
	    	PWM_3(200,-200);
	    	PWM_4(-200,200);
	    	HAL_UART_Receive_IT(&huart2, rx_data_1, 1);
	    }
	    else if (command == 's')
	    {
	    	PWM_3(0,0);
	    	PWM_4(0,0);
	    	HAL_UART_Receive_IT(&huart2, rx_data_1, 1);
	    }
	    else if (command == 'a')
	    {
	    	PWM_3(0,200);
	    	PWM_4(200,0);
	    	HAL_UART_Receive_IT(&huart2, rx_data_1, 1);
	    }
	    else if (command == 'c')
	    {
	    	PWM_3(200,0);
	    	PWM_4(0,200);
	    	HAL_UART_Receive_IT(&huart2, rx_data_1, 1);
	    }
	    else if (command == 'd')
	    {
	    	PWM_3(-200,0);
	    	PWM_4(0,-200);
	    	HAL_UART_Receive_IT(&huart2, rx_data_1, 1);
	    }
	    else if (command == 'e')
	    {
	    	PWM_3(0,-200);
	    	PWM_4(-200,0);
	    	HAL_UART_Receive_IT(&huart2, rx_data_1, 1);
	    }
	    else if (command == 'g')
	    {
	    	PWM_3(-200,-200);
	    	PWM_4(200,200);
	    	HAL_UART_Receive_IT(&huart2, rx_data_1, 1);
	    }
	    else if (command == 'h')
	    {
	    	PWM_3(200,200);
	    	PWM_4(-200,-200);
	    	HAL_UART_Receive_IT(&huart2, rx_data_1, 1);
	    }

        /*switch (command) {
            case 'f':
                PWM_3(500,500);
                PWM_4(500,500);
                //check++;
                break;
            case 'b':
        	    PWM_3(-500,-500);
        	    PWM_4(-500,-500);
                break;
            case 'l':
        	    PWM_3(500,-500);
        	    PWM_4(-500,500);
                break;
            case 'r':
        	    PWM_3(-500,500);
        	    PWM_4(500,-500);
                break;
            case 's':
        	    PWM_3(0,0);
        	    PWM_4(0,0);
                break;
            default:
        	    PWM_3(0,0);
        	    PWM_4(0,0);
                break;
        }
        HAL_UART_Receive_IT(&huart2, &rx_data_1, 1);*/
	}

}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */
//moment_OL2_genC_initialize();
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
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_2);
  HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_3);
  HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_4);
  HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_2);
  HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_3);
  HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_4);


  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, SET);
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, SET);
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, SET);
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, SET);
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, SET);
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, SET);
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, SET);
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, SET);

  HAL_UART_Receive_IT(&huart2, rx_data_1, 1);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */


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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 71;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 999;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */
  HAL_TIM_MspPostInit(&htim3);

}

/**
  * @brief TIM4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM4_Init(void)
{

  /* USER CODE BEGIN TIM4_Init 0 */

  /* USER CODE END TIM4_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM4_Init 1 */

  /* USER CODE END TIM4_Init 1 */
  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 71;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 999;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_PWM_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM4_Init 2 */

  /* USER CODE END TIM4_Init 2 */
  HAL_TIM_MspPostInit(&htim4);

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13
                          |GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8|GPIO_PIN_9, GPIO_PIN_RESET);

  /*Configure GPIO pins : PB10 PB11 PB12 PB13
                           PB14 PB15 */
  GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13
                          |GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PA8 PA9 */
  GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
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
