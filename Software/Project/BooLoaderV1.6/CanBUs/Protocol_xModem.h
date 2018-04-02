//======================Copyright (c)=====================================
// 文件名称: Protocol_xModem.H
// 功能描述:
//
// 修改记录:
//           2015-01-23, PiaoHong 创建文件
//
//
//========================================================================

#ifndef _PROTOCOL_XMODEM_H
#define _PROTOCOL_XMODEM_H
//= Start ================================================================
#include "config.h"
#include "type.h"
#include "CanBus.h"

#define FLASH_PAGE_SIZE 1024

typedef struct
{
    UNS8   Saddr;      // 7bit 1-126
    UNS8   CMD;        // 4bit 1-16

    UNS8   Daddr;      // 7bit 1-126 127???

    UNS8   Channel;    // 4bit 0-15
    UNS8   Parameters; // 7bit 0-127

    UNS8   DatLen;     // 4bit 0-8
    UNS8   Data[8];
}CAN_PACKET;

UNS8 Protocol_Can_Rec_Update(CanRxMsg *msg);
//--------------------------------------------------------------
// 函数名称: ProtocolxModem_Poll
// 功能描述: 轮询 定时调用
// 输入参数: 无
// 返回参数: 无
// 修改记录:
//           2009-11-19, PiaoHong 创建函数
//---------------------------------------------------------------
extern void ProtocolxModem_Poll(void);

//--------------------------------------------------------------
// 函数名称: ProtocolxModem_RecData
// 功能描述: 接收到数据
// 输入参数: 数据指针，数据长度
// 返回参数: 成功解析 true
// 修改记录:
//           2009-11-19, PiaoHong 创建函数
//---------------------------------------------------------------
extern UNS8 ProtocolxModem_RecData(CAN_PACKET * pCAN_Packet);

//--------------------------------------------------------------
// 函数名称: ProtocolxModem_Init
// 功能描述: 协议初始化
// 输入参数: true 恢复成默认数据
// 返回参数: 无
// 修改记录:
//           2014-06-23, PiaoHong 创建函数
//---------------------------------------------------------------
extern void ProtocolxModem_Init(UNS8 Data_Init);

//= end   ================================================================
#undef extern

#endif //_PROTOCOL_XMODEM_H


