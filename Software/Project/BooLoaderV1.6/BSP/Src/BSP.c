//======================Copyright (c)=====================================
// �ļ�����: BSP.C
// ��������:
//
// �޸ļ�¼:
//           2014-11-22, PiaoHong �����ļ�
//
//
//========================================================================
#include "BSP.H"

//= Start ================================================================

typedef  void (*pFunction)(void);

//--------------------------------------------------------------
// ��������: JumpToApplication
// ��������: ���Ƴ�����ת��ָ��λ�ÿ�ʼִ��
// �������: ����ִ�е�ַ
// ���ز���: ������ת״̬
// �޸ļ�¼:
//           2015-01-24, PiaoHong ��������
//---------------------------------------------------------------
UNS8 JumpToApplication(UNS32 Addr)
{
	pFunction Jump_To_Application;

	__IO uint32_t JumpAddress;
	/* Test if user code is programmed starting from address "ApplicationAddress" */

      //ȡ���û�������ַ�ڵ����ݣ�����������û�����Ķ�ջ��ַ����ջ��ַ��ָ��RAM�ģ�
      //�������������û������ջ�Ƿ�����RAM��
	if (((*(__IO uint32_t*)Addr) & 0x2FFE0000 ) == 0x20000000)
	{
	  /* Jump to user application */
        //ȡ���û�����ڶ������ڵ����ݣ�����������û�����ĸ�λ��ַ��
	  JumpAddress = *(__IO uint32_t*) (Addr + 4);                     //��λַ��
	  Jump_To_Application = (pFunction) JumpAddress;                  //�ѵڶ�����ת���ɺ���

	  /* Initialize user application's Stack Pointer */

	  __set_MSP(*(__IO uint32_t*) Addr);                               //���û������ջ��ַַ��Ϊջ��ָ��

	  #ifdef USE_USB_PORT
	  USB_Cable_Config(DISABLE);
	  #endif
	  Jump_To_Application();                                            //�����û�����
	}
//	TimeOutFlag=0xFF;
	return 1;
}

//--------------------------------------------------------------
// ��������: BSP_WatchDog_Init
// ��������: ���Ź���ʼ��
// �������: ��
// ���ز���: ��
// �޸ļ�¼:
//           2014-12-01, PiaoHong ��������
//---------------------------------------------------------------
void BSP_WatchDog_Init(void)
{
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);//�ر�IWDG_PR��IWDG_RLR��д����
	IWDG_SetReload(0xfff);					//������װ��ֵΪ0xfff
	IWDG_SetPrescaler(IWDG_Prescaler_32);	//����Ԥ��Ƶϵ��Ϊ32
	IWDG_Enable();							//ʹ�ܿ��Ź�
}

//--------------------------------------------------------------
// ��������: BSP_WatchDog_Reset
// ��������: �忴�Ź�
// �������: ��
// ���ز���: ��
// �޸ļ�¼:
//           2014-12-01, PiaoHong ��������
//---------------------------------------------------------------
void BSP_WatchDog_Reset(void)
{
	IWDG_ReloadCounter();		//ι��
}


//--------------------------------------------------------------
// ��������: BSP_Init
// ��������: BSP��ʼ��
// �������: ��
// ���ز���: ��
// �޸ļ�¼:
//           2014-11-22, PiaoHong ��������
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



