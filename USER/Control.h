#ifndef __CONTROL_H__
#define __CONTROL_H__

#include "stdio.h"	
#include "stm32f10x.h"
#include "sys.h" 

void chassiscontrol(void);
void updownplatform_control(void);

extern int chassis_data_order[4];
extern int updownplatform_data_order;

#endif 
