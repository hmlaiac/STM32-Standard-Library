#ifndef __BSP_I2C_H
#define __BSP_I2C_H
#include "stm32f10x.h"
// RCC enable
#define USER_I2C_RCC_GPIO					RCC_APB2Periph_GPIOB
#define	USER_I2C_RCC							RCC_APB1Periph_I2C1

//port pin select
#define USER_I2Cx 								I2C1

#define USER_SDA_PORT							GPIOB
#define USER_SDA_PIN							GPIO_Pin_7

#define USER_SCL_PORT							GPIOB
#define USER_SCL_PIN							GPIO_Pin_6

//EEPROM select
#define EEPROM_DEVICE_ADDRESS     0xA0

//useful function here
void I2C_EEPROM_Config(void);
void EEPROM_WriteByte(uint8_t address, uint8_t data);
uint8_t EEPROM_ReadByte(void);
#endif  //__BSP_I2C_H
