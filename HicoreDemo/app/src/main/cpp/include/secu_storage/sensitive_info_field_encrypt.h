/**
 * @note    : HangZhou Hikvision Digital Technology Co., Ltd. All Right Reserved.
 * @file    : sensitive_info_field_encrypt.h
 * @brief   : ������Ϣ�ֶμ���
 * @author  : caohaojie
 * @date    : 2019��11��11��
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
#define SENSITICE_FIELD_SRL_ENC_LEN_CAL(x)       (BASE64_ENC_LEN_CAL(AES_CBC_PKCS7PADDING_ENC_LEN_CAL(x)))   // string�ֶμ��ܳ��ȱ仯����aes-cbc-pkcs7padding���ܣ���base64����
#define SENSITICE_FIELD_BIN_ENC_LEN_CAL(x)       (AES_CBC_PKCS7PADDING_ENC_LEN_CAL(x))                       //binary�ֶμ��ܳ��ȱ仯��aes-cbc-pkcs7paddingae����


/************************************************************************
 Type Definition
 ************************************************************************/

/************************************************************************
 Function Declaration
 ************************************************************************/

/**
 * @fn       : sensitive_info_field_encode 
 * @brief    : ������Ϣ���ܽӿ�
 * @param    : pstSecParam [in/out]  : �ӽ��ܲ���
 * @return   : HPR_OK : success; HPR_ERROR: fail 
 * @author   : caohaojie
 * @note     : ����ַ�������ʹ��., �ڲ��Ⱦ���aes_128_cbc_pkcs7padding���ܣ��ٽ���base64����
 * @note     : ���ĳ��� = ((���ĳ���/16 +1) * 16 ) % 3 ? (((���ĳ���/16 +1) * 16 ) /3 +1)* 4 : (((���ĳ���/16 +1) * 16 ) /3)* 4, ����ѡ�����ֵ ((���ĳ��� +16 ) /3 +1) *4
 */
HPR_INT32 sensitive_info_field_encode(SEC_PARAM_P pstSecParam);

/**
 * @fn       : sensitive_info_field_decode
 * @brief    : ������Ϣ���ܽӿ�
 * @param    : pstSecParam [in/out]  : �ӽ��ܲ���
 * @return   : HPR_OK : success; HPR_ERROR: fail 
 * @author   : caohaojie
 * @note     : ����ַ�������ʹ��., �ڲ��Ƚ��ʹ�base64����, �ٽ���aes_128_cbc_pkcs7padding����
 * @note     : ���ĳ��� = ((���ĳ���/16 +1) * 16 ) % 3 ? (((���ĳ���/16 +1) * 16 ) /3 +1)* 4 : (((���ĳ���/16 +1) * 16 ) /3)* 4, ����ѡ�����ֵ ((���ĳ��� +16 ) /3 +1) *4
 */
HPR_INT32 sensitive_info_field_decode(SEC_PARAM_P pstSecParam);

/**
 * @fn       : sensitive_info_field_encode_binary 
 * @brief    : ������Ϣ���ܽӿ�
 * @param    : pstSecParam [in/out]  : �ӽ��ܲ���
 * @return   : HPR_OK : success; HPR_ERROR: fail 
 * @author   : caohaojie
 * @note     : ��Զ���������ʹ��., �ڲ�����aes_128_cbc_pkcs7padding����
 * @note     : ���ĳ��� = ((���ĳ���/16 +1) * 16, ����ѡ�����ֵ ((���ĳ��� +16) 
 */
HPR_INT32 sensitive_info_field_encode_binary(SEC_PARAM_P pstSecParam);

/**
 * @fn       : sensitive_info_field_decode_binary 
 * @brief    : ������Ϣ���ܽӿ�
 * @param    : pstSecParam [in/out]  : �ӽ��ܲ���
 * @return   : HPR_OK : success; HPR_ERROR: fail 
 * @author   : caohaojie
 * @note     : ��Զ���������ʹ��., �ڲ�����aes_128_cbc_pkcs7padding����
 * @note     : ���ĳ��� = ((���ĳ���/16 +1) * 16, ����ѡ�����ֵ ((���ĳ��� +16) 
 */
HPR_INT32 sensitive_info_field_decode_binary(SEC_PARAM_P pstSecParam);

/**
 * @fn       : sensitive_info_field_encode_nopadding
 * @brief    : ������Ϣ���ܽӿ�
 * @param    : pstSecParam [in/out]  : �ӽ��ܲ���
 * @return   : HPR_OK : success; HPR_ERROR: fail 
 * @author   : caohaojie
 * @note     : ������Ρ�������Ҫ����ܺ󱣳�ԭ���ȵ�����ʹ��., �ڲ�����aes_128_ctr����
 * @note     : ���ĳ��� = ���ĳ���
 */
HPR_INT32 sensitive_info_field_encode_nopadding(SEC_PARAM_P pstSecParam);

/**
 * @fn       : sensitive_info_field_decode_nopadding 
 * @brief    : ������Ϣ���ܽӿ�
 * @param    : pstSecParam [in/out]  : �ӽ��ܲ���
 * @return   : HPR_OK : success; HPR_ERROR: fail 
 * @author   : caohaojie
 * @note     : ������Ρ�������Ҫ����ܺ󱣳�ԭ���ȵ�����ʹ��., �ڲ�����aes_128_ctr����
 * @note     : ���ĳ��� = ���ĳ���
 */
HPR_INT32 sensitive_info_field_decode_nopadding(SEC_PARAM_P pstSecParam);

#ifdef __cplusplus
}
#endif
#endif /* __SENSITIVE_INFO_ENCRYPT_H__ END */
