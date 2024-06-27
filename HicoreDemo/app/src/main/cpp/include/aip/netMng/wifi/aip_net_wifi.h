/**
 * @copyright HangZhou Hikvision Digital Technology Co., Ltd. All Right Reserved.
 * @file      aip_net_wifi.h
 * @brief     wifi网络配置公共接口
**/

#ifndef __AIP_NET_WIFI_H__
#define __AIP_NET_WIFI_H__

/************************************************************************
 Included Header
 ************************************************************************/
#include "common/aip_common.h"
#include "lstLib.h"

#ifdef __cplusplus
extern "C"{
#endif

/************************************************************************
 Macros
 ************************************************************************/
#define NET_WIFI_SSID_LEN           64      // 支持的最长wifi ssid 长度(包含截断符)
#define NET_WIFI_BSSID_LEN          20      // 支持的最长wifi bssid 长度(包含截断符)
#define NET_WIFI_KEY_LEN            64      // 支持的最长wifi key 长度(包含截断符)

/* GNU AP模式相关宏. */
#define NET_WIFI_AP_HOSTAPD_CTRL_INTERFACE ("/home/app/aip/var/run/hostapd") // hostapd控制Unix套接字目录
#define NET_WIFI_AP_INTERFACE (NET_IF_NAME_WLAN0)                            // 开启ap的网卡名
#define NET_WIFI_AP_UNIX_DOMAIN_SOCKET_PATH ("/home/app/aip/var/run/hostapd/wlan0")

/************************************************************************
 Type Definition
 ************************************************************************/

/**
 * @brief: 无线网卡驱动类型
 * @note:  该参数选择需要和设备实际无线网卡驱动类型对应
**/
typedef enum
{
    E_WIFI_DRIVER_WEXT    = 0,      // 基于ioctl的wext
    E_WIFI_DRIVER_NL80211 = 1,      // 基于netlink的80211
    E_WIFI_DRIVER_INVALID,          // 非法类型
} NET_WIFI_DRIVER_TYRE_E;

//@breif: wifi sta 模式参数
typedef struct
{
    HPR_BOOL bEnable;     //表示是否开启对应的网络链接
    NET_WIFI_DRIVER_TYRE_E eDriverType; //无线网卡驱动类型
                                        //linux: 需要根据实际设备的无线驱动类型选择参数
                                        //android: 该参数无效由android系统自动识别
} WIFI_STA_MODE_PARAM_T, *WIFI_STA_MODE_PARAM_P;

//@breif: wifi ap 模式参数
typedef struct
{
    HPR_BOOL bEnable;      //表示是否开启对应的网络链接
} WIFI_AP_MODE_PARAM_T, *WIFI_AP_MODE_PARAM_P;

//@breif: wifi服务初始化模块
//@note: bSupStaMode bSupApMode 至少有一个应当为HPR_TRUE
typedef struct
{
    HPR_BOOL bSupStaMode;  //支持sta模式（即设备通过wifi连接其他热点）
    WIFI_STA_MODE_PARAM_T  stStaParam; //sta模式参数。仅在bSupStaMode 使能时有效
 
    HPR_BOOL bSupApMode;   //支持Ap模式 （即设备作为Ap热点被别人连接）
    WIFI_AP_MODE_PARAM_T   stApParam;//Ap模式参数。仅在bSupApMode 使能时有效
} WIFI_SERVICE_INIT_PARAM_T, *WIFI_SERVICE_INIT_PARAM_P;

/**
 * @brief: 当前wifi连接状态
**/
typedef enum
{
    E_WIFI_STATUS_CLOSED       = 0,      // WIFI已关闭
    E_WIFI_STATUS_OPENING      = 1,      // wifi打开中
    E_WIFI_STATUS_DISCONNECTED = 2,      // WIFI未连接或断开连接
    E_WIFI_STATUS_CONNECTING   = 3,      // WIFI正在连接中
    E_WIFI_STATUS_CONNECTED    = 4,      // WIFI已连接
    E_WIFI_STATUS_INVALID,               // 非法类型
} NET_WIFI_STATUS_E;

/**
 * @enum:	NET_WIFI_AP_STATUS
 * @brief:  WiFi AP 状态.
 * @author: xiaoxinyu
 */
typedef enum
{
    E_WIFI_AP_STATUS_CLOSING = 0, // 关闭中
    E_WIFI_AP_STATUS_CLOSED,      // 已关闭
    E_WIFI_AP_STATUS_OPENING,     // 开启中
    E_WIFI_AP_STATUS_OPENED,      // 已开启
    E_WIFI_AP_STATUS_FAILED,      // 状态异常
} NET_WIFI_AP_STATUS_E;

/**
 * @enum:	NET_WIFI_AP_ERR_CODE
 * @brief:  WiFi AP模式错误码
 * @author: xiaoxinyu
 */
typedef enum
{
    E_WIFI_AP_ERR_OK = 0,            // 正常
    E_WIFI_AP_ERR_ERROR = 1,         // 通用错误
    E_WIFI_AP_ERR_OPEN_FAILED,       // 开启AP模式失败
    E_WIFI_AP_ERR_CLOSE_FAILED,      // 关闭AP模式失败
    E_WIFI_AP_ERR_NOT_SUPPORT,       // 当前不支持AP模式
    E_WIFI_AP_ERR_SSID_LENGTH,       // AP热点名称长度不合法
    E_WIFI_AP_ERR_RISKY_PASSWD,      // 风险密码
    E_WIFI_AP_ERR_SECURITY_PROTOCOL, // 不支持的AP加密协议类型
    E_WIFI_AP_ERR_CONFIG_FAILED,     // WiFi参数配置失败

    E_WIFI_AP_ERR_UNKNOWN, // 未知错误
} NET_WIFI_AP_ERR_CODE;

/**
 * @brief: Wifi安全性 类型
**/
typedef enum
{
    E_WIFI_SECURITY_NONE            = 0, // 不加密
    E_WIFI_SECURITY_WEP             = 1, // wep加密
    E_WIFI_SECURITY_WPA_PSK         = 2, // wpa-psk
    E_WIFI_SECURITY_WPA_ENTPRISE    = 3, // wpa-Enterprise
    E_WIFI_SECURITY_WPA2_PSK        = 4, // WPA2_PSK
    E_WIFI_SECURITY_WPA2_ENTERPRISE = 5, // WPA2-enterprise
    E_WIFI_SECURITY_WPA3            = 6, // WPA3
    E_WIFI_SECURITY_INVALID,             // 非法类型
} NET_WIFI_SECURITY_E;

/**
 * @brief: ap热点基础信息
 * @note : 添加网络时仅需要以下信息
**/
typedef struct
{
    HPR_INT8            byaSsid[NET_WIFI_SSID_LEN];    // 网络的SSID,即一般意义的wifi名
    NET_WIFI_SECURITY_E eSecurity;                     // 要添加网络的安全类型
    HPR_INT8            byaKey[NET_WIFI_KEY_LEN];      // 要添加网络的密钥. eSecurity不为E_WIFI_SECURITY_NONE,需要提供对应的密钥 */
} NET_WIFI_NETWORK_INFO_T, *NET_WIFI_NETWORK_INFO_P;

/**
 * @brief: ap热点信息
**/
typedef struct
{
    HPR_INT8                byaSsid[NET_WIFI_SSID_LEN];    // 网络的SSID,即一般意义的wifi名
    NET_WIFI_SECURITY_E     eSecurity;                     // 要添加网络的安全类型
    HPR_INT8                byaBssid[NET_WIFI_BSSID_LEN];  // BSSID
    HPR_UINT32              dwSignalStrength;              // 网络的信号等级信息, 0-100信号由最弱变为最强*/
    HPR_INT32               sdwSignalLevel;                // 网络的信号原始信噪比, 一般是一个负数值，dwSignalStrength 依赖该值转换得到。*/
} NET_WIFI_NETWORK_DETAILS_INFO_T, *NET_WIFI_NETWORK_DETAILS_INFO_P;

/**
 * @brief: ap热点链表节点
**/
typedef struct
{
    NODE                            node;              //链表节点
    NET_WIFI_NETWORK_DETAILS_INFO_T stInfo;
} NET_WIFI_NETWORK_DETAILS_INFO_NODE_T, *NET_WIFI_NETWORK_DETAILS_INFO_NODE_P;

typedef LIST NET_WIFI_INFO_LIST;         /* wifi节点列表，每个链表节点结构体为 NET_WIFI_NETWORK_DETAILS_INFO_NODE_P*/

// wifi 链接信息
typedef struct 
{
    NET_WIFI_STATUS_E               eCurStatus;    //当前wifi状态
    NET_WIFI_NETWORK_DETAILS_INFO_T stInfo;        //如果处于已经状态，表示连接的ap网络信息，否则无意义
} NET_WIFI_STATUS_INFO_T, *NET_WIFI_STATUS_INFO_P;


/************************************************************************
  Function Declaration
 ************************************************************************/

/**
 * @fn       AIP_EXTERN HPR_INT32 aip_net_wifi_service_start(WIFI_SERVICE_INIT_PARAM_P pstParam)
 * @brief    开启wifi服务
 * @param[in] pstParam : wifi服务模块参数
 * @note     开启wifi后，将尝试自动连接之前保存并选择连接的ap网络
 * @return   HPR_OK: success； other:fail
**/
AIP_EXTERN HPR_INT32 aip_net_wifi_service_start(WIFI_SERVICE_INIT_PARAM_P pstParam);

/**
 * @fn     AIP_EXTERN HPR_INT32 aip_net_wifi_service_stop(HPR_VOID)
 * @brief  关闭wifi服务
 * @note   调用该接口后将会完全释放wifi相关服务，再次调起将会存在一定时间消耗
 * @return HPR_OK: success； other:fail
 * @see    net_wifi_service_pause
**/
AIP_EXTERN HPR_INT32 aip_net_wifi_service_stop(HPR_VOID);


/*******************************************************************************
 *                                WiFi Sta Mode                                *
 *******************************************************************************/

/**
 * @fn       AIP_EXTERN HPR_INT32 aip_net_wifi_sta_open(HPR_VOID)
 * @brief    开启wifi模块 sta模式服务（即设备扫描其他热点进行连接模式）
 * @note     开启sta模式后，将尝试自动连接之前保存并选择连接的ap网络
 * @return   HPR_OK: success； other:fail
 **/
AIP_EXTERN HPR_INT32 aip_net_wifi_sta_open(HPR_VOID);

/**
 * @fn       AIP_EXTERN HPR_INT32 aip_net_wifi_sta_close(HPR_VOID)
 * @brief    关闭wifi模块 sta模式服务
 * @return   HPR_OK: success； other:fail
 **/
AIP_EXTERN HPR_INT32 aip_net_wifi_sta_close(HPR_VOID);

/**
 * @fn     AIP_EXTERN HPR_INT32 aip_net_wifi_scan_networks(HPR_VOID)
 * @brief  立即进行一次wifi ap网络扫描
 * @note   wifi服务开启后默认会进行周期性扫描更新ap网络状态
 * @return HPR_OK: success； other:fail
**/
AIP_EXTERN HPR_INT32 aip_net_wifi_scan_networks(HPR_VOID);

/**
 * @fn         AIP_EXTERN NET_WIFI_INFO_LIST* aip_net_wifi_get_networks_list(HPR_VOID)
 * @brief      返回当前wifi ap网络链表
 * @return     success: wifi ap任店链表, 返回的链表声明周期结束后，需要显示的调用net_wifi_release_wifi_info_list 释放
 *             fail   : NULL
**/
AIP_EXTERN NET_WIFI_INFO_LIST* aip_net_wifi_get_networks_list(HPR_VOID);

/**
 * @fn         AIP_EXTERN HPR_INT32 aip_net_wifi_release_wifi_info_list(NET_WIFI_INFO_LIST* pList)
 * @brief      释放wifi ap 网络链表
 * @param[in]  要释放的网络链表
 * @return     HPR_OK: success; other:fail
 * @see        aip_net_wifi_get_networks_list
**/
AIP_EXTERN HPR_INT32 aip_net_wifi_release_wifi_info_list(NET_WIFI_INFO_LIST* pList);

/**
 * @fn         AIP_EXTERN HPR_INT32 aip_net_wifi_connect_network(NET_WIFI_NETWORK_INFO_P pstNetworkInfo)
 * @brief      连接一个新的ap网络
 * @param[in]  pstNetworkInfo,  要连接的wifi信息
                允许为NULL，若该参数为NULL，将尝试以无密码方式连接网络或者以之前保存的密码进行链接(如果曾经设置过)
 * @note   要连接的ap网络必须存在scan后的列表或者被手动add过, 新添加一个网络也采用该接口，（添加后将会自动尝试连接）
 * @return HPR_OK: success； other:fail
**/
AIP_EXTERN HPR_INT32 aip_net_wifi_connect_network(NET_WIFI_NETWORK_INFO_P pstNetworkInfo);

/**
 * @fn         AIP_EXTERN HPR_INT32 aip_net_wifi_disconnect_network(HPR_VOID)
 * @brief      断开连接
 * @return HPR_OK: success； other:fail
**/
AIP_EXTERN HPR_INT32 aip_net_wifi_disconnect_network(HPR_VOID);

/**
 * @fn         AIP_EXTERN HPR_INT32 aip_net_wifi_clear_all_networks(HPR_VOID)
 * @brief      清空所有保存网络(断开已经链接的网络)
 * @return HPR_OK: success； other:fail
**/
AIP_EXTERN HPR_INT32 aip_net_wifi_clear_all_networks(HPR_VOID);

/**
 * @fn         AIP_EXTERN HPR_INT32 aip_net_wifi_clear_network(HPR_INT8 *szSsid)
 * @brief      清除指定wifi ssid的网络的保存配置
 * @param[in]  szSsid: 要忘记的ap网络的ssid(即一般意义的wifi名)，长度限制应该小于NET_WIFI_SSID_LEN
 * @return HPR_OK: success； other:fail
**/
AIP_EXTERN HPR_INT32 aip_net_wifi_clear_network(HPR_INT8 *szSsid);

/**
 * @fn         AIP_EXTERN HPR_INT32 aip_net_wifi_get_connect_status_info(NET_WIFI_STATUS_INFO_P pStatusInfo)
 * @brief      获取当前wifi链接状态
 * @param[out] pstStatusInfo: 当前链接状态以及连接的ap网络信息（如果处于已连接状态）
 * @return HPR_OK: success； other:fail
**/
AIP_EXTERN HPR_INT32 aip_net_wifi_get_connect_status_info(NET_WIFI_STATUS_INFO_P pstStatusInfo);

/**
 * @fn         AIP_EXTERN HPR_INT32 aip_net_wifi_sta_auto_test_set_test_ap_info(HPR_INT8 *szSsid, HPR_INT32 sdwLevel)
 * @brief      设置要测试的ap信息
 * @param[in]  szSsid: 测试ap网络的ssid(即一般意义的wifi名)，长度限制应该小于NET_WIFI_SSID_LEN
 * @param[in]  sdwLevel: wifi信号强度(未转换后的值，应当是个小于等级-45的值)
 * @return HPR_OK: success； other:fail
**/
AIP_EXTERN HPR_INT32 aip_net_wifi_sta_auto_test_set_test_ap_info(HPR_INT8 *szSsid, HPR_INT32 sdwLevel);

/**
 * @fn         AIP_EXTERN HPR_INT32 aip_net_wifi_sta_auto_test_start(HPR_INT8 *szSsid)
 * @brief      开始wifi自动测试
 * @return HPR_OK: success； other:fail
**/
AIP_EXTERN HPR_INT32 aip_net_wifi_sta_auto_test_start(HPR_VOID);

/**
 * @fn         AIP_EXTERN HPR_INT32 aip_net_wifi_sta_auto_test_get_result(HPR_INT8 *szSsid)
 * @brief      检测wifi 自动测试是否成功
 * @note       即是否找到了匹配的ssid，以及强度是否一致
 * @return HPR_OK: success； other:fail
**/
AIP_EXTERN HPR_INT32 aip_net_wifi_sta_auto_test_get_result(HPR_VOID);


/*******************************************************************************
 *                                WiFi AP Mode                                 *
 *******************************************************************************/

/**
 * @fn:		aip_net_wifi_ap_open
 * @brief:  开启wifi模块 ap模式服务 (即设备作为AP热点供其他终端连接). 该接口会手动设置默认IP,子网和网关, 并
 *          将配置模式设置成手动.
 * @param:
 *          HPR_VOID - NA
 * @return: AIP_EXTERN HPR_INT32 HPR_OK/HPR_ERROR
 * @author: xiaoxinyu
 */
AIP_EXTERN HPR_INT32 aip_net_wifi_ap_open(HPR_VOID);

/**
 * @fn:		aip_net_wifi_ap_close
 * @brief:  关闭wifi模块 ap模式服务
 * @param:
 *          HPR_VOID - NA
 * @return: AIP_EXTERN HPR_INT32
 * @author: xiaoxinyu
 */
AIP_EXTERN HPR_INT32 aip_net_wifi_ap_close(HPR_VOID);

/**
 * @fn:		aip_net_wifi_set_ap_config
 *          设置WiFi AP模式热点参数
 * @param:
 *          NET_WIFI_NETWORK_INFO_T *pstApConfig - 热点配置参数
 * @return: AIP_EXTERN HPR_INT32 HPR_OK/HPR_ERROR
 * @author: xiaoxinyu
 */
AIP_EXTERN HPR_INT32 aip_net_wifi_set_ap_config(NET_WIFI_NETWORK_INFO_T *pstApConfig);

/**
 * @fn:		aip_net_wifi_get_ap_config
 *          获取WiFi AP模式热点参数
 * @param:
 *          NET_WIFI_NETWORK_INFO_T *pstApConfig - 热点配置参数
 * @return: AIP_EXTERN HPR_INT32 HPR_OK/HPR_ERROR
 * @author: xiaoxinyu
 */
AIP_EXTERN HPR_INT32 aip_net_wifi_get_ap_config(NET_WIFI_NETWORK_INFO_T *pstApConfig);

/**
 * @fn:		aip_net_wifi_get_ap_status
 *          获取当前AP状态
 * @param:
 *          HPR_VOID - NA
 * @return: AIP_EXTERN NET_WIFI_AP_STATUS_E AP状态值
 * @author: xiaoxinyu
 */
AIP_EXTERN NET_WIFI_AP_STATUS_E aip_net_wifi_get_ap_status(HPR_VOID);

/**
 * @fn:		aip_net_wifi_ap_get_err_code_info
 *          获取WiFi AP模式错误码对应的描述信息
 * @param:
 *          NET_WIFI_AP_ERR_CODE eErrCode - 错误码
 * @return: AIP_EXTERN const HPR_INT8* 字符描述
 * @author: xiaoxinyu
 */
AIP_EXTERN const HPR_INT8* aip_net_wifi_ap_get_err_code_info(NET_WIFI_AP_ERR_CODE eErrCode);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif //__AIP_NET_WIFI_H__ end
