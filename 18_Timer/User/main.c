#include "stm32f10x.h"
#include "bsp_led.h"
#include "bsp_RccConfig.h"
#include "bsp_exti.h"
#include "bsp_systick.h"
void Delay(uint32_t num){
	for(;num!=0;num--){}
}

int main(void){
	HSE_SetSysClk(RCC_PLLMul_9);
	//HSI_SetSysClk(RCC_PLLMul_9);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	NVIC_Config();
	GPIOA_Config();
	GPIOB_Config();
	EXTI_Config();
	
	while(1){
		LED_Toggle;
		Systick_Delay(200,72000);
	}
}
