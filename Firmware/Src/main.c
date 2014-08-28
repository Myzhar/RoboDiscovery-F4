/**
  ******************************************************************************
  * File Name          : main.c
  * Date               : 28/08/2014 17:15:59
  * Description        : Main program body
  ******************************************************************************
  *
  * COPYRIGHT(c) 2014 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "dma.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "usb_device.h"
#include "gpio.h"

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN 0 */
#include "leds_handler.h"
#include "button_handler.h"	
#include "tim_handler.h"

static uint64_t ticks=0;
/* USER CODE END 0 */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

int main(void)
{

  /* USER CODE BEGIN 1 */
	ticks = 0;
	
  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* System interrupt init*/
  /* Sets the priority grouping field */
  HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_0);
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_I2C2_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM7_Init();
  MX_TIM11_Init();
  MX_TIM12_Init();
  //MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_USB_DEVICE_Init();

  /* USER CODE BEGIN 2 */
	volatile uint8_t led_idx = 0;
	volatile uint8_t color_idx = 0;
	
	volatile uint8_t but1_count = 0;
	volatile uint8_t but2_count = 0;
	volatile uint8_t but_disc_count = 0;
	
	LedColor color;
	
	initRgbLeds();	
	
	HAL_TIM_IC_Start_IT( &htim12, TIM_CHANNEL_2 );
  /* USER CODE END 2 */

  /* USER CODE BEGIN 3 */
	/* Infinite loop */	
	while (1)
	{			
		uint8_t set = 0;
		
		if( getButton1State() == BUT_PRESSED )
			but1_count++;
		else
			but1_count = 0;
		
		if( getButton2State() == BUT_PRESSED )
			but2_count++;
		else
			but2_count = 0;
		
		if( getButtonDiscState() == BUT_PRESSED )
			but_disc_count++;
		else
			but_disc_count = 0;
		
		/*if( but1_count==2 )
		{
			but1_count = 0;
			
			led_idx++;
			if( led_idx ==16 )
				led_idx=0;
			
			set = 1;
		}
		
		if( but2_count==2 )
		{
			but2_count = 0;
			
			color_idx++;
			if( color_idx > 7 )
				color_idx=0;
			
			switch(color_idx)
			{
			case 0:
				color.R = 0;
				color.G = 0;
				color.B = 0;
				break;
			case 1:
				color.R = 255;
				color.G = 0;
				color.B = 0;
				break;
			case 2:
				color.R = 0;
				color.G = 255;
				color.B = 0;
				break;
			case 3:
				color.R = 0;
				color.G = 0;
				color.B = 255;
				break;
			case 4:
				color.R = 0;
				color.G = 255;
				color.B = 255;
				break;
			case 5:
				color.R = 255;
				color.G = 255;
				color.B = 0;
				break;
			case 6:
				color.R = 255;
				color.G = 0;
				color.B = 255;
				break;
			case 7:
				color.R = 255;
				color.G = 255;
				color.B = 255;
				break;
			}
			
			set = 1;
		}			
		
		if( set==1 )
		{
			for( int i=0; i<16; i++ )
			{
				if( i==led_idx)
					setLedColor( i, color );
				else
				{
					LedColor black;
					black.R = 0;
					black.G = 0;
					black.B = 0;
					setLedColor( i, black );
				}
			}
		}*/
		
		// MUX on output 0 for Sonar 1
		HAL_GPIO_WritePin( GPIOA, GPIO_PIN_10, GPIO_PIN_RESET );
		HAL_GPIO_WritePin( GPIOA, GPIO_PIN_9, GPIO_PIN_RESET );
		HAL_GPIO_WritePin( GPIOA, GPIO_PIN_8, GPIO_PIN_RESET );
		HAL_GPIO_WritePin( GPIOC, GPIO_PIN_9, GPIO_PIN_RESET );
		HAL_GPIO_WritePin( GPIOC, GPIO_PIN_8, GPIO_PIN_RESET );
		
		// Trigger on Sonar Pulse
		HAL_TIM_PWM_Start( &htim11, TIM_CHANNEL_1 );
		
		HAL_Delay(100);	
	}
  /* USER CODE END 3 */

}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  __PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_SYSCLK|RCC_CLOCKTYPE_PCLK1
                              |RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);

  HAL_RCC_EnableCSS();

}

/* USER CODE BEGIN 4 */
void HAL_SYSTICK_Callback(void)
{
	ticks++;
}

/* USER CODE END 4 */

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
/* User can add his own implementation to report the file name and line number,
ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
