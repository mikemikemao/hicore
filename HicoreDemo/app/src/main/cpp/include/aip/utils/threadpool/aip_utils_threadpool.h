/**
 * @copyright HangZhou Hikvision Digital Technology Co., Ltd. All Right Reserved.
 * @file     aip_utils_threadpool.hpp
 * @brief    线程池
**/
#ifndef __AIP_UTILS_THREADPOOL_H__
#define __AIP_UTILS_THREADPOOL_H__

/************************************************************************
 Included Header
 ************************************************************************/
#include <stddef.h>
#include "common/aip_common.h"


#ifdef __cplusplus
extern "C" {
#endif

/************************************************************************
 Macros
 ************************************************************************/
#define AIP_THREAD_FACTORY_HANDLE_ERROR NULL

/************************************************************************
 Type Definition
 ************************************************************************/

/** @brief  线程池 handle**/
typedef HPR_VOID* AIP_THREAD_FACTORY_HANDLE;

/**
 * @brief: 关闭线程池的策略
 * @note : 每位独立
**/
typedef enum 
{
    E_AIP_THREADPOOL_CLOSE_GRACEFUL  = 0x01,   //优雅的，置位  :将会等待所有已经注册到线程池的任务执行完毕后关闭；
                                               //        不置位:忽略已经注册但是尚未开始执行的任务，直接关闭
                                               //需要注意，无论是否置位，已经开始执行的任务将会执行完再关闭
} AIP_THREADPOOL_CLOSE_FLAGS_E;

/**@brief  任务类型**/
typedef void(*AIP_THREAD_TASK_PROC)(void*);
typedef HPR_VOID* AIP_THRAD_TASK_CONTEXT;

/************************************************************************
 Function Declaration
 ************************************************************************/


/**
 * @fn         AIP_EXTERN AIP_THREAD_FACTORY_HANDLE aip_utils_threadpool_create_factory(HPR_INT8 *pbyFactoryName, HPR_UINT32 dwMinWorker, HPR_UINT32 dwMaxWorker)
 * @brief      创建一个线程池
 * @param[in]  pbyFactoryName : 线程池的名称，不允许为NULL, 不允许存在同名的线程池
 * @param[in]  dwMinWorker : 线程池最少运行线程数，无论是否空闲，线程池始终保持线程存在这么多任务线程
 * @param[in]  dwMaxWorker : 线程池最少运行线程数，无论是否空闲，在线程忙碌时，允许线程池增长到这么多的任务线程,并在空闲
 * 时释放到dwMinWorker数
 * @return     成功返回 对应的线程池handle, 失败返回AIP_THREAD_FACTORY_HANDLE_ERROR
**/
AIP_EXTERN AIP_THREAD_FACTORY_HANDLE aip_utils_threadpool_create_factory(HPR_INT8 *pbyFactoryName, HPR_UINT32 dwMinWorker, HPR_UINT32 dwMaxWorker);

/**
 * @fn         AIP_EXTERN HPR_INT32 aip_utils_threadpool_close_factory(AIP_THREAD_FACTORY_HANDLE hdlFactory, AIP_THREADPOOL_CLOSE_FLAGS_E eFlag)
 * @brief      关闭指定handle的线程池
 * @param[in]  hdlFactory : 要删除的线程池的handle
 * @param[in]  eFlag      : 关闭策略，see AIP_THREADPOOL_CLOSE_FLAGS_E define
 * @return     success: HPR_OK; fail: HPR_ERROR
**/
AIP_EXTERN HPR_INT32 aip_utils_threadpool_close_factory(AIP_THREAD_FACTORY_HANDLE hdlFactory, AIP_THREADPOOL_CLOSE_FLAGS_E eFlag);

/**
 * @fn         AIP_EXTERN HPR_INT32 aip_utils_threadpool_close_factory_by_name(HPR_INT8 *pbyFactoryName, AIP_THREADPOOL_CLOSE_FLAGS_E eFlag)
 * @brief      关闭指定名称的线程池
 * @param[in]  pbyFactoryName : 要删除的线程池的名称
 * @param[in]  eFlag          : 关闭策略，see AIP_THREADPOOL_CLOSE_FLAGS_E define
 * @return     success: HPR_OK; fail: HPR_ERROR
**/
AIP_EXTERN HPR_INT32 aip_utils_threadpool_close_factory_by_name(HPR_INT8 *pbyFactoryName, AIP_THREADPOOL_CLOSE_FLAGS_E eFlag);

/**
 * @fn         AIP_EXTERN HPR_INT32 aip_utils_threadpool_assign_task(AIP_THREAD_FACTORY_HANDLE hdlFactory, AIP_THREAD_TASK_PROC pProc, AIP_THRAD_TASK_CONTEXT pContext);
 * @brief      向指定线程池分配一个线程任务
 * @param[in]  hdlFactory : 线程池的handle
 * @param[in]  pbyTaskName : 任务名称, 不允许为NULL
 * @param[in]  pProc       : 执行任务的函数指针
 * @param[in]  pContext    : 上下文(即函数指针所需要的参数)
 * 时释放到dwMinWorker数
 * @return     成功返回 对应的线程池handle, 失败返回AIP_THREAD_FACTORY_HANDLE_ERROR
**/
AIP_EXTERN HPR_INT32 aip_utils_threadpool_assign_task(AIP_THREAD_FACTORY_HANDLE hdlFactory, AIP_THREAD_TASK_PROC pProc, AIP_THRAD_TASK_CONTEXT pContext);

/**
 * @fn         AIP_EXTERN HPR_VOID aip_utils_threadpool_show_info(HPR_VOID);
 * @brief      打印输出线程池当前执行状态
**/
AIP_EXTERN HPR_VOID aip_utils_threadpool_show_info(HPR_VOID);

#ifdef __cplusplus
}
#endif

#endif /*  __AIP_UTILS_THREADPOOL_H__ END */
