#ifndef BSP_LED_H
#define BSP_LED_H
#include "stm32f10x.h"

#define LED_G_Pin GPIO_Pin_0
#define LED_B_Pin GPIO_Pin_1
#define LED_R_Pin	GPIO_Pin_5


#define ON	1
#define OFF 0
#define LED_G_LIGHT(a)	if(a)GPIO_ResetBits(GPIOB,GPIO_Pin_0);else GPIO_SetBits(GPIOB,GPIO_Pin_0);
#define LED_Toggle	(GPIOB->ODR ^= GPIO_Pin_0)

enum{Green, Blue, Red, Sky, Violet, Yellow};

//useful function is here
#define GPIO_Pin_x (LED_G_Pin|LED_B_Pin|LED_R_Pin)
void LED_RCC_Enable(void);
void LED_cmd(uint8_t color);

#endif
