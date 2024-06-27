/**
 * @note    : HangZhou Hikvision Digital Technology Co., Ltd. All Right Reserved.
 * @file    : encrypt_algo_interface.h
 * @brief   : 基础加解密算法接口
 * @author  : caohaojie
 * @date    : 2019年11月11日
 * @history :
 *            <version>    <time>           <author >   <desc>
 *            1.0          2019 - 11- 11    caohaojie   create
 * @note    : 内部算法实现依赖openssl库
 */
#ifndef __ENCRYPT_ALGO_INTERFACE_H__
#define __ENCRYPT_ALGO_INTERFACE_H__

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

#define AES_BLOCK_LEN   (16) //128bit               //AES 分块长度
#define AES_128_BIT     (128) //128bit
#define AES_256_BIT     (256) //256bit
#define AES_128_KEY_LEN (16) //128bit               //AES_128 加密算法 秘钥字节长度 
#define AES_256_KEY_LEN (32) //256bit               //AES_128 加密算法 秘钥字节长度 
#define AES_IV_LEN      (16) //128bit               //AES_ 加密算法 初始化向量字节长度

#define BASE64_ENC_LEN_CAL(x)                   (((x-1) /3 + 1) * 4)                        // base64明文变密文的长度变化。 除3（向上取整）再乘4
#define AES_CBC_ZEROPADDING_ENC_LEN_CAL(x)      ((((x-1) /16) + 1)* 16)                     // aes-cbc-zeropadding 明文变密文的长度变化。除16（向上取整）再乘16
#define AES_ECB_ZEROPADDING_ENC_LEN_CAL(x)      ((((x-1) /16) + 1)* 16)                     // aes-ecb-zeropadding 明文变密文的长度变化。除16（向上取整）再乘16
#define AES_CBC_PKCS7PADDING_ENC_LEN_CAL(x)     (((x /16) + 1)* 16)                         // aes-cbc-pkcs7padding 明文变密文的长度变化。16倍数+16, 非16倍数16对齐

/************************************************************************
 Type Definition
 ************************************************************************/


/* aes-ecb, cbc, ctr加解密函数传递参数 */
typedef struct
{
    HPR_UINT8 *pbySrc;       // [in]  : 源地址
    HPR_INT32 sdwSrcLen;     // [in]  : 原文长度 
    HPR_UINT8 *pbyDst;       // [out] : 目的地址
    HPR_INT32 sdwDstLen;     // [out] : 输出长度
    HPR_INT32 sdwBufLen;     // [in]  : 目的地址可用的buf长度, 用于校验目的地址长度是否满足输出内容。当该值为-1时代表不需要对buf长度进行校验，以解决一些外部接口没有传入buf长度的情况
    HPR_UINT8  *pbyKey;       // [in]  : 密钥(16byte)
    HPR_UINT8  *pbyIv;        // [in]  : iv向量(16byte)
} SEC_PARAM_ST, *SEC_PARAM_P;

typedef HPR_INT32 (*fnAesCallbackType)(SEC_PARAM_P stSecParam);

/************************************************************************
 Function Declaration
 ************************************************************************/

HPR_INT32 util_aes_128_ecb_encrypt_nopadding(SEC_PARAM_P pstSecParam);
HPR_INT32 util_aes_128_ecb_decrypt_nopadding(SEC_PARAM_P pstSecParam);
HPR_INT32 util_aes_128_cbc_encrypt_zeropadding(SEC_PARAM_P pstSecParam);
HPR_INT32 util_aes_128_cbc_decrypt_zeropadding(SEC_PARAM_P pstSecParam);
HPR_INT32 util_aes_256_cbc_encrypt_zeropadding(SEC_PARAM_P pstSecParam);
HPR_INT32 util_aes_256_cbc_decrypt_zeropadding(SEC_PARAM_P pstSecParam);
HPR_INT32 util_aes_128_cbc_encrypt_pkcs7padding(SEC_PARAM_P pstSecParam);
HPR_INT32 util_aes_128_cbc_decrypt_pkcs7padding(SEC_PARAM_P pstSecParam);
HPR_INT32 util_aes_256_cbc_encrypt_pkcs7padding(SEC_PARAM_P pstSecParam);
HPR_INT32 util_aes_256_cbc_decrypt_pkcs7padding(SEC_PARAM_P pstSecParam);
HPR_INT32 util_aes_128_ctr_encrypt(SEC_PARAM_P pstSecParam);
HPR_INT32 util_aes_128_ctr_decrypt(SEC_PARAM_P pstSecParam);

#ifdef __cplusplus
}
#endif
#endif /* __ENCRYPT_ALGO_INTERFACE_H__ END */
