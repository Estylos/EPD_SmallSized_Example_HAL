/* USER CODE BEGIN Header */
/**
 * @file        main.c
 * @brief       EPD driver test program
 * @author      Esteban CADIC
 *              STMicroelectronics
 *              Pervasive Displays Inc
 * @version     1.0
 * @date        2024
 * @copyright   MIT License
 *
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "spi.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include "epd_driver.h"
#include "epd_screens.h"

/* DEMOS IMAGES FROM https://github.com/PervasiveDisplays/EPD_Driver_GF_small/ */
/* Screen Size: 154, 206, 213, 266, 271, 287, 290, 370, 417, 437 */
#define SCREEN 266
#include "../../Images/fastupdate_src/demoImageData.h"
#include "../../Images/globalupdate_src/demoImageData.h"

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

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
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
	MX_USART2_UART_Init();
	MX_SPI1_Init();
	/* USER CODE BEGIN 2 */

	ePaperDisplay_t epd;
	epd.spi = &hspi1;

	// CubeMX pin and port constants
	epd.panelBusy.pin = EPD_BUSY_Pin;
	epd.panelBusy.port = EPD_BUSY_GPIO_Port;

	epd.panelCS.pin = EPD_CS_Pin;
	epd.panelCS.port = EPD_CS_GPIO_Port;

	epd.panelDC.pin = EPD_DC_Pin;
	epd.panelDC.port = EPD_DC_GPIO_Port;

	epd.panelReset.pin = EPD_RST_Pin;
	epd.panelReset.port = EPD_RST_GPIO_Port;

	// Select the constants for your EPD (from epd_screens.h)
	epd.epdType = EPD_DISPLAY_266;
	epd.displaySizeH = EPD_DISPLAY_266_SIZE_H;
	epd.displaySizeV = EPD_DISPLAY_266_SIZE_V;

	epd.epdPSR[0] = EPD_DISPLAY_266_PSR0;
	epd.epdPSR[1] = EPD_DISPLAY_266_PSR1;

	// Initialize the COG for Global Update
	initializeGlobalUpdateCOG(&epd);

	// Make a Global Update
	globalUpdateDisplay(&epd, BW_monoBuffer, BW_0x00Buffer);

	// Power off the COG
	powerOffCOG(&epd);

	HAL_Delay(2000);

	// Initialize the COG for Fast Update
	initializeFastUpdateCOG(&epd);

	// Make some Fast Updates
	fastUpdateDisplay(&epd, FastPic_1, FastPic_b);
	fastUpdateDisplay(&epd, FastPic_b, FastPic_w);
	fastUpdateDisplay(&epd, FastPic_w, FastPic_2);
	fastUpdateDisplay(&epd, FastPic_2, FastPic_3);
	fastUpdateDisplay(&epd, FastPic_3, FastPic_4);

	HAL_Delay(2000);
	fastUpdateDisplay(&epd, FastPic_4, FastPic_b);
	fastUpdateDisplay(&epd, FastPic_b, FastPic_w);

	HAL_Delay(1000);
	powerOffCOG(&epd);

	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while(1)
	{
		HAL_GPIO_TogglePin(NUCLEO_LED_GPIO_Port, NUCLEO_LED_Pin);
		HAL_Delay(1000);

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
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
	RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL16;
	if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		Error_Handler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
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
	while(1)
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
