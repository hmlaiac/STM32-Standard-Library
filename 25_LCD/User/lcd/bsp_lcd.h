#ifndef BSP_LCD_H
#define BSP_LCD_H
#include "stm32f10x.h"
#include ".\usart\bsp_usart.h"
//RCC CLK
#define LCD_GPIO								RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE,\
																ENABLE)																
#define FSMC_CLK_CMD						RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC,ENABLE)

//pin & port
#define LCD_FSMC_DATA_0_PORT				GPIOD
#define LCD_FSMC_DATA_0_PIN					GPIO_Pin_14
#define LCD_FSMC_DATA_1_PORT				GPIOD
#define LCD_FSMC_DATA_1_PIN					GPIO_Pin_15
#define LCD_FSMC_DATA_2_PORT				GPIOD
#define LCD_FSMC_DATA_2_PIN					GPIO_Pin_0
#define LCD_FSMC_DATA_3_PORT				GPIOD
#define LCD_FSMC_DATA_3_PIN					GPIO_Pin_1
#define LCD_FSMC_DATA_4_PORT				GPIOE
#define LCD_FSMC_DATA_4_PIN					GPIO_Pin_7
#define LCD_FSMC_DATA_5_PORT				GPIOE
#define LCD_FSMC_DATA_5_PIN					GPIO_Pin_8
#define LCD_FSMC_DATA_6_PORT				GPIOE
#define LCD_FSMC_DATA_6_PIN					GPIO_Pin_9
#define LCD_FSMC_DATA_7_PORT				GPIOE
#define LCD_FSMC_DATA_7_PIN					GPIO_Pin_10
#define LCD_FSMC_DATA_8_PORT				GPIOE
#define LCD_FSMC_DATA_8_PIN					GPIO_Pin_11
#define LCD_FSMC_DATA_9_PORT				GPIOE
#define LCD_FSMC_DATA_9_PIN					GPIO_Pin_12
#define LCD_FSMC_DATA_10_PORT				GPIOE
#define LCD_FSMC_DATA_10_PIN				GPIO_Pin_13
#define LCD_FSMC_DATA_11_PORT				GPIOE
#define LCD_FSMC_DATA_11_PIN				GPIO_Pin_14
#define LCD_FSMC_DATA_12_PORT				GPIOE
#define LCD_FSMC_DATA_12_PIN				GPIO_Pin_15
#define LCD_FSMC_DATA_13_PORT				GPIOD
#define LCD_FSMC_DATA_13_PIN				GPIO_Pin_8
#define LCD_FSMC_DATA_14_PORT				GPIOD
#define LCD_FSMC_DATA_14_PIN				GPIO_Pin_9
#define LCD_FSMC_DATA_15_PORT				GPIOD
#define LCD_FSMC_DATA_15_PIN				GPIO_Pin_10

#define LCD_FSMC_NE_PORT						GPIOD
#define LCD_FSMC_NE_PIN							GPIO_Pin_7
#define LCD_FSMC_NOE_PORT						GPIOD
#define LCD_FSMC_NOE_PIN						GPIO_Pin_4
#define LCD_FSMC_NWE_PORT						GPIOD
#define LCD_FSMC_NWE_PIN						GPIO_Pin_5
#define LCD_FSMC_CMD_PORT						GPIOD
#define LCD_FSMC_CMD_PIN						GPIO_Pin_11

#define LCD_RST_PORT								GPIOE
#define LCD_RST_PIN									GPIO_Pin_1
#define LCD_BL_PORT									GPIOD
#define LCD_BL_PIN									GPIO_Pin_12

//FSMC BANK Address
#define LCD_BANK										FSMC_Bank1_NORSRAM1
#define LCD_Data										(uint32_t)(0x60020000)
#define LCD_Command									(uint32_t)(0x60000000)

//Display Information
#define      CMD_SetCoordinateX		 		    0x2A	     //设置X坐标
#define      CMD_SetCoordinateY		 		    0x2B	     //设置Y坐标
#define      CMD_SetPixel		 		          0x2C	     //填充像素
#define 			ILI9341_LESS_PIXEL	  							240			//液晶屏较短方向的像素宽度
#define 			ILI9341_MORE_PIXEL	 								320			//液晶屏较长方向的像素宽度

//useful function here
void LCD_CONFIG(void);
void LCD_WriteCommand(uint16_t command);
void LCD_WriteData(uint16_t data);
uint16_t LCD_ReadData(void);
//implementing functions
void LCD_Sleep_Mode(void);
void LCD_WakeUP(void);
/* **************Debuy Area*************** is here */
#define DEBUG_DELAY()
void LCD_Test(void);
#endif //BSP_LCD_H
