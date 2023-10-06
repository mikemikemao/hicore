/*
 * CopyRight:	HangZhou Hikvision System Technology Co., Ltd. All	Right Reserved.
 * FileName:	HRP_Event.h
 * Desc:		OS Layer Component.
 * Author:		schina
 * Date:		2009-03-02
 * Contact:		zhaoyiji@hikvision.com.cn
 * History:		Created By Zhaoyiji 2009-06-05
 * */

/*! 
	\file HPR_Event.h
	\brief HPR Event Manager.

	Details.
*/

#ifndef __HPR_EVENT_H__
#define __HPR_EVENT_H__

#include "HPR_Config.h"
#include "HPR_Types.h"
#include "HPR_Addr.h"

/**< ����λ */
#define HPR_FD_BASE		1

/**< ����λ */
#define HPR_FD_READ		(HPR_FD_BASE<<0)
#define HPR_FD_WRITE	(HPR_FD_BASE<<1)
#define HPR_FD_OOB		(HPR_FD_BASE<<2)
#define HPR_FD_ACCEPT	(HPR_FD_BASE<<3)
#define HPR_FD_CONNECT	(HPR_FD_BASE<<4)
#define HPR_FD_CLOSE	(HPR_FD_BASE<<5)
#define HPR_FD_QOS		(HPR_FD_BASE<<6)
#define HPR_GROUP_QOS	(HPR_FD_BASE<<7)

/**< ������λ�� */
#define HPR_FD_MAX_EVENT	8

#if defined (OS_WINDOWS)
#define HPR_WAIT_OBJECT_0 WAIT_OBJECT_0						/**<��һ���¼�	*/
#define HPR_WAIT_TIMEOUT		WAIT_TIMEOUT				/**<��ʱ		*/
#define HPR_WAIT_INVALID_PARAM	((HPR_UINT32)0x7ffffffe)	/**<��������	*/
#define HPR_WAIT_INVALID_EVENT	((HPR_UINT32)0x7ffffffd)	/**<��Ч�¼�	*/
#define HPR_WAIT_FAILED			((HPR_UINT32)0x7ffffffc)	/**<�ȴ�ʧ��	*/
typedef WSANETWORKEVENTS HPR_NETWORKEVENTS_T;
#elif defined (OS_POSIX)
#define HPR_WAIT_OBJECT_0		((HPR_UINT32)0x0)
#define HPR_WAIT_TIMEOUT		((HPR_UINT32)0x7fffffff)
#define HPR_WAIT_INVALID_PARAM	((HPR_UINT32)0x7ffffffe)
#define HPR_WAIT_INVALID_EVENT	((HPR_UINT32)0x7ffffffd)
#define HPR_WAIT_FAILED			((HPR_UINT32)0x7ffffffc)
typedef struct HPR_NETWORKEVENTS_S
{
	HPR_UINT32 lNetworkEvents;
	HPR_INT32 iErrorCode[HPR_FD_MAX_EVENT];
}HPR_NETWORKEVENTS_T;
#else
#endif

/**
 * ģ����� FD_CLOSE, FD_READ, FD_WRITE��windows��������
 */

/**
 * HPR_CreateEvent ����һ���¼����.
 * @param bInitState (IN) �¼���ʼ״̬(HPR_TRUE����״̬,HPR_FALSE�Ǵ���״̬).
 * @return NULLʧ��,����ֵ�ɹ�.
 * @sa HPR_CloseEvent().
 */
HPR_DECLARE HPR_HANDLE CALLBACK HPR_CreateEvent(HPR_BOOL bInitState);

/**
 * HPR_CloseEvent �ر�һ���¼����.
 * @param hEvent (IN) �¼��������HPR_CreateEvent����.
 * @return HPR_TRUE �ɹ���HPR_FALSEʧ��.
 * @sa HPR_CreateEvent().
 */
HPR_DECLARE HPR_BOOL CALLBACK HPR_CloseEvent(HPR_HANDLE hEvent);

/**
 * HPR_WaitForSingleObject �ȴ������¼���Ϣ����
 * @param hEvent (IN) �¼����
 * @param nTimeOut (IN) �ȴ���ʱʱ��
 * @return HPR_WAIT_OBJECT_0�ɹ���HPR_WAIT_TIMEOUT��ʱʧ�ܣ�����ֵʧ��.
 * @sa HPR_WaitForMultipleObjects
 */
HPR_DECLARE HPR_UINT32 CALLBACK HPR_WaitForSingleObject(HPR_HANDLE hEvent, HPR_UINT32 nTimeOut);

/**
 * HPR_WaitForMultipleObjects �ȴ�����¼���Ϣ����
 * @param nEventCount (IN) �¼�����
 * @param hEvents (IN) �¼��������
 * @param bWaitAll (IN) �Ƿ�ȫ���ȴ�����֧�֣�ֻ�ܵȴ����е�һ���¼�����
 * @param nTimeOut (IN) �ȴ���ʱʱ��
 * @return HPR_WAIT_OBJECT_0�ɹ���HPR_WAIT_TIMEOUT��ʱʧ�ܣ�����ֵʧ��
 * @sa HPR_WaitForSingleObject
 */
HPR_DECLARE HPR_UINT32 CALLBACK HPR_WaitForMultipleObjects(HPR_UINT32 nEventCount, HPR_HANDLE* hEvents, HPR_BOOL bWaitAll, HPR_UINT32 nTimeOut);

/**
 * HPR_ResetEvent �����¼���Ϣ
 * @param hEvent (IN) �¼����
 * @return HPR_TRUE �ɹ���HPR_FALSEʧ��.
 * @sa HPR_SetEvent
 */
HPR_DECLARE HPR_BOOL CALLBACK HPR_ResetEvent(HPR_HANDLE hEvent);

/**
 * HPR_SetEvent �����¼�
 * @param hEvent (IN) �¼����
 * @return HPR_TRUE �ɹ���HPR_FALSEʧ��.
 * @sa HPR_ResetEvent
 */
HPR_DECLARE HPR_BOOL CALLBACK HPR_SetEvent(HPR_HANDLE hEvent);

/**
 * HPR_EventSelect �������¼����¼������
 * @param nSockFd (IN) �����׽���
 * @param hEvent (IN) �¼����
 * @param nFlag (IN) �����¼���־������λ'|'������
 * @return 0 �ɹ���-1ʧ��.
 * @sa
 */
HPR_DECLARE HPR_INT32 CALLBACK HPR_EventSelect(HPR_SOCK_T nSockFd, HPR_HANDLE hEvent, HPR_UINT32 nFlag);

/**
 * HPR_EnumNetworkEvents ö�������¼�
 * @param nSockFd (IN) �����׽���
 * @param hEvent (IN) �¼����
 * @param pNetworkEvents (OUT) �����¼�����
 * @return 0 �ɹ���-1ʧ��.
 * @sa
 */
HPR_DECLARE HPR_INT32 CALLBACK HPR_EnumNetworkEvents(HPR_SOCK_T nSockFd, HPR_HANDLE hEvent, HPR_NETWORKEVENTS_T* pNetworkEvents);

#endif
