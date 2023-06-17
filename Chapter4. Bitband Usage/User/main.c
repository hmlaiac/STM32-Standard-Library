#include "stm32f10x.h"
#include "bsp_led.h"
#include "bsp_key.h"


#define GPIOB_ODR_ADDR (GPIOB_BASE+0x0C)
#define BITBAND(Addr, n) *(uint32_t*)((Addr & 0xF0000000)+0x02000000+((Addr & 0x00FFFFFF)<<5)+(n<<2))

void Delay(uint32_t num){
	for(;num!=0;num--){}
}

int main(void){
	LED_G_Init_CLK();
	LED_G_Init();
	GPIOA_CLK_Config();
	Key_Config();
	while(1){
		BITBAND(GPIOB_ODR_ADDR, 0)=0;
		Delay(0xFFFFF);
		BITBAND(GPIOB_ODR_ADDR, 0)=1;
		Delay(0xFFFFF);
	}
}
