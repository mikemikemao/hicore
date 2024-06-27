/**
 * @note     HangZhou Hikvision Digital Technology Co., Ltd. All Right Reserved.
 * @file     aip_security_lock_manage.h
 * @brief    用户安全锁定管理 
 */
#ifndef __AIP_SECURITY_LOCK_MANAGE__
#define __AIP_SECURITY_LOCK_MANAGE__

/************************************************************************
 Included Header
 ************************************************************************/
#include "HPR_Addr.h"
#include "lstLib.h"

#include "aip_security_event.h"
#include "common/aip_common.h"

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
 * @brief    : 还未锁定的计次信息
 */
typedef struct
{
    HPR_UINT32 dwRetryCount;           /* 当前剩余试错次数 */
    time_t     dwResumePeriod;         /* 试错次数要保留的时间, 秒数 */
    time_t     dwResumeWhenTimeUp;     /* 试错次数清零时间, 距离开机启动的秒数（掉电失效，因此每次上电要根据dwResumeWhenTimeUtc重新获取） */
    time_t     dwResumeWhenTimeUtc;    /* 试错次数清零时间, UTC时间(受校时影响,因此每次校时要根据dwResumeWhenTimeUp更新） */
    time_t     dwFailLastTimeUtc;      /* 上次认证失败时间, UTC时间(校时时不更新)*/
} SECURITY_LOCK_RETRY_COUNT_INFO_T, *SECURITY_LOCK_RETRY_COUNT_INFO_P;

/**
 * @brief    : 已锁定的倒计时信息
 */
typedef struct
{
    time_t dwLockPeriod;         /* 总锁定时间, 秒数 */
    time_t dwLockUtilTimeUp;     /* 解锁时间, 距离开机启动的秒数（掉电失效，因此每次上电要根据dwLockUtilTimeUtc重新获取） */
    time_t dwLockUtilTimeUtc;    /* 解锁时间, UTC时间(受校时影响,因此每次校时要根据dwLockUtilTimeUp更新） */
    time_t dwLockTimeUtc;        /* 锁定时间, UTC时间(校时时不更新)*/
} SECURITY_LOCK_UNLOCK_COUNT_DOWN_INFO_T, *SECURITY_LOCK_UNLOCK_COUNT_DOWN_INFO_P;

typedef union
{
    SECURITY_LOCK_RETRY_COUNT_INFO_T       stRetryCount;        // 试错次数 信息, 未锁定时，有效
    SECURITY_LOCK_UNLOCK_COUNT_DOWN_INFO_T stUnlockCountDown;   // 锁定倒计时信息,已经锁定时有效
} SECURITY_LOCK_COUNT_INFO_U;

/**
 * @brief    : 触发获取锁定信息或认证结果的信息
 */
typedef struct
{
    SECURITY_LOCK_TRIGGER_INFO_T stBaseInfo;

    HPR_BOOL bIsLocked;          /* 锁定状态，是否锁定 */
    HPR_UINT32 dwFailThreshold;  /* 触发锁定的次数阈值 */
    SECURITY_LOCK_COUNT_INFO_U   unCountInfo;

    HPR_BOOL (* security_lock_info_equals)(SECURITY_LOCK_TRIGGER_INFO_T *pstToCompare, SECURITY_LOCK_TRIGGER_INFO_T *pstCompare);  /* 触发信息比较接口回调 */
} SECURITY_LOCK_DETAIL_INFO_T, *SECURITY_LOCK_DETAIL_INFO_P;

//锁定信息
typedef struct
{
    NODE node;                       /*链表节点*/
    SECURITY_LOCK_DETAIL_INFO_T stInfo;
} SECURITY_USER_LOCK_DETAILS_INFO_NODE_T, *SECURITY_USER_LOCK_DETAILS_INFO_NODE_P;

typedef LIST SECURITY_USER_LOCK_INFO_LIST;         /* 当前锁定的每个信息列表, 每个链表节点结构体为 SECURITY_USER_LOCK_DETAILS_INFO_NODE_P*/




/************************************************************************
 Function Declaration
 ************************************************************************/

/**
 * @fn      AIP_EXTERN HPR_INT32 aip_security_user_lock_manage_service_start(SECURITY_EVENT_CALLBACK_FUN fnCbFun)
 * @brief   用户锁定服务开启
 * @param[in] fnCbFun, 回调函数,允许为NULL
 * @return  HPR_OK:success; other:fail
 */
AIP_EXTERN HPR_INT32 aip_security_user_lock_manage_service_start(SECURITY_EVENT_CALLBACK_FUN fnCbFun);

/**
 * @fn      AIP_EXTERN HPR_INT32 aip_security_user_lock_manage_service_stop(HPR_VOID)
 * @brief   用户锁定服务关闭
 * @return  HPR_OK:success; other:fail
 */
AIP_EXTERN HPR_INT32 aip_security_user_lock_manage_service_stop(HPR_VOID);

/**
 * @fn        AIP_EXTERN HPR_INT32 aip_security_lock_get_config(HPR_VOID)
 * @brief     获取当前ip锁定配置
 * @param [in], 要解锁的类型
 * @return    HPR_OK: 解锁成功; other:解锁失败
**/
AIP_EXTERN HPR_INT32 aip_security_lock_get_config(SECURITY_LOCK_CONFIG_TYPE_P pstTypeInfo, SECURITY_LOCK_DETAIL_CONFIG_P pstDetailConfig);

/**
 * @fn        AIP_EXTERN HPR_INT32 aip_security_lock_set_config(HPR_VOID)
 * @brief     设置当前ip锁定配置
 * @param     [in], 要解锁的类型
 * @return    HPR_OK: 解锁成功; other:解锁失败
 * @note      暂未实现
**/
AIP_EXTERN HPR_INT32 aip_security_lock_set_config(SECURITY_LOCK_DETAIL_CONFIG_P pstDetailConfig);

/**
 * @fn        AIP_EXTERN HPR_INT32 aip_security_lock_auth_fail(SECURITY_LOCK_TRIGGER_INFO_P pstInfo
 * @brief     非法登录时，更新数据
 * @param[in] pstUser : 用户锁定信息
 * @return     HPR_OK: success; other:fail
**/
AIP_EXTERN HPR_INT32 aip_security_lock_auth_fail(SECURITY_LOCK_TRIGGER_INFO_P pstInfo);

/**
 * @fn        AIP_EXTERN HPR_INT32 aip_security_lock_auth_success(SECURITY_LOCK_TRIGGER_INFO_P pstInfo
 * @brief     合法登录时，更新数据
 * @param[in] pstUser : 用户锁定信息
 * @return     HPR_OK: success; other:fail
**/
AIP_EXTERN HPR_INT32 aip_security_lock_auth_success(SECURITY_LOCK_TRIGGER_INFO_P pstInfo);

/**
 * @fn      AIP_EXTERN SECURITY_USER_LOCK_INFO_LIST* aip_security_user_lock_get_lock_info_list(HPR_VOID)
 * @brief   获取当前锁定信息列表
 * @return  success: wifi ap任店链表, 返回的链表声明周期结束后，需要显示的调用aip_security_user_release_lock_info_list 释放
 *          fail   : NULL
 */
AIP_EXTERN SECURITY_USER_LOCK_INFO_LIST* aip_security_user_lock_get_lock_info_list(HPR_VOID);

/**
 * @fn         AIP_EXTERN HPR_INT32 aip_security_user_release_lock_info_list(SECURITY_USER_LOCK_INFO_LIST* pList)
 * @brief      释放锁定信息链表
 * @param [in] pList： 要释放的链表地址
 * @return     HPR_OK: success; other:fail
**/
AIP_EXTERN HPR_INT32 aip_security_user_release_lock_info_list(SECURITY_USER_LOCK_INFO_LIST* pList);

/**
 * @fn        AIP_EXTERN HPR_INT32 aip_security_lock_get_lock_info(SECURITY_LOCK_TRIGGER_INFO_P pstInfo, SECURITY_LOCK_DETAIL_INFO_P pstDetailInfo)
 * @brief     获取指定的用户/ip锁定信息
 * @param[in] pstUser : 用户锁定信息
 * @param[out] pstDetailInfo : 用户锁定详细信息
 * @return     HPR_OK: success; other:fail
**/
AIP_EXTERN HPR_INT32 aip_security_lock_get_lock_info(SECURITY_LOCK_TRIGGER_INFO_P pstInfo, SECURITY_LOCK_DETAIL_INFO_P pstDetailInfo);

/**
 * @fn        AIP_EXTERN HPR_BOOL aip_security_lock_check_lock(SECURITY_LOCK_TRIGGER_INFO_P pstInfo)
 * @brief     校验指定用户/ip是否锁定
 * @param[in] pstUser : 用户锁定信息
 * @param[out] pstDetailInfo : 用户锁定详细信息
 * @return     HPR_TRUE: 锁定; HPR_FALSE:未锁定
**/
AIP_EXTERN HPR_BOOL aip_security_lock_check_lock(SECURITY_LOCK_TRIGGER_INFO_P pstInfo);

/**
 * @fn        AIP_EXTERN HPR_INT32 aip_security_lock_clear_by_info(SECURITY_LOCK_TRIGGER_INFO_P pstInfo)
 * @brief     指定用户/ip解锁
 * @param[in] pstUser : 用户锁定信息
 * @return    HPR_OK: 解锁成功; other:解锁失败
 * @note      没找到锁定信息也视解锁失败
 * @note      存在试错次数但是还未锁定的，将清空锁定信息
**/
AIP_EXTERN HPR_INT32 aip_security_lock_clear_by_info(SECURITY_LOCK_TRIGGER_INFO_P pstInfo);

/**
 * @fn        AIP_EXTERN HPR_INT32 aip_security_lock_clear_all_remote(HPR_VOID)
 * @brief     清空所有远程锁定信息
 * @return     HPR_OK: 解锁成功; other:解锁失败
**/
AIP_EXTERN HPR_INT32 aip_security_lock_clear_all_remote(HPR_VOID);

/**
 * @fn        AIP_EXTERN HPR_INT32 aip_security_lock_clear_all_local(HPR_VOID)
 * @brief     清空本地远程锁定信息
 * @return    HPR_OK: 解锁成功; other:解锁失败
**/
AIP_EXTERN HPR_INT32 aip_security_lock_clear_all_local(HPR_VOID);

/**
 * @fn        AIP_EXTERN HPR_INT32 aip_security_lock_unlock_all_user(HPR_VOID)
 * @brief     清空所有锁定信息
 * @return     HPR_OK: 解锁成功; other:解锁失败
**/
AIP_EXTERN HPR_INT32 aip_security_lock_clear_all_info(HPR_VOID);

/**
 * @fn        AIP_EXTERN HPR_INT32 aip_security_lock_clear_all_by_type(SECURITY_LOCK_TYPE_E eType)
 * @brief     将指定类型的锁定信息都清空
 * @param [in], 要解锁的类型
 * @return    HPR_OK: 解锁成功; other:解锁失败
**/
AIP_EXTERN HPR_INT32 aip_security_lock_clear_all_by_type(SECURITY_LOCK_TYPE_E eType);

#ifdef __cplusplus
}
#endif
#endif /* __AIP_SECURITY_LOCK_MANAGE__ END */
