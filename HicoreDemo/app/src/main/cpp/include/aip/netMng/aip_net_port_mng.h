/**
 * @copyright HangZhou Hikvision Digital Technology Co., Ltd. All Right Reserved.
 * @file      aip_net_port_mng.h
 * @brief     端口服务管理
 */
#ifndef __AIP_NET_PORT_MNG__
#define __AIP_NET_PORT_MNG__

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

#define NET_PROT_SERVICE_LEN   32  //注册端口的服务名称长度限制(包含截断符)

/************************************************************************
 Type Definition
 ************************************************************************/

//@brief 绑定端口的协议类型
typedef enum 
{
    E_BIND_PORT_PROTOCOL_TCP       = 0,          //tcp
    E_BIND_PORT_PROTOCOL_UDP       = 1,          //udp
    E_BIND_PORT_PROTOCOL_INVALID   = 2,
} NET_BIND_PORT_PROTOCOL_E;


/************************************************************************
  Function Declaration
 ************************************************************************/
/**
 * @fn      HPR_INT32 aip_net_port_mng_init(HPR_VOID)
 * @brief   端口服务管理初始化
 * @return  HPR_OK: success; other: fail
**/
HPR_INT32 aip_net_port_mng_init(HPR_VOID);

/**
 * @fn      HPR_INT32 aip_net_port_mng_fini(HPR_VOID)
 * @brief   端口服务管理反初始化
 * @return  HPR_OK: success; other: fail
**/
HPR_INT32 aip_net_port_mng_fini(HPR_VOID);

/**
 * @fn         AIP_EXTERN HPR_INT32 aip_net_port_bind(NET_BIND_PORT_PROTOCOL_E eProtocolType, HPR_UINT16 wPort, HPR_INT8 *szServiceName)
 * @brief      向端口管理服务申请绑定一个端口
 * @param[in]  eProtocolType  : 端口协议类型,TCP or UDP
 * @param[in]  wPort          : 端口
 * @param[in]  szServiceName  : 要绑定这个端口的服务名称,如果提供长度应该保证小于NET_IF_PROT_SERVICE_LEN, 如果提供的服务
 * 名称已经bind过，将会进行修改该服务的端口
 *                              允许为NULL，如果为NULL,则会增加绑定到一个匿名服务
 * @return     HPR_OK:success, other:fail
**/
AIP_EXTERN HPR_INT32 aip_net_port_bind(NET_BIND_PORT_PROTOCOL_E eProtocolType, HPR_UINT16 wPort, HPR_INT8 *szServiceName);

/**
 * @fn         AIP_EXTERN HPR_INT32 aip_net_port_unbind(NET_BIND_PORT_PROTOCOL_E eProtocolType, HPR_UINT16 wPort)
 * @brief      向端口管理服务解绑一个端口
 * @param[in]  eProtocolType  : 端口协议类型,TCP or UDP
 * @param[in]  wPort          : 端口
 * @return     HPR_OK:success, other:fail
**/
AIP_EXTERN HPR_INT32 aip_net_port_unbind(NET_BIND_PORT_PROTOCOL_E eProtocolType, HPR_UINT16 wPort);

/**
 * @fn         AIP_EXTERN HPR_INT32 aip_net_port_unbind_by_name(HPR_INT8 *szServiceName)
 * @brief      向端口管理服务解绑一个服务的绑定端口
 * @param[in]  szServiceName  : 要绑定这个端口的服务名称,提供长度应该保证小于NET_IF_PROT_SERVICE_LEN
 *                              仅限绑定时提供了服务名称的端口采用这种方式解绑
 * @return     HPR_OK:success, other:fail
**/
AIP_EXTERN HPR_INT32 aip_net_port_unbind_by_name(HPR_INT8 *szServiceName);

#ifdef __cplusplus
}
#endif
#endif /* __AIP_NET_PORT_MNG__ END */
