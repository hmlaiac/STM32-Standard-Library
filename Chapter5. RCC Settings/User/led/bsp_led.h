#ifndef BSP_LED_H
#define BSP_LED_H
#include "stm32f10x.h"
#define ON	1
#define OFF 0
#define LED_G_LIGHT(a)	if(a)GPIO_ResetBits(GPIOB,GPIO_Pin_0);else GPIO_SetBits(GPIOB,GPIO_Pin_0);
void 	LED_G_Init_CLK(void);
void	LED_G_Init(void);

#endif
