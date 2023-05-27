#ifndef __BSP_SPI_H
#define __BSP_SPI_H
#include "stm32f10x.h"
#include ".\usart\bsp_usart.h"
#define FULL_ADDRESS_ACCESS_MODE      0

#if FULL_ADDRESS_WRITE_MODE
//In this Mode, user is able to write any address. But the writing speed becomes low
void SPI_Sector_FULL_Write();
void SPI_FULL_Write();
#endif

//Memory data
#define Block_size										65536
#define Sector_size										4096
//Debug Flag
static uint8_t SPI_Debuy_SUCCESS = 0;
#define SPI_Debuy_UKNOW_ERROR					(uint8_t)0x1
#define SPI_TIME_OUT								  (uint8_t)0x10
#define SPI_ALWAYS_BUSY								(uint8_t)0x100
#define SPI_POWER_DOWN_FLAG						(uint8_t)0x1000
#define SPI_DEVICE_ID_ERROR						(uint8_t)0x10000

#define Dummy	        						(uint8_t)0xFF
//memory allocation
#define Block(a)                  (a*0x10000)
#define Sector(a)									(a*0x1000)
#define Flash_address(a,b)				(a*0x10000+b*0x1000)
//general define
#define USER_SPI_BASE    					SPI1

//RCC


//pin & port
#define	SPI_CS_PORT								GPIOC
#define	SPI_CS_PIN								GPIO_Pin_0

#define	SPI_SCK_PORT							GPIOA
#define	SPI_SCK_PIN								GPIO_Pin_5

#define	SPI_MOSI_PORT							GPIOA
#define	SPI_MOSI_PIN							GPIO_Pin_7

#define	SPI_MISO_PORT							GPIOA
#define	SPI_MISO_PIN							GPIO_Pin_6

//useful function here
#define SPI_CS_LOW()     						GPIO_ResetBits(SPI_CS_PORT, SPI_CS_PIN )
#define SPI_CS_HIGH()    						GPIO_SetBits(SPI_CS_PORT, SPI_CS_PIN )					

void SPI_CONFIG(void);
void SPI_delay(uint32_t num); 
void Write_Enable(void);

uint8_t SPI_Power_Down(void);
uint8_t SPI_Release_Power_Down(void);
uint8_t SPI_Get_Device_ID(uint8_t* data);
uint8_t SPI_Get_JEDEC_ID(uint8_t *data);
uint8_t SPI_Sector_Erase(uint32_t address);
uint8_t SPI_Read_data(uint8_t *data, uint32_t address, uint32_t num_to_read);
uint8_t SPI_SectorWrite(uint8_t* data, uint32_t address, uint32_t size);
uint8_t BufferWrite(uint8_t* data, uint32_t address, uint32_t size);
uint8_t Chip_Erase(uint8_t enable);

#endif //__BSP_SPI_H
