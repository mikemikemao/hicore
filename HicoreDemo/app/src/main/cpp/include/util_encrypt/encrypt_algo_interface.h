/**
 * @note    : HangZhou Hikvision Digital Technology Co., Ltd. All Right Reserved.
 * @file    : encrypt_algo_interface.h
 * @brief   : �����ӽ����㷨�ӿ�
 * @author  : caohaojie
 * @date    : 2019��11��11��
 * @history :
 *            <version>    <time>           <author >   <desc>
 *            1.0          2019 - 11- 11    caohaojie   create
 * @note    : �ڲ��㷨ʵ������openssl��
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

#define AES_BLOCK_LEN   (16) //128bit               //AES �ֿ鳤��
#define AES_128_BIT     (128) //128bit
#define AES_256_BIT     (256) //256bit
#define AES_128_KEY_LEN (16) //128bit               //AES_128 �����㷨 ��Կ�ֽڳ��� 
#define AES_256_KEY_LEN (32) //256bit               //AES_128 �����㷨 ��Կ�ֽڳ��� 
#define AES_IV_LEN      (16) //128bit               //AES_ �����㷨 ��ʼ�������ֽڳ���

#define BASE64_ENC_LEN_CAL(x)                   (((x-1) /3 + 1) * 4)                        // base64���ı����ĵĳ��ȱ仯�� ��3������ȡ�����ٳ�4
#define AES_CBC_ZEROPADDING_ENC_LEN_CAL(x)      ((((x-1) /16) + 1)* 16)                     // aes-cbc-zeropadding ���ı����ĵĳ��ȱ仯����16������ȡ�����ٳ�16
#define AES_ECB_ZEROPADDING_ENC_LEN_CAL(x)      ((((x-1) /16) + 1)* 16)                     // aes-ecb-zeropadding ���ı����ĵĳ��ȱ仯����16������ȡ�����ٳ�16
#define AES_CBC_PKCS7PADDING_ENC_LEN_CAL(x)     (((x /16) + 1)* 16)                         // aes-cbc-pkcs7padding ���ı����ĵĳ��ȱ仯��16����+16, ��16����16����

/************************************************************************
 Type Definition
 ************************************************************************/


/* aes-ecb, cbc, ctr�ӽ��ܺ������ݲ��� */
typedef struct
{
    HPR_UINT8 *pbySrc;       // [in]  : Դ��ַ
    HPR_INT32 sdwSrcLen;     // [in]  : ԭ�ĳ��� 
    HPR_UINT8 *pbyDst;       // [out] : Ŀ�ĵ�ַ
    HPR_INT32 sdwDstLen;     // [out] : �������
    HPR_INT32 sdwBufLen;     // [in]  : Ŀ�ĵ�ַ���õ�buf����, ����У��Ŀ�ĵ�ַ�����Ƿ�����������ݡ�����ֵΪ-1ʱ������Ҫ��buf���Ƚ���У�飬�Խ��һЩ�ⲿ�ӿ�û�д���buf���ȵ����
    HPR_UINT8  *pbyKey;       // [in]  : ��Կ(16byte)
    HPR_UINT8  *pbyIv;        // [in]  : iv����(16byte)
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
