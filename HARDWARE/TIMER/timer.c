#include "timer.h"
#include "led.h"
#include "usart.h"
//////////////////////////////////////////////////////////////////////////////////	 

void TIM2_PWM_Init(u16 arr,u16 psc)
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);// 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);// 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB , ENABLE); 
	                                                                     	

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	
	TIM_TimeBaseStructure.TIM_Period = arr; 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); 
 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; 
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
	TIM_OCInitStructure.TIM_Pulse = 500; 
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 
	

	TIM_OC2Init(TIM2, &TIM_OCInitStructure);  
  TIM_OC2Init(TIM2, &TIM_OCInitStructure);  
	
	TIM_OC3Init(TIM2, &TIM_OCInitStructure);  
	TIM_OC3Init(TIM2, &TIM_OCInitStructure); 

  TIM_OC4Init(TIM2, &TIM_OCInitStructure); 
	TIM_OC4Init(TIM2, &TIM_OCInitStructure); 

  TIM_CtrlPWMOutputs(TIM2,ENABLE);	
	TIM_ARRPreloadConfig(TIM2, ENABLE); 
	TIM_Cmd(TIM2, ENABLE);  

}
