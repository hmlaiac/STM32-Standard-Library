#include ".\i2c\bsp_i2c.h"
static void delay(){
	uint8_t i =100;
	while(i--);
}

static void RCC_I2C_ENABLE(){
	RCC_APB2PeriphClockCmd(USER_I2C_RCC_GPIO,ENABLE);
	RCC_APB1PeriphClockCmd(USER_I2C_RCC,ENABLE);
}

static void GPIO_Config(){
	GPIO_InitTypeDef 	  	GPIO_SDA;
	GPIO_SDA.GPIO_Mode = 	GPIO_Mode_AF_OD;
	GPIO_SDA.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_SDA.GPIO_Pin = 	USER_SDA_PIN;
	GPIO_Init(USER_SDA_PORT, &GPIO_SDA);
	
	GPIO_InitTypeDef 	  	GPIO_SCL;
	GPIO_SCL.GPIO_Mode = 	GPIO_Mode_AF_OD;
	GPIO_SCL.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_SCL.GPIO_Pin = 	USER_SCL_PIN;
	GPIO_Init(USER_SCL_PORT, &GPIO_SCL);
}

static void I2C_Config(){
	I2C_InitTypeDef I2C_Def;
	I2C_Def.I2C_Ack = I2C_Ack_Enable;
	I2C_Def.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_Def.I2C_ClockSpeed = 400000;
	I2C_Def.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_Def.I2C_Mode = I2C_Mode_I2C;
	I2C_Def.I2C_OwnAddress1  = 0x7F;
	
	I2C_Init(USER_I2Cx, &I2C_Def);
	I2C_Cmd(USER_I2Cx,ENABLE);
}

void I2C_EEPROM_Config(void){
	RCC_I2C_ENABLE();
	GPIO_Config();
	I2C_Config();
}

void EEPROM_WriteByte(uint8_t address, uint8_t data){
	delay();
	while(I2C_GetFlagStatus(USER_I2Cx, I2C_FLAG_BUSY));
	I2C_GenerateSTART(USER_I2Cx,ENABLE);
	while(I2C_CheckEvent(USER_I2Cx,I2C_EVENT_MASTER_MODE_SELECT)==ERROR){}
	delay();			
	I2C_Send7bitAddress(USER_I2Cx, EEPROM_DEVICE_ADDRESS, I2C_Direction_Transmitter);
	while(I2C_CheckEvent(USER_I2Cx,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)==ERROR);
		
	I2C_SendData(USER_I2Cx, address);
	while(I2C_CheckEvent(USER_I2Cx,I2C_EVENT_MASTER_BYTE_TRANSMITTED) ==ERROR){}
	
	I2C_SendData(USER_I2Cx, data);
	while(I2C_CheckEvent(USER_I2Cx,I2C_EVENT_MASTER_BYTE_TRANSMITTED)==ERROR){}
		
	I2C_GenerateSTOP(USER_I2Cx,ENABLE);
	delay();	
}

uint8_t EEPROM_ReadByte(void){
	delay();
	uint8_t temp;
	while(I2C_GetFlagStatus(USER_I2Cx, I2C_FLAG_BUSY));
	I2C_GenerateSTART(USER_I2Cx,ENABLE);
	while(I2C_CheckEvent(USER_I2Cx,I2C_EVENT_MASTER_MODE_SELECT)==ERROR){}
	delay();	
	I2C_Send7bitAddress(USER_I2Cx, EEPROM_DEVICE_ADDRESS, I2C_Direction_Receiver);
	while(I2C_CheckEvent(USER_I2Cx,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED)==ERROR);
	
	I2C_AcknowledgeConfig(USER_I2Cx,DISABLE);
	temp = I2C_ReceiveData(USER_I2Cx);
	while(I2C_CheckEvent(USER_I2Cx,I2C_EVENT_MASTER_BYTE_RECEIVED )==ERROR){}
		
	I2C_GenerateSTOP(USER_I2Cx,ENABLE);
	I2C_AcknowledgeConfig(USER_I2Cx,ENABLE);
	delay();	
	return temp;
}
