/**	@file opdevsdk_hardware_basic_device_info.h
 *	@note 2012-2019 HangZhou Hikvision Digital Technology Co., Ltd. All Right Reserved.
 *	@brief �豸������Ϣͷ�ļ�
 *
 *	@author		baozhonghui
 *	@date		2020/09/11
 *
 *	@note ��ʷ��¼��
 *	@note 2020/09/11 V1.0.0 baozhonghui �½��ļ�
 *
 *	@warning
 */

#ifndef __OPDEVSDK_HARDWARE_BASIC_DEVICE_INFO_H__
#define __OPDEVSDK_HARDWARE_BASIC_DEVICE_INFO_H__

/************************************************************************
 Included Header
 ************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif


/************************************************************************
 Macros
 ************************************************************************/

/************************************************************************
 Type Definition
 ************************************************************************/

/**
 * @fn       : template_a
 * @brief    : һ��ʾ���ӿ�
 * @return   : 0
 * @author   : caohaojie
 */
int template_a(void);


/**
 * @fn       : template_get_version
 * @brief    : ����汾��Ϣ
 * @param    : pbyVersion       : [out], ����汾�ţ���ʽΪx.y.z.svn
 * @param    : sdwVerBufLen     : [in] , pbyVersion ���ó���,���鳤��Ϊ32�ֽ�
 * @param    : pbyTime          : [out], �������ʱ��,��ʽΪ %Y-%m-%d %H:%M:%S
 * @param    : sdwTimeBufLen    : [out], pbyTime ���ó���,���鳤��Ϊ32�ֽ�
 * @return   : success:0; other: fail
 * @author   : caohaojie
 */
int template_get_version(char* pbyVersion, int sdwVerBufLen, char* pbyTime, int sdwTimeBufLen);

#ifdef __cplusplus
}
#endif
#endif // __OPDEVSDK_BASIC_DEVICE_INFO_H__
