#include "sys.h"
#include "usart.h"	

 
#if EN_USART1_RX   //如果使能了接收

  
void uart_init(u32 bound){
  //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//使能USART1，GPIOA时钟
  
  
  //USART1_RX	  GPIOA.10初始化
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//上拉输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.10  

  //Usart1 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  
   //USART 初始化设置

	USART_InitStructure.USART_BaudRate = bound;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_Even;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx  ;	//收模式

  USART_Init(USART1, &USART_InitStructure); //初始化串口1
  USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);//开启串口空闲中断
  USART_Cmd(USART1, ENABLE);                    //使能串口1 
	

}

u8 Uart1_RX[Usart1_RX_LEN] = {0};	


void USART1_IRQHandler(void)
{
	static uint32_t this_time_rx_len = 0;
	if(USART_GetITStatus(USART1, USART_IT_IDLE) != RESET)
	{
		//clear the idle pending flag 
		(void)USART1->SR;
		(void)USART1->DR;

    DMA_Cmd(DMA1_Channel5, DISABLE); 
	//	DMA_ClearFlag( DMA1_FLAG_GL5 );   
  //  this_time_rx_len = BSP_USART1_DMA_RX_BUF_LEN - DMA_GetCurrDataCounter(DMA1_Channel5); //
	 this_time_rx_len = Usart1_RX_LEN - DMA_GetCurrDataCounter(DMA1_Channel5); //


		
		 if(this_time_rx_len == RC_FRAME_LENGTH)
			{
				RemoteDataPrcess(Uart1_RX);
   //     LostCounterFeed(GetLostCounter(LOST_COUNTER_INDEX_RC));
			}
	   DMA_SetCurrDataCounter(DMA1_Channel5,BSP_USART1_DMA_RX_BUF_LEN);//111111
     DMA_Cmd(DMA1_Channel5, ENABLE); 
	}
	
	else
	{
	USART_ReceiveData(USART1);
	USART_ClearFlag(USART1,USART_FLAG_ORE);		
	
	}
}




RC_Ctl_t RC_CtrlData;   //remote control data


void RemoteDataPrcess(uint8_t *pData)
{
    if(pData == NULL)
    {
        return;
    }
    
    RC_CtrlData.rc.ch0 = ((int16_t)pData[0] | ((int16_t)pData[1] << 8)) & 0x07FF; 
    RC_CtrlData.rc.ch1 = (((int16_t)pData[1] >> 3) | ((int16_t)pData[2] << 5)) & 0x07FF;
    RC_CtrlData.rc.ch2 = (((int16_t)pData[2] >> 6) | ((int16_t)pData[3] << 2) |
                         ((int16_t)pData[4] << 10)) & 0x07FF;
    RC_CtrlData.rc.ch3 = (((int16_t)pData[4] >> 1) | ((int16_t)pData[5]<<7)) & 0x07FF;
    
    RC_CtrlData.rc.s1 = ((pData[5] >> 4) & 0x000C) >> 2;
    RC_CtrlData.rc.s2 = ((pData[5] >> 4) & 0x0003);

    RC_CtrlData.mouse.x = ((int16_t)pData[6]) | ((int16_t)pData[7] << 8);
    RC_CtrlData.mouse.y = ((int16_t)pData[8]) | ((int16_t)pData[9] << 8);
    RC_CtrlData.mouse.z = ((int16_t)pData[10]) | ((int16_t)pData[11] << 8);    

    RC_CtrlData.mouse.press_l = pData[12];
    RC_CtrlData.mouse.press_r = pData[13];
 
    RC_CtrlData.key.v = ((int16_t)pData[14]);// | ((int16_t)pData[15] << 8);
	
	
}






#endif	

