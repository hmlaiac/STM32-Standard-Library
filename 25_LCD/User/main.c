#include "stm32f10x.h"
#include ".\usart\bsp_usart.h"
#include ".\i2c\bsp_i2c.h"
#include ".\spi\bsp_spi.h"
#include ".\lcd\bsp_lcd.h"
uint8_t read_buffer[512];
uint8_t write_buffer[256];
uint8_t data[8];

int main(void){
	usart_config();
	LCD_CONFIG();
	LCD_Test();
	while(1){
	}
}
