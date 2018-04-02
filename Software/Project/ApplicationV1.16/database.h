/**
	*****************************************************************************
	*@file database.h
	*@brief 
	*@version 0.1
	*@data 2017/06/10
	*@author xwb
	*
	* Copyright(c) 2017, moorgen
 	* All rights reserved
	*****************************************************************************
*/ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _DATABASE_H_
#define _DATABASE_H_

/* Includes ------------------------------------------------------------------*/
#include "type.h"
#include "Lib_UserGlobal.h"
#include "BSP_EEPROM.h"
#include "Protocol_M1_Scene.h"
#include "Protocol_M1_Device.h"
/* Public macro ------------------------------------------------------------*/

#define EEPROM_HEAD			0xAA

#ifndef DataBaseNumber
#define DataBaseNumber
enum 
{
	DEVICE_INFO = 0,
	CHANNEL_INFO = 1,
	KEY_SET_INFO = 2,
	SCENE_LIST   = 3,
	SCENE_DATA   = 4,
	MAX_DATABASE_NUMBER
}DataBaseNumber;
#endif
/* Public types ------------------------------------------------------------*/
typedef struct
{
    UNS8* Data;
    UNS16 DataLen;
    UNS16 EEaddr;
    UNS8  Flag;
}DATABASE;
/* Public variables ---------------------------------------------------------*/

/* Public constants --------------------------------------------------------*/


/* Public functions ------------------------------------------------------- */
void DataBase_Init(void);
void clear_all_data(void);
void DataBase_Save(UNS8 DB_Index);
void DataBase_Poll(void);
void DataBase_SaveNow_ScenenList(UNS8 channel, UNS16 id);
void DataBase_Save_Scenen(UNS8 channel, UNS16 id);
UNS8 DataBase_Load_Scenen(UNS8 channel, UNS16 id);
void DataBase_SaveNowByIndex(UNS8 DB_Index);
#endif

/************************** Copyright (c) 2017, moorgen *******END OF FILE******/
