#ifndef __BSP_ADVANCETIMER_H
#define __BSP_ADVANCETIMER_H
#include "stm32f10x.h"

extern uint16_t IC1Value;
extern uint16_t IC2Value;

//RCC INIT
#define IN_TIMER_RCC_GPIO							RCC_APB2Periph_GPIOA
#define IN_TIMER_RCC_TIMER						RCC_APB2Periph_TIM1

//select timer
#define IN_TIMER_X 									TIM1

//select pin
#define IN_TIMER_CH1_PORT						GPIOA
#define IN_TIMER_CH1_PIN							GPIO_Pin_8



//useful function here
void TIMER_CONFIG(void);

#endif  //__BSP_ADVANCETIMER_H
