/******************************************
*Copyright (c) 2016, Dooya
*All rights reserved.
*
*@file BSP_gpio.c
*@brief ??????
*@version 0.1
*@data 2016/12/3
*@author xwb
******************************************/

/* Includes ------------------------------------------------------------------*/
#include "BSP_gpio.h"
/* Private macro -------------------------------------------------------------*/ 
#define PIN_JTDI							A,  15
#define PIN_LED1							C,  15
#define PIN_OUT1							A,  1
#define PIN_OUT2							A,  2
#define PIN_OUT3							A,  3
#define PIN_OUT4							A,  0
/* Private types ------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Public variables ---------------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/ 
/* Public functions ---------------------------------------------------------*/  

void LED1_ON(void)
{ 
	GPIO_SetBits(PIN_PORT(PIN_LED1), PIN_PIN(PIN_LED1));
}

void LED1_OFF(void)
{
	GPIO_ResetBits(PIN_PORT(PIN_LED1), PIN_PIN(PIN_LED1));  
}
void LED1_Reversal(void)
{	
	GPIO_WriteBit(PIN_PORT(PIN_LED1), PIN_PIN(PIN_LED1), (GPIO_ReadOutputDataBit(PIN_PORT(PIN_LED1), PIN_PIN(PIN_LED1))? Bit_RESET:Bit_SET));
}

void OUT1_ON(void)
{ 
	GPIO_ResetBits(PIN_PORT(PIN_OUT1), PIN_PIN(PIN_OUT1));
}

void OUT1_OFF(void)
{
	GPIO_SetBits(PIN_PORT(PIN_OUT1), PIN_PIN(PIN_OUT1));  
}
void OUT2_ON(void)
{ 
	GPIO_ResetBits(PIN_PORT(PIN_OUT2), PIN_PIN(PIN_OUT2));
}

void OUT2_OFF(void)
{
	GPIO_SetBits(PIN_PORT(PIN_OUT2), PIN_PIN(PIN_OUT2));  
}

void OUT3_ON(void)
{ 
	GPIO_ResetBits(PIN_PORT(PIN_OUT3), PIN_PIN(PIN_OUT3));
}

void OUT3_OFF(void)
{
	GPIO_SetBits(PIN_PORT(PIN_OUT3), PIN_PIN(PIN_OUT3));  
}
void OUT4_ON(void)
{ 
	GPIO_ResetBits(PIN_PORT(PIN_OUT4), PIN_PIN(PIN_OUT4));
}

void OUT4_OFF(void)
{
	GPIO_SetBits(PIN_PORT(PIN_OUT4), PIN_PIN(PIN_OUT4));  
}

/**
	*@brief io初始化
	*@param	none
	*@retval none
	*@note none
	*/
void BSP_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	DBGMCU->CR = DBGMCU->CR & ~((uint32_t)1<<5);	        //关闭TRACESWO信号跟踪
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE); //禁用JTAG，启用SW-DP
	 
	RCC_APB2PeriphClockCmd(PIN_RCC(PIN_JTDI), ENABLE);
	
	GPIO_ResetBits(PIN_PORT(PIN_JTDI), PIN_PIN(PIN_JTDI));
  GPIO_InitStructure.GPIO_Pin = PIN_PIN(PIN_JTDI);
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(PIN_PORT(PIN_JTDI), &GPIO_InitStructure);
	
//	OUT1_OFF();
//	OUT2_OFF();
//	OUT3_OFF();
//	OUT4_OFF();
//	RCC_APB2PeriphClockCmd(PIN_RCC(PIN_LED1)|RCC_APB2Periph_AFIO, ENABLE);
//  GPIO_InitStructure.GPIO_Pin = PIN_PIN(PIN_LED1);
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//	GPIO_Init(PIN_PORT(PIN_LED1), &GPIO_InitStructure);
//	
//	RCC_APB2PeriphClockCmd(PIN_RCC(PIN_OUT1)|RCC_APB2Periph_AFIO, ENABLE);
//  GPIO_InitStructure.GPIO_Pin = PIN_PIN(PIN_OUT1);
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//	GPIO_Init(PIN_PORT(PIN_OUT1), &GPIO_InitStructure);
//	
//	RCC_APB2PeriphClockCmd(PIN_RCC(PIN_OUT2)|RCC_APB2Periph_AFIO, ENABLE);
//  GPIO_InitStructure.GPIO_Pin = PIN_PIN(PIN_OUT2);
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//	GPIO_Init(PIN_PORT(PIN_OUT2), &GPIO_InitStructure);
//	
//	RCC_APB2PeriphClockCmd(PIN_RCC(PIN_OUT3)|RCC_APB2Periph_AFIO, ENABLE);
//  GPIO_InitStructure.GPIO_Pin = PIN_PIN(PIN_OUT3);
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//	GPIO_Init(PIN_PORT(PIN_OUT3), &GPIO_InitStructure);
//	
//	RCC_APB2PeriphClockCmd(PIN_RCC(PIN_OUT4)|RCC_APB2Periph_AFIO, ENABLE);
//  GPIO_InitStructure.GPIO_Pin = PIN_PIN(PIN_OUT4);
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//	GPIO_Init(PIN_PORT(PIN_OUT4), &GPIO_InitStructure);
}
                             


                             


/************************ Copyright (c) 2016, Dooya *****END OF FILE****/

