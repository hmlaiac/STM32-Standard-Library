#include "stm32f10x.h"
#include "bsp_led.h"
#include "bsp_key.h"

void Delay(uint32_t num){
	for(;num!=0;num--){}
}

int main(void){
	LED_G_Init_CLK();
	LED_G_Init();
	GPIOA_CLK_Config();
	Key_Config();
	while(1){
		if(KeyScan(GPIOA,GPIO_Pin_0)){
			LED_TOGGLE;
		}
	}
}
