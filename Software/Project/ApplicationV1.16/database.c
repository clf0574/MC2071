/**
	*****************************************************************************
	*@file database.c
	*@brief 
	*@version 0.1
	*@data 2017/06/10
	*@author xwb
	*
	* Copyright(c) 2017, moorgen
 	* All rights reserved
	*****************************************************************************
*/ 

/* Includes ------------------------------------------------------------------*/
#include "database.h"
#include "BSP.h"

/* Private macro -------------------------------------------------------------*/


#define FLAG_None       0x00
#define FLAG_Save       0x01
#define FLAG_Save_Now   0x02
#define FLAG_NotInit    0x80

#define DB_ITEM_COUNT   (sizeof(DataBase)/sizeof(DATABASE))
/* Private types ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
#define TIME_SAFE   (20000)
#define SCENE_EE_ADDR 1024*7
static INT16 g_SafeTime = 0;


DATABASE DataBase[]=
{ 
    {(UNS8*)&g_DeviceInfo,        sizeof(g_DeviceInfo),      8    },
		{(UNS8*)&g_ChannelInfo,        sizeof(g_ChannelInfo),      100    },
		{(UNS8*)&g_KeySet,           sizeof(g_KeySet),         1024    },
		{(UNS8*)&g_SceneList,        sizeof(g_SceneList),      1024*3    },
		{(UNS8*)&g_SceneDataHead,        sizeof(g_SceneDataHead),      SCENE_EE_ADDR   }
		
};
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
 * @brief Êý¾Ý¶ÁÈ¡
 * @param  DB_Index[UNS8] Êý¾Ý¿é
 * @retval none
 *@note none
 */ 
UNS8 DataBase_Load(UNS8 DB_Index)
{
    UNS8 tmp;
    UNS8 *p;
    DATABASE * pDB = &DataBase[DB_Index];

    p = pDB->Data;

    if(BSP_EEPROM_Load(pDB->Data,pDB->DataLen,pDB->EEaddr) == true)
    {
				if(pDB->Data[0] != 0xAA)
				{
					return false;
				}
        tmp = GetChkSum(p, pDB->DataLen);
        if (tmp == 0xff)  //¼ìÑéºÍ¶Ô
            return(true);
    }
		
    return(false);
}

/**
 * @brief Êý¾Ý±£´æµ½EEprom
 * @param  Data[UNS8 *] Êý¾Ý
 * @param  DataLen[UNS16] Êý¾Ý³¤¶È
 * @param  EEaddr[UNS16] µØÖ·
 * @retval none
 *@note none
 */ 
void DataBase_SaveNow(UNS8* Data, UNS16 DataLen, UNS16 EEaddr)
{		
//	  UNS8 tmp = 0, err = 0;
//    UNS8 *p;
//		UNS8 buffer[2048];

    
    BSP_EEPROM_Save(Data,DataLen,EEaddr);
//		if(BSP_EEPROM_Load(buffer,DataLen,EEaddr) == true)
//    {
//				if(buffer[0] != 0xAA)
//				{
//					err = 1;
//				}
//				else
//				{
//					p = &buffer[0];
//					tmp = GetChkSum(p, DataLen-1);
//					if (tmp != Data[DataLen-1])  //¼ìÑéºÍ¶
//					{
//						err = 1;
//					}
//				}
//        if(err == 1)
//				{
//					 BSP_EEPROM_Save(Data,DataLen,EEaddr);
//				}					 
//    }
		
}

/**
 * @brief ±£´æ³¡¾°ÁÐ±í
 * @param  DB_Index[UNS8] Êý¾Ý¿é
 * @retval none
 *@note none
 */ 
void DataBase_SaveNow_ScenenList(UNS8 channel, UNS16 id)
{
    UNS8 *p;
    DATABASE * pDB;
	UNS32 addr = 0;

    DataBase[SCENE_LIST].Flag = FLAG_None;

    pDB = &DataBase[SCENE_LIST];
    p = pDB->Data;
    pDB->Data[pDB->DataLen-1] = (~ GetChkSum(p, pDB->DataLen - 1));  //ÖØÐÂ¼ÆËã¼ìÑéºÍ
		
	addr = &g_SceneList.CheckSum - &g_SceneList.Head;
    DataBase_SaveNow(&(pDB->Data[addr]),(pDB->DataLen-addr),(pDB->EEaddr+addr));
	addr = ((UNS8*)&g_SceneList.SceneList[channel].SceneId[id]) - &g_SceneList.Head;
    DataBase_SaveNow(&(pDB->Data[addr]), 2 ,(pDB->EEaddr+addr));
}

/**
 * @brief Êý¾Ý±£´æ
 * @param  DB_Index[UNS8] Êý¾Ý¿é
 * @retval none
 *@note none
 */ 
void DataBase_SaveNowByIndex(UNS8 DB_Index)
{
    UNS8 *p;
    DATABASE * pDB;

    DataBase[DB_Index].Flag = FLAG_None;

    pDB = &DataBase[DB_Index];
    p = pDB->Data;
    pDB->Data[pDB->DataLen-1] = (~ GetChkSum(p, pDB->DataLen - 1));  //ÖØÐÂ¼ÆËã¼ìÑéºÍ
		
    DataBase_SaveNow(pDB->Data,pDB->DataLen,pDB->EEaddr);
}
/**
 * @brief Êý¾Ý±£´æ±ê¼Ç
 * @param  DB_Index[UNS8] Êý¾Ý¿é
 * @retval none
 *@note none
 */  
void DataBase_Save(UNS8 DB_Index)
{
	
	DataBase[DB_Index].Flag = FLAG_Save;
	if(DB_Index == KEY_SET_INFO)
	{
		g_SafeTime = 0;
	}
}
/**
 * @brief ³¡¾°Êý¾Ý±£´æ
 * @param  channel[UNS8] Í¨µÀµØÖ·
 * @param  id[UNS16] ³¡¾°¶ÔÓ¦µÄÊý×éÎ»ÖÃ
 * @retval none
 *@note none
 */  
void DataBase_Save_Scenen(UNS8 channel, UNS16 id)
{
		g_SafeTime = TIME_SAFE;
//		delay_ms(10);0825
    DataBase[SCENE_DATA].Flag = FLAG_Save;
		DataBase[SCENE_DATA].EEaddr = SCENE_EE_ADDR + channel*MAX_SCENE_NUMBER*sizeof(g_SceneDataHead)+ id*sizeof(g_SceneDataHead);
		DataBase_SaveNowByIndex(SCENE_DATA);

		g_SafeTime = TIME_SAFE;		
}
/**
 * @brief ³¡¾°Êý¾Ý¶ÁÈ¡
 * @param  channel[UNS8] Í¨µÀµØÖ·
 * @param  id[UNS16] ³¡¾°¶ÔÓ¦µÄÊý×éÎ»ÖÃ
 * @retval none
 *@note none
 */  
UNS8 DataBase_Load_Scenen(UNS8 channel, UNS16 id)
{
    UNS8 tmp;
    UNS8 *p;
    DATABASE * pDB = &DataBase[SCENE_DATA];
		
    p = pDB->Data;
		pDB->EEaddr = SCENE_EE_ADDR + channel*MAX_SCENE_NUMBER*sizeof(g_SceneDataHead)+ id*sizeof(g_SceneDataHead);
    if(BSP_EEPROM_Load(pDB->Data,pDB->DataLen,pDB->EEaddr) == true)
    {
				if(pDB->Data[0] != 0xAA)
				{
					return false;
				}
        tmp = GetChkSum(p, pDB->DataLen);
        if (tmp == 0xff)  //¼ìÑéºÍ¶Ô
            return(true);
    }

    return(false);
}
/**
 * @brief  Êý¾Ý¶¨Ê±±£´æ
 * @param  none
 * @retval none
 	*@note none
 */                           
void DataBase_Poll(void)
{
    UNS8 i;

	  if(g_SafeTime > 0)
    {
        g_SafeTime--;
        return;
    }
		g_SafeTime = TIME_SAFE;
    for(i=0; i<DB_ITEM_COUNT;   i++)
    {
        if(DataBase[i].Flag == FLAG_Save)
        {
            DataBase_SaveNowByIndex(i);
            break;
        }
    }
}

/**
 * @brief  Í¨µÀÊý¾Ý³õÊ¼»¯
 * @param  none
 * @retval none
 *@note none
 */    
void ChannelInfo_Init(void)
{
	UNS8 i;
	
	memset(&g_ChannelInfo, 0, sizeof(g_ChannelInfo));
	g_ChannelInfo.Head= EEPROM_HEAD;
	for(i=0; i<DEVICE_CHANNEL_NUMBER; i++)
	{	
		g_ChannelInfo.Channel[i].Type = DEVICE_TYPE;
	}	
}

/**
 * @brief Çå³ýËùÓÐÊý¾Ý
 * @param  none
 * @retval none
 *@note none
 */  
void clear_all_data(void)
{
		memset(DataBase[DEVICE_INFO].Data, 0, DataBase[DEVICE_INFO].DataLen);
		g_DeviceInfo.Head = EEPROM_HEAD;
		Mac_Init();
		g_DeviceInfo.AddrHAL = ((Get_CRC8(g_DeviceInfo.MAC, 8)/2)<<4)&0x07F0;
		g_DeviceInfo.channelNumber = DEVICE_CHANNEL_NUMBER;
		DataBase_SaveNowByIndex(DEVICE_INFO);
		
		ChannelInfo_Init();
		DataBase_SaveNowByIndex(CHANNEL_INFO);
	
		memset(DataBase[SCENE_LIST].Data, 0, DataBase[SCENE_LIST].DataLen);
		g_SceneList.Head = EEPROM_HEAD;
		DataBase_SaveNowByIndex(SCENE_LIST);
		
		memset(DataBase[KEY_SET_INFO].Data, 0, DataBase[KEY_SET_INFO].DataLen);
		g_KeySet.head = EEPROM_HEAD;
		g_KeySet.shakeVal = 1;
		g_KeySet.keyMode = KEY_LOCAL_MODE;
		g_KeySet.linghtMode = LINGHT_ATUO_ON;
		g_KeySet.LedMode = MODE_DEAL_OFF;
		g_KeySet.Linght = 0xFF;
		DataBase_SaveNowByIndex(KEY_SET_INFO);
		
		BSP_Interrupt_Disable();
		BSP_ResetTo_App();

}
/**
 * @brief Êý¾Ý³õÊ¼»¯
 * @param  none
 * @retval none
 *@note none
 */    
void DataBase_Init(void)
{
	UNS8 i;
	
	
	if(DataBase_Load(DEVICE_INFO) == false)
	{		
		memset(DataBase[DEVICE_INFO].Data, 0, DataBase[DEVICE_INFO].DataLen);
		g_DeviceInfo.Head = EEPROM_HEAD;
		Mac_Init();
		g_DeviceInfo.AddrHAL = ((Get_CRC8(g_DeviceInfo.MAC, 8)/2)<<4)&0x07F0;
		if((g_DeviceInfo.AddrHAL&0x07F0) == 0x7F0)
		{
			g_DeviceInfo.AddrHAL = 0x07E0;
		}
		g_DeviceInfo.channelNumber = DEVICE_CHANNEL_NUMBER;
		DataBase_SaveNowByIndex(DEVICE_INFO);
		
		memset(DataBase[SCENE_LIST].Data, 0, DataBase[SCENE_LIST].DataLen);
		g_SceneList.Head = EEPROM_HEAD;
		DataBase_SaveNowByIndex(SCENE_LIST);	
	}


	if(DataBase_Load(CHANNEL_INFO) == false)
	{		
		ChannelInfo_Init();
		DataBase_SaveNowByIndex(CHANNEL_INFO);
	}
	
	if(DataBase_Load(KEY_SET_INFO) == false)
	{
		memset(DataBase[KEY_SET_INFO].Data, 0, DataBase[KEY_SET_INFO].DataLen);
		g_KeySet.head = EEPROM_HEAD;
		g_KeySet.shakeVal = 1;
		g_KeySet.keyMode = KEY_LOCAL_MODE;
		g_KeySet.linghtMode = LINGHT_ATUO_ON;
		g_KeySet.LedMode = MODE_DEAL_OFF;
		g_KeySet.Linght = 0xFF;
		DataBase_SaveNowByIndex(KEY_SET_INFO);
	}	
	bsp_SetKeyMode(g_KeySet.keyMode);
	bsp_SetLinghtMode(g_KeySet.linghtMode);
	bsp_pled_brightness_adj(g_KeySet.Linght);
	bsp_pled_LED_mode(g_KeySet.LedMode);
	DataBase[KEY_SET_INFO].Flag = FLAG_None;
	if(DataBase_Load(SCENE_LIST) == false)
	{
//		memset(DataBase[SCENE_LIST].Data, 0, DataBase[SCENE_LIST].DataLen);
//		g_SceneList.Head = EEPROM_HEAD;
//		DataBase_SaveNowByIndex(SCENE_LIST);
	}	
	
	
	/*³õÊ¼»¯Éè±¸×´Ì¬Öµ*/
	for(i=0; i<DEVICE_CHANNEL_NUMBER; i++)
	{	
		g_ChannelState[i].state = 0x02;
		g_SceneExe[i].timer = TIMER_NONE;
		g_ChannelRunMode[i].runTimer = TIMER_NONE;
		g_ChannelRunMode[i].sceneTimer = TIMER_NONE;
	}
	g_ChannelRunMode[PANEL_CHANNEL_ADDR].runTimer = TIMER_NONE;
	g_ChannelRunMode[PANEL_CHANNEL_ADDR].sceneTimer = TIMER_NONE;
			
}


/************************** Copyright (c) 2017, moorgen *******END OF FILE******/

