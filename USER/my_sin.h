/*
**************************************************************************************************************
*	@file	my_sin.h
*	@author 
*	@version 
*	@date    
*	@brief	���Ǻ������
***************************************************************************************************************
*/


#ifndef __MY_SIN_H
#define __MY_SIN_H

#ifdef __cplusplus
	extern "C" {
#endif


/*
 *	 ͷ�ļ�
 */
#include "stm32f10x.h"
#include <math.h>
#include <stdlib.h>


/*
 *	��������
 */
/*
 *	my_sin:	sin�����
 *	ang:	�Ƕȣ���λ�㣩
 */
extern float my_sin(float ang);


/*
 *	�궨��
 */
/*
 *	cos���
 */
#define my_cos(ang)	my_sin(90-(ang))

#ifdef __cplusplus
}
#endif

#endif	/*    __MY_SIN_H    */

