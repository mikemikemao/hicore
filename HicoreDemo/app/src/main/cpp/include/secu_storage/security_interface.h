
/**
 * @note    : HangZhou Hikvision Digital Technology Co., Ltd. All Right Reserved.
 * @file    : security_interface.h
 * @brief   : ��ȫģ��
 * @author  : caohaojie
 * @date    : 2019��08��15��
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

//#define NO_SEC_SQL  (1)    // ��ʹ�ü������ݿ�
#define DEVCFG_SEC  (1)    // ���������ļ�����
// #define VIS_DB_SEC  (1)    // �����Խ����ݿ����
// #define ACS_DB_SEC  (1)    // �����Ž����ݿ����
// #define EVENT_DB_SEC  (1)    // �����¼����ݿ����
// #define AES_128_GCM_FACE (1)  //�������� gcm ���ܿ���
#define AES_128_CBC_PART_FACE (1)  //�������� cbc �ְ� ���ܿ���
// #define AES_128_CBC_FACE (1)  // �������� cbc ���ܿ���,�ú궨����AES_128_GCM_FACE ������ͬʱ����

/************************************************************************
 Type Definition
 ************************************************************************/

/************************************************************************
 Function Declaration
 ************************************************************************/

/**
 * @fn       : security_resource_init 
 * @brief    : ��ȫ�����Դ��ʼ��
 * @return   : HPR_OK: success; other: fail
 * @author   : caohaojie
 */
HPR_INT32 security_resource_init(void);

/**
 * @fn       : security_resource_uninit 
 * @brief    : ��ȫ�����Դ����ʼ��
 * @return   : HPR_OK: success; other: fail
 * @author   : caohaojie
 */
HPR_INT32 security_resource_uninit(void);

/**
 * @fn       : openssl_init 
 * @brief    : ��ʼ��openssl ���߳�ʹ�õ���Դ
 * @return   : HPR_OK: success; HPR_ERROR: fail
 * @note     : �漰���̵߳���opensslʱ,�����ڵ���openssl��Դǰ�ȵ��øú���������Դ��ʼ�� 
 * @author   : caohaojie
 */
HPR_INT32 openssl_init(HPR_VOID);

/**
 * @fn       : openssl_fini 
 * @brief    : ����ʼ��openssl ���߳�ʹ�õ���Դ
 * @return   : HPR_OK: success; HPR_ERROR: fail
 * @note     : �����ڲ�����Ҫ����openssl��,�ͷ���Դ
 * @author   : caohaojie
 */
HPR_INT32 openssl_fini(HPR_VOID);


/**
 * @fn       : security_resource_clean 
 * @brief    : ��ȫģ����Կ�ļ����
 * @return   : HPR_OK: success; other: fail
 * @author   : caohaojie
 */
HPR_INT32 security_resource_clean(void);
#ifdef __cplusplus
}
#endif
#endif /* __SECURITY_INTERFACE_H__ END */

