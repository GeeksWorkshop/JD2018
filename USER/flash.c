#include "main.h"
uint32_t offsetAddress;
uint32_t sectorPosition;
uint32_t sectorStartAddress;
uint16_t dataIndex;
//?????????(16???)
uint16_t FLASH_ReadHalfWord(uint32_t address)
{
  return *(__IO uint16_t*)address; 
}

//?????????????
void FLASH_ReadMoreData(uint32_t startAddress,uint16_t *readData,uint16_t countToRead)
{
  uint16_t dataIndex;
  for(dataIndex=0;dataIndex<countToRead;dataIndex++)
  {
    readData[dataIndex]=FLASH_ReadHalfWord(startAddress+dataIndex*2);
  }
}



//?????????(32???)
uint32_t FLASH_ReadWord(uint32_t address)
{
  uint32_t temp1,temp2;
  temp1=*(__IO uint16_t*)address; 
  temp2=*(__IO uint16_t*)(address+2); 
  return (temp2<<16)+temp1;
}

//?????????????
void FLASH_WriteMoreData(uint32_t startAddress,uint16_t *writeData,uint16_t countToWrite)
{
  if(startAddress<FLASH_BASE||((startAddress+countToWrite*2)>=(FLASH_BASE+1024*FLASH_SIZE)))
  {
    return;//????
  }
  FLASH_Unlock();         //?????
  offsetAddress=startAddress-FLASH_BASE;               //????0X08000000????????
  sectorPosition=offsetAddress/SECTOR_SIZE;            //??????,??STM32F103VET6?0~255
  
  sectorStartAddress=sectorPosition*SECTOR_SIZE+FLASH_BASE;    //????????

  FLASH_ErasePage(sectorStartAddress);//??????
  

  for(dataIndex=0;dataIndex<countToWrite;dataIndex++)
  {
    FLASH_ProgramHalfWord(startAddress+dataIndex*2,writeData[dataIndex]);
  }
  
  FLASH_Lock();//?????
}

