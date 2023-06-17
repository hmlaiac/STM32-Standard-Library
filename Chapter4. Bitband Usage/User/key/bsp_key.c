#include "bsp_key.h"

void GPIOA_CLK_Config(){
	RCC_APB2PeriphClockCmd(RCC_KeyPort, ENABLE);
}

void Key_Config(){
	GPIO_InitTypeDef Key;
	Key.GPIO_Pin = GPIO_KeyPin;
	Key.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIO_KeyPort, &Key);
}

uint8_t KeyScan(GPIO_TypeDef* Port, uint16_t GPIO_Pin){
	if(GPIO_ReadInputDataBit(Port, GPIO_Pin)==1){
		while(GPIO_ReadInputDataBit(Port, GPIO_Pin)==1){}
		return 1; //keypressed
	}else{
		return 0; // Not pressed
	}
}
