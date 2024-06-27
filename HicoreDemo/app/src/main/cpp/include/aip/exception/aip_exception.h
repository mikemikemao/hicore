/**
 * @copyright HangZhou Hikvision Digital Technology Co., Ltd. All Right Reserved.
 * @file     aip_exception.h
 * @brief    异常处理
**/
#ifndef __AIP_EXCEPTION_H__
#define __AIP_EXCEPTION_H__

/************************************************************************
 Included Header
 ************************************************************************/
#include "common/aip_common.h"
#include "common/aip_common_event.h"
#include "exception/watchdog/aip_watchdog.h"

#ifdef __cplusplus
extern "C" {
#endif

/************************************************************************
 Macros
 ************************************************************************/

/************************************************************************
 Type Definition
 ************************************************************************/

/**
 * @brief  致命信号信息
 * @note AIP_EVENT_MODULE_E为 E_AIP_EVENT_MODULE_NET
 * @note AIP_EVENT_CMD_E为 E_EXCEPTION_EVENT_DEADLY_SIGNAL
 * 对应的入参
**/
typedef struct
{
    HPR_INT32  sdwSignum;  //触发的信号值
} NET_EVENT_DEAYLY_SIGNAL_MSG_T, *NET_EVENT_DEAYLY_SIGNAL_MSG_P;

/**
 * @brief 异常模块AIP_EVENT_CMD_E索引
 * @note AIP_EVENT_MODULE_E为 E_AIP_EVENT_MODULE_EXCEPTION
**/
typedef enum
{
    E_EXCEPTION_EVENT_DEADLY_SIGNAL   = 0,  // 进程接收到了致命的信号
                                      //入参:NET_EVENT_DEAYLY_SIGNAL_MSG_P 触发的信息
                                      //出参:NULL
                                      //返回值: HPR_OK
                                      //        HPR_FALSE
    E_EXCEPTION_EVENT_SOFT_WDT_SHOCK  = 1,  // 软件看门狗任务休克(线程喂狗超时,或进程检测异常)
                                      //入参:NET_EVENT_SOFT_WDT_SHOCK_MSG_P 任务信息
                                      //出参:NULL
                                      //返回值: HPR_OK
                                      //        HPR_FALSE
} EXCEPTION_EVENT_CMD_E;



//@brief: 任务类型 .
//@note ：类型名称错误，保持已经在用版本兼容，不再修改
typedef enum
{
    E_TASK_TYPE_THREAD  = 0,     // 线程
    E_TASK_TYPE_PROCESS = 1,     // 进程
    E_TASK_TYPE_INVALID,         //无效
} NET_EVNET_TASK_TYPE_E;

/**
 * @brief  软件看门狗任务休克进程信息
**/
typedef struct
{
    pid_t      hdlPid;                          // 进程Pid
    HPR_INT8   byaCmd[CMD_LEN];                 // 执行的进程命令
} NET_EVENT_PROCESS_INFO_MSG_T, *NET_EVENT_PROCESS_INFO_MSG_P;

/**
 * @brief  软件看门狗任务休克线程信息
**/
typedef struct
{
    HPR_LONG   hdlTid;                              // 线程Tid(gettid获取而非pthread_self)
    HPR_UINT32 dwShockPeriod;                       // 休克周期, 单位s
} NET_EVENT_THREAD_TASK_MSG_T, *NET_EVENT_THREAD_TASK_MSG_P;

/**
 * @brief  软件看门狗任务休克(线程喂狗超时)信息
 * @note AIP_EVENT_MODULE_E为 E_AIP_EVENT_MODULE_NET
 * @note AIP_EVENT_CMD_E为 E_EXCEPTION_EVENT_SOFT_WDT_SHOCK
 * 对应的入参
**/
typedef struct
{
    WDT_HANDLE hdlTask;                             // 任务的handle
    HPR_INT8   byaTaskName[WDT_S_TASK_NAME_LEN];    // 监视的任务名字，一般为线程名或进程名
    NET_EVNET_TASK_TYPE_E eTaskType;                // 任务类型

    HPR_BOOL  bRestartSuccess;                      // 是否重启成功
    HPR_UINT32  dwRestartCount;                     // 重启过的次数
 
    union
    {
        NET_EVENT_THREAD_TASK_MSG_T  stThreadInfo;   //eTaskType == E_TASK_TYPE_THREAD;
        NET_EVENT_PROCESS_INFO_MSG_T stProcessInfo;  //eTaskType == E_TASK_TYPE_PROCESS;
    };
} NET_EVENT_SOFT_WDT_SHOCK_MSG_T, *NET_EVENT_SOFT_WDT_SHOCK_MSG_P;

/** @brief  异常模块初始化参数*/
typedef struct
{
    HPR_BOOL bEnableDeadlySigPro;    // [in], 是否使能致命信号处理
    HPR_BOOL bEnableHwWatchdog;      // [in], 是否使能硬件看门狗模块
    HPR_BOOL bEnableSfWatchdog;      // [in], 是否使能软件看门狗模块
    HPR_BOOL bPauseSfWatchdog;       // [in], 是否暂停软件看门狗模块(bEnableSfWatchdog 为HPR_TRUE时该参数才有效)
                                     //       HPR_TRUE时，软件看门狗注册、喂狗命令将正常，当软件看门狗超时时不会触发异常
                                     //       处理。(该参数可能在上层进行调试时很有效)
} EXCEPTION_PARAM_T, *EXCEPTION_PARAM_P;

/**
 *  @brief 异常服务回调
 */
typedef AIP_EVENT_CALLBACK_FUN EXCEPTION_EVENT_CALLBACK_FUN ;

/************************************************************************
  Function Declaration
 ************************************************************************/

/**
 * @fn        AIP_EXTERN HPR_INT32 aip_exception_service_start(EXCEPTION_PARAM_P pstInitParam, EXCEPTION_EVENT_CALLBACK_FUN fnCbFun)
 * @brief     开启异常处理服务
 * @param[in] pstInitParam, see EXCEPTION_PARAM_P define
 * @param[in] fnCbFun, 回调函数,允许为NULL
 * @note      当前包括异常信号处理、硬件看门狗、软件看门狗
 * @return    HPR_OK: success; other: fail
 */
AIP_EXTERN HPR_INT32 aip_exception_service_start(EXCEPTION_PARAM_P pstInitParam, EXCEPTION_EVENT_CALLBACK_FUN fnCbFun);

/**
 * @fn      AIP_EXTERN HPR_INT32 aip_exception_service_stop(HPR_VOID)
 * @brief   关闭异常处理服务
 * @note    当前包括异常信号处理、硬件看门狗、软件看门狗
 * @return  HPR_OK: success; other: fail
 */
AIP_EXTERN HPR_INT32 aip_exception_service_stop(HPR_VOID);

/**
 * @fn        AIP_EXTERN HPR_INT32 aip_exception_set_catch_dealy_signal_flag(HPR_BOOL bEnable)
 * @brief     设置是否捕获致命信号
 * @param[in] bEnable 是否由进程自己捕获(如果自己捕获处理,将不会抛给系统,如coredump不会生成 )
 * @return    HPR_OK: success; other: fail
 */
AIP_EXTERN HPR_INT32 aip_exception_set_catch_dealy_signal_flag(HPR_BOOL bEnable);



#ifdef __cplusplus
}
#endif
#endif /* __AIP_EXCEPTION_H__ END */
