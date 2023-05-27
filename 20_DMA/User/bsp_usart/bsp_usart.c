#include "bsp_usart.h"

void RCC_USART_Enable(void){	//clock enable
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
}


static void GPIO_Config(){
	//Initialize PA9
	GPIO_InitTypeDef	GPIO_StructDef;
	GPIO_StructDef.GPIO_Pin = USART_rx_pin;
	GPIO_StructDef.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_StructDef.GPIO_Speed = GPIO_Speed_50MHz;
	
	//Initialize PA10
	GPIO_InitTypeDef	GPIO_StructDefin;
	GPIO_StructDefin.GPIO_Pin = USART_tx_pin;
	GPIO_StructDefin.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	
	GPIO_Init(GPIOA, &GPIO_StructDef);
	GPIO_Init(GPIOA, &GPIO_StructDefin);
}

static void UAART_NIVC_Config(){
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitTypeDef NVICStuctInit;
	NVICStuctInit.NVIC_IRQChannel = USART1_IRQn;
	NVICStuctInit.NVIC_IRQChannelPreemptionPriority = 1;
	NVICStuctInit.NVIC_IRQChannelSubPriority = 1;
	NVICStuctInit.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVICStuctInit);
}

static void USART_init_config(){
	USART_InitTypeDef USART_StructInit;
	USART_StructInit.USART_BaudRate = 115200;
	USART_StructInit.USART_WordLength = USART_WordLength_8b;
	USART_StructInit.USART_StopBits = USART_StopBits_1;
	USART_StructInit.USART_Parity = USART_Parity_No;
	USART_StructInit.USART_Mode = ( USART_Mode_Rx | USART_Mode_Tx );
	USART_StructInit.USART_HardwareFlowControl = USART_HardwareFlowControl_None ;
	USART_Init(USART1, &USART_StructInit); //USARTInit
}

void usart_config(void){
	GPIO_Config(); // GPIOInit
	USART_init_config(); //usart init
	UAART_NIVC_Config(); //NVICInit
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); //Interruption enable
	USART_Cmd(USART1, ENABLE);
}

//Send 8 bits data each time
void SendByte(USART_TypeDef* USARTx, uint8_t Data){
	USART_SendData(USARTx, Data);
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET){}
}

// Send array
void SendString(USART_TypeDef* USARTx, uint8_t* Data){
	uint8_t i = 0;
	while(Data[i]!='\0'){
		USART_SendData(USARTx, Data[i]);
		while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET){}
		++i;
	}
}
