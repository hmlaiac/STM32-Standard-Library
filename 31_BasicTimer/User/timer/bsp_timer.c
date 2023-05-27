#include ".\timer\bsp_timer.h"
uint16_t time_up = 0;

static void NVIC_Config(){
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitTypeDef NVICStuctInit;
	NVICStuctInit.NVIC_IRQChannel = TIMER_IT;
	NVICStuctInit.NVIC_IRQChannelPreemptionPriority = 1;
	NVICStuctInit.NVIC_IRQChannelSubPriority = 1;
	NVICStuctInit.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVICStuctInit);
}


static void TIMER_RCC_INIT(){
	RCC_APB1PeriphClockCmd (RCC_APB1Periph_TIM2, ENABLE);
}

static void TIMER_INIT(){
	TIM_TimeBaseInitTypeDef  TIMER_STRUCT;
		TIMER_STRUCT.TIM_Period = (1000-1); // count from 0 to 999 
	TIMER_STRUCT.TIM_Prescaler = (72-1); //divide it to 1MHz
	TIMER_STRUCT.TIM_ClockDivision = TIM_CKD_DIV1; //
	TIMER_STRUCT.TIM_CounterMode = TIM_CounterMode_Up; //don't matter, timer2 is always count up
	TIMER_STRUCT.TIM_RepetitionCounter = 0; //repetive count value for x-1£¬no need
	TIM_TimeBaseInit(TIMER_X, &TIMER_STRUCT);
	
	//interuption
	TIM_ITConfig(TIMER_X, TIM_IT_Update, ENABLE);
	
	TIM_Cmd(TIMER_X, ENABLE);
}

void TIMER_CONFIG(void){
	TIMER_RCC_INIT();
	NVIC_Config();
	TIMER_INIT();
}
