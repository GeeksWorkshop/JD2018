
#include <sys.h>	 
#include "encoder.h"	

uint8_t ReadReceiveBuffer[READ_BUFFER_SIZE] = {0};

volatile float pos_x;
volatile float pos_y;
volatile float zangle;
volatile float xangle=0;
volatile float yangle=0;
float w_z=0;
static uint8_t count=0;
static uint8_t i=0;


static union
{
	uint8_t data[24];
	volatile float ActVal[6];
}posture;


void encoder_init(u32 bound)
{
   //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
//	DMA_InitTypeDef DMA_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); //使能GPIOA时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);//使能USART3时钟
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);
 
	//串口3对应引脚复用映射
	//GPIO_PinAFConfig(GPIOB,GPIO_PinSource10,GPIO_AF_USART3); //GPIOB10复用为USART3
	//GPIO_PinAFConfig(GPIOB,GPIO_PinSource11,GPIO_AF_USART3); //GPIOB11复用为USART3
	
	  //USART1_RX	  GPIOA.10初始化

	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_3;
  GPIO_Init(GPIOA,&GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);


   //USART3 初始化设置
	USART_InitStructure.USART_BaudRate = bound;//波特率设置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx;	//收发模式
  USART_Init(USART2, &USART_InitStructure); //初始化串口3
	
//	USART_DMACmd(USART3,USART_DMAReq_Rx,ENABLE);  
	USART_Cmd(USART2, ENABLE);  //使能串口3
//	USART_ClearFlag(USART3, USART_FLAG_TC);
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启相关中断

// NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;//串口1中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器、
	
//	DMA_DeInit(DMA1_Stream1);

//  DMA_InitStructure.DMA_Channel            = DMA_Channel_4;
//  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART3->DR;
//  DMA_InitStructure.DMA_Memory0BaseAddr    = (uint32_t)ReadReceiveBuffer;
//  DMA_InitStructure.DMA_DIR                = DMA_DIR_PeripheralToMemory;
//  DMA_InitStructure.DMA_BufferSize         = READ_BUFFER_SIZE;
//  DMA_InitStructure.DMA_PeripheralInc      = DMA_PeripheralInc_Disable;
//  DMA_InitStructure.DMA_MemoryInc          = DMA_MemoryInc_Enable;
//  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
//  DMA_InitStructure.DMA_MemoryDataSize     = DMA_MemoryDataSize_Byte;
//  DMA_InitStructure.DMA_Mode               = DMA_Mode_Circular;
//  DMA_InitStructure.DMA_Priority           = DMA_Priority_High ;
//  DMA_InitStructure.DMA_FIFOMode           = DMA_FIFOMode_Disable;
//  DMA_InitStructure.DMA_FIFOThreshold      = DMA_FIFOThreshold_1QuarterFull;
//  DMA_InitStructure.DMA_MemoryBurst        = DMA_MemoryBurst_Single;
//  DMA_InitStructure.DMA_PeripheralBurst    = DMA_PeripheralBurst_Single;

//  DMA_Init(DMA1_Stream1, &DMA_InitStructure);
//	DMA_ITConfig(DMA1_Stream1,DMA_IT_TC,ENABLE);
//  DMA_Cmd(DMA1_Stream1, ENABLE);	

}

//void DMA1_Stream1_IRQHandler(void)
//{
//	if(DMA_GetITStatus(DMA1_Stream1, DMA_IT_TCIF4))
//	{
//		DMA_ClearFlag(DMA1_Stream1, DMA_FLAG_TCIF4);
//		DMA_ClearITPendingBit(DMA1_Stream1, DMA_IT_TCIF4);
//	}
//}

void USART2_IRQHandler(void)
{
	static uint8_t ch;

 if(USART_GetITStatus(USART2, USART_IT_RXNE)!= RESET)
	{
		USART_ClearITPendingBit( USART2,USART_IT_RXNE);
		ch=USART_ReceiveData(USART2);
		switch(count)
		{
			case 0:
				if(ch==0x0d)
				count++;
				else
				count=0;
				break;
			case 1:
				if(ch==0x0a)
				{
					i=0;
					count++;
				}
				else if(ch==0x0d);
				else
					count=0;
				break;
			case 2:
				posture.data[i]=ch;
				i++;
				if(i>=24)
				{
					i=0;
					count++;
				}
				break;
			case 3:
				if(ch==0x0a) count++;
				else count=0;
				break;
			case 4:
				if(ch==0x0d)
				{
					zangle=posture.ActVal[0];
					xangle=posture.ActVal[1];
					yangle=posture.ActVal[2];
					pos_x =posture.ActVal[3];
					pos_y =posture.ActVal[4];
					w_z =posture.ActVal[5];
				}
				count=0;
				break;
			default:
				count=0;
				break;
		}
	}
}





