/**
 * @copyright HangZhou Hikvision Digital Technology Co., Ltd. All Right Reserved.
 * @file      net_cellular_mobile.h
**/

#ifndef __AIP_NET_CELLULAR_MOBILE_H__
#define __AIP_NET_CELLULAR_MOBILE_H__

/************************************************************************
 Included Header
 ************************************************************************/
#include "common/aip_common.h"
#include "netMng/aip_net_common.h"

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
 * @brief: 当前蜂窝网络开关状态
**/
typedef enum
{
    E_CELLULAR_STATUS_CLOSED  = 0,      // 关闭
    E_CELLULAR_STATUS_OPEN    = 1,      // 开启
    E_CELLULAR_STATUS_INVALID,          // 非法类型
} NET_CELLULAR_STATUS_E;

/**
 * @brief: 当前蜂窝网络sim卡状态
**/
typedef enum
{
    E_CELLULAR_SIM_STATUS_ONLINE  = 0,      // sim连接正常
    E_CELLULAR_SIM_STATUS_OFFLINE = 1,      // sim连接异常
    E_CELLULAR_SIM_STATUS_INVALID,          // 非法类型
} NET_CELLULAR_SIM_STATUS_E;

/**
 * @brief: 当前蜂窝网络流量状态
**/
typedef enum
{
    E_CELLULAR_CONNECT_STATUS_ONLINE  = 0,      // 蜂窝网络流量在线
    E_CELLULAR_CONNECT_STATUS_OFFLINE = 1,      // 蜂窝网络流量不在线
    E_CELLULAR_CONNECT_STATUS_INVALID,          // 非法类型
} NET_CELLULAR_CONNECT_STATUS_E;

/**
 * @brief: 当前蜂窝网络拨号类型状态
**/
typedef enum
{
    E_CELLULAR_CONNECT_NET_TYPE_2G  = 0,      // 2g
    E_CELLULAR_CONNECT_NET_TYPE_3G  = 1,      // 3g
    E_CELLULAR_CONNECT_NET_TYPE_4G  = 2,      // 4g
    E_CELLULAR_CONNECT_NET_TYPE_5G  = 3,      // 5g
    E_CELLULAR_CONNECT_NET_TYPE_INVALID,      // 非法类型
} NET_CELLULAR_CONNECT_NET_TYPE_E;

typedef struct
{
    HPR_INT8 byaName[128];     // 设置名称 (title, 自定义用于展示的名称)
    HPR_INT8 byaAPN[128];      // Apn名称 (如ctnet等Apn名称)
    HPR_INT8 byaUserName[128]; // Apn连接用户名
    HPR_INT8 byaUserPwd[128];  // Apn连接密码
} AIP_NET_CELLULAR_APN_PARAM_T, *AIP_NET_CELLULAR_APN_PARAM_P;

/************************************************************************
  Function Declaration
 ************************************************************************/

/**
 * @fn       AIP_EXTERN HPR_INT32 aip_net_cellular_open(HPR_VOID)
 * @brief    打开蜂窝移动网络
 * @return   HPR_OK: success； other:fail
 **/
AIP_EXTERN HPR_INT32 aip_net_cellular_open(HPR_VOID);

/**
 * @fn       AIP_EXTERN HPR_INT32 aip_net_cellular_close(HPR_VOID)
 * @brief    关闭蜂窝移动网络
 * @return   HPR_OK: success； other:fail
 **/
AIP_EXTERN HPR_INT32 aip_net_cellular_close(HPR_VOID);

/**
 * @fn:		aip_net_cellular_apn_param_update
 * @brief:  触发一次蜂窝APN配置参数更新, 更新时将会通过E_NET_EVENT_CELLULAR_APN_CONFIG_UPDATE回调通知
 * @param:
 *          HPR_VOID - NA
 * @return: AIP_EXTERN HPR_INT32 HPR_OK/HPR_ERROR
 * @author: xiaoxinyu
 */
AIP_EXTERN HPR_INT32 aip_net_cellular_apn_param_update(HPR_VOID);

/**
 * @fn:		aip_net_cellular_get_apn_param
 * @brief:  获取当前蜂窝APN配置参数, E_NET_EVENT_CELLULAR_APN_CONFIG_UPDATE回调触发后再调用该接口
 * @param:
 *          AIP_NET_CELLULAR_APN_PARAM_T *pstApnParam - [OUT] APN配置参数
 * @return: HPR_INT32 HPR_OK/HPR_ERROR
 * @author: xiaoxinyu
 */

AIP_EXTERN HPR_INT32 aip_net_cellular_get_apn_param(AIP_NET_CELLULAR_APN_PARAM_T *pstApnParam);
/**
 * @fn        AIP_EXTERN HPR_INT32 aip_net_cellular_set_apn_param(AIP_NET_CELLULAR_APN_PARAM_P pstParam)
 * @brief     设置apn参数（当使用一些不常用的apn连接方式时，需要设置自定义参数,已解决系统不支持识别的问题）
 * @param[in] pstParam: see AIP_NET_CELLULAR_APN_PARAM_P define
 * @return    HPR_OK: success； other:fail
 **/
AIP_EXTERN HPR_INT32 aip_net_cellular_set_apn_param(AIP_NET_CELLULAR_APN_PARAM_P pstParam);

/**
 * @fn        AIP_EXTERN HPR_INT32 aip_net_cellular_del_apn_param(HPR_INT8* szName;
 * @brief     通过自定义展示的名称删除apn参数（同AIP_NET_CELLULAR_APN_PARAM_P 中的byaName）
 * @param[in] szName, 要删除的名称， （即aip_net_cellular_set_apn_param 中AIP_NET_CELLULAR_APN_PARAM_P 中的byaName）
 * @return    HPR_OK: success； other:fail
 **/
AIP_EXTERN HPR_INT32 aip_net_cellular_del_apn_param(HPR_INT8* szName);

/**
 * @fn        AIP_EXTERN HPR_INT32 aip_net_cellular_select_apn_param(HPR_INT8* szName;
 * @brief     通过自定义展示的名称选择apn参数（同AIP_NET_CELLULAR_APN_PARAM_P 中的byaName）
 * @param[in] szName, 要选择的名称， （即aip_net_cellular_set_apn_param 中AIP_NET_CELLULAR_APN_PARAM_P 中的byaName）
 * @return    HPR_OK: success； other:fail
 **/
AIP_EXTERN HPR_INT32 aip_net_cellular_select_apn_param(HPR_INT8* szName);

/**
 * @fn       AIP_EXTERN HPR_INT32 aip_net_cellular_status_update(HPR_VOID)
 * @brief    触发一次蜂窝移动网络开关状态更新, 更新时将会通过E_NET_EVENT_CELLULAR_STATUS_UPDATE 回调更新
 * @return HPR_OK: success； other:fail
 **/
AIP_EXTERN HPR_INT32 aip_net_cellular_status_update(HPR_VOID);

/**
 * @fn       AIP_EXTERN NET_CELLULAR_STATUS_E aip_net_cellular_status_get(HPR_VOID);
 * @brief    获取蜂窝移动网络开关状态
 * @return   开关状态, sed NET_CELLULAR_STATUS_E define
 **/
AIP_EXTERN NET_CELLULAR_STATUS_E aip_net_cellular_status_get(HPR_VOID);

/**
 * @fn       AIP_EXTERN HPR_INT32 aip_net_cellular_sim_status_update(HPR_VOID)
 * @brief    触发一次蜂窝移动网络SIM状态更新, 更新时将会通过E_NET_EVENT_CELLULAR_SIM_STATUS_UPDATE 回调更新
 * @return HPR_OK: success； other:fail
 **/
AIP_EXTERN HPR_INT32 aip_net_cellular_sim_status_update(HPR_VOID);

/**
 * @fn       AIP_EXTERN NET_CELLULAR_SIM_STATUS_E aip_net_cellular_sim_status_get(HPR_VOID)
 * @brief    获取蜂窝移动网络SIM卡开关状态
 * @return   开关状态, sed NET_CELLULAR_SIM_STATUS_E define
 **/
AIP_EXTERN NET_CELLULAR_SIM_STATUS_E aip_net_cellular_sim_status_get(HPR_VOID);

/**
 * @fn       AIP_EXTERN HPR_INT32 aip_net_cellular_connect_type_update(HPR_VOID)
 * @brief    触发一次蜂窝网络连接类型更新, 更新时将会通过E_NET_EVENT_CELLULAR_CONNECT_TYPE_UPDATE 回调更新
 * @return HPR_OK: success； other:fail
 **/
AIP_EXTERN HPR_INT32 aip_net_cellular_connect_type_update(HPR_VOID);

/**
 * @fn       AIP_EXTERN NET_CELLULAR_CONNECT_NET_TYPE_E aip_net_cellular_connect_type_get(HPR_VOID)
 * @brief    获取蜂窝移动网络拨号类型
 * @return   开关状态, sed NET_CELLULAR_CONNECT_NET_TYPE_E define
 **/
AIP_EXTERN NET_CELLULAR_CONNECT_NET_TYPE_E aip_net_cellular_connect_type_get(HPR_VOID);

/**
 * @fn       AIP_EXTERN HPR_INT32 aip_net_cellular_signal_level_update(HPR_VOID)
 * @brief    触发一次蜂窝网络信号强度更新, 更新时将会通过E_NET_EVENT_CELLULAR_SIGNAL_LEVEL_UPDATE 回调更新
 * @return HPR_OK: success； other:fail
 **/
AIP_EXTERN HPR_INT32 aip_net_cellular_signal_level_update(HPR_VOID);

/**
 * @fn       AIP_EXTERN HPR_INT32 aip_net_cellular_signal_level_get(HPR_VOID)
 * @brief    获取蜂窝移动网络信号等级
 * @return   信号等级
 **/
AIP_EXTERN HPR_INT32 aip_net_cellular_signal_level_get(HPR_VOID);

/**
 * @fn       AIP_EXTERN NET_CELLULAR_CONNECT_STATUS_E aip_net_cellular_connect_status_get(HPR_VOID)
 * @brief    获取蜂窝移动网络sim卡开关状态
 * @return   开关状态, sed NET_CELLULAR_CONNECT_STATUS_E define
 **/
AIP_EXTERN NET_CELLULAR_CONNECT_STATUS_E aip_net_cellular_connect_status_get(HPR_VOID);

/**
 * @fn       AIP_EXTERN NET_INTERFACE_CARD_E aip_net_cellular_nic_get(HPR_VOID)
 * @brief    获取当前蜂窝网络网卡枚举
 * @return   网卡, sed NET_INTERFACE_CARD_E define
 **/
AIP_EXTERN NET_INTERFACE_CARD_E aip_net_cellular_nic_get(HPR_VOID);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif //__AIP_NET_CELLULAR_MOBILE_H__ end
