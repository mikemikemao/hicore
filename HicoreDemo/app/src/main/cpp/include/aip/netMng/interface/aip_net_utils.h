/**
 * @copyright HangZhou Hikvision Digital Technology Co., Ltd. All Right Reserved.
 * @file      aip_net_utils.h
 * @brief     网络工具接口(地址校验、地址转换相关)
 */
#ifndef __AIP_NET_UTILS_H__
#define __AIP_NET_UTILS_H__

/************************************************************************
 Included Header
 ************************************************************************/
#include "netinet/in.h"

#include "HPR_Addr.h"

#include "common/aip_common.h"

#include "netMng/aip_net_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/************************************************************************
 Macros
 ************************************************************************/


#ifndef IF_NAMESIZE
	#define IF_NAMESIZE  16
#endif


/************************************************************************
 Type Definition
 ************************************************************************/

/************************************************************************
  Function Declaration
 ************************************************************************/

/**
 * @fn        AIP_EXTERN HPR_BOOL aip_net_utils_check_ipaddr_legal_in_str_v4(HPR_INT8 *szIp)
 * @brief     检查IPV4地址是否合法
 * @note      注意和ip是否有效进行区分
 * @param[in] szIp : 要校验的ip地址
 * @return    合法：HPR_TRUE, 非法：HPR_FALSE
 * @note      0.0.0.0 也是合法ip
 * @see       aip_net_utils_check_ipaddr_valid_in_str_v4
**/
AIP_EXTERN HPR_BOOL aip_net_utils_check_ipaddr_legal_in_str_v4(HPR_INT8 *szIp);

/**
 * @fn        AIP_EXTERN HPR_BOOL aip_net_utils_check_ipaddr_valid_v4(in_addr_t dwIp)
 * @brief     检查IPV4地址是否有效
 * @note      有效ip地址必须合法且为A、B、C类地址之一, 不允许为未指定(全0)地址，不允许为回环地址,不允许为广播地址
 * @param[in] dwIp : 要校验的ip地址
 * @return    有效：HPR_TRUE, 无效：HPR_FALSE
**/
AIP_EXTERN HPR_BOOL aip_net_utils_check_ipaddr_valid_v4(in_addr_t dwIp);

/**
 * @fn        AIP_EXTERN HPR_BOOL aip_net_utils_check_ipaddr_valid_in_str_v4(HPR_INT8 *szIp)
 * @brief     检查IPV4地址(字符串格式)是否有效
 * @note      有效ip地址必须合法且为A、B、C类地址之一, 不允许为未指定(全0)地址，不允许为回环地址,不允许为广播地址
 * @param[in] szIp : 要校验的ip地址
 * @return    有效：HPR_TRUE, 无效：HPR_FALSE
**/
AIP_EXTERN HPR_BOOL aip_net_utils_check_ipaddr_valid_in_str_v4(HPR_INT8 *szIp);

/**
 * @fn        AIP_EXTERN HPR_BOOL aip_net_utils_check_ipaddr_valid_or_unspecified_v4(in_addr_t dwIp)
 * @brief     检查IPV4地址是否有效, 
 * @note      有效ip地址必须合法且为A、B、C类地址之一, 不允许为回环地址,不允许为广播地址
 * @note      允许为未指定(全0)地址
 * @note      该参数常用于校验默认值为未指定地址的ip地址配置
 * @param[in] dwIp : 要校验的ip地址
 * @return    有效：HPR_TRUE, 无效：HPR_FALSE
**/
AIP_EXTERN HPR_BOOL aip_net_utils_check_ipaddr_valid_or_unspecified_v4(in_addr_t dwIp);

/**
 * @fn        AIP_EXTERN HPR_BOOL aip_net_utils_check_ipaddr_valid_or_unspecified_in_str_v4(HPR_INT8 *szIp)
 * @brief     检查IPV4地址(字符串格式)是否有效
 * @note      有效ip地址必须合法且为A、B、C类地址之一, 不允许为回环地址,不允许为广播地址
 * @note      允许为未指定(0.0.0.0)地址
 * @note      该参数常用于校验默认值为未指定地址的ip地址配置
 * @param[in] szIp : 要校验的ip地址
 * @return    有效：HPR_TRUE, 无效：HPR_FALSE
**/
AIP_EXTERN HPR_BOOL aip_net_utils_check_ipaddr_valid_or_unspecified_in_str_v4(HPR_INT8 *szIp);

/**
 * @fn        AIP_EXTERN HPR_BOOL aip_net_utils_check_netmask_legal_v4(in_addr_t dwNetmask)
 * @brief     检查IPV4地址的子网掩码是否合法
 * @note      注意和是否有效进行区分, 合法的子网掩码应该从第0位开始置位且连续,最高为不应该置位
 * @param[in] dwNetmask : 要校验的子网掩码地址
 * @return    合法：HPR_TRUE, 非法：HPR_FALSE
**/
AIP_EXTERN HPR_BOOL aip_net_utils_check_netmask_legal_v4(in_addr_t dwNetmask);

/**
 * @fn        AIP_EXTERN HPR_BOOL aip_net_utils_check_netmask_legal_in_str_v4(HPR_INT8 *szNetmask)
 * @brief     检查IPV4地址的子网掩码(字符串)是否合法
 * @note      注意和是否有效进行区分, 合法的子网掩码应该从第0位开始置位且连续
 * @param[in] szNetmask: 要校验的ip地址
 * @return    合法：HPR_TRUE, 非法：HPR_FALSE
 * @see       net_utils_check_netmask_valid_in_str_v4
**/
AIP_EXTERN HPR_BOOL aip_net_utils_check_netmask_legal_in_str_v4(HPR_INT8 *szNetmask);

/**
 * @fn          AIP_EXTERN HPR_BOOL aip_net_utils_check_netmask_valid_v4(in_addr_t dwIp, in_addr_t dwNetmask)
 * @brief       检查IPV4地址的子网掩码是否有效
 * @note        一个有效的子网掩码必须合法且结合ip地址校验(保证ip地址的网络地址和主机地址部分均不全为0)
 * @param[in]   dwIp : 子网掩码对应的ip地址
 * @param[in]   dwNetmask : 要校验的子网掩码地址
 * @return      有效：HPR_TRUE, 无效：HPR_FALSE
 * @note        若ip地址是一个无效地址，也返回无效
**/
AIP_EXTERN HPR_BOOL aip_net_utils_check_netmask_valid_v4(in_addr_t dwIp, in_addr_t dwNetmask);

/**
 * @fn         AIP_EXTERN HPR_BOOL aip_net_utils_check_netmask_valid_in_str_v4(HPR_INT8 *szIp, HPR_INT8 *szNetmask)
 * @brief      检查IPV4子网掩码(字符串格式)是否有效
 * @note        一个有效的子网掩码必须合法且结合ip地址校验(保证ip地址的网络地址和主机地址部分均不全为0)
 * @param[in]  szIp : 子网掩码对应的ip地址
 * @param[in]  szNetmask : 要校验的子网掩码地址
 * @return     合法：HPR_TRUE, 非法：HPR_FALSE
 * @note       若ip地址是一个无效地址，也返回无效
**/
AIP_EXTERN HPR_BOOL aip_net_utils_check_netmask_valid_in_str_v4(HPR_INT8 *szIp, HPR_INT8 *szNetmask);

/**
 * @fn        AIP_EXTERN HPR_BOOL aip_net_utils_check_ipaddr_legal_in_str_v6(HPR_INT8 *szIpv6)
 * @brief     检查字符串格式的IPV6地址是否非法
 * @note      注意和ip是否有效进行区分
 * @param[in] szIp : 要校验的ip地址, see NET_IP_V6_ADDR_STR_LEN define
 * @return    合法：HPR_TRUE, 非法：HPR_FALSE
 * @see       net_utils_check_ipaddr_valid_in_str_v6
**/
AIP_EXTERN HPR_BOOL aip_net_utils_check_ipaddr_legal_in_str_v6(HPR_INT8 *szIpv6);

/**
 * @fn        AIP_EXTERN HPR_BOOL aip_net_utils_check_ipaddr_valid_v6(struct in6_addr *pstIpAddrV6)
 * @brief     检查IPV6地址是否有效
 * @note      单播地址：格式合法且不能为未指定地址、回环地址、组播地址、链路本地地址、IPV4映射地址、IPV4兼容地址
 * @param[in] pstIpAddrV6 : 要校验的ip地址
 * @return    合法：HPR_TRUE, 非法：HPR_FALSE
**/
AIP_EXTERN HPR_BOOL aip_net_utils_check_ipaddr_valid_v6(struct in6_addr *pstIpAddrV6);

/**
 * @fn        AIP_EXTERN HPR_BOOL aip_net_utils_check_ipaddr_valid_in_str_v6(HPR_INT8 *szIpV6)
 * @brief     检查IPV6地址(字符串格式)是否有效
 * @note      单播地址：格式合法且不能为未指定地址、回环地址、组播地址、链路本地地址、IPV4映射地址、IPV4兼容地址
 * @param[in] szIpV6 : 要校验的ip地址
 * @return    合法：HPR_TRUE, 非法：HPR_FALSE
**/
AIP_EXTERN HPR_BOOL aip_net_utils_check_ipaddr_valid_in_str_v6(HPR_INT8 *szIpV6);

/**
 * @fn        AIP_EXTERN HPR_BOOL aip_net_utils_check_ipaddr_valid_or_unspecified_v6(struct in6_addr *pstIpAddrV6)
 * @brief     检查IPV6地址是否有效
 * @note      单播地址：格式合法且不能为回环地址、组播地址、链路本地地址、IPV4映射地址、IPV4兼容地址
 * @note      允许为未指定地址(全0)
 * @param[in] pstIpAddrV6 : 要校验的ip地址
 * @return    合法：HPR_TRUE, 非法：HPR_FALSE
**/
AIP_EXTERN HPR_BOOL aip_net_utils_check_ipaddr_valid_or_unspecified_v6(struct in6_addr *pstIpAddrV6);

/**
 * @fn        AIP_EXTERN HPR_BOOL aip_net_utils_check_ipaddr_valid_or_unspecified_in_str_v6(HPR_INT8 *szIpV6)
 * @brief     检查IPV6地址(字符串格式)是否有效
 * @note      单播地址：格式合法且不能回环地址、组播地址、链路本地地址、IPV4映射地址、IPV4兼容地址
 * @note      允许为未指定地址(全0)
 * @param[in] szIpV6 : 要校验的ip地址
 * @return    合法：HPR_TRUE, 非法：HPR_FALSE
**/
AIP_EXTERN HPR_BOOL aip_net_utils_check_ipaddr_valid_or_unspecified_in_str_v6(HPR_INT8 *szIpV6);

/**
 * @fn        AIP_EXTERN HPR_BOOL aip_net_utils_check_prefix_len_legal_v6(HPR_UINT32 dwPrefixLen)
 * @brief     检查IPV6 子网前缀长度是否合法(注意与是否有效区分)
 * @param[in] dwPrefixLen : 要校验的子网前缀长度(表示ipv6地址的前多少bit位代表网络ID)
 * @note      合法的子网前缀长度应当是一个大于0且小于 NET_IP_V6_ADDR_BIT_LEN 的值
 * @see       aip_net_utils_check_prefix_len_valid_v6
 * @see       aip_net_utils_check_prefix_len_valid_in_str_v6
 * @return    合法：HPR_TRUE, 非法：HPR_FALSE
**/
AIP_EXTERN HPR_BOOL aip_net_utils_check_prefix_len_legal_v6(HPR_UINT32 dwPrefixLen);

/**
 * @fn        AIP_EXTERN HPR_BOOL aip_net_utils_check_prefix_len_valid_v6(struct in6_addr *pstIpAddrV6, HPR_UINT32 dwPrefixLen)
 * @brief     检查IPV6子网前缀长度是否有效
 * @note      一个有效的子网前缀长度必须合法且结合ip地址校验(保证ip地址的网络地址和主机地址部分均不全为0)
 * @param[in] pstIpAddrV6 : 子网前缀长度对应的ip地址
 * @param[in] dwPrefixLen : 要检验的子网前缀长度
 * @return    合法：HPR_TRUE, 非法：HPR_FALSE
 * @note      若ip地址是一个无效地址，也返回无效
**/
AIP_EXTERN HPR_BOOL aip_net_utils_check_prefix_len_valid_v6(struct in6_addr *pstIpAddrV6, HPR_UINT32 dwPrefixLen);

/**
 * @fn        AIP_EXTERN HPR_BOOL aip_net_utils_check_prefix_len_valid_in_str_v6(HPR_INT8 *szIpV6, HPR_UINT32 dwPrefixLen)
 * @brief     检查IPV6地址(字符串格式)子网前缀长度是否有效
 * @note      一个有效的子网
 * 前缀长度必须合法且结合ip地址校验(保证ip地址的网络地址和主机地址部分均不全为0)
 * @param[in] szIpV6 : 子网前缀长度对应的ip地址(字符串格式）
 * @param[in] dwPrefixLen : 要检验的子网前缀长度
 * @return    合法：HPR_TRUE, 非法：HPR_FALSE
 * @note        若ip地址是一个无效地址，也返回无效
**/
AIP_EXTERN HPR_BOOL aip_net_utils_check_prefix_len_valid_in_str_v6(HPR_INT8 *szIpV6, HPR_UINT32 dwPrefixLen);

/**
 * @fn        AIP_EXTERN HPR_BOOL aip_net_utils_check_gateway_valid_v6(struct in6_addr *pstGatewayV6)
 * @brief     检查IPV6网关地址是否有效
 * @note      默认网关：格式合法且不能为未指定地址、回环地址、组播地址、IPV4映射地址、IPV4兼容地址
 * @param[in] pstGatewayV6 : 要校验的网关地址
 * @return    合法：HPR_TRUE, 非法：HPR_FALSE
**/
AIP_EXTERN HPR_BOOL aip_net_utils_check_gateway_valid_v6(struct in6_addr *pstGatewayV6);

/**
 * @fn        AIP_EXTERN HPR_BOOL aip_net_utils_check_gateway_valid_in_str_v6(HPR_INT8 *szGateyayV6)
 * @brief     检查IPV6 网关地址(字符串格式)是否有效
 * @note      默认网关：格式合法且不能为未指定地址、回环地址、组播地址、IPV4映射地址、IPV4兼容地址
 * @param[in] szGateyayV6 : 要校验的网关地址
 * @return    合法：HPR_TRUE, 非法：HPR_FALSE
**/
AIP_EXTERN HPR_BOOL aip_net_utils_check_gateway_valid_in_str_v6(HPR_INT8 *szGateyayV6);

/**
 * @fn         AIP_EXTERN HPR_BOOL aip_net_utils_check_netinfo_valid_in_str_v4(HPR_INT8 *szIp, HPR_INT8 *szNetmask, HPR_INT8 *szGateway)
 * @brief      检查IPV4ip地址、子网掩码、网关(字符串格式)是否有效
 * @note        一个有效的子网掩码必须合法且结合ip地址校验(保证ip地址的网络地址和主机地址部分均不全为0)
 * @param[in]  szIp : 子网掩码对应的ip地址
 * @param[in]  szNetmask : 要校验的子网掩码地址
 * @param[in]  szGateyay : 要校验的网关地址
 * @return     合法：HPR_TRUE, 非法：HPR_FALSE
 * @note       若ip地址是一个无效地址，也返回无效
**/
AIP_EXTERN HPR_BOOL aip_net_utils_check_netinfo_valid_in_str_v4(HPR_INT8 *szIp, HPR_INT8 *szNetmask, HPR_INT8 *szGateway);

/**
 * @fn        AIP_EXTERN HPR_BOOL aip_net_utils_check_netinfo_valid_in_str_v6(HPR_INT8 *szIpv6, HPR_UINT32 dwPrefixLen, HPR_INT8 *szGatewayV6)
 * @brief      检查IPV6ip地址、子网掩码前缀长度、网关(字符串格式)是否有效
 * @note        一个有效的子网掩码必须合法且结合ip地址校验(保证ip地址的网络地址和主机地址部分均不全为0)
 * @param[in]  szIpV6 : 子网掩码对应的ip地址
 * @param[in] dwPrefixLen : 要检验的子网前缀长度
 * @param[in]  szGatewayV6 : 要校验的网关地址
 * @return     合法：HPR_TRUE, 非法：HPR_FALSE
 * @note        若ip地址是一个无效地址，也返回无效
**/
AIP_EXTERN HPR_BOOL aip_net_utils_check_netinfo_valid_in_str_v6(HPR_INT8 *szIpv6, HPR_UINT32 dwPrefixLen, HPR_INT8 *szGatewayV6);

/**
 * @fn         AIP_EXTERN HPR_INT32 aip_net_utils_convert_prefix_len_to_common_netmask(NET_IP_PROTOCOL_E eDomain, HPR_UINT32 dwPrefixLen, NET_IP_ADDR_COMMON_P pstNetmask);
 * @brief      转换子网前缀长度为子网掩码结构体
 * @param[in]   eDomain   : ip协议类型
 *                          E_IP_PROTOCOL_V4 : ipv4
 *                          E_IP_PROTOCOL_V6 : ipv6
 * @param[in]  dwPrefixLen : 子网前缀长度(表示ipv6地址的前多少bit位代表网络ID), 
 *                          合法的ipv4子网前缀长度应当是一个不大于 NET_IP_ADDR_BIT_LEN 的值
 *                          合法的ipv6子网前缀长度应当是一个不大于 NET_IP_V6_ADDR_BIT_LEN 的值
 * @param[out] pstNetmask: 子网掩码结构体
 * @return     success：HPR_OK, fail： other
**/
AIP_EXTERN HPR_INT32 aip_net_utils_convert_prefix_len_to_common_netmask(NET_IP_PROTOCOL_E eDomain, HPR_UINT32 dwPrefixLen, NET_IP_ADDR_COMMON_P pstNetmask);

/**
 * @fn      AIP_EXTERN HPR_INT32 aip_net_utils_convert_common_netmask_to_prefix_len(NET_IP_PROTOCOL_E eDomain, NET_IP_ADDR_COMMON_P pstNetmask);
 * @brief   转换子网掩码结构体为子网前缀长度
 * @param[in]   eDomain   : ip协议类型
 *                          E_IP_PROTOCOL_V4 : ipv4
 *                          E_IP_PROTOCOL_V6 : ipv6
 * @param[in] pstNetmask: 子网掩码结构体
 * @return   success：转换得到的子网前缀长度, fail：-1
**/
AIP_EXTERN HPR_INT32 aip_net_utils_convert_common_netmask_to_prefix_len(NET_IP_PROTOCOL_E eDomain, NET_IP_ADDR_COMMON_P pstNetmask);

/**
 * @fn         AIP_EXTERN HPR_INT32 aip_net_utils_convert_prefix_len_to_u_netmask(NET_IP_PROTOCOL_E eDomain, HPR_UINT32 dwPrefixLen, U_IN_ADDR *pstNetmask);
 * @brief      转换子网前缀长度为子网掩码结构体
 * @param[in]   eDomain   : ip协议类型
 *                          E_IP_PROTOCOL_V4 : ipv4
 *                          E_IP_PROTOCOL_V6 : ipv6
 * @param[in]  dwPrefixLen : 子网前缀长度(表示ipv6地址的前多少bit位代表网络ID), 
 *                          合法的ipv4子网前缀长度应当是一个不大于 NET_IP_ADDR_BIT_LEN 的值
 *                          合法的ipv6子网前缀长度应当是一个不大于 NET_IP_V6_ADDR_BIT_LEN 的值
 * @param[out] pstNetmask: 子网掩码结构体
 * @return     success：HPR_OK, fail：other
**/
AIP_EXTERN HPR_INT32 aip_net_utils_convert_prefix_len_to_u_netmask(NET_IP_PROTOCOL_E eDomain, HPR_UINT32 dwPrefixLen, U_IN_ADDR *pstNetmask);

/**
 * @fn      AIP_EXTERN HPR_INT32 aip_net_utils_convert_u_netmask_to_prefix_len(NET_IP_PROTOCOL_E eDomain, U_IN_ADDR *pstNetmask);
 * @brief   转换子网掩码结构体为子网前缀长度
 * @param[in]   eDomain   : ip协议类型
 *                          E_IP_PROTOCOL_V4 : ipv4
 *                          E_IP_PROTOCOL_V6 : ipv6
 * @param[in] pstNetmask: 子网掩码结构体
 * @return   success：转换得到的子网前缀长度, fail：-1
**/
AIP_EXTERN HPR_INT32 aip_net_utils_convert_u_netmask_to_prefix_len(NET_IP_PROTOCOL_E eDomain, U_IN_ADDR *pstNetmask);


//@brief: NET_IP_ADDR_COMMON_T

/**
 * @fn         AIP_EXTERN HPR_INT32 aip_net_utils_convert_common_addr_to_hpr_addr(NET_IP_PROTOCOL_E eDomain, NET_IP_ADDR_COMMON_P pstCommonAddr, HPR_ADDR_T *pstHprAddr)
 * @brief      将NET_IP_ADDR_COMMON_T 结构体的ip转换为HPR_ADDR_T结构体的ip
 * @param[in]  eDomain: 要转换ip的类型。
 *                          E_IP_PROTOCOL_V4 : ipv4, 转换ipv4部分地址
 *                          E_IP_PROTOCOL_V6 : ipv6, 转换ipv4部分地址
 *                          则按照ipv4地址转换
 * @paramp[in] pstCommonAddr, NET_IP_ADDR_COMMON_P结构体表示的ip地址
 * @param[out] pstHprAddr   , HPR_ADDR_T结构体表示的ip地址
 * @note       该接口不对ip合法性进行校验
 * @return     HPR_OK: sucess; other:fail
 */
AIP_EXTERN HPR_INT32 aip_net_utils_convert_common_addr_to_hpr_addr(NET_IP_PROTOCOL_E eDomain, NET_IP_ADDR_COMMON_P pstCommonAddr, HPR_ADDR_T *pstHprAddr);

/*
 * @fn         AIP_EXTERN HPR_INT32 aip_net_utils_convert_common_addr_to_u_addr(NET_IP_PROTOCOL_E eDomain, NET_IP_ADDR_COMMON_P pstCommonAddr, U_IN_ADDR *pstUAddr)
 * @brief      将NET_IP_ADDR_COMMON_T 结构体的ip转换为U_IN_ADDR结构体的ip
 * @param[in]  eDomain: 要转换ip的类型。
 *                          E_IP_PROTOCOL_V4 : ipv4, 转换ipv4部分地址
 *                          E_IP_PROTOCOL_V6 : ipv6, 转换ipv4部分地址
 *                          则按照ipv4地址转换
 * @paramp[in] pstCommonAddr, NET_IP_ADDR_COMMON_P结构体表示的ip地址
 * @param[out] pstHprAddr   , U_IN_ADDR结构体表示的ip地址
 * @note       该接口不对ip合法性进行校验
 * @note       注意U_IN_ADDR不是一个v4和v6类型的联合体，而是一个结构体。因此其中可能同时存在v4和v6信息。
 *             因此进行v4转换时接口内仅会处理v4部分数据，不修改v6部分数据, 反之亦然
 * @return     HPR_OK: sucess; other:fail
 */
AIP_EXTERN HPR_INT32 aip_net_utils_convert_common_addr_to_u_addr(NET_IP_PROTOCOL_E eDomain, NET_IP_ADDR_COMMON_P pstCommonAddr, U_IN_ADDR *pstUAddr);

/**
 * @fn            AIP_EXTERN HPR_INT32 aip_net_utils_convert_hpr_addr_convert_to_string(HPR_ADDR_T *pstAddr, HPR_INT8 *byaBuf, HPR_UINT32 dwBufSize)
 * @brief         解析地址结构体对应的字符串，支持IPv6和IPv4,自动根据pstAddr中的protocol枚举值((struct sockaddr*)pstAddr)->sa_family)选择
 * @param [in]    pstAddr  : 地址结构体
 * @param [out]   byaBuf   : 地址的字符串输出地址
 * @param [in]    dwBufSize: byaBuf的可用长度，建议在40字节(INET_ADDRSTRLEN)已经以上。
 * @return        HPR_OK: success; other: fail
 * @see           inet_pton
 */
AIP_EXTERN HPR_INT32 aip_net_utils_convert_common_addr_to_string(NET_IP_PROTOCOL_E eDomain, NET_IP_ADDR_COMMON_P pstCommonAddr, HPR_INT8 *byaBuf, HPR_UINT32 dwBufSize);

/**
 * @fn          AIP_EXTERN HPR_INT32 aip_net_utils_convert_ip_string_to_structure_auto(HPR_INT8 *szIP, HPR_ADDR_T *pstAddr)
 * @brief       转换字符串格式的ip地址为结构体格式，支持IPv6和IPv4,自动判断所属的ip类型转换
 * @param [in]  szIP    :字符串地址, 应当是一个合法的ipv4或者ipv6地址, see NET_IP_ADDR_STR_LEN and NET_IP_V6_ADDR_STR_LEN define
 * @param [out] pstAddr :输出结构体地址
 * @return      HPR_OK: success; other: fail
 * @see         inet_pton
 */
AIP_EXTERN HPR_INT32 aip_net_utils_convert_string_to_common_addr(NET_IP_PROTOCOL_E eDomain, HPR_INT8 *szIP, NET_IP_ADDR_COMMON_P pstCommonAddr);

/**
 * @brief aip_net_utils_convert_hpr_addr_to_common_addr
 *        将HPR_ADDR_T 结构体的ip转换为NET_IP_ADDR_COMMON_P结构体的ip
 * @param [in] pstHprAddr : HPR_ADDR_T结构体IP
 * @param [out] pstCommonAddr : NET_IP_ADDR_COMMON_P结构体IP
 * @return HPR_OK: success; other: fail
 */
AIP_EXTERN HPR_INT32 aip_net_utils_convert_hpr_addr_to_common_addr(HPR_ADDR_T *pstHprAddr, NET_IP_ADDR_COMMON_P pstCommonAddr);

/**
 * @brief aip_net_utils_convert_hpr_addr_to_u_addr
 *        将HPR_ADDR_T 结构体的ip转换为U_IN_ADDR结构体的ip
 * @param [in] pstHprAddr : HPR_ADDR_T结构体IP
 * @param [out] pstUAddr : U_IN_ADDR结构体IP
 * @return HPR_OK: success; other: fail
 */
AIP_EXTERN HPR_INT32 aip_net_utils_convert_hpr_addr_to_u_addr(HPR_ADDR_T *pstHprAddr, U_IN_ADDR *pstUAddr);

/**
 * @fn            AIP_EXTERN HPR_INT32 aip_net_utils_convert_hpr_addr_convert_to_string(HPR_ADDR_T *pstAddr, HPR_INT8 *byaBuf, HPR_UINT32 dwBufSize)
 * @brief         解析地址结构体对应的字符串，支持IPv6和IPv4,自动根据pstAddr中的protocol枚举值((struct sockaddr*)pstAddr)->sa_family)选择
 * @param [in]    pstAddr  : 地址结构体
 * @param [out]   byaBuf   : 地址的字符串输出地址
 * @param [in]    dwBufSize: byaBuf的可用长度，建议在40字节(INET_ADDRSTRLEN)已经以上。
 * @return        HPR_OK: success; other: fail
 * @see           inet_pton
 */
AIP_EXTERN HPR_INT32 aip_net_utils_convert_hpr_addr_to_string(HPR_ADDR_T *pstAddr, HPR_INT8 *byaBuf, HPR_UINT32 dwBufSize);

/**
 * @fn          AIP_EXTERN HPR_INT32 aip_net_utils_convert_ip_string_to_structure_auto(HPR_INT8 *szIP, HPR_ADDR_T *pstAddr)
 * @brief       转换字符串格式的ip地址为结构体格式，支持IPv6和IPv4,自动判断所属的ip类型转换
 * @param [in]  szIP    :字符串地址, 应当是一个合法的ipv4或者ipv6地址, see NET_IP_ADDR_STR_LEN and NET_IP_V6_ADDR_STR_LEN define
 * @param [out] pstAddr :输出结构体地址
 * @return      HPR_OK: success; other: fail
 * @see         inet_pton
 */
AIP_EXTERN HPR_INT32 aip_net_utils_convert_string_to_hpr_addr(HPR_INT8 *szIP, HPR_ADDR_T *pstAddr);


//@brief: U_IN_ADDR

/**
 * @brief AIP_EXTERN HPR_INT32 aip_net_utils_converty_u_addr_to_common_addr((NET_IP_PROTOCOL_E eDomain, U_IN_ADDR *pstAddrU, HPR_ADDR_T *pstAddr)
 * 将U_IN_ADDR 结构体的ip转换为NET_IP_ADDR_COMMON_P结构体的ip
 * @param[in], eDomain: 要转换ip的类型。
 * @paramp[in] pstUAddr: 被转换的结构体
 * @param[out] pstCommonAddr：转换成的结构体
 * @return HPR_OK: success; other: fail
 */
AIP_EXTERN HPR_INT32 aip_net_utils_convert_u_addr_to_common_addr(NET_IP_PROTOCOL_E eDomain, U_IN_ADDR *pstUAddr, NET_IP_ADDR_COMMON_P pstCommonAddr);

//@note: 之前提供了错误的对外接口，保持兼容
#define aip_net_utils_converty_u_addr_to_common_addr aip_net_utils_convert_u_addr_to_common_addr

/**
 * @brief AIP_EXTERN HPR_INT32 aip_net_utils_convert_u_addr_to_hpr_addr((NET_IP_PROTOCOL_E eDomain, U_IN_ADDR *pstAddrU, HPR_ADDR_T *pstAddr)
 * 将U_IN_ADDR 结构体的ip转换为HPR_ADDR_T结构体的ip
 * @param[in], eDomain: 要转换ip的类型。
 * @paramp[in] pstUAddr: 被转换的结构体
 * @param[out] pstHprAddr：转换成的结构体
 * @return HPR_OK: success; other: fail
 */
AIP_EXTERN HPR_INT32 aip_net_utils_convert_u_addr_to_hpr_addr(NET_IP_PROTOCOL_E eDomain, U_IN_ADDR *pstUAddr, HPR_ADDR_T *pstHprAddr);

/**
 * @fn            AIP_EXTERN HPR_INT32 aip_net_utils_convert_hpr_addr_convert_to_string(HPR_ADDR_T *pstAddr, HPR_INT8 *byaBuf, HPR_UINT32 dwBufSize)
 * @brief         解析地址结构体对应的字符串，支持IPv6和IPv4,自动根据pstAddr中的protocol枚举值((struct sockaddr*)pstAddr)->sa_family)选择
 * @param [in]    pstAddr  : 地址结构体
 * @param [out]   byaBuf   : 地址的字符串输出地址
 * @param [in]    dwBufSize: byaBuf的可用长度，建议在40字节(INET_ADDRSTRLEN)已经以上。
 * @return        HPR_OK: success; other: fail
 * @see           inet_pton
 */
AIP_EXTERN HPR_INT32 aip_net_utils_convert_u_addr_to_string(NET_IP_PROTOCOL_E eDomain, U_IN_ADDR *pstUAddr, HPR_INT8 *byaBuf, HPR_UINT32 dwBufSize);

/**
 * @fn          AIP_EXTERN HPR_INT32 aip_net_utils_convert_ip_string_to_structure_auto(HPR_INT8 *szIP, HPR_ADDR_T *pstAddr)
 * @brief       转换字符串格式的ip地址为结构体格式，支持IPv6和IPv4,自动判断所属的ip类型转换
 * @param [in]  szIP    :字符串地址, 应当是一个合法的ipv4或者ipv6地址, see NET_IP_ADDR_STR_LEN and NET_IP_V6_ADDR_STR_LEN define
 * @param [out] pstAddr :输出结构体地址
 * @return      HPR_OK: success; other: fail
 * @see         inet_pton
 */
AIP_EXTERN HPR_INT32 aip_net_utils_convert_string_to_u_addr(NET_IP_PROTOCOL_E eDomain, HPR_INT8 *szIP, U_IN_ADDR *pstUAddr);


//@brief: in_addr_t
/**
 * @fn          AIP_EXTERN HPR_INT32 aip_net_utils_convert_ntoa_v4(in_addr_t dwIp, HPR_INT8 *byaBuf, HPR_UINT32 dwBufSize);
 * @brief       转换ipv4地址为字符串
 * @param [in]  dwIp     :  ipv4 地址
 * @param [out] byaBuf   : 地址的字符串输出地址
 * @param [in]  dwBufSize: byaBuf的可用长度，建议在40字节(INET_ADDRSTRLEN)已经以上。
 * @return      HPR_OK: success; other: fail
 * @see         inet_pton
 */
AIP_EXTERN HPR_INT32 aip_net_utils_convert_ntoa_v4(in_addr_t dwIp, HPR_INT8 *byaBuf, HPR_UINT32 dwBufSize);

//@brief: domain
/**
 * @fn          AIP_EXTERN HPR_BOOL aip_net_check_domain_legal(const HPR_INT8* szDomain)
 * @brief       校验域名是否合法(注意合法不代表有效也不代表网络通畅)
 * @param [in]  szDomain : 用于校验的域名地址，应该是一个以‘\0’截断的字符串, see NET_DOMAIN_NAME_LEN;
 * @note        域名可以由（a-z、A-Z大小写等价）26个英文字母、数字（0-9）以及连接符“-”组成，域名的首位必须是字母或数字，域名长度不小于3个字符，不超过63个字符，域名至少包含主体和后缀，即最少有一个.分隔符,每段不超过62个字符
 * @return      HPR_TRUE: 合法域名; HPR_FLASE: 非法域名
 */
AIP_EXTERN HPR_BOOL aip_net_check_domain_legal(const HPR_INT8* szDomain);

#ifdef __cplusplus
}
#endif
#endif /* __AIP_NET_UTILS_H__ END */
