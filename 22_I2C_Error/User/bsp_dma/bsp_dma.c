#include "bsp_dma.h"
const uint32_t Peri_Array[32] = {0x1, 0x2, 0x3, 0x4, 0x1, 0x2, 0x3, 0x4,
											0x1, 0x2, 0x3, 0x4, 0x1, 0x2, 0x3, 0x4,
											0x1, 0x2, 0x3, 0x4, 0x1, 0x2, 0x3, 0x4,
											0x1, 0x2, 0x3, 0x4, 0x1, 0x2, 0x3, 0x4};			

uint32_t Mem_Array[32];
uint8_t DataBufer_8b1000 [1000];
void DMA_RCC_ENABLE(void){
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
}


void DMA_Config(){
	DMA_InitTypeDef DMA_InitStruct;
	DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)Peri_Array;
	DMA_InitStruct.DMA_MemoryBaseAddr= (uint32_t)Mem_Array;
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStruct.DMA_BufferSize = 32; //remark error may occur here
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Enable;
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
	DMA_InitStruct.DMA_MemoryDataSize= DMA_MemoryDataSize_Word;
	DMA_InitStruct.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStruct.DMA_Priority = DMA_Priority_High ;
	DMA_InitStruct.DMA_M2M = DMA_M2M_Enable;
	
	DMA_Init(DMA1_Channel6, &DMA_InitStruct);
	DMA_Cmd(DMA1_Channel6,ENABLE);
	while(DMA_GetFlagStatus(DMA1_FLAG_TC6)==RESET){}
}

static void Data_Init(){
	uint32_t i = 0;
	for(;i<1000;++i){
		DataBufer_8b1000[i] = 'P';
	}
}

void DMA_P2M_Config(void){
	Data_Init();
	DMA_InitTypeDef DMA_InitStruct;
	DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)Peri_addr; 
	DMA_InitStruct.DMA_MemoryBaseAddr= (uint32_t)DataBufer_8b1000;
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralDST;
	DMA_InitStruct.DMA_BufferSize = 1000; //remark error may occur here
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStruct.DMA_MemoryDataSize= DMA_MemoryDataSize_Byte;
	DMA_InitStruct.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStruct.DMA_Priority = DMA_Priority_High ;
	DMA_InitStruct.DMA_M2M = DMA_M2M_Disable;
	
	DMA_Init(DMA1_Channel4, &DMA_InitStruct);
	USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE); 
	DMA_Cmd(DMA1_Channel4,ENABLE);
	while(DMA_GetFlagStatus(DMA1_FLAG_TC6)==RESET){}
}

uint8_t memory_compare(const uint32_t* array1, uint32_t* array2, uint8_t size){
	uint8_t i=0;
	for(;i<size;){
		if(array1[i]!=array2[i]){
			return 0;
		}
		++i;
	}
	return 1;
}

