#include ".\lcd\bsp_lcd.h"
static void LCD_RCC_ENABLE(){
	LCD_GPIO;
	FSMC_CLK_CMD;
}

static void LCD_GPIO_INIT(){
	GPIO_InitTypeDef  temp;
	temp.GPIO_Mode = GPIO_Mode_AF_PP;
	temp.GPIO_Speed = GPIO_Speed_50MHz;
	//Define FSMC data pins INIT here
	temp.GPIO_Pin = LCD_FSMC_DATA_0_PIN;
	GPIO_Init(LCD_FSMC_DATA_0_PORT,&temp);
	
	temp.GPIO_Pin = LCD_FSMC_DATA_1_PIN;
	GPIO_Init(LCD_FSMC_DATA_1_PORT,&temp);
	
	temp.GPIO_Pin = LCD_FSMC_DATA_2_PIN;
	GPIO_Init(LCD_FSMC_DATA_2_PORT,&temp);
	
	temp.GPIO_Pin = LCD_FSMC_DATA_3_PIN;
	GPIO_Init(LCD_FSMC_DATA_3_PORT,&temp);
	
	temp.GPIO_Pin = LCD_FSMC_DATA_4_PIN;
	GPIO_Init(LCD_FSMC_DATA_4_PORT,&temp);
	
	temp.GPIO_Pin = LCD_FSMC_DATA_5_PIN;
	GPIO_Init(LCD_FSMC_DATA_5_PORT,&temp);
	
	temp.GPIO_Pin = LCD_FSMC_DATA_6_PIN;
	GPIO_Init(LCD_FSMC_DATA_6_PORT,&temp);
	
	temp.GPIO_Pin = LCD_FSMC_DATA_7_PIN;
	GPIO_Init(LCD_FSMC_DATA_7_PORT,&temp);
	
	temp.GPIO_Pin = LCD_FSMC_DATA_8_PIN;
	GPIO_Init(LCD_FSMC_DATA_8_PORT,&temp);
	
	temp.GPIO_Pin = LCD_FSMC_DATA_9_PIN;
	GPIO_Init(LCD_FSMC_DATA_9_PORT,&temp);
	
	temp.GPIO_Pin = LCD_FSMC_DATA_10_PIN;
	GPIO_Init(LCD_FSMC_DATA_10_PORT,&temp);
	
	temp.GPIO_Pin = LCD_FSMC_DATA_11_PIN;
	GPIO_Init(LCD_FSMC_DATA_11_PORT,&temp);
	
	temp.GPIO_Pin = LCD_FSMC_DATA_12_PIN;
	GPIO_Init(LCD_FSMC_DATA_12_PORT,&temp);
	
	temp.GPIO_Pin = LCD_FSMC_DATA_13_PIN;
	GPIO_Init(LCD_FSMC_DATA_13_PORT,&temp);
	
	temp.GPIO_Pin = LCD_FSMC_DATA_14_PIN;
	GPIO_Init(LCD_FSMC_DATA_14_PORT,&temp);
	
	temp.GPIO_Pin = LCD_FSMC_DATA_15_PIN;
	GPIO_Init(LCD_FSMC_DATA_15_PORT,&temp);
	
	//other FSMC pin
	temp.GPIO_Pin = LCD_FSMC_NE_PIN	;
	GPIO_Init(LCD_FSMC_NE_PORT,&temp);
	
	temp.GPIO_Pin = LCD_FSMC_NOE_PIN	;
	GPIO_Init(LCD_FSMC_NOE_PORT,&temp);

	temp.GPIO_Pin = LCD_FSMC_NWE_PIN;
	GPIO_Init(LCD_FSMC_NWE_PORT	,&temp);

	temp.GPIO_Pin = LCD_FSMC_CMD_PIN;
	GPIO_Init(LCD_FSMC_CMD_PORT,&temp);

	
	//LCD reset and back_light pin
	temp.GPIO_Mode = GPIO_Mode_Out_PP;
	
	temp.GPIO_Pin = LCD_RST_PIN;
	GPIO_Init(LCD_RST_PORT, &temp);
	
	temp.GPIO_Pin = LCD_BL_PIN;
	GPIO_Init(LCD_BL_PORT, &temp);
}

static void LCD_FSMC_INIT(){
	FSMC_NORSRAMTimingInitTypeDef time_temp;
	time_temp.FSMC_AccessMode = FSMC_AccessMode_B;
	time_temp.FSMC_DataSetupTime = 0x4;
	time_temp.FSMC_AddressSetupTime = 0x1;
	time_temp.FSMC_AddressHoldTime = 0x0;
	time_temp.FSMC_BusTurnAroundDuration = 0;
	time_temp.FSMC_CLKDivision = 0x1;
	time_temp.FSMC_DataLatency = 0;
	
	FSMC_NORSRAMInitTypeDef temp;
	temp.FSMC_Bank = LCD_BANK; //used
	temp.FSMC_ExtendedMode = FSMC_ExtendedMode_Enable; //used
	temp.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b; //used
	temp.FSMC_MemoryType = FSMC_MemoryType_NOR; // used
	temp.FSMC_WriteOperation = FSMC_WriteOperation_Enable; //used
	temp.FSMC_AsynchronousWait = FSMC_AsynchronousWait_Disable;
	temp.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;
	temp.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;
	temp.FSMC_WaitSignal = 0;
	temp.FSMC_WaitSignalActive = 0;
	temp.FSMC_WaitSignalPolarity = 0;
	temp.FSMC_WrapMode = 0;
	temp.FSMC_WriteBurst = 0;
	
	temp.FSMC_ReadWriteTimingStruct = &time_temp;	
	temp.FSMC_WriteTimingStruct = &time_temp;
	
	FSMC_NORSRAMInit(&temp);
	FSMC_NORSRAMCmd(LCD_BANK,ENABLE);
}



void LCD_WriteCommand(uint16_t command){
	*(volatile uint16_t*)(LCD_Command) = command;
}

void LCD_WriteData(uint16_t data){
	*(volatile uint16_t*)(LCD_Data) = data;
}

uint16_t LCD_ReadData(void){
	return ( * ( volatile uint16_t * ) ( LCD_Data ) );
}


static void ILI9341_Delay ( __IO uint32_t nCount )
{
  for ( ; nCount != 0; nCount -- );
	
}

static void ILI9341_REG_Config ( void )
{
	/*  Power control B (CFh)  */
	DEBUG_DELAY  ();
	LCD_WriteCommand ( 0xCF  );
	LCD_WriteData ( 0x00  );
	LCD_WriteData ( 0x81  );
	LCD_WriteData ( 0x30  );
	
	/*  Power on sequence control (EDh) */
	DEBUG_DELAY ();
	LCD_WriteCommand ( 0xED );
	LCD_WriteData ( 0x64 );
	LCD_WriteData ( 0x03 );
	LCD_WriteData ( 0x12 );
	LCD_WriteData ( 0x81 );
	
	/*  Driver timing control A (E8h) */
	DEBUG_DELAY ();
	LCD_WriteCommand ( 0xE8 );
	LCD_WriteData ( 0x85 );
	LCD_WriteData ( 0x10 );
	LCD_WriteData ( 0x78 );
	
	/*  Power control A (CBh) */
	DEBUG_DELAY ();
	LCD_WriteCommand ( 0xCB );
	LCD_WriteData ( 0x39 );
	LCD_WriteData ( 0x2C );
	LCD_WriteData ( 0x00 );
	LCD_WriteData ( 0x34 );
	LCD_WriteData ( 0x02 );
	
	/* Pump ratio control (F7h) */
	DEBUG_DELAY ();
	LCD_WriteCommand ( 0xF7 );
	LCD_WriteData ( 0x20 );
	
	/* Driver timing control B */
	DEBUG_DELAY ();
	LCD_WriteCommand ( 0xEA );
	LCD_WriteData ( 0x00 );
	LCD_WriteData ( 0x00 );
	
	/* Frame Rate Control (In Normal Mode/Full Colors) (B1h) */
	DEBUG_DELAY ();
	LCD_WriteCommand ( 0xB1 );
	LCD_WriteData ( 0x00 );
	LCD_WriteData ( 0x1B );
	
	/*  Display Function Control (B6h) */
	DEBUG_DELAY ();
	LCD_WriteCommand ( 0xB6 );
	LCD_WriteData ( 0x0A );
	LCD_WriteData ( 0xA2 );
	
	/* Power Control 1 (C0h) */
	DEBUG_DELAY ();
	LCD_WriteCommand ( 0xC0 );
	LCD_WriteData ( 0x35 );
	
	/* Power Control 2 (C1h) */
	DEBUG_DELAY ();
	LCD_WriteCommand ( 0xC1 );
	LCD_WriteData ( 0x11 );
	
	/* VCOM Control 1 (C5h) */
	LCD_WriteCommand ( 0xC5 );
	LCD_WriteData ( 0x45 );
	LCD_WriteData ( 0x45 );
	
	/*  VCOM Control 2 (C7h)  */
	LCD_WriteCommand ( 0xC7 );
	LCD_WriteData ( 0xA2 );
	
	/* Enable 3G (F2h) */
	LCD_WriteCommand ( 0xF2 );
	LCD_WriteData ( 0x00 );
	
	/* Gamma Set (26h) */
	LCD_WriteCommand ( 0x26 );
	LCD_WriteData ( 0x01 );
	DEBUG_DELAY ();
	
	/* Positive Gamma Correction */
	LCD_WriteCommand ( 0xE0 ); //Set Gamma
	LCD_WriteData ( 0x0F );
	LCD_WriteData ( 0x26 );
	LCD_WriteData ( 0x24 );
	LCD_WriteData ( 0x0B );
	LCD_WriteData ( 0x0E );
	LCD_WriteData ( 0x09 );
	LCD_WriteData ( 0x54 );
	LCD_WriteData ( 0xA8 );
	LCD_WriteData ( 0x46 );
	LCD_WriteData ( 0x0C );
	LCD_WriteData ( 0x17 );
	LCD_WriteData ( 0x09 );
	LCD_WriteData ( 0x0F );
	LCD_WriteData ( 0x07 );
	LCD_WriteData ( 0x00 );
	
	/* Negative Gamma Correction (E1h) */
	LCD_WriteCommand ( 0XE1 ); //Set Gamma
	LCD_WriteData ( 0x00 );
	LCD_WriteData ( 0x19 );
	LCD_WriteData ( 0x1B );
	LCD_WriteData ( 0x04 );
	LCD_WriteData ( 0x10 );
	LCD_WriteData ( 0x07 );
	LCD_WriteData ( 0x2A );
	LCD_WriteData ( 0x47 );
	LCD_WriteData ( 0x39 );
	LCD_WriteData ( 0x03 );
	LCD_WriteData ( 0x06 );
	LCD_WriteData ( 0x06 );
	LCD_WriteData ( 0x30 );
	LCD_WriteData ( 0x38 );
	LCD_WriteData ( 0x0F );
	
	/* memory access control set */
	DEBUG_DELAY ();
	LCD_WriteCommand ( 0x36 ); 	
	LCD_WriteData ( 0xC8 );    /*竖屏  左上角到 (起点)到右下角 (终点)扫描方式*/
	DEBUG_DELAY ();
	
	/* column address control set */
	LCD_WriteCommand ( CMD_SetCoordinateX ); 
	LCD_WriteData ( 0x00 );
	LCD_WriteData ( 0x00 );
	LCD_WriteData ( 0x00 );
	LCD_WriteData ( 0xEF );
	
	/* page address control set */
	DEBUG_DELAY ();
	LCD_WriteCommand ( CMD_SetCoordinateY ); 
	LCD_WriteData ( 0x00 );
	LCD_WriteData ( 0x00 );
	LCD_WriteData ( 0x01 );
	LCD_WriteData ( 0x3F );
	
	/*  Pixel Format Set (3Ah)  */
	DEBUG_DELAY ();
	LCD_WriteCommand ( 0x3a ); 
	LCD_WriteData ( 0x55 );
	
	/* Sleep Out (11h)  */
	LCD_WriteCommand ( 0x11 );	
	ILI9341_Delay ( 0xAFFf<<2 );
	DEBUG_DELAY ();
	
	/* Display ON (29h) */
	LCD_WriteCommand ( 0x29 ); 
	
	
}

void ILI9341_GramScan ( uint8_t ucOption )
{	
	uint16_t LCD_SCAN_MODE, LCD_X_LENGTH, LCD_Y_LENGTH;
	//参数检查，只可输入0-7
	if(ucOption >7 )
		return;
	
	//根据模式更新LCD_SCAN_MODE的值，主要用于触摸屏选择计算参数
	LCD_SCAN_MODE = ucOption;
	
	//根据模式更新XY方向的像素宽度
	if(ucOption%2 == 0)	
	{
		//0 2 4 6模式下X方向像素宽度为240，Y方向为320
		LCD_X_LENGTH = ILI9341_LESS_PIXEL;
		LCD_Y_LENGTH =	ILI9341_MORE_PIXEL;
	}
	else				
	{
		//1 3 5 7模式下X方向像素宽度为320，Y方向为240
		LCD_X_LENGTH = ILI9341_MORE_PIXEL;
		LCD_Y_LENGTH =	ILI9341_LESS_PIXEL; 
	}

	//0x36命令参数的高3位可用于设置GRAM扫描方向	
	LCD_WriteCommand ( 0x36 ); 
	LCD_WriteData ( 0x08 |(ucOption<<5));//根据ucOption的值设置LCD参数，共0-7种模式
	LCD_WriteCommand ( CMD_SetCoordinateX ); 
	LCD_WriteData ( 0x00 );		/* x 起始坐标高8位 */
	LCD_WriteData ( 0x00 );		/* x 起始坐标低8位 */
	LCD_WriteData ( ((LCD_X_LENGTH-1)>>8)&0xFF ); /* x 结束坐标高8位 */	
	LCD_WriteData ( (LCD_X_LENGTH-1)&0xFF );				/* x 结束坐标低8位 */

	LCD_WriteCommand ( CMD_SetCoordinateY ); 
	LCD_WriteData ( 0x00 );		/* y 起始坐标高8位 */
	LCD_WriteData ( 0x00 );		/* y 起始坐标低8位 */
	LCD_WriteData ( ((LCD_Y_LENGTH-1)>>8)&0xFF );	/* y 结束坐标高8位 */	 
	LCD_WriteData ( (LCD_Y_LENGTH-1)&0xFF );				/* y 结束坐标低8位 */

	/* write gram start */
	LCD_WriteCommand ( CMD_SetPixel );	
}

void ILI9341_BackLed_Control ( FunctionalState enumState )
{
	if ( enumState )
		GPIO_ResetBits ( LCD_BL_PORT, LCD_BL_PIN );	
	else
		GPIO_SetBits ( LCD_BL_PORT, LCD_BL_PIN );
		
}



/**
 * @brief  ILI9341 软件复位
 * @param  无
 * @retval 无
 */
void ILI9341_Rst ( void )
{			
	GPIO_ResetBits ( LCD_RST_PORT, LCD_RST_PIN );	 //低电平复位

	ILI9341_Delay ( 0xAFF ); 					   

	GPIO_SetBits ( LCD_RST_PORT, LCD_RST_PIN );		 	 

	ILI9341_Delay ( 0xAFF ); 	
	
}

void LCD_CONFIG(void){
	LCD_RCC_ENABLE();
	LCD_GPIO_INIT();
	LCD_FSMC_INIT();
	ILI9341_BackLed_Control ( ENABLE );      //点亮LCD背光灯
	ILI9341_Rst ();
	ILI9341_REG_Config();
	ILI9341_GramScan(6);
}

uint32_t LCD_Create_Window(uint16_t posX1, uint16_t posX2, uint16_t posY1, uint16_t posY2){
	uint32_t window_size = (posX2-posX1) * (posY2-posY1);
	LCD_WriteCommand(0x2A);
	LCD_WriteData(posX1>>8);
	LCD_WriteData((posX1&0xFF));
	LCD_WriteData(posX2>>8);
	LCD_WriteData((posX2&0xFF));
	
	LCD_WriteCommand(0x2B);
	LCD_WriteData(posY1>>8);
	LCD_WriteData((posY1&0xFF));
	LCD_WriteData(posY2>>8);
	LCD_WriteData((posY2&0xFF));
	return window_size;
}

void LCD_Memory_Write(uint32_t color_16b, uint32_t window_size){
	LCD_WriteCommand(0x2C);
	
	for(uint32_t i=0;i<window_size;i++){
		LCD_WriteData(color_16b);
	}
}



void LCD_Test(void){
	uint32_t REG_data = 0x0;
	uint16_t temp;
	LCD_WriteCommand(0x09);
	
	LCD_ReadData();
	
	temp = LCD_ReadData();
	REG_data += (temp&0xFE)<<25;
	
	temp = LCD_ReadData();
	REG_data += (temp&0x7F)<<16;
	
	temp = LCD_ReadData();
	REG_data += (temp&0x7)<<8;
	
	temp = LCD_ReadData();
	REG_data += (temp&0xE0)<<5;
	
	SendByte(REG_data>>24);
	SendByte(REG_data>>16);
	SendByte(REG_data>>8);
	SendByte(REG_data);
	
	uint32_t window = LCD_Create_Window(0, 99, 0, 99);
	LCD_Memory_Write(0x0000,window);
}
