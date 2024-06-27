/**
 * @copyright HangZhou Hikvision Digital Technology Co., Ltd. All Right Reserved.
 * @file      aip_net_config.h
 * @brief     网卡参数配置接口(网卡使能状态、ip地址、子网掩码、网关、dns、网络地址获取方式等)
 * @note      支持ipv6和ipv4
 */

#ifndef __AIP_NET_CONFIG_H__
#define __AIP_NET_CONFIG_H__

/************************************************************************
 Included Header
 ************************************************************************/
#include <netinet/in.h>
#include "common/aip_common.h"
#include "netMng/aip_net_common.h"
#include "netMng/interface/aip_net_ip_link.h"
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
//@brief: ip地址配置方式
typedef enum
{
    E_CFG_METHOD_MANUL    = 0,                    // 手动配置
    E_CFG_METHOD_AUTO     = 1,                    // 动态获取(dhcp)
    E_CFG_METHOD_IPV6_RA  = 2,                    // 路由公告(仅IPV6支持)
    E_CFG_METHOD_INVALID  = 3,
} NET_IP_ADDR_CFG_METHOD_E;

//@brief: 网卡类别
typedef enum
{
    E_IF_TYPE_ETH            = 0,                        // 以太网卡(即有线网)
    E_IF_TYPE_WLAN           = 1,                        // 无线网卡类型(wifi)
    E_IF_TYPE_CELULAR_MOBILE = 2,                        // 蜂窝网络t通信类型(3/4/5g)
} NET_IF_TYPE_E;


/** @brief IP信息*/
typedef struct
{
    NET_IP_ADDR_CFG_METHOD_E eCfgMethod;   //[in],ip信息配置方式，仅当使用手动配置时,静态ip信息方有效

    //@brief: 静态ip信息
    NET_IP_INFO_COMMON_T stIpInfo;   // [in], ip信息(ip地址以及子网掩码前缀长度)
    NET_IP_ADDR_COMMON_T stGateway;  // [in], 网关地址信息;
} NET_INTERFACE_IP_PARAM_T, *NET_INTERFACE_IP_PARAM_P;

/** @brief 网卡参数*/
typedef struct
{

    HPR_INT8                 byaNicName[NET_IF_NAME_LEN];   // [in], 网卡名
    NET_IF_TYPE_E            eIfType;       //[in], 网卡类型
    //@brief: ip
    NET_INTERFACE_IP_PARAM_T stIpParamV4;   // [in], ipv4 信息
    NET_INTERFACE_IP_PARAM_T stIpParamV6;   // [in], ipv6 信息, 支持ipv6时生效。see NET_INIT_DETAIL_PARAM_T.bSupportIpv6
    //@brief: dns
    HPR_BOOL                 bAutoDns;      // [in], dns是否自动获取，HPR_TRUE: 开启自动dns(开启后该网卡的dns将根据dhcp自动获取) HPR_FALSE 手动配置。
                                             //      配置dns自动获取时 请确保至少ipv4或ipv4为自动获取，否则意味着途径获取到dns(接口内部不对该逻辑做校验)
    NET_DNS_T                stDns;          // [in], 要配置的dns，仅bAutoDns 为 HPR_FALSE 时有效。支持最大配置两个dns。


    HPR_UINT32               dwMTU;          //MTU,要求大于68且小于等于1500，如非特殊配置，建议1500

    NET_ETH_IF_WORK_MODE_E   eIfWorkMode;    //网卡工作模式,如非特殊需要，建议为E_ETH_IF_AUTO
                                             //仅eIfType类型为E_IF_TYPE_ETH,需要. 否则为无效参数
} NET_INTERFACE_PARAM_T, *NET_INTERFACE_PARAM_P;


/** @brief IP和DNS参数*/
typedef struct 
{
    NET_INTERFACE_IP_PARAM_T stIpParam;     // [in], ip信息
    HPR_BOOL                 bAutoDns;      // [in], dns是否自动获取，HPR_TRUE: 开启自动dns(开启后该网卡的dns将根据dhcp自动获取) HPR_FALSE 手动配置。
    NET_DNS_T                stDns;         // [in], 要配置的dns，仅bAutoDns 为 HPR_FALSE 时有效。支持最大配置两个dns。
} NET_INTERFACE_IP_AND_DNS_PARAM_T, *NET_INTERFACE_IP_AND_DNS_PARAM_P;

/** @brief 网卡信息 IP和DNS参数*/
typedef struct 
{
    NET_INTERFACE_CARD_E eNicIdx;                   // [in], 网卡枚举值
    NET_INTERFACE_IP_AND_DNS_PARAM_T stIpAndDnsParam;     // [in], ip和DNS信息
} NET_INTERFACE_IF_AND_DNS_PARAM_T, *NET_INTERFACE_IF_AND_DNS_PARAM_P;

/** @brief  网络冲突检测服务 初始化参数*/
typedef struct
{
    HPR_BOOL  bSupportIpv6;                                   // [in], HPR_TRUE:  支持ipv6， HPR_FALSE:不支持ipv6
    HPR_INT32 sdwValidNicNum;                                 // [in], 有效网卡个数
    HPR_BOOL  bIgnoreIpParam;                                 // [in], HPR_TRUE: 忽略初始化h时stIfIdxParam中IP和DNS参数(stIpParamV4、stIpParamV6、bAutoDns、stDns)，不会进行初始化配置
                                                              //       HPR_FALSE:不忽略
    NET_INTERFACE_PARAM_T  stIfIdxParam[NET_NIC_MAX_NUM];     // [in], 网卡信息, 应该设备支持的所有有效网卡（包括以太网、无线、3/4/5g 网卡节点).
                                                              // 数组的前sdwValidNicNum 成员为有效网卡参数
} NET_IF_PARAM_T, *NET_IF_PARAM_P;

//@note
typedef struct 
{
    HPR_INT8  *szNicName;           //网卡名
    HPR_UINT32 dwTableIdx;          //接口自定义路由表号
    HPR_UINT32 dwPrePriority;       //接口自定义路由表前缀路由优先级
    HPR_UINT32 dwGwPriority;        //接口自定义路由表网关路由优先级
    HPR_UINT32 dwRulePriority;      //接口策略路由优先级
    HPR_UINT32 dwToRulePriority;    //接口策略路由优先级(to dns)
} NET_ROUTE_MANAGE_INFO_T, *NET_ROUTE_MANAGE_INFO_P;


/************************************************************************
  Function Declaration
 ************************************************************************/

/**
 * @fn         AIP_EXTERN NET_IP_ADDR_CFG_METHOD_E aip_net_get_ip_cfg_mode(HPR_INT8 *szNicName, NET_IP_PROTOCOL_E eDomain)
 * @brief      获取指定网卡指定协议簇的ip地址获取模式
 * @param[in]  szNicName  : 网络接口名称
 * @param[in]   eDomain   : ip协议类型
 *                          E_IP_PROTOCOL_V4 : ipv4
 *                          E_IP_PROTOCOL_V6 : ipv6
 * @return     success: 网卡配置方式, fail:E_CFG_METHOD_INVALID
**/
AIP_EXTERN NET_IP_ADDR_CFG_METHOD_E aip_net_get_ip_cfg_mode(HPR_INT8 *szNicName, NET_IP_PROTOCOL_E eDomain);

/**
 * @fn        AIP_EXTERN HPR_INT32 aip_net_set_ip_cfg_mode(HPR_INT8 *szNicName, NET_IP_PROTOCOL_E eDomain,NET_IP_ADDR_CFG_METHOD_E eCfgMethod)
 * @brief      配置指定网卡指定协议簇的ip地址获取模式
 * @param[in]  szNicName  : 网络接口名称
 * @param[in]   eDomain   : ip协议类型
 *                          E_IP_PROTOCOL_V4 : ipv4
 *                          E_IP_PROTOCOL_V6 : ipv6
 * @param[in]  eCfgMethod : 配置方式
 * @return     HPR_OK:success, other:fail
**/
AIP_EXTERN HPR_INT32 aip_net_set_ip_cfg_mode(HPR_INT8 *szNicName, NET_IP_PROTOCOL_E eDomain, NET_IP_ADDR_CFG_METHOD_E eCfgMethod);

/**
 * @fn          AIP_EXTERN HPR_INT32 aip_net_set_if_ip_info(HPR_INT8 *szNicName, NET_IP_PROTOCOL_E eDomain, NET_INTERFACE_IP_PARAM_P pstIpInfo)
 * @brief       配置指定网卡指定协议簇ip地址(包括ip地址、子网掩码前缀长度、网关地址)
 * @param[in]   szNicName : 网络接口名称
 * @param[in]   eDomain   : ip协议类型
 *                          E_IP_PROTOCOL_V4 : ipv4
 *                          E_IP_PROTOCOL_V6 : ipv6
 * @param[int]  pstIpParam : 网卡ip信息
 * @return      HPR_OK: success; other, fail
 * @note        配置时将会清空指定网卡指定iP协议类型的原有地址
 * 息
**/
AIP_EXTERN HPR_INT32 aip_net_set_if_ip_info(HPR_INT8 *szNicName, NET_IP_PROTOCOL_E eDomain, NET_INTERFACE_IP_PARAM_P pstIpParam);

/**
 * @fn          AIP_EXTERN HPR_INT32 aip_net_get_gateway(HPR_INT8 *szNicName, NET_IP_PROTOCOL_E eDomain, NET_IP_ADDR_COMMON_P pstGateway)
 * @brief       获取指定网卡指定协议簇当前网关
 * @param[in]   szNicName : 网络接口名称
 * @param[in]   eDomain   : ip协议类型
 *                          E_IP_PROTOCOL_V4 : ipv4
 *                          E_IP_PROTOCOL_V6 : ipv6
 * @param[out]   pstGateway :获取到的网关地址存放位置
 * @return      success:ipv4网关地址, fail:0
**/
AIP_EXTERN HPR_INT32 aip_net_get_gateway(HPR_INT8 *szNicName, NET_IP_PROTOCOL_E eDomain, NET_IP_ADDR_COMMON_P pstGateway);

/**
 * @fn          AIP_EXTERN HPR_INT32 aip_net_get_gateway_in_str(HPR_INT8 *szNicName, HPR_INT8 *byaBuf, HPR_INT32 dwBufSize)
 * @brief       获取指定网卡指定协议簇的当前网关(字符串形式)
 * @param[in]   szNicName : 网络接口名称
 * @param[in]   eDomain   : ip协议类型
 *                          E_IP_PROTOCOL_V4 : ipv4
 *                          E_IP_PROTOCOL_V6 : ipv6
 * @param[out]  byaBuf    : 存放网关地址的buf地址
 * @param[in]   dwBufSize : buf大小, ipv4要求大于等于NET_IP_ADDR_STR_LEN, ipv6要求大于等于NET_IP_V6_ADDR_STR_LEN
 * @return      HPR_OK: success; other:fail
**/
AIP_EXTERN HPR_INT32 aip_net_get_gateway_in_str(HPR_INT8 *szNicName, NET_IP_PROTOCOL_E eDomain, HPR_INT8 *byaBuf, HPR_INT32 dwBufSize);

/**
 * @fn          AIP_EXTERN HPR_INT32 aip_net_get_ip_info_in_str_v4(HPR_INT8 *szNicName, HPR_INT8 *byaBuf, HPR_INT32 dwBufSize);
 * @brief       字符串形式获取指定网卡名的网卡当前ipv4地址
 * @param[in]   szNicName : 网络接口名称
 * @param[out]  pbyIpAddr : 允许为NULL，不为NULL时应该指向一个sizeof为NET_IP_ADDR_STR_LEN的数组指针，将返回字符串格式的ipv4地址(包含截断符)
 * @param[out]  pbyNetmask : 允许为NULL，不为NULL时应该指向一个sizeof为NET_IP_ADDR_STR_LEN的数组指针，将返回字符串格式的ipv4的子网掩码（包含截断符）
 * @note        pbyIpAddr 和pbyNetmask 不允许同时未NULL,因为这代表你从该接口没有实际获取到什么
 * @return      HPR_OK: success; other:fail
**/
AIP_EXTERN HPR_INT32 aip_net_get_ip_info_in_str_v4(HPR_INT8 *szNicName, HPR_INT8 pbyIpAddr[NET_IP_ADDR_STR_LEN], HPR_INT8 pbyNetmask[NET_IP_ADDR_STR_LEN]);

/**
 * @fn          AIP_EXTERN HPR_INT32 aip_net_get_ip_info_in_str_v4(HPR_INT8 *szNicName, HPR_INT8 *byaBuf, HPR_INT32 dwBufSize);
 * @brief       字符串形式获取指定网卡名的网卡当前ipv4地址
 * @param[in]   szNicName : 网络接口名称
 * @param[out]  pbyIpAddr : 允许为NULL，不为NULL时应该指向一个sizeof 为NET_IP_V6_ADDR_STR_LEN的数组，将返回字符串格式的ipv6地址(包含截断符)
 * @param[out]  pdwPrefixLen : 允许为NULL，不为NULL时将返回子网掩码前缀长度
 * @note        pbyIpAddr 和pdwPrefixLen 不允许同时未NULL,因为这代表你从该接口没有实际获取到什么
 * @return      HPR_OK: success; other:fail
**/
AIP_EXTERN HPR_INT32 aip_net_get_ip_info_in_str_v6(HPR_INT8 *szNicName, HPR_INT8 pbyIpAddr[NET_IP_V6_ADDR_STR_LEN], HPR_UINT32* pdwPrefixLen);



/**
 * @fn          AIP_EXTERN HPR_INT32 aip_net_clean_ip_info_system(HPR_INT8 *szNicName, NET_IP_PROTOCOL_E eDomain)
 * @brief       清空指定网卡名的网卡ip信息
 * @brief       清空指定网卡指定协议簇的网卡ip信息
 * @note        包括ip地址、网关地址、路由信息、策略路由信息
 * @param[in]   szNicName : 网络接口名称
 * @param[in]   eDomain   : ip协议类型
 *                          E_IP_PROTOCOL_V4 : ipv4
 *                          E_IP_PROTOCOL_V6 : ipv6
 * @return      HPR_OK: success; other, fail
 * @note        清空ip、网关、路由、策略路由
 * 息
**/
AIP_EXTERN HPR_INT32 aip_net_clean_ip_info_system(HPR_INT8 *szNicName, NET_IP_PROTOCOL_E eDomain);

//@brief: dns

/**
 * @fn         AIP_EXTERN HPR_BOOL aip_net_get_auto_dns_flag(HPR_INT8 *szNicName)
 * @brief      获取指定网卡的dns 获取方式(自动获取还是手动配置)
 * @param[in]  szNicName : 网络接口名称
 * @return     HPR_TRUE:  当前为自动获取dns
 *             HRP_FLASE: 当前为手动配置dns
 *             异常视为 HPR_FLASE
**/
AIP_EXTERN HPR_BOOL aip_net_get_auto_dns_flag(HPR_INT8 *szNicName);

/**
 * @fn         AIP_EXTERN HPR_INT32 aip_net_set_auto_dns_flag(HPR_INT8 *szNicName, HPR_BOOL bAutoDns)
 * @brief      设置指定网卡的dns 获取方式(自动获取还是手动配置)
 * @note       开启自动获取要求先至少开启ipv4、ipv6dhcp获取ip中的一项
 * @param[in]  szNicName : 网络接口名称
 * @param[in]  bAutoDns:  HPR_TRUE: 开启自动dns(开启后该网卡的dns将根据dhcp自动获取)
 *                        HPR_FLAE: 关闭自动dns
 * @note       安卓该参数无意义，会与ip获取方式保持一致
 * @return     HPR_OK:success, other:fail
**/
AIP_EXTERN HPR_INT32 aip_net_set_auto_dns_flag(HPR_INT8 *szNicName, HPR_BOOL bAutoDns);

/**
 * @fn         AIP_EXTERN HPR_INT32 aip_net_get_dns(HPR_INT8 *szNicName, NET_DNS_P pstDns)
 * @brief      获取指定网卡的dns, 不区分IPv4还是IPv6
 * @param[in]  szNicName : 网络接口名称，允许为NULL
 *                          当指定有效网卡名时, 返回该网卡当前对应的dns配置
 *                          当为NULL时, 返回系统实际使用的dns配置
 * @param[out] pstDns    : dns信息
 * @return     HPR_OK    :success, other:fail
**/
AIP_EXTERN HPR_INT32 aip_net_get_dns(HPR_INT8 *szNicName, NET_DNS_P pstDns);

/**
 * @fn         AIP_EXTERN HPR_INT32 aip_net_get_dns_v4(HPR_INT8 *szNicName, NET_DNS_P pstDns)
 * @brief      获取指定网卡的IPv4 dns
 * @param[in]  szNicName : 网络接口名称，允许为NULL
 *                          当指定有效网卡名时, 返回该网卡当前对应的dns配置
 *                          当为NULL时, 返回系统实际使用的dns配置
 * @param[out] pstDns    : dns信息
 * @return     HPR_OK    :success, other:fail
**/
AIP_EXTERN HPR_INT32 aip_net_get_dns_v4(HPR_INT8 *szNicName, NET_DNS_P pstDns);

/**
 * @fn         AIP_EXTERN HPR_INT32 aip_net_get_dns_v6(HPR_INT8 *szNicName, NET_DNS_P pstDns)
 * @brief      获取指定网卡的IPv6 dns
 * @param[in]  szNicName : 网络接口名称，允许为NULL
 *                          当指定有效网卡名时, 返回该网卡当前对应的dns配置
 *                          当为NULL时, 返回系统实际使用的dns配置
 * @param[out] pstDns    : dns信息
 * @return     HPR_OK    :success, other:fail
**/
AIP_EXTERN HPR_INT32 aip_net_get_dns_v6(HPR_INT8 *szNicName, NET_DNS_P pstDns);

/**
 * @fn         AIP_EXTERN HPR_INT32 aip_net_set_dns(HPR_INT8 *szNicName, NET_DNS_P pstDns)
 * @brief      设置指定网卡系统的IPv4 dns
 * @param[in]  szNicName : 网络接口名称
 * @param[in]  pstDns: dns信息
 * @return     HPR_OK:success, other:fail
 * @note       调用该接口后将自动设置改网卡dns配置模式为手动配置
 * @note       系统实际使用的dns不一定恒等于指定网卡的dns配置
 * @see        net_set_auto_dns_flag
**/
AIP_EXTERN HPR_INT32 aip_net_set_dns(HPR_INT8 *szNicName, NET_DNS_P pstDns);

/**
 * @fn         AIP_EXTERN HPR_INT32 aip_net_set_dns_v6(HPR_INT8 *szNicName, NET_DNS_P pstDns)
 * @brief      设置指定网卡系统的IPv6 dns
 * @param[in]  szNicName : 网络接口名称
 * @param[in]  pstDns: dns信息
 * @return     HPR_OK:success, other:fail
 * @note       调用该接口后将自动设置改网卡dns配置模式为手动配置
 * @note       系统实际使用的dns不一定恒等于指定网卡的dns配置
 * @see        net_set_auto_dns_flag
**/
AIP_EXTERN HPR_INT32 aip_net_set_dns_v6(HPR_INT8 *szNicName, NET_DNS_P pstDns);

/**
 * @fn         AIP_EXTERN HPR_INT32 aip_net_del_dns(HPR_INT8 *szNicName)
 * @brief      清空指定网卡dns
 * @param[in]  szNicName : 网络接口名称，允许为NULL
 *                        当指定有效网卡名时, 清空该网卡当前对应的dns配置
 *                        当为NULL时, 清空系统实际使用的dns配置
 *                        注意！当前LINUX使用该接口时，不支持清空特定网卡名，只支持清空系统使用的dns配置
 * @return     HPR_OK:success, other:fail
**/
AIP_EXTERN HPR_INT32 aip_net_del_dns(HPR_INT8 *szNicName);

/**
 * @fn          AIP_EXTERN HPR_INT32 aip_net_set_if_ip_info_and_dns(HPR_INT8 *szNicName, NET_IP_PROTOCOL_E eDomain, NET_INTERFACE_IP_AND_DNS_PARAM_P pstIpAndDnsInfo)
 * @brief       配置指定网卡指定协议簇ip地址(包括ip地址、子网掩码前缀长度、网关地址)
 * @param[in]   szNicName : 网络接口名称
 * @param[in]   eDomain   : ip协议类型
 *                          E_IP_PROTOCOL_V4 : ipv4
 *                          E_IP_PROTOCOL_V6 : ipv6
 * @param[int]  pstIpAndDnsInfo : 网卡ip和dns信息
 * @return      HPR_OK: success; other, fail
 * @note        配置时将会清空指定网卡指定iP协议类型的原有地址
 * 息
**/
AIP_EXTERN HPR_INT32 aip_net_set_if_ip_info_and_dns(HPR_INT8 *szNicName, NET_IP_PROTOCOL_E eDomain, NET_INTERFACE_IP_AND_DNS_PARAM_P pstIpAndDnsInfo);

/**
 * @fn:         aip_net_set_route_cfg_info
 * @brief:      设置网卡路由配置信息
 * @param[in]:  pstRouteInfo 需要设置的路由信息
 * @return:     HPR_INT32 HPR_OK/HPR_ERROR
 * @author:     xiaoxinyu
 */
AIP_EXTERN HPR_INT32 aip_net_set_route_cfg_info(NET_ROUTE_MANAGE_INFO_P pstRouteInfo);

#ifdef TEST_USE_INTERNAL_FUNC
/**@fn: aip_net_test_init
 * @brief: 给静态全局变量s_stIfManage初始化, 使其他函数在测试时可用。
 * @param[in]: pstIfParam
 * @return: HRP_OK, HPR_ERROR
 * @author: xiaoxinyu
 */
AIP_EXTERN HPR_INT32 aip_net_config_test_init(const NET_IF_PARAM_T *pstIfParam);

HPR_INT32 aip_net_if_service_start(NET_IF_PARAM_P pstParam);
HPR_INT32 aip_net_if_service_stop(HPR_VOID);
#endif

#ifdef __cplusplus
}
#endif

#endif /* __AIP_NET_CONFIG_H__ */
