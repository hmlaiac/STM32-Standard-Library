#include ".\advancetimer\bsp_advancetimer.h"

static void TIMER_RCC_INIT(){
	RCC_APB2PeriphClockCmd(TIMER_RCC_GPIO, ENABLE);
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	RCC_APB2PeriphClockCmd(TIMER_RCC_TIMER, ENABLE);
}

static void GPIO_INIT(){
	GPIO_InitTypeDef GPIO_STRUCT;
	GPIO_STRUCT.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_STRUCT.GPIO_Speed = GPIO_Speed_50MHz;
	// chx
	GPIO_STRUCT.GPIO_Pin = TIMER_CH1_PIN;
	GPIO_Init(TIMER_CH1_PORT, &GPIO_STRUCT);
	//chxn
	GPIO_STRUCT.GPIO_Pin = TIMER_CH1N_PIN;
	GPIO_Init(TIMER_CH1N_PORT, &GPIO_STRUCT);
	// bkin
	GPIO_STRUCT.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_STRUCT.GPIO_Pin = TIMER_BKIN_PIN;
	GPIO_Init(TIMER_BKIN_PORT, &GPIO_STRUCT);
}


static void TIMER_INIT(){
	TIM_TimeBaseInitTypeDef  TIMER_STRUCT;
	TIMER_STRUCT.TIM_ClockDivision = TIM_CKD_DIV1; //
	TIMER_STRUCT.TIM_CounterMode = TIM_CounterMode_Up; //don't matter, timer2 is always count up
	TIMER_STRUCT.TIM_Period = (1000-1); // count from 0 to 999 
	TIMER_STRUCT.TIM_Prescaler = (72-1); //divide it to 1MHz
	TIMER_STRUCT.TIM_RepetitionCounter = 0; //repetive count value for x-1£¬no need
	TIM_TimeBaseInit(TIMER_X, &TIMER_STRUCT);
	
	TIM_OCInitTypeDef TIM_OC_STRUCT;
	TIM_OC_STRUCT.TIM_OCMode = TIM_OCMode_PWM1; //
	TIM_OC_STRUCT.TIM_OCIdleState = TIM_OCIdleState_Reset; //
	TIM_OC_STRUCT.TIM_OCNIdleState = TIM_OCIdleState_Set; //
	
	TIM_OC_STRUCT.TIM_OCPolarity = TIM_OCPolarity_High; 
	TIM_OC_STRUCT.TIM_OCNPolarity = TIM_OCNPolarity_High;
	
	TIM_OC_STRUCT.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OC_STRUCT.TIM_OutputNState = TIM_OutputNState_Enable;
	TIM_OC_STRUCT.TIM_Pulse = 400;
	TIM_OC1Init(TIMER_X, &TIM_OC_STRUCT);
	TIM_OC1PreloadConfig(TIMER_X, TIM_OCPreload_Enable );
	
	
	TIM_BDTRInitTypeDef TIM_BD_STRUCT;
	TIM_BD_STRUCT.TIM_AutomaticOutput = TIM_AutomaticOutput_Enable;
	TIM_BD_STRUCT.TIM_Break = TIM_Break_Enable;
	TIM_BD_STRUCT.TIM_BreakPolarity = TIM_BreakPolarity_High;
	TIM_BD_STRUCT.TIM_DeadTime = 11;
	TIM_BD_STRUCT.TIM_LOCKLevel = TIM_LOCKLevel_1;
	TIM_BD_STRUCT.TIM_OSSIState = TIM_OSSIState_Enable;
	TIM_BD_STRUCT.TIM_OSSRState = TIM_OSSRState_Enable;
	TIM_BDTRConfig(TIMER_X, &TIM_BD_STRUCT);
	
	TIM_Cmd(TIMER_X, ENABLE);
	TIM_CtrlPWMOutputs(TIMER_X, ENABLE);
}


void TIMER_CONFIG(void){
	TIMER_RCC_INIT();
	GPIO_INIT();
	TIMER_INIT();
}
