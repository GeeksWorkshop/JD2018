#ifndef __LED_H
#define __LED_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//LED��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/2
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 
#define LED3 PBout(14)	// PA8
#define LED2 PBout(15)	// PD2	
#define LED1 PBout(13)	// PA8
#define LED0 PBout(12)	// PD2	

#define sennn0 PCin(0)	// PA8
#define sennn1 PCin(1)	// PA8

#define LED0 PBout(12)	// PD2	

void LED_Init(void);//��ʼ��

		 				    
#endif
