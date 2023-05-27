#ifndef __BSP_USART_H
#define __BSP_USART_H
#include "stm32f10x.h"

#define USART_rx_port		GPIOA
#define USART_tx_port		GPIOA
#define USART_rx_pin		GPIO_Pin_9
#define USART_tx_pin		GPIO_Pin_10

//useful funcdtion here;
void RCC_USART_Enable(void);
void usart_config(void);
void SendByte(USART_TypeDef* USARTx, uint8_t Data);
void SendString(USART_TypeDef* USARTx, uint8_t* Data);

#endif
