/**
 * @note    : HangZhou Hikvision Digital Technology Co., Ltd. All Right Reserved.
 * @file    : sqlcipher_config.h
 * @brief   : sqlcipher加密数据库相关
 * @author  : caohaojie
 * @date    : 2019年11月11日
 * @note    : Create
 */
#ifndef __SQLCIPHER_CONFIG_H__
#define __SQLCIPHER_CONFIG_H__

/************************************************************************
 Included Header
 ************************************************************************/
#include "HPR_Types.h"
#include "HPR_Config.h"
#ifndef SQLITE_HAS_CODEC
    #define SQLITE_HAS_CODEC
    #include "sqlite3.h"
    #undef SQLITE_HAS_CODEC
#else
    #include "sqlite3.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/************************************************************************
 Macros
 ************************************************************************/

/** @brief: 加密数据库 配置*/

#define CIPHER                  ("'aes-256-cbc'")                 // 加密算法
// #define CIPHER                  ("'aes-128-cbc'")                 // 加密算法
#define CIPHER_PAGE_SIZE        (4096)                          // 加密页字节大小
#define KDF_ITER                (64000)                         // 密码短语生成密钥种子的迭代次数，兼容老版本
#define KDF_ITER_5000           (5000)                   		// 64000次太慢，和明眸保持一致改用5000次，符合安全需求,内部切换成5000次迭代
#define CIPHER_HMAC_ALGORITHM   ("HMAC_SHA1")                   // 加密页验证算法
#define CIPHER_KDF_ALGORITHM    ("PBKDF2_HMAC_SHA1")            // 密码短语生成密钥种子的迭代算法
#define CIPHER_KEY_LEN          (64)                            // 



/************************************************************************
 Type Definition
 ************************************************************************/
/*
    数据库文件转换参数
*/
typedef struct
{
    HPR_UINT8 *pbyInKey;   // [in] : 加密文件原有的密钥,  需字符形式， 如果为NULL,代表为不加密文件
    HPR_UINT8 *pbyOutKey;  // [in] : 加密文件加密的新密钥,  需字符形式, 如果为NULL,代表为不加密文件
    HPR_UINT8 *pbyInPath;  // [in] :  源加密数据文件名
    HPR_UINT8 *pbyOutPath; // [in] :  目的加密数据文件名
    HPR_FLOAT *pfRate;       // [out] : 导入导出进度
    HPR_FLOAT fRateBegin;  // [in] : 导入导出起始进度
    HPR_FLOAT fRateEnd;    // [in] : 导入导出最大进度
} SEC_DEC_DB_PARAM_ST, *SEC_DEC_DB_PARAM_P;


/************************************************************************
 Function Declaration
 ************************************************************************/

/**
 * @fn       : sec_dec_db 
 * @brief    : sqlciher 加密数据库 转换 (将原有的加密数据数据库解密后用新密码加密储存)
 * @param    : pstParam  : 见结构体SEC_DEC_DB_PARAM_ST 定义
 * @note     : pstParam->pbyInPath 和 pstParam->pbyOutPath 不可以一致
 * @note     : pbyInDbName 和 pbyOutDbName 不可以一致
 * @return   : HPR_OK: success; other : fail 
 * @author   : caohaojie
 */
HPR_INT32 sec_dec_db(SEC_DEC_DB_PARAM_P pstParam);

/**
 * @fn       : config_cipher_database 
 * @brief    : 配置加密数据库 加密配置
 * @param    : pDb   [in]   : 数据库节点
 * @param    : szKey [in]   ：密码，需字符形式， 如果为NULL,代表为不加密文件
 * @return   : HPR_OK: success; other: fail
 * @author   : caohaojie
 */
HPR_INT32 config_cipher_database(sqlite3 *pDb, HPR_UINT8 *szKey, HPR_INT32 sdwKeyLen);

#ifdef __cplusplus
}
#endif
#endif /* __SQLCIPHER_CONFIG_H__ END */
