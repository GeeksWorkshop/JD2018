#include "timer7.h"
#include "main.h"
#include "encoder.h"

float change1;
float x=0;
float y=0;
float h=0;


float xPIDout,yPIDout,change1PIDout,hPIDout;

int speed_ref=100;
int current_out=0; 
int i=0;

s16 buff_3510iq[4],posloop_out[4];
s16 pos_ref[4]={1000,1000,1000,1000};


void TIM4_Configuration(void)    //2ms中断
{
    TIM_TimeBaseInitTypeDef  tim;
    NVIC_InitTypeDef         nvic;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
    
    nvic.NVIC_IRQChannel = TIM4_IRQn;
    nvic.NVIC_IRQChannelPreemptionPriority = 2;
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

void TIM4_IRQHandler(void)  
{
	

	
    if (TIM_GetITStatus(TIM4,TIM_IT_Update)!= RESET) 
		{
        TIM_ClearITPendingBit(TIM4,TIM_IT_Update);
        TIM_ClearFlag(TIM4, TIM_FLAG_Update);	
		 

				change1=(RC_CtrlData.rc.ch0-0x400)*(0x600)/(0x694-0x16c)*0.1;
				 x= (RC_CtrlData.rc.ch2-0x400)*(0xf00)/(0x694-0x16c);
				 y= (RC_CtrlData.rc.ch3-0x400)*(0xf00)/(0x694-0x16c); 
				 h=(RC_CtrlData.rc.ch1-0x400)*(0xf00)/(0x694-0x16c);

		if(RC_CtrlData.rc.s1==3)
		{
		 posloop_out[0]=h*5;
		 posloop_out[1]=-x+change1*20;
		 posloop_out[2]=x/2-y*0.866+change1*20;
		 posloop_out[3]=x/2+y*0.866+change1*20;	 		
		}
		else
		{
					 //位置环
	
		 hPIDout=pid_calc(&pid_pos[0],PMotor.CircleNum,h/10);//h
			
		 change1PIDout=pid_calc(&pid_pos[1], -zangle,change1);//zangle
		 xPIDout=pid_calc(&pid_pos[2], pos_x,x);//x
		 yPIDout=pid_calc(&pid_pos[3], pos_y,y);//y	
			posloop_out[0]=hPIDout;
					 //矩阵变换
		 posloop_out[1]=xPIDout+change1PIDout;
		 posloop_out[2]=-xPIDout/2+yPIDout*0.866+change1PIDout;
		 posloop_out[3]=-xPIDout/2-yPIDout*0.866+change1PIDout;	 			
		}

		buff_3510iq[0]=pid_calc(&pid_spd[0], motordata[0][1],
																			posloop_out[0]);		 
				 //速度环	 
				for (i=1;i<=3;i++)
				 {
					buff_3510iq[i]=pid_calc(&pid_spd[i], motordata[i][1],
																			posloop_out[i]);
				 }
			
			if(RC_CtrlData.rc.s1==2)
			{	
			Set_CM_Speed(CAN1,buff_3510iq[0],0,0,0);
			}
			else
			{
			Set_CM_Speed(CAN1,buff_3510iq[0],buff_3510iq[1],buff_3510iq[2],buff_3510iq[3]);
			}
			
		}
}
