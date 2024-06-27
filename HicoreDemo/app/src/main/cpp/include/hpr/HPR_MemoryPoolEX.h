#ifndef __HPR_MEMORY_POOL_EX_H__
#define __HPR_MEMORY_POOL_EX_H__

/** @file	HPR_MemoryPoolEx.h
 *  @note   HangZhou Hikvision System Technology Co., Ltd. All Right Reserved.
 *  @brief  �ɱ䳤�ڴ�أ��ڹ̶��ڴ�ػ����ϵ���չ������һ���ڴ��Ķ������
 *	
 *  @author zhourui9
 *  @data   2018/08/18
 * 
 *	@note �����û���Ҫ���ڴ�鳤�Ȳ�һ�£��ȷ���һ���ϴ���ڴ�飬�����л���һ���Ŀռ���û�
 *	@note �����ڴ�Խ������Ҫ��ʼ���߽����ݣ��䳤��ÿ�η����ڴ涼��Ҫ��ʼ����Ӱ�����ܣ����Ա䳤�ڴ�ز���������Խ���⹦��
 *	@note 
 *
 *  @warning ������д���ļ���صľ�����Ϣ
 */

#include "HPR_Config.h"
#include "HPR_Types.h"

/**
 * HPR_MemoryPoolEx_Create ����һ���䳤�ڴ�ؾ��
 * @param minSize (IN) ��С�ڴ�(��λsizeUnit��Ĭ��MB����ʵ��������Ϊ1���û���Ϊ0�Ļ����ڲ�Ҳ��ת��Ϊ1)
 * @param maxSize (IN) ����ڴ�(��λsizeUnit��Ĭ��MB)
 * @param idleTimeoutMillis (IN) ���г�ʱ����ʱ��(��λ���룬Ĭ��1���ӻ���)
 * @param noLock (IN) ����(Ĭ��false��������ʱ��<0�Ҵ˲�������Ϊtrue������ͬʱ����ʱ����Ч�����ܸ��ߣ�����Ҫ�û��Լ������̰߳�ȫ)
 * @param sizeUnit (IN) ��С��λ(Ĭ���ף��û�Ҳ�����Լ����壬�õ�λ��СͬʱҲ��ÿ�η������������ֽ�����������Χ�ڿ��ʵ����)
 * @return �ڴ�ؾ��
 */
#ifdef __cplusplus
HPR_DECLARE HPR_HANDLE CALLBACK HPR_MemoryPoolEx_Create(HPR_SIZE minSize, // ��С�ڴ�(��λsizeUnit��Ĭ��MB����ʵ��������Ϊ1���û���Ϊ0�Ļ����ڲ�Ҳ��ת��Ϊ1)
                                                        HPR_SIZE maxSize, // ����ڴ�(��λsizeUnit��Ĭ��MB)
                                                        HPR_INT64 idleTimeoutMillis = 60000, // ���г�ʱ����ʱ��(��λ���룬Ĭ��1���ӻ���)
                                                        HPR_BOOL noLock = HPR_FALSE, // ����(Ĭ��false��������ʱ��<0�Ҵ˲�������Ϊtrue������ͬʱ����ʱ����Ч�����ܸ��ߣ�����Ҫ�û��Լ������̰߳�ȫ)
                                                        HPR_SIZE sizeUnit = 1048576); // ��С��λ(Ĭ���ף��û�Ҳ�����Լ����壬�õ�λ��СͬʱҲ��ÿ�η������������ֽ�����������Χ�ڿ��ʵ����)
#else
HPR_DECLARE HPR_HANDLE CALLBACK HPR_MemoryPoolEx_Create(HPR_SIZE minSize, // ��С�ڴ�(��λsizeUnit��Ĭ��MB����ʵ��������Ϊ1���û���Ϊ0�Ļ����ڲ�Ҳ��ת��Ϊ1)
                                                        HPR_SIZE maxSize, // ����ڴ�(��λsizeUnit��Ĭ��MB)
                                                        HPR_INT64 idleTimeoutMillis, // ���г�ʱ����ʱ��(��λ���룬Ĭ��1���ӻ���)
                                                        HPR_BOOL noLock, // ����(Ĭ��false��������ʱ��<0�Ҵ˲�������Ϊtrue������ͬʱ����ʱ����Ч�����ܸ��ߣ�����Ҫ�û��Լ������̰߳�ȫ)
                                                        HPR_SIZE sizeUnit); // ��С��λ(Ĭ���ף��û�Ҳ�����Լ����壬�õ�λ��СͬʱҲ��ÿ�η������������ֽ�����������Χ�ڿ��ʵ����)
#endif

/**
 * HPR_MemoryPoolEx_Destroy ����һ���䳤�ڴ��
 * @param memoryPoolHandle (IN) �ڴ�ؾ��
 * @return
 */
HPR_DECLARE HPR_VOID CALLBACK HPR_MemoryPoolEx_Destroy(HPR_HANDLE memoryPoolHandle);

/**
 * HPR_MemoryPoolEx_Alloc �����ڴ�
 * @param memoryPoolHandle (IN) �ڴ�ؾ��
 * @param bytes (IN) �����С(��λ�ֽ�)
 * @return �ڴ�ָ��
 */
HPR_DECLARE HPR_VOIDPTR CALLBACK HPR_MemoryPoolEx_Alloc(HPR_HANDLE memoryPoolHandle, HPR_SIZE bytes);

/**
 * HPR_MemoryPoolEx_Free �ͷ��ڴ�
 * @param memoryPoolHandle (IN) �ڴ�ؾ��
 * @param ptr (IN) �ڴ�ָ��
 * @return
 */
HPR_DECLARE HPR_VOID CALLBACK HPR_MemoryPoolEx_Free(HPR_HANDLE memoryPoolHandle, HPR_VOIDPTR ptr);

/**
 * HPR_MemoryPoolEx_Size ��ȡ��ǰ�ڴ�ռ�ô�С
 * @param memoryPoolHandle (IN) �ڴ�ؾ��
 * @return �ڴ�ռ�ô�С(��λ�ֽ�)
 */
HPR_DECLARE HPR_SIZE CALLBACK HPR_MemoryPoolEx_Size(HPR_HANDLE memoryPoolHandle);

/**
 * HPR_MemoryPoolEx_IdleSize ��ȡ��ǰ�����ڴ�ռ�ô�С
 * @param memoryPoolHandle (IN) �ڴ�ؾ��
 * @return �����ڴ��С(��λ�ֽ�)
 */
HPR_DECLARE HPR_SIZE CALLBACK HPR_MemoryPoolEx_IdleSize(HPR_HANDLE memoryPoolHandle);

#ifdef __cplusplus
namespace hpr 
{
    class CRealMemoryPoolEx;
}

class HPR_DECLARE_CLASS HPR_MemoryPoolEx
{
public:
    HPR_MemoryPoolEx(HPR_SIZE minSize, // ��С�ڴ�(��λsizeUnit��Ĭ��MB����ʵ��������Ϊ1���û���Ϊ0�Ļ����ڲ�Ҳ��ת��Ϊ1)
        HPR_SIZE maxSize, // ����ڴ�(��λsizeUnit��Ĭ��MB)
        HPR_INT64 idleTimeoutMillis = 60000, // ���г�ʱ����ʱ��(��λ���룬Ĭ��1���ӻ���)
        HPR_BOOL noLock = HPR_FALSE, // ����(Ĭ��false��������ʱ��<0�Ҵ˲�������Ϊtrue������ͬʱ����ʱ����Ч�����ܸ��ߣ�����Ҫ�û��Լ������̰߳�ȫ)
        HPR_SIZE sizeUnit = 1048576); // ��С��λ(Ĭ���ף��û�Ҳ�����Լ����壬�õ�λ��СͬʱҲ��ÿ�η������������ֽ�����������Χ�ڿ��ʵ����)

    virtual ~HPR_MemoryPoolEx();

    HPR_VOIDPTR Alloc(HPR_SIZE bytes); // �����С���ܳ���sizeUnit��λ��С�����������򷵻�NULL

    HPR_VOID Free(void* ptr);

    HPR_SIZE Size() const;

    HPR_SIZE IdleSize() const;

private:
    HPR_MemoryPoolEx(const HPR_MemoryPoolEx&);
    const HPR_MemoryPoolEx& operator=(const HPR_MemoryPoolEx&);

    hpr::CRealMemoryPoolEx* const m_pRef; // Ϊ�˲��õ��������ڲ���Ա
};
#endif

#endif
