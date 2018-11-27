#include "main.h"	
#include "jetson.h"	

vs32 change1=0;
vs32 change2=0;
vs32 change3=0;
vs16 x=0;
vs16 y=0;
vs16 h=0;
u8 pData222[30];
 int main(void)
 { 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//???????????2:2??????,2??????
	delay_init();	    	
	LED_Init();		  		
  TIM2_PWM_Init(999,1439);	
	uart_init(100000);	
	uart3_init(100000);	 
  delay_ms(1000);
  USART1_DMA_RX();
	USART3_DMA_RX();
	 
 	CAN_Mode_Init(CAN_SJW_1tq,CAN_BS2_2tq,CAN_BS1_3tq,6,CAN_Mode_Normal);//CAN???????,???1Mbps    
  delay_ms(1000);
	chassis_pid_param_init();	 
	 
	 RC_CtrlData.rc.ch3=0x400;
	 RC_CtrlData.rc.ch2=0x400;
	 RC_CtrlData.rc.ch0=0x400;
	 RC_CtrlData.rc.ch1=0x400;
	 
	 RC2_CtrlData.rc.ch3=0x400;
	 RC2_CtrlData.rc.ch2=0x400;
	 RC2_CtrlData.rc.ch0=0x400;
	 RC2_CtrlData.rc.ch1=0x400;
	 
	 TIM_SetCompare2(TIM2,0);
	 
	 while(1)		 
	 {
		led_flag++;

		 change1= (RC_CtrlData.rc.ch0-0x400)*(0x600)/(0x694-0x16c);
		 x=- (RC_CtrlData.rc.ch2-0x400)*(0xf00)/(0x694-0x16c);
		 y=- (RC_CtrlData.rc.ch3-0x400)*(0xf00)/(0x694-0x16c); 
		 h=(RC_CtrlData.rc.ch1-0x400)*(0xf00)/(0x694-0x16c);

		 			 if(RC_CtrlData.rc.s1==2)
						{
						GPIO_SetBits(GPIOA,GPIO_Pin_1);
						GPIO_ResetBits(GPIOA,GPIO_Pin_0);
						}
						if(RC_CtrlData.rc.s1==1)
						{
						GPIO_SetBits(GPIOA,GPIO_Pin_0);
						GPIO_ResetBits(GPIOA,GPIO_Pin_1);
						}	
						if(RC_CtrlData.rc.s1==3)
						{
						GPIO_SetBits(GPIOA,GPIO_Pin_0);
						GPIO_SetBits(GPIOA,GPIO_Pin_1);
						}		
						
			if(RC_CtrlData.rc.s2==2)
			{
			GPIO_SetBits(GPIOA,GPIO_Pin_2);
			GPIO_ResetBits(GPIOA,GPIO_Pin_3);
			}
			if(RC_CtrlData.rc.s2==1)
			{
			GPIO_SetBits(GPIOA,GPIO_Pin_3);
			GPIO_ResetBits(GPIOA,GPIO_Pin_2);
			}	
			if(RC_CtrlData.rc.s2==3)
			{
			GPIO_SetBits(GPIOA,GPIO_Pin_3);
			GPIO_SetBits(GPIOA,GPIO_Pin_2);
			}			
		 
		 if(RC_CtrlData.rc.s1==3&RC_CtrlData.rc.s2==3)
		 { 
		 change1= (RC2_CtrlData.rc.ch0-0x400)*(0x600)/(0x694-0x16c);
		 x=- (RC2_CtrlData.rc.ch2-0x400)*(0xf00)/(0x694-0x16c);
		 y=- (RC2_CtrlData.rc.ch3-0x400)*(0xf00)/(0x694-0x16c); 
		 h=(RC2_CtrlData.rc.ch1-0x400)*(0xf00)/(0x694-0x16c);
		 }
		 else
		{
		change1= (RC_CtrlData.rc.ch0-0x400)*(0x600)/(0x694-0x16c);
		 x=- (RC_CtrlData.rc.ch2-0x400)*(0xf00)/(0x694-0x16c);
		 y=- (RC_CtrlData.rc.ch3-0x400)*(0xf00)/(0x694-0x16c); 
		 h=(RC_CtrlData.rc.ch1-0x400)*(0xf00)/(0x694-0x16c);
		 }

		 posloop_out[1]=x+change1;
		 posloop_out[2]=-x/2+y*0.866+change1;
		 posloop_out[3]=-x/2-y*0.866+change1;

    for (i=1;i<=3;i++)
		 {
			buff_3510iq[i]=pid_calc(&pid_spd[i], moto_chassis[i].speed_rpm,
																	posloop_out[i]);

		 }
		 buff_3510iq[0]=h;
  	Set_CM_Speed(CAN1,buff_3510iq[0],buff_3510iq[1],buff_3510iq[2],buff_3510iq[3]);
	 	 
	 


		 
	 if(led_flag>200)
	 {		 
	 led_flag=0;
	 LED0=!LED0;
	 LED1=!LED1;
	 }
	  delay_ms(5);
 }	 	

  }
 

void chassis_pid_param_init(void)
{
	int k=0;
	for (k=0; k < 4; k++)
	{
	PID_struct_init(&pid_spd[k], POSITION_PID, 10000, 1000, 5, 0.01f, 0.0f);
	PID_struct_init(&pid_pos[k], POSITION_PID, 8000, 1000, 1, 0.05f, 0.0f);	
	}

}









