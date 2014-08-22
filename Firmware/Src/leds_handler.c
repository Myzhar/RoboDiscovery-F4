#include "leds_handler.h"
#include "tim.h"

// >>>>> Values to update the color of the leds
// @Note: at each interrupt the values in upd_led_X_vals vectors are
//        decreased. If the value is zero the led is off.
//        Each update cycle lasts 256 counts, for 256 levels of light of each led

static uint8_t led_upd_count = 0;
static uint8_t cycle = 0;
static uint8_t tr_idx = 0;

static uint8_t led_R_vals[MAX_LED_COUNT]; // Contains the R value for each led
static uint8_t led_G_vals[MAX_LED_COUNT]; // Contains the G value for each led
static uint8_t led_B_vals[MAX_LED_COUNT]; // Contains the B value for each led

static uint8_t upd_led_R_vals[MAX_LED_COUNT]; // Contains the status of each R led. If not zero the led is ON
static uint8_t upd_led_G_vals[MAX_LED_COUNT]; // Contains the status of each G led. If not zero the led is ON
static uint8_t upd_led_B_vals[MAX_LED_COUNT]; // Contains the status of each B led. If not zero the led is ON
// <<<<< Values to update the color of the leds 

#define COL_MIN_RNG 50
#define COL_MAX_RNG 150


#define TR_S1_R GPIO_PIN_0
#define TR_S1_G GPIO_PIN_1
#define TR_S1_B GPIO_PIN_2
#define TR_S2_R GPIO_PIN_3
#define TR_S2_G GPIO_PIN_8 // Note TR_S2_GREEN is not on Port D, but on Port B!!!
#define TR_S2_B GPIO_PIN_5

#define KLED_1 GPIO_PIN_6
#define KLED_2 GPIO_PIN_7
#define KLED_3 GPIO_PIN_8
#define KLED_4 GPIO_PIN_9
#define KLED_5 GPIO_PIN_10
#define KLED_6 GPIO_PIN_11
#define KLED_7 GPIO_PIN_12
#define KLED_8 GPIO_PIN_13

// >>>>> Private Functions
void setK_pinState( uint8_t k_idx, uint8_t state );
// <<<<< Private Functions

void initRgbLeds( void )
{
	resetRgbLeds();
	
	for( uint8_t i=0; i<MAX_LED_COUNT; i++  )
	{
		upd_led_R_vals[i]=0;
		upd_led_G_vals[i]=0;
		upd_led_B_vals[i]=0;			
	}
	
	HAL_TIM_Base_Start_IT( &htim7 );
}

void resetRgbLeds(void)
{	
	HAL_GPIO_WritePin( GPIOD, TR_S1_R, GPIO_PIN_SET );
	HAL_GPIO_WritePin( GPIOD, TR_S1_G, GPIO_PIN_SET );
	HAL_GPIO_WritePin( GPIOD, TR_S1_B, GPIO_PIN_SET );
	HAL_GPIO_WritePin( GPIOD, TR_S2_R, GPIO_PIN_SET );
	HAL_GPIO_WritePin( GPIOB, TR_S2_G, GPIO_PIN_SET );
	HAL_GPIO_WritePin( GPIOD, TR_S2_B, GPIO_PIN_SET );
	HAL_GPIO_WritePin( GPIOD, KLED_1, GPIO_PIN_RESET );
	HAL_GPIO_WritePin( GPIOD, KLED_2, GPIO_PIN_RESET );
	HAL_GPIO_WritePin( GPIOD, KLED_3, GPIO_PIN_RESET );
	HAL_GPIO_WritePin( GPIOD, KLED_4, GPIO_PIN_RESET );
	HAL_GPIO_WritePin( GPIOD, KLED_5, GPIO_PIN_RESET );
	HAL_GPIO_WritePin( GPIOD, KLED_6, GPIO_PIN_RESET );
	HAL_GPIO_WritePin( GPIOD, KLED_7, GPIO_PIN_RESET );
	HAL_GPIO_WritePin( GPIOD, KLED_8, GPIO_PIN_RESET );	
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

void setK_pinState( uint8_t led_idx, uint8_t state )
{	
	if( led_idx > 7 )
		led_idx-=8;
	
	uint16_t pinK_idx;
	if( led_idx==0 )
		pinK_idx = KLED_1;
	else if( led_idx==1 )
		pinK_idx = KLED_2;
	else if( led_idx==2 )
		pinK_idx = KLED_3;
	else if( led_idx==3 )
		pinK_idx = KLED_4;
	else if( led_idx==4 )
		pinK_idx = KLED_5;
	else if( led_idx==5 )
		pinK_idx = KLED_6;
	else if( led_idx==6 )
		pinK_idx = KLED_7;
	else if( led_idx==7 )
		pinK_idx = KLED_8;
		
	if(state==1)
		HAL_GPIO_WritePin( GPIOD, pinK_idx, GPIO_PIN_SET );	
	else
		HAL_GPIO_WritePin( GPIOD, pinK_idx, GPIO_PIN_RESET );	
}

void setLedColor( uint8_t ledIdx, LedColor color )
{
	led_R_vals[ledIdx] = color.R;
	led_G_vals[ledIdx] = color.G;
	led_B_vals[ledIdx] = color.B;
}

#define CYC 2

void on_RGB_led_timer_timeout( void )
{		
	// >>>>> Update RGB values if this is the first update of the cycle
	if( led_upd_count==0 )
	{
		for( uint8_t i=0; i<MAX_LED_COUNT; i++  )
		{
			upd_led_R_vals[i]=led_R_vals[i];
			upd_led_G_vals[i]=led_G_vals[i];
			upd_led_B_vals[i]=led_B_vals[i];
		}
	}
	// <<<<< Update RGB values if this is the first update of the cycle
	
	// >>>>> Open all transistors
	resetRgbLeds();
	// <<<<< Open all transistors	
	
	if(cycle%CYC==0) // one cycle to led transistor open correctly
	{
		cycle++;
		return;
	}
	
	tr_idx = cycle/CYC;
	
	// >>>>> Decrease RGB update values		
	switch(tr_idx)
	{
		case 0:			
			HAL_GPIO_WritePin( GPIOD, TR_S1_R, GPIO_PIN_RESET );			
			for( int i=0; i<8;i++ )
			{
				if(upd_led_R_vals[i]!=0)				
				{
					setK_pinState(i, 1 );
					upd_led_R_vals[i]--;					
				}
			}			
			break;
			
		case 1:
			HAL_GPIO_WritePin( GPIOD, TR_S1_G, GPIO_PIN_RESET );
			for( int i=0; i<8;i++ )
			{
				if(upd_led_G_vals[i]!=0)				
				{
					setK_pinState(i, 1 );
					upd_led_G_vals[i]--;					
				}
			}			
			break;
			
		case 2:
			HAL_GPIO_WritePin( GPIOD, TR_S1_B, GPIO_PIN_RESET );
			for( int i=0; i<8;i++ )
			{
				if(upd_led_B_vals[i]!=0)				
				{
					setK_pinState(i, 1 );
					upd_led_B_vals[i]--;					
				}
			}			
			break;

		case 3:
			HAL_GPIO_WritePin( GPIOD, TR_S2_R, GPIO_PIN_RESET );
			for( int i=8; i<16;i++ )
			{
				if(upd_led_R_vals[i]!=0)				
				{
					setK_pinState(i, 1 );
					upd_led_R_vals[i]--;					
				}
			}			
			break;
			
		case 4:
			HAL_GPIO_WritePin( GPIOB, TR_S2_G, GPIO_PIN_RESET );
			for( int i=8; i<16;i++ )
			{
				if(upd_led_G_vals[i]!=0)				
				{
					setK_pinState(i, 1 );
					upd_led_G_vals[i]--;					
				}
			}			
			break;
			
		case 5:
			HAL_GPIO_WritePin( GPIOD, TR_S2_B, GPIO_PIN_RESET );
			for( int i=8; i<16;i++ )
			{
				if(upd_led_B_vals[i]!=0)				
				{
					setK_pinState(i, 1 );
					upd_led_B_vals[i]--;					
				}
			}			
			break;		
	}		
		
	// Update cycle index
	cycle++;
	if( cycle==(6*CYC) )
	{
		cycle = 0;
		led_upd_count++;
	}
}
