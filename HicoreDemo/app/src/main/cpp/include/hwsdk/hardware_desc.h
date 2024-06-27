/**
 * @file      : hardware_desc.h
 * @brief     :
 * @author    : baozhonghui (baozhonghui@hikvision.com.cn)
 * @version   : V1.0.0
 * @date      : 2021-01-06 02:01:58
 * @copyright : Copyright (c) 2021
 **/
#ifndef __OPDEVSDK_HARDWARE_DESC_H__
#define __OPDEVSDK_HARDWARE_DESC_H__
#include "opdevsdk_hardware_ex.h"
#include "opdevsdk_hardware_common.h"

typedef enum
{
    DEV_NODE_NAME_DEV_TTYS1 = 1,    // "/dev/ttyS1"
    DEV_NODE_NAME_DEV_TTYS2 = 2,    // "/dev/ttyS2"
    DEV_NODE_NAME_DEV_TTYS3 = 3,    // "/dev/ttyS3"
    DEV_NODE_NAME_DEV_TTYS4 = 4,    // "/dev/ttyS4"
    DEV_NODE_NAME_DEV_TTYRS485_1 = 5, // "/dev/DDM/tty_rs485_1"
    DEV_NODE_NAME_DEV_TTYACM = 6, // "/dev/ttyACM0"
    DEV_NODE_NAME_MAX,
}DEV_NODE_NAME_E;

typedef enum
{
    HW_IF_TYPE_485_1       = 1, //��һ·485�ӿ�
    HW_IF_TYPE_WIEGAND_1,       //��һ·Τ���ӿ�
    HW_IF_TYPE_ALARMIN,         //��������
    HW_IF_TYPE_ALARMOUT,        //�������
    HW_IF_TYPE_RF,              //��Ƶ�ӿ�
    HW_IF_TYPE_RF_125K,         //��Ƶ�ӿ�----125K
    HW_IF_TYPE_RF_1356M,        //��Ƶ�ӿ�-----13.56M
    HW_IF_TYPE_FINGER,       //ָ�ƽӿ�
    HW_IF_TYPE_ID_READER,       //���֤�Ķ���
    HW_IF_TYPE_TAMPER,       //����ӿ���Ϣ
    HW_IF_TYPE_QR, //��һ·��ά���ͷ
    HW_IF_TYPE_MAX
} HW_IF_TYPE_E;

typedef enum
{
    HARDWARE_CONN_MODE_SOC       = 0, //�ӿ�������SOC
    HARDWARE_CONN_MODE_MCU,           //�ӿ�������MCU
    HARDWARE_CONN_MODE_NO_EXIST,      //�ӿڲ�����
    HARDWARE_CONN_MODE_MAX
} HARDWARE_CONN_MODE_E;

typedef struct
{
    HPR_INT8 * pbyName;                    //�ڵ�����ָ���ڵ�������ָ���ڵ������ʣ�����ʹ��Ĭ�Ϸ��ʷ�ʽ
    HARDWARE_CONN_MODE_E enConnType;   //�ӿ����ӷ�ʽ
    HPR_INT32 dwBitNo;                       //��Ӧ��bitλ���������������io������2.0�İ汾�޸�ʧ���£��޸�Ϊ��0��ʼ;
}INTFACE_DESC_T;



typedef struct
{
    HPR_INT8 byDevName[64];
    HPR_UINT8 byMcuNum;
    HPR_UINT8 byAlarmOutNum;  ///< the alarm out number of hardware
    INTFACE_DESC_T stAlarmOut[4];
    HPR_UINT8 byAlarmInNum;   ///< the alarm in number of hardware
    INTFACE_DESC_T stAlarmIn[8];
    HPR_UINT8 byRs485Num;   ///< the RS485 number of hardware
    INTFACE_DESC_T stRs485[2];

    HPR_UINT8 byRf1356MNum;  ///< the rf 13.56M Num of hardware
    INTFACE_DESC_T stRf1356M[2];
    HPR_UINT8 byRf125KNum;  ///< the rf 125k Num of hardware
    INTFACE_DESC_T stRf125k[2];
    HPR_UINT8 byWiegandNum;  ///< the wiegand Num of hardware
    INTFACE_DESC_T stWiegand[4];
    HPR_UINT8 byDoorSensorNum;  ///< the door sensor of hardware
    INTFACE_DESC_T stDoorSensor[4];
    HPR_UINT8 byDoorButtonNum;  ///< the door button of hardware
    INTFACE_DESC_T stDoorButton[4];
    HPR_UINT8 byLockerNum;   ///< the locker button of hardware
    INTFACE_DESC_T stFinger;
    INTFACE_DESC_T stIdReader;
    HPR_UINT8 byTamperNum;  ///< the tamper number of hardware
    INTFACE_DESC_T stTamper[4];
    INTFACE_DESC_T stQr;

}HARDWARE_DESC_T;


typedef struct
{
    HPR_INT32 dwDeviceType;  //�豸�ͺ�
    HPR_INT8* pbyDeviceName;  //�豸��
    HPR_INT32 (* hardware_desc)(HARDWARE_DESC_T * pstHardwareDesc);  //��ȡ�豸�����ӿ�
    struct HARDWARE_TREE_T *pstNextDevice;   //
}HARDWARE_TREE_T;


#define HARDWARE_FUNC_NAME(name) void opdevsdk_hwif_get_hard_desc_ ## name(HARDWARE_DESC_T * pstru)
#define HARDWARE_FUNC(name) HARDWARE_FUNC_NAME(name)

#define HARDWARE_FUNC_EX(name_string, dev_type, dev_calss) \
void opdevsdk_hwif_get_hard_desc_ ## dev_type(HARDWARE_DESC_T * pstru)                                  \
{                                                                                                   \
    if(NULL == pstru)                                                                               \
    {                                                                                               \
        printf("NULL == pstru");                                                                    \
        return ;                                                                                    \
    }                                                                                               \
    printf("get %s hardward\n", #name_string);                                                      \
    opdevsdk_hwif_get_hard_desc_ ## dev_calss(pstru);                                                         \
    snprintf((HPR_INT8*)&pstru->byDevName , sizeof(pstru->byDevName), "%s", #name_string);    \
} \

HPR_INT8* opdevsdk_hwif_get_dev_node_name(DEV_NODE_NAME_E enKey);
HARDWARE_DESC_T* opdevsdk_hardware_get_device_info();
HARDWARE_CONN_MODE_E opdevsdk_hwif_check_capa_support(HW_IF_TYPE_E enType);
HPR_INT32 opdevsdk_hwif_hardware_info_init(OPDEVSDK_ST_INIT_OPTIONS* pstruParam);
HPR_INT32 opdevsdk_hwif_hardware_is_support_mcu();
HPR_INT32 opdevsdk_hwif_hardware_is_init_desc();
#endif