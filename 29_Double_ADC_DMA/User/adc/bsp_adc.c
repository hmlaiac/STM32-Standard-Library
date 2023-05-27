#include ".\adc\bsp_adc.h"
uint32_t ADC_GET_DATA = 0; // change to 32bits data
static void CLK_CONFIG(){
	//This clock should be less than 14MHz
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
}

static void RCC_ADC_ENABLE(){
	RCC_APB2PeriphClockCmd(ADC_RCC_GPIO_CLK, ENABLE);
	RCC_AHBPeriphClockCmd(ADC_RCC_DMA_CLK,ENABLE);
	RCC_APB2PeriphClockCmd(ADC_RCC_ADC1_CLK,ENABLE);
	RCC_APB2PeriphClockCmd(ADC_RCC_ADC2_CLK,ENABLE);
}

static void ADC_DMA_INIT(){
	DMA_DeInit(ADC_DMA_CHANNEL);
	DMA_InitTypeDef DMA_InitStruct;
	DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)(&ADC_X_1->DR);
	DMA_InitStruct.DMA_MemoryBaseAddr= (uint32_t) (&ADC_GET_DATA); //address set to 32bits data
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStruct.DMA_BufferSize = 1; //buffer size is 1
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Disable; // increment disable
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word; //32bits
	DMA_InitStruct.DMA_MemoryDataSize= DMA_MemoryDataSize_Word;
	DMA_InitStruct.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStruct.DMA_Priority = DMA_Priority_High ;
	DMA_InitStruct.DMA_M2M = DMA_M2M_Disable;
	
	DMA_Init(ADC_DMA_CHANNEL, &DMA_InitStruct);
	DMA_Cmd(ADC_DMA_CHANNEL,ENABLE);
}


static void GPIO_INIT(){
	GPIO_InitTypeDef GPIO_INITSTRUCT;
	GPIO_INITSTRUCT.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_INITSTRUCT.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_INITSTRUCT.GPIO_Pin = ADC_GPIO_PIN_1;
	GPIO_Init(ADC_GPIO_PORT_1,&GPIO_INITSTRUCT);
	
	GPIO_INITSTRUCT.GPIO_Pin = ADC_GPIO_PIN_2;
	GPIO_Init(ADC_GPIO_PORT_2,&GPIO_INITSTRUCT);
}

static void ADC_INIT(){
	//adc 1 Init
	ADC_InitTypeDef ADC_INITSTRUCT;
	ADC_INITSTRUCT.ADC_ContinuousConvMode = ENABLE;
	ADC_INITSTRUCT.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_INITSTRUCT.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; //not need soft trig
	ADC_INITSTRUCT.ADC_Mode = ADC_Mode_RegSimult; // reg simult
	ADC_INITSTRUCT.ADC_NbrOfChannel = 1; //channel set to 1
	ADC_INITSTRUCT.ADC_ScanConvMode = ENABLE; //Enable multi channel mode
	
	ADC_Init(ADC_X_1, &ADC_INITSTRUCT);
	ADC_RegularChannelConfig(ADC_X_1,ADC_CHANNEL_1, 1, ADC_SampleTime_55Cycles5);
	//adc 2 Init
	ADC_Init(ADC_X_2, &ADC_INITSTRUCT);
	ADC_RegularChannelConfig(ADC_X_2,ADC_CHANNEL_2, 1, ADC_SampleTime_55Cycles5);
	//DMA enable
	
	//adc 1 enable
	ADC_DMACmd(ADC_X_1,ENABLE);
	ADC_Cmd(ADC_X_1, ENABLE);
	ADC_StartCalibration(ADC_X_1);
	while(ADC_GetCalibrationStatus(ADC_X_1));
	//adc 2 enable
	ADC_ExternalTrigConvCmd(ADC_X_2, ENABLE);
	ADC_Cmd(ADC_X_2, ENABLE);
	ADC_StartCalibration(ADC_X_2);
	while(ADC_GetCalibrationStatus(ADC_X_2));
	
	ADC_SoftwareStartConvCmd(ADC_X_1, ENABLE);
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

