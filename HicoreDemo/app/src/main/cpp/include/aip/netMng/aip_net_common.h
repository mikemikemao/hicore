/**
 * @copyright HangZhou Hikvision Digital Technology Co., Ltd. All Right Reserved.
 * @file      aip_net_common.h
 * @brief     网络公共基础定义
 */

#ifndef __AIP_NET_COMMON_H__
#define __AIP_NET_COMMON_H__

/************************************************************************
 Included Header
 ************************************************************************/
#include "common/aip_common.h"
#include "lstLib.h"
#include <netinet/in.h>

#ifdef __cplusplus
extern "C" {
#endif

/************************************************************************
 Macros
 ************************************************************************/
#define NET_IF_NAME_LEN        (16)    /* 网卡设备名称长度上限 */
#define NET_NIC_MAX_NUM        (4)    // 支持的最大网卡个数

//@brief 网卡名
//@see   NET_INTERFACE_CARD_E
#define NET_IF_NAME_ETH0  "eth0"
#define NET_IF_NAME_ETH1  "eth1"
#define NET_IF_NAME_ETH2  "eth2"
#define NET_IF_NAME_WLAN0 "wlan0"
#define NET_IF_NAME_PPP0  "ppp0"
#define NET_IF_NAME_USB0  "usb0"
#define NET_IF_NAME_USB1  "usb1"
#define NET_IF_NAME_LOOP  "lo"
#define NET_IF_NAME_EN1   "en1"

#define NET_IP_ADDR_STR_LEN    (16)     /* ipv4 地址字符串格式长度 */
#define NET_IP_V6_ADDR_STR_LEN (48)     /* ipv6 地址字符串格式长度 */
#define NET_DOMAIN_NAME_LEN    (64)     /* 域名长度(包含截断符)*/
#define NET_IP_COMMON_ADDR_STR_LEN NET_IP_V6_ADDR_STR_LEN /* ip 地址字符串格式长度 */
#define NET_IP_ADDR_BIT_LEN    (32)     /* ipv4 地址bit位长度 */
#define NET_IP_V6_ADDR_BIT_LEN (128)    /* ipv6 地址bit位长度 */
#define NET_MAC_ADDR_LEN       (6)      /* mac 地址格式长度(非字符串) */

//@brief dns
#define NET_DNS_MAX_NUM        (2)                     /* 支持最大的dns个数*/
#define NET_DNS_ADDR_STR_LEN   NET_IP_V6_ADDR_STR_LEN /* dns 地址字符串格式长度*/

/*  Max number when getting router advertisement address. */
#define NET_IP_RA_ADDR_MAX_NUM (8)
/************************************************************************
 Type Definition
 ************************************************************************/

//@brief 网卡索引号
typedef enum 
{
    E_NIC_ETH0       = 0,   // @see NET_IF_NAME_ETH0 define
    E_NIC_ETH1       = 1,   // @see NET_IF_NAME_ETH1  define
    E_NIC_ETH2       = 2,   // @see NET_IF_NAME_ETH2  define
    E_NIC_WLAN0      = 3,   // @see NET_IF_NAME_WLAN0 define
    E_NIC_PPP0       = 4,   // @see NET_IF_NAME_PPP0  define
    E_NIC_USB0       = 5,   // @see NET_IF_NAME_USB0  define
    E_NIC_USB1       = 6,   // @see NET_IF_NAME_USB1  define
    E_NIC_LOOP       = 7,   // @see NET_IF_NAME_LOOP  define
    E_NIC_EN1        = 8,   // @see NET_IF_NAME_EN1  define
    E_NIC_INVALID,          // 不支持的网卡
} NET_INTERFACE_CARD_E;


//@brief: ip协议版本
typedef enum
{
    E_IP_PROTOCOL_V4      = 0,             // ipv4
    E_IP_PROTOCOL_V6      = 1,             // ipv6
    E_IP_PROTOCOL_AUTO    = 2,             // 自动,一些接口支持提供auto来根据入参自动判断协议类型
    E_IP_PROTOCOL_INVALID = 3,             // 非法
} NET_IP_PROTOCOL_E;

//@brief: ip 信息,v4v6同样的联合体
typedef struct 
{
    union
    {
        struct in_addr  stAddressV4; //IPV4地址
        struct in6_addr stAddressV6; //IPV6地址
    } data;

#define  addr_ipAddressV4   data.stAddressV4     //IPV4地址
#define  addr_ipAddressV6   data.stAddressV6     //IPV6地址
} NET_IP_ADDR_COMMON_T, *NET_IP_ADDR_COMMON_P;

//@brief: ip 信息,v4v6同样的联合体
typedef struct
{
    NET_IP_ADDR_COMMON_T stIpaddr;
#define info_ipAddressV4   stIpaddr.addr_ipAddressV4     // IPV4地址
#define info_ipAddressV6   stIpaddr.addr_ipAddressV6     // IPV6地址

    HPR_UINT32           dwPrefixLen;           // 子网掩码长度

} NET_IP_INFO_COMMON_T, *NET_IP_INFO_COMMON_P;

/**
 * @brief DNS参数结构体
 * @note  内含多个dns地址，序号小的相对优先级高
 * @note  支持ipv6和ipv4
**/
typedef struct
{
    HPR_INT8 byaDnsAddr[NET_DNS_MAX_NUM][NET_DNS_ADDR_STR_LEN];  //字符串格式, 全0为无效dns
} NET_DNS_T, *NET_DNS_P;


typedef struct U_IN_ADDR
{                       /* 24 bytes */
    struct in_addr v4;  /* IPv4地址 */
    struct in6_addr v6; /* IPv6地址 */
    HPR_UINT8 res[4];
} U_IN_ADDR;

/******************************************************************************
 * @struct:	NET_IP_RA_ADDR_NODE
 * @brief:	路由公告地址链表节点
 * @author: xiaoxinyu
 *****************************************************************************/
typedef struct NET_IP_RA_ADDR_NODE
{
    NODE node;
    struct in6_addr stIpAddr;
    struct in6_addr stNetmask;
} NET_IP_RA_ADDR_NODE_T, *NET_IP_RA_ADDR_NODE_P;

typedef LIST NET_IP_RA_ADDR_LIST;
/************************************************************************
  Function Declaration
 ************************************************************************/

/************************************************************************
  Function Declaration
 ************************************************************************/

/**
 * @fn          AIP_EXTERN HPR_INT8* aip_net_get_nic_name_by_index(NET_INTERFACE_CARD_E eNicIdx);
 * @brief       获取指定网卡索引的网卡名
 * @param [in]  eNicIdx : 网卡索引号
 * @return      success: 网卡名字符串，fail: NULL
 * @note        返回了网卡名只代表对应网卡索引对应的网卡名存在，不代表网卡存在
 * @see         NET_INTERFACE_CARD_E
**/
AIP_EXTERN HPR_INT8* aip_net_get_nic_name_by_index(NET_INTERFACE_CARD_E eNicIdx);

/**
 * @fn          AIP_EXTERN NET_INTERFACE_CARD_E aip_net_get_index_nic_by_name(HPR_INT8 *szNicName)
 * @brief       获取指定网卡名网卡的索引
 * @param [in]  szNicName: 网卡名
 * @return      success: 网卡索引值，fail(如不支持的网卡名): E_NIC_INVALID
 * @see         NET_INTERFACE_CARD_E
**/
AIP_EXTERN NET_INTERFACE_CARD_E aip_net_get_index_nic_by_name(HPR_INT8 *szNicName);

#ifdef __cplusplus
}
#endif

#endif /* __AIP_NET_COMMON_H__ */
