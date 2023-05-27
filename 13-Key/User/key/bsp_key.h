#ifndef BSP_KEY_H
#define BSP_KEY_H
#include "stm32f10x.h"

#define RCC_KeyPort	   RCC_APB2Periph_GPIOA
#define GPIO_KeyPort	 GPIOA
#define GPIO_KeyPin	   GPIO_Pin_0


void GPIOA_CLK_Config(void);// configuration of APB2_GPIOA_CLK
void Key_Config(void); // allow GPIOA_0 accees floating input
uint8_t KeyScan(GPIO_TypeDef* Port, uint16_t GPIO_Pin);
#endif
