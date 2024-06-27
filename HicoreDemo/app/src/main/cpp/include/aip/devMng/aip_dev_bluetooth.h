/**
 * @copyright  HangZhou Hikvision Digital Technology Co., Ltd. All Right Reserved.
 * @file       aip_dev_bluetooth.h
 * @brief      蓝牙对外接口
**/

#ifndef __AIP_DEV_BLUETOOTH_H__
#define __AIP_DEV_BLUETOOTH_H__

/************************************************************************
 Included Header
 ************************************************************************/
#include "common/aip_common.h"
#include "common/aip_common_event.h"

#ifdef __cplusplus
extern "C" {
#endif

/************************************************************************
 Macros
 ************************************************************************/
#ifdef ANDROID
    #define AIP_BLUETOOTH_NAME_LEN        (20)    // 蓝牙名称长度限制,包含截断符
#else
    #define AIP_BLUETOOTH_NAME_LEN        (30)    // 蓝牙名称长度限制,包含截断符
    #define AIP_HOST_BLUETOOTH_NAME_LEN   (29)    // 主机蓝牙名称长度限制,包含截断符
#endif

#define AIP_BLUETOOTH_MANUFACTURE_LEN (31)    //蓝牙广播报文最长就31字节，还需要包含其他字段

/************************************************************************
 Type Definition
 ************************************************************************/

/**
 * @brief 蓝牙模块AIP_EVENT_CMD_E索引
 * @note AIP_EVENT_MODULE_E为 E_AIP_EVENT_MODULE_DEV_BLUETOOTH
**/
typedef enum
{
    E_BLUETOOTH_STATUS_UPDATE  = 0,   // 底层蓝牙开关状态信息更新
                                      // 可主动调用aip_dev_bluetooth_status_get 获取最新蓝牙开关状态
                                      //入参:NULL
                                      //出参:NULL
                                      //返回值: HPR_OK
                                      //        HPR_FALSE
    E_BLUETOOTH_RECV_MSG       = 1,   // 蓝牙收到消息
                                      //入参:BLUETOOTH_EVENT_RECV_MSG_P
                                      //出参:NULL
                                      //返回值: HPR_OK
                                      //        HPR_FALSE
} BLUETOOTH_EVENT_CMD_E;

/**
 * @brief  蓝牙收到消息回调
 * @note AIP_EVENT_MODULE_E为 E_AIP_EVENT_MODULE_DEV_BLUETOOTH
 * @note AIP_EVENT_CMD_E为 E_BLUETOOTH_RECV_MSG
 * 对应的入参
**/
typedef struct
{
    HPR_INT8*  pbyData;    //收到的蓝牙数据
    HPR_UINT32 dwLen;      //收到的蓝牙数据长度
} BLUETOOTH_EVENT_RECV_MSG_T, *BLUETOOTH_EVENT_RECV_MSG_P;

/**
 *  @brief 蓝牙服务回调
 */
typedef AIP_EVENT_CALLBACK_FUN BLUETOOTH_EVENT_CALLBACK_FUN ;

/**
 * @brief: 当前蓝牙开关状态
**/
typedef enum
{
    E_BLUETOOTH_STATUS_CLOSED    = 0,      // 关闭
    E_BLUETOOTH_STATUS_OPEN      = 1,      // 开启,但未连接
    E_BLUETOOTH_STATUS_CONNECTED = 2,      // 开启,且已连接
    E_BLUETOOTH_STATUS_INVALID,            // 非法类型
} AIP_BLUETOOTH_STATUS_E;

//@breif: 蓝牙初始化参数
typedef struct
{

    HPR_BOOL   bEnable;                            // 表示是否开启蓝牙(ble蓝牙广播由BSP确认是否与蓝牙一起打开）
    HPR_INT8   byaName[AIP_BLUETOOTH_NAME_LEN + 1];    // 蓝牙名称
    HPR_INT32  sdwFactoryId;                       // 蓝牙厂商ID, 仅BLE蓝牙需要
    HPR_INT8   byaManufactureData[AIP_BLUETOOTH_MANUFACTURE_LEN];    // 广播私有数据, 仅BLE蓝牙需要
    HPR_UINT32 dwManufactureLen;                                     // 广播私有数据有效长度,表示byaManufactureData中有效数据的长度
} AIP_BLUETOOTH_PARAM_T, *AIP_BLUETOOTH_PARAM_P;

/************************************************************************
  Function Declaration
 ************************************************************************/

/**
 * @fn        AIP_EXTERN HPR_INT32 aip_dev_bluetooth_service_start(AIP_BLUETOOTH_PARAM_P pstParam, BLUETOOTH_EVENT_CALLBACK_FUN fnCbFun);
 * @brief     开启蓝牙服务
 * @note      初始化时设置指定的蓝牙名称，和厂商私有数据。根据指定的开关状态配置。(ble蓝牙广播由BSP确认是否与蓝牙一起打开）
 * @param[in] pstParam, 初始化参数
 * @param[in] fnCbFun,  回调处理函数
 * @return    HPR_OK: success； other:fail
 **/
AIP_EXTERN HPR_INT32 aip_dev_bluetooth_service_start(AIP_BLUETOOTH_PARAM_P pstParam, BLUETOOTH_EVENT_CALLBACK_FUN fnCbFun);

/**
 * @fn     HPR_INT32 aip_dev_bluetooth_service_stop(HPR_VOID)
 * @brief  关闭蓝牙服务
 * @return HPR_OK: success； other:fail
 * @note   当前不支持, always返回HRP_OK
 **/
HPR_INT32 aip_dev_bluetooth_service_stop(HPR_VOID);

/**
 * @fn        AIP_EXTERN HPR_INT32 aip_dev_bluetooth_set_manufacture(HPR_INT32 sdwFactoryId, HPR_INT8* pbyManufacture, HPR_UINT32 dwLen);
 * @brief     设置蓝牙广播的私有数据
 * @note      ble 蓝牙模式相关,
 *            仅允许在蓝牙开启状态下配置,未开启状态下报错
 *                蓝牙已经打开状态下，按照以下接口接口调用顺序配置aip_dev_bluetooth_close_advertising -> aip_dev_bluetooth_set_manufacture -> aip_dev_bluetooth_open_advertising
 *                蓝牙关闭状态下，按照以下接口接口调用顺序配置aip_dev_bluetooth_open -> aip_dev_bluetooth_set_manufacture -> aip_dev_bluetooth_open_advertising
 * @param[in] sdwFactoryId, SIG联盟分配的厂商id 如0xAABB
 * @param[in] pbyManufacture : 私有数据，int类型数组，如 {0x30, 0xFF, 0X31, 0XAA}
 * @param[in] dwLen, 私有数据对应的长度
 * @return    HPR_OK: success； other:fail
 **/
AIP_EXTERN HPR_INT32 aip_dev_bluetooth_set_manufacture(HPR_INT32 sdwFactoryId, HPR_INT8* pbyManufacture, HPR_UINT32 dwLen);

/**
 * @fn        AIP_EXTERN HPR_INT32 aip_dev_bluetooth_set_name(const HPR_INT8* szName)
 * @brief     设置蓝牙名称
 * @param[in] szName: 蓝牙名称, see AIP_BLUETOOTH_NAME_LEN define
 *            仅允许在蓝牙开启状态下配置,未开启状态下报错
 *                针对ble模式时
 *                蓝牙已经打开状态下，按照以下接口接口调用顺序配置aip_dev_bluetooth_close_advertising -> aip_dev_bluetooth_set_name -> aip_dev_bluetooth_open_advertising
 *                蓝牙关闭状态下，按照以下接口接口调用顺序配置aip_dev_bluetooth_open -> aip_dev_bluetooth_set_name -> aip_dev_bluetooth_open_advertising
 *                针对经典蓝牙模式时
 *                蓝牙已经打开状态下，按照以下接口接口调用顺序配置 aip_dev_bluetooth_set_name
 *                蓝牙关闭状态下，按照以下接口接口调用顺序配置aip_dev_bluetooth_open -> aip_dev_bluetooth_set_name

 * @return    HPR_OK: success； other:fail
 **/
AIP_EXTERN HPR_INT32 aip_dev_bluetooth_set_name(const HPR_INT8* szName);

/**
 * @fn       AIP_EXTERN AIP_BLUETOOTH_STATUS_E aip_dev_bluetooth_status_get(HPR_VOID);
 * @brief    获取蓝牙开关状态
 * @return   开关状态, sed AIP_BLUETOOTH_STATUS_E define
 **/
AIP_EXTERN AIP_BLUETOOTH_STATUS_E aip_dev_bluetooth_status_get(HPR_VOID);

/**
 * @fn       AIP_EXTERN HPR_BOOL aip_dev_bluetooth_advertising_status_get(HPR_VOID)
 * @brief    获取蓝牙开关广播状态
 * @return   开关状态, sed HPR_BOOL define
 **/
AIP_EXTERN HPR_BOOL aip_dev_bluetooth_advertising_status_get(HPR_VOID);

/**
 * @fn       AIP_EXTERN HPR_INT32 aip_dev_bluetooth_open(HPR_VOID)
 * @brief    打开蓝牙
 * @return   HPR_OK: success； other:fail
 **/
AIP_EXTERN HPR_INT32 aip_dev_bluetooth_open(HPR_VOID);

/**
 * @fn       AIP_EXTERN HPR_INT32 aip_dev_bluetooth_close(HPR_VOID)
 * @brief    关闭蓝牙
 * @note     BLE蓝牙关闭蓝牙线要先关闭蓝牙广播，否则ble蓝牙还在广播
 * @return   HPR_OK: success； other:fail
 **/
AIP_EXTERN HPR_INT32 aip_dev_bluetooth_close(HPR_VOID);

/**
 * @fn       AIP_EXTERN HPR_INT32 aip_dev_bluetooth_open_advertising(HPR_VOID)
 * @brief    打开蓝牙广播
 * @note     ble 蓝牙模式相关
 * @return   HPR_OK: success； other:fail
 **/
AIP_EXTERN HPR_INT32 aip_dev_bluetooth_open_advertising(HPR_VOID);

/**
 * @fn       AIP_EXTERN HPR_INT32 aip_dev_bluetooth_close_advertising(HPR_VOID)
 * @brief    关闭蓝牙广播
 * @note     ble 蓝牙模式相关
 * @return   HPR_OK: success； other:fail
 **/
AIP_EXTERN HPR_INT32 aip_dev_bluetooth_close_advertising(HPR_VOID);

/**
 * @fn      AIP_EXTERN HPR_INT32 aip_dev_bluetooth_send(HPR_INT8* pbyData, HPR_UINT32 dwLen);
 * @brief   通过蓝牙发送数据
 * @return  fail:-1, success:将返回一个整数，表示实际发送的长度
 **/
AIP_EXTERN HPR_INT32 aip_dev_bluetooth_send(HPR_INT8* pbyData, HPR_UINT32 dwLen);

/**
 * @fn      AIP_EXTERN HPR_INT32 aip_dev_bluetooth_set_disconnect(HPR_VOID);
 * @brief   主动断开连接在设备上的所有蓝牙
 * @return  HPR_OK: success； other:fail
 **/
AIP_EXTERN HPR_INT32 aip_dev_bluetooth_set_disconnect(HPR_VOID);

#ifdef __cplusplus
}
#endif
#endif /* __AIP_DEV_BLUETOOTH_H__ END */
