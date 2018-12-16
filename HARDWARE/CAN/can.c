#include "can.h"
#include "led.h"
//#include "delay.h"
//#include "usart.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK��ӢSTM32������
//CAN���� ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/11
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////
//CAN��ʼ��
//tsjw:����ͬ����Ծʱ�䵥Ԫ.��Χ:CAN_SJW_1tq~ CAN_SJW_4tq
//tbs2:ʱ���2��ʱ�䵥Ԫ.   ��Χ:CAN_BS2_1tq~CAN_BS2_8tq;
//tbs1:ʱ���1��ʱ�䵥Ԫ.   ��Χ:CAN_BS1_1tq ~CAN_BS1_16tq
//brp :�����ʷ�Ƶ��.��Χ:1~1024;  tq=(brp)*tpclk1
//������=Fpclk1/((tbs1+1+tbs2+1+1)*brp);
//mode:CAN_Mode_Normal,��ͨģʽ;CAN_Mode_LoopBack,�ػ�ģʽ;
//Fpclk1��ʱ���ڳ�ʼ����ʱ������Ϊ36M,�������CAN_Mode_Init(CAN_SJW_1tq,CAN_BS2_8tq,CAN_BS1_9tq,4,CAN_Mode_LoopBack);
//������Ϊ:36M/((8+9+1)*4)=500Kbps
//����ֵ:0,��ʼ��OK;
//    ����,��ʼ��ʧ��;


moto_measure_t moto_chassis[4] = { 0 }; //4 chassis moto

int UpDownPlatform_Motor[2];

int motordata[4][2];
CanRxMsg can1_rx_message;
CanTxMsg can1_tx_message;

vs32 difffff=0;
vs32 latchhhh=2050;
PlatformMotor PMotor={0,0,0,0,&PlatformCircle};

u8 CAN_Mode_Init(u8 tsjw,u8 tbs2,u8 tbs1,u16 brp,u8 mode)
{

	  GPIO_InitTypeDef GPIO_InitStructure; 
	  CAN_InitTypeDef        CAN_InitStructure;
 	  CAN_FilterInitTypeDef  CAN_FilterInitStructure;
#if CAN_RX0_INT_ENABLE 
   	NVIC_InitTypeDef  NVIC_InitStructure;
#endif

	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//ʹ��PORTAʱ��	                   											 

  	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);//ʹ��CAN1ʱ��	

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//��������
    GPIO_Init(GPIOA, &GPIO_InitStructure);		//��ʼ��IO
   
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU ;//��������
    GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��IO
	  
 	//CAN��Ԫ����
	  CAN_DeInit(CAN1);
    CAN_StructInit(&CAN_InitStructure);
 	  CAN_InitStructure.CAN_TTCM=DISABLE;						 //��ʱ�䴥��ͨ��ģʽ  //
 	  CAN_InitStructure.CAN_ABOM=DISABLE;						 //����Զ����߹���	 //
  	CAN_InitStructure.CAN_AWUM=DISABLE;						 //˯��ģʽͨ���������(���CAN->MCR��SLEEPλ)//
  	CAN_InitStructure.CAN_NART=DISABLE;						 	//��ֹ�����Զ����� //
  	CAN_InitStructure.CAN_RFLM=DISABLE;						 //���Ĳ�����,�µĸ��Ǿɵ� // 
  	CAN_InitStructure.CAN_TXFP=ENABLE;						 //���ȼ��ɱ��ı�ʶ������ //
  	CAN_InitStructure.CAN_Mode= mode;	         //ģʽ���ã� mode:0,��ͨģʽ;1,�ػ�ģʽ; //
  	//���ò�����
  	CAN_InitStructure.CAN_SJW=tsjw;				//����ͬ����Ծ���(Tsjw)Ϊtsjw+1��ʱ�䵥λ  CAN_SJW_1tq	 CAN_SJW_2tq CAN_SJW_3tq CAN_SJW_4tq
  	CAN_InitStructure.CAN_BS1=tbs1; //Tbs1=tbs1+1��ʱ�䵥λCAN_BS1_1tq ~CAN_BS1_16tq
  	CAN_InitStructure.CAN_BS2=tbs2;//Tbs2=tbs2+1��ʱ�䵥λCAN_BS2_1tq ~	CAN_BS2_8tq
  	CAN_InitStructure.CAN_Prescaler=brp;            //��Ƶϵ��(Fdiv)Ϊbrp+1	//
  	CAN_Init(CAN1, &CAN_InitStructure);            // ��ʼ��CAN1 

 	  CAN_FilterInitStructure.CAN_FilterNumber=0;	  //������0
   	CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask; 
  	CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit; //32λ 
  	CAN_FilterInitStructure.CAN_FilterIdHigh=0x0000;////32λID
  	CAN_FilterInitStructure.CAN_FilterIdLow=0x0000;
  	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0x0000;//32λMASK
  	CAN_FilterInitStructure.CAN_FilterMaskIdLow=0x0000;
  	CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_Filter_FIFO0;//������0������FIFO0
 	  CAN_FilterInitStructure.CAN_FilterActivation=ENABLE; //���������0

  	CAN_FilterInit(&CAN_FilterInitStructure);//�˲�����ʼ��
#if CAN_RX0_INT_ENABLE
	
	  CAN_ITConfig(CAN1,CAN_IT_FMP0,ENABLE);//FIFO0��Ϣ�Һ��ж�����.		    
    CAN_ITConfig(CAN1,CAN_IT_TME,ENABLE); 
		
  	NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;     // �����ȼ�Ϊ1
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;            // �����ȼ�Ϊ0
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  	NVIC_Init(&NVIC_InitStructure);
		

		
		NVIC_InitStructure.NVIC_IRQChannel = USB_HP_CAN1_TX_IRQn;
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;     // �����ȼ�Ϊ1
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;            // �����ȼ�Ϊ0
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  	NVIC_Init(&NVIC_InitStructure);
   
   
#endif
	return 0;
}   
 


#if CAN_RX0_INT_ENABLE	//ʹ��RX0�ж�
//�жϷ�����			    
		CanRxMsg RxMessage;

void USB_LP_CAN1_RX0_IRQHandler(void)
{
 	 CanRxMsg rx_message;	
		 if (CAN_GetITStatus(CAN1,CAN_IT_FMP0)!= RESET)
	{
        CAN_ClearITPendingBit(CAN1, CAN_IT_FMP0);
        CAN_Receive(CAN1, CAN_FIFO0, &rx_message);
			     if(rx_message.StdId==0x201)
					 { motordata[0][0] =(int16_t)((rx_message.Data[0]<<8)|(rx_message.Data[1]));
					   motordata[0][1] =(int16_t)((rx_message.Data[2]<<8)|(rx_message.Data[3]));}
					 			     else if(rx_message.StdId==0x202)
										 {motordata[1][0] =(int16_t)((rx_message.Data[0]<<8)|(rx_message.Data[1]));
					            motordata[1][1] =(int16_t)((rx_message.Data[2]<<8)|(rx_message.Data[3]));}
										 		else	  if(rx_message.StdId==0x203)
												{motordata[2][0] =(int16_t)((rx_message.Data[0]<<8)|(rx_message.Data[1]));
					               motordata[2][1] =(int16_t)((rx_message.Data[2]<<8)|(rx_message.Data[3]));}
												else 		 if(rx_message.StdId==0x204)
												{motordata[3][0] =(int16_t)((rx_message.Data[0]<<8)|(rx_message.Data[1]));
					               motordata[3][1] =(int16_t)((rx_message.Data[2]<<8)|(rx_message.Data[3]));}
												
						 PMotor.Pos_Now=motordata[0][0];
												 
						 PMotor.CircleCalc(&PMotor);
						difffff=PMotor.Pos_Now-PMotor.Pos_Last;
						 PMotor.Pos_Last=PMotor.Pos_Now;
    }

   
}

void PlatformCircle(PlatformMotor *PM)
{
	PM->Pos_Diff=PM->Pos_Now-PM->Pos_Last;
	if(PM->Pos_Diff<-latchhhh)
		PM->CircleNum++;
	else if(PM->Pos_Diff>latchhhh)
		PM->CircleNum--;
	else;
}


void USB_HP_CAN1_TX_IRQHandler(void)
{
    if (CAN_GetITStatus(CAN1,CAN_IT_TME)!= RESET) 
	{
		CAN_ClearITPendingBit(CAN1,CAN_IT_TME);
    }
}


#endif



//can�ڽ������ݲ�ѯ
//buf:���ݻ�����;	 
//����ֵ:0,�����ݱ��յ�;
//		 ����,���յ����ݳ���;
u8 Can_Receive_Msg(u8 *buf)
{		   		   
 	 CanRxMsg rx_message;	
		 if (CAN_GetITStatus(CAN1,CAN_IT_FMP0)!= RESET)
	{
        CAN_ClearITPendingBit(CAN1, CAN_IT_FMP0);
        CAN_Receive(CAN1, CAN_FIFO0, &rx_message);
			     if(rx_message.StdId==0x201)
					 { motordata[0][0] =(int16_t)((rx_message.Data[0]<<8)|(rx_message.Data[1]));
					   motordata[0][1] =(int16_t)((rx_message.Data[2]<<8)|(rx_message.Data[3]));}
					 			     else if(rx_message.StdId==0x202)
										 {motordata[1][0] =(int16_t)((rx_message.Data[0]<<8)|(rx_message.Data[1]));
					            motordata[1][1] =(int16_t)((rx_message.Data[2]<<8)|(rx_message.Data[3]));}
										 		else	  if(rx_message.StdId==0x203)
												{motordata[2][0] =(int16_t)((rx_message.Data[0]<<8)|(rx_message.Data[1]));
					               motordata[2][1] =(int16_t)((rx_message.Data[2]<<8)|(rx_message.Data[3]));}
												else 		 if(rx_message.StdId==0x204)
												{motordata[3][0] =(int16_t)((rx_message.Data[0]<<8)|(rx_message.Data[1]));
					               motordata[3][1] =(int16_t)((rx_message.Data[2]<<8)|(rx_message.Data[3]));
												}

    }
		return 0;	
		
}







void CanReceiveMsgProcess(CanRxMsg * msg)
{      
        //GMYawEncoder.ecd_bias = yaw_ecd_bias;
  //      can_count++;
		switch(msg->StdId)
		{
		case CAN_3510Moto1_ID:
    case CAN_3510Moto2_ID:
    case CAN_3510Moto3_ID:
    case CAN_3510Moto4_ID:
    {
        static u8 i;
        i = msg->StdId- CAN_3510Moto1_ID;

        moto_chassis[i].msg_cnt++ <= 50 ? get_moto_offset(&moto_chassis[i], msg) : get_moto_measure(&moto_chassis[i], msg);
    }
    break;
			
				default:
				{
				}
		}
		
}


void get_moto_offset(moto_measure_t* ptr,CanRxMsg * msg)
{
    ptr->angle        = (uint16_t)(msg->Data[0] << 8 | msg->Data[1]);
    ptr->offset_angle = ptr->angle;
}

void get_moto_measure(moto_measure_t* ptr, CanRxMsg * msg)
{
    ptr->speed_rpm     = (int16_t)(msg->Data[2] << 8 | msg->Data[3]);
   
    ptr->given_current = (int16_t)(msg->Data[4] << 8 | msg->Data[5]) / -5;
    ptr->hall          = msg->Data[6];
	
	  ptr->last_angle    = ptr->angle;
    ptr->angle         = (uint16_t)(msg->Data[0] << 8 | msg->Data[1]);
	
    if (ptr->angle - ptr->last_angle > 4096)
		{
			ptr->round_cnt--;
			//ptr->ecd_raw_rate = ptr->angle - ptr->last_angle - 8192;
		}
    else if (ptr->angle - ptr->last_angle < -4096)
		{
      ptr->round_cnt++;
			//ptr->ecd_raw_rate = ptr->angle - ptr->last_angle + 8192;
		}
		else
		{
			//ptr->ecd_raw_rate = ptr->angle - ptr->last_angle;
		}
		//total encoder value
    ptr->total_ecd = ptr->round_cnt * 8192 + ptr->angle - ptr->offset_angle;
	  //total angle/degree
		ptr->total_angle = ptr->total_ecd * 360 / 8192;
}


void Set_CM_Speed(CAN_TypeDef *CANx, int16_t cm1_iq, int16_t cm2_iq, int16_t cm3_iq, int16_t cm4_iq)
{
    CanTxMsg tx_message;
    tx_message.StdId = 0x200;
    tx_message.IDE = CAN_Id_Standard;
    tx_message.RTR = CAN_RTR_Data;
    tx_message.DLC = 0x08;
    
    tx_message.Data[0] = (uint8_t)(cm1_iq >> 8);
    tx_message.Data[1] = (uint8_t)cm1_iq;
    tx_message.Data[2] = (uint8_t)(cm2_iq >> 8);
    tx_message.Data[3] = (uint8_t)cm2_iq;
    tx_message.Data[4] = (uint8_t)(cm3_iq >> 8);
    tx_message.Data[5] = (uint8_t)cm3_iq;
    tx_message.Data[6] = (uint8_t)(cm4_iq >> 8);
    tx_message.Data[7] = (uint8_t)cm4_iq;
    CAN_Transmit(CANx,&tx_message);
}

