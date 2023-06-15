#include "bsp_led.h"
// initialize APB2_CLK

void LED_G_Init_CLK(){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
}

void LED_G_Init(){
	GPIO_InitTypeDef LED_G;
	LED_G.GPIO_Pin = GPIO_Pin_0;
	LED_G.GPIO_Mode = GPIO_Mode_Out_PP;
	LED_G.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &LED_G);
}



