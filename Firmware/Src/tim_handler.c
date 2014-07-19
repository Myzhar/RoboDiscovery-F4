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
