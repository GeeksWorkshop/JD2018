#include "main.h"		
 int main(void)
 { 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	delay_init();	    	
	LED_Init();		  		
  TIM2_PWM_Init(999,1439);	
	uart_init(100000);	 
  delay_ms(1000);
  USART1_DMA_RX();
 	CAN_Mode_Init(CAN_SJW_1tq,CAN_BS2_2tq,CAN_BS1_3tq,6,CAN_Mode_Normal);//CAN初始化环回模式,波特率1Mbps    
  delay_ms(1000);
	chassis_pid_param_init();	 	 
	 while(1)		 
	 {
		led_flag++;
    for (i=0;i<4;i++)
		 {
		posloop_out[i]=pid_calc(&pid_pos[i], moto_chassis[i].total_angle,
																	pos_ref[i]);
    buff_3510iq[i]=pid_calc(&pid_spd[i], moto_chassis[i].speed_rpm,
																	posloop_out[i]);
		 }
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
	PID_struct_init(&pid_spd[k], POSITION_PID, 10000, 1000, 1, 0.0f, 0.0f);
	PID_struct_init(&pid_pos[k], POSITION_PID, 8000, 1000, 1, 0.05f, 0.0f);	
	}

}









