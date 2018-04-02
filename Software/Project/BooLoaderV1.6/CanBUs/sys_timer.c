/**
  ******************************************************************************
  * @file    sys_timer.c
  * @author  xwb
  * @version V1.0.0
  * @date    26/04/2015
  * @brief   This file is sys_timer file.
  ******************************************************************************
  */
#include "sys_timer.h"
#include "can_config.h"

extern INT16 ReBoot_OverTime;

/**
  * @brief  TIM4_Configuration 100us
  * @param  NONE
  * @retval NONE
  */
static void TIM4_Configuration(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	/* Time Base configuration */
	TIM_TimeBaseStructure.TIM_Prescaler = SystemCoreClock/2/1000000 - 1;//1M
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period = 100 - 1;//1ms
	//TIM_TimeBaseStructure.TIM_Period = 0xFFFF - 1;//1ms
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	//TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;

	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	/* 清除溢出中断标志 */
	TIM_ClearFlag(TIM4, TIM_FLAG_Update);							    
	/* TIM IT enable */
	TIM_ITConfig(TIM4, TIM_IT_CC1, ENABLE);
	/* TIM enable counter */
	TIM_Cmd(TIM4, ENABLE);
}
/**
  * @brief  NVIC_Configuration
  * @param  NONE
  * @retval NONE
  */
static void NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    /* Enable the TIM5 global Interrupt */
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
    NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 8;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}
/**
  * @brief  RCC_Configuration
  * @param  NONE
  * @retval NONE
  */
static void RCC_Configuration(void)
{
	/* TIM4 clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
}
/**
  * @brief  TIM4_start
  * @param  NONE
  * @retval NONE
  */
void TIM4_start(void)
{
	RCC_Configuration();

	/* configure TIM4 for remote and encoder */
	NVIC_Configuration();
	TIM4_Configuration();
}
/**
  * @brief  canInitTimer
  * @param  NONE
  * @retval NONE
  */
void sysTimerInit(void)
{
	TIM4_start();
}
/**
  * @brief  TIM4_IRQHandler 100us
  * @param  NONE
  * @retval NONE
  */
void TIM4_IRQHandler(void)
{

	static UNS32 secCount = 0, msCount = 0;

	secCount ++;
	msCount++;
	if (TIM_GetITStatus(TIM4, TIM_FLAG_CC1) != RESET)
	{
		TIM_ClearITPendingBit(TIM4,TIM_FLAG_CC1);
		if(msCount == 10)
		{
			secCount++;
			msCount = 0;
			ReBoot_OverTime--;
		}

		if(secCount == 1000)
		{
			
		}
	}
}

