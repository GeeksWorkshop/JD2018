#include "main.h"	
#include "jetson.h"	


u8 pData222[30];
int led_flag=0;

 int main(void)
 { 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//???????????2:2??????,2??????
	delay_init();	 
	
//		delay_ms(1500);	
//		delay_ms(1500);	
//		delay_ms(1500);	
//		delay_ms(1500);	
//		delay_ms(1500);	
//		delay_ms(1500);	
//		delay_ms(1500);	
//		delay_ms(1500);	
//		delay_ms(1500);	
	
	LED_Init();		  		
  TIM2_PWM_Init(999,1439);	
	uart_init(100000);	
	uart3_init(115200);	 
		USART1_DMA_RX();
		USART3_DMA_RX();
	 
		encoder_init(115200);
		CAN_Mode_Init(CAN_SJW_1tq,CAN_BS2_2tq,CAN_BS1_3tq,6,CAN_Mode_Normal);//CAN???????,???1Mbps    
		delay_ms(1000);
		chassis_pid_param_init();	 
		TIM4_Configuration();
	 
			 RC_CtrlData.rc.ch3=0x400;
			 RC_CtrlData.rc.ch2=0x400;
			 RC_CtrlData.rc.ch0=0x400;
			 RC_CtrlData.rc.ch1=0x400;
			 
			 RC2_CtrlData.rc.ch3=0x400;
			 RC2_CtrlData.rc.ch2=0x400;
			 RC2_CtrlData.rc.ch0=0x400;
			 RC2_CtrlData.rc.ch1=0x400;

	 while(1)		 
	 {
				led_flag++;
					 if(led_flag>20)
					 {		 
					 led_flag=0;
					 LED0=!LED0;
					 LED1=!LED1;
						 
//						 	USART3->DR=0x0a;
//							delay_ms(1);	
//						 	USART3->DR=0x11;						 
//							delay_ms(1);	
//							USART3->DR=0x55;
//							delay_ms(1);
//							USART3->DR=0xaa;
//							delay_ms(1);
//							USART3->DR=0x55;
//							delay_ms(1);
//							USART3->DR=0xaa;
//							delay_ms(1);
//						 	USART3->DR=0x11;
//							delay_ms(1);
//							USART3->DR=0xa0;	
					 }
				delay_ms(5);
		}	 
	 
 }
 

void chassis_pid_param_init(void)
{

	PID_struct_init(&pid_pos[0], POSITION_PID, 15000, 0, 60, 0.0f, 0.0f);//h
	
	PID_struct_init(&pid_pos[1], POSITION_PID, 800, 400,80, 0.1f, 0.0f);//角度
	PID_struct_init(&pid_pos[2], POSITION_PID, 800, 400, -40.0f, -0.2f, 0.0f);//x
	PID_struct_init(&pid_pos[3], POSITION_PID, 800, 400, -40.0f, -0.2f, 0.0f);//	y
	
	PID_struct_init(&pid_spd[0], POSITION_PID, 10000, 5000, 10, 0.0f, 0.0f);//底盘电机
	PID_struct_init(&pid_spd[1], POSITION_PID, 10000, 5000, 10, 0.0f, 0.0f);//底盘电机
	PID_struct_init(&pid_spd[2], POSITION_PID, 10000, 5000, 10, 0.0f, 0.0f);//底盘电机
	PID_struct_init(&pid_spd[3], POSITION_PID,10000, 5000, 10, 0.0f, 0.0f);//底盘电机
	
	//void PID_struct_init(pid,mode,maxout,intergral_limit,kp,ki,kd)
}









