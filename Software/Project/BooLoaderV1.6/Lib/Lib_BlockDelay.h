/******************************************
*Copyright (c) 2016, Dooya
*All rights reserved.
*
*@file my_delay.h
*@brief delay
*@version 0.1
*@data 2017/04/14
*@author xwb
******************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _LIB_BLOCK_DELAY_H_
#define _LIB_BLOCK_DELAY_H_

/* Includes ------------------------------------------------------------------*/
#include "config.h"
#include "type.h"
#include "stdint.h"

/* Public macro ------------------------------------------------------------*/
/* Public types ------------------------------------------------------------*/


/* Public variables ---------------------------------------------------------*/

/* Public constants --------------------------------------------------------*/



/* Public functions ------------------------------------------------------- */
void delay_us(UNS32 us);
void delay_ms(UNS32 us);
void delay_s(UNS32 s);
#endif

/************************ Copyright (c) 2016, Dooya *****END OF FILE****/

