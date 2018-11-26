#ifndef __JETSON_H
#define __JETSON_H
#include "stdio.h"	
#include "sys.h" 
#include "usart.h"	

#define USART_REC_LEN  			200  	//�����������ֽ��� 200
#define EN_USART3_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����
#define  BSP_USART3_DMA_RX_BUF_LEN               30u                   
#define  RC_FRAME_LENGTH                            18u
static uint8_t _USART3_DMA_RX_BUF[BSP_USART3_DMA_RX_BUF_LEN];
	
extern u8  USART_RX_BUF[USART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART_RX_STA;         		//����״̬���	

//����봮���жϽ��գ��벻Ҫע�����º궨��
void uart3_init(u32 bound);

//uint32_t *GetLostCounter(uint8_t index)

#define Usart3_RX_LEN   30

extern u8 Uart3_RX[Usart3_RX_LEN] ;	


void RemoteDataPrcess2(uint8_t *pData);



#endif


