#include "button_handler.h"

uint8_t getButtonDiscState()
{
	GPIO_PinState state = HAL_GPIO_ReadPin( GPIOA, GPIO_PIN_0 );
	if( state == GPIO_PIN_SET )
		return BUT_PRESSED;
	else
		return BUT_RELEASED;
	
}
	
uint8_t getButton1State()
{
	return HAL_GPIO_ReadPin( GPIOB, GPIO_PIN_12 );
}

uint8_t getButton2State()
{
	return HAL_GPIO_ReadPin( GPIOB, GPIO_PIN_13 );
}
