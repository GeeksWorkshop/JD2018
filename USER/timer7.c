#include "timer7.h"

void TIM4_Configuration(void)    //2ms中断
{
    TIM_TimeBaseInitTypeDef  tim;
    NVIC_InitTypeDef         nvic;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
    
    nvic.NVIC_IRQChannel = TIM4_IRQn;
    nvic.NVIC_IRQChannelPreemptionPriority = 1;
    nvic.NVIC_IRQChannelSubPriority = 1;
    nvic.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvic);

    tim.TIM_Prescaler =840-1;
    tim.TIM_CounterMode = TIM_CounterMode_Up;
    tim.TIM_ClockDivision = TIM_CKD_DIV1;
    tim.TIM_Period = 200-1;
    TIM_TimeBaseInit(TIM4,&tim);
	  TIM_Cmd(TIM4, ENABLE);	 
    TIM_ITConfig(TIM4, TIM_IT_Update,ENABLE);
}

float input  =0 ;

void TIM4_IRQHandler(void)  
{
		
    if (TIM_GetITStatus(TIM4,TIM_IT_Update)!= RESET) 
		{
        TIM_ClearITPendingBit(TIM4,TIM_IT_Update);
        TIM_ClearFlag(TIM4, TIM_FLAG_Update);	
//			
//			  chassiscontrol();
//			  updownplatform_control();

			
			// 轮子PID速度环

//			
//				updownplatformpid.Input=UpDownPlatform_Motor[1];
			  PidCalc(&updownplatformpid);

//				UpDownPlatform_data=updownplatformpid.Output;
			}
			
}
