#ifndef __BSP_USART_H
#define __BSP_USART_H
#include "stm32f10x.h"
#include <stdio.h>
#define USART_X					USART1

#define USART_rx_port		GPIOA
#define USART_tx_port		GPIOA
#define USART_rx_pin		GPIO_Pin_9
#define USART_tx_pin		GPIO_Pin_10


void usart_config(void);
void SendArray(uint8_t *data, uint32_t size);
void SendByte(uint8_t Data);
void SendString(char* Data);

#endif
