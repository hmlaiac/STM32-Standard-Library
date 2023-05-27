#include "bsp_led.h"
// initialize APB2_CLK

void LED_RCC_Enable(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
}

static void LED_Config(){
	GPIO_InitTypeDef LED;
	LED.GPIO_Pin = GPIO_Pin_x;
	LED.GPIO_Mode = GPIO_Mode_Out_PP;
	LED.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOB, &LED);
}



void LED_cmd(uint8_t color){
	LED_Config();
	if(color == Green){
		GPIO_ResetBits(GPIOB,GPIO_Pin_0);
		GPIO_SetBits(GPIOB,GPIO_Pin_1);
		GPIO_SetBits(GPIOB,GPIO_Pin_5);
	}else if(color == Blue){
		GPIO_SetBits(GPIOB,GPIO_Pin_0);
		GPIO_ResetBits(GPIOB,GPIO_Pin_1);
		GPIO_SetBits(GPIOB,GPIO_Pin_5);
	}else if(color == Red){
		GPIO_SetBits(GPIOB,GPIO_Pin_0);
		GPIO_SetBits(GPIOB,GPIO_Pin_1);
		GPIO_ResetBits(GPIOB,GPIO_Pin_5);
	}else if(color == Sky){
		GPIO_ResetBits(GPIOB,GPIO_Pin_0);
		GPIO_ResetBits(GPIOB,GPIO_Pin_1);
		GPIO_SetBits(GPIOB,GPIO_Pin_5);
	}else if(color == Violet){
		GPIO_SetBits(GPIOB,GPIO_Pin_0);
		GPIO_ResetBits(GPIOB,GPIO_Pin_1);
		GPIO_ResetBits(GPIOB,GPIO_Pin_5);
	}else if(color == Yellow){
		GPIO_ResetBits(GPIOB,GPIO_Pin_0);
		GPIO_SetBits(GPIOB,GPIO_Pin_1);
		GPIO_ResetBits(GPIOB,GPIO_Pin_5);
	}
}
