#ifndef __BSP_ADC_H
#define __BSP_ADC_H
#include "stm32f10x.h"
#include "bsp_usart.h"
//param need to make it to global in main.c
extern uint16_t ADC_GET_DATA;
//RCC
#define ADC_RCC_GPIO_CLK						RCC_APB2Periph_GPIOC
#define ADC_RCC_CLK 								RCC_APB2Periph_ADC1
//GPIO CONFIG
#define ADC_GPIO_PORT								GPIOC
#define ADC_GPIO_PIN								GPIO_Pin_1
//ADC CONFIG
#define ADC_X   										ADC1

//useful function here
void ADC_CONFIG(void);

#endif //__BSP_ADC_H
