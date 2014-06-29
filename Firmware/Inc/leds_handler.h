#ifndef _LEDS_HANDLER_H_
#define _LEDS_HANDLER_H_

#include "gpio.h"

#define LED_ON 	0
#define LED_OFF 1

#define LED_RED			0
#define LED_GREEN		1
#define LED_BLUE		2
#define LED_YELLOW	3
#define LED_PURPLE	4
#define LED_CYAN		5
#define LED_WHITE		6
#define LED_BLACK		7

// Initialize RGB Leds turning all off
void initRgbLeds( void );

// Sets the state of the Red Led on Discovery Board
void setLedDiscRed( uint8_t state );

// Toggle Red Led on Discovery Board
void toggleLedDiscRed( void );

// Sets the state of the Blue Led on Discovery Board
void setLedDiscBlue( uint8_t state );

// Toggle Blue Led on Discovery Board
void toggleLedDiscBlue( void );

// Sets the state of one of the 16 RGB Leds on the RoboDiscovery
void setStateLedColor( uint8_t ledIdx, uint8_t color );

#endif
