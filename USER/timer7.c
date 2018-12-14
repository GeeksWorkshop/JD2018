#include "timer7.h"
#include "main.h"
#include "encoder.h"

float change1;
float x=0;
float y=0;
float high=200;
float angg_pre;

float xPIDout,yPIDout,change1PIDout,hPIDout;

int speed_ref=100;
int current_out=0; 
int i=0;

s16 buff_3510iq[4],posloop_out[4];
s16 pos_ref[4]={1000,1000,1000,1000};


void TIM4_Configuration(void)    //2msÖÐ¶Ï
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
	

	if(sennn0==0)
	{
		PMotor.CircleNum=50;
	}
	if(sennn1==0)
	{
		PMotor.CircleNum=2050;
	}
	
	
    if (TIM_GetITStatus(TIM4,TIM_IT_Update)!= RESET) 
		{
        TIM_ClearITPendingBit(TIM4,TIM_IT_Update);
        TIM_ClearFlag(TIM4, TIM_FLAG_Update);	
		 


			//ËÙ¶È»·¿ØÖÆ£¬ÆÁ±ÎÎ»ÖÃ»·£¬Ö±½Ó¿ØÖÆ
		if(RC_CtrlData.rc.s1==3)
		{
					 x= (RC_CtrlData.rc.ch2-0x400)*(0xf00)/(0x694-0x16c);
					 y= (RC_CtrlData.rc.ch3-0x400)*(0xf00)/(0x694-0x16c); 
					 high=(RC_CtrlData.rc.ch1-0x400)*(0xf00)/(0x694-0x16c)*5;
					 change1=(RC_CtrlData.rc.ch0-0x400)*(0x600)/(0x694-0x16c)*0.1;		
					 posloop_out[0]=high;
					 posloop_out[1]=-x+change1*20;
					 posloop_out[2]=x/2-y*0.866+change1*20;
					 posloop_out[3]=x/2+y*0.866+change1*20;	 		
		}
		//¼ÓÈëÎ»ÖÃ¿ØÖÆ
		if(RC_CtrlData.rc.s1==1)
		{
					
			
			
					if(RC_CtrlData.rc.s2==1)//Ò£¿ØÆ÷¿ØÖÆÎ»ÖÃ
					{
						 x= (RC_CtrlData.rc.ch2-0x400)*(0xf00)/(0x694-0x16c);
						 y= (RC_CtrlData.rc.ch3-0x400)*(0xf00)/(0x694-0x16c); 
						 high=(RC_CtrlData.rc.ch1-0x400)*(0xf00)/(0x694-0x16c)+200;//Ä¬ÈÏÆô¶¯Î»ÖÃ200 ¸ß¶È200
						 change1=(RC_CtrlData.rc.ch0-0x400)*(0x600)/(0x694-0x16c)*0.1;		
					}
					if(RC_CtrlData.rc.s2==2)//jetson¿ØÖÆÎ»ÖÃ
					{
						 x= RC2_CtrlData.rc.ch2;
						 y= RC2_CtrlData.rc.ch3;
						 change1=RC2_CtrlData.rc.ch0;				
						 high=RC2_CtrlData.rc.ch1;;//Ä¬ÈÏÆô¶¯ »á±»ÏÞ·ù

						
						//À¬»øÍ°
								if(RC2_CtrlData.rc.s1==0x1)//Ç°½ø
								{

									GPIO_SetBits(GPIOB,GPIO_Pin_7);
									GPIO_ResetBits(GPIOB,GPIO_Pin_6);
								}else if(RC2_CtrlData.rc.s1==0x2)//»ØÍË
								{
	
									GPIO_SetBits(GPIOB,GPIO_Pin_6);
									GPIO_ResetBits(GPIOB,GPIO_Pin_7);
								}
								else//²»¶¯
								{
								GPIO_ResetBits(GPIOB,GPIO_Pin_6);
								GPIO_ResetBits(GPIOB,GPIO_Pin_7);									
								}

						

						
								if(RC2_CtrlData.rc.s2==0x1)//Ç°½ø
								{
								GPIO_SetBits(GPIOA,GPIO_Pin_0);
								GPIO_ResetBits(GPIOA,GPIO_Pin_1);
								}else if(RC2_CtrlData.rc.s2==0x2)//»ØÍË
								{
								GPIO_SetBits(GPIOA,GPIO_Pin_1);
								GPIO_ResetBits(GPIOA,GPIO_Pin_0);
								}
								else//²»¶¯
								{
								GPIO_ResetBits(GPIOA,GPIO_Pin_1);
								GPIO_ResetBits(GPIOA,GPIO_Pin_0);									
								}
						
						
					}
					
					//Î»ÖÃ»·ÊäÈëÖµÏÞÎ»
					
					if(high<=50)
					{high=50;}
					if(high>=2050)
					{high=2050;}
					
					
						//Î»ÖÃ»·	
						 hPIDout=pid_calc(&pid_pos[0],PMotor.CircleNum,high);//h¡
					
						 change1PIDout=pid_calc(&pid_pos[1], -zangle,change1);//zangle
						 xPIDout=pid_calc(&pid_pos[2], pos_x,x);//x
						 yPIDout=pid_calc(&pid_pos[3], pos_y,y);//y	
										
					 //¾ØÕó±ä»»
						 posloop_out[0]=hPIDout;
						 posloop_out[1]=xPIDout+change1PIDout;
						 posloop_out[2]=-xPIDout/2+yPIDout*0.866+change1PIDout;
						 posloop_out[3]=-xPIDout/2-yPIDout*0.866+change1PIDout;	 			
		}	 
		
		//Ç°Ãæ×öÎ»ÖÃ»·ÒÔ¼°¾ØÕó±ä»»
				 //ËÙ¶È»·	 
				for (i=0;i<=3;i++)
				 {
					buff_3510iq[i]=pid_calc(&pid_spd[i], motordata[i][1],
																			posloop_out[i]);
				 }
				 
			//
			//½ûÖ¹ÒÆ¶¯£¬ÆÁ±ÎÈÎºÎµç»ú¿ØÖÆ
			if(RC_CtrlData.rc.s1==2)
			{	
						Set_CM_Speed(CAN1,0,0,0,0);
				
								//ÍÆ¸Ë¿ØÖÆ
								if(RC_CtrlData.rc.ch3>0x500)//Ç°½ø
								{
								GPIO_SetBits(GPIOA,GPIO_Pin_0);
								GPIO_ResetBits(GPIOA,GPIO_Pin_1);
								}else if(RC_CtrlData.rc.ch3<0x300)//»ØÍË
								{
								GPIO_SetBits(GPIOA,GPIO_Pin_1);
								GPIO_ResetBits(GPIOA,GPIO_Pin_0);
								}
								else//²»¶¯
								{
								GPIO_ResetBits(GPIOA,GPIO_Pin_1);
								GPIO_ResetBits(GPIOA,GPIO_Pin_0);									
								}
								
								
								if(RC_CtrlData.rc.ch1>0x500&sennn2==1)//Ç°½ø
								{

									GPIO_SetBits(GPIOB,GPIO_Pin_7);
									GPIO_ResetBits(GPIOB,GPIO_Pin_6);
								}else if(RC_CtrlData.rc.ch1<0x300)//»ØÍË
								{
	
									GPIO_SetBits(GPIOB,GPIO_Pin_6);
									GPIO_ResetBits(GPIOB,GPIO_Pin_7);
								}
								else//²»¶¯
								{
								GPIO_ResetBits(GPIOB,GPIO_Pin_6);
								GPIO_ResetBits(GPIOB,GPIO_Pin_7);									
								}				
								
								
								
			}	
			else
			{
				
				//¸ß¶ÈµÄÊä³öÏÞÎ»
					if(PMotor.CircleNum<=50&buff_3510iq[0]<0)
					{
						buff_3510iq[0]=0;
					}
					if(PMotor.CircleNum>=2030&buff_3510iq[0]>0)
					{
						buff_3510iq[0]=0;
					}				
					
				
			Set_CM_Speed(CAN1,buff_3510iq[0],buff_3510iq[1],buff_3510iq[2],buff_3510iq[3]);
			}
			
		}
}
