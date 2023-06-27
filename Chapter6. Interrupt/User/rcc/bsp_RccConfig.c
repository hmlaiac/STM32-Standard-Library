#include "bsp_RccConfig.h"

void HSE_SetSysClk(uint32_t RCC_PLLMulx){
	//Reset the clock
	RCC_DeInit();
	RCC_HSEConfig(RCC_HSE_ON);
	if(RCC_WaitForHSEStartUp()==SUCCESS){
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
		FLASH_SetLatency(FLASH_Latency_2);
				
		RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMulx);
		RCC_PLLCmd(ENABLE);
		
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
		while(RCC_GetSYSCLKSource()!=0x08){}
		RCC_HCLKConfig(RCC_SYSCLK_Div1);
		RCC_PCLK1Config(RCC_HCLK_Div2);
		RCC_PCLK2Config(RCC_HCLK_Div1);
	}
	else{
		//RCC is not opened fail
	}
}

void HSI_SetSysClk(uint32_t RCC_PLLMulx){
	//Reset the clock
	RCC_DeInit();
	RCC_HSEConfig(RCC_HSE_ON);
	if(RCC_WaitForHSEStartUp()==SUCCESS){
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
		FLASH_SetLatency(FLASH_Latency_2);
				
		RCC_PLLConfig(RCC_PLLSource_HSI_Div2, RCC_PLLMulx);
		RCC_PLLCmd(ENABLE);
		
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
		while(RCC_GetSYSCLKSource()!=0x08){}
		RCC_HCLKConfig(RCC_SYSCLK_Div1);
		RCC_PCLK1Config(RCC_HCLK_Div2);
		RCC_PCLK2Config(RCC_HCLK_Div1);
	}
	else{
		//RCC is not opened fail
	}
}
