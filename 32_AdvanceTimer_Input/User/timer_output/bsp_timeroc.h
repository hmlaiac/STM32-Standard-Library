#ifndef __BSP_TIMEROC_H
#define __BSP_TIMEROC_H
#include "stm32f10x.h"

//RCC INIT
#define TIMER_RCC_GPIO						(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOA)
#define TIMER_RCC_TIMER						RCC_APB2Periph_TIM8

//select timer
#define TIMER_X 									TIM8

//select pin
#define TIMER_CH1_PORT						GPIOC
#define TIMER_CH1_PIN							GPIO_Pin_6

#define TIMER_CH1N_PORT						GPIOA
#define TIMER_CH1N_PIN						GPIO_Pin_7

#define TIMER_BKIN_PORT						GPIOA
#define TIMER_BKIN_PIN						GPIO_Pin_6


#define TIMER_ETR_PORT						GPIOA
#define TIMER_ETR_PIN							GPIO_Pin_0


//useful function here
void TIMER_OC_CONFIG(void);

#endif  //__BSP_TIMEROC_H
