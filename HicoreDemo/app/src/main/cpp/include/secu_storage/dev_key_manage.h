/**
 * @note    : HangZhou Hikvision Digital Technology Co., Ltd. All Right Reserved.
 * @file    : dev_key_manage.h
 * @brief   : �豸��Կ����
 * @author  : caohaojie
 * @date    : 2019��11��11��
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

#define DB_KEY_LEN    (64) //�������ݿ���Կ
/************************************************************************
 Type Definition
 ************************************************************************/

// @brief: ��Ҫ������Կ��ģ��ö��ֵ
typedef enum
{
    E_SECURE_ENCRYPT_MODULE_INVALID      = 0,
    E_SECURE_ENCRYPT_MODULE_ROOT         = 2, // ����Կ
    E_SECURE_ENCRYPT_MODULE_DEVCFG       = 3, // �����ļ�
    E_SECURE_ENCRYPT_MODULE_FACE_PICS    = 4, // ����ͼƬ
    E_SECURE_ENCRYPT_MODULE_DB_VIS       = 5, // �Խ����ݿ�
    E_SECURE_ENCRYPT_MODULE_DB_ACS       = 6, // �Ž����ݿ�
    E_SECURE_ENCRYPT_MODULE_DB_EVENT     = 7, // �¼����ݿ�
    E_SECURE_ENCRYPT_MODULE_PEOPLE       = 8, // ���ݿ���Ա������Ϣ
    E_SECURE_ENCRYPT_MODULE_MEETTING     = 9, // �������ݿ�������Ϣ ��Կ
    E_SECURE_ENCRYPT_MODULE_MAX          = 10,
} SECURE_ENCRYPT_MODULE_E;


// @brief: gcm 128 ���� ��Կ�ͳ�ʼ������
typedef struct
{
    HPR_INT8 caPwd[AES_128_KEY_LEN + 1];  // ��Կ
    HPR_INT8 caIv[AES_IV_LEN + 1];   // ��ʼ������
} FILE_ENCRYPT_KEY_ST; //40bytes





/************************************************************************
 Function Declaration
 ************************************************************************/

/**
 * @fn       : init_security_encrypt_key
 * @brief    : ��ȡ���ݼ��ܵ���Կ, ���û�еĻ�����
 * @return   : HPR_OK: success; other: fail
 * @author   : caohaojie
 * @note     : ������ģ���ʼ��ǰ��Ҫ�ȵ�������ӿ�
 */
HPR_INT32 init_security_encrypt_key(HPR_VOID);

/**
 * @fn       : get_secure_encrypt_key
 * @brief    : ��ȡ���ݼ��ܵ���Կ
 * @return   : HPR_OK: success; other: fail
 * @author   : caohaojie
 */
HPR_INT32 get_secure_encrypt_key(HPR_VOID);

/**
 * @fn       : gen_secure_encrypt_key
 * @brief    : ���ɼ�����Կ
 * @return   : HPR_OK: success; other: fail
 * @author   : caohaojie
 */
HPR_INT32 gen_secure_encrypt_key(HPR_VOID);

/**
 * @fn       : security_encrypt_key_clean
 * @brief    : ��Կ�ļ����
 * @return   : HPR_OK: success; other: fail
 * @author   : caohaojie
 */
HPR_INT32 security_encrypt_key_clean(HPR_VOID);

/**
 * @fn       : get_module_key
 * @brief    : ��ȡģ����Կ
 * @param    : eModuleIndex [in] : ģ��������
 * @param    : pDst [out]        : Ŀ�ĵ�ַ
 * @param    : sdwSize [in]      : Ŀ�ĵ�ַ���ÿռ�
 * @return   : HPR_OK: success ; other: fail
 * @author   : caohaojie
 */
HPR_INT32 get_module_key(SECURE_ENCRYPT_MODULE_E eModuleIndex, HPR_VOID* pDst, HPR_INT32 sdwSize);

#ifdef __cplusplus
}
#endif
#endif /* __DEV_KEY_MANAGE_H__ END */
