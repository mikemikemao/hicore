/**
 * @note    : HangZhou Hikvision Digital Technology Co., Ltd. All Right Reserved.
 * @file    : sqlcipher_config.h
 * @brief   : sqlcipher�������ݿ����
 * @author  : caohaojie
 * @date    : 2019��11��11��
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

/** @brief: �������ݿ� ����*/

#define CIPHER                  ("'aes-256-cbc'")                 // �����㷨
// #define CIPHER                  ("'aes-128-cbc'")                 // �����㷨
#define CIPHER_PAGE_SIZE        (4096)                          // ����ҳ�ֽڴ�С
#define KDF_ITER                (64000)                         // �������������Կ���ӵĵ��������������ϰ汾
#define KDF_ITER_5000           (5000)                   		// 64000��̫��������������һ�¸���5000�Σ����ϰ�ȫ����,�ڲ��л���5000�ε���
#define CIPHER_HMAC_ALGORITHM   ("HMAC_SHA1")                   // ����ҳ��֤�㷨
#define CIPHER_KDF_ALGORITHM    ("PBKDF2_HMAC_SHA1")            // �������������Կ���ӵĵ����㷨
#define CIPHER_KEY_LEN          (64)                            // 



/************************************************************************
 Type Definition
 ************************************************************************/
/*
    ���ݿ��ļ�ת������
*/
typedef struct
{
    HPR_UINT8 *pbyInKey;   // [in] : �����ļ�ԭ�е���Կ,  ���ַ���ʽ�� ���ΪNULL,����Ϊ�������ļ�
    HPR_UINT8 *pbyOutKey;  // [in] : �����ļ����ܵ�����Կ,  ���ַ���ʽ, ���ΪNULL,����Ϊ�������ļ�
    HPR_UINT8 *pbyInPath;  // [in] :  Դ���������ļ���
    HPR_UINT8 *pbyOutPath; // [in] :  Ŀ�ļ��������ļ���
    HPR_FLOAT *pfRate;       // [out] : ���뵼������
    HPR_FLOAT fRateBegin;  // [in] : ���뵼����ʼ����
    HPR_FLOAT fRateEnd;    // [in] : ���뵼��������
} SEC_DEC_DB_PARAM_ST, *SEC_DEC_DB_PARAM_P;


/************************************************************************
 Function Declaration
 ************************************************************************/

/**
 * @fn       : sec_dec_db 
 * @brief    : sqlciher �������ݿ� ת�� (��ԭ�еļ����������ݿ���ܺ�����������ܴ���)
 * @param    : pstParam  : ���ṹ��SEC_DEC_DB_PARAM_ST ����
 * @note     : pstParam->pbyInPath �� pstParam->pbyOutPath ������һ��
 * @note     : pbyInDbName �� pbyOutDbName ������һ��
 * @return   : HPR_OK: success; other : fail 
 * @author   : caohaojie
 */
HPR_INT32 sec_dec_db(SEC_DEC_DB_PARAM_P pstParam);

/**
 * @fn       : config_cipher_database 
 * @brief    : ���ü������ݿ� ��������
 * @param    : pDb   [in]   : ���ݿ�ڵ�
 * @param    : szKey [in]   �����룬���ַ���ʽ�� ���ΪNULL,����Ϊ�������ļ�
 * @return   : HPR_OK: success; other: fail
 * @author   : caohaojie
 */
HPR_INT32 config_cipher_database(sqlite3 *pDb, HPR_UINT8 *szKey, HPR_INT32 sdwKeyLen);

#ifdef __cplusplus
}
#endif
#endif /* __SQLCIPHER_CONFIG_H__ END */
