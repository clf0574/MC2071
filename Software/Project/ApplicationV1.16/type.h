/******************************************
*Copyright (c) 2016, Dooya
*All rights reserved.
*
*@file type.h
*@brief data type
*@version 0.1
*@data 2017/06/16
*@author xwb
******************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _TYPE_H_
#define _TYPE_H_

/* Includes ------------------------------------------------------------------*/
/* Public macro ------------------------------------------------------------*/
// Integers
#define INT8 signed char
#define INT16 signed short
#define INT32 signed int

// Unsigned integers
#define UNS8   unsigned char
#define UNS16  unsigned short
#define UNS32  unsigned int

// Reals
#define REAL32 float
#define REAL64 double

#define __IO volatile 

#define TIMEVAL UNS32

#define false           0x00
#define true            (!false)
#define FALSE           0x00
#define TRUE            (!FALSE)
/* Public types ------------------------------------------------------------*/
typedef union
{
    UNS16 Value;
    struct
    {
        UNS8  L;
        UNS8  H;
    }byte;  
}uUNS16;

typedef union
{
    UNS32 Value;
    struct
    {
        UNS8  L;
        UNS8  mL;
        UNS8  mH;
        UNS8  H;
    }byte;   
    struct
    {			
			uUNS16 L;
			uUNS16 H;
    }word;
}uUNS32;


/* Public variables ---------------------------------------------------------*/

/* Public constants --------------------------------------------------------*/



/* Public functions ------------------------------------------------------- */

#endif

/************************ Copyright (c) 2016, Dooya *****END OF FILE****/
