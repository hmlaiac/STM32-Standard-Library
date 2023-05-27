#ifndef __BSP_ADC_H
#define __BSP_ADC_H
#include "stm32f10x.h"
#include "bsp_usart.h"
//param need to make it to global in main.c
extern uint32_t ADC_GET_DATA;
//RCC
#define ADC_RCC_GPIO_CLK								RCC_APB2Periph_GPIOC
#define ADC_RCC_DMA_CLK									RCC_AHBPeriph_DMA1
#define ADC_RCC_ADC1_CLK 								RCC_APB2Periph_ADC1
#define ADC_RCC_ADC2_CLK 								RCC_APB2Periph_ADC2
//DMA
#define ADC_DMA_CHANNEL							DMA1_Channel1
#define ADC_CHANNEL_1									ADC_Channel_11 // for PC1
#define ADC_CHANNEL_2									ADC_Channel_12 // for PC2
//GPIO CONFIG
#define ADC_GPIO_PORT_1								GPIOC
#define ADC_GPIO_PIN_1								GPIO_Pin_1

#define ADC_GPIO_PORT_2								GPIOC
#define ADC_GPIO_PIN_2								GPIO_Pin_2


//ADC CONFIG
#define ADC_X_1   										ADC1 
#define ADC_X_2   										ADC2


//useful function here
void ADC_CONFIG(void);

#endif //__BSP_ADC_H
