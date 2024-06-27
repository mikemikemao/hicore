/**	@file opdevsdk_hardware_basic_device_info.h
 *	@note 2012-2019 HangZhou Hikvision Digital Technology Co., Ltd. All Right Reserved.
 *	@brief 设备基础信息头文件
 *
 *	@author		baozhonghui
 *	@date		2020/09/11
 *
 *	@note 历史记录：
 *	@note 2020/09/11 V1.0.0 baozhonghui 新建文件
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
 * @brief    : 一个示例接口
 * @return   : 0
 * @author   : caohaojie
 */
int template_a(void);


/**
 * @fn       : template_get_version
 * @brief    : 组件版本信息
 * @param    : pbyVersion       : [out], 组件版本号，格式为x.y.z.svn
 * @param    : sdwVerBufLen     : [in] , pbyVersion 可用长度,建议长度为32字节
 * @param    : pbyTime          : [out], 组件编译时间,格式为 %Y-%m-%d %H:%M:%S
 * @param    : sdwTimeBufLen    : [out], pbyTime 可用长度,建议长度为32字节
 * @return   : success:0; other: fail
 * @author   : caohaojie
 */
int template_get_version(char* pbyVersion, int sdwVerBufLen, char* pbyTime, int sdwTimeBufLen);

#ifdef __cplusplus
}
#endif
#endif // __OPDEVSDK_BASIC_DEVICE_INFO_H__
