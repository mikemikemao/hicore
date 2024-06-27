/*
 * CopyRight:	HangZhou Hikvision System Technology Co., Ltd. All	Right Reserved.
 * FileName:	HRP_Timer.h
 * Desc:		OS Layer Component.
 * Author:		schina
 * Date:		2009-03-02
 * Contact:		zhaoyiji@hikvision.com.cn
 * History:		Created By Zhaoyiji 2009-03-02
 * */

/*! 
	\file HPR_Timer.h
	\brief HPR Timer Manager.

	Details.
*/

#ifndef __HPR_TIMER_H__
#define __HPR_TIMER_H__

#include "HPR_Config.h"
#include "HPR_Types.h"

/*
��ʱ��������
��ʱ�����ö�ý��ʱ��+�첽ʱ�ӵ�ģʽ,��ý��ʱ������ϵͳ�������֧��16����
�����ý��ʱ�ӷ���ʧ�ܣ�������첽ʱ��

ʱ��ѡ��HPR_SetTimer() bFlag=HPR_FALSE��ʹ�ö�ý��ʱ��

��ʱ�����ȣ���ý��ʱ��1ms,�첽ʱ��1ms.

���ƣ���ʱ�����1500��
*/

typedef HPR_VOIDPTR (* HPR_CBF_Timer)(HPR_INT32 hEvent, HPR_VOIDPTR pUsrData);

/**
 * HPR_SetTimer create timer and set timer interval.
 * @param pCbf (IN) user defined function
 * @param pUsrData (IN) user defined data pass to pCbf 
 * @param nTimeOut (IN) timer interval in millisecond interval.
 * @param hEvent (OUT) timer event to create, may use in HPR_KillTimer.
 * @param bFlag (IN) special to use mmtimer. if false, not use mmtimer.
 * @return 0 success, -1 fail.
 * @sa HPR_KillTimer
 */
HPR_DECLARE HPR_INT32 CALLBACK HPR_SetTimer(HPR_CBF_Timer pCbf, HPR_VOIDPTR pUsrData,\
									HPR_UINT32 nTimeOut, HPR_INT32* hEvent, HPR_BOOL bFlag);

/**
 * HPR_KillTimer kill timer crated by HPR_SetTimer
 * @param hEvent (IN) timer event created by HPR_SetTimer
 * @return	0 success, -1 fail.
 * @sa HPR_SetTimer
 */
HPR_DECLARE HPR_INT32 CALLBACK HPR_KillTimer(HPR_INT32 hEvent); 

#endif
