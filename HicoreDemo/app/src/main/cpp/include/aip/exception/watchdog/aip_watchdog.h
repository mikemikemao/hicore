/**
 * @copyright HangZhou Hikvision Digital Technology Co., Ltd. All Right Reserved.
 * @file      aip_watchdog.h
 * @brief     看门狗(包括硬件看门狗和软件看门狗)
 * @note      硬件看门狗服务: 当前进程定时向系统喂狗，超时时间不喂狗，系统自动重启
 * @note      硬件看门狗服务运行依赖 kernel提供了对应的功能,否则不会触发异常重启
 * @note      软件看门狗服务:定时监测线程运行状态，对于超时不喂狗的线程要么重启要么重启系统
 * @note      软件看门狗服务监测的线程喂狗超时后，会生成当前各线程cpu占用率信息，用于定位
**/
#ifndef __AIP_WATCHDOG_H__
#define __AIP_WATCHDOG_H__

/************************************************************************
 Included Header
 ************************************************************************/
#include "common/aip_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/************************************************************************
 Macros
 ************************************************************************/

#define WDT_INVALID_HANDLE NULL            // 无效handle
#define WDT_S_TASK_NAME_LEN    (64)      // 要求托管的任务名长度限制(包含截断符)

/************************************************************************
 Type Definition
 ************************************************************************/


/**
 * @brief   重启服务接口 类型
 * @return  success: HPR_OK; other: fail
**/
typedef HPR_INT32(*WATCH_DOG_RESTART_TASK_CALLBACK_FUN)(HPR_VOID);

/**
 * @brief   进程探测接口 类型
 * @return  探测成功: HPR_OK; other: fail
**/
typedef HPR_INT32(*WATCH_DOG_DETECT_TASK_CALLBACK_FUN)(HPR_VOID);

typedef HPR_VOID *WDT_HANDLE;              // （软件）看门狗任务handle

//@brief: 进程任务异常处理类型
typedef enum
{
    E_PROCESS_TASK_GARBAGE_TYPE_RESTART = 0,   // 重启
    E_PROCESS_TASK_GARBAGE_TYPE_DROP    = 1,   // 丢弃
    E_PROCESS_TASK_GARBAGE_TYPE_INVALID,       //无效
} PROCESS_TASK_GABAGE_TYPE_E;


/************************************************************************
  Function Declaration
 ************************************************************************/

/**
 * @fn      AIP_EXTERN HPR_INT32 aip_hw_watchdog_service_start(HPR_VOID)
 * @brief   开启硬件看门狗服务
 * @note    包括开启硬件看门狗休克检测和定时喂狗循环
 * @note    默认硬件看门狗休克时间为60 S
 * @note    默认硬件看门狗喂狗时间为2 S
 * @return  HPR_OK: success; other: fail
**/
AIP_EXTERN HPR_INT32 aip_hw_watchdog_service_start(HPR_VOID);

/**
 * @fn      AIP_EXTERN HPR_INT32 aip_hw_watchdog_service_stop(HPR_VOID)
 * @brief   关闭硬件看门狗服务
 * @note    关闭硬件看门狗后同时重置设置的看门狗休克时间和喂狗时间为默认配置
 * @return  HPR_OK: success; other: fail
**/
AIP_EXTERN HPR_INT32 aip_hw_watchdog_service_stop(HPR_VOID);

/**
 * @fn       AIP_EXTERN HPR_VOID aip_hw_watchdog_set_regular_diet(HPR_BOOL bEnable);
 * @brief    设置硬件看门狗是否停止周期性喂狗
 * @param[in] bEnable : HPR_TRUE:  恢复硬件看门狗周期性喂狗
 *                      HPR_FALSE: 停止周期性喂狗
 * @return  HPR_OK: success; other: fail
**/
AIP_EXTERN HPR_VOID aip_hw_watchdog_set_regular_diet(HPR_BOOL bEnable);

/**
 * @fn        AIP_EXTERN HPR_INT32 aip_hw_watchdog_set_shock_time(HPR_UINT32 dwTime)
 * @brief     关闭硬件看门狗休克时间（超过多久没喂狗会触发重启）
 * @param[in] dwTime: 设置的硬件看门狗休克时间（单位S）
 * @note      休克时间需要大于喂狗时间(2s)，否则报错
 * @return    HPR_OK: success; other: fail
**/
AIP_EXTERN HPR_INT32 aip_hw_watchdog_set_shock_time(HPR_UINT32 dwTime);

/**
 * @fn      AIP_EXTERN HPR_INT32 aip_soft_watchdog_service_start(HPR_VOID)
 * @brief   开启软件看门狗服务
 * @note    开启软件看门狗休克检测
 * @return  HPR_OK: success; other: fail
**/
AIP_EXTERN HPR_INT32 aip_soft_watchdog_service_start(HPR_VOID);

/**
 * @fn      AIP_EXTERN HPR_INT32 aip_soft_watchdog_service_stop(HPR_VOID)
 * @brief   关闭软件看门狗服务
 * @note    关闭软件看门狗服务后，同时会清空所有线程任务检测信息
 * @return  HPR_OK: success; other: fail
**/
AIP_EXTERN HPR_INT32 aip_soft_watchdog_service_stop(HPR_VOID);

/**
 * @fn      AIP_EXTERN HPR_INT32 aip_soft_watchdog_service_pause(HPR_VOID)
 * @brief   中断软件看门狗服务
 * @note    中断后不会再触发线程任务超时异常处理
 * @note    中断软件看门狗服务后，当前线程任务检测信息不清空，resume_soft_watchdog_service后将重新恢复
 * @return  HPR_OK: success; other: fail
 * @see     aip_soft_watchdog_service_resume
**/
AIP_EXTERN HPR_INT32 aip_soft_watchdog_service_pause(HPR_VOID);

/**
 * @fn      AIP_EXTERN HPR_INT32 aip_soft_watchdog_service_resume(HPR_VOID)
 * @brief   恢复软件看门狗服务
 * @return  HPR_OK: success; other: fail
**/
AIP_EXTERN HPR_INT32 aip_soft_watchdog_service_resume(HPR_VOID);

/**
 * @fn         AIP_EXTERN WDT_HANDLE aip_soft_watchdog_thread_task_register(HPR_INT8 *szName, HPR_UINT32 dwNameLen, HPR_UINT32 dwSharkTime, WATCH_DOG_RESTART_TASK_CALLBACK_FUN fnRestartFun)
 * @brief      向软件看门狗注册一个托管检测线程
 * @param[in]  szName: 模块名或线程名, 否则返回失败, see WDT_S_THREAD_NAME_LENGTH define
 * @param[in]  dwSharkPeriod: 设置的该任务休克时间（单位S）, 要求至少大于10S
 * @param[in]  fnRestartFun: 如果是一个非NULL值，则代表该服务支持一个重启接口。软件看门狗在检测到托管任务异常后，会先尝
 * 试调用重启接口重启服务，否则将进行重启当前进程。重启接口返回失败也会重启当前进程
 * @return     success: 任务handle; fail: NULL
**/
AIP_EXTERN WDT_HANDLE aip_soft_watchdog_thread_task_register(HPR_INT8 *szName, HPR_UINT32 dwSharkPeriod, WATCH_DOG_RESTART_TASK_CALLBACK_FUN fnRestartFun);

#define aip_soft_watchdog_task_register aip_soft_watchdog_thread_task_register

/**
 * @fn         AIP_EXTERN WDT_HANDLE aip_soft_watchdog_process_task_register(HPR_INT8 *szName, HPR_INT8 *szCmdName, WATCH_DOG_DETECT_TASK_CALLBACK_FUN fnDetectFun, WATCH_DOG_RESTART_TASK_CALLBACK_FUN fnRestartFun, PROCESS_TASK_GABAGE_TYPE_E eGarbageType)
 * @brief      向软件看门狗注册监测一个常驻进程
 * @param[in]  szName       : 模块名或进程名, see WDT_S_THREAD_NAME_LENGTH define
 * @param[in]  szCmdName    : 进程执行的命令(若有参数带参数, 常驻进程应该是一个带&字符的字符串，表示后台运行)
 * @param[in]  fnDetectFun  : 如果是一个非NULL值，则代表该服务自定义了一个检测进程在线接口，否则将采用默认的方式(kill)检
 * 测进程是否在线
 * @param[in]  fnRestartFun: 如果是一个非NULL值，则代表该服务支持一个重启接口。软件看门狗在检测到托管任务异常后,会尝试调
 * 用fnRestartFun进行重启服务，并释放当前task
 * @param[in]  eGarbageType: 默认进程任务释放类型,若fnRestartFun不为NULL, 按以下类型进行处理：
                                              //E_PROCESS_TASK_GARBAGE_TYPE_DROP: 任务监测到异常后抛异常后自动释放该task
                                              //E_PROCESS_TASK_GARBAGE_TYPE_RESTART: 任务监测到异常后将抛异常并重新调用byaCmd 拉起进程
 * @return     success: 任务handle; fail: NULL
**/
AIP_EXTERN WDT_HANDLE aip_soft_watchdog_process_task_register(HPR_INT8 *szName, HPR_INT8 *szCmdName, WATCH_DOG_DETECT_TASK_CALLBACK_FUN fnDetectFun, WATCH_DOG_RESTART_TASK_CALLBACK_FUN fnRestartFun, PROCESS_TASK_GABAGE_TYPE_E eGarbageType);

/**
 * @fn         AIP_EXTERN WDT_HANDLE aip_soft_watchdog_process_task_register_low_memory
 * @brief      向软件看门狗注册监测一个常驻进程(vfork启动子进程), 内存不够时使用
 * @param[in]  szName       : 模块名或进程名, see WDT_S_THREAD_NAME_LENGTH define
 * @param[in]  szCmdName    : 进程执行的命令(若有参数带参数, 常驻进程应该是一个带&字符的字符串，表示后台运行)
 * @param[in]  fnDetectFun  : 如果是一个非NULL值，则代表该服务自定义了一个检测进程在线接口，否则将采用默认的方式(kill)检
 * 测进程是否在线
 * @param[in]  fnRestartFun: 如果是一个非NULL值，则代表该服务支持一个重启接口。软件看门狗在检测到托管任务异常后,会尝试调
 * 用fnRestartFun进行重启服务，并释放当前task
 * @param[in]  eGarbageType: 默认进程任务释放类型,若fnRestartFun不为NULL, 按以下类型进行处理：
                                              //E_PROCESS_TASK_GARBAGE_TYPE_DROP: 任务监测到异常后抛异常后自动释放该task
                                              //E_PROCESS_TASK_GARBAGE_TYPE_RESTART: 任务监测到异常后将抛异常并重新调用byaCmd 拉起进程
 * @return     success: 任务handle; fail: NULL
**/
AIP_EXTERN WDT_HANDLE aip_soft_watchdog_process_task_register_low_memory(
    HPR_INT8 *szName, HPR_INT8 *szCmdName, WATCH_DOG_DETECT_TASK_CALLBACK_FUN fnDetectFun,
    WATCH_DOG_RESTART_TASK_CALLBACK_FUN fnRestartFun, PROCESS_TASK_GABAGE_TYPE_E eGarbageType);

/**
 * @fn         AIP_EXTERN WDT_HANDLE aip_soft_watchdog_process_task_register_with_pid(HPR_INT8 *szName, HPR_INT8 *szCmdName, WATCH_DOG_DETECT_TASK_CALLBACK_FUN fnDetectFun, WATCH_DOG_RESTART_TASK_CALLBACK_FUN fnRestartFun)
 * @brief      向软件看门狗注册监测一个已经运行的常驻进程
 * @param[in]  szName       : 模块名或进程名, see WDT_S_THREAD_NAME_LENGTH define
 * @param[in]  dwPid        : 进程pid
 * @param[in]  fnDetectFun  : 如果是一个非NULL值，则代表该服务自定义了一个检测进程在线接口，否则将采用默认的方式(kill)检
 * 测进程是否在线
 * @param[in]  fnRestartFun: 如果是一个非NULL值，则代表该服务支持一个重启接口。软件看门狗在检测到托管任务异常后,会尝试调
 * 用fnRestartFun进行重启服务，并释放当前task
 *                           如果是一个NULL值,   任务监测到异常后抛异常后自动释放该task
 * @return     success: 任务handle; fail: NULL
**/
AIP_EXTERN WDT_HANDLE aip_soft_watchdog_process_task_register_with_pid(HPR_INT8 *szName, HPR_INT32 dwPid, WATCH_DOG_DETECT_TASK_CALLBACK_FUN fnDetectFun, WATCH_DOG_RESTART_TASK_CALLBACK_FUN fnRestartFun);

/**
 * @fn         AIP_EXTERN HPR_INT32 aip_soft_watchdog_task_unregister(WDT_HANDLE hdlTask)
 * @brief      向软件看门狗注销一个托管检测线程任务
 * @param[in]  hdlTask: 要注销的任务handle
 * @return     HPR_OK: success; other: fail
**/
AIP_EXTERN HPR_INT32 aip_soft_watchdog_task_unregister(WDT_HANDLE hdlTask);

/**
 * @fn         AIP_EXTERN HPR_INT32 aip_soft_watchdog_thread_task_feed(WDT_HANDLE hdlTask)
 * @brief      托管检测线程任务进行喂狗
 * @param[in]  hdlTask: 要注销的任务handle
 * @return     HPR_OK: success; other: fail
**/
AIP_EXTERN HPR_INT32 aip_soft_watchdog_thread_task_feed(WDT_HANDLE hdlTask);

#define aip_soft_watchdog_task_feed aip_soft_watchdog_thread_task_feed

/**
 * @fn         AIP_EXTERN HPR_INT32 aip_soft_watchdog_tasks_show(HPR_VOID)
 * @brief      输出当前软件看门狗监测的状态
 * @return     HPR_OK: success; other: fail
**/
AIP_EXTERN HPR_INT32 aip_soft_watchdog_tasks_show(HPR_VOID);

#ifdef __cplusplus
}
#endif
#endif /* __AIP_WATCHDOG_H__ END */

