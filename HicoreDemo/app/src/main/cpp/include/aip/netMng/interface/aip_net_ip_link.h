/**
 * @copyright HangZhou Hikvision Digital Technology Co., Ltd. All Right Reserved.
 * @file     aip_net_ip_link.h
 * @brief    网络设备配置相关接口
 * @note     如启用/禁用某个网卡，改变MTC以及MAC地址
 */
#ifndef __AIP_NET_IP_LINK_H__
#define __AIP_NET_IP_LINK_H__

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
//@brief 以太网卡(有线网卡)工作模式
//@note  枚举定义与原有基线定义保持一致
typedef enum
{
    E_ETH_IF_10M_HALF          = 1,  /* 10M 半双工 */
    E_ETH_IF_10M_FULL          = 2,  /* 10M 全双工 */
    E_ETH_IF_100M_HALF         = 3,  /* 100M 半双工 */
    E_ETH_IF_100M_FULL         = 4,  /* 100M 全双工 */
    E_ETH_IF_AUTO              = 5,  /* 全自动 */
    E_ETH_IF_1000M_FULL        = 6,  /* 1000M 全双工 */
    E_ETH_IF_INVALID_WORK_MODE = 7,  /* 失效 */
} NET_ETH_IF_WORK_MODE_E;

/************************************************************************
  Function Declaration
 ************************************************************************/

/**
 * @fn         AIP_EXTERN HPR_INT32 aip_net_if_up(HPR_INT8 *szNicName)
 * @brief      使能指定网卡
 * @param[in]  szNicName : 网络接口名称
 * @return     HPR_OK:success, other:fail
**/
AIP_EXTERN  HPR_INT32 aip_net_if_up(HPR_INT8 *szNicName);

/**
 * @fn         AIP_EXTERN HPR_INT32 aip_net_if_down(HPR_INT8 *szNicName)
 * @brief      失能指定网卡
 * @param[in]  szNicName : 网络接口名称
 * @return     HPR_OK:success, other:fail
**/
AIP_EXTERN HPR_INT32 aip_net_if_down(HPR_INT8 *szNicName);

/**
 * @fn          AIP_EXTERN HPR_INT32 aip_net_get_mac(HPR_INT8 *szNicName, HPR_INT8 pbyMacAddr[NET_MAC_ADDR_LEN])
 * @brief       获取指定网卡名的网卡mac地址(注意非字符串)
 * @param[in]   szNicName   : 网络接口名称
 * @param[out]  pbyMacAddr  : mac地址
 * @return      HPR_OK:success, other:fail
**/
AIP_EXTERN HPR_INT32 aip_net_get_mac(HPR_INT8 *szNicName, HPR_INT8 pbyMacAddr[NET_MAC_ADDR_LEN]);

/**
 * @fn          AIP_EXTERN HPR_INT32 aip_net_set_mac(HPR_INT8 *szNicName, HPR_INT8 pbyMacAddr[NET_MAC_ADDR_LEN])
 * @brief       设置mac地址(注意非字符串)
 * @param[in]   szNicName    : 网络接口名称
 * @param[in]   pbyMacAddr   : 要设置mac地址
 * @return      HPR_OK:success, other:fail
**/
AIP_EXTERN HPR_INT32 aip_net_set_mac(HPR_INT8 *szNicName, HPR_INT8 pbyMacAddr[NET_MAC_ADDR_LEN]);

/**
 * @fn         AIP_EXTERN HPR_INT32 aip_net_set_mtu(HPR_INT8 *szNicName, HPR_UINT32 dwMTU);
 * @brief      设置指定网卡的MTU值
 * @param [in] szNicName: 网络接口名称
 * @param [in] dwMTU : MTU， 要求大于68且小于等于1500
 * @return     HPR_OK:success, other:fail
**/
AIP_EXTERN HPR_INT32 aip_net_set_mtu(HPR_INT8 *szNicName, HPR_UINT32 dwMTU);

/**
 * @fn         AIP_EXTERN HPR_INT32 aip_net_set_eth_if_work_mode(HPR_INT8 *szNicName, NET_ETH_IF_WORK_MODE_E)
 * @brief      设置以太网卡类型
 * @param [in] szNicName: 网络接口名称
 * @param [in] eWorkMode: 网卡工作模式
 * @return     HPR_OK:success, other:fail
**/
AIP_EXTERN HPR_INT32 aip_net_set_eth_if_work_mode(HPR_INT8 *szNicName, NET_ETH_IF_WORK_MODE_E eWorkMode);

/**
 * @fn         AIP_EXTERN HPR_INT32 aip_net_get_eth_if_work_mode_config(HPR_INT8 *szNicName, NET_ETH_IF_WORK_MODE_E)
 * @brief      返回当前网卡工作模式配置
 * @param [in] szNicName: 网络接口名称
 * @note       注意与aip_net_get_eth_if_work_mode_status所区分；如果配置项为自动，设备实际状态协商后的速率配置为1000M则
 *             该接口会返回E_ETH_IF_AUTO,而非E_ETH_IF_1000M_FULL
 * @return     success: 返回当前网卡工作模式配置:, fail:E_ETH_IF_INVALID_WORK_MODE
**/
AIP_EXTERN NET_ETH_IF_WORK_MODE_E aip_net_get_eth_if_work_mode_config(HPR_INT8 *szNicName);

/**
 * @fn         AIP_EXTERN HPR_INT32 aip_net_get_eth_if_work_mode_status(HPR_INT8 *szNicName, NET_ETH_IF_WORK_MODE_E)
 * @brief      返回当前网卡工作模式状态
 * @param [in] szNicName: 网络接口名称
 * @note       注意与aip_net_get_eth_if_work_mode_config所区分；如果配置项为自动，设备实际状态协商后的速率配置为1000M则
 *             该接口会返回E_ETH_IF_1000M_FULL,而非E_ETH_IF_AUTO
 * @return     success: 返回当前网卡工作模式状态:, fail:E_ETH_IF_INVALID_WORK_MODE
**/
AIP_EXTERN NET_ETH_IF_WORK_MODE_E aip_net_get_eth_if_work_mode_status(HPR_INT8 *szNicName);

#ifdef __cplusplus
}
#endif
#endif /* __AIP_NET_IP_LINK_H__ END */
