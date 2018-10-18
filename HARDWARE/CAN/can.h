#ifndef __CAN_H
#define __CAN_H	 
#include "sys.h"	    
 //////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//CAN���� ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/11
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////

//CAN����RX0�ж�ʹ��
#define CAN_RX0_INT_ENABLE	1		//0,��ʹ��;1,ʹ��.								    
										 							 				    
u8 CAN_Mode_Init(u8 tsjw,u8 tbs2,u8 tbs1,u16 brp,u8 mode);//CAN��ʼ��
 
u8 Can_Send_Msg(u8* msg,u8 len);						//��������

u8 Can_Receive_Msg(u8 *buf);							//��������

 #define   CAN_3510MotoAll_ID  0x200
 #define   CAN_3510Moto1_ID    0x201
 #define   CAN_3510Moto2_ID    0x202
 #define   CAN_3510Moto3_ID    0x203
 #define   CAN_3510Moto4_ID    0x204
 
 typedef struct
{
    int16_t  speed_rpm;

    int16_t  given_current;
    uint8_t  hall;

    uint16_t offset_angle;
    int32_t  round_cnt;
    int32_t  total_ecd;
    int32_t  total_angle;
	  u32      msg_cnt;
	
	  uint16_t angle; //abs angle range:[0,8191]
    uint16_t last_angle; //abs angle range:[0,8191]
} moto_measure_t;

void CanReceiveMsgProcess(CanRxMsg * msg);
void get_moto_offset(moto_measure_t* ptr,CanRxMsg * msg);
void get_moto_measure(moto_measure_t* ptr, CanRxMsg * msg);
void Set_CM_Speed(CAN_TypeDef *CANx, int16_t cm1_iq, int16_t cm2_iq, int16_t cm3_iq, int16_t cm4_iq);


#define RATE_BUF_SIZE 6
typedef struct{
	int32_t raw_value;   									//���������������ԭʼֵ
	int32_t last_raw_value;								//��һ�εı�����ԭʼֵ
	int32_t ecd_value;                       //��������������ı�����ֵ
	int32_t diff;													//���α�����֮��Ĳ�ֵ
	int32_t temp_count;                   //������
	uint8_t buf_count;								//�˲�����buf��
	int32_t ecd_bias;											//��ʼ������ֵ	
	int32_t ecd_raw_rate;									//ͨ������������õ����ٶ�ԭʼֵ
	int32_t rate_buf[RATE_BUF_SIZE];	//buf��for filter
	int32_t round_cnt;										//Ȧ��
	int32_t filter_rate;											//�ٶ�
	float ecd_angle;											//�Ƕ�
}Encoder;
#endif

















