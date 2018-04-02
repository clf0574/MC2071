/*
This file is part of CanFestival, a library implementing CanOpen Stack.

Copyright (C): Edouard TISSERANT and Francis DUPIN
AT91 Port: Peter CHRISTEN

See COPYING file for copyrights details.

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#ifndef _BSP_CAN_H_
#define _BSP_CAN_H_

#include "config.h"

/*_CAN1*/
#define CAN1_CLK                    RCC_APB1Periph_CAN1
#define CAN1_RX_PIN                 GPIO_Pin_11
#define CAN1_TX_PIN                 GPIO_Pin_12
#define CAN1_GPIO_PORT              GPIOA
#define CAN1_GPIO_CLK               RCC_APB2Periph_GPIOA
#define CAN1_AF_PORT                GPIO_AF_CAN1
#define CAN1_RX_SOURCE              GPIO_PinSource0
#define CAN1_TX_SOURCE              GPIO_PinSource1       

#define BSP_CAN_Send_Msg(CANx,m) CAN_Transmit(CANx, m)

typedef void* CAN_PORT;

void BSP_CAN_Init(CAN_PORT CANx, UNS32 bitrate);
void CAN_NVIC_Config(FunctionalState NewState);
FlagStatus CAN_TX_FIFO_Is_Empty(CAN_TypeDef* CANx);
#endif /* _CNA_CONFIG_H_ */

