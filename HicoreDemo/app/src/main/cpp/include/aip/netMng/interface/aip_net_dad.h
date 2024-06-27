/**
 * @copyright HangZhou Hikvision Digital Technology Co., Ltd. All Right Reserved.
 * @file      aip_net_dad.h
 * @brief     网络冲突检测服务
 * @note      支持ipv6和ipv4
 */
#ifndef __AIP_NET_DAD_H__
#define __AIP_NET_DAD_H__

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

/************************************************************************
 Type Definition
 ************************************************************************/

/************************************************************************
  Function Declaration
 ************************************************************************/

/**
 * @fn         AIP_EXTERN HPR_BOOL aip_net_dad_check_ip_conflict(NET_INTERFACE_CARD_E eNicIdx);
 * @brief      校验当前网卡Ip冲突状态
 * @param[in]  eNicIdx: 校验的网卡索引
 * @return     HPR_FLASE-不存在ip冲突；HPR_TRUE-存在ip冲突
 * @note       若传递的eNicIdx为非法参，将返回 HPR_FLASE
*/
AIP_EXTERN HPR_BOOL aip_net_dad_check_ip_conflict(NET_INTERFACE_CARD_E eNicIdx);

/* 编写单元测试用例时需要获取这些函数做一些准备工作*/
#ifdef TEST_USE_INTERNAL_FUNC

/**@fn       HPR_INT32 aip_net_dad_service_start(HPR_VOID)
 * @brief    开启ip冲突检测服务
 * @note     服务成功启动后将会常住一个名为"net_dad_task"
 *           的监测线程(线程优先级20)，线程加入软件看门狗检测，监测周期为 100s
 *           100s失败将会触发软件看门狗异常
 * @return   HPR_OK: success； other:fail
 */
AIP_EXTERN HPR_INT32 aip_net_dad_service_start(HPR_VOID);

/**@fn       HPR_INT32 aip_net_dad_service_stop(HPR_VOID)
 * @brief    关闭ip冲突检测服务
 * @return   HPR_OK: success； other:fail
 */
AIP_EXTERN HPR_INT32 aip_net_dad_service_stop(HPR_VOID);
#endif

/**@fn             AIP_EXTERN HPR_INT32 aip_net_dad_set_interval(HPR_UINT32 dwInterval)
 * @brief          设置主动ip冲突检测的周期
 * @dwInterval[in] :ip检测周期，单位s, 默认为60s
 * @return         HPR_OK: success； other:fail
 */
AIP_EXTERN HPR_INT32 aip_net_dad_set_interval(HPR_UINT32 dwInterval);

/**@fn             AIP_EXTERN HPR_UINT32 aip_net_dad_get_interval(HPR_VOID)
 * @brief          获取主动ip冲突检测的周期
 * @return         ip检测周期，单位s
 */
AIP_EXTERN HPR_UINT32 aip_net_dad_get_interval(HPR_VOID);


#ifdef __cplusplus
}
#endif
#endif /* __AIP_NET_DAD_H__ END */
