/******************************************
*Copyright (c) 2016, Dooya
*All rights reserved.
*
*@file loopServe.h
*@brief loop serve
*@version 0.1
*@data 2017/04/14
*@author xwb
******************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _BSP_GPIO_H_
#define _BSP_GPIO_H_

/* Includes ------------------------------------------------------------------*/
#include "config.h"
#include "type.h"
/* Public macro ------------------------------------------------------------*/
// Integers
/* Public types ------------------------------------------------------------*/


/* Public variables ---------------------------------------------------------*/

/* Public constants --------------------------------------------------------*/

#define UCONCAT(a, b)       a ## b
#define UEXPANDED(a, b)     UCONCAT(a, b)

#define U_ARG1(a, b) a
#define U_ARG2(a, b) b



#define PIN_RCC(Pin)    UEXPANDED(RCC_APB2Periph_GPIO , U_ARG1(Pin))
#define PIN_PORT(Pin)   UEXPANDED(GPIO , U_ARG1(Pin))
#define PIN_PIN(Pin)    UEXPANDED(GPIO_Pin_ , U_ARG2(Pin))
#define PIN_NO(Pin)     U_ARG2(Pin)

#define EXTI_Line(Pin)      UEXPANDED(EXTI_Line , U_ARG2(Pin))
#define GPIO_PinSource(Pin) UEXPANDED(GPIO_PinSource , U_ARG2(Pin))

#define PIN_STATE(Pin)  GPIO_ReadInputDataBit(UEXPANDED(GPIO , U_ARG1(Pin)), UEXPANDED(GPIO_Pin_ , U_ARG2(Pin)))




/* Public functions ------------------------------------------------------- */
void LED1_ON(void);
void LED1_OFF(void);
void LED1_Reversal(void);
void BSP_GPIO_Init(void);
#endif

/************************ Copyright (c) 2016, Dooya *****END OF FILE****/
