/**
 * @copyright HangZhou Hikvision Digital Technology Co., Ltd. All Right Reserved.
 * @file      aip_net_status.h
 * @brief     网络状态查询接口
 * @brief     网卡优先级相关接口
**/
#ifndef __AIP_NET_STATUS_H__
#define __AIP_NET_STATUS_H__

/************************************************************************
 Included Header
 ************************************************************************/
#include "HPR_Types.h"
#include "netMng/aip_net_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/************************************************************************
 Macros
 ************************************************************************/
#define NET_IF_PRIORITY_MODULE_LEN   32  // 注册优先级的模块名长度限制(包含截断符)
#define NET_IF_PRIORITY_IF_NUM       4  // 注册优先级的网卡个数限制

/************************************************************************
 Type Definition
 ************************************************************************/
typedef enum
{
    E_NET_STATUS_NET_BROKEN  = 1,  // 网络断开
    E_NET_STATUS_NET_CONNECT = 2,  // 网络连接
    E_NET_STATUS_NET_INVALID = 3,  // 非法
} NET_CONNECT_STATUS_E;

// @brief: 网卡优先级信息,按照排在前面的网卡高优先级
// @note : 当前仅支持配置E_NIC_ETH0、E_NIC_ETH1、E_NIC_WLAN0、E_NIC_PPP0 的优先级
// @note : 多余无效值请设置成E_NIC_INVALID;
typedef struct
{
    NET_INTERFACE_CARD_E eNicIdx[NET_IF_PRIORITY_IF_NUM];
} NET_IF_PRIORITY_INFO_T, *NET_IF_PRIORITY_INFO_P;

/**
 * @fn         AIP_EXTERN HPR_BOOL aip_net_check_netcard_connect_status(HPR_INT8 *szNicName)
 * @brief      获取指定网卡的网络链接状态
 * @param[in]  szNicName: 网卡名称
 * @return     HPR_TRUE: 网卡在线(仅代表网卡处于使能状态且存在有效连接(指有线网卡存在网线连接,无线网卡存在有效wifi链接),不代表网络真正通畅)
 *             HPR_FALSE: 网卡不存在或处于失能状态或无有效链接
**/
AIP_EXTERN HPR_BOOL aip_net_check_netcard_connect_status(HPR_INT8 *szNicName);

/**
 * @fn         AIP_EXTERN HPR_BOOL aip_net_check_connect_status(HPR_VOID)
 * @brief      获取网络是否在线
 * @note       任一网卡在线均视为在线，无一网卡在线则视为不在线
 * @return     HPR_TRUE: 网卡在线(仅代表网卡处于使能状态且存在有效连接(指有线网卡存在网线连接,无线网卡存在有效wifi链接),不代表网络真正通畅)
 *             HPR_FALSE: 网卡不存在或处于失能状态或无有效链接
**/
AIP_EXTERN HPR_BOOL aip_net_check_connect_status(HPR_VOID);

/**
 * @fn        AIP_EXTERN HPR_INT32 aip_net_set_interface_priority(NET_IF_PRIORITY_INFO_P pstPriorityInfo, HPR_INT8 *szModuleName)
 * @brief     设置网卡优先级网卡
 * @param[in] pstPriorityInfo : 优先级配置
 * @param[in] szModuleName      要配置优先级的模块名，若为NULL,表示通用配置
                                若制定了模块名, 字符串有效长度应该小于NET_IF_PRIORITY_MODULE_LEN
 * @return    HPR_OK:success, other:fail
 * @note  默认通用优先级 eth0 > eth1 > wlan0 > ppp0
*/
AIP_EXTERN HPR_INT32 aip_net_set_interface_priority(NET_IF_PRIORITY_INFO_P pstPriorityInfo, HPR_INT8 *szModuleName);

/**
 * @fn        AIP_EXTERN NET_INTERFACE_CARD_E aip_net_get_interface_by_priority(HPR_INT8 *szModuleName)
 * @brief     根据当前网卡优先级配置返回应该使用的网卡索引值
 * @param[in] szModuleName      要查询优先级的模块名，若为NULL,表示通用配置
                                若要查询的模块名未配置，也根据通用配置返回
 * @return    success: 网卡索引值, fail: E_NIC_INVALID
 * @note  默认通用优先级 eth0 > eth1 > wlan0 > ppp0
*/
AIP_EXTERN NET_INTERFACE_CARD_E aip_net_get_interface_by_priority(HPR_INT8 *szModuleName);

/**
 * @fn        AIP_EXTERN HPR_INT32 aip_net_del_interface_priority(HPR_INT8 *szModuleName);
 * @brief     删除指定模块的网卡优先级配置
 * @param[in] szModuleName      要配置优先级的模块名，若为NULL,表示通用配置
                                若制定了模块名, 字符串有效长度应该小于NET_IF_PRIORITY_MODULE_LEN
 * @return    HPR_OK:success, other:fail
 * @note     没有找到也视为成功,返回HPR_OK
*/
AIP_EXTERN HPR_INT32 aip_net_del_interface_priority(HPR_INT8 *szModuleName);

/**
 * @fn             AIP_EXTERN HPR_VOID aip_net_interface_priority_list_reset(HPR_VOID)
 * @brief          清空维护的网卡优先级列表
**/
AIP_EXTERN HPR_VOID aip_net_interface_priority_list_reset(HPR_VOID);



#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* __AIP_NET_STATUS_H__ END */
