#ifndef _SONAR_HANDLER_H_
#define _SONAR_HANDLER_H_

#include "tim.h"
#include "leds_handler.h"

#define MAX_SONAR_COUNT 16
#define MEAS_NOT_VALID 32000

extern uint32_t sonar_mm_vec[MAX_SONAR_COUNT];

void initSonars( TIM_HandleTypeDef* pulseTIM, TIM_HandleTypeDef* echoTIM );
void setAreaLimits( uint32_t danger_mm, uint32_t warning_mm);

uint8_t pulseSonar( uint8_t sonar_idx );

void onNewMeasureReceived();

TIM_HandleTypeDef* getSonarEchoTIM();

#endif
