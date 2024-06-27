#ifndef __HPR_MEMORY_POOL_H__
#define __HPR_MEMORY_POOL_H__

/** @file	HPR_MemoryPool.h
 *  @note   HangZhou Hikvision System Technology Co., Ltd. All Right Reserved.
 *  @brief 	�ɶ�̬�����ڴ�Ķ����ڴ�� 
 *	
 *  @author zhourui9
 *  @data   2018/08/15
 * 
 *	@note �ڴ������һ���ķ�Χ�ڸ��������ڴ���к󣬳���һ����ʱ��δ��ʹ����ᱻ�黹��ϵͳ
 *	@note ��ʷ��¼��
 *	@note 
 *
 *  @warning ������д���ļ���صľ�����Ϣ
 */

#include "HPR_Config.h"
#include "HPR_Types.h"

/**
 * HPR_MemoryPool_Create ����һ�������ڴ�ؾ��
 * @param blockSize (IN) ���С
 * @param minBlockNum (IN) ����С����(�ڴ�鲻�����ڸ�ֵ)
 * @param maxBlockNum (IN) ���������(�ڴ�鲻�ᳬ����ֵ�����Ѵﵽ��ֵ���û����÷���ӿڻط��ؿ�)
 * @param enableCheckBoundaryOverflow (IN) �Ƿ����ü��߽����
 * @param idleTimeoutMillis (IN) ����г�ʱ����ʱ��(��λ���룬Ĭ��1���ӻ���)
 * @param noLock (IN) �Ƿ�����(Ĭ��false��������ʱ��<0�Ҵ˲�������Ϊtrue������ͬʱ����ʱ����Ч�����ܸ��ߣ�����Ҫ�û��Լ������̰߳�ȫ)
 * @return �ڴ�ؾ��
 */
#ifdef __cplusplus
HPR_DECLARE HPR_HANDLE CALLBACK HPR_MemoryPool_Create(HPR_SIZE blockSize,
                                                      HPR_SIZE minBlockNum,
                                                      HPR_SIZE maxBlockNum,
                                                      HPR_BOOL enableCheckBoundaryOverflow = HPR_TRUE,
                                                      HPR_INT64 idleTimeoutMillis = 60000,
                                                      HPR_BOOL noLock = HPR_FALSE);
#else
HPR_DECLARE HPR_HANDLE CALLBACK HPR_MemoryPool_Create(HPR_SIZE blockSize,
                                                      HPR_SIZE minBlockNum,
                                                      HPR_SIZE maxBlockNum,
                                                      HPR_BOOL enableCheckBoundaryOverflow,
                                                      HPR_INT64 idleTimeoutMillis,
                                                      HPR_BOOL noLock);
#endif

/**
 * HPR_MemoryPool_Destroy ����һ�������ڴ��
 * @param memoryPoolHandle (IN) �ڴ�ؾ��
 * @return
 */
HPR_DECLARE HPR_VOID CALLBACK HPR_MemoryPool_Destroy(HPR_HANDLE memoryPoolHandle);

/**
 * HPR_MemoryPool_Alloc ����һ����
 * @param memoryPoolHandle (IN) �ڴ�ؾ��
 * @return ���ַָ��
 */
HPR_DECLARE HPR_VOIDPTR CALLBACK HPR_MemoryPool_Alloc(HPR_HANDLE memoryPoolHandle);

/**
 * HPR_MemoryPool_Free �ͷ�һ����
 * @param memoryPoolHandle (IN) �ڴ�ؾ��
 * @param ptr (IN) ��ָ��
 * @return
 */
HPR_DECLARE HPR_VOID CALLBACK HPR_MemoryPool_Free(HPR_HANDLE memoryPoolHandle, HPR_VOIDPTR ptr);

/**
 * HPR_MemoryPool_Size ��ȡ��ǰ�ڴ�ռ�ô�С
 * @param memoryPoolHandle (IN) �ڴ�ؾ��
 * @return �ڴ�ռ�ô�С(��λ�ֽ�)
 */
HPR_DECLARE HPR_SIZE CALLBACK HPR_MemoryPool_Size(HPR_HANDLE memoryPoolHandle);

/**
 * HPR_MemoryPool_IdleSize ��ȡ�����ڴ�ռ�ô�С
 * @param memoryPoolHandle (IN) �ڴ�ؾ��
 * @return �����ڴ��С(��λ�ֽ�)
 */
HPR_DECLARE HPR_SIZE CALLBACK HPR_MemoryPool_IdleSize(HPR_HANDLE memoryPoolHandle);

#ifdef __cplusplus
namespace hpr 
{
    class CRealMemoryPool;
}

class HPR_DECLARE_CLASS HPR_MemoryPool 
{
public:
    HPR_MemoryPool(HPR_SIZE blockSize, // ���С
        HPR_SIZE minBlockNum, // ����С����(�ڴ�鲻�����ڸ�ֵ)
        HPR_SIZE maxBlockNum, // ���������(�ڴ�鲻�ᳬ����ֵ�����Ѵﵽ��ֵ���û����÷���ӿڻط��ؿ�)
        HPR_BOOL enableCheckBoundaryOverflow = HPR_TRUE, // ���ü��߽����
        HPR_INT64 idleTimeoutMillis = 60000, // ���г�ʱ����ʱ��(��λ���룬Ĭ��1���ӻ���)
        HPR_BOOL noLock = HPR_FALSE); // ����(Ĭ��false��������ʱ��<0�Ҵ˲�������Ϊtrue������ͬʱ����ʱ����Ч�����ܸ��ߣ�����Ҫ�û��Լ������̰߳�ȫ)

    virtual ~HPR_MemoryPool();

    HPR_VOIDPTR Alloc();

    HPR_VOID Free(void* ptr);

    HPR_SIZE Size() const;

    HPR_SIZE IdleSize() const;

private:
    HPR_MemoryPool(const HPR_MemoryPool&);
    const HPR_MemoryPool& operator=(const HPR_MemoryPool&);

    hpr::CRealMemoryPool* const m_pRef; // Ϊ�˲��õ��������ڲ���Ա
};
#endif


#endif
