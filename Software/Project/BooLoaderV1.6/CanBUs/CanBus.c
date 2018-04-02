/******************************************
*Copyright (c) 2016, Dooya
*All rights reserved.
*
*@file CanBus.c
*@brief can通信
*@version 0.1
*@data 2017/6/17
*@author xwb
******************************************/

/* Includes ------------------------------------------------------------------*/
#include "CanBus.h"
#include "Protocol_xModem.h"
/* Private macro -------------------------------------------------------------*/ 

/* Private types ------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
static ts_CAN_Tx_Object CAN_Tx_Object;
static ts_CAN_Rx_Object CAN_Rx_Object;
static CanTxMsg CAN_TX_Obj_Msg;
/* Public variables ---------------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/ 
/* Public functions ---------------------------------------------------------*/  
 
/**
	*@brief CAN 接收初始化
	*@param	none
	*@retval [ErrorStatus]
	*@note none
	*/
ErrorStatus CAN_Rx_Objects_Init(void)
{
		CAN_Rx_Object.pCAN_Rx_Queue = Create_Queue(sizeof(CanRxMsg), CAN_RX_OBJ_MSG_LMT);

		if(CAN_Rx_Object.pCAN_Rx_Queue != NULL)
				return SUCCESS;
		else
				return ERROR;
}

/**
	*@brief CAN 接收数据放入队列
	*@param	RxMessage[CanRxMsg *] Can数据
	*@retval [ErrorStatus]
	*@note none
	*/
ErrorStatus CAN_Rx_Object_Push(CanRxMsg *RxMessage)
{
		if(CAN_Rx_Object.pCAN_Rx_Queue != NULL)
		{
				return(Queue_Write(RxMessage, CAN_Rx_Object.pCAN_Rx_Queue));
		}
		else
		{
				return ERROR;
		}
}
/**
	*@brief 从队列中取出CAN数据
	*@param	RxMessage[CanRxMsg *] Can数据
	*@retval [ErrorStatus]
	*@note none
	*/                             
ErrorStatus CAN_Rx_Object_Popup(CanRxMsg *RxMessage)
{
		ErrorStatus Status_Read = ERROR;
		
		if(CAN_Rx_Object.pCAN_Rx_Queue == NULL)
		{
				return ERROR;
		}

		CAN_NVIC_Config(DISABLE);

		Status_Read = Queue_Read(RxMessage, CAN_Rx_Object.pCAN_Rx_Queue);
		CAN_NVIC_Config(ENABLE);

		return(Status_Read);
}

void CanBus_Poll(void)
{
	static CanRxMsg msg;
	if(CAN_Rx_Object_Popup(&msg))
	{
		Protocol_Can_Rec_Update(&msg);
	}
}
/**
	*@brief CAN 发送初始化
	*@param	none
	*@retval [ErrorStatus]
	*@note none
	*/
ErrorStatus CAN_Tx_Objects_Init(void)
{
		CAN_Tx_Object.pCAN_Tx_Queue = Create_Queue(sizeof(CanTxMsg), CAN_TX_OBJ_MSG_LMT);

		if(CAN_Tx_Object.pCAN_Tx_Queue != NULL)
				return SUCCESS;
		else
				return ERROR;
}
/**
	*@brief 从队列中取出CAN数据
	*@param	TxMessage[CanTxMsg *] Can数据
	*@retval [ErrorStatus]
	*@note none
	*/   
static ErrorStatus CAN_Tx_Object_Popup(CanTxMsg* TxMessage)
{
		if(CAN_Tx_Object.pCAN_Tx_Queue != NULL)
		{
				if(Queue_Read(TxMessage, CAN_Tx_Object.pCAN_Tx_Queue) == SUCCESS)
						return SUCCESS;
				else
						return ERROR;
		}
		else
		{
				return ERROR;
		}
}

/**
	*@brief CAN发送队列是否为空
	*@param	none
	*@retval [ErrorStatus]
	*@note none
	*/ 
static FlagStatus CAN_Tx_Object_Is_Empty(void)
{
		return(Queue_Is_Empty(CAN_Tx_Object.pCAN_Tx_Queue));
}
/**
	*@brief CAN发送状态
	*@param	NewState[FlagStatus]：SET 发送 RESET空闲
	*@retval [ErrorStatus]
	*@note none
	*/ 
static void CAN_Tx_Object_Flag_Set(FlagStatus NewState)
{
		CAN_Tx_Object.Flag_Transmit = NewState;
}
/**
	*@brief CAN发送完成中断
	*@param	none
	*@retval none
	*@note none
	*/  
void CAN_Tx_Object_Interrupt_Handler(void)
{
		if(CAN_GetITStatus(CAN1, CAN_IT_TME) == SET)
		{
				if(CAN_Tx_Object_Is_Empty() != SET)
				{
						if(CAN_Tx_Object_Popup(&CAN_TX_Obj_Msg) == SUCCESS)
								CAN_Transmit(CAN1, &CAN_TX_Obj_Msg);
				}
				else
				{
						if(CAN_TX_FIFO_Is_Empty(CAN1) == SET)
						{
								CAN_Tx_Object_Flag_Set(RESET);
						}
				}
		}
}
/**
	*@brief 从发送数据放入队列并发送
	*@param	TxMessage[CanTxMsg *] Can数据
	*@retval [ErrorStatus]
	*@note none
	*/ 
ErrorStatus CAN_Tx_Object_Push(CanTxMsg* TxMessage)
{
	CanTxMsg CAN_TX_Msg_Obj_Push;
	if(CAN_Tx_Object.pCAN_Tx_Queue != NULL)
	{
			if(Queue_Is_Full(CAN_Tx_Object.pCAN_Tx_Queue) != SET)
			{
					if(CAN_Tx_Object.Flag_Transmit == RESET)
					{
							Queue_Write((ps_Item)(TxMessage), CAN_Tx_Object.pCAN_Tx_Queue);

							if(Queue_Read(&CAN_TX_Msg_Obj_Push, CAN_Tx_Object.pCAN_Tx_Queue) == SUCCESS)
							{
									CAN_Tx_Object.Flag_Transmit = SET;
									BSP_CAN_Send_Msg(CAN1, &CAN_TX_Msg_Obj_Push);
							}
					}
					else
					{
							Queue_Write((ps_Queue)(TxMessage), CAN_Tx_Object.pCAN_Tx_Queue);
					}

					return SUCCESS;
			}
			else
			{
					return ERROR;
			}
	}
	else
	{
			return ERROR;
	}
}

/**
	*@brief CAN总线初始化
	*@param	TxMessage[CanTxMsg *] Can数据
	*@retval [ErrorStatus]
	*@note none
	*/ 
void CanBus_Init(void)
{
	BSP_CAN_Init(CAN1, 50000);
	CAN_Rx_Objects_Init();
	CAN_Tx_Objects_Init();
}
/************************ Copyright (c) 2016, Dooya *****END OF FILE****/
