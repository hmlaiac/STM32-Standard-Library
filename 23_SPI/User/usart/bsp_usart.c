#include ".\usart\bsp_usart.h"

static void RCC_USART_Enable(void){	//clock enable
	RCC_APB2PeriphClockCmd(USER_USART_RCC_GPIO, ENABLE);
	RCC_APB2PeriphClockCmd(USER_USART_RCC_USARTx, ENABLE);
}


static void GPIO_Config(){
	//Initialize PA9
	GPIO_InitTypeDef	GPIO_StructDef;
	GPIO_StructDef.GPIO_Pin = USER_USART_TX_PIN;
	GPIO_StructDef.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_StructDef.GPIO_Speed = GPIO_Speed_50MHz;
	
	//Initialize PA10
	GPIO_InitTypeDef	GPIO_StructDefin;
	GPIO_StructDefin.GPIO_Pin = USER_USART_RX_PIN;
	GPIO_StructDefin.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	
	GPIO_Init(USER_USART_TX_PORT, &GPIO_StructDef);
	GPIO_Init(USER_USART_RX_PORT, &GPIO_StructDefin);
}


static void USART_init_config(){
	USART_InitTypeDef USART_StructInit;
	USART_StructInit.USART_BaudRate = 115200;
	USART_StructInit.USART_WordLength = USART_WordLength_8b;
	USART_StructInit.USART_StopBits = USART_StopBits_1;
	USART_StructInit.USART_Parity = USART_Parity_No;
	USART_StructInit.USART_Mode = ( USART_Mode_Rx | USART_Mode_Tx );
	USART_StructInit.USART_HardwareFlowControl = USART_HardwareFlowControl_None ;
	USART_Init(USER_USARTx, &USART_StructInit); //USARTInit
}

void usart_config(void){
	USART_DeInit(USART1);
	RCC_USART_Enable(); // enalbe clk 
	GPIO_Config(); // GPIOInit
	USART_init_config(); //usart init
	USART_Cmd(USART1, ENABLE);
}

//Send 8 bits data each time
void SendByte(uint8_t Data){
	USART_SendData(USER_USARTx, Data);
	while(USART_GetFlagStatus(USER_USARTx, USART_FLAG_TXE) == RESET){}
}

// Send array
void SendString(char* Data){
	uint8_t i = 0;
	while(Data[i]!='\0'){
		USART_SendData(USER_USARTx, Data[i]);
		while(USART_GetFlagStatus(USER_USARTx, USART_FLAG_TXE) == RESET){}
		++i;
	}
}

void SendArray(uint8_t* data, uint32_t num){
	uint32_t i=0;
	for(;i<num;i++){
		USART_SendData(USER_USARTx, data[i]);
		while(USART_GetFlagStatus(USER_USARTx, USART_FLAG_TXE) == RESET){}
	}
}
