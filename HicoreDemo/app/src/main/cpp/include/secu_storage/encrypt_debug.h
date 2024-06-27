/** 
 * @note    : HangZhou Hikvision Digital Technology Co., Ltd. All Right Reserved.
 * @file    : encrypt_debug.h
 * @brief   : ��ȫ�ӽ���ģ������ļ�
 * @author  : caohaojie
 * @data    : 2018-3-19 21: 14: 09
 * @history :
 *            <version>    <time>      <author >   <desc>
 *            1.0          2018 - 9 - 22   caohaojie   create
 */ 

#ifndef __ENCRYPT_DEBUG_H__
#define __ENCRYPT_DEBUG_H__

/************************************************************************
 Included Header
 ************************************************************************/
#include "HPR_Types.h"
#include "HPR_Config.h"
#include "dev_key_manage.h"



#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

/************************************************************************
 Macros
 ************************************************************************/
#define __ENCRYPTION__DEBUG__                 /** ����ģʽ�� �õ��Զ��� */

/************************************************************************
Type Definition
************************************************************************/


/************************************************************************
 Function Declaration
 ************************************************************************/

#ifdef  __ENCRYPTION__DEBUG__

/**
 * @fn       : app_encryption_get_key
 * @brief    : ��ȡ����ģ����Կ
 * @date     : 2018-12-18
 * @author   : caohaojie
 * @requires :
 * @note     : ��������ģʽ��ʹ��
 */
HPR_INT32 app_encryption_get_key(const HPR_INT8* recvBuf, HPR_INT32 dwRecvBufLen, HPR_INT8* sendBuf, HPR_INT32 dwSendBufLen);

/**
 * @fn       : app_file_sec_dec
 * @brief    : �ļ��ӽ��� �����ʽ  cmd srcfile:srcpwd:dstfile:dstpwd
 * @param    : recvBuf
 * @param    : sendBuf
 * @return   : HPR_OK: success; other: fail 
 * @author   : caohaojie
 */
HPR_INT32 app_file_sec_dec(const HPR_INT8* recvBuf, HPR_INT32 dwRecvBufLen, HPR_INT8* sendBuf, HPR_INT32 dwSendBufLen);


#endif //__ENCRYPTION__DEBUG__ 

#ifdef __cplusplus
}
#endif  /* __cplusplus */


#endif //__ENCRYPT_DEBUG_H__
