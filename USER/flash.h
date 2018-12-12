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
	
#ifndef __flash_H__
#define __flash_H__


#include "main.h"	
#include "stdio.h"	
#include "stm32f10x.h"
	
#define FLASH_SIZE 512          //??MCU?FLASH????(???K)

#if FLASH_SIZE<256
  #define SECTOR_SIZE           1024    //??
#else 
  #define SECTOR_SIZE           2048    //??
#endif




void FLASH_WriteMoreData(uint32_t startAddress,uint16_t *writeData,uint16_t countToWrite);
uint32_t FLASH_ReadWord(uint32_t address);
void FLASH_ReadMoreData(uint32_t startAddress,uint16_t *readData,uint16_t countToRead);
#endif
