//======================Copyright (c)=====================================
// �ļ�����: Protocol_xModem.H
// ��������:
//
// �޸ļ�¼:
//           2015-01-23, PiaoHong �����ļ�
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
// ��������: ProtocolxModem_Poll
// ��������: ��ѯ ��ʱ����
// �������: ��
// ���ز���: ��
// �޸ļ�¼:
//           2009-11-19, PiaoHong ��������
//---------------------------------------------------------------
extern void ProtocolxModem_Poll(void);

//--------------------------------------------------------------
// ��������: ProtocolxModem_RecData
// ��������: ���յ�����
// �������: ����ָ�룬���ݳ���
// ���ز���: �ɹ����� true
// �޸ļ�¼:
//           2009-11-19, PiaoHong ��������
//---------------------------------------------------------------
extern UNS8 ProtocolxModem_RecData(CAN_PACKET * pCAN_Packet);

//--------------------------------------------------------------
// ��������: ProtocolxModem_Init
// ��������: Э���ʼ��
// �������: true �ָ���Ĭ������
// ���ز���: ��
// �޸ļ�¼:
//           2014-06-23, PiaoHong ��������
//---------------------------------------------------------------
extern void ProtocolxModem_Init(UNS8 Data_Init);

//= end   ================================================================
#undef extern

#endif //_PROTOCOL_XMODEM_H


