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
int chassis_data_order[4]={0};
int motordata[4][2];
void TIM4_IRQHandler(void)  
{
		
    if (TIM_GetITStatus(TIM4,TIM_IT_Update)!= RESET) 
		{
        TIM_ClearITPendingBit(TIM4,TIM_IT_Update);
        TIM_ClearFlag(TIM4, TIM_FLAG_Update);	
//			
//			  chassiscontrol();
//			  updownplatform_control();
		chassispid[0].SetPoint=chassis_data_order[0];
				chassispid[1].SetPoint=chassis_data_order[1];
				chassispid[2].SetPoint=chassis_data_order[2];
				chassispid[3].SetPoint=chassis_data_order[3];		
			  chassispid[0].Input=motordata[0][1];
			  chassispid[1].Input=motordata[1][1];
			  chassispid[2].Input=motordata[2][1];
			  chassispid[3].Input=motordata[3][1];
			  PidCalc(&chassispid[0]);
			  PidCalc(&chassispid[1]);
			  PidCalc(&chassispid[2]);
			  PidCalc(&chassispid[3]);
			
//				updownplatformpid.Input=UpDownPlatform_Motor[1];
//			  PidCalc(&updownplatformpid);
//				
//			  chassis_data[0]=chassispid[0].Output;
//				chassis_data[1]=chassispid[1].Output;
//				chassis_data[2]=chassispid[2].Output;
//				chassis_data[3]=chassispid[3].Output;
//				UpDownPlatform_data=updownplatformpid.Output;
			
			// 轮子PID速度环

//			
//				updownplatformpid.Input=UpDownPlatform_Motor[1];
			  PidCalc(&updownplatformpid);

//				UpDownPlatform_data=updownplatformpid.Output;
			}
			
}
