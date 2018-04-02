//======================Copyright (c)=====================================
// �ļ�����: BSP_SysTick.C
// ��������:
//
// �޸ļ�¼:
//           2014-11-22, PiaoHong �����ļ�
//
//
//========================================================================
#include "BSP_SysTick.h"

//= Start ================================================================

// SystemFrequency/1000 ST3.0.0 ��汾
// ����Ϊ ST3.5.0 ��汾
#define TICK_1ms    (SystemCoreClock / 1000)
#define TICK_500us  (SystemCoreClock / 2000)
#define TICK_200us  (SystemCoreClock / 5000)
#define TICK_100us  (SystemCoreClock / 10000)
#define TICK_10us   (SystemCoreClock / 100000)
#define TICK_1us    (SystemCoreClock / 1000000)

#define TICK_SEL    TICK_1ms

volatile UNS32 SysTick_Count = 0;
extern volatile INT16 ReBoot_OverTime; //��ʱ������
//--------------------------------------------------------------
// ��������: SysTick_Handler
// ��������: ϵͳ�δ�ʱ���ж�
// �������: ��
// ���ز���: ��
// �޸ļ�¼:
//           2014-11-21, PiaoHong ��������
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
// ��������: BSP_SysTick_Init
// ��������: ����ϵͳ�δ�ʱ����ʱ
// �������: ��
// ���ز���: ��ʱ true
// �޸ļ�¼:
//           2014-11-21, PiaoHong ��������
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
// ��������: BSP_SysTick_Init
// ��������: ����ϵͳ�δ�ʱ����ʱ
// �������: ��
// ���ز���: ��ʱ true
// �޸ļ�¼:
//           2014-11-21, PiaoHong ��������
//---------------------------------------------------------------
void BSP_SysTick_OverTime_Reset(void)
{
    SysTick_Count = 0;
}

//--------------------------------------------------------------
// ��������: BSP_SysTick_Init
// ��������: ����ϵͳ�δ�ʱ��
// �������: ��
// ���ز���: ��
// �޸ļ�¼:
//           2014-11-21, PiaoHong ��������
//---------------------------------------------------------------
void BSP_SysTick_Init(void)
{
    if (SysTick_Config(TICK_SEL))
    {
        /* Capture error */
        while (1);
    }
    // ʹ�ܵδ�ʱ��
    SysTick->CTRL |=  SysTick_CTRL_ENABLE_Msk;
}

//= end   ================================================================


