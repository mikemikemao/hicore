/**
 * @copyright  HangZhou Hikvision Digital Technology Co., Ltd. All Right Reserved.
 * @file       aip_usb_mng.h
 * @brief      usb 节点管理
**/

#ifndef __AIP_USB_MNG_H__
#define __AIP_USB_MNG_H__

/************************************************************************
 Included Header
 ************************************************************************/
#include "common/aip_common.h"


#ifdef __cplusplus
extern "C" {
#endif

/************************************************************************
 Macros
 ************************************************************************/
//推荐的usb挂载路径
#define USB_MOUNT_NODE                      "/mnt/usb"

//错误码
#define AIP_DEV_ERR_PARAM                    (-1) //参数错误
#define AIP_DEV_ERR_USB_NO_NODE              (-2) //找不到usb节点(usb未插入或者已损坏)
#define AIP_DEV_ERR_USB_MOUNT_FAIL           (-3) //挂载失败
#define AIP_DEV_ERR_MOUNT_PATH_CREATE_FAIL   (-4) //挂载目录创建失败
#define AIP_DEV_ERR_USB_UMOUNT_FAIL          (-5) //卸载失败

/************************************************************************
 Type Definition
 ************************************************************************/

/**
 * @brief  挂载权限方式
**/
typedef enum
{
    E_MOUNT_OPT_RO = 0,      // 只读方式挂载
    E_MOUNT_OPT_RW = 1,      // 读写方式挂载
} MOUNT_OPT_PERMISSION_TYPE_E;


/************************************************************************
  Function Declaration
 ************************************************************************/

/**
 * @fn        AIP_EXTERN HPR_INT32 aip_usb_mount(const HPR_INT8* szMountPath)
 * @brief     挂载U盘, 内部会自动检索U盘的节点
 * @param[in] szMountPath : U盘 挂载的路径, 推荐使用USB_MOUNT_NODE 挂载在/mnt下
 * @return    HPR_OK: success
 *            AIP_DEV_ERR_PARAM: 参数错误
 *            AIP_DEV_ERR_USB_NO_NODE: 找不到usb节点(usb未插入或者已损坏)
 *            AIP_DEV_ERR_USB_MOUNT_FAIL: 挂载失败
 *            AIP_DEV_ERR_MOUNT_PATH_CRESTE_FAIL: 挂载目录创建
 * @note      按照/dev/msc%s > /dev/msd%s > /dev/msa%s> /dev/msb%s > /dev/sda%s > /dev/sbd%s 的优先级寻找usb节点挂载
 *            其中 %s指代空或1-8数字。且按照以下优先级 如/dev/msc1 > /dev/msc2 >.../dev/msc8 > /dev/msc
 * @note      如果usb节点已经挂载会先卸载再挂载，如果挂载目录已经挂载，会先卸载再挂载。
 * @note      只会尝试以"vfat" 和“exfat”、“fuseblk”格式进行挂载, 实际系统支持的文件格式可以通过 /proc/filesystems查看
 * @note      卸载请使用系统接口umount
**/
AIP_EXTERN HPR_INT32 aip_usb_mount(const HPR_INT8* szMountPath);

/**
 * @fn        AIP_EXTERN HPR_INT32 aip_usb_mount_from_original_block(const HPR_INT8* szMountPath)
 * @brief     挂载U盘, 内部会自动检索U盘的原始节点
 * @param[in] szMountPath : U盘 挂载的路径, 推荐使用USB_MOUNT_NODE 挂载在/mnt下
 * @return    HPR_OK: success
 *            AIP_DEV_ERR_PARAM: 参数错误
 *            AIP_DEV_ERR_USB_NO_NODE: 找不到usb节点(usb未插入或者已损坏)
 *            AIP_DEV_ERR_USB_MOUNT_FAIL: 挂载失败
 *            AIP_DEV_ERR_MOUNT_PATH_CRESTE_FAIL: 挂载目录创建
 * @note      按照/dev/msc%s > /dev/msd%s > /dev/msa%s> /dev/msb%s > /dev/sda%s > /dev/sbd%s 的优先级寻找usb节点挂载
 *            其中 %s指代空或1-8数字。且按照以下优先级 如/dev/msc1 > /dev/msc2 >.../dev/msc8 > /dev/msc
 * @note      如果usb节点已经挂载会先卸载再挂载，如果挂载目录已经挂载，会先卸载再挂载。
 * @note      只会尝试以"vfat" 和“exfat”、“fuseblk”格式进行挂载, 实际系统支持的文件格式可以通过 /proc/filesystems查看
 * @note      卸载请使用系统接口umount
**/
AIP_EXTERN HPR_INT32 aip_usb_mount_from_original_block(const HPR_INT8* szMountPath);

/**
 * @fn          AIP_EXTERN HPR_BOOL aip_check_mount_node_permission(HPR_INT8* szNode, MOUNT_OPT_PERMISSION_TYPE_E eOptType)
 * @brief       检查设备节点挂载权限方式
 * @param[in]   szNode, 表示设备节点
 * @param[in]   eOptType, 表示想要查询的挂载权限方式
 * @return      HPR_TRUE: 挂载方式和eOptType一致; HPR_FALSE: 未被挂载或不一致
*/
AIP_EXTERN HPR_BOOL aip_check_mount_node_permission(HPR_INT8* szNode, MOUNT_OPT_PERMISSION_TYPE_E eOptType);

/**
 * @fn          AIP_EXTERN HPR_BOOL aip_check_mount_path_permission(HPR_INT8* szName, MOUNT_OPT_PERMISSION_TYPE_E eOptType)
 * @brief       检查挂载路径挂载权限方式
 * @param[in]   szPath 表示挂载路径名
 * @param[in]   eOptType, 表示想要查询的挂载权限方式
 * @return      HPR_TRUE: 挂载方式和eOptType一致; HPR_FALSE: 未被挂载或不一致
*/
AIP_EXTERN HPR_BOOL aip_check_mount_path_permission(HPR_INT8* szPath, MOUNT_OPT_PERMISSION_TYPE_E eOptType);

/**
 * @fn          AIP_EXTERN HPR_BOOL aip_check_dev_node_has_mount(HPR_INT8* szNode, HPR_INT8 *pbyPathBuf, HPR_UINT32 dwBufSize)
 * @brief       查看指定的设备节点是否已经被挂载
 * @param[in]   szNode 表示设备节点名
 * @param[out]  pbyPathBuf 允许为NULL， 当不为NULL时且设备节点被挂载时，将返回挂载路径
 * @param[in]   dwBufSize 的空间长度
 * @return      HPR_TRUE: 对应的节点或者路径已经被挂载; HPR_FALSE: 未被挂载
*/
AIP_EXTERN HPR_BOOL aip_check_dev_node_has_mount(HPR_INT8* szNode, HPR_INT8 *pbyPathBuf, HPR_UINT32 dwBufSize);

/**
 * @fn          AIP_EXTERN HPR_BOOL aip_check_path_has_mount(HPR_INT8* szPath, HPR_INT8 *pbyNodeBuf, HPR_UINT32 dwBufSize)
 * @brief       查看指定的设备路径是否已经被挂载
 * @param[in]   szPath 表示挂载路径 , 如 “/tmp”, 请勿写成“/tmp/”
 * @param[out]  pbyNodeBuf 允许为NULL， 当不为NULL时且设备节点被挂载时，将返回挂载的设备节点
 * @param[in]   dwBufSize 的空间长度
 * @return      HPR_TRUE: 对应的节点或者路径已经被挂载; HPR_FALSE: 未被挂载
*/
AIP_EXTERN HPR_BOOL aip_check_path_has_mount(HPR_INT8* szPath, HPR_INT8 *pbyNodeBuf, HPR_UINT32 dwBufSize);

#ifdef __cplusplus
}
#endif
#endif /* __AIP_USB_MNG_H__ END */
