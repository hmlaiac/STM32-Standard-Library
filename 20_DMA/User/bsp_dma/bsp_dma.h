#ifndef __BSP_DMA_H
#define __BSP_DMA_H
#include "stm32f10x.h"

extern const uint32_t Peri_Array[32];									
extern uint32_t Mem_Array[32];


void DMA_RCC_ENABLE(void);
void DMA_Config(void);
uint8_t memory_compare(const uint32_t* array1, uint32_t* array2, uint8_t size);
#endif
