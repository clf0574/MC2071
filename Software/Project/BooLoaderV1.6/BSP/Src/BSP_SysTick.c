//======================Copyright (c)=====================================
// 文件名称: BSP_SysTick.C
// 功能描述:
//
// 修改记录:
//           2014-11-22, PiaoHong 创建文件
//
//
//========================================================================
#include "BSP_SysTick.h"

//= Start ================================================================

// SystemFrequency/1000 ST3.0.0 库版本
// 以下为 ST3.5.0 库版本
#define TICK_1ms    (SystemCoreClock / 1000)
#define TICK_500us  (SystemCoreClock / 2000)
#define TICK_200us  (SystemCoreClock / 5000)
#define TICK_100us  (SystemCoreClock / 10000)
#define TICK_10us   (SystemCoreClock / 100000)
#define TICK_1us    (SystemCoreClock / 1000000)

#define TICK_SEL    TICK_1ms

volatile UNS32 SysTick_Count = 0;
extern volatile INT16 ReBoot_OverTime; //超时，重启
//--------------------------------------------------------------
// 函数名称: SysTick_Handler
// 功能描述: 系统滴答定时器中断
// 输入参数: 无
// 返回参数: 无
// 修改记录:
//           2014-11-21, PiaoHong 创建函数
//---------------------------------------------------------------
void SysTick_Handler(void)
{
    if(++SysTick_Count >= SYSTICK_OVER)
    {
        SysTick_Count = 0;
    }
		ReBoot_OverTime--;
}

//--------------------------------------------------------------
// 函数名称: BSP_SysTick_Init
// 功能描述: 启动系统滴答定时器超时
// 输入参数: 无
// 返回参数: 超时 true
// 修改记录:
//           2014-11-21, PiaoHong 创建函数
//---------------------------------------------------------------
UNS8 BSP_SysTick_OverTime(UNS16 ms)
{
    if(SysTick_Count >= ms)
    {
        return true;
    }
    return false;
}

//--------------------------------------------------------------
// 函数名称: BSP_SysTick_Init
// 功能描述: 启动系统滴答定时器超时
// 输入参数: 无
// 返回参数: 超时 true
// 修改记录:
//           2014-11-21, PiaoHong 创建函数
//---------------------------------------------------------------
void BSP_SysTick_OverTime_Reset(void)
{
    SysTick_Count = 0;
}

//--------------------------------------------------------------
// 函数名称: BSP_SysTick_Init
// 功能描述: 启动系统滴答定时器
// 输入参数: 无
// 返回参数: 无
// 修改记录:
//           2014-11-21, PiaoHong 创建函数
//---------------------------------------------------------------
void BSP_SysTick_Init(void)
{
    if (SysTick_Config(TICK_SEL))
    {
        /* Capture error */
        while (1);
    }
    // 使能滴答定时器
    SysTick->CTRL |=  SysTick_CTRL_ENABLE_Msk;
}

//= end   ================================================================


