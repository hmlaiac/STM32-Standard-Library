#include "bsp_i2c.h"

void RCC_I2C_Enable(void){
	RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C1, ENABLE);
}

void I2C_Config(void){
	I2C_InitTypeDef I2C_Structdef;
	I2C_Structdef.I2C_ClockSpeed = 400000;
	I2C_Structdef.I2C_Mode = I2C_Mode_I2C;
	I2C_Structdef.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_Structdef.I2C_OwnAddress1 = (0xA);   //1011 0001 problem may occur here
	I2C_Structdef.I2C_Ack = I2C_Ack_Enable;
	I2C_Structdef.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_Init(I2C1, &I2C_Structdef);
	I2C_Cmd(I2C1, ENABLE);
}
