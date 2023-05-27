#ifndef __BSP_USART_H
#define __BSP_USART_H
#include "stm32f10x.h"

//RCC select
#define USER_USART_RCC_GPIO					RCC_APB2Periph_GPIOA
#define USER_USART_RCC_USARTx					RCC_APB2Periph_USART1

//port and pin select
#define USER_USARTx    					USART1
#define USER_USART_TX_PORT			GPIOA
#define USER_USART_TX_PIN				GPIO_Pin_9

#define USER_USART_RX_PORT			GPIOA
#define USER_USART_RX_PIN				GPIO_Pin_10

//useful function here
void usart_config(void);
void SendByte(uint8_t Data);
void SendString(char* Data);
void SendArray(uint8_t* data, uint32_t num);
#endif //__BSP_USART_H
