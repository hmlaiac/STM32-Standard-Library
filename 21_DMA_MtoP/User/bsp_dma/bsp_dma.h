#ifndef __BSP_DMA_H
#define __BSP_DMA_H
#include "stm32f10x.h"
#define Peri_base				0x40013800
#define Peri_addr				(Peri_base+0x04)

extern const uint32_t Peri_Array[32];									
extern uint32_t Mem_Array[32];
extern uint8_t DataBufer_8b1000 [1000];


//useful function here
void DMA_RCC_ENABLE(void);
void DMA_Config(void);
void DMA_P2M_Config(void);
uint8_t memory_compare(const uint32_t* array1, uint32_t* array2, uint8_t size);
#endif
