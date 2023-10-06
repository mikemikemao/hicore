/*
* CopyRight:	HangZhou Hikvision System Technology Co., Ltd. All	Right Reserved.
* FileName:		HRP_ThreadPoolFlex.h
* Desc:			OS Layer Component.
* Author:		zhaoyiji
* Date:			2009-03-30
* Contact:		zhaoyiji@hikvision.com.cn
* History:		Created By zhaoyiji 2011-03-12
* */

/*! 
\file HPR_ThreadPool.h
\brief HPR ThreadPool Manager.

Details.
*/

#ifndef __HPR_THREADPOOLFLEX_H__	
#define __HPR_THREADPOOLFLEX_H__

#include "HPR_Config.h"
#include "HPR_Types.h"


/**
* HPR_ThreadPool_Create
* @param MaxThreadNum (IN) �̳߳�����߳���.
* @param nIdleTime (IN) �߳̿����˳�ʱ�䣬�Ժ���ƣ���������ʱ��û�������߳��Զ��˳�.
* @param fWorkRoutine the thread work routine.
* @param nStackSize (IN) �̶߳�ջ��С�����ֽڼƣ�0ΪĬ�ϴ�С.
* @return NULL fail, else success.
* @sa HPR_ThreadPoolFlex_Create(),HPR_ThreadPoolFlex_Destroy()
*/
HPR_DECLARE HPR_HANDLE CALLBACK HPR_ThreadPoolFlex_Create(HPR_UINT32 nMaxThreadNum, HPR_UINT32 nIldeTime, HPR_VOIDPTR(CALLBACK *fWorkRoutine)(HPR_VOIDPTR), HPR_UINT32 nStackSize = 0);

/**
* HPR_ThreadPool_Destroy
* @param hHandle (IN) created by HPR_ThreadPool_CreateFlex
* @return 0 success, -1 fail.
* @sa HPR_ThreadPool_CreateFlex(),HPR_ThreadPool_WorkFlex()
*/
HPR_DECLARE HPR_INT32 CALLBACK HPR_ThreadPoolFlex_Destroy(HPR_HANDLE hHandle);

/**
* HPR_ThreadPoolFlex_Work
* @param hHandle (IN) created by HPR_ThreadPoolFlex_Create
* @param Params (IN) parameter pass to fWorkRoutine.
* @return 0 success, -1 fail.
* @sa HPR_ThreadPoolFlex_Create(),HPR_ThreadPoolFlex_Destroy()
*/
HPR_DECLARE HPR_INT32 CALLBACK HPR_ThreadPoolFlex_Work(HPR_HANDLE hHandle, HPR_VOIDPTR pParam);

#endif
