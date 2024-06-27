/**
 * @copyleft HangZhou Hikvision Digital Technology Co., Ltd. All Right Reserved.
 * @file     aip_shell_server.h
 * @brief    shell命令对外头文件
 */

#ifndef __AIP_SHELL_SERVER_H__
#define __AIP_SHELL_SERVER_H__

/************************************************************************
 Included Header
 ************************************************************************/
#include "common/aip_common.h"
#include "utils/aip_utils_file_process.h"


#ifdef __cplusplus
extern "C" {
#endif

/************************************************************************
 Macros
 ************************************************************************/

#define SHELL_CMD_LEN      64          /* 命令最大长度(包含截断符) */
#define SHELL_CMD_HELP_LEN 128    /* 命令帮助信息最大长度(包含截断符) */

/************************************************************************
 Type Definition
 ************************************************************************/

/** @brief  串口调试服务 初始化参数*/
typedef struct
{
    HPR_INT8 byaCmdPathPrefix[COMMON_PATH_LEN];  //[in], 串口命令生成到的路径前缀。若传递要求路径合法且存在,且以'\0'截止；若未传递有效字符串,将使用默认路径
                                                 //      (gnu/linux系统"/usr/bin", android 系统为"/home/app/bin")
    HPR_INT8 byaClientToolPath[COMMON_PATH_LEN]; //[in], 客户端工具所在路径。若传递要求路径合法且存在,且以'\0'截止;若未传递有效字符串,将使用默认路径("/home/app/aip/bin/shell/acsTools")
} SHELL_SERVICE_PARAM_T, *SHELL_SERVICE_PARAM_P;

/**
 * @brief   shell命令注册回调函数声明 类型
 * @return  success: HPR_OK; other: fail
 **/
typedef HPR_INT32 (*SHELL_REG_CALLBACK)(const HPR_INT8* byRecvBuf, HPR_INT32 sdwRecvBufLen, HPR_INT8* bySendBuf, HPR_INT32 sdwSendBufLen);

/************************************************************************
  Function Declaration
 ************************************************************************/

/**
 * @fn      AIP_EXTERN HPR_INT32 aip_shell_service_start(SHELL_SERVICE_PARAM_P pstInitParam)
 * @param   see SHELL_SERVICE_PARAM_P define
 * @brief   开启shell命令服务
 * @return  HPR_OK: success； other:fail
**/
AIP_EXTERN HPR_INT32 aip_shell_service_start(SHELL_SERVICE_PARAM_P pstInitParam);

/**
 * @fn      AIP_EXTERN HPR_INT32 aip_shell_service_stop(HPR_VOID)
 * @brief   关闭shell命令模块
 * @return  HPR_OK: success； other:fail
**/
AIP_EXTERN HPR_INT32 aip_shell_service_stop(HPR_VOID);

/*
 * @fn          AIP_EXTERN HPR_INT32 aip_shell_reg_cmd(HPR_INT8* szShellCmdName, SHELL_REG_CALLBACK pFnCallBack, HPR_INT8* szShellCmdHelp)
 * @brief       注册shell命令 (每次注册一个shell命令，就动态分配一块内存连接在shell管理列表中,同名不能注册)
 * @param[in]   szShellCmdName: shell命令名,  模块命名方式 代码层_模块名_指令                 比如 aip_sip_test, 
 *              长度约束见SHELL_CMD_LEN
 * @param[in]   callbackFunc: shell命令回调函数
 * @param[in]   szShellCmdHelp: 命令usage，提供了帮助信息的命令，帮助信息将会在helpe命令中体现
 *              长度约束见SHELL_CMD_HELP_LEN
 * @return      HPR_OK: success； other:fail
**/
AIP_EXTERN HPR_INT32 aip_shell_reg_cmd(HPR_INT8* szShellCmdName, SHELL_REG_CALLBACK pFnCallBack, HPR_INT8* szShellCmdHelp);

/**
 * @fn      AIP_EXTERN HPR_INT32 aip_shell_cmd_parse(HPR_INT32 sdwArgc, HPR_INT8* ppbyArgv[])
 * @brief   shell命令处理
 * @param[in]  参数个数
 * @param[in]  参数
 * @note    仅rtos 支持
 * @return  HPR_OK: success； other:fail
**/
AIP_EXTERN HPR_INT32 aip_shell_cmd_parse(HPR_INT32 sdwArgc, HPR_INT8* ppbyArgv[]);

#ifdef __cplusplus
}
#endif
#endif /* __AIP_SHELL_SERVER_H__ END */

