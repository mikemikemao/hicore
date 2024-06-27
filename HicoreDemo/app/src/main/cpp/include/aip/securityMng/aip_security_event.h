/**
 * @copyright HangZhou Hikvision Digital Technology Co., Ltd. All Right Reserved.
 * @file      aip_security_event.h
 * @brief     用户安全相关的一些基础接口
**/

#ifndef __AIP_SECURITY_EVENT_H__
#define __AIP_SECURITY_EVENT_H__

/************************************************************************
 Included Header
 ************************************************************************/
#include "common/aip_common.h"
#include "common/aip_common_event.h"
#include "HPR_Addr.h"


#ifdef __cplusplus
extern "C"{
#endif



/************************************************************************
 Macros
 ************************************************************************/

/************************************************************************
 Type Definition
 ************************************************************************/

/**
 * @brief 安全模块AIP_EVENT_CMD_E索引
 * @note AIP_EVENT_MODULE_E为 E_AIP_EVENT_MODULE_SECURITY
**/
typedef enum
{
    E_SECURITY_EVENT_LOCK           = 0,  // 触发锁定
                                      //入参:SECURITY_LOCK_TRIGGER_INFO_P, 锁定信息
                                      //出参:NULL
                                      //返回值: HPR_OK
                                      //        HPR_FALSE
    E_SECURITY_EVENT_UNLOCK         = 1,  // 触发解锁(仅锁定时间到触发的解锁会抛回调)，调用任何主动解锁的接口都不会触发该回调
                                      //入参:SECURITY_LOCK_TRIGGER_INFO_P, 解锁信息
                                      //出参:NULL
                                      //返回值: HPR_OK
                                      //        HPR_FALSE
} SECURITY_EVENT_CMD_E;


/**
 * @brief : 触发锁定/认证的类型
 */
typedef enum
{
    E_SECURITY_LOCK_TYPE_LOGIN      = 0,  // 登录,修改参数类型
    E_SECURITY_LOCK_TYPE_FORGET_PWD = 1,  // 忘记密码找回密码类型
    E_SECURITY_LOCK_TYPE_OPERATE    = 2,  // 操作锁定，具体操作类型用户自定义
    E_SECURITY_LOCK_TYPE_INVALID,         // 非法参数类型
} SECURITY_LOCK_TYPE_E;

/**
 * @brief    : 锁定配置类型
 */
typedef struct
{
    SECURITY_LOCK_TYPE_E eTriggerType;         /* 触发的类型 */
    HPR_BOOL bLocal;                           /* 是否本地登录 */
    HPR_BOOL bAdmin;                           /* 是否管理员用户 */
} SECURITY_LOCK_CONFIG_TYPE_T, *SECURITY_LOCK_CONFIG_TYPE_P;

/**
 * @brief    : 锁定配置信息
 */
typedef struct
{
    SECURITY_LOCK_CONFIG_TYPE_T stBaseInfo;

    HPR_UINT32 dwFailThreshold;  /* 触发锁定的次数阈值 */
    time_t     dwResumePeriod;   /* 试错次数要保留的时间, 秒数 */
    time_t     dwLockPeriod;     /* 总锁定时间, 秒数 */
} SECURITY_LOCK_DETAIL_CONFIG_T, *SECURITY_LOCK_DETAIL_CONFIG_P;


/**
 * @brief    : 触发获取锁定信息或认证结果的信息
 * @note     : 当触发类型是E_SECURITY_LOCK_TYPE_OPERATE时，仅关注szUserName和szOperateName即可，如果不关注用户类型，则szUserName置空
 */
typedef struct
{
    SECURITY_LOCK_TYPE_E eTriggerType;                     /* 触发的类型, 不同锁定类型独立维护一份锁定信息*/
    HPR_BOOL             bLocal;                           /* 是否本地登录, 远程和本地各自独立维护一份锁定信息*/
    HPR_BOOL             bAdmin;                           /* 是否管理员用户, 会影响不同的锁定次数, 该值仅在第一次触发失败时,起到设置最大锁定次数的作用。
                                                              不会作为查找锁定信息的依据 */
    HPR_BOOL             bLockDev;                         /* 是否锁定设备,  锁定设备的类型,不再关注用户名和ip信息
                                                              比如锁定阶段，无论按个ip操作,都返回锁定*/
    HPR_INT8             szUserName[USER_NAME_LEN];        /* 本地和远程都可以传递用户名区分锁定信息，若不区分用户名，可以置空 */
    HPR_INT8             szOperateName[OPERATE_NAME_LEN];  /* 关键操作定义，当 eTriggerType 为 E_SECURITY_LOCK_TYPE_OPERATE 时有效  */
    HPR_ADDR_T           stRemoteAddr;                     /* 远程需要增加ip 触发请求的客户端ip, 本地类型不关心该参数，请置空*/
} SECURITY_LOCK_TRIGGER_INFO_T, *SECURITY_LOCK_TRIGGER_INFO_P;

/**
 *  @brief 异常服务回调
 */
typedef AIP_EVENT_CALLBACK_FUN SECURITY_EVENT_CALLBACK_FUN ;


/************************************************************************
  Function Declaration
 ************************************************************************/


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif //__AIP_SECURITY_EVENT_H__ end
