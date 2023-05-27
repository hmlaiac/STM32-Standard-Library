#include "stm32f10x.h"
#include "bsp_RccConfig.h"
#include "bsp_exti.h"
#include "bsp_systick.h"
#include "bsp_usart.h"
#include ".\adc\bsp_adc.h"

void Delay(uint32_t num){
	for(;num!=0;num--){}
}


int main(void){
	uint8_t i;
	float voltage = 0;
	HSE_SetSysClk(RCC_PLLMul_9);
	usart_config();
	ADC_CONFIG();
	SendString("Hello World!\n");
	while(1){
		for(i=0;i<5;i++){
			voltage = (float)(ADC_Multi_Data[i]) / (float)0xFFF * 3.3;
			printf("Data get is: %x, voltage is: %fV \n",ADC_Multi_Data[i],voltage);
		}
		Delay(0xFFFFFF);
	}
}
