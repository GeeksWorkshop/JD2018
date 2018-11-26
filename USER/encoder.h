/**
  ********************************(C) COPYRIGHT 2017 DJI************************
  * @file       pid.h
	* @brief      pid parameter initialization, position and delta pid calculate
	* @update	  
	*	@history
	* Version     Date          Author           Modification
  * V1.0.0      Apr-30-2017   Richard.luo        
  * @verbatim
	********************************(C) COPYRIGHT 2017 DJI************************
	*/
	
#ifndef __encoder_H__
#define __encoder_H__

#include "sys.h"

#define READ_BUFFER_SIZE      28

#include "stdio.h"	
#include "stm32f10x.h"
#include "sys.h" 

	
void uart3_init(u32 bound);
void USART3_IRQHandler(void);
//void DMA1_Stream1_IRQHandler(void);



#endif
