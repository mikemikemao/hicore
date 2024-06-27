/******************************************************************************
  @note HangZhou Hikvision Digital Technology Co., Ltd. All Right Reserved.
 ******************************************************************************
  @file  aip_util_module.h
  @brief  调试打印模块定义 v1.0.0
******************************************************************************/

#ifndef __AIP_UTIL_MODULE_H__
#define __AIP_UTIL_MODULE_H__

#ifdef __cplusplus
extern "C"
{
#endif

/*----------------------------------------------*
 * Macros                                       *
 *----------------------------------------------*/

/** 主模块定义总览
#define MODULE_DEFAULT                                     (0)
#define MODULE_RFAPP                                       (1)
#define MODULE_NET_PROTOCOL                                (2)
#define MODULE_VERIFY                                      (3)
#define MODULE_GUI_MOUDLE                                  (4)
#define MODULE_EVENT                                       (5)
#define MODULE_FP_MOUDLE                                   (6)
#define MODULE_FACE_MOUDLE                                 (7)
#define MODULE_HD_INTERFACE                                (8)
#define MODULE_NET_BASE                                    (9)
#define MODULE_STORAGE                                     (10)
#define MODULE_SYSTEM                                      (11)
#define MODULE_UTIL                                        (12)
#define MODULE_INTERCOM                                    (13)
#define MODULE_STREAM                                      (14)
#define MODULE_FILE                                        (15)
#define MODULE_HEOP                                        (16)
#define MODULE_EHOME                                       (17)
#define MODULE_QRCODE                                      (18)
#define MODULE_THERMAL                                     (19)
#define MODULE_EZVIZ                                       (20)
#define MODULE_DEVMGMT                                     (21)
#define MODULE_DOWNLINK                                    (22)
#define MODULE_MEDIAPLAY                                   (23)
#define MODULE_ALARM                                       (24)
#define MODULE_BAT                                         (25)
#define MODULE_DBG_MEETING 								   (26)
*/

#define MODULE_MAX_NUM (32) /** 主模块 最大个数   */
#define MASK_MAX_NUM (32)   /** 子模块 最大个数   */

/** @brief 模块定义 */

/********************** BEGIN 默认模块 用于暂时不指定模块分类的打印 **********/
#define MODULE_DEFAULT (0)
/** module slot in MODULE_DEFAULT *********************************/
#define MASK_DEFAULT (0)
/********************** END   默认模块 用于暂时不指定模块分类的打印 **********/

/********************** BEGIN 卡模块 **************************************/
#define MODULE_RFAPP (1)
/** module slot in MODULE_RFAPP ***********************************/
#define MASK_RFAPP_TYPEA (0)
#define MASK_RFAPP_TYPEB (1)
#define MASK_RFAPP_PSAM (2)
#define MASK_ID_BASE (3)
#define MASK_ID_SIMULATOR_BASE (4)
#define MASK_ID_SIMULATOR_DEV (5)
#define MASK_ID_PIV_DEV (6)
#define MASK_RFAPP_CPU (7)
#define MASK_RFAPP_MIFARE (8)
#define MASK_RFAPP_EM (9)

/********************** BEGIN 网络协议模块 *******************************/
#define MODULE_NET_PROTOCOL (2)
/** module slot in MODULE_NET_PROTOCOL *************************************/
#define MASK_SDK_NETFUNCS (0)
#define MASK_SDK_ISAPI_NETFUNCS (1)
#define MASK_SDK_ATTENDANCE (2)
#define MASK_SDK_REPORT (3)
#define MASK_NET_LOGIN (4)
#define MASK_SECURITY_CTRL (5)
#define MASK_DVR_NET (6)
#define MASK_EHOME (7)
#define MASK_EHOME_CMD (8)
#define MASK_POST_PIC (9)
#define MASK_SDK_EZVIZ (10)
#define MASK_SADP (11)
#define MASK_NET_IPCM (12)
#define MASK_NET_RTSP (13)
#define MASK_NET_VIS (14) //对讲私有协议
#define MASK_WEBSOCKET_SERVICE (15)
#define MASK_NET_SERVER (16)
#define MASK_WEB_SERVICE (17)
#define MASK_ISAPI_COMMON (18)
#define MASK_ISAPI_BODY_PROC (19)
#define MASK_SENSOR_COMM (20)
#define MASK_ClOUD (21) //武汉云
#define MASK_NET_ANTI_PROTOCOL (22)
#define MASK_UI_ISAPI_PROTOCOL (23)
#define MASK_NET_UPNP_PROTOCOL (24)
#define MASK_NET_PPP_PROTOCOL (25)
#define MASK_NET_SMTP_PROTOCOL (26)
#define MASK_NET_ONVIF_PROTOCOL (27)


/********************** BEGIN 权限认证模块 *******************************/
#define MODULE_VERIFY (3)
/******************************************************************/
/*module slot in MODULE_VERIFY **************/
#define MASK_VERIFY_DATA_DEAL (0)
#define MASK_VERIFY_USR (1)
#define MASK_PLAN_MNG (2)
#define MASK_ANTI_MNG (3)
#define MASK_DOOR_STATE_MNG (4)
#define MASK_ACS_LOG (5)
#define MASK_SQL_USER (6)
#define MASK_INPUT_DATA_ANALY (7)
#define MASK_VERIFY_MULTI (8)
#define MASK_GPRS_TEST                                   (9)
#define MASK_FACE                                        (10)
#define MASK_VERIFY_LEADER                               (11) // 首卡
#define MASK_VERIFY_INTERLOCK                            (12) // 互锁
#define MASK_VERIFY_CROSS_INTERLOCK                      (13) // 跨设备互锁
#define MASK_CARD                                          (14)

/********************** BEGIN GUI模块 ***********************************/
#define MODULE_GUI_MOUDLE (4)
/** module slot in MODULE_GUI_APP **********************************/
#define MASK_GUI_APP                        (0)

/********************** BEGIN 事件模块 **********************************/
#define MODULE_EVENT (5)
/** module slot in MODULE_EVENT ************************************/
#define MASK_EVENT_MNG (0)
#define MASK_SQL_EVENT (1)
#define MASK_EVENT_LINKAGE (2)
#define MASK_EVENT_UPLOAD                                  (3)


/********************** BEGIN 指纹模块 **********************************/
#define MODULE_FP_MOUDLE (6)
/** module slot in MODULE_FINGER_PRINT *****************************/
#define MASK_HIK_MODULE (0)
#define MASK_HIK_SENSOR (1)
#define MASK_FP_IDENTIFI (2)

/*********************** BEGIN 人脸、识别模块***********************************/
#define MODULE_FACE_MOUDLE (7)
/** module slot in MODULE_FACE_MOUDLE ******************************/
#define MASK_COLLECT (0)
#define MASK_BLACKLIST (1)
#define MASK_FACE_BASE (2)
#define MASK_FACE_PIC (3)
#define MASK_FACE_DATA (4)
#define MASK_FACE_MODEL (5)
#define MASK_MODETCTRL (6)

/********************** BEGIN 硬件接口模块 *******************************/
#define MODULE_HD_INTERFACE (8)
/** module slot in MODULE_INTERFACE ********************************/
#define MASK_INTER_BASE                                    (0)
#define MASK_INTER_DSP                                     (1)
#define MASK_INTER_GUI                                     (2)
#define MASK_INTER_KERNEL                                  (3)
#define MASK_INTER_MCU                                     (4)
#define MASK_INTER_SERIAL                                  (5)
#define MASK_INTER_BSP                                     (6)
#define MASK_INTER_ALARMOUT                                (7)
#define MASK_INTER_AUDIO                                   (8)
#define MASK_INTER_BACKLIGHT                               (9)
#define MASK_INTER_SUB1G                                   (10)
#define MASK_RS485                                         (11)
#define MASK_WEIGAND                                       (12)
#define MASK_DOORBELL                                      (13)
#define MASK_KEYBOARD                                      (14)
#define MASK_COMDEV                                        (15)
#define MASK_BLUETOOTH                                     (16)
#define MASK_LED                                           (17)
#define MASK_BEEP                                          (18)


/********************** BEGIN 基础网络模块 *******************************/
#define MODULE_NET_BASE (9)
/** module slot in MODULE_NET_SER1 ********************************/
#define MASK_NETBASE_DDNS (0)
#define MASK_NETBASE_HTTP (1)
#define MASK_NETBASE_PSIASERVER (2)
#define MASK_NETBASE_RTSPSERVER (3)
#define MASK_NETBASE_NETDA (4)
#define MASK_NETBASE_IPDAD (5)
#define MASK_NETBASE_RTSPCLIENT (6)
#define MASK_NETBASE_SADP (7)
#define MASK_NETBASE_HTTPC (8)
#define MASK_NETBASE_WIFI (9)
#define MASK_NETBASE_FTP (10)
#define MASK_NET_SIP (11)
#define MASK_MAINTAIN_SNTP (12)
#define MASK_NETBASE_ARP (13)
#define MASK_GPRS (14)
#define MASK_NETBASE_CELLULAR (15)

/********************** BEGIN 数据存储模块 ********************************/
#define MODULE_STORAGE (10)
/** module slot in MODULE_STORAGE*********************************/
#define MASK_STOR_CDRW (0)
#define MASK_STOR_EDEV (1)
#define MASK_STOR_HD_MANAGER (2)
#define MASK_STOR_ISCSI (3)
#define MASK_STOR_NFS (4)
#define MASK_STOR_RAID (5)
#define MASK_STOR_ANR (6)
#define MASK_STOR_DISK_QUOTA (7)
#define MASK_STOR_PIC (8)
#define MASK_FACE_DATA_BASE (9)
#define MASK_ACS_DATA_BASE (10)
#define MASK_IMPORT (11)
#define MASK_STOR_REC (12)


/********************** BEGIN 系统模块 ***********************************/
#define MODULE_SYSTEM (11)
/** module slot in MODULE_SYSTEM ********************************/
#define MASK_SYS_ABILITY (0)
#define MASK_SYS_CLOCK (1)
#define MASK_SYS_INIT (2)
#define MASK_SYS_PARAM (3)
#define MASK_SYS_SHDOWN (4)
#define MASK_SYS_INFO (5)
#define MASK_SYS_TASK (6)
#define MASK_SYS_UPGRATE (7)
#define MASK_SYS_USER (8)
#define MASK_SYS_VERSION (9)
#define MASK_SYS_WATCH_DOG (10)
#define MASK_CONFIG_PARAM (11)
#define MASK_CONFIG_JSON (12)
#define MASK_CONFIG_DSP (13)
#define MASK_SYS_CAP (14)
#define MASK_SYS_DAY_NIGHT_CTRL (15)
#define MASK_SYS_SECURITY (16)
#define MASK_SYS_POWER_CTRL (17)
#define MASK_SYS_PWD_MNG (18)

/********************** BEGIN UTIL模块**********************************/
#define MODULE_UTIL (12)
/** module slot in MODULE_UTIL ********************************/
#define MASK_UTIL_COMMON (0)
#define MASK_UTIL_DEBUG (1)
#define MASK_UTIL_ENCRYPT (2)
#define MASK_UTIL_HPR (3)
#define MASK_UTIL_WRAP (4)
#define MASK_UTIL_XML (5)
#define MASK_UTIL_PA (6)
#define MASK_UTIL_XLS (7)
#define MASK_UTIL_T1 (8)
#define MASK_UTIL_DEVSTATUS (9)

/********************** BEGIN INTERCOM模块*****************************/
#define MODULE_INTERCOM (13)
/** module slot in MODULE_INTERCOM ***************************/
#define MASK_INTC_CALL (0)
#define MASK_INTC_DB (1)
#define MASK_INTC_SIPSERVER (2)
#define MASK_INTC_VOIP (3)
#define MASK_INTC_IPC (4)
#define MASK_INTC_SIPC (5)
#define MASK_INTC_PROTOCOL                                 (6) // SIP 协议
#define MASK_INTC_DATABASE                                 (7) // 数据库相关操作
#define MASK_INTC_TALK                                     (8) // 通话逻辑
#define MASK_INTC_ACTION                                   (9)
#define MASK_INTC_COMMON                                   (10)
#define MASK_INTC_ANALOG                                   (11)//半数字


/********************** BEGIN STREAM模块 ********************************/
#define MODULE_STREAM (14)
/** module slot in MODULE_STREAM ********************************/
#define MASK_STREAM_SERVER (0)
#define MASK_STREAM_CLIENT (1)

/*********************** specially used to debug current files. *********/
/*********************** remember module it at last *********************/
#define MODULE_DBG_FILE (15)
/** module slot in MODULE_DBG_FILE ********************************/
#define MASK_DBG_FILE (0)

/********************** HEOP模块 **********************************/
#define MODULE_HEOP (16)
/** module slot in MODULE_DBG_HEOP ********************************/
#define MASK_HEOP (0)
#define MASK_HEOP_IPC (1)
#define MASK_HEOP_PROTOCOL (2)
#define MASK_APP_MANAGE (3)      //三方app管理

/********************** EHOME模块 **********************************/
#define MODULE_EHOME (17)
/** module slot in MODULE_DBG_EHOME ********************************/
#define MASK_EHOME_BASE (0)
#define MASK_EHOME_PIC (1)
#define MASK_EHOME_COMMU    (2)
#define MASK_EHOME_DATA_DEAL (3)

/********************** 二维码模块 **********************************/
#define MODULE_QRCODE (18)
/** module slot in MODULE_DBG_QRCODE ********************************/
#define MASK_QRCODE (0)

/**********************测温模块 **********************************/
#define MODULE_THERMAL (19)
/** module slot in MODULE_DBG_THERMAL ********************************/
#define MASK_THERMO (0)

/********************** EHOME模块 **********************************/
#define MODULE_EZVIZ (20)
/** module slot in MODULE_EZVIZ ********************************/
#define MASK_EZVIZ_BASE (0)
#define MASK_EZVIZ_PIC (1)
#define MASK_EZVIZ_DEAL (2)

/********************** 子设备管理模块 **********************************/
#define MODULE_DEVMGMT (21)
/** module slot in MODULE_DEVMGMT ********************************/
#define MASK_DEVMGMT (0)
#define MASK_SUB_CONTROLLER_MNG (1)
#define MASK_SUB_CONTROLLER_COMMU (2)

/********************** 下行网络模块 **********************************/
#define MODULE_DOWNLINK                  (22)
/** module slot in MODULE_DOWNLINK ********************************/
#define MASK_DOWNLINK_NRDMNG             (0)

/********************** 音视频播放管理模块 **********************************/
#define MODULE_MEDIAPLAY                  (23)
/** module slot in MODULE_MEDIAPLAY ********************************/
#define MASK_AUDIO_PLAY              (0)
#define MASK_BROADCAST               (1)
#define MASK_ADVIDEO                 (2)
#define MASK_AUDIO_PRIORITY          (3)

/********************** 报警检测模块 **********************************/
#define MODULE_ALARM                 (24)
/** module slot in MODULE_ALARM ********************************/
#define MASK_EXCEP_ALARM             (0)
#define MASK_MOVEMENT_DETECT         (1)


/********************** BEGIN 业务自动化测试模块**********************************/
#define MODULE_BAT                                          (25)
/** module slot in MODULE_BAT ********************************/
#define MASK_BAT_ATS                                        (0)
#define MASK_BAT_MAIN                                       (1)
#define MASK_BAT_ACS                                        (2)
/********************** END 业务自动化测试模块***********************************/

/********************** 会议平板模块 **********************************/
#define MODULE_DBG_MEETING 									(26)
/** module slot in MODULE_DBG_MEETING ********************************/
#define MASK_MEETING_DATA_BASE                              (0)
#define MASK_MEETING_MNG                                    (1)

#ifdef __cplusplus
}
#endif

#endif // __UTIL_MODULE_H__
