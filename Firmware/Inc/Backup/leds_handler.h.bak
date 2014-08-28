#ifndef _LEDS_HANDLER_H_
#define _LEDS_HANDLER_H_

#include "gpio.h"

#define MAX_LED_COUNT 16

#define LED_ON 	0
#define LED_OFF 1

typedef struct _led_color
{
	uint8_t R;
	uint8_t G;
	uint8_t B;
} LedColor;

#define LED_BLACK		LedColor(0,0,0)
#define LED_RED			LedColor(255,0,0)
#define LED_GREEN		LedColor(0,255,0)
#define LED_BLUE		LedColor(0,0,255)
#define LED_YELLOW		LedColor(255,255,0)
#define LED_PURPLE		LedColor(255,0,255)
#define LED_CYAN		LedColor(0,255,255)
#define LED_WHITE		LedColor(255,255,255)




// Initialize RGB Leds 
void initRgbLeds( void );

// Turn all RGB leds off
inline void resetRgbLeds( void );

// RGB Leds timer timeout
void on_RGB_led_timer_timeout( void );

// Sets the state of the Red Led on Discovery Board
void setLedDiscRed( uint8_t state );

// Toggle Red Led on Discovery Board
void toggleLedDiscRed( void );

// Sets the state of the Blue Led on Discovery Board
void setLedDiscBlue( uint8_t state );

// Toggle Blue Led on Discovery Board
void toggleLedDiscBlue( void );

// Sets the state of one of the 16 RGB Leds on the RoboDiscovery
//void setStateLedColor( uint8_t ledIdx, uint8_t color );

// Sets the color of a LED
void setLedColor( uint8_t ledIdx, LedColor color );

#endif
