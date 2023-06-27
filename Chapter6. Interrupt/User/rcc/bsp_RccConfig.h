#ifndef __BSP_RCCCONFIG_H
#define __BSP_RCCCONFIG_H
#include "stm32f10x.h"

void HSE_SetSysClk(uint32_t RCC_PLLMulx);
void HSI_SetSysClk(uint32_t RCC_PLLMulx);

#endif

