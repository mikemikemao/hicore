/**
 * @copyright  HangZhou Hikvision Digital Technology Co., Ltd. All Right Reserved.
 * @file       aip.h
 * @brief      aip层对外总接口
**/

#ifndef __AIP_H__
#define __AIP_H__

/************************************************************************
 Included Header
 ************************************************************************/

#include "aip_build_config.h"

#include "common/aip_common.h"
#include "common/aip_common_event.h"
#include "utils/aip_utils_base.h"
#include "utils/aip_utils_code_convert.h"
#include "utils/aip_utils_file_process.h"
#include "utils/aip_utils_string_deal.h"
#include "utils/aip_utils_communication.h"

#include "utilDebug/aip_util_debug.h"

#include "shell/aip_shell_server.h"

#include "exception/aip_exception.h"
#include "exception/watchdog/aip_watchdog.h"

#include "securityMng/aip_security_lock_manage.h"
#include "securityMng/aip_security_user_utils.h"

#include "timeMng/aip_time_common.h"
#include "timeMng/aip_time_mng.h"
#include "timeMng/aip_time_utils.h"

#include "netMng/aip_net_mng.h"
#include "netMng/aip_net_common.h"
#include "netMng/aip_net_port_mng.h"
#include "netMng/interface/aip_net_config.h"
#include "netMng/interface/aip_net_dad.h"
#include "netMng/interface/aip_net_utils.h"
#include "netMng/interface/aip_net_status.h"
#include "netMng/interface/aip_net_ip_link.h"
#include "netMng/interface/aip_net_ip_addr.h"

#include "netMng/wifi/aip_net_wifi.h"
#include "netMng/cellular/aip_net_cellular_mobile.h"

#include "devMng/aip_usb_mng.h"
#include "devMng/aip_dev_bluetooth.h"
#include "appMng/aip_app_mng.h"

#ifdef __cplusplus
extern "C" {
#endif

/************************************************************************
 Macros
 ************************************************************************/

/************************************************************************
 Type Definition
 ************************************************************************/

/** @brief  平台层 初始化参数*/
typedef struct
{
    AIP_EVENT_CALLBACK_FUN    fnCbFun;                  // [in], 回调函数
    EXCEPTION_PARAM_T         stExceptionInfo;          // [in], 异常模块参数
    SHELL_SERVICE_PARAM_T     stShellInfo;              // [in], shell调试命令模块参数
    HPR_BOOL                  bEnableSecuriyUserLock;   // [in], 是否使能安全用户锁定模块
    HPR_BOOL                  bEnableTimeMng;           // [in], 是否使能时间模块
    TIME_INIT_T               stTimeInfo;               // [in], 时间管理模块, 当bEnableNetMng 为HPR_TRUE时有效 AIP_INIT_PARAM_T, *AIP_INIT_PARAM_P;
    HPR_BOOL                  bEnableNetMng;            // [in], 是否使能网络模块
    NET_MNG_PARAM_T           stNetInfo;                // [in], 网络模块参数，当bEnableNetMng 为HPR_TRUE时有效
    HPR_BOOL                  bEnableBLEMng;            // [in], 是否使能蓝牙模块
    AIP_BLUETOOTH_PARAM_T     stBLEParam;               // [in], 蓝牙模块参数，当bEnableBLEMng 为HPR_TRUE时有效
    HPR_BOOL                  bDisableSecurityResource; // [in], 是否失能安全存储密钥初始化
    HPR_INT8                  byaRes[124];              // [in], 预留参数
} AIP_INIT_PARAM_T, *AIP_INIT_PARAM_P;

/************************************************************************
 Function Declaration
 ************************************************************************/

/**
 * @fn        AIP_EXTERN HPR_INT32 aip_service_start(AIP_INIT_PARAM_P pstInitParam)
 *  @brief    开启aip layer 基础服务
 *  @param    see AIP_INIT_PARAM_P define
 *  @note     调用该接口后, 将默认拉起aip层提供的内部子服务，内部子服务均提供了独立的控制接口，
 *            支持外部封装独立的启动服务接口
 *  @return   HPR_OK: success； other:fail
**/
AIP_EXTERN HPR_INT32 aip_service_start(AIP_INIT_PARAM_P pstInitParam);

/**
 *  @fn       AIP_EXTERN HPR_INT32 aip_service_stop(HPR_VOID)
 *  @brief    关闭aip layer 基础服务
 *  @return   HPR_OK: success； other:fail
**/
AIP_EXTERN HPR_INT32 aip_service_stop(HPR_VOID);

/**
 * @fn       AIP_EXTERN HPR_INT32 aip_get_version(HPR_UINT8* pbyVersion, HPR_UINT32 dwVerBufLen, HPR_UINT8* pbyTime, HPR_UINT32 dwTimeBufLen);
 * @brief    获取aip版本信息
 * @param    pbyVersion      : [out], 版本号，格式为x.y.z.svn
 * @param    dwVerBufLen     : [in] , pbyVersion 可用长度,建议长度为32字节
 * @param    pbyTime         : [out], 编译时间,格式为 %Y-%m-%d %H:%M:%S
 * @param    dwTimeBufLen    : [out], pbyTime 可用长度,建议长度为32字节
 * @return   HPR_OK:success; other: fail
 */
AIP_EXTERN HPR_INT32 aip_get_version(HPR_UINT8* pbyVersion, HPR_UINT32 dwVerBufLen, HPR_UINT8* pbyTime, HPR_UINT32 dwTimeBufLen);

#ifdef __cplusplus
}
#endif
#endif /* __AIP_H__ END */
