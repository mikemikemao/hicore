/**
 * @note    : HangZhou Hikvision Digital Technology Co., Ltd. All Right Reserved.
 * @file    : dev_key_manage.h
 * @brief   : 设备密钥管理
 * @author  : caohaojie
 * @date    : 2019年11月11日
 * @note    : Create
 */
#ifndef __DEV_KEY_MANAGE_H__
#define __DEV_KEY_MANAGE_H__

/************************************************************************
 Included Header
 ************************************************************************/
#include "encrypt_algo_interface.h"
#include "HPR_Types.h"
#include "HPR_Config.h"


#ifdef __cplusplus
extern "C" {
#endif

/************************************************************************
 Macros
 ************************************************************************/

#define DB_KEY_LEN    (64) //加密数据库密钥
/************************************************************************
 Type Definition
 ************************************************************************/

// @brief: 需要加密秘钥的模块枚举值
typedef enum
{
    E_SECURE_ENCRYPT_MODULE_INVALID      = 0,
    E_SECURE_ENCRYPT_MODULE_ROOT         = 2, // 根秘钥
    E_SECURE_ENCRYPT_MODULE_DEVCFG       = 3, // 配置文件
    E_SECURE_ENCRYPT_MODULE_FACE_PICS    = 4, // 人脸图片
    E_SECURE_ENCRYPT_MODULE_DB_VIS       = 5, // 对讲数据库
    E_SECURE_ENCRYPT_MODULE_DB_ACS       = 6, // 门禁数据库
    E_SECURE_ENCRYPT_MODULE_DB_EVENT     = 7, // 事件数据库
    E_SECURE_ENCRYPT_MODULE_PEOPLE       = 8, // 数据库人员敏感信息
    E_SECURE_ENCRYPT_MODULE_MEETTING     = 9, // 会议数据库敏感信息 秘钥
    E_SECURE_ENCRYPT_MODULE_MAX          = 10,
} SECURE_ENCRYPT_MODULE_E;


// @brief: gcm 128 加密 秘钥和初始化向量
typedef struct
{
    HPR_INT8 caPwd[AES_128_KEY_LEN + 1];  // 秘钥
    HPR_INT8 caIv[AES_IV_LEN + 1];   // 初始化向量
} FILE_ENCRYPT_KEY_ST; //40bytes





/************************************************************************
 Function Declaration
 ************************************************************************/

/**
 * @fn       : init_security_encrypt_key
 * @brief    : 获取数据加密的秘钥, 如果没有的话生成
 * @return   : HPR_OK: success; other: fail
 * @author   : caohaojie
 * @note     : 在所有模块初始化前需要先调用这个接口
 */
HPR_INT32 init_security_encrypt_key(HPR_VOID);

/**
 * @fn       : get_secure_encrypt_key
 * @brief    : 获取数据加密的秘钥
 * @return   : HPR_OK: success; other: fail
 * @author   : caohaojie
 */
HPR_INT32 get_secure_encrypt_key(HPR_VOID);

/**
 * @fn       : gen_secure_encrypt_key
 * @brief    : 生成加密秘钥
 * @return   : HPR_OK: success; other: fail
 * @author   : caohaojie
 */
HPR_INT32 gen_secure_encrypt_key(HPR_VOID);

/**
 * @fn       : security_encrypt_key_clean
 * @brief    : 秘钥文件清除
 * @return   : HPR_OK: success; other: fail
 * @author   : caohaojie
 */
HPR_INT32 security_encrypt_key_clean(HPR_VOID);

/**
 * @fn       : get_module_key
 * @brief    : 获取模块秘钥
 * @param    : eModuleIndex [in] : 模块索引号
 * @param    : pDst [out]        : 目的地址
 * @param    : sdwSize [in]      : 目的地址可用空间
 * @return   : HPR_OK: success ; other: fail
 * @author   : caohaojie
 */
HPR_INT32 get_module_key(SECURE_ENCRYPT_MODULE_E eModuleIndex, HPR_VOID* pDst, HPR_INT32 sdwSize);

#ifdef __cplusplus
}
#endif
#endif /* __DEV_KEY_MANAGE_H__ END */
