#include "tim_handler.h"
#include "leds_handler.h"

// Callback for Timer timeout
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance==TIM7)
	{
		on_RGB_led_timer_timeout();
	}
}

uint32_t ic_val;
uint32_t range_mm; 
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	ic_val = HAL_TIM_ReadCapturedValue( htim, TIM_CHANNEL_2 );	
	range_mm = (int)((float)ic_val*0.175f+0.5f);
	
	LedColor green;
	green.R = 0;
	green.G = 255;
	green.B = 0;
	
	LedColor red;
	red.R = 255;
	red.G = 0;
	red.B = 0;
	
	if( range_mm < 500 ) 
		setLedColor( 0, red );
	else
		setLedColor( 0, green );
}
