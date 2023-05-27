#include "bsp_exti.h"

void NVIC_Config(void){
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitTypeDef NVICStuctInit;
	NVICStuctInit.NVIC_IRQChannel = EXTI0_IRQn;
	NVICStuctInit.NVIC_IRQChannelPreemptionPriority = 1;
	NVICStuctInit.NVIC_IRQChannelSubPriority = 1;
	NVICStuctInit.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVICStuctInit);
}

void GPIOA_Config(void){
	GPIO_InitTypeDef GPIOStructInit;
	GPIOStructInit.GPIO_Pin = GPIO_Pin_0;
	GPIOStructInit.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA,&GPIOStructInit);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);
}

void GPIOB_Config(void){
	GPIO_InitTypeDef GPIOStructInit;
	GPIOStructInit.GPIO_Pin = GPIO_Pin_0;
	GPIOStructInit.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIOStructInit.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOB,&GPIOStructInit);
	
	//GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource0);
}


void EXTI_Config(void){
	EXTI_InitTypeDef EXTI0StructInit;
	EXTI0StructInit.EXTI_Line = EXTI_Line0; // refer to GPIOA
	EXTI0StructInit.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI0StructInit.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI0StructInit.EXTI_LineCmd = ENABLE;
	
	EXTI_Init(&EXTI0StructInit);
}

