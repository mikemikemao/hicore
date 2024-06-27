#ifndef __HPR_SHARED_MUTEX_H__
#define __HPR_SHARED_MUTEX_H__

/** @file	HPR_SharedMutex.h
 *  @note   HangZhou Hikvision System Technology Co., Ltd. All Right Reserved.
 *  @brief 	������/��д��
 *	
 *  @author zhourui9
 *  @data   2018/08/29
 * 
 *	@note д/��ռ����ʹ��Lock/Unlock���ж�ռ����/��������ʹ��LockShared/UnlockShared
 *	@note ��ʷ��¼��
 *	@note 
 *
 *  @warning ������д���ļ���صľ�����Ϣ
 */

#include "HPR_Config.h"
#include "HPR_Types.h"
#include "HPR_Mutex.h"
#include "HPR_Cond.h"

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct HPR_SHARED_MUTEX_T HPR_SHARED_MUTEX_T;

#ifdef __cplusplus
}
#endif

/**
 * HPR_SharedMutexCreate ����������
 * @param pMutex (OUT) ���������Ĺ�����
 * @return 0 success, -1 fail.
 * @sa HPR_SharedMutexCreate
 */
HPR_DECLARE HPR_INT32 CALLBACK HPR_SharedMutexCreate(HPR_SHARED_MUTEX_T* pMutex); 

/**
 * HPR_SharedMutexDestroy ����ͨ��HPR_SharedMutexCreate���������Ĺ�����.
 * @param pMutex (IN) ͨ��HPR_SharedMutexCreate���������Ĺ�����.
 * @return 0 success, -1 fail.
 * @sa HPR_SharedMutexCreate
 */
HPR_DECLARE HPR_INT32 CALLBACK HPR_SharedMutexDestroy(HPR_SHARED_MUTEX_T* pMutex); 

/**
 * HPR_SharedMutexLock ��ռ(д)����
 * @param pMutex (IN) ͨ��HPR_SharedMutexCreate���������Ĺ�����.
 * @return 0 success, -1 fail.
 * @sa HPR_SharedMutexCreate,HPR_SharedMutexTryLock(),HPR_SharedMutexUnlock().
 */
HPR_DECLARE HPR_INT32 CALLBACK HPR_SharedMutexLock(HPR_SHARED_MUTEX_T* pMutex); 

/**
 * HPR_SharedMutexTryLock ���Զ�ռ(д)����
 * @param pMutex (IN) ͨ��HPR_SharedMutexCreate���������Ĺ�����.
 * @return 0 success, -1 fail.
 * @sa HPR_SharedMutexCreate(),HPR_SharedMutexUnlock(),HPR_SharedMutexLock().
 */
HPR_DECLARE HPR_INT32 CALLBACK HPR_SharedMutexTryLock(HPR_SHARED_MUTEX_T* pMutex);

/**
 * HPR_SharedMutexUnlock ��ռ(д)����
 * @param pMutex (IN) ͨ��HPR_SharedMutexCreate���������Ĺ�����.
 * @return 0 success, -1 fail.
 * @sa HPR_SharedMutexCreate(),HPR_SharedMutexTryLock(),HPR_SharedMutexLock()
 */
HPR_DECLARE HPR_INT32 CALLBACK HPR_SharedMutexUnlock(HPR_SHARED_MUTEX_T* pMutex); 

/**
 * HPR_SharedMutexLockShared ����(��)����
 * @param pMutex (IN) ͨ��HPR_SharedMutexCreate���������Ĺ�����.
 * @return 0 success, -1 fail.
 * @sa HPR_SharedMutexCreate,HPR_SharedMutexTryLock(),HPR_SharedMutexUnlock().
 */
HPR_DECLARE HPR_INT32 CALLBACK HPR_SharedMutexLockShared(HPR_SHARED_MUTEX_T* pMutex); 

/**
 * HPR_SharedMutexTryLockShared ���Թ���(��)����
 * @param pMutex (IN) ͨ��HPR_SharedMutexCreate���������Ĺ�����.
 * @return 0 success, -1 fail.
 * @sa HPR_SharedMutexCreate(),HPR_SharedMutexUnlock(),HPR_SharedMutexLock().
 */
HPR_DECLARE HPR_INT32 CALLBACK HPR_SharedMutexTryLockShared(HPR_SHARED_MUTEX_T* pMutex);

/**
 * HPR_SharedMutexUnlockShared ����(��)����
 * @param pMutex (IN) ͨ��HPR_SharedMutexCreate���������Ĺ�����.
 * @return 0 success, -1 fail.
 * @sa HPR_SharedMutexCreate(),HPR_SharedMutexTryLock(),HPR_SharedMutexLock()
 */
HPR_DECLARE HPR_INT32 CALLBACK HPR_SharedMutexUnlockShared(HPR_SHARED_MUTEX_T* pMutex);

#ifdef __cplusplus
// ��������д��һ������c++��������Ϊ���ܻ�ȡ�ڲ���HPR_MUTEX_T����ΪHPR��������ֻ�����������
class HPR_DECLARE_CLASS HPR_UniqueMutex
{
public:
    HPR_UniqueMutex();
    HPR_UniqueMutex(HPR_UINT32 nFlag);
    ~HPR_UniqueMutex();

    HPR_INT32 Lock();
    HPR_INT32 Unlock();
    HPR_INT32 TryLock();

    HPR_MUTEX_T m_mutex;

private:
    HPR_UniqueMutex(const HPR_UniqueMutex&);
    const HPR_UniqueMutex& operator=(const HPR_UniqueMutex&);
};

class HPR_DECLARE_CLASS HPR_SharedMutex
{
private:
    class HPR_DECLARE_CLASS CStateData 
    {
    public:
        CStateData();

        unsigned int m_uSharedCount;
        bool m_bExclusive;
        unsigned int m_bExclusiveWaitingBlockedCount;
    };

    HPR_SharedMutex(const HPR_SharedMutex&);
    const HPR_SharedMutex& operator=(const HPR_SharedMutex&);

    CStateData m_cState;
    HPR_UniqueMutex m_cStateChange;
    HPR_Cond m_cSharedCond;
    HPR_Cond m_cExclusiveCond;

public:
    HPR_SharedMutex();
    ~HPR_SharedMutex();

    HPR_INT32 Lock();
    HPR_INT32 Unlock();
    HPR_INT32 TryLock();

    HPR_INT32 LockShared();
    HPR_INT32 UnlockShared();
    HPR_INT32 TryLockShread();

};
#endif

#endif
