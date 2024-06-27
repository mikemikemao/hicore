/**
 * @note    : HangZhou Hikvision Digital Technology Co., Ltd. All Right Reserved.
 * @file    : sensitive_info_field_encrypt.h
 * @brief   : 敏感信息字段加密
 * @author  : caohaojie
 * @date    : 2019年11月11日
 * @note    : Create
 */
#ifndef __SENSITIVE_INFO_ENCRYPT_H__
#define __SENSITIVE_INFO_ENCRYPT_H__


/************************************************************************
 Included Header
 ************************************************************************/
#include "HPR_Types.h"
#include "HPR_Config.h"
#include "encrypt_algo_interface.h"

#ifdef __cplusplus
extern "C" {
#endif

/************************************************************************
 Macros
 ************************************************************************/
#define SENSITICE_FIELD_SRL_ENC_LEN_CAL(x)       (BASE64_ENC_LEN_CAL(AES_CBC_PKCS7PADDING_ENC_LEN_CAL(x)))   // string字段加密长度变化。先aes-cbc-pkcs7padding加密，再base64编码
#define SENSITICE_FIELD_BIN_ENC_LEN_CAL(x)       (AES_CBC_PKCS7PADDING_ENC_LEN_CAL(x))                       //binary字段加密长度变化。aes-cbc-pkcs7paddingae加密


/************************************************************************
 Type Definition
 ************************************************************************/

/************************************************************************
 Function Declaration
 ************************************************************************/

/**
 * @fn       : sensitive_info_field_encode 
 * @brief    : 敏感信息加密接口
 * @param    : pstSecParam [in/out]  : 加解密参数
 * @return   : HPR_OK : success; HPR_ERROR: fail 
 * @author   : caohaojie
 * @note     : 针对字符串类型使用., 内部先经过aes_128_cbc_pkcs7padding加密，再进行base64编码
 * @note     : 密文长度 = ((明文长度/16 +1) * 16 ) % 3 ? (((明文长度/16 +1) * 16 ) /3 +1)* 4 : (((明文长度/16 +1) * 16 ) /3)* 4, 可以选择最大值 ((明文长度 +16 ) /3 +1) *4
 */
HPR_INT32 sensitive_info_field_encode(SEC_PARAM_P pstSecParam);

/**
 * @fn       : sensitive_info_field_decode
 * @brief    : 敏感信息解密接口
 * @param    : pstSecParam [in/out]  : 加解密参数
 * @return   : HPR_OK : success; HPR_ERROR: fail 
 * @author   : caohaojie
 * @note     : 针对字符串类型使用., 内部先进故宫base64解码, 再进行aes_128_cbc_pkcs7padding解密
 * @note     : 密文长度 = ((明文长度/16 +1) * 16 ) % 3 ? (((明文长度/16 +1) * 16 ) /3 +1)* 4 : (((明文长度/16 +1) * 16 ) /3)* 4, 可以选择最大值 ((明文长度 +16 ) /3 +1) *4
 */
HPR_INT32 sensitive_info_field_decode(SEC_PARAM_P pstSecParam);

/**
 * @fn       : sensitive_info_field_encode_binary 
 * @brief    : 敏感信息加密接口
 * @param    : pstSecParam [in/out]  : 加解密参数
 * @return   : HPR_OK : success; HPR_ERROR: fail 
 * @author   : caohaojie
 * @note     : 针对二进制类型使用., 内部进行aes_128_cbc_pkcs7padding加密
 * @note     : 密文长度 = ((明文长度/16 +1) * 16, 可以选择最大值 ((明文长度 +16) 
 */
HPR_INT32 sensitive_info_field_encode_binary(SEC_PARAM_P pstSecParam);

/**
 * @fn       : sensitive_info_field_decode_binary 
 * @brief    : 敏感信息解密接口
 * @param    : pstSecParam [in/out]  : 加解密参数
 * @return   : HPR_OK : success; HPR_ERROR: fail 
 * @author   : caohaojie
 * @note     : 针对二进制类型使用., 内部进行aes_128_cbc_pkcs7padding解密
 * @note     : 密文长度 = ((明文长度/16 +1) * 16, 可以选择最大值 ((明文长度 +16) 
 */
HPR_INT32 sensitive_info_field_decode_binary(SEC_PARAM_P pstSecParam);

/**
 * @fn       : sensitive_info_field_encode_nopadding
 * @brief    : 敏感信息加密接口
 * @param    : pstSecParam [in/out]  : 加解密参数
 * @return   : HPR_OK : success; HPR_ERROR: fail 
 * @author   : caohaojie
 * @note     : 针对整形、浮点数要求加密后保持原长度的类型使用., 内部进行aes_128_ctr加密
 * @note     : 密文长度 = 明文长度
 */
HPR_INT32 sensitive_info_field_encode_nopadding(SEC_PARAM_P pstSecParam);

/**
 * @fn       : sensitive_info_field_decode_nopadding 
 * @brief    : 敏感信息解密接口
 * @param    : pstSecParam [in/out]  : 加解密参数
 * @return   : HPR_OK : success; HPR_ERROR: fail 
 * @author   : caohaojie
 * @note     : 针对整形、浮点数要求加密后保持原长度的类型使用., 内部进行aes_128_ctr加密
 * @note     : 密文长度 = 明文长度
 */
HPR_INT32 sensitive_info_field_decode_nopadding(SEC_PARAM_P pstSecParam);

#ifdef __cplusplus
}
#endif
#endif /* __SENSITIVE_INFO_ENCRYPT_H__ END */
