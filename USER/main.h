#ifndef  _MAIN_H
#define  _MAIN_H

#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "encoder.h"
#include "dma.h"
#include "timer.h"
#include "can.h"
#include "pid.h"
#include "timer7.h"
#include "chassispid.h"

extern pid_t pid_pos[4];
extern RC_Ctl_t RC_CtrlData;
extern RC_Ctl_t RC2_CtrlData;
extern moto_measure_t moto_chassis[4] ;


extern float change1;
extern float x;
extern float y;
extern float h;



void chassis_pid_param_init(void);
#endif
