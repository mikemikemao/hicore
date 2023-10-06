/*
 * CopyRight:	HangZhou Hikvision System Technology Co., Ltd. All	Right Reserved.
 * FileName:	HRP_MsgQ.h
 * Desc:		OS Layer Component.
 * Author:		schina
 * Date:		2009-03-02
 * Contact:		zhaoyiji@hikvision.com.cn
 * History:		Created By Zhaoyiji 2009-03-02
 * */

/*! 
	\file HPR_MsgQ.h
	\brief HPR msgq Manager.

	Details.
*/

#ifndef __HPR_MSGQ_H__
#define __HPR_MSGQ_H__

#include "HPR_Config.h"
#include "HPR_Types.h"


#define HPR_MAX_MSGQ_COUNT	100
#define HPR_MAX_MSG_COUNT	100
#define HPR_MAX_MSGQ_SIZE	8096

/**
	�����ȼ���ʱ���Ƶ���Ϣ����
*/

/**
 * struct HPR_MSG_T
 */
typedef struct HPR_MSG_BLOCK_T
{
	int iMsgType;		/**< ��Ϣ����			*/
	int iPriority;		/**< ��Ϣ���ȼ�			*/
	int iMsgLen;		/**< ��Ϣ����(pMsg����)	*/
	char pMsg[1];		/**< ��Ϣ����			*/
}HPR_MSG_BLOCK_T;

/**
 * HPR_MsgQCreateEx ����һ����Ϣ����
 * @param pMsgQId (OUT) ��Ϣ���о��
 * @return 0�ɹ���-1ʧ��.
 * @sa HPR_MsgQDestroyEx
 */
HPR_DECLARE HPR_INT32 CALLBACK HPR_MsgQCreateEx(HPR_HANDLE* pMsgQId);

/**
 * HPR_MsgQDestroyEx ������Ϣ���о��������Ϣ����
 * @param hMsgQId (IN) ��Ϣ���о��
 * @return 0�ɹ���-1ʧ�ܡ�
 * @sa HPR_MsgQCreateEx
 */
HPR_DECLARE HPR_INT32 CALLBACK HPR_MsgQDestroyEx(HPR_HANDLE hMsgQId);

/**
 * HPR_MsgQSendEx ������Ϣ����Ϣ����
 * @param hMsgQId (IN) ��Ϣ���о��
 * @param pMsg (IN) ��Ϣ��,��Ϣ����󳤶�8096�ֽ�
 * @param nTimeOut (IN) ��ʱʱ�䣬��λ����(ms), С�ڵ���0��ʾ����(INFINITE)
 * @return 0�ɹ���-1ʧ��
 * @sa HPR_MsgQReceiveEx
 */
HPR_DECLARE HPR_INT32 CALLBACK HPR_MsgQSendEx(HPR_HANDLE hMsgQId, HPR_MSG_BLOCK_T* pMsg, HPR_UINT32 nTimeOut=HPR_INFINITE);

/**
 * HPR_MsgQReceiveEx ����Ϣ���н�����Ϣ
 * @param hMsgQId (IN) ��Ϣ���о��
 * @param pMsg (OUT) ��Ϣ��,��Ϣ����󳤶�8096�ֽ�
 * @param iTimeOut(IN) ��ʱʱ�䣬��λ����(ms), С�ڵ���0��ʾ����(INFINITE)
 * @return 0�ɹ���-1ʧ��
 * @sa HPR_MsgQSendEx
 */
HPR_DECLARE HPR_INT32 CALLBACK HPR_MsgQReceiveEx(HPR_HANDLE hMsgQId, HPR_MSG_BLOCK_T* pMsg, HPR_UINT32 nTimeOut=HPR_INFINITE);


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#include "HPR_Time.h"
#include "HPR_Semaphore.h"
#include "HPR_Mutex.h"
namespace hpr
{

	class HPR_DECLARE_CLASS hpr_msgq
	{
	public:
		hpr_msgq();
		virtual ~hpr_msgq();
		
	public:
		hpr_int32 putq(HPR_MSG_BLOCK_T* msg);
		hpr_int32 getq(HPR_MSG_BLOCK_T** msg, hpr_int32 timeout = -1);
		void reset();
		
	private:
		hpr_int32 init();
		void destroy();
		
	private:
		hpr::hpr_recursive_mutex m_mutex;
		hpr::hpr_sem m_sem;
		void* m_q;
	};
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#endif
