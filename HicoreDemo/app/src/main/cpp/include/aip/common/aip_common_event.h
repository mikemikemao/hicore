/**
 * @copyright  HangZhou Hikvision Digital Technology Co., Ltd. All Right Reserved.
 * @file       aip_common_event.h
 * @brief      订阅事件回调类型定义
**/

#ifndef __AIP_COMMON_EVENT_H__
#define __AIP_COMMON_EVENT_H__

/************************************************************************
 Included Header
 ************************************************************************/
#include "HPR_Types.h"

#ifdef __cplusplus
extern "C" {
#endif

/************************************************************************
 Macros
 ************************************************************************/
#define AIP_EVENT_CMD_E HPR_INT32

/************************************************************************
 Type Definition
 ************************************************************************/

/** @brief: 事件模块索引*/
typedef enum
{
    E_AIP_EVENT_MODULE_EXCEPTION       = 0,  // 异常管理模块, 对应的AIP_EVENT_CMD_E见 EXCEPTION_EVENT_CMD_E 定义
    E_AIP_EVENT_MODULE_NET             = 1,  // 网络管理模块，对应的AIP_EVENT_CMD_E见 NET_EVENT_CMD_E 定义
    E_AIP_EVENT_MODULE_TIME            = 2,  // 时间管理模块，对应的AIP_EVENT_CMD_E见 TIME_EVENT_CMD_E 定义
    E_AIP_EVENT_MODULE_SECURITY        = 3,  // 安全管理模块，对应的AIP_EVENT_CMD_E见 SECURITY_EVENT_CMD_E 定义
    E_AIP_EVENT_MODULE_DEV_BLUETOOTH   = 4,  // 蓝牙管理模块，对应的AIP_EVENT_CMD_E见 BLUETOOTH_EVENT_CMD_E 定义
    E_AIP_EVENT_MODULE_APP             = 5,  // APP管理模块，对应的AIP_EVENT_CMD_E见  APP_EVENT_CMD_E 定义
} AIP_EVENT_MODULE_E;


/** @brief: 事件 回调参数*/
typedef struct
{
    AIP_EVENT_MODULE_E  eModule;              // [in],  event的模块
    AIP_EVENT_CMD_E     eCmd;                 // [in],  具体event
    HPR_VOID*           pstInParam;           // [in],  入参结构体指针
    HPR_UINT32          dwInSize;             // [in],  入参结构体大小
    HPR_VOID*           pstOutParam;          // [out], 出参结构体指针
    HPR_UINT32          dwOutSize;            // [in],  出参结构体大小
} AIP_EVENT_CALLBACK_PARAM_T, *AIP_EVENT_CALLBACK_PARAM_P;

/**
 * @brief  aip服务回调接口类型
 * @param  see AIP_EVENT_CALLBACK_PARAM_P define
 * @return HPR_OK: success; other:fail
**/
typedef HPR_INT32(*AIP_EVENT_CALLBACK_FUN)(AIP_EVENT_CALLBACK_PARAM_P pstParam);

/************************************************************************
 Function Declaration
 ************************************************************************/

#ifdef __cplusplus
}
#endif
#endif /* __AIP_COMMON_EVENT_H__ END */
