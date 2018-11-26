#ifndef __JETSON_H
#define __JETSON_H
#include "stdio.h"	
#include "sys.h" 
#include "usart.h"	

#define USART_REC_LEN  			200  	//定义最大接收字节数 200
#define EN_USART3_RX 			1		//使能（1）/禁止（0）串口1接收
#define  BSP_USART3_DMA_RX_BUF_LEN               30u                   
#define  RC_FRAME_LENGTH                            18u
static uint8_t _USART3_DMA_RX_BUF[BSP_USART3_DMA_RX_BUF_LEN];
	
extern u8  USART_RX_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART_RX_STA;         		//接收状态标记	

//如果想串口中断接收，请不要注释以下宏定义
void uart3_init(u32 bound);

//uint32_t *GetLostCounter(uint8_t index)

#define Usart3_RX_LEN   30

extern u8 Uart3_RX[Usart3_RX_LEN] ;	


void RemoteDataPrcess2(uint8_t *pData);



#endif


