//======================Copyright (c)=====================================
// �ļ�����: BSP_Flash.c
// ��������:
//
// �޸ļ�¼:
//           2015-01-23, PiaoHong �����ļ�
//
//
//========================================================================
#include "BSP_flash.h"
#include "Protocol_xModem.h"
//= Start ================================================================

extern UNS8 Flash_PageBuf[];


//--------------------------------------------------------------
// ��������: BSP_Flash_ClearPage
// ��������: FLASH ҳ����
// �������: ��ַ
// ���ز���: FLASH_Status
// �޸ļ�¼:
//           2015-01-23, PiaoHong ��������
//---------------------------------------------------------------
FLASH_Status BSP_Flash_ClearPage(UNS32 Page_Address)
{
	FLASH_Status FLASHStatus = FLASH_COMPLETE;
	FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);
	FLASHStatus = FLASH_ErasePage(Page_Address);
	return FLASHStatus;
}

//--------------------------------------------------------------
// ��������: BSP_Flash_ReadPage
// ��������: FLASH ҳ��
// �������: ��ַ
// ���ز���: ��
// �޸ļ�¼:
//           2015-01-23, PiaoHong ��������
//---------------------------------------------------------------
void BSP_Flash_ReadPage(UNS32 aAdd)
{
    UNS32 tPageWordCnt = FLASH_PAGE_SIZE/4;
    UNS32 * tPoint=(UNS32 *)Flash_PageBuf;
    UNS32 tPageNo = aAdd/FLASH_PAGE_SIZE; //ȡ��ҳ��
    UNS32 tPageNoBaseAdd = tPageNo*FLASH_PAGE_SIZE;
    while(tPageWordCnt--)  //256-1
    {
        *(tPoint+tPageWordCnt) = (*(__IO uint32_t*) (tPageNoBaseAdd+(0*FLASH_PAGE_SIZE)+tPageWordCnt*4));   //255-0
    }
}

//--------------------------------------------------------------
// ��������: Flash_WritePage
// ��������: FLASH ҳд
// �������: ��ַ
// ���ز���: ��
// �޸ļ�¼:
//           2015-01-23, PiaoHong ��������
//---------------------------------------------------------------
void Flash_WritePage(UNS32 aAdd)
{
    UNS32 tPageWordCnt = FLASH_PAGE_SIZE/4;
    UNS32 * tPoint=(UNS32 *)Flash_PageBuf;

    UNS32 tPageNo = aAdd/FLASH_PAGE_SIZE; //ȡ��ҳ��
    UNS32 tPageNoBaseAdd = tPageNo*FLASH_PAGE_SIZE;

    while(tPageWordCnt--)   //256---1
    {
        FLASH_ProgramWord((tPageNoBaseAdd+(0*FLASH_PAGE_SIZE)+tPageWordCnt*4),*(tPoint+tPageWordCnt));  //255-0
    }
}

//--------------------------------------------------------------
// ��������: BSP_Flash_WritePage
// ��������: FLASH ҳд
// �������: ��ַ
// ���ز���: ��
// �޸ļ�¼:
//           2015-01-23, PiaoHong ��������
//---------------------------------------------------------------
void BSP_Flash_WritePage(UNS32 aAdd)
{
    FLASH_Unlock(); 		//����Falsh
    BSP_Flash_ClearPage(aAdd);
    Flash_WritePage(aAdd);
    FLASH_Lock(); 		    //��������Falsh
}


//--------------------------------------------------------------
// ��������: BSP_Flash_WriteWordFormBuf
// ��������: ͨ��ҳ����дFLASHһ�ֺ���
// �������: ��
// ���ز���: ��
// �޸ļ�¼:
//           2015-01-23, PiaoHong ��������
//---------------------------------------------------------------
void BSP_Flash_WriteWordFormBuf(UNS32 aData,UNS32 aAdd)
{
    UNS32 * tPoint = (UNS32*)Flash_PageBuf;

    UNS32 tByteIndex = aAdd%FLASH_PAGE_SIZE; //ȡ��ҳ��

    tByteIndex = tByteIndex/4;

    BSP_Flash_ReadPage(aAdd);
    *(tPoint+tByteIndex) = aData;
    FLASH_Unlock(); 		//��������Falsh
    BSP_Flash_ClearPage(aAdd);
    Flash_WritePage(aAdd);
    FLASH_Lock(); 		//��������Falsh
}


//= end   ================================================================



