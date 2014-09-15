#include "sonar_handler.h"

// >>>>> Public variables
uint32_t sonar_mm_vec[MAX_SONAR_COUNT];
// <<<<< Public variables

// >>>>> Private variables
static uint32_t ic_val;
static uint32_t last_range_mm; 

static uint8_t sonar_active;

static TIM_HandleTypeDef *pulseTIM;
static TIM_HandleTypeDef *echoTIM;

static LedColor green;	
static LedColor yellow;	
static LedColor red;

static uint32_t warning_rad_mm;
static uint32_t danger_rad_mm;

#define NO_SONAR_ACTIVE 20
// <<<<< Private variables

void initSonars( TIM_HandleTypeDef* optPulseTIM, TIM_HandleTypeDef* optEchoTIM )
{
	warning_rad_mm = 1000;
	danger_rad_mm = 500;
	
	green.R = 0;
	green.G = 255;
	green.B = 0;
	
	yellow.R = 0;
	yellow.G = 255;
	yellow.B = 255;
	
	red.R = 255;
	red.G = 0;
	red.B = 0;
	
	for( int i=0; i<MAX_SONAR_COUNT; i++ )
		sonar_mm_vec[i] = MEAS_NOT_VALID;
	
	pulseTIM = optPulseTIM;
	echoTIM = optEchoTIM;
	
	HAL_TIM_IC_Start_IT( echoTIM, TIM_CHANNEL_2 );	
	
	sonar_active = NO_SONAR_ACTIVE;
}

void setAreaLimits( uint32_t danger_mm, uint32_t warning_mm)
{
	warning_rad_mm = warning_mm;
	danger_rad_mm = danger_mm;
}

TIM_HandleTypeDef* getSonarEchoTIM()
{
	return echoTIM;
}

uint8_t pulseSonar( uint8_t sonar_idx )
{
	if( sonar_idx >= MAX_SONAR_COUNT)  
		return 0;
	
	if( sonar_active!=NO_SONAR_ACTIVE ) 
		return 0;
	
	// MUX enable
	HAL_GPIO_WritePin( GPIOA, GPIO_PIN_10, GPIO_PIN_RESET );
	
	switch( sonar_idx )
	{
	case 0:
		HAL_GPIO_WritePin( GPIOA, GPIO_PIN_9, GPIO_PIN_RESET ); // D
		HAL_GPIO_WritePin( GPIOA, GPIO_PIN_8, GPIO_PIN_RESET ); // C
		HAL_GPIO_WritePin( GPIOC, GPIO_PIN_9, GPIO_PIN_RESET ); // B
		HAL_GPIO_WritePin( GPIOC, GPIO_PIN_8, GPIO_PIN_RESET ); // A
		break;
		
	case 1:
		HAL_GPIO_WritePin( GPIOA, GPIO_PIN_9, GPIO_PIN_RESET ); // D
		HAL_GPIO_WritePin( GPIOA, GPIO_PIN_8, GPIO_PIN_RESET ); // C
		HAL_GPIO_WritePin( GPIOC, GPIO_PIN_9, GPIO_PIN_RESET ); // B
		HAL_GPIO_WritePin( GPIOC, GPIO_PIN_8, GPIO_PIN_SET ); // A
		break;
		
	case 2:
		HAL_GPIO_WritePin( GPIOA, GPIO_PIN_9, GPIO_PIN_RESET ); // D
		HAL_GPIO_WritePin( GPIOA, GPIO_PIN_8, GPIO_PIN_RESET ); // C
		HAL_GPIO_WritePin( GPIOC, GPIO_PIN_9, GPIO_PIN_SET ); // B
		HAL_GPIO_WritePin( GPIOC, GPIO_PIN_8, GPIO_PIN_RESET ); // A
		break;
		
	case 3:
		HAL_GPIO_WritePin( GPIOA, GPIO_PIN_9, GPIO_PIN_RESET ); // D
		HAL_GPIO_WritePin( GPIOA, GPIO_PIN_8, GPIO_PIN_RESET ); // C
		HAL_GPIO_WritePin( GPIOC, GPIO_PIN_9, GPIO_PIN_SET ); // B
		HAL_GPIO_WritePin( GPIOC, GPIO_PIN_8, GPIO_PIN_SET ); // A
		break;
		
	case 4:
		break;
		
	case 5:
		break;
		
	case 6:
		break;
		
	case 7:
		break;
		
	case 8:
		break;
		
	case 9:
		break;
		
	case 10:
		break;
		
	case 11:
		break;
		
	case 12:
		break;
		
	case 13:
		break;
		
	case 14:
		break;
		
	case 15:
		break;
		
	}
	
	sonar_active = sonar_idx;
	HAL_TIM_PWM_Start( pulseTIM, TIM_CHANNEL_1 );	
	
	return 1;
}

void onNewMeasureReceived()
{
	ic_val = HAL_TIM_ReadCapturedValue( echoTIM, TIM_CHANNEL_2 );	
	last_range_mm = (int)((float)ic_val*0.175f+0.5f);
	
	if( sonar_active >= MAX_SONAR_COUNT)  
		return;
	
	if( last_range_mm < danger_rad_mm ) 
		setLedColor( sonar_active, red );
	else if( last_range_mm < warning_rad_mm ) 
		setLedColor( sonar_active, yellow );	
	else
		setLedColor( sonar_active, green );	
	
	sonar_mm_vec[sonar_active] = last_range_mm;
	sonar_active = NO_SONAR_ACTIVE;
}
