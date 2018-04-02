//======================Copyright (c)=====================================
// 文件名称: BSP.C
// 功能描述:
//
// 修改记录:
//           2014-11-22, PiaoHong 创建文件
//
//
//========================================================================
#include "BSP.H"

//= Start ================================================================

typedef  void (*pFunction)(void);

//--------------------------------------------------------------
// 函数名称: JumpToApplication
// 功能描述: 控制程序跳转到指定位置开始执行
// 输入参数: 程序执行地址
// 返回参数: 程序跳转状态
// 修改记录:
//           2015-01-24, PiaoHong 创建函数
//---------------------------------------------------------------
UNS8 JumpToApplication(UNS32 Addr)
{
	pFunction Jump_To_Application;

	__IO uint32_t JumpAddress;
	/* Test if user code is programmed starting from address "ApplicationAddress" */

      //取出用户程序首址内的数据，这个数据是用户程序的堆栈地址，堆栈地址是指向RAM的，
      //所以下面是判用户程序堆栈是否落在RAM。
	if (((*(__IO uint32_t*)Addr) & 0x2FFE0000 ) == 0x20000000)
	{
	  /* Jump to user application */
        //取出用户程序第二个字内的数据，这个数据是用户程序的复位地址。
	  JumpAddress = *(__IO uint32_t*) (Addr + 4);                     //复位址地
	  Jump_To_Application = (pFunction) JumpAddress;                  //把第二个字转换成函数

	  /* Initialize user application's Stack Pointer */

	  __set_MSP(*(__IO uint32_t*) Addr);                               //把用户程序的栈顶址址设为栈顶指针

	  #ifdef USE_USB_PORT
	  USB_Cable_Config(DISABLE);
	  #endif
	  Jump_To_Application();                                            //跳到用户程序
	}
//	TimeOutFlag=0xFF;
	return 1;
}

//--------------------------------------------------------------
// 函数名称: BSP_WatchDog_Init
// 功能描述: 看门狗初始化
// 输入参数: 无
// 返回参数: 无
// 修改记录:
//           2014-12-01, PiaoHong 创建函数
//---------------------------------------------------------------
void BSP_WatchDog_Init(void)
{
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);//关闭IWDG_PR和IWDG_RLR的写保护
	IWDG_SetReload(0xfff);					//设置重装载值为0xfff
	IWDG_SetPrescaler(IWDG_Prescaler_32);	//设置预分频系数为32
	IWDG_Enable();							//使能看门狗
}

//--------------------------------------------------------------
// 函数名称: BSP_WatchDog_Reset
// 功能描述: 清看门狗
// 输入参数: 无
// 返回参数: 无
// 修改记录:
//           2014-12-01, PiaoHong 创建函数
//---------------------------------------------------------------
void BSP_WatchDog_Reset(void)
{
	IWDG_ReloadCounter();		//喂狗
}


//--------------------------------------------------------------
// 函数名称: BSP_Init
// 功能描述: BSP初始化
// 输入参数: 无
// 返回参数: 无
// 修改记录:
//           2014-11-22, PiaoHong 创建函数
//---------------------------------------------------------------
void BSP_Init(void)
{
	BSP_Interrupt_Disable();

	NVIC_SetVectorTable(NVIC_VectTab_FLASH, BSP_ADDR_Boot);

	BSP_GPIO_Init();

	BSP_SysTick_Init();
	BSP_WatchDog_Init();

	BSP_Interrupt_Enable();
}

//= end   ================================================================



