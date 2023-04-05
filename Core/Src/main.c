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
#include "usb_device.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "usbd_hid.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
extern USBD_HandleTypeDef hUsbDeviceFS;
keyboardReportDes HIDKeyboardReport = {0, 0, 0, 0, 0, 0, 0, 0};
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */
void type(uint8_t c);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void type(uint8_t c) {
	if (c >= 0x41 && c <= 0x5A) {
		// Letra maiúscula
		HIDKeyboardReport.modifier = 0x02; //SHIFT
		HIDKeyboardReport.keyCode1 = c - 0x3D;
		USBD_HID_SendReport(&hUsbDeviceFS, (uint8_t *)&HIDKeyboardReport, sizeof(HIDKeyboardReport));
		HAL_Delay(15);
		// Liberar teclas
		HIDKeyboardReport.modifier = 0x00;
		HIDKeyboardReport.keyCode1 = 0x00;
		USBD_HID_SendReport(&hUsbDeviceFS, (uint8_t *)&HIDKeyboardReport, sizeof(HIDKeyboardReport));
	} else if (c >= 0x61 && c <= 0x7A) {
		// Letra minúscula
		HIDKeyboardReport.keyCode1 = c - 0x5D;
		USBD_HID_SendReport(&hUsbDeviceFS, (uint8_t *)&HIDKeyboardReport, sizeof(HIDKeyboardReport));
		HAL_Delay(15);
		// Liberar tecla
		HIDKeyboardReport.keyCode1 = 0x00;
		USBD_HID_SendReport(&hUsbDeviceFS, (uint8_t *)&HIDKeyboardReport, sizeof(HIDKeyboardReport));
	} else if (c >= 0x31 && c <= 0x39) {
		// Dígito de 1 a 9
		HIDKeyboardReport.keyCode1 = c - 0x13;
		USBD_HID_SendReport(&hUsbDeviceFS, (uint8_t *)&HIDKeyboardReport, sizeof(HIDKeyboardReport));
		HAL_Delay(15);
		// Liberar tecla
		HIDKeyboardReport.keyCode1 = 0x00;
		USBD_HID_SendReport(&hUsbDeviceFS, (uint8_t *)&HIDKeyboardReport, sizeof(HIDKeyboardReport));
	} else if (c == 0x30) {
		// Dígito 0
		HIDKeyboardReport.keyCode1 = 0x27;
		USBD_HID_SendReport(&hUsbDeviceFS, (uint8_t *)&HIDKeyboardReport, sizeof(HIDKeyboardReport));
		HAL_Delay(15);
		// Liberar tecla
		HIDKeyboardReport.keyCode1 = 0x00;
		USBD_HID_SendReport(&hUsbDeviceFS, (uint8_t *)&HIDKeyboardReport, sizeof(HIDKeyboardReport));
	} else if (c == 0x20) {
		// Espaço
		HIDKeyboardReport.keyCode1 = 0x2C;
		USBD_HID_SendReport(&hUsbDeviceFS, (uint8_t *)&HIDKeyboardReport, sizeof(HIDKeyboardReport));
		HAL_Delay(15);
		// Liberar tecla
		HIDKeyboardReport.keyCode1 = 0x00;
		USBD_HID_SendReport(&hUsbDeviceFS, (uint8_t *)&HIDKeyboardReport, sizeof(HIDKeyboardReport));
	} else if (c == 0x0D) {
		// ENTER
		HIDKeyboardReport.keyCode1 = 0x28;
		USBD_HID_SendReport(&hUsbDeviceFS, (uint8_t *)&HIDKeyboardReport, sizeof(HIDKeyboardReport));
		HAL_Delay(15);
		// Liberar tecla
		HIDKeyboardReport.keyCode1 = 0x00;
		USBD_HID_SendReport(&hUsbDeviceFS, (uint8_t *)&HIDKeyboardReport, sizeof(HIDKeyboardReport));
	} else if (c == 0x1B) {
		// ESC
		HIDKeyboardReport.keyCode1 = 0x29;
		USBD_HID_SendReport(&hUsbDeviceFS, (uint8_t *)&HIDKeyboardReport, sizeof(HIDKeyboardReport));
		HAL_Delay(15);
		// Liberar tecla
		HIDKeyboardReport.keyCode1 = 0x00;
		USBD_HID_SendReport(&hUsbDeviceFS, (uint8_t *)&HIDKeyboardReport, sizeof(HIDKeyboardReport));
	} else if (c == 0x09) {
		// TAB
		HIDKeyboardReport.keyCode1 = 0x2B;
		USBD_HID_SendReport(&hUsbDeviceFS, (uint8_t *)&HIDKeyboardReport, sizeof(HIDKeyboardReport));
		HAL_Delay(15);
		// Liberar tecla
		HIDKeyboardReport.keyCode1 = 0x00;
		USBD_HID_SendReport(&hUsbDeviceFS, (uint8_t *)&HIDKeyboardReport, sizeof(HIDKeyboardReport));
	} else if (c == 0x7F) {
		// BACKSPACE
		HIDKeyboardReport.keyCode1 = 0x2A;
		USBD_HID_SendReport(&hUsbDeviceFS, (uint8_t *)&HIDKeyboardReport, sizeof(HIDKeyboardReport));
		HAL_Delay(15);
		// Liberar tecla
		HIDKeyboardReport.keyCode1 = 0x00;
		USBD_HID_SendReport(&hUsbDeviceFS, (uint8_t *)&HIDKeyboardReport, sizeof(HIDKeyboardReport));
	} else if (c == 0x2D) {
		// -
		HIDKeyboardReport.keyCode1 = 0x2D;
		USBD_HID_SendReport(&hUsbDeviceFS, (uint8_t *)&HIDKeyboardReport, sizeof(HIDKeyboardReport));
		HAL_Delay(15);
		// Liberar tecla
		HIDKeyboardReport.keyCode1 = 0x00;
		USBD_HID_SendReport(&hUsbDeviceFS, (uint8_t *)&HIDKeyboardReport, sizeof(HIDKeyboardReport));
	} else if (c == 0x2E) {
		// .
		HIDKeyboardReport.keyCode1 = 0x37;
		USBD_HID_SendReport(&hUsbDeviceFS, (uint8_t *)&HIDKeyboardReport, sizeof(HIDKeyboardReport));
		HAL_Delay(15);
		// Liberar tecla
		HIDKeyboardReport.keyCode1 = 0x00;
		USBD_HID_SendReport(&hUsbDeviceFS, (uint8_t *)&HIDKeyboardReport, sizeof(HIDKeyboardReport));
	} else if (c == 0x2F) {
		// Barra
		HIDKeyboardReport.keyCode1 = 0x38;
		USBD_HID_SendReport(&hUsbDeviceFS, (uint8_t *)&HIDKeyboardReport, sizeof(HIDKeyboardReport));
		HAL_Delay(15);
		// Liberar tecla
		HIDKeyboardReport.keyCode1 = 0x00;
		USBD_HID_SendReport(&hUsbDeviceFS, (uint8_t *)&HIDKeyboardReport, sizeof(HIDKeyboardReport));
	} else if (c == 0x5C) {
		// Barra invertida
		HIDKeyboardReport.keyCode1 = 0x31;
		USBD_HID_SendReport(&hUsbDeviceFS, (uint8_t *)&HIDKeyboardReport, sizeof(HIDKeyboardReport));
		HAL_Delay(15);
		// Liberar tecla
		HIDKeyboardReport.keyCode1 = 0x00;
		USBD_HID_SendReport(&hUsbDeviceFS, (uint8_t *)&HIDKeyboardReport, sizeof(HIDKeyboardReport));
	} else if (c == 0x3D) {
		// =
		HIDKeyboardReport.keyCode1 = 0x2E;
		USBD_HID_SendReport(&hUsbDeviceFS, (uint8_t *)&HIDKeyboardReport, sizeof(HIDKeyboardReport));
		HAL_Delay(15);
		// Liberar tecla
		HIDKeyboardReport.keyCode1 = 0x00;
		USBD_HID_SendReport(&hUsbDeviceFS, (uint8_t *)&HIDKeyboardReport, sizeof(HIDKeyboardReport));
	} else if (c == 0x27) {
		// Aspa simples
		HIDKeyboardReport.keyCode1 = 0x34;
		USBD_HID_SendReport(&hUsbDeviceFS, (uint8_t *)&HIDKeyboardReport, sizeof(HIDKeyboardReport));
		HAL_Delay(15);
		// Liberar tecla
		HIDKeyboardReport.keyCode1 = 0x00;
		USBD_HID_SendReport(&hUsbDeviceFS, (uint8_t *)&HIDKeyboardReport, sizeof(HIDKeyboardReport));
	} else if (c == 0x5F) {
		// _
		HIDKeyboardReport.modifier = 0x02; //SHIFT
		HIDKeyboardReport.keyCode1 = 0x2D;
		USBD_HID_SendReport(&hUsbDeviceFS, (uint8_t *)&HIDKeyboardReport, sizeof(HIDKeyboardReport));
		HAL_Delay(15);
		// Liberar teclas
		HIDKeyboardReport.modifier = 0x00;
		HIDKeyboardReport.keyCode1 = 0x00;
		USBD_HID_SendReport(&hUsbDeviceFS, (uint8_t *)&HIDKeyboardReport, sizeof(HIDKeyboardReport));
	} else if (c == 0x7E) {
		// ~
		HIDKeyboardReport.modifier = 0x02; //SHIFT
		HIDKeyboardReport.keyCode1 = 0x35;
		USBD_HID_SendReport(&hUsbDeviceFS, (uint8_t *)&HIDKeyboardReport, sizeof(HIDKeyboardReport));
		HAL_Delay(15);
		// Liberar teclas
		HIDKeyboardReport.modifier = 0x00;
		HIDKeyboardReport.keyCode1 = 0x00;
		USBD_HID_SendReport(&hUsbDeviceFS, (uint8_t *)&HIDKeyboardReport, sizeof(HIDKeyboardReport));
	} else if (c == 0x3C) {
		// <
		HIDKeyboardReport.modifier = 0x02; //SHIFT
		HIDKeyboardReport.keyCode1 = 0x36;
		USBD_HID_SendReport(&hUsbDeviceFS, (uint8_t *)&HIDKeyboardReport, sizeof(HIDKeyboardReport));
		HAL_Delay(15);
		// Liberar teclas
		HIDKeyboardReport.modifier = 0x00;
		HIDKeyboardReport.keyCode1 = 0x00;
		USBD_HID_SendReport(&hUsbDeviceFS, (uint8_t *)&HIDKeyboardReport, sizeof(HIDKeyboardReport));
	} else if (c == 0x3E) {
		// >
		HIDKeyboardReport.modifier = 0x02; //SHIFT
		HIDKeyboardReport.keyCode1 = 0x37;
		USBD_HID_SendReport(&hUsbDeviceFS, (uint8_t *)&HIDKeyboardReport, sizeof(HIDKeyboardReport));
		HAL_Delay(15);
		// Liberar teclas
		HIDKeyboardReport.modifier = 0x00;
		HIDKeyboardReport.keyCode1 = 0x00;
		USBD_HID_SendReport(&hUsbDeviceFS, (uint8_t *)&HIDKeyboardReport, sizeof(HIDKeyboardReport));
	} else if (c == 0x2A) {
		// Asterisco
		HIDKeyboardReport.modifier = 0x02; //SHIFT
		HIDKeyboardReport.keyCode1 = 0x25;
		USBD_HID_SendReport(&hUsbDeviceFS, (uint8_t *)&HIDKeyboardReport, sizeof(HIDKeyboardReport));
		HAL_Delay(15);
		// Liberar teclas
		HIDKeyboardReport.modifier = 0x00;
		HIDKeyboardReport.keyCode1 = 0x00;
		USBD_HID_SendReport(&hUsbDeviceFS, (uint8_t *)&HIDKeyboardReport, sizeof(HIDKeyboardReport));
	} else if (c == 0x22) {
		// Aspas duplas
		HIDKeyboardReport.modifier = 0x02; //SHIFT
		HIDKeyboardReport.keyCode1 = 0x34;
		USBD_HID_SendReport(&hUsbDeviceFS, (uint8_t *)&HIDKeyboardReport, sizeof(HIDKeyboardReport));
		HAL_Delay(15);
		// Liberar teclas
		HIDKeyboardReport.modifier = 0x00;
		HIDKeyboardReport.keyCode1 = 0x00;
		USBD_HID_SendReport(&hUsbDeviceFS, (uint8_t *)&HIDKeyboardReport, sizeof(HIDKeyboardReport));
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
  MX_USB_DEVICE_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  uint8_t c = 0x00;
	  HAL_UART_Receive(&huart2, &c, 1, 5000); //Bloqueia até receber um caracter
	  if (c) {
		  uint8_t buffer[100];
		  snprintf((char *)buffer, 100, "Rx 0x%02X\n", c);
		  HAL_UART_Transmit(&huart2, buffer, strlen((char *)buffer), 10);
		  type(c);
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
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 15;
  RCC_OscInitStruct.PLL.PLLN = 144;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 5;
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

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
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
  huart2.Init.BaudRate = 9600;
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
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

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
