#include "dma.h"
#include "usart.h"
void USART1_DMA_RX(void)
{
    DMA_InitTypeDef DMA_InitStructure;
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
    DMA_DeInit(DMA1_Channel5);  
    DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)(&USART1->DR);   
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)Uart1_RX;   
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;        
    DMA_InitStructure.DMA_BufferSize =sizeof(Uart1_RX);  
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;        
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;      
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; 
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;     
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;               
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh; 
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;             
    DMA_Init(DMA1_Channel5,&DMA_InitStructure); 
    DMA_Cmd(DMA1_Channel5,ENABLE);  
    USART_DMACmd(USART1,USART_DMAReq_Rx,ENABLE);        
}
 

















