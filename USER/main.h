#ifndef  _MAIN_H
#define  _MAIN_H

#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "dma.h"
#include "timer.h"
#include "can.h"
#include "pid.h"
extern pid_t pid_pos[4];
extern RC_Ctl_t RC_CtrlData;
extern moto_measure_t moto_chassis[4] ;
int speed_ref=100;
int current_out=0; 
int i=0;
int led_flag=0;
s16 buff_3510iq[4],posloop_out[4];
s16 pos_ref[4]={1000,1000,1000,1000};
void chassis_pid_param_init(void);
#endif
