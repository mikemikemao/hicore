
/**
 * @note    : HangZhou Hikvision Digital Technology Co., Ltd. All Right Reserved.
 * @file    : security_interface.h
 * @brief   : 安全模块
 * @author  : caohaojie
 * @date    : 2019年08月15日
 * @note    : Create
 */
#ifndef __SECURITY_INTERFACE_H__
#define __SECURITY_INTERFACE_H__

/************************************************************************
 Included Header
 ************************************************************************/
#include "HPR_Types.h"
#include "HPR_Config.h"

#ifdef __cplusplus
extern "C" {
#endif

/************************************************************************
 Macros
 ************************************************************************/

//#define NO_SEC_SQL  (1)    // 不使用加密数据库
#define DEVCFG_SEC  (1)    // 开启配置文件加密
// #define VIS_DB_SEC  (1)    // 开启对讲数据库加密
// #define ACS_DB_SEC  (1)    // 开启门禁数据库加密
// #define EVENT_DB_SEC  (1)    // 开启事件数据库加密
// #define AES_128_GCM_FACE (1)  //人脸数据 gcm 加密开启
#define AES_128_CBC_PART_FACE (1)  //人脸数据 cbc 分包 加密开启
// #define AES_128_CBC_FACE (1)  // 人脸数据 cbc 加密开启,该宏定义与AES_128_GCM_FACE 不允许同时开启

/************************************************************************
 Type Definition
 ************************************************************************/

/************************************************************************
 Function Declaration
 ************************************************************************/

/**
 * @fn       : security_resource_init 
 * @brief    : 安全相关资源初始化
 * @return   : HPR_OK: success; other: fail
 * @author   : caohaojie
 */
HPR_INT32 security_resource_init(void);

/**
 * @fn       : security_resource_uninit 
 * @brief    : 安全相关资源反初始化
 * @return   : HPR_OK: success; other: fail
 * @author   : caohaojie
 */
HPR_INT32 security_resource_uninit(void);

/**
 * @fn       : openssl_init 
 * @brief    : 初始化openssl 多线程使用的资源
 * @return   : HPR_OK: success; HPR_ERROR: fail
 * @note     : 涉及多线程调用openssl时,必须在调用openssl资源前先调用该函数进行资源初始化 
 * @author   : caohaojie
 */
HPR_INT32 openssl_init(HPR_VOID);

/**
 * @fn       : openssl_fini 
 * @brief    : 反初始化openssl 多线程使用的资源
 * @return   : HPR_OK: success; HPR_ERROR: fail
 * @note     : 可以在不再需要调用openssl后,释放资源
 * @author   : caohaojie
 */
HPR_INT32 openssl_fini(HPR_VOID);


/**
 * @fn       : security_resource_clean 
 * @brief    : 安全模块秘钥文件清除
 * @return   : HPR_OK: success; other: fail
 * @author   : caohaojie
 */
HPR_INT32 security_resource_clean(void);
#ifdef __cplusplus
}
#endif
#endif /* __SECURITY_INTERFACE_H__ END */

