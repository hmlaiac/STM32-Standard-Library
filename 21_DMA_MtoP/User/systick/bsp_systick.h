#ifndef __BSP_SYSTICK_H
#define __BSP_SYSTICK_H
#include "stm32f10x.h"

//useful function here
void Systick_Delay(uint32_t	time_ms, uint32_t counter);
void milis(uint32_t	time_ms);
void micros(uint32_t	time_us);
#endif
