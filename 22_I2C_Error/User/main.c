#include "stm32f10x.h"
#include "bsp_led.h"
#include "bsp_RccConfig.h"
#include "bsp_exti.h"
#include "bsp_systick.h"
#include "bsp_usart.h"
#include "bsp_dma.h"
#include "bsp_eeprom.h"
uint8_t datasend[8] = {1,2,3,4,5,6,7,8};
uint8_t dataread[8];

void RCC_Config(){
	RCC_USART_Enable();
	RCC_EEPROM_Enable();
}

void Device_Config(){
	usart_config();
	EEPROM_Config();
}

int main(void){
	HSE_SetSysClk(RCC_PLLMul_9);
	RCC_Config();
	Device_Config();
	
	//char char1[100] = "EEPROM is start here\n";
	//SendString(USART1, char1);
	EEPROM_SendByte(0, datasend, 8);
	//EEPROM_ReadByte(0, datasend, 8);
	SendArray(USART1, dataread, 8);
	while(1){
	}
}
