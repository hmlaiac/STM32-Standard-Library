#ifndef __BSP_ADC_H
#define __BSP_ADC_H
#include "stm32f10x.h"
#include "bsp_usart.h"
//param need to make it to global in main.c
extern uint16_t ADC_GET_DATA;
extern uint16_t ADC_Multi_Data[5];
#define Peri_Addr										(ADC_X+0x4C)
//RCC
#define ADC_RCC_GPIO_CLK								RCC_APB2Periph_GPIOC
#define ADC_RCC_DMA_CLK									RCC_AHBPeriph_DMA1
#define ADC_RCC_ADC_CLK 								RCC_APB2Periph_ADC1
//DMA
#define ADC_DMA_CHANNEL							DMA1_Channel1
#define ADC_CHANNEL_1									ADC_Channel_11 // for PC1
#define ADC_CHANNEL_2									ADC_Channel_12 // for PC2
#define ADC_CHANNEL_3									ADC_Channel_13 // for PC2
#define ADC_CHANNEL_4									ADC_Channel_14 // for PC2
#define ADC_CHANNEL_5									ADC_Channel_15 // for PC2
//GPIO CONFIG
#define ADC_GPIO_PORT_1								GPIOC
#define ADC_GPIO_PIN_1								GPIO_Pin_1

#define ADC_GPIO_PORT_2								GPIOC
#define ADC_GPIO_PIN_2								GPIO_Pin_2

#define ADC_GPIO_PORT_3								GPIOC
#define ADC_GPIO_PIN_3								GPIO_Pin_3

#define ADC_GPIO_PORT_4								GPIOC
#define ADC_GPIO_PIN_4								GPIO_Pin_4

#define ADC_GPIO_PORT_5								GPIOC
#define ADC_GPIO_PIN_5								GPIO_Pin_5

//ADC CONFIG
#define ADC_X   										ADC1 

//useful function here
void ADC_CONFIG(void);

#endif //__BSP_ADC_H
