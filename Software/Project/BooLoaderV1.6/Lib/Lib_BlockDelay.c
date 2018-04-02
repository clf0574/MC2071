/******************************************
*Copyright (c) 2016, Dooya
*All rights reserved.
*
*@file master.c
*@brief ??????
*@version 0.1
*@data 2016/12/3
*@author xwb
******************************************/

/* Includes ------------------------------------------------------------------*/
#include "Lib_BlockDelay.h"
/* Private macro -------------------------------------------------------------*/  
/* Private types ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Public variables ---------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/ 
/* Public functions ---------------------------------------------------------*/  


/**
	*@brief Œ¢√Î—” ±∫Ø ˝
	*@param none
	*@retval none
	*@note none
	*/
void delay_us(UNS32 us)
{
	UNS32 clock = SystemCoreClock/1000000/7;
	UNS32 i;
	
	for(i=0; i<clock*us; i++)
	{
	}
}
/**
	*@brief ∫¡√Î—” ±∫Ø ˝
	*@param none
	*@retval none
	*@note none
	*/                             
void delay_ms(UNS32 ms)
{
	UNS32 i;
	for(i=0; i<ms; i++)
	{
		delay_us(1000);
	}
}
/**
	*@brief √Î—” ±∫Ø ˝
	*@param none
	*@retval none
	*@note none
	*/    
void delay_s(UNS32 s)
{
	UNS32 i;
	for(i=0; i<s; i++)
	{
		delay_ms(1000);
	}
}
/************************ Copyright (c) 2016, Dooya *****END OF FILE****/
