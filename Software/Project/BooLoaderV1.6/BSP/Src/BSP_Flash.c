//======================Copyright (c)=====================================
// 文件名称: BSP_Flash.c
// 功能描述:
//
// 修改记录:
//           2015-01-23, PiaoHong 创建文件
//
//
//========================================================================
#include "BSP_flash.h"
#include "Protocol_xModem.h"
//= Start ================================================================

extern UNS8 Flash_PageBuf[];


//--------------------------------------------------------------
// 函数名称: BSP_Flash_ClearPage
// 功能描述: FLASH 页擦除
// 输入参数: 地址
// 返回参数: FLASH_Status
// 修改记录:
//           2015-01-23, PiaoHong 创建函数
//---------------------------------------------------------------
FLASH_Status BSP_Flash_ClearPage(UNS32 Page_Address)
{
	FLASH_Status FLASHStatus = FLASH_COMPLETE;
	FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);
	FLASHStatus = FLASH_ErasePage(Page_Address);
	return FLASHStatus;
}

//--------------------------------------------------------------
// 函数名称: BSP_Flash_ReadPage
// 功能描述: FLASH 页读
// 输入参数: 地址
// 返回参数: 无
// 修改记录:
//           2015-01-23, PiaoHong 创建函数
//---------------------------------------------------------------
void BSP_Flash_ReadPage(UNS32 aAdd)
{
    UNS32 tPageWordCnt = FLASH_PAGE_SIZE/4;
    UNS32 * tPoint=(UNS32 *)Flash_PageBuf;
    UNS32 tPageNo = aAdd/FLASH_PAGE_SIZE; //取的页号
    UNS32 tPageNoBaseAdd = tPageNo*FLASH_PAGE_SIZE;
    while(tPageWordCnt--)  //256-1
    {
        *(tPoint+tPageWordCnt) = (*(__IO uint32_t*) (tPageNoBaseAdd+(0*FLASH_PAGE_SIZE)+tPageWordCnt*4));   //255-0
    }
}

//--------------------------------------------------------------
// 函数名称: Flash_WritePage
// 功能描述: FLASH 页写
// 输入参数: 地址
// 返回参数: 无
// 修改记录:
//           2015-01-23, PiaoHong 创建函数
//---------------------------------------------------------------
void Flash_WritePage(UNS32 aAdd)
{
    UNS32 tPageWordCnt = FLASH_PAGE_SIZE/4;
    UNS32 * tPoint=(UNS32 *)Flash_PageBuf;

    UNS32 tPageNo = aAdd/FLASH_PAGE_SIZE; //取的页号
    UNS32 tPageNoBaseAdd = tPageNo*FLASH_PAGE_SIZE;

    while(tPageWordCnt--)   //256---1
    {
        FLASH_ProgramWord((tPageNoBaseAdd+(0*FLASH_PAGE_SIZE)+tPageWordCnt*4),*(tPoint+tPageWordCnt));  //255-0
    }
}

//--------------------------------------------------------------
// 函数名称: BSP_Flash_WritePage
// 功能描述: FLASH 页写
// 输入参数: 地址
// 返回参数: 无
// 修改记录:
//           2015-01-23, PiaoHong 创建函数
//---------------------------------------------------------------
void BSP_Flash_WritePage(UNS32 aAdd)
{
    FLASH_Unlock(); 		//解锁Falsh
    BSP_Flash_ClearPage(aAdd);
    Flash_WritePage(aAdd);
    FLASH_Lock(); 		    //重新锁定Falsh
}


//--------------------------------------------------------------
// 函数名称: BSP_Flash_WriteWordFormBuf
// 功能描述: 通过页缓存写FLASH一字函数
// 输入参数: 无
// 返回参数: 无
// 修改记录:
//           2015-01-23, PiaoHong 创建函数
//---------------------------------------------------------------
void BSP_Flash_WriteWordFormBuf(UNS32 aData,UNS32 aAdd)
{
    UNS32 * tPoint = (UNS32*)Flash_PageBuf;

    UNS32 tByteIndex = aAdd%FLASH_PAGE_SIZE; //取的页号

    tByteIndex = tByteIndex/4;

    BSP_Flash_ReadPage(aAdd);
    *(tPoint+tByteIndex) = aData;
    FLASH_Unlock(); 		//重新锁定Falsh
    BSP_Flash_ClearPage(aAdd);
    Flash_WritePage(aAdd);
    FLASH_Lock(); 		//重新锁定Falsh
}


//= end   ================================================================



