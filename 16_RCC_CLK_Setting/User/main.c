#include "stm32f10x.h"
#include "bsp_led.h"
#include "bsp_RccConfig.h"
void Delay(uint32_t num){
	for(;num!=0;num--){}
}

int main(void){
	HSE_SetSysClk(RCC_PLLMul_9);
	//HSI_SetSysClk(RCC_PLLMul_9);
	LED_G_Init_CLK();
	LED_G_Init();
	while(1){
		LED_G_LIGHT(ON);
		Delay(1000000);
		LED_G_LIGHT(OFF);
		Delay(1000000);
	}
}
