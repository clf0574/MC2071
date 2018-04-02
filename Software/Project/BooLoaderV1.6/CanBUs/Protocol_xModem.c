//======================Copyright (c)=====================================
// �ļ�����: Protocol_xModem.C
// ��������:
//
// �޸ļ�¼:
//           2015-01-23, PiaoHong �����ļ�
//
//
//=======================================================================

#include "Protocol_xModem.h"
#include "BSP_Flash.h"
#include "BSP.h"
//= Start ================================================================
#define Sec *1000



typedef enum 
{
	UPDATE_WAIT = 0,
	UPDATE_START, 
	UPDATE_OK
}UpdateFlag;

volatile INT16 ReBoot_OverTime = 2 Sec; //��ʱ������
UpdateFlag g_updateFlag = UPDATE_WAIT; //

UNS8 MY_ADDR = 0x7f;
UNS8 Flash_PageBuf[FLASH_PAGE_SIZE];


UNS8 ProtocolxModem_RecData(CAN_PACKET * pCAN_Packet);


UNS8 Protocol_Can_Rec_Update(CanRxMsg *msg)
{
    UNS8 j;
    UNS32 tmp32 = 0;
		CAN_PACKET CAN_Packet_Rx;
    if (msg->IDE == CAN_ID_EXT)
    {
        if (msg->RTR== CAN_RTR_DATA)
        {
            tmp32 = msg->ExtId;

            CAN_Packet_Rx.Parameters = tmp32 & 0x7f;
            tmp32 >>= 7;
            CAN_Packet_Rx.Channel = tmp32 & 0x0f;
            tmp32 >>= 4;
            CAN_Packet_Rx.Daddr = tmp32 & 0x7f;
            tmp32 >>= 7;
            CAN_Packet_Rx.CMD = tmp32 & 0x0f;
            tmp32 >>= 4;
            CAN_Packet_Rx.Saddr = tmp32 & 0x7f;

            CAN_Packet_Rx.DatLen = msg->DLC;

            for (j = 0;j < CAN_Packet_Rx.DatLen;j++)
            {
                CAN_Packet_Rx.Data[j] = msg->Data[j];
            }
						ProtocolxModem_RecData(&CAN_Packet_Rx);
            return true;
        }
    }

    return false;
}



UNS8 Protocol_Can_SendData(CAN_PACKET * pCAN_Packet)
{
		UNS8 i;
    CanTxMsg msg;
		UNS32 ID_Field = 0;

    ID_Field <<= 7;
    ID_Field |= pCAN_Packet->Saddr;

    ID_Field <<= 4;
    ID_Field |= pCAN_Packet->CMD;

    ID_Field <<= 7;
    ID_Field |= pCAN_Packet->Daddr;

    ID_Field <<= 4;
    ID_Field |= pCAN_Packet->Channel;

    ID_Field <<= 7;
    ID_Field |= pCAN_Packet->Parameters;

    msg.ExtId= ID_Field;
    msg.IDE = CAN_ID_EXT;
    msg.RTR = CAN_RTR_DATA;
    msg.DLC = pCAN_Packet->DatLen;

    for(i=0;i<pCAN_Packet->DatLen;i++)
    {
        msg.Data[i] = pCAN_Packet->Data[i];
    }
		CAN_Tx_Object_Push(&msg);

    return false;
}


//--------------------------------------------------------------
// ��������: ProtocolxModem_RecData
// ��������: ���յ�����
// �������: ����ָ�룬���ݳ���
// ���ز���: �ɹ����� true
// �޸ļ�¼:
//           2009-11-19, PiaoHong ��������
//---------------------------------------------------------------
UNS8 ProtocolxModem_RecData(CAN_PACKET * pCAN_Packet)
{
		static UNS8 *p;
		static volatile UNS32 Flash_Addr = 0;
		static UNS8 Pack_Count = 0;
		static UNS16 checkSum = 0;
		static volatile UNS32 Flash_Addr_Last = 0;
    UNS16 i;
    UNS8 *s;
		uUNS32 Addr32;

    if (pCAN_Packet->CMD != 0x0c)
			return false;

    ReBoot_OverTime = 2 Sec;

    switch (pCAN_Packet->Channel)
    {
        case 0:     //��������
					MY_ADDR = pCAN_Packet->Daddr;
					Flash_Addr_Last = 0;
					g_updateFlag = UPDATE_START;
					break;

        case 1:     //ҳ��ʼ
					Addr32.byte.H = pCAN_Packet->Data[0];
					Addr32.byte.mH = pCAN_Packet->Data[1];
					Addr32.byte.mL = pCAN_Packet->Data[2];
					Addr32.byte.L = pCAN_Packet->Data[3];
					Flash_Addr = Addr32.Value;
					Pack_Count = 0;
					checkSum = 0;
					break;

        case 2:     //ҳ����
					p = (UNS8 *) & Flash_PageBuf;
					p += pCAN_Packet->Parameters * 8;

					s = pCAN_Packet->Data;

					for (i = 0;i < 8;i++)
					{
							checkSum += *s;
							*p++ = *s++;
					}

					Pack_Count++;
					return true;

        case 3:     //ҳ����
					if(Pack_Count == 0)
						return false;

					i = pCAN_Packet->Data[2]*0x100 + pCAN_Packet->Data[3];
					if((i == checkSum)&&(pCAN_Packet->Data[1] == Pack_Count))
					{   
						if((Flash_Addr > Flash_Addr_Last) && (Flash_Addr >= BSP_ADDR_App))
						{
							Flash_Addr_Last = Flash_Addr;
							BSP_Flash_WritePage(Flash_Addr_Last);   
						}								
						break;
					}
					//����
					pCAN_Packet->DatLen = 1;
					pCAN_Packet->Saddr = MY_ADDR;
					pCAN_Packet->Daddr = 0;
					pCAN_Packet->Data[0] = 0xee;
					Protocol_Can_SendData(pCAN_Packet);
					return false;
        case 4:     //�������
					ReBoot_OverTime = 100;
					g_updateFlag = UPDATE_OK;
					break;

        default:
					return false;
    }

    //Ӧ��
    pCAN_Packet->DatLen = 0;
    pCAN_Packet->Saddr = MY_ADDR;
    pCAN_Packet->Daddr = 0;
    Protocol_Can_SendData(pCAN_Packet);

    return true;
}

//--------------------------------------------------------------
// ��������: ProtocolxModem_Poll
// ��������: ��ʱ���
// �������: ��
// ���ز���: ��
// �޸ļ�¼:
//           2009-11-19, PiaoHong ��������
//---------------------------------------------------------------
void ProtocolxModem_Poll(void)
{
    if((ReBoot_OverTime < 0) && (g_updateFlag != UPDATE_START))
    {
			//��תAPP
      LED1_OFF();	
      BSP_ResetTo_App();
			ReBoot_OverTime = 2 Sec;
			__enable_irq();
    }
		if(g_updateFlag == UPDATE_START)
		{
			ReBoot_OverTime = 2 Sec;
		}
}
//--------------------------------------------------------------
// ��������: ProtocolxModem_Init
// ��������: Э���ʼ��
// �������: true �ָ���Ĭ������
// ���ز���: ��
// �޸ļ�¼:
//           2014-06-23, PiaoHong ��������
//---------------------------------------------------------------
void ProtocolxModem_Init(UNS8 Data_Init)
{

}



//= end   ================================================================



