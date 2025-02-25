/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "i2c.h"
#include "usb_device.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define MPU6050_ADDR 0xD0
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
extern uint8_t CDC_Transmit_FS(uint8_t* Buf, uint16_t Len);

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
  MX_I2C1_Init();
  MX_USB_DEVICE_Init();
  /* USER CODE BEGIN 2 */

  uint8_t result = 0x0;
  HAL_I2C_Mem_Read (&hi2c1, MPU6050_ADDR, 0x75, 1, &result, 1, 100);
  HAL_Delay (1000);

  if (result == 0x68) {
	  uint8_t send[] = "the device was found\r\n";
	  CDC_Transmit_FS (send, (uint16_t)sizeof(send));
	  HAL_Delay (10);
	  uint8_t data;
	  data = 0x00;
	  HAL_I2C_Mem_Write (&hi2c1, MPU6050_ADDR, 0x6B, 1, &data, 1, 500); //initialize mpu clock
	  data = 0x07;
	  HAL_I2C_Mem_Write (&hi2c1, MPU6050_ADDR, 0x19, 1, &data, 1, 500); //measurement poll rate of 1 khz
	  data = 0b00001000;
	  HAL_I2C_Mem_Write (&hi2c1, MPU6050_ADDR, 0x1C, 1, &data, 1, 500); //accel set to [-4g, 4g]
	  data = 0x00;
	  HAL_I2C_Mem_Write (&hi2c1, MPU6050_ADDR, 0x1B, 1, &data, 1, 500); //gyro set to [-250degree/sec, 250degree/sec]
  } else {
	  uint8_t send[] = "          \r\n";
	  itoa(result, (char*)send, 10);
	  HAL_Delay (10);
	  CDC_Transmit_FS (send, sizeof(send));
	  HAL_Delay (10);
	  uint8_t errormessage[] = "there was an error\r\n";
	  CDC_Transmit_FS (errormessage, sizeof(errormessage));
	  HAL_Delay (10);
  }

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  //HAL_GPIO_TogglePin (GPIOC, GPIO_PIN_13);
	  //HAL_Delay (150);

	  uint8_t acceldata[] = {0, 0, 0, 0, 0, 0};
	  HAL_I2C_Mem_Read (&hi2c1, MPU6050_ADDR, 0x3B, 1, acceldata, 6, 1000);
	  HAL_Delay(100);
	  if ((acceldata[2] == 0) && (acceldata[3] == 0)) {
		  uint8_t erroraccel[] = "error getting data\r\n";
		  CDC_Transmit_FS (erroraccel, sizeof(erroraccel));
	  }
	  int16_t rawx = (uint16_t)(acceldata[0] << 8 | acceldata[1]);
	  int16_t rawy = (uint16_t)(acceldata[2] << 8 | acceldata[3]);
	  int16_t rawz = (uint16_t)(acceldata[4] << 8 | acceldata[5]);
	  HAL_Delay(50);
	  uint8_t bufferx[] = "        : x\r\n";
	  uint8_t buffery[] = "        : y\r\n";
	  uint8_t bufferz[] = "        : z\r\n\r\n";
	  itoa(rawx, (char*)bufferx, 10);
	  itoa(rawy, (char*)buffery, 10);
	  itoa(rawz, (char*)bufferz, 10);
	  CDC_Transmit_FS (bufferx, sizeof(bufferx));
	  HAL_Delay(2);
	  CDC_Transmit_FS (buffery, sizeof(buffery));
	  HAL_Delay(2);
	  CDC_Transmit_FS (bufferz, sizeof(bufferz));
	  HAL_Delay(20);

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
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 7;
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
