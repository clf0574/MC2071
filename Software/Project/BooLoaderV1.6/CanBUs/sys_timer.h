/******************************************
*Copyright (c) 2016, Dooya
*All rights reserved.
*
*@file sys_timer.h
*@brief timer
*@version 0.1
*@data 2017/04/14
*@author xwb
******************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _SYS_TIMER_H_
#define _SYS_TIMER_H_

/* Includes ------------------------------------------------------------------*/
#include "config.h"
#include "type.h"
/* Public macro ------------------------------------------------------------*/
/* Public types ------------------------------------------------------------*/


/* Public variables ---------------------------------------------------------*/

/* Public constants --------------------------------------------------------*/

/* Public functions ------------------------------------------------------- */
void sysTimerInit(void);
void timer_dealyUs(UNS32 us);
void timer_dealyMs(UNS32 ms);
#endif

/************************ Copyright (c) 2016, Dooya *****END OF FILE****/



