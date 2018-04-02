/**
  ******************************************************************************
  * @file    can_stm32.c
  * @author  Zhenglin R&D Driver Software Team
  * @version V1.0.0
  * @date    26/04/2015
  * @brief   This file is can_stm32 file.
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "BSP_can.h"
#include "stm32f10x_can.h"
#include "BSP_gpio.h"
#include "Lib_BlockDelay.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/**
  * @brief  canInit
  * @param  CANx:CAN1 or CAN2 bitrate
  * @retval 0£ºSuccess
  */
void BSP_CAN_Init(CAN_PORT CANx, UNS32 bitrate)
{
	CAN_InitTypeDef        CAN_InitStructure;
	CAN_FilterInitTypeDef  CAN_FilterInitStructure;
	GPIO_InitTypeDef  GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	/* Enable GPIO clock */
	RCC_APB2PeriphClockCmd(CAN1_GPIO_CLK, ENABLE);

	/* Configure CAN1 RX pin */
	GPIO_InitStructure.GPIO_Pin = CAN1_RX_PIN ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(CAN1_GPIO_PORT, &GPIO_InitStructure);
	
	
	/* Configure CAN1 TX pin */
	GPIO_InitStructure.GPIO_Pin = CAN1_TX_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(CAN1_GPIO_PORT, &GPIO_InitStructure);
	/* CAN configuration ********************************************************/  
	/* Enable CAN clock */
	RCC_APB1PeriphClockCmd(CAN1_CLK, ENABLE);

	/* CAN register init */
	CAN_DeInit(CANx);
	CAN_DBGFreeze(CAN1, DISABLE);
	CAN_StructInit(&CAN_InitStructure);
	/* CAN cell init */
	CAN_InitStructure.CAN_TTCM = DISABLE;    
	CAN_InitStructure.CAN_ABOM = ENABLE;   
	CAN_InitStructure.CAN_AWUM = DISABLE;		
	CAN_InitStructure.CAN_NART = DISABLE;	
	CAN_InitStructure.CAN_RFLM = DISABLE;	
	CAN_InitStructure.CAN_TXFP = ENABLE;		
	CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;	
	
	if(bitrate == 50000)
	{
		CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;
		CAN_InitStructure.CAN_BS1 = CAN_BS1_13tq;
		CAN_InitStructure.CAN_BS2 = CAN_BS2_2tq;
		CAN_InitStructure.CAN_Prescaler = 45;
	}
	else
	{
		/*Ä¬ÈÏ50K*/
		CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;
		CAN_InitStructure.CAN_BS1 = CAN_BS1_13tq;
		CAN_InitStructure.CAN_BS2 = CAN_BS2_2tq;
		CAN_InitStructure.CAN_Prescaler = 45;
	}
		 

	
	CAN_Init(CANx, &CAN_InitStructure);

	CAN_FilterInitStructure.CAN_FilterNumber = 0;	 
	CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;   
	CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
	CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;
	CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;
	CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0;    
	CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;           
	CAN_FilterInit(&CAN_FilterInitStructure);

	/* Enable FIFO 0 message pending Interrupt */
	CAN_ITConfig(CANx, (CAN_IT_TME| CAN_IT_FMP0 | CAN_IT_FF0 | CAN_IT_FOV0), ENABLE);              

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 6;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	NVIC_InitStructure.NVIC_IRQChannel = USB_HP_CAN1_TX_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 6;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void CAN_NVIC_Config(FunctionalState NewState)
{
	NVIC_InitTypeDef NVIC_InitStruct;

	/* Enable CAN intterupt in the NVIC */
	NVIC_InitStruct.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 6;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelCmd = NewState;
	NVIC_Init(&NVIC_InitStruct);
}

FlagStatus CAN_TX_FIFO_Is_Empty(CAN_TypeDef* CANx)
{
	uint32_t Status = 0;

	Status = CANx ->TSR & CAN_TSR_TME;

	if(Status == CAN_TSR_TME)
		return SET;
	else
		return RESET;
}
/******************* (C) COPYRIGHT 2015 Personal Electronics *****END OF FILE****/


