#include "stm32f10x.h"
#include "bsp_led.h"
#include ".\usart\bsp_usart.h"
#include ".\i2c\bsp_i2c.h"
#include ".\spi\bsp_spi.h"
uint8_t read_buffer[5120];
uint8_t write_buffer[5120];
uint8_t data[8];

int main(void){
	uint32_t addr = 0;
	uint16_t i=0;
	usart_config();
	SPI_CONFIG();
	SPI_Release_Power_Down();
	SPI_Get_Device_ID(data);
	SendArray(data,1);
	SPI_Get_JEDEC_ID(data);
	SendArray(data,3);
	
	for(i=0;i<5120;i++){
		write_buffer[i] = 0xAA;
	}
	
//	BufferWrite(write_buffer, 0x5000, 5120);
//	for(i=0;i<2048;i++){
//		SPI_Read_data(read_buffer, addr, 4096);
//		SendArray(read_buffer,4096);
//		addr+=0x1000;
//	}
	
//	Chip_Erase(1);

	while(1){
	}
}
