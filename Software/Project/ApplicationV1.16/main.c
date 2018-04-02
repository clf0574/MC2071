/**
	*****************************************************************************
	*@file main.c
	*@brief 
	*@version 0.1
	*@data 2016/06/10
	*@author xwb
	*
	* Copyright(c) 2017, moorgen
 	* All rights reserved
	*****************************************************************************
*/ 

/* Includes ------------------------------------------------------------------*/
#include "config.h"
#include "CanBus.h"
#include "BSP.h"
#include "Protocol_M1.h"
#include "Protocol_M1_Device.h"
#include "database.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "configMap.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/** 
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{	
	BSP_Init(); 
	Sys_Run_State();
	Protocol_M1_Init();		
	DataBase_Init();
	CanBus_Init(); 
	BSP_Interrupt_Enable();
	Device_Init();
	ConfigMap_Init(1);
	
	while(1)
	{
		CanBus_Poll();
		BSP_GPIO_Rest();
		DataBase_Poll();
		BSP_WatchDog_Reset();	
	}
}

/************************** Copyright (c) 2017, moorgen *******END OF FILE******/

