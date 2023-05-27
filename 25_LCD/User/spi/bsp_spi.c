#include ".\spi\bsp_spi.h"
uint8_t SPI_Debuy_SUCCESS;

static void SPI_RCC_CONFIG(){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1,ENABLE);
}

static void GPIO_CONFIG(){
	GPIO_InitTypeDef GPIO_Init_param;
	//Initialization of CS
	GPIO_Init_param.GPIO_Pin = SPI_CS_PIN; 
	GPIO_Init_param.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init_param.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SPI_CS_PORT, &GPIO_Init_param);
	//Initialization of SCK
	GPIO_Init_param.GPIO_Pin = SPI_SCK_PIN; 
	GPIO_Init_param.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(SPI_SCK_PORT, &GPIO_Init_param);
	//Initialization of MOSI
	GPIO_Init_param.GPIO_Pin = SPI_MOSI_PIN; 
	GPIO_Init_param.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(SPI_MOSI_PORT, &GPIO_Init_param);
	//Initialization of MISO
	GPIO_Init_param.GPIO_Pin = SPI_MISO_PIN; 
	GPIO_Init_param.GPIO_Mode = GPIO_Mode_AF_PP;;
	GPIO_Init(SPI_MISO_PORT, &GPIO_Init_param);
}

static void SPI_INIT(){
	SPI_InitTypeDef temp;
	temp.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
	temp.SPI_CPHA = SPI_CPHA_2Edge;
	temp.SPI_CPOL = SPI_CPOL_High;
	temp.SPI_CRCPolynomial = 7;		//CRC?
	temp.SPI_DataSize = SPI_DataSize_8b;
	temp.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	temp.SPI_FirstBit = SPI_FirstBit_MSB;
	temp.SPI_Mode = SPI_Mode_Master;
	temp.SPI_NSS = SPI_NSS_Soft;
	
	SPI_Init(USER_SPI_BASE,&temp);
	SPI_Cmd(USER_SPI_BASE, ENABLE);
}

void SPI_CONFIG(void){
	SPI_RCC_CONFIG();
	GPIO_CONFIG();
	SPI_CS_HIGH();
	SPI_INIT();
}

//Time Check

//Flash Command
void Write_Enable(void){
	SPI_CS_LOW();
	SPI_I2S_SendData(USER_SPI_BASE, 0x06);
	while(SPI_I2S_GetFlagStatus(USER_SPI_BASE,SPI_I2S_FLAG_TXE)==RESET){}
	SPI_CS_HIGH();
}

uint8_t ReadByte(uint8_t data){
	while(SPI_I2S_GetFlagStatus(USER_SPI_BASE,SPI_I2S_FLAG_TXE)==RESET){}
	SPI_I2S_SendData(USER_SPI_BASE, data);
	while(SPI_I2S_GetFlagStatus(USER_SPI_BASE,SPI_I2S_FLAG_RXNE)==RESET){}
	return SPI_I2S_ReceiveData(USER_SPI_BASE);
}

uint8_t Release_Power_Down(void){
	uint8_t data;	

	SPI_CS_LOW();
	ReadByte(0xAB); 
	ReadByte(0xFF);
	ReadByte(0xFF);
	ReadByte(0xFF);
	
	data = ReadByte(0xFF);;
	SPI_CS_HIGH();
	
	SPI_Debuy_SUCCESS &=~ SPI_POWER_DOWN;
	
	if(data!=0x16){
		SPI_Debuy_SUCCESS |= SPI_DEVICE_ID_ERROR;
	}
	return SPI_Debuy_SUCCESS;
}

static uint8_t Wait_For_Process(){
	uint8_t state = 0;
	uint32_t i = 0xFFFFFF;
	SPI_CS_LOW();
	ReadByte(0x05); 
	do{
		state = ReadByte(Dummy);
		state &= 0x1;
		if(i==0){  //counting for 10000 loop error
			SendString("Bus Busy Error");
			return 0;
		}
		i--;
	}while(state == 1); // the process is still busy
	
	SPI_CS_HIGH();
	return 1;
}

uint8_t Get_Device_ID(uint8_t* data){

	SPI_CS_LOW();
	ReadByte(0xAB); 
	ReadByte(Dummy);
	ReadByte(Dummy);
	ReadByte(Dummy);
	
	*data = ReadByte(Dummy);;
	SPI_CS_HIGH();
	
	if(*data==0x16) return 1;else return 0;
}

//This ID is followed by the standard of JEDEC
uint8_t Get_JEDEC_ID(uint8_t *data){
	/*data0 is manufacturer ID, data1 is memory id, data2 is capacity id*/
	SPI_CS_LOW();
	ReadByte(0x9F);
	data[0] = ReadByte(Dummy);
	data[1] = ReadByte(Dummy);
	data[2] = ReadByte(Dummy);
	SPI_CS_HIGH();
	if(data[0]==0x9F) return 1;else return 0;
}

static void WriteEnable(){
	SPI_CS_LOW();
	ReadByte(0x06);
	SPI_CS_HIGH();
}

uint8_t Sector_Erase(uint32_t address){
	uint8_t temp;
	WriteEnable();
	SPI_CS_LOW();
	ReadByte(0x20);
	temp = (address&0xFF0000)>>16;
	ReadByte(temp);
	temp = (address&0x00FF00)>>8;
	ReadByte(temp);
	temp = (address&0x0000FF)>>0;
	ReadByte(temp);
	SPI_CS_HIGH();
	Wait_For_Process();
	return 1;
}

uint8_t Read_data(uint8_t *data, uint32_t address, uint32_t num_to_read){
	uint8_t temp;
	WriteEnable();
	SPI_CS_LOW();
	ReadByte(0x03);
	ReadByte((address&0xFF0000)>>16);
	ReadByte((address&0xFF00)>>8);
	ReadByte((address&0xFF));
	
	//Read data
	uint32_t i=0;
	for(;i<num_to_read;i++){
		data[i] = ReadByte(Dummy);
	}
	SPI_CS_HIGH();
	return temp;
}

uint8_t Page_Program(uint8_t* data, uint32_t address, uint32_t size){
	if(size>256) return 0;//size not access
	
	Sector_Erase(address);
	WriteEnable();
	SPI_CS_LOW();
	ReadByte(0x02);
	ReadByte((address&0xFF0000)>>16);
	ReadByte((address&0xFF00)>>8);
	ReadByte((address&0xFF));
	
	//write data
	uint32_t i;
	for(i=0;i<size;i++){
		 ReadByte(data[i]);
	}
	SPI_CS_HIGH();
	Wait_For_Process();
	return 1;
}

void SPI_delay(uint32_t num){
	while(num--){};
}

uint8_t Power_Down(void){
	SPI_CS_LOW();
	ReadByte(0xB9);
	SPI_CS_HIGH();
	SPI_delay(0x1000);
	SPI_Debuy_SUCCESS |= SPI_POWER_DOWN;
	return SPI_POWER_DOWN;
}
