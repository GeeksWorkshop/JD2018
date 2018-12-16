#include "sys.h"
#include "jetson.h"	

 
#if EN_USART1_RX   //如果使能了接收

  
void uart3_init(u32 bound){
  //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);	//使能USART1，GPIOA时钟
  
  RCC_APB1PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	//使能USART1，GPIOA时钟
  
  
  //USART1_RX	  GPIOA.10初始化
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;//PA11
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//上拉输入
  GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOA.10  

	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA11
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOA.11 
	
  //Usart1 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  
   //USART 初始化设置

	USART_InitStructure.USART_BaudRate = bound;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx|USART_Mode_Tx ;	//收模式

  USART_Init(USART3, &USART_InitStructure); //初始化串口1
  USART_ITConfig(USART3, USART_IT_IDLE, ENABLE);//开启串口空闲中断
  USART_Cmd(USART3, ENABLE);                    //使能串口1 
	

}

u8 Uart3_RX[Usart3_RX_LEN] = {0};	


void USART3_IRQHandler(void)
{
	static uint32_t this_time_rx_len2 = 0;
	if(USART_GetITStatus(USART3, USART_IT_IDLE) != RESET)
	{
		//clear the idle pending flag 
		(void)USART3->SR;
		(void)USART3->DR;

    DMA_Cmd(DMA1_Channel3, DISABLE); 
	//	DMA_ClearFlag( DMA1_FLAG_GL5 );   
  //  this_time_rx_len = BSP_USART1_DMA_RX_BUF_LEN - DMA_GetCurrDataCounter(DMA1_Channel5); //
	 this_time_rx_len2 = Usart3_RX_LEN - DMA_GetCurrDataCounter(DMA1_Channel3); //


		
		 if(this_time_rx_len2 == RC_FRAME_LENGTH)
			{
				RemoteDataPrcess2(Uart3_RX);
   //     LostCounterFeed(GetLostCounter(LOST_COUNTER_INDEX_RC));
			}
	   DMA_SetCurrDataCounter(DMA1_Channel3,BSP_USART3_DMA_RX_BUF_LEN);//111111
     DMA_Cmd(DMA1_Channel3, ENABLE); 
	}
	
	else
	{
	USART_ReceiveData(USART3);
	USART_ClearFlag(USART3,USART_FLAG_ORE);		
	
	}
}

RC_Ctl_t RC2_CtrlData;   //remote control data
//55 00 00 40 01 0A 00 00 00 00 00 AA 00 00 00 00 00 00
//55 00 00 40 01 0A 00 00 00 00 00 AA 00 00 00 00 00 00

extern u8 pData222[30];

void RemoteDataPrcess2(uint8_t *pData)
{
		int ii;
    if(pData == NULL)
    {
        return;
    }

		
		for(ii=0;ii<20;ii++)
		{
			    pData222[ii]=pData[ii];
		}

		
			if((pData[11]==0xaa)&(pData[0]==0x55))
			{
	    RC2_CtrlData.rc.ch0 = (int16_t)pData[1]|((int16_t)pData[2] << 8);//a 
			RC2_CtrlData.rc.ch1 = (int16_t)pData[3]|((int16_t)pData[4] << 8);//h
		  RC2_CtrlData.rc.ch2 = ((int16_t)pData[5]|((int16_t)pData[6] << 8)); //x
			RC2_CtrlData.rc.ch3 = ((int16_t)pData[7]|((int16_t)pData[8] << 8)); //y
			RC2_CtrlData.rc.s1=(int16_t)pData[9];

			RC2_CtrlData.rc.s2=(int16_t)pData[10];
			}
//		RC2_CtrlData.rc.ch1 = (((int16_t)pData[1]|((int16_t)pData[2] << 8));
//    RC2_CtrlData.rc.ch2 = (((int16_t)pData[2] >> 6) | ((int16_t)pData[3] << 2) |
//                         ((int16_t)pData[4] << 10)) & 0x07FF;
//    RC2_CtrlData.rc.ch3 = (((int16_t)pData[4] >> 1) | ((int16_t)pData[5]<<7)) & 0x07FF;
//    RC2_CtrlData.rc.ch0 = ((int16_t)pData[0] | ((int16_t)pData[1] << 8)) & 0x07FF; 
//    RC2_CtrlData.rc.ch1 = (((int16_t)pData[1] >> 3) | ((int16_t)pData[2] << 5)) & 0x07FF;
//    RC2_CtrlData.rc.ch2 = (((int16_t)pData[2] >> 6) | ((int16_t)pData[3] << 2) |
//                         ((int16_t)pData[4] << 10)) & 0x07FF;
//    RC2_CtrlData.rc.ch3 = (((int16_t)pData[4] >> 1) | ((int16_t)pData[5]<<7)) & 0x07FF;
//    
//    RC2_CtrlData.rc.s1 = ((pData[5] >> 4) & 0x000C) >> 2;
//    RC2_CtrlData.rc.s2 = ((pData[5] >> 4) & 0x0003);

//    RC2_CtrlData.mouse.x = ((int16_t)pData[6]) | ((int16_t)pData[7] << 8);
//    RC2_CtrlData.mouse.y = ((int16_t)pData[8]) | ((int16_t)pData[9] << 8);
//    RC2_CtrlData.mouse.z = ((int16_t)pData[10]) | ((int16_t)pData[11] << 8);    

//    RC2_CtrlData.mouse.press_l = pData[12];
//    RC2_CtrlData.mouse.press_r = pData[13];
// 
//    RC2_CtrlData.key.v = ((int16_t)pData[14]);
		// | ((int16_t)pData[15] << 8);
	
}






#endif	

