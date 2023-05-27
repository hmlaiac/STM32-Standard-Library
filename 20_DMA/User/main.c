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
}



int main(void){
	HSE_SetSysClk(RCC_PLLMul_9);
	RCC_Config();
	
	LED_cmd(Yellow);
	milis(500);
	DMA_Config();
	if(memory_compare(Peri_Array, Mem_Array, 32)==1){
		LED_cmd(Green);
	}else{
		LED_cmd(Red);
	};
	
	while(1){
		
	}
}
