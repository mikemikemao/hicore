#ifndef __HPR_MEMORY_POOL_GLOBAL_H__
#define __HPR_MEMORY_POOL_GLOBAL_H__

/** @file	HPR_MemoryPoolGlobal.h
 *  @note   HangZhou Hikvision System Technology Co., Ltd. All Right Reserved.
 *  @brief 	ȫ���ڴ��
 *	
 *  @author zhourui9
 *  @data   2018/09/04
 * 
 *	@note �ڲ���װ�˶����ͬ��λ�ı䳤�ڴ�أ��������ɹ�ͬʹ�øýӿڣ�ʹ���ڴ�����õ���Ч����
 *	@note �����յ��ڴ��1���ӿ����Զ����գ�ÿ�η���֧�ֵ�����ڴ�Ϊ10MB
 *	@note 
 *
 *  @warning ������д���ļ���صľ�����Ϣ
 */

#include "HPR_Config.h"
#include "HPR_Types.h"

HPR_INT32 HPR_InitMemoryPool_Inter(HPR_SIZE maxBytes);

HPR_INT32 HPR_FiniMemoryPool_Inter(void);


/**
 * HPR_MemoryPoolGlobal_Init ȫ���ڴ�س�ʼ��
 * @param bytes (IN) ����ܷ����С(��λ�ֽ�)
 * @return HPR_TRUR���ɹ���HPR_FALSE��ʧ��(�ѱ���ʼ��)
 * @note ����HPR_finiʱ���Զ�����ʼ��,������ڴ�����Ϊ32λ:2G��64λ:5G;����ֵ��������ֵʱ�ᱻǿ�Ƶ�������ֵ
 */
HPR_DECLARE HPR_BOOL CALLBACK HPR_MemoryPoolGlobal_Init(HPR_SIZE maxBytes);

/**
 * HPR_MemoryPoolGlobal_Alloc ����һ����
 * @param bytes (IN) �����С(��λ�ֽ�)
 * @return ���ַָ��
 */
HPR_DECLARE HPR_VOIDPTR CALLBACK HPR_MemoryPoolGlobal_Alloc(HPR_SIZE bytes);

/**
 * HPR_MemoryPoolGlobal_Free �ͷ�һ����
 * @param ptr (IN) ��ָ��
 * @return
 */
HPR_DECLARE HPR_VOID CALLBACK HPR_MemoryPoolGlobal_Free(HPR_VOIDPTR ptr);

/**
 * HPR_MemoryPoolGlobal_Size ��ȡ��ǰ�ڴ�ռ�ô�С
 * @return �ڴ�ռ�ô�С(��λ�ֽ�)
 */
HPR_DECLARE HPR_SIZE CALLBACK HPR_MemoryPoolGlobal_Size(void);

/**
 * HPR_MemoryPoolGlobal_IdleSize ��ȡ�����ڴ�ռ�ô�С
 * @return �����ڴ��С(��λ�ֽ�)
 */
HPR_DECLARE HPR_SIZE CALLBACK HPR_MemoryPoolGlobal_IdleSize(void);


#endif
