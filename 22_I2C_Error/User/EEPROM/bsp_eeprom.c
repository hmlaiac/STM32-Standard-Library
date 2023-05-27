#include "bsp_eeprom.h"
static uint32_t Error_Message(char *data){
	SendString(USART1, data);
	return 0;
}

static void _GPIO_Config(){
	GPIO_InitTypeDef  GPIO_Structdef;
	GPIO_Structdef.GPIO_Pin = I2C1_SCL_pin;
	GPIO_Structdef.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Structdef.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_Init(I2C1_SCL, &GPIO_Structdef);
	
	GPIO_Structdef.GPIO_Pin = I2C1_SDA_pin;
	GPIO_Init(I2C1_SDA, &GPIO_Structdef);
}

static void _I2C_Config(){
	I2C_InitTypeDef I2C_Structdef;
	
	I2C_Structdef.I2C_ClockSpeed = 400000;
	I2C_Structdef.I2C_Mode = I2C_Mode_I2C;
	I2C_Structdef.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_Structdef.I2C_OwnAddress1 = 0x0A;   //1011 0001 problem may occur here
	I2C_Structdef.I2C_Ack = I2C_Ack_Enable;
	I2C_Structdef.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	
	I2C_Init(I2C1, &I2C_Structdef);
	I2C_Cmd(I2C1, ENABLE);
}




void RCC_EEPROM_Enable(void){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
}

void EEPROM_Config(void){
	_I2C_Config();
	_GPIO_Config();
}

uint32_t EEPROM_SendByte(uint8_t addr, uint8_t* Data, uint8_t size){
	uint8_t i=0;
	uint16_t countdown = Debug_Flag;
	
	while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY)==SET){
		countdown--;
		if(countdown==0){
			return Error_Message("Bus busy Error");
		}
	}
	
//	countdown = Debug_Flag;
//	I2C_GenerateSTART(I2C1, ENABLE);
//	while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT) == ERROR)
//	{
//		countdown--;
//		if(countdown==0){
//			return Error_Message("Mode1 Error\n");
//		}
//	}
//	
//	countdown = Debug_Flag;
//	I2C_Send7bitAddress(I2C1, 0xA0, I2C_Direction_Transmitter);
//	while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) == ERROR){
//		countdown-=1;
//		if(countdown==0){
//			return Error_Message("Mode transmit fail\n");
//		}
//	}

	
	do{
		I2C_GenerateSTART(I2C1, ENABLE);
		while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT) == ERROR);
		
		I2C_Send7bitAddress(I2C1, 0xA0, I2C_Direction_Transmitter);
	}while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED)==ERROR);
	
	
	countdown = Debug_Flag;
	I2C_SendData(I2C1, addr); //send address
	while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED)==ERROR){}
	
	//send data
	for(;i<size;++i){
		countdown = Debug_Flag;
		while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTING)==ERROR){}
		I2C_SendData(I2C1, Data[i]);
	}

	I2C_GenerateSTOP(I2C1, ENABLE);
	countdown = Debug_Flag;
	while(I2C_CheckEvent(I2C1, I2C_EVENT_SLAVE_STOP_DETECTED) ==ERROR){
			if(countdown==0){
				countdown --;
				return Error_Message("Stop fail\n");
			}
	}
	return 1;
}



uint32_t EEPROM_ReadByte(uint8_t addr, uint8_t* dataGet, uint8_t size){
	uint8_t i=0;	
	uint16_t countdown = Debug_Flag;
	
	I2C_GenerateSTART(I2C1, ENABLE);
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT)) // send start
	{
		countdown--;
		if(countdown==0){
			return Error_Message("Mode2 Error");
		}
	}
	
	
	I2C_Send7bitAddress(I2C1, 0xA0, I2C_Direction_Receiver); //Receiver Mode
	countdown = Debug_Flag;
	while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED) == ERROR){
		countdown --;
		if(countdown==0){
			return Error_Message("Mode transmit fail\n");
		}
	}

	countdown = Debug_Flag;
	I2C_SendData(I2C1, addr); //send address
	while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED)==ERROR){
		countdown --;
		if(countdown==0){
			return Error_Message("Address transmit fail\n");
		}
	}
		
	
	for(;i<size;++i){
		if(i==(size-1)){
			I2C_AcknowledgeConfig(I2C1, DISABLE);
		}
		dataGet[i] = I2C_ReceiveData(I2C1);
		countdown = Debug_Flag;
		while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED) == ERROR){
			countdown--;
			if(countdown==0){
				return Error_Message("Receive data Error");
			}
		};
	}
	
	I2C_AcknowledgeConfig(I2C1, ENABLE);
	I2C_GenerateSTOP(I2C1, ENABLE);
	return 1;
}


