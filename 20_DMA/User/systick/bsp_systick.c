#include "bsp_systick.h"


void Systick_Delay(uint32_t	time_ms, uint32_t counter){
	SysTick_Config(counter);
	uint32_t i;
	for(i=0;i<time_ms;++i){
		while(!(SysTick->CTRL&(1<<16))){}
	}
	SysTick->CTRL &=~(1<<0);
}


void milis(uint32_t	time_ms){
	SysTick_Config(72000);
	uint32_t i;
	for(i=0;i<time_ms;++i){
		while(!(SysTick->CTRL&(1<<16))){}
	}
	SysTick->CTRL &=~(1<<0);
}

void micros(uint32_t	time_us){
	SysTick_Config(72);
	uint32_t i;
	for(i=0;i<time_us;++i){
		while(!(SysTick->CTRL&(1<<16))){}
	}
	SysTick->CTRL &=~(1<<0);
}
