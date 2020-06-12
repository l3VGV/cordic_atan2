/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "math.h"

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
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

int __io_putchar(int ch)
{
 ITM_SendChar(ch);
 return(ch);
}

int _write(int file, char *ptr, int len)
 {
 int DataIdx;
 for (DataIdx = 0; DataIdx < len; DataIdx++)
 {
 __io_putchar(*ptr++);
 }
 return len;
 }


#define CORDIC_MAXITER 16
#define CORDIC_PI 0x10000000

int CORDIC_ZTBL[] = { 0x04000000, 0x025C80A4, 0x013F670B, 0x00A2223B,
		0x005161A8, 0x0028BAFC, 0x00145EC4, 0x000A2F8B, 0x000517CA, 0x00028BE6,
		0x000145F3, 0x0000A2FA, 0x0000517D, 0x000028BE, 0x0000145F, 0x00000A30 };

int fxpt_atan2(int y, int x) {
	int k, tx, z = 0, fl = 0;
	if (x < 0) {
		fl = ((y > 0) ? +1 : -1);
		x = -x;
		y = -y;
	}
	for (k = 0; k < CORDIC_MAXITER; k++) {
		tx = x;
		if (y <= 0) {
			x -= (y >> k);
			y += (tx >> k);
			z -= CORDIC_ZTBL[k];
		} else {
			x += (y >> k);
			y -= (tx >> k);
			z += CORDIC_ZTBL[k];
		}
	}

	if (fl != 0) {
		z += fl * CORDIC_PI;
	}
	return z;			// radians multiplied by factor M
	//*m = x; // sqrt(x^2+y^2) multiplied by gain F
}

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {
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
	/* USER CODE BEGIN 2 */
	volatile uint32_t startP, endP;
#define PI 3.1415926536897932384626f

	if (!(CoreDebug->DEMCR & CoreDebug_DEMCR_TRCENA_Msk)) {
		CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
		DWT->CYCCNT = 0;
		DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
	}

	for (int i = 0; i < 360; i += 1) {
		int16_t cs = 32767.0f * cos((float) i * PI / 180.0f);
		int16_t sn = 32767.0f * sin((float) i * PI / 180.0f);
		uint32_t atan2_clocks = 0;
		uint32_t atan2f_clocks = 0;
		uint32_t fxpt_at2_clocks = 0;

		startP = DWT->CYCCNT;
		int16_t at2f = 32767.0f * (float) atan2f((float) sn, (float) cs) / (PI);
		endP = DWT->CYCCNT;
		atan2f_clocks = endP - startP;

		startP = DWT->CYCCNT;
		int16_t fxpt_at2 = fxpt_atan2(sn << 15, cs << 15) >> 13;
		endP = DWT->CYCCNT;
		fxpt_at2_clocks = endP - startP;

		//float dif = 100.0f*abs(at2-fxpt_at2)/at2;

		int16_t iang = 2 * 32767.0f * i / 360.0f;

		printf(
				" angle = %i(%i), fxpt_atan2 = %i(%i), atan2f = %i(%i), sn= %i cs=%i \n",
				i, iang, fxpt_at2, fxpt_at2_clocks, at2f, atan2f_clocks, sn,
				cs);

		HAL_Delay(1);
	}

	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1) {
		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */
	}
	/* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

	/** Initializes the CPU, AHB and APB busses clocks
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}
	/** Initializes the CPU, AHB and APB busses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
		Error_Handler();
	}
}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void) {

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */

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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
