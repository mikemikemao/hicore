/** 
 * @note    : HangZhou Hikvision Digital Technology Co., Ltd. All Right Reserved.
 * @file    : encrypt_debug.h
 * @brief   : 安全加解密模块调试文件
 * @author  : caohaojie
 * @data    : 2018-3-19 21: 14: 09
 * @history :
 *            <version>    <time>      <author >   <desc>
 *            1.0          2018 - 9 - 22   caohaojie   create
 */ 

#ifndef __ENCRYPT_DEBUG_H__
#define __ENCRYPT_DEBUG_H__

/************************************************************************
 Included Header
 ************************************************************************/
#include "HPR_Types.h"
#include "HPR_Config.h"
#include "dev_key_manage.h"



#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

/************************************************************************
 Macros
 ************************************************************************/
#define __ENCRYPTION__DEBUG__                 /** 调试模式下 该调试定义 */

/************************************************************************
Type Definition
************************************************************************/


/************************************************************************
 Function Declaration
 ************************************************************************/

#ifdef  __ENCRYPTION__DEBUG__

/**
 * @fn       : app_encryption_get_key
 * @brief    : 获取加密模块秘钥
 * @date     : 2018-12-18
 * @author   : caohaojie
 * @requires :
 * @note     : 仅供调试模式下使用
 */
HPR_INT32 app_encryption_get_key(const HPR_INT8* recvBuf, HPR_INT32 dwRecvBufLen, HPR_INT8* sendBuf, HPR_INT32 dwSendBufLen);

/**
 * @fn       : app_file_sec_dec
 * @brief    : 文件加解密 命令格式  cmd srcfile:srcpwd:dstfile:dstpwd
 * @param    : recvBuf
 * @param    : sendBuf
 * @return   : HPR_OK: success; other: fail 
 * @author   : caohaojie
 */
HPR_INT32 app_file_sec_dec(const HPR_INT8* recvBuf, HPR_INT32 dwRecvBufLen, HPR_INT8* sendBuf, HPR_INT32 dwSendBufLen);


#endif //__ENCRYPTION__DEBUG__ 

#ifdef __cplusplus
}
#endif  /* __cplusplus */


#endif //__ENCRYPT_DEBUG_H__
