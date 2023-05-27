#include "stm32f10x.h"
#include "bsp_led.h"
#include "bsp_RccConfig.h"
#include "bsp_exti.h"
#include "bsp_systick.h"
#include "bsp_usart.h"
#include "bsp_dma.h"

void RCC_Config(){
	LED_RCC_Enable();
	DMA_RCC_ENABLE();
	RCC_USART_Enable();
}



int main(void){
	HSE_SetSysClk(RCC_PLLMul_9);
	RCC_Config();
	
	
	usart_config();
	DMA_P2M_Config();
	while(1){
	}
}
