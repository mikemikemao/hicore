/**
 * @copyright HangZhou Hikvision Digital Technology Co., Ltd. All Right Reserved.
 * @file      aip_net_mng.h
 * @brief     网络通信模块
**/
#ifndef __AIP_NET_MNG_H__
#define __AIP_NET_MNG_H__

/************************************************************************
 Included Header
 ************************************************************************/
#include "common/aip_common.h"
#include "common/aip_common_event.h"
#include "netMng/interface/aip_net_config.h"
#include "netMng/interface/aip_net_ip_link.h"
#include "netMng/wifi/aip_net_wifi.h"
#include "aip_build_config.h"


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
 * @brief 网络模块AIP_EVENT_CMD_E索引
 * @note AIP_EVENT_MODULE_E为 E_AIP_EVENT_MODULE_NET
**/
typedef enum
{
    E_NET_EVENT_STATUS_BROKEN       = 0,  //网卡网络断开
                                      //入参:NET_INTERFACE_CARD_E*, 网卡索引值
                                      //出参:NULL
                                      //返回值: HPR_OK
                                      //        HPR_FALSE
    E_NET_EVENT_STATUS_RESUME       = 1,  //网卡网络恢复
                                      //入参:NET_INTERFACE_CARD_E*, 网卡索引值
                                      //出参:NULL
                                      //返回值: HPR_OK
                                      //        HPR_FALSE
    E_NET_EVENT_STATUS_CONFLICT     = 2,//网卡网络地址冲突
                                      //入参:NET_EVENT_CONFILIT_MSG_P, 冲突的网卡网络信息
                                      //出参:NULL
                                      //返回值: HPR_OK
                                      //        HPR_FALSE
    E_NET_EVENT_DHCPC_GET_SUCCESS   = 3,//网卡dhcp成功
                                      //入参:NET_DHCPC_STATUS_P, dhcp信息
                                      //出参:NULL
                                      //返回值: HPR_OK
                                      //        HPR_FALSE
    E_NET_EVENT_WIFI_CONNECT_STATUS_UPDATE  = 4,// 底层wifi状态信息更新
                                        // 表示其他客户端或外部驱动对底层wifi状态进行了变更，收到该回调
                                        // 可主动调用aip_net_wifi_get_connect_status_info 获取最新wifi状态
                                      //入参:NULL
                                      //出参:NULL
                                      //返回值: HPR_OK
                                      //        HPR_FALSE
    E_NET_EVENT_WIFI_AP_LIST_UPDATE  = 5,//  wifi热点信息 更新
                                        // 表示wifi 热点信息有所更新，
                                        // 可主动调用aip_net_wifi_get_networks_list 获取最新ap 热点列表
                                        //入参:NULL
                                        //出参:NULL
                                        //返回值: HPR_OK
                                        //        HPR_FALSE
    E_NET_EVENT_INTERFACE_INFO_UPDATE = 6,//  网卡ip信息 更新(ip配置方式、ip地址、子网掩码、网关地址、dns 更新都会触发该回调)
                                        // 可主动调用aip_net_get_ip_cfg_mode、aip_net_get_ip_info、aip_net_get_gateway、aip_net_get_dns 获取当前网络配置方式和ip网关信息以及dns
                                        //入参:NET_INTERFACE_CARD_E*, 更新了状态的网卡索引值
                                        //出参:NULL
                                        //返回值: HPR_OK
                                        //        HPR_FALSE
    E_NET_EVENT_CELLULAR_STATUS_UPDATE = 7,//  蜂窝网络状态 更新
                                        // 可主动调用aip_net_cellular_status_get 获取当前蜂窝网络状态
                                        //入参:NULL
                                        //出参:NULL
                                        //返回值: HPR_OK
                                        //        HPR_FALSE
    E_NET_EVENT_STATUS_RESUME_NOCONFLICT = 8,//网卡网络地址从冲突恢复到不冲突状态
                                             //网卡的所有网络地址均为不冲突状态还视为网卡的不冲突状态
                                      //入参:NET_EVENT_RESUME_NOCONFLICT_MSG_P, 网卡信息
                                      //出参:NULL
                                      //返回值: HPR_OK
                                      //        HPR_FALSE
    E_NET_EVENT_CELLULAR_SIM_STATUS_UPDATE = 9,//  蜂窝网络SIM状态 更新
                                        // 可主动调用aip_net_cellular_sim_status_get 获取当前蜂窝网络SIM状态
                                        //入参:NULL
                                        //出参:NULL
                                        //返回值: HPR_OK
                                        //        HPR_FALSE
    E_NET_EVENT_INTERFACE_CONFIG_UPDATE = 10,//  网卡ipv4配置信息 更新(ip配置方式、ip地址、子网掩码、网关地址、dns 配置更新都会触发该回调)
                                             //  注意与E_NET_EVENT_INTERFACE_INFO_UPDATE(表示网卡状态已经变化)区分，该枚
                                             //  举仅代表配置进行了更新，状态不一定已经更新
                                        //入参:NET_INTERFACE_IF_AND_DNS_PARAM_P, 更新了状态的网卡索引值
                                        //注意仅IP配置方式为静态时，其中的ip、子网掩码、网关地址有效
                                        //    仅Dns配置方式为手动时，其中的dns参数有效
                                        //出参:NULL
                                        //返回值: HPR_OK
                                        //        HPR_FALSE
#if (defined(SUP_IPV6_CONFIG) && (SUP_IPV6_CONFIG))
    E_NET_EVENT_INTERFACE_CONFIG_UPDATE_IPV6 = 11,//  网卡ipv6配置信息 更新(ip配置方式、ip地址、子网掩码、网关地址、dns 配置更新都会触发该回调)
                                             //  注意与E_NET_EVENT_INTERFACE_INFO_UPDATE(表示网卡状态已经变化)区分，该枚
                                             //  举仅代表配置进行了更新，状态不一定已经更新
                                        //入参:NET_INTERFACE_IF_AND_DNS_PARAM_P, 更新了状态的网卡索引值
                                        //注意仅IP配置方式为静态时，其中的ip、子网掩码、网关地址有效
                                        //    仅Dns配置方式为手动时，其中的dns参数有效
                                        //出参:NULL
                                        //返回值: HPR_OK
                                        //        HPR_FALSE
#endif // #if (defined(SUP_IPV6_CONFIG) && (SUP_IPV6_CONFIG))

    E_NET_EVENT_CELLULAR_CONNECT_TYPE_UPDATE = 12,//  蜂窝网络链接类型 更新
                                        // 可主动调用aip_net_cellular_connect_type_get 获取当前蜂窝网络连接类型
                                        //入参:NULL
                                        //出参:NULL
                                        //返回值: HPR_OK
                                        //        HPR_FALSE
    E_NET_EVENT_CELLULAR_SIGNAL_LEVEL_UPDATE = 13,//  蜂窝网络信号强度 更新
                                        // 可主动调用aip_net_cellular_signal_level_get 获取当前蜂窝网络信号强度
                                        //入参:NULL
                                        //出参:NULL
                                        //返回值: HPR_OK
                                        //        HPR_FALSE
    E_NET_EVENT_WIFI_AP_STATUS_UPDATE = 14, // WiFi AP模式状态更新
                                            // 可主动调用aip_net_wifi_get_ap_status 获取当前WiFi AP状态
                                            // 入参: NULL
                                            // 出参: NULL
                                            // 返回值: HPR_OK/HPR_ERROR
    E_NET_EVENT_CELLULAR_APN_PARAM_UPDATE = 15, // 蜂窝网络APN配置更新
                                            // 可主动调用aip_net_cellular_get_apn_param 获取当前APN配置
                                            // 入参: NULL
                                            // 出参: NULL
                                            // 返回值: HPR_OK/HPR_ERROR
} NET_EVENT_CMD_E;


/**
 * @note AIP_EVENT_MODULE_E为 E_AIP_EVENT_MODULE_NET
 * @note AIP_EVENT_CMD_E为 E_NET_EVENT_DHCPC_GET_SUCCESS
 * 对应的入参
**/
typedef struct
{
    NET_INTERFACE_CARD_E eNetIdx; // 网卡序号
    NET_IP_PROTOCOL_E    eDomain; // ip协议版本
} NET_DHCPC_STATUS_T, *NET_DHCPC_STATUS_P;


/**
 * @brief  网卡网路地址冲突信息
 * @note AIP_EVENT_MODULE_E为 E_AIP_EVENT_MODULE_NET
 * @note AIP_EVENT_CMD_E为 E_NET_EVENT_STATUS_CONFLICT
 * 对应的入参
**/
typedef struct
{
    NET_INTERFACE_CARD_E eNicIdx;              // 网卡序号
    NET_IP_PROTOCOL_E    eDomain;              // ip协议版本
    NET_IP_ADDR_COMMON_T stIpAddr;             // 冲突的ip地址
    HPR_INT8 byaConflictMac[NET_MAC_ADDR_LEN]; // 冲突的mac地址(非本机)(注意非可读字符串)
} NET_EVENT_CONFILIT_MSG_T, *NET_EVENT_CONFILIT_MSG_P;

/**
 * @brief  网卡网络地址从冲突恢复到不冲突状态信息
 * @note AIP_EVENT_MODULE_E为 E_AIP_EVENT_MODULE_NET
 * @note AIP_EVENT_CMD_E为 E_NET_EVENT_STATUS_RESUME_NOCONFLICT
 * 对应的入参
**/
typedef struct
{
    NET_INTERFACE_CARD_E eNicIdx;              // 网卡序号
} NET_EVENT_RESUME_NOCONFLICT_MSG_T, *NET_EVENT_RESUME_NOCONFLICT_MSG_P;

/** @brief  网络信道参数*/
/** @note   用来表示无线、蜂窝网络参数*/
typedef struct
{
    HPR_BOOL bEnable;      //表示是否开启对应的网络链接
    HPR_BOOL bSupport;     //是否支持表示是否支持这项服务,HPR_TRUE: 支持，HPR_FALSE
} NET_CHANNAL_PARAM_T, *NET_CHANNAL_PARAM_P;

/** @brief  网络冲突检测服务 初始化参数*/
typedef struct
{
    NET_IF_PARAM_T  stIfParam;                     //[in], 网卡参数
    WIFI_SERVICE_INIT_PARAM_T stWifiInfo;
    NET_CHANNAL_PARAM_T stCelularParam;            //[in]. 蜂窝网络 参数
} NET_MNG_PARAM_T, *NET_MNG_PARAM_P;

/**
 *  @brief 网络服务回调
 */
typedef AIP_EVENT_CALLBACK_FUN NET_EVENT_CALLBACK_FUN ;

/************************************************************************
  Function Declaration
 ************************************************************************/

/**
 * @fn        AIP_EXTERN HPR_INT32 aip_net_mng_service_start(NET_MNG_PARAM_P pstInitParam, NET_EVENT_CALLBACK_FUN fnCbFun)
 * @brief     开启网络管理服务
 * @param[in] pstInitParam, see NET_MNG_PARAM_P define
 * @param[in] fnCbFun, 回调函数,允许为NULL
 * @note      包括网络网卡服务和端口管理服务
 * @return    HPR_OK: success； other:fail
**/
AIP_EXTERN HPR_INT32 aip_net_mng_service_start(NET_MNG_PARAM_P pstInitParam, NET_EVENT_CALLBACK_FUN fnCbFun);

/**
 *  @fn       AIP_EXTERN HPR_INT32 aip_net_mng_service_stop(HPR_VOID)
 *  @brief    关闭网络管理服务
 *  @return   HPR_OK: success； other:fail
**/
AIP_EXTERN HPR_INT32 aip_net_mng_service_stop(HPR_VOID);


#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /*  __AIP_NET_MNG_H__ END */
