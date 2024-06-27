/**
 * @copyright  HangZhou Hikvision Digital Technology Co., Ltd. All Right Reserved.
 * @file       aip_utils_communication.h
 * @brief      通信常用通用接口
**/
#ifndef __AIP_UTIL_COMMUNICATION_H__
#define __AIP_UTIL_COMMUNICATION_H__

/************************************************************************
 Included Header
 ************************************************************************/
#include <sys/time.h>
#include "lstLib.h"

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

/** * @brief IP地址列表**/
typedef struct
{
    NODE node;                                 /*链表节点*/
    NET_IP_PROTOCOL_E    eDomain;              // ip协议版本
    NET_IP_ADDR_COMMON_T stIpAddr;             // ip地址
} AIP_ADDR_INFO_NODE_T, *AIP_ADDR_INFO_NODE_P;

typedef LIST AIP_ADDR_INFO_LIST;         /* ip地址列表, 每个链表节点结构体为 AIP_ADDR_INFO_NODE_P*/

/************************************************************************
 Function Declaration
 ************************************************************************/


/**
 * @fn        AIP_EXTERN HPR_INT32 aip_utils_net_connect_with_timeout(HPR_INT32 sdwSocket, struct sockaddr* pstAddrs, HPR_UINT32 dwAddrsLen, HPR_INT32 sdwMSecond)
 * @brief     连接服务器，可设置阻塞超时时间
 * @param[in] sdwSocket  : 网络socket句柄。范围:大于0
 * @param[in] pstAddrs   : 包含协议簇、服务器ip和端口号等信息。
 * @param[in] dwAddrsLen : pstAddrs地址指向的结构体有效长度
 * @param[in] sdwMSecond : 连接超时时间. 若为0 表示不等待，如为-1表示无限制等待. 若为一个正整数，表示等待的链接超时时间（ms为单位）
 * @return    HPR_OK: success, other:fail
 * @note      接口内部接口将会绑定网卡进行connect，绑定的网卡按照当前优先级选取最优的在线网卡  @see aip_net_get_interface_by_priority
 */
AIP_EXTERN HPR_INT32 aip_utils_net_connect_with_timeout(HPR_INT32 sdwSocket, struct sockaddr* pstAddrs, HPR_UINT32 dwAddrsLen, HPR_INT32 sdwMSecond);

/**
 * @fn        AIP_EXTERN HPR_INT32 aip_utils_readn_with_timeout(HPR_INT32 sdwConnfd, HPR_VOIDPTR pbyDataBuf, HPR_UINT32 dwDataLen, struct timeval *pstTimeout)
 * @brief     在超时时间内，从网络缓冲区中读取n个字节数据
 * @param[in] sdwConnfd  : 接收的网络句柄，这里指与socket对应的fd
 * @param[in] pbyDataBuf : 接收数据的缓冲区指针
 * @param[in] dwDataLen  : 需要接收的数据的长度
 * @param[in] pstTimeout : 超时时间 允许为NULL，当NULL时表示死等
 * @return    -1: 表示发送失败，其他值表示实际接收到的字节数
 * @note      如指定了一个超时时间，将会返回超时时间内实际接收到的长度(可能是0)，
 *            如未指定一个超时时间，该接口将会直到接受到了dwDataLen或者异常时才会返回
**/
AIP_EXTERN HPR_INT32 aip_utils_readn_with_timeout(HPR_INT32 sdwConnfd, HPR_VOIDPTR pbyDataBuf, HPR_UINT32 dwDataLen, struct timeval *pstTimeout);

/**
 * @fn        AIP_EXTERN HPR_INT32 aip_utils_writen_with_timeout(HPR_INT32 sdwConnfd, HPR_VOIDPTR pbyDataBuf, HPR_UINT32 dwDataLen, struct timeval *pstTimeout)
 * @brief     在超时时间内，发送n个字节数据
 * @param[in] sdwConnfd  : 发送的网络句柄，这里指与socket对应的fd
 * @param[in] pbyDataBuf : 发送数据的缓冲区指针
 * @param[in] dwDataLen  : 需要发送的数据的长度
 * @param[in] pstTimeout : 超时时间 允许为NULL，当NULL时表示死等
 * @return    -1: 表示发送失败，其他值表示实际发送到的字节数
 * @note      如指定了一个超时时间，将会返回超时时间内实际发送到的长度(可能是0)，
 *            如未指定一个超时时间，该接口将会直到发送到了dwDataLen或者异常时才会返回
**/
AIP_EXTERN HPR_INT32 aip_utils_writen_with_timeout(HPR_INT32 sdwConnfd, HPR_VOIDPTR pbyDataBuf, HPR_UINT32 dwDataLen, struct timeval *pstTimeout);

/**
 * @fn         AIP_EXTERN HPR_INT32 aip_utils_net_get_peer_addr(HPR_INT32 sdwConnfd, NET_IP_ADDR_COMMON_P pstIpAddr)
 * @brief      获取socket链接的对端ip地址
 * @param[in]  sdwConnfd  : socket句柄
 * @param[out] peDomain   : 对端ip地址协议簇类型
 *                          E_IP_PROTOCOL_V4 : ipv4
 *                          E_IP_PROTOCOL_V6 : ipv6
 * @note       ipv6链路但是是ipv4映射地址也会返回对应的ipv4地址
 * @param[out] pstIpAddr  : ip地址
 * @return    HPR_OK: success; other: fail
**/
AIP_EXTERN HPR_INT32 aip_utils_net_get_peer_addr(HPR_INT32 sdwConnfd, NET_IP_PROTOCOL_E *peDomain, NET_IP_ADDR_COMMON_P pstIpAddr);

/**
 * @fn         AIP_EXTERN AIP_ADDR_INFO_LIST* aip_utils_net_get_addr_list_by_domain(HPR_INT8* szDomain, NET_IP_PROTOCOL_E eIpProtocol, HPR_INT8* szNicName)
 * @note       同 aip_utils_net_get_addr_list_by_domain_with_timeout(szDomain, eIpProtocol, szNicName, -1)
**/
AIP_EXTERN AIP_ADDR_INFO_LIST* aip_utils_net_get_addr_list_by_domain(HPR_INT8* szDomain, NET_IP_PROTOCOL_E eIpProtocol, HPR_INT8* szNicName);

/**
 * @fn         AIP_EXTERN AIP_ADDR_INFO_LIST* aip_utils_net_get_addr_list_by_domain_with_timeout(HPR_INT8* szDomain, NET_IP_PROTOCOL_E eIpProtocol, HPR_INT8* szNicName, HPR_INT32 sdwMSecond)
 * @brief      dns解析 通过域名解析ip地址
 * @param[in]  szDomain   : 要查找的域名， see NET_DOMAIN_NAME_LEN define
 * @param[in]  eIpProtocol: 要查找的ip协议簇
 *                          E_IP_PROTOCOL_V4 : ipv4
 *                          E_IP_PROTOCOL_V6 : ipv6
 *                          E_IP_PROTOCOL_AUTO : ipv4和ipv6
 * @param[in]  szNicName  : 要限定的网卡名， see NET_IF_NAME_LEN define
 *                          允许为NULL，当NULL时表示不限制网卡
 * @param[in]  sdwMSecond : 连接超时时间. 若为0 表示不等待，如为-1表示无限制等待. 若为一个正整数，表示等待的链接超时时间（ms为单位, 当前内部精度只有100ms，更精确的配置将会被忽略）
 * @return  success: 解析到的ip地址列表, 返回的链表声明周期结束后，需要显示的调用aip_util_release_addr_list 释放
 *          fail   : NULL
**/
AIP_EXTERN AIP_ADDR_INFO_LIST* aip_utils_net_get_addr_list_by_domain_with_timeout(HPR_INT8* szDomain, NET_IP_PROTOCOL_E eIpProtocol, HPR_INT8* szNicName, HPR_INT32 sdwMSecond);

/**
 * @fn         AIP_EXTERN HPR_INT32 aip_util_release_addr_list(AIP_ADDR_INFO_LIST* pList)
 * @brief      释放ip地址链表信息
 * @param [in] pList： 要释放的链表地址
 * @return     HPR_OK: success; other:fail
**/
AIP_EXTERN HPR_INT32 aip_util_release_addr_list(AIP_ADDR_INFO_LIST* pList);

#ifdef __cplusplus
}
#endif
#endif /* __AIP_UTIL_COMMUNICATION_H__ END */
