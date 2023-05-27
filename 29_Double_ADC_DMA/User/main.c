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
	uint16_t adc1_data = 0;
	uint16_t adc2_data = 0;
	float voltage = 0;
	HSE_SetSysClk(RCC_PLLMul_9);
	usart_config();
	ADC_CONFIG();
	SendString("Hello World!\n");
	while(1){
			adc1_data = (ADC_GET_DATA & 0xffff);
			adc2_data = (ADC_GET_DATA & 0xffff0000) >>16;
			voltage = (float)(adc1_data) / (float)0xFFF * 3.3;
			printf("Data1 get is: %x, voltage is: %fV \n",adc1_data,voltage);
			voltage = (float)(adc2_data) / (float)0xFFF * 3.3;
			printf("Data2 get is: %x, voltage is: %fV \n",adc2_data,voltage);
		Delay(0xFFFFFF);
	}
}
