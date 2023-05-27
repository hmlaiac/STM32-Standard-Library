#include ".\adc\bsp_adc.h"
uint16_t ADC_GET_DATA;
static void CLK_CONFIG(){
	//This clock should be less than 14MHz
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
}

static void RCC_ADC_ENABLE(){
	RCC_APB2PeriphClockCmd(ADC_RCC_GPIO_CLK, ENABLE);
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
	ADC_RegularChannelConfig(ADC_X,ADC_Channel_11, 1, ADC_SampleTime_55Cycles5);
	ADC_ITConfig(ADC_X, ADC_IT_EOC, ENABLE);
	ADC_Cmd(ADC_X, ENABLE);
	ADC_StartCalibration(ADC_X);
	while(ADC_GetCalibrationStatus(ADC_X));
	ADC_SoftwareStartConvCmd(ADC_X, ENABLE);
}

void ADC_NVIC_INIT(void){
	NVIC_InitTypeDef NVICStuctInit;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVICStuctInit.NVIC_IRQChannel = ADC1_2_IRQn;
	NVICStuctInit.NVIC_IRQChannelPreemptionPriority = 1;
	NVICStuctInit.NVIC_IRQChannelSubPriority = 1;
	NVICStuctInit.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVICStuctInit);
}

void ADC_CONFIG(void){
	CLK_CONFIG();
	RCC_ADC_ENABLE();
	GPIO_INIT();
	ADC_INIT();
	ADC_NVIC_INIT();
}

