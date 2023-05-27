#include ".\advancetimer\bsp_advancetimer.h"

uint16_t IC1Value = 0;
uint16_t IC2Value = 0;
static void TIMER_RCC_INIT(){
	RCC_APB2PeriphClockCmd(IN_TIMER_RCC_GPIO, ENABLE);
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	RCC_APB2PeriphClockCmd(IN_TIMER_RCC_TIMER, ENABLE);
}

static void GPIO_INIT(){
	GPIO_InitTypeDef GPIO_STRUCT;
	GPIO_STRUCT.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_STRUCT.GPIO_Speed = GPIO_Speed_50MHz;
	// chx
	GPIO_STRUCT.GPIO_Pin = IN_TIMER_CH1_PIN;
	GPIO_Init(IN_TIMER_CH1_PORT, &GPIO_STRUCT);
}

static void NVIC_Config(){
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitTypeDef NVICStuctInit;
	NVICStuctInit.NVIC_IRQChannel = TIM1_CC_IRQn;
	NVICStuctInit.NVIC_IRQChannelPreemptionPriority = 1;
	NVICStuctInit.NVIC_IRQChannelSubPriority = 1;
	NVICStuctInit.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVICStuctInit);
}

static void TIMER_INIT(){
	TIM_TimeBaseInitTypeDef  TIMER_STRUCT;
	TIMER_STRUCT.TIM_ClockDivision = TIM_CKD_DIV1; //
	TIMER_STRUCT.TIM_CounterMode = TIM_CounterMode_Up; //don't matter, timer2 is always count up
	TIMER_STRUCT.TIM_Period = (1000-1); // count from 0 to 999 
	TIMER_STRUCT.TIM_Prescaler = (72-1); //divide it to 1MHz
	TIMER_STRUCT.TIM_RepetitionCounter = 0; //repetive count value for x-1£¬no need
	TIM_TimeBaseInit(IN_TIMER_X, &TIMER_STRUCT);
	
	TIM_ICInitTypeDef TIM_IN_STRUCT;
	TIM_IN_STRUCT.TIM_Channel = TIM_Channel_1;
	TIM_IN_STRUCT.TIM_ICFilter = 0x0;
	TIM_IN_STRUCT.TIM_ICPolarity = TIM_ICPolarity_Rising;
	TIM_IN_STRUCT.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_IN_STRUCT.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM_PWMIConfig(IN_TIMER_X, &TIM_IN_STRUCT);
	
	//select input trigger signal
	TIM_SelectInputTrigger(IN_TIMER_X, TIM_TS_TI1FP1);	
	//select slave mode
	TIM_SelectSlaveMode(IN_TIMER_X, TIM_SlaveMode_Reset);
  TIM_SelectMasterSlaveMode(IN_TIMER_X, TIM_MasterSlaveMode_Enable); 
	
	//set up interruption
	TIM_ITConfig (IN_TIMER_X, TIM_IT_CC1, ENABLE);
	TIM_ClearITPendingBit(IN_TIMER_X, TIM_IT_CC1);
	

	TIM_Cmd(IN_TIMER_X, ENABLE);
}


void TIMER_CONFIG(void){
	TIMER_RCC_INIT();
	GPIO_INIT();
	NVIC_Config();
	TIMER_INIT();
}
