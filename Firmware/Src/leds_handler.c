#include "leds_handler.h"

#define TR_S1_R 0
#define TR_S1_G 1
#define TR_S1_B 2
#define TR_S2_R 3
#define TR_S2_G 4
#define TR_S2_B 5

void initLeds(void)
{	
	// All the leds (inluded the 4 on Discovery Board) are on PORTD
	HAL_GPIO_WritePin( GPIOD, GPIO_PIN_All, GPIO_PIN_SET );
}

void setLedDiscRed( uint8_t state )
{
	if( state==LED_ON ) 
		HAL_GPIO_WritePin( GPIOD, GPIO_PIN_14, GPIO_PIN_RESET );
	else
		HAL_GPIO_WritePin( GPIOD, GPIO_PIN_14, GPIO_PIN_SET );
}

void toggleLedDiscRed( void )
{
	GPIOD->ODR ^= GPIO_PIN_14;
}

void setLedDiscBlue( uint8_t state )
{
	if( state==LED_ON ) 
		HAL_GPIO_WritePin( GPIOD, GPIO_PIN_15, GPIO_PIN_RESET );
	else
		HAL_GPIO_WritePin( GPIOD, GPIO_PIN_15, GPIO_PIN_SET );
}

void toggleLedDiscBlue( void )
{
	GPIOD->ODR ^= GPIO_PIN_15;
}

void setStateLedColor( uint8_t ledIdx, uint8_t color )
{
	if( ledIdx>15 )
		return;
			
	uint8_t pin = ledIdx/2 + ledIdx%2;
	uint16_t pinK_idx;
	if( pin==0 )
		pinK_idx = GPIO_PIN_6;
	else if( pin==1 )
		pinK_idx = GPIO_PIN_7;
	else if( pin==2 )
		pinK_idx = GPIO_PIN_8;
	else if( pin==3 )
		pinK_idx = GPIO_PIN_9;
	else if( pin==4 )
		pinK_idx = GPIO_PIN_10;
	else if( pin==5 )
		pinK_idx = GPIO_PIN_11;
	else if( pin==6 )
		pinK_idx = GPIO_PIN_12;
	else if( pin==7 )
		pinK_idx = GPIO_PIN_13;
	
	HAL_GPIO_WritePin( GPIOD, pinK_idx, GPIO_PIN_RESET );
	
	
	switch(color)
	{
		case LED_RED:
		{
			if( ledIdx%2 == 0 )
			{
				HAL_GPIO_WritePin( GPIOD, TR_S1_R, GPIO_PIN_RESET );
				HAL_GPIO_WritePin( GPIOD, TR_S1_G, GPIO_PIN_SET );
				HAL_GPIO_WritePin( GPIOD, TR_S1_B, GPIO_PIN_SET );
			}
			else
			{
				HAL_GPIO_WritePin( GPIOD, TR_S2_R, GPIO_PIN_RESET );
				HAL_GPIO_WritePin( GPIOD, TR_S2_G, GPIO_PIN_SET );
				HAL_GPIO_WritePin( GPIOD, TR_S2_B, GPIO_PIN_SET );
			}					
		}
		break;
		
		case LED_GREEN:
		{
			if( ledIdx%2 == 0 )
			{
				HAL_GPIO_WritePin( GPIOD, TR_S1_R, GPIO_PIN_SET );
				HAL_GPIO_WritePin( GPIOD, TR_S1_G, GPIO_PIN_RESET );
				HAL_GPIO_WritePin( GPIOD, TR_S1_B, GPIO_PIN_SET );
			}
			else
			{
				HAL_GPIO_WritePin( GPIOD, TR_S2_R, GPIO_PIN_SET );
				HAL_GPIO_WritePin( GPIOD, TR_S2_G, GPIO_PIN_RESET );
				HAL_GPIO_WritePin( GPIOD, TR_S2_B, GPIO_PIN_SET );
			}					
		}
		break;
		
		case LED_BLUE:
		{
			if( ledIdx%2 == 0 )
			{
				HAL_GPIO_WritePin( GPIOD, TR_S1_R, GPIO_PIN_SET );
				HAL_GPIO_WritePin( GPIOD, TR_S1_G, GPIO_PIN_SET );
				HAL_GPIO_WritePin( GPIOD, TR_S1_B, GPIO_PIN_RESET );
			}
			else
			{
				HAL_GPIO_WritePin( GPIOD, TR_S2_R, GPIO_PIN_SET );
				HAL_GPIO_WritePin( GPIOD, TR_S2_G, GPIO_PIN_SET );
				HAL_GPIO_WritePin( GPIOD, TR_S2_B, GPIO_PIN_RESET );
			}					
		}
		break;
		
		case LED_YELLOW:
		{
			if( ledIdx%2 == 0 )
			{
				HAL_GPIO_WritePin( GPIOD, TR_S1_R, GPIO_PIN_RESET );
				HAL_GPIO_WritePin( GPIOD, TR_S1_G, GPIO_PIN_RESET );
				HAL_GPIO_WritePin( GPIOD, TR_S1_B, GPIO_PIN_SET );
			}
			else
			{
				HAL_GPIO_WritePin( GPIOD, TR_S2_R, GPIO_PIN_RESET );
				HAL_GPIO_WritePin( GPIOD, TR_S2_G, GPIO_PIN_RESET );
				HAL_GPIO_WritePin( GPIOD, TR_S2_B, GPIO_PIN_SET );
			}					
		}
		break;
		
		case LED_PURPLE:
		{
			if( ledIdx%2 == 0 )
			{
				HAL_GPIO_WritePin( GPIOD, TR_S1_R, GPIO_PIN_RESET );
				HAL_GPIO_WritePin( GPIOD, TR_S1_G, GPIO_PIN_SET );
				HAL_GPIO_WritePin( GPIOD, TR_S1_B, GPIO_PIN_RESET );
			}
			else
			{
				HAL_GPIO_WritePin( GPIOD, TR_S2_R, GPIO_PIN_RESET );
				HAL_GPIO_WritePin( GPIOD, TR_S2_G, GPIO_PIN_SET );
				HAL_GPIO_WritePin( GPIOD, TR_S2_B, GPIO_PIN_RESET );
			}					
		}
		break;
		
		case LED_CYAN:
		{
			if( ledIdx%2 == 0 )
			{
				HAL_GPIO_WritePin( GPIOD, TR_S1_R, GPIO_PIN_SET );
				HAL_GPIO_WritePin( GPIOD, TR_S1_G, GPIO_PIN_RESET );
				HAL_GPIO_WritePin( GPIOD, TR_S1_B, GPIO_PIN_RESET );
			}
			else
			{
				HAL_GPIO_WritePin( GPIOD, TR_S2_R, GPIO_PIN_SET );
				HAL_GPIO_WritePin( GPIOD, TR_S2_G, GPIO_PIN_RESET );
				HAL_GPIO_WritePin( GPIOD, TR_S2_B, GPIO_PIN_RESET );
			}					
		}
		break;
		
		case LED_WHITE:
		{
			if( ledIdx%2 == 0 )
			{
				HAL_GPIO_WritePin( GPIOD, TR_S1_R, GPIO_PIN_RESET );
				HAL_GPIO_WritePin( GPIOD, TR_S1_G, GPIO_PIN_RESET );
				HAL_GPIO_WritePin( GPIOD, TR_S1_B, GPIO_PIN_RESET );
			}
			else
			{
				HAL_GPIO_WritePin( GPIOD, TR_S2_R, GPIO_PIN_RESET );
				HAL_GPIO_WritePin( GPIOD, TR_S2_G, GPIO_PIN_RESET );
				HAL_GPIO_WritePin( GPIOD, TR_S2_B, GPIO_PIN_RESET );
			}					
		}
		break;
		
		case LED_BLACK:
		{
			if( ledIdx%2 == 0 )
			{
				HAL_GPIO_WritePin( GPIOD, TR_S1_R, GPIO_PIN_SET );
				HAL_GPIO_WritePin( GPIOD, TR_S1_G, GPIO_PIN_SET );
				HAL_GPIO_WritePin( GPIOD, TR_S1_B, GPIO_PIN_SET );
			}
			else
			{
				HAL_GPIO_WritePin( GPIOD, TR_S2_R, GPIO_PIN_SET );
				HAL_GPIO_WritePin( GPIOD, TR_S2_G, GPIO_PIN_SET );
				HAL_GPIO_WritePin( GPIOD, TR_S2_B, GPIO_PIN_SET );
			}					
		}
		break;
	}
}
