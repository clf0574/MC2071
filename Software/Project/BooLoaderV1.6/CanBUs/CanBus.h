/******************************************
*Copyright (c) 2016, Dooya
*All rights reserved.
*
*@file CanBus.h
*@brief CanBus
*@version 0.1
*@data 2017/6/17
*@author xwb
******************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _CAN_BUS_H_
#define _CAN_BUS_H_

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "BSP_can.h"
#include "Queue_List.h"
/* Public macro ------------------------------------------------------------*/
#define CAN_RX_OBJ_MSG_LMT 15
#define CAN_TX_OBJ_MSG_LMT 25
/* Public types ------------------------------------------------------------*/
typedef struct{
		ps_Queue pCAN_Rx_Queue;
		uint8_t  Index_ID;
}ts_CAN_Rx_Object, *ps_CAN_Rx_Object;

typedef struct{
		ps_Queue pCAN_Tx_Queue;
		FlagStatus Flag_Transmit;
} ts_CAN_Tx_Object, *ps_CAN_Tx_Object;
/* Public variables ---------------------------------------------------------*/

/* Public constants --------------------------------------------------------*/



/* Public functions ------------------------------------------------------- */
void CanBus_Poll(void);
ErrorStatus CAN_Tx_Object_Push(CanTxMsg* TxMessage);
void CAN_Tx_Object_Interrupt_Handler(void);
ErrorStatus CAN_Rx_Object_Push(CanRxMsg *RxMessage);
ErrorStatus CAN_Rx_Object_Popup(CanRxMsg *RxMessage);
void CanBus_Init(void);
#endif

/************************ Copyright (c) 2016, Dooya *****END OF FILE****/
