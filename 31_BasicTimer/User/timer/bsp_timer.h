#ifndef __BSP_TIMER_H
#define __BSP_TIMER_H
#include "stm32f10x.h"

extern uint16_t time_up;

//select timer
#define TIMER_X 									TIM2

//for interruption
#define TIMER_IT                  TIM2_IRQn


void TIMER_CONFIG(void);
#endif //__BSP_TIMER_H
