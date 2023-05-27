#include ".\adc\bsp_adc.h"
uint16_t ADC_GET_DATA;
static void CLK_CONFIG(){
	//This clock should be less than 14MHz
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
}

static void ADC_DMA_INIT(){
	DMA_DeInit(ADC_DMA_CHANNEL);
	DMA_InitTypeDef DMA_InitStruct;
	DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)(&ADC_X->DR);
	DMA_InitStruct.DMA_MemoryBaseAddr= (uint32_t) (&ADC_GET_DATA);
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStruct.DMA_BufferSize = 1; //remark error may occur here
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Disable;
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStruct.DMA_MemoryDataSize= DMA_MemoryDataSize_HalfWord;
	DMA_InitStruct.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStruct.DMA_Priority = DMA_Priority_High ;
	DMA_InitStruct.DMA_M2M = DMA_M2M_Disable;
	
	DMA_Init(ADC_DMA_CHANNEL, &DMA_InitStruct);
	DMA_Cmd(ADC_DMA_CHANNEL,ENABLE);
}

static void RCC_ADC_ENABLE(){
	RCC_APB2PeriphClockCmd(ADC_RCC_GPIO_CLK, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
}

static void GPIO_INIT(){
	GPIO_InitTypeDef GPIO_INITSTRUCT;
	GPIO_INITSTRUCT.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_INITSTRUCT.GPIO_Pin = ADC_GPIO_PIN;
	GPIO_INITSTRUCT.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(ADC_GPIO_PORT,&GPIO_INITSTRUCT);
}

static void ADC_INIT(){
	ADC_InitTypeDef ADC_INITSTRUCT;
	ADC_INITSTRUCT.ADC_ContinuousConvMode = ENABLE;
	ADC_INITSTRUCT.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_INITSTRUCT.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_INITSTRUCT.ADC_Mode = ADC_Mode_Independent;
	ADC_INITSTRUCT.ADC_NbrOfChannel = 1;
	ADC_INITSTRUCT.ADC_ScanConvMode = DISABLE;
	
	ADC_Init(ADC_X, &ADC_INITSTRUCT);
	ADC_RegularChannelConfig(ADC_X,ADC_CHANNEL, 1, ADC_SampleTime_55Cycles5);
	//ADC_ITConfig(ADC_X, ADC_IT_EOC, ENABLE);
	ADC_Cmd(ADC_X, ENABLE);
	ADC_DMACmd(ADC_X,ENABLE);
	
	ADC_StartCalibration(ADC_X);
	while(ADC_GetCalibrationStatus(ADC_X));
	ADC_SoftwareStartConvCmd(ADC_X, ENABLE);
}

//void ADC_NVIC_INIT(void){
//	NVIC_InitTypeDef NVICStuctInit;
//	
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
//	NVICStuctInit.NVIC_IRQChannel = ADC1_2_IRQn;
//	NVICStuctInit.NVIC_IRQChannelPreemptionPriority = 1;
//	NVICStuctInit.NVIC_IRQChannelSubPriority = 1;
//	NVICStuctInit.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVICStuctInit);
//}

void ADC_CONFIG(void){
	CLK_CONFIG();
	RCC_ADC_ENABLE();
	GPIO_INIT();
	ADC_DMA_INIT();
	ADC_INIT();
	
	//ADC_NVIC_INIT();
}

