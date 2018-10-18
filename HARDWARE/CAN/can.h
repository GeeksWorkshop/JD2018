#ifndef __CAN_H
#define __CAN_H	 
#include "sys.h"	    
 //////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板
//CAN驱动 代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/11
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////

//CAN接收RX0中断使能
#define CAN_RX0_INT_ENABLE	1		//0,不使能;1,使能.								    
										 							 				    
u8 CAN_Mode_Init(u8 tsjw,u8 tbs2,u8 tbs1,u16 brp,u8 mode);//CAN初始化
 
u8 Can_Send_Msg(u8* msg,u8 len);						//发送数据

u8 Can_Receive_Msg(u8 *buf);							//接收数据

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
	int32_t raw_value;   									//编码器不经处理的原始值
	int32_t last_raw_value;								//上一次的编码器原始值
	int32_t ecd_value;                       //经过处理后连续的编码器值
	int32_t diff;													//两次编码器之间的差值
	int32_t temp_count;                   //计数用
	uint8_t buf_count;								//滤波更新buf用
	int32_t ecd_bias;											//初始编码器值	
	int32_t ecd_raw_rate;									//通过编码器计算得到的速度原始值
	int32_t rate_buf[RATE_BUF_SIZE];	//buf，for filter
	int32_t round_cnt;										//圈数
	int32_t filter_rate;											//速度
	float ecd_angle;											//角度
}Encoder;
#endif

















