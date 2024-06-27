/*
 * CopyRight:	HangZhou Hikvision System Technology Co., Ltd. All	Right Reserved.
 * FileName:	TimedWait.h
 * Desc:		OS Layer Component.
 * Author:		schina
 * Date:		2009-11-10
 * Contact:		zhaoyiji@hikvision.com.cn
 * History:		Created By Zhaoyiji 2009-11-10
 * */

#ifndef __TIMED_WAIT__
#define __TIMED_WIAT__

#include "HPR_Cond.h"
#include "HPR_Mutex.h"
#include "HPR_Semaphore.h"
#include "HPR_Thread.h"
#include "HPR_Utils.h"
#include "HPR_Time.h"

#if defined (OS_APPLE)

//��ʼ��Timedwait��Դ
HPR_INT32 HPR_InitTimeWait_Inter();

//����Timedwair��Դ
void HPR_FiniTimedWait_Inter();

//����ʱ�ȴ���������
HPR_INT32 CondTimedWait(HPR_COND_T* pCond, HPR_MUTEX_T* pMutex, HPR_UINT32 nTimeOut);

//����ʱ�ȴ��ź���
HPR_INT32 SemTimedWait(HPR_SEM_T* pSem, HPR_UINT32 nTimeOut);

#endif

#endif