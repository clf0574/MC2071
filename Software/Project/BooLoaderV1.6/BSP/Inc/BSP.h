//======================Copyright (c)=====================================
// 文件名称: BSP.H
// 功能描述:
//
// 修改记录:
//           2014-11-22, PiaoHong 创建文件
//
//
//========================================================================

#ifndef _BSP_H
#define _BSP_H

//= Start ================================================================


#include "config.h"
#include "type.h"
#include "BSP_SysTick.h"


#define BSP_Interrupt_Disable() __disable_irq() //关闭总中断
#define BSP_Interrupt_Enable()  __enable_irq()  //开启总中断

//--------------------------------------------------------------
// 函数名称: JumpToApplication
// 功能描述: 控制程序跳转到指定位置开始执行
// 输入参数: 程序执行地址
// 返回参数: 程序跳转状态
// 修改记录:
//           2015-01-24, PiaoHong 创建函数
//---------------------------------------------------------------
extern UNS8 JumpToApplication(UNS32 Addr);



#define BSP_ADDR_Boot       0x08000000UL
#define BSP_ADDR_App        0x08004000UL

#define BSP_ResetTo_App()   JumpToApplication(BSP_ADDR_App)     //(*((void(*)(void))(BSP_ADDR_App)))()
#define BSP_ResetTo_Boot()  JumpToApplication(BSP_ADDR_Boot)    //(*((void(*)(void))(BSP_ADDR_Boot)))()

//--------------------------------------------------------------
// 函数名称: BSP_Init
// 功能描述: BSP初始化
// 输入参数: 无
// 返回参数: 无
// 修改记录:
//           2014-11-22, PiaoHong 创建函数
//---------------------------------------------------------------
extern void BSP_Init(void);


//--------------------------------------------------------------
// 函数名称: BSP_WatchDog_Reset
// 功能描述: 清看门狗
// 输入参数: 无
// 返回参数: 无
// 修改记录:
//           2014-12-01, PiaoHong 创建函数
//---------------------------------------------------------------
extern void BSP_WatchDog_Reset(void);

//= end   ================================================================


#endif //_BSP_H


