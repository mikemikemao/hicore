/**
 * @copyright HangZhou Hikvision Digital Technology Co., Ltd. All Right Reserved.
 * @file      aip_net_ip_addr.h
 * @brief     网卡网络地址配置相关接口
 */
#ifndef __AIP_NET_IP_ADDR_H__
#define __AIP_NET_IP_ADDR_H__

/************************************************************************
 Included Header
 ************************************************************************/
#include "common/aip_common.h"
#include "netMng/aip_net_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/************************************************************************
 Macros
 ************************************************************************/

/************************************************************************
 Type Definition
 ************************************************************************/

/************************************************************************
  Function Declaration
 ************************************************************************/

/**
 * @fn          AIP_EXTERN HPR_INT32 aip_net_get_ip_info(HPR_INT8 *szNicName, NET_IP_PROTOCOL_E eDomain, NET_IP_INFO_COMMON_P pstIpInfo)
 * @brief       获取指定网卡指定协议簇的ip地址
 * @param[in]   szNicName : 网络接口名称
 * @param[in]   eDomain   : ip协议类型
 *                          E_IP_PROTOCOL_V4 : ipv4
 *                          E_IP_PROTOCOL_V6 : ipv6
 * @param[out]  pstIpInfo : ip信息，根据eDomian类型,返回对应的ip类型地址和子网掩码前缀长度
 * @return      HPR_OK: success; other:fail
 * @note        实际底层系统同网卡同个ip协议类型支持配置多个ip地址，当出现获取到多个地址时，仅返回第一个符合条件的地址信息
**/
AIP_EXTERN HPR_INT32 aip_net_get_ip_info(HPR_INT8 *szNicName, NET_IP_PROTOCOL_E eDomain, NET_IP_INFO_COMMON_P pstIpInfo);

/******************************************************************************
 * @fn:		aip_net_get_ra_ip_list
 * @brief:  获取指定网卡IPv6路由公告地址链表, 链表指针传入时需要为空.
 * @param:
 *          HPR_INT8 *pbyNicName - 网卡名
 *          NET_IP_RA_ADDR_LIST **pstRaList - [OUT] 路由公告IPv6地址链表指针
 * @return: AIP_EXTERN HPR_INT32 HPR_OK/HPR_ERROR
 * @author: xiaoxinyu
 ******************************************************************************/
AIP_EXTERN HPR_INT32 aip_net_get_ra_ip_list(HPR_INT8 *pbyNicName,
                                            NET_IP_RA_ADDR_LIST **pstRaList);
/**
 * @fn          AIP_EXTERN HPR_INT32 aip_net_set_ip_info(HPR_INT8 *szNicName, NET_IP_PROTOCOL_E eDomain, NET_IP_INFO_COMMON_P pstIpInfo)
 * @brief       设置网卡指定ip协议簇的ip信息(包括ip地址和子网掩码前缀长度)
 * @param[in]   szNicName : 网络接口名称
 * @param[in]   eDomain   : ip协议类型
 *                          E_IP_PROTOCOL_V4 : ipv4
 *                          E_IP_PROTOCOL_V6 : ipv6
 * @param[in]   pstIpInfo : ip信息，根据eDomian类型,设置对应的ip协议簇地址和子网掩码前缀长度
 * @return      HPR_OK:success; other:fail
 * @note        配置时将会清空指定网卡指定iP协议类型的原有ip信息
**/
AIP_EXTERN HPR_INT32 aip_net_set_ip_info(HPR_INT8 *szNicName, NET_IP_PROTOCOL_E eDomain, NET_IP_INFO_COMMON_P pstIpInfo);

/**
 * @fn          AIP_EXTERN HPR_INT32 aip_net_set_ip_info_in_str_v4(HPR_INT8 *szNicName, HPR_INT8 *szIpAddr, HPR_INT8 *szNetmask);
 * @brief       设置指定网卡ipv4地址信息(包括ip地址和子网掩码)(字符串形式)
 * @param[in]   szNicName : 网络接口名称
 * @param[in]   szIpAddr  : 要设置的ip地址
 * @param[in]   szNetmask : 要设置的子网掩码
 * @return      HPR_OK: success; other:fail
**/
AIP_EXTERN HPR_INT32 aip_net_set_ip_info_in_str_v4(HPR_INT8 *szNicName, HPR_INT8 *szIpAddr, HPR_INT8 *szNetmask);

/**
 * @fn          AIP_EXTERN HPR_INT32 aip_net_set_ip_info_in_str_v6(HPR_INT8 *szNicName, HPR_INT8 *szIpAddr, HPR_UINT32 dwPrefixLen)
 * @brief       设置指定网卡ipv6地址信息(包括ip地址和子网掩码)(字符串形式)
 * @param[in]   szNicName : 网络接口名称
 * @param[in]   szIpAddr  : 要设置的ip地址
 * @param[in]   dwPrefixLen : 要设置的子网掩码前缀长度
 * @return      HPR_OK: success; other:fail
**/
AIP_EXTERN HPR_INT32 aip_net_set_ip_info_in_str_v6(HPR_INT8 *szNicName, HPR_INT8 *szIpAddr, HPR_UINT32 dwPrefixLen);

/**
 * @fn          AIP_EXTERN HPR_INT32 aip_net_del_ip_info_all(HPR_INT8 *szNicName, NET_IP_PROTOCOL_E eDomain)
 * @brief       删除指定网卡指定协议簇的所有ip地址
 * @param[in]   szNicName : 网络接口名称
 * @param[in]   eDomain   : ip协议类型
 *                          E_IP_PROTOCOL_V4 : ipv4
 *                          E_IP_PROTOCOL_V6 : ipv6。 不会删除路由公告地址
 * @return      success:ipv4地址, fail:0
**/
AIP_EXTERN HPR_INT32 aip_net_del_ip_info_all(HPR_INT8 *szNicName, NET_IP_PROTOCOL_E eDomain);

#ifdef __cplusplus
}
#endif
#endif /* __AIP_NET_IP_ADDR_H__ END */
