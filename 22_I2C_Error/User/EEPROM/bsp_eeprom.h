#ifndef __BSP_EEPROM_H
#define __BSP_EEPROM_H
#include "stm32f10x.h"
#include "bsp_usart.h"
#include "bsp_systick.h"
//address
#define I2C1_SCL				    GPIOB
#define I2C1_SDA				    GPIOB
#define I2C1_SCL_pin				GPIO_Pin_6
#define I2C1_SDA_pin				GPIO_Pin_7

//useful function here
void RCC_EEPROM_Enable(void);
void EEPROM_Config(void);
//command
uint32_t EEPROM_SendByte(uint8_t addr, uint8_t* Data, uint8_t size);
uint32_t EEPROM_ReadByte(uint8_t addr, uint8_t* dataGet, uint8_t size);


//Debug message
#define Debug_Flag        (uint16_t)10000
#endif
