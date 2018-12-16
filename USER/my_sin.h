/*
**************************************************************************************************************
*	@file	my_sin.h
*	@author 
*	@version 
*	@date    
*	@brief	三角函数查表
***************************************************************************************************************
*/


#ifndef __MY_SIN_H
#define __MY_SIN_H

#ifdef __cplusplus
	extern "C" {
#endif


/*
 *	 头文件
 */
#include "stm32f10x.h"
#include <math.h>
#include <stdlib.h>


/*
 *	函数声明
 */
/*
 *	my_sin:	sin查表函数
 *	ang:	角度（单位°）
 */
extern float my_sin(float ang);


/*
 *	宏定义
 */
/*
 *	cos查表
 */
#define my_cos(ang)	my_sin(90-(ang))

#ifdef __cplusplus
}
#endif

#endif	/*    __MY_SIN_H    */

