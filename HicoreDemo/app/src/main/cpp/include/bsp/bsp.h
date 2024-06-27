#ifndef __LIBBSP_H__
#define __LIBBSP_H__
#ifdef __cplusplus
extern "C"{
#endif
/*--------------------------------------------------------------------------------------------------------------------
--------------------------------------------------macro definition for AIP A2S/A2-------------------------------------
--------------------------------------------------------------------------------------------------------------------*/
#define BSP_DEV_MCU_USB_NAME  "/dev/bsp_usb"

/*--------------------------------------------------------------------------------------------------------------------
--------------------------------------------------for ERR CODE--------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------*/
#define ERR_INPUT -1
#define ERR_CONNECT    -2
#define ERR_SEND       -3
#define ERR_RECV       -4
#define ERR_NET_NO_PREPARE -5
#define ERR_TIMEOUT -6
#define ERR_APK_NO_SIGN -7

/*--------------------------------------------------------------------------------------------------------------------
---------------------------------------------------for device---------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------*/
#define EMMC_HIK_PARTITION	"/dev/block/platform/fe310000.sdhci/by-name/hik"

/*--------------------------------------------------------------------------------------------------------------------
---------------------------------------------------for app---------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------*/
#define PATH_SIZE 128
#define PACKAGE_NAME_SIZE 128
#define PACKAGES_NUM_MAX 10

#define WIFI_SSID_SIZE 128
#define WIFI_PSW_SIZE 128
#define WIFI_BSSID_SIZE 20

#define IPV4_SIZE 20
#define IPV6_SIZE 40
#define MAC_SIZE 40

#define APN_SIZE 128
#define TIME_SIZE 128
#define SIZE_32 32
/**
 * desc : reboot device
 * ret  : 0: success
 *       -1: fail
 */
int bsp_reboot_device(char *);

/**
 * desc : write reset flag to system, need call reboot or power-off-on to make effect
 * ret  : 0: success
 *       -1: fail
 * other: support R1/R2/R3/A2/A2S
 */
int bsp_reset_device_write_misc(void);
int bsp_reset_device_write_cache(void);

/**
 * desc : call write reset flag func and reboot device
 * ret  : 0: success
 *       -1: fail
 *
 * through = write + reboot
 */
int bsp_reset_device_through_misc(void);
int bsp_reset_device_through_cache(void);

/**
 * desc : get the version and build date of bsp resources
 * ret  : 0: success
 *       -1: fail
 */
int Bsp_GetVersion(char* sVersion, int iVerBufLen, char* sTime, int iTimeBufLen);

/**
 * desc : get the cpu temperature
 * ret  : 0: success
 *       -1: fail
 */
int bsp_get_cpu_temp(int *tmp);
/*--------------------------------------------------------------------------------------------------------------------
-----------------------------------------for bsp modules(wifi\4G\ethernet\blutooth\settings...)-----------------------
--------------------------------------------------------------------------------------------------------------------*/
#define WIFI_INFO_ARRAY_SIZE 30

//wifi加密方式
typedef enum {
    SECURITY_TYPE_OPEN = 0,     //无密码
    SECURITY_TYPE_WEP,          //WEP加密
    SECURITY_TYPE_WPA,          //WPA加密
    SECURITY_TYPE_WPA3,         //WPA3加密
}BSP_CORE_WIFI_SECURITY_TYPE;

/*wifi开关*/
typedef enum {
    WIFI_CLOSE = 0,     //关闭wifi
    WIFI_OPEN,          //打开wifi
}BSP_CORE_WIFI_ENABLE;

/*移动网络流量开关*/
typedef enum {
    TELE_CLOSE = 0,     //关闭流量
    TELE_OPEN,          //打开流量
}BSP_CORE_TELE_ENABLE;


#define SUPPORT_TELE_NETTYPE 1 //提供给应用使用，是否支持获取网络类型，AIP同事需要根据这个同步版本（防止AIP更新，但libbsp没更新的项目）
/*移动网络拨号类型*/
typedef enum {
    TELE_TYPE_UNKNOWN = 0,     //未知
   	TELE_TYPE_2G = 2,     //2G
   	TELE_TYPE_3G = 3,     //3G
   	TELE_TYPE_4G = 4,     //4G
   	TELE_TYPE_5G = 5,     //5G
}BSP_CORE_TELE_NETTYPE;


/*wifi状态*/
typedef enum {
    WIFI_STATE_DISABLING = 0,   //关闭中
    WIFI_STATE_DISABLED,        //已关闭1
    WIFI_STATE_ENABLING,        //打开中2
    WIFI_STATE_ENABLED,         //已打开3
    WIFI_STATE_UNKNOWN,         //未知错误无法连接4
    WIFI_STATE_CONNECTED,       //已连接5
    WIFI_STATE_CONNECTING,      //连接中6
    WIFI_STATE_DISCONNECTING,   //断开中7
    WIFI_STATE_DISCONNECTED,    //已断开8
}BSP_CORE_WIFI_STATUS;

/*wifi ap状态*/
typedef enum {
    WIFI_AP_STATE_DISABLING = 0,   //关闭中
    WIFI_AP_STATE_DISABLED,        //已关闭1
    WIFI_AP_STATE_ENABLING,        //打开中2
    WIFI_AP_STATE_ENABLED,         //已打开3
    WIFI_AP_STATE_FAILED,         //打开异常4
}BSP_CORE_WIFI_AP_STATUS;

/*ble状态*/
typedef enum {
    BLE_STATE_DISABLED = 0,   //已关闭
    BLE_STATE_ENABLED,        //已打开1
    BLE_STATE_CONNECTED,      //已连接2
    BLE_STATE_DISCONNECTED,   //已断开3
}BSP_CORE_BLE_STATUS;

/*GPS状态*/
typedef enum {
    GPS_STATE_OUT_OF_SERVICE = 0,      //服务区外
    GPS_STATE_TEMPORARILY_UNAVAILABLE, //暂停服务
    GPS_STATE_AVAILABLE,      //可用
    GPS_STATE_CLOSE,   //已关闭
    GPS_STATE_OPEN,   //已打开
}BSP_CORE_GPS_STATUS;

typedef enum {
    STATIC = 0,            //静态
    DHCP,                  //动态
    STATELESS,             //路由公告 仅用于ipv6
    STATELESS_DHCP,        //无状态dhcp
}BSP_CORE_SET_MODE;

/*APK验签开关*/
typedef enum {
    APK_SIGN_CHECK_CLOSE = 0,     //关闭APK验签功能
    APK_SIGN_CHECK_OPEN,          //打开APK验签功能
}BSP_CORE_APP_SIGN_CHECK_STATUS;

struct bsp_net_wifi_config{
    char ssid[WIFI_SSID_SIZE]; /* wifi ssid */
    char psw[WIFI_PSW_SIZE];  /* wifi password */
    int security;   /* wifi security type :BSP_CORE_WIFI_SECURITY_TYPE*/
};

struct bsp_net_wifi_scan_data{
    char ssid[WIFI_SSID_SIZE];    /* SSID */
    char bssid[WIFI_BSSID_SIZE];    /* BSSID */
    int  level;        /* wifi level */
    int  security;     /* wifi security type :BSP_CORE_WIFI_SECURITY_TYPE*/
};

struct bsp_net_wifi_info{
    char ssid[WIFI_SSID_SIZE];    /* SSID */
    char bssid[WIFI_BSSID_SIZE];    /* BSSID */
    int level;        /* wifi level */
    char ip[IPV6_SIZE];       /* wifi ip */
    char mac[MAC_SIZE];      /* MAC address */
    int id;           /* ap id */
};

struct bsp_net_tele_apn_config{
    char APNname[APN_SIZE];  /* APN description */
    char APN[APN_SIZE];      /* APN type */
    char APNuser[APN_SIZE];  /* APN user */
    char APNpsw[APN_SIZE];   /* APN password */
};

struct bsp_net_data{
    int mode;          /*BSP_CORE_SET_MODE */
    char phyname[8]; /* phy name */
    char ip[IPV6_SIZE];      /* phy ip */
    char gateway[IPV6_SIZE]; /* phy gateway */
    char netmask[IPV6_SIZE]; /* phy netmask */
    char dns1[IPV6_SIZE];    /* phy dns1 */
    char dns2[IPV6_SIZE];    /* phy dns2 */
    char mac[MAC_SIZE];     /* phy mac */
};

struct bsp_net_eth_config{
    int mode;          /*BSP_CORE_SET_MODE */
    char ip[IPV6_SIZE];      /* phy ip */
    char gateway[IPV6_SIZE]; /* phy gateway */
    int netmask; /* phy netmask */
    char dns1[IPV6_SIZE];    /* phy dns1 */
    char dns2[IPV6_SIZE];    /* phy dns2 */
};

struct bsp_net_ipv6_ip_node
{
    char ip[IPV6_SIZE];      /* phy ip */
    struct bsp_net_ipv6_ip_node *next;
};

struct bsp_net_ipv6_data{
    int mode;          /*BSP_CORE_SET_MODE */
    char phyname[8];  /* phy name */
    struct bsp_net_ipv6_ip_node *ip_head;      /* phy ip */
    char gateway[IPV6_SIZE]; /* phy gateway */
    int prefix;       /* ipv6 addr prefix length */
    char dns1[IPV6_SIZE];    /* phy dns1 */
    char dns2[IPV6_SIZE];    /* phy dns2 */
    char mac[MAC_SIZE];     /* phy mac */
};

struct bsp_net_ipv6_config{
    int mode;          /*BSP_CORE_SET_MODE */
    char phyname[8];  /* phy name */
    char ip[IPV6_SIZE];      /* phy ip */
    char gateway[IPV6_SIZE]; /* phy gateway */
    int prefix;       /* ipv6 addr prefix length */
    char dns1[IPV6_SIZE];    /* phy dns1 */
    char dns2[IPV6_SIZE];    /* phy dns2 */
};

struct bsp_gps_data{
    double longitude;//经度
    double latitude;//纬度
    double accuracy;//水平精度因子
    double speed;//对地速度
    double altitude;//海拔
    int usedsatellite_count;//用于定位卫星数
    int satellite_count;//可见卫星数
    int snr[32];//信噪比
};

struct bsp_setting_time_data{
    char time[TIME_SIZE];      /* Current Time yyyy-MM-dd HH:mm:ss*/
    char timezone[TIME_SIZE];  /* timezone id read Android_timezone_id.txt*/
    int timezone_offset; /* timezone offset 单位秒*/
    int DST_offset;      /* DST offset 单位秒*/
};

struct bsp_app_info{
    int pid;                     // 运行进程号(未运行返回-1)
    unsigned int app_size;       // 应用大小，单位KB
    unsigned int data_size;      // 用户数据
    unsigned int cache_size;     // 缓存
    unsigned int vmrss_size;     // 内存
    char pack_name[PACKAGE_NAME_SIZE];			 // app包名
};

struct bsp_core_setting_callback {
    void (*time_info_cb)(struct bsp_setting_time_data time_data);
    void (*language_info_cb)(char *language);//预留回调暂未使用，目前设置项由apk设置
};

struct bsp_core_wifi_callback {
    void (*wifi_info_cb)(struct bsp_net_wifi_info info_data);
    void (*wifi_scan_cb)(struct bsp_net_wifi_scan_data scan_data[]);
    void (*wifi_status_cb)(int status);//BSP_CORE_WIFI_STATUS
    void (*wifi_ap_status_cb)(int status);//BSP_CORE_WIFI_AP_STATUS
};

struct bsp_core_net_callback {
    /*usb0  0:disconnect 1:connect
      eth0  0:static 1:dhcp
      wlan0 0:static 1:dhcp
    */
    void (*netdata_cb)(char *name, int mode);                                //网卡状态变化回调
    void (*net_eth_config_cb)(struct bsp_net_eth_config eth_config);         //以太网ui参数配置回调
    void (*net_ipv6_config_cb)(struct bsp_net_ipv6_config net_ipv6_config);  // ipv6网络ui参数配置回调，包括usb0, eth0, wlan0, 通过phyname成员选择
};

struct bsp_core_tele_callback {
    void (*tele_data_enable)(int enable);//4g流量开关状态回调
    void (*tele_sim_ready)(int ready);//4g流量开关状态回调
    void (*tele_active_apn)(struct bsp_net_tele_apn_config apn_config);//当前APN
    void (*tele_signal_level)(int level);//4g信号等级
    void (*tele_net_type)(BSP_CORE_TELE_NETTYPE type);//拨号类型回调
};

struct bsp_core_ble_callback {
    void (*ble_recv_data)(char* data, int length);//接收蓝牙数据回调
    void (*ble_status_cb)(int enable);//蓝牙开关状态
};

struct bsp_core_wifi_ap_callback {
    void (*wifi_ap_status_cb)(int status);//BSP_CORE_WIFI_AP_STATUS
};

struct bsp_core_gps_callback {
    void (*gps_status_cb)(int status);//BSP_CORE_GPS_STATUS
    void (*gps_data_cb)(struct bsp_gps_data gps_data);//BSP_CORE_GPS_DATA
};

struct bsp_core_app_callback {
    void (*app_package_name_cb)(int install_result, char *package_name);//APP包名回调
    void (*app_list_packages_cb)(int app_num, char list_packages[][PACKAGE_NAME_SIZE]);//APP列表回调
    void (*app_info_cb)(struct bsp_app_info app_info);//app信息回调
};

/*================================================ init ================================================*/
/**
 * desc : 向bsp.so服务注册监听回调,分模块功能注册
 */
void bsp_core_register_setting_callback(struct bsp_core_setting_callback *cb);//设置项
void bsp_core_register_wifi_callback(struct bsp_core_wifi_callback *cb);//wifi信息
void bsp_core_register_net_callback(struct bsp_core_net_callback *cb);//网络状态变化
void bsp_core_register_tele_callback(struct bsp_core_tele_callback *cb);//移动网络状态
void bsp_core_register_ble_callback(struct bsp_core_ble_callback *cb);//蓝牙数据接收
void bsp_core_register_wifi_ap_callback(struct bsp_core_wifi_ap_callback *cb);//wifi ap信息回调
void bsp_core_register_gps_callback(struct bsp_core_gps_callback *cb);//gps信息回调
void bsp_core_register_app_callback(struct bsp_core_app_callback *cb);//app信息回调

/**
 * desc : 初始化bsp.so中接收服务
 * block function has no ret, while 1 to accept a socket in this function
 */
int bsp_core_server_init();

/**
 * desc : 检查安卓通信服务是否启动，启动完成后才能够正常接受设置接口调用
 */
int bsp_core_check_server_isok();

/**
 * desc : 升级4G模组固件，nl668模块传入.zip包路径。 l716传入.bin路径
 */
int bsp_core_net_tele_update(char* path);

/*================================================ net ================================================*/
/**
 * desc : 开关wifi
 * enable ： BSP_CORE_WIFI_ENABLE
 * ret : ERR CODE
 */
int bsp_core_net_wifi_enable(int enable);
/**
 * desc : 触发wifi扫描
 * ret : ERR CODE
 */
int bsp_core_net_wifi_scan();
/**
 * desc : 连接wifi
 * *wifi_config ： struct bsp_net_wifi_config
 * ret : ERR CODE
 */
int bsp_core_net_wifi_connect(struct bsp_net_wifi_config *wifi_config);
/**
 * desc : 断开wifi
 * ret : ERR CODE
 */
int bsp_core_net_wifi_disconnect();
/**
 * desc : 删除指定ssid的wifi配置
 * *ssid ： char
 * ret : ERR CODE
 */
int bsp_core_net_wifi_remove(char *ssid);
/**
 * desc : 获取已连接的wifi信息, 通过wifi_info_cb回调
 * ret : ERR CODE
 */
int bsp_core_net_wifi_wifiinfo();

/**
 * desc : 获取wifi开关状态
 * ret : ERR CODE
 */
int bsp_core_net_wifi_get_status();

/**
 * desc : 获取流量开关状态
 * ret : ERR CODE
 */
int bsp_core_net_tele_get_status();

/**
 * desc : 移动网络流量开关
 * enable ： BSP_CORE_TELE_ENABLE
 * ret : ERR CODE
 */
int bsp_core_net_tele_enable(int enable);

/**
 * desc : 增加移动网络apn配置
 * *apn_config ： struct bsp_net_tele_apn_config
 * ret : ERR CODE
 */
int bsp_core_net_tele_addapn(struct bsp_net_tele_apn_config *apn_config);

/**
 * desc : 删除移动网络apn配置
 * *name ： char
 * ret : ERR CODE
 */
int bsp_core_net_tele_deleteapn(char *name);

/**
 * desc : 选择apn
 * *name ： char
 * ret : ERR CODE
 */
int bsp_core_net_tele_selectapn(char *name);

/**
 * desc : 查看当前apn
 * *name ： char
 * ret : ERR CODE
 */
int bsp_core_net_tele_getapn();

/**
 * desc : 查看信号强度
 * *name ： char
 * ret : ERR CODE
 */
int bsp_core_net_tele_level();

/**
 * desc : 查看当前移动网络类型
 * 
 * ret : ERR CODE
 */
int bsp_core_net_tele_type();


/**
 * desc : 获取4G网卡名称
 * *name ： char 网卡名称接收buff
 *  size : int 网卡名称存储buff大小至少为5
 *  ret : ERR CODE
 */
int bsp_core_net_tele_get_4gphyname(char *name, int size);

/**
 * desc : 检查sim卡状态
 * ret : 未就绪0 已就绪1
 * SIM卡提供商代码 46000 46002移动  46001中国联通  46003电信
 */
int bsp_core_net_tele_sim_check();

/**
 * desc : 设置指定网卡的信息
 * *bsp_data ： struct bsp_net_data
 * ret : ERR CODE
 */
int bsp_core_net_set_para(struct bsp_net_data *bsp_data);

/**
 * desc : 获取指定网卡的信息
 * *phyname ： char , need phyname "eth0" "eth1" "wlan0"...
 * ret : ERR CODE
 */
int bsp_core_net_get_para(struct bsp_net_data *bsp_data);

/**
 * desc : 设置指定网卡的ipv6信息
 * *bsp_data ： struct 
 
 * note ：通过bsp_net_ipv6_config中phyname成员指定网卡
 * ret : ERR CODE
 */
int bsp_core_net_ipv6_set_para(struct bsp_net_ipv6_data *bsp_data);

/**
 * desc : 获取指定网卡的ipv6信息
 * *bsp_data ： struct bsp_net_ipv6_data
 * note ：通过bsp_net_ipv6_data中phyname成员指定网卡
 * ret : ERR CODE
 */
int bsp_core_net_ipv6_get_para(struct bsp_net_ipv6_data *bsp_data);

/*================================================ settings ================================================*/
/**
 * desc : 设置时区
 * *id ： char, support : read Android_timezone_id.txt
 * ret : ERR CODE
 */
int bsp_core_setting_timezone(char *id);

/**
 * desc : 设置系统语言
 * *lang ： char, support :"zh_CN" "zh_TW" "en_US"
 *
 * ret : ERR CODE
 */
int bsp_core_setting_language(char *lang);

/**
 * desc : 触发当前时间信息回调
 * 通过time_info_cb回调
 * ret : ERR CODE
 */
int bsp_core_setting_gettime();

/**
 * desc : 重启设备
 * reason : 重启原因
 * ret : ERR CODE
 */
int bsp_core_setting_reboot(char* reason);

/**
 * desc : OTA升级
 * path : OTA全量升级包update.zip路径
 * ret : ERR CODE
 */
int bsp_core_setting_otaupdate(char* path);

/*================================================ ble ================================================*/
/**
 * desc : 开启关闭蓝牙
 * 0 close  1 open
 * ret : ERR CODE
 */
int bsp_core_ble_set_ble_enable(int enable);

/**
 * desc : 设置蓝牙广播私有数据
 * id : int SIG联盟分配的厂商id 如0xAABB
 * manufacture : int* 私有数据，int类型数组，如 {0x30, 0xFF, 0X31, 0XAA}
 * length ： int 私有数据数组长度
 * ret : ERR CODE
 */
int bsp_core_ble_set_manufacture(int id, char* manufacture, int length);

/**
 * desc : 设置蓝牙名称
 * *blename ： char
 * ret : ERR CODE
 */
int bsp_core_ble_set_ble_name(char *blename);

/**
 * desc : 开启关闭广播
 * 0 close  1 open
 * ret : ERR CODE
 */
int bsp_core_ble_set_advertising(int enable);

/**
 * desc : 发送数据，接收数据通过bsp_core_callback中ble_recv_data数据回调
 * data : int* 传输数据，int类型数组，如 {0x30, 0xFF, 0X31, 0XAA}
 * length ： int 传输数据数组长度
 * ret : ERR CODE
 */
int bsp_core_ble_send_data(char* data, int length);

/**
 * desc : 获取蓝牙开关状态
 * ret : ERR CODE
 */
int bsp_core_ble_get_status();

/**
 * desc : 断开ble蓝牙
 * ret : ERR CODE
 */
int bsp_core_ble_disconnect();

/*================================================ wifi AP ================================================*/
/**
 * desc : wifi热点开关
 * ret : ERR CODE
 */
int bsp_core_net_wifi_ap_enable(int enable);

/**
 * desc : 设置ap的信息，包括名称、密码、加密类型
 * *wifi_config ： struct bsp_net_wifi_config
 * ret : ERR CODE
 */
int bsp_core_net_wifi_set_ap_config(struct bsp_net_wifi_config *wifi_config);

/**
 * desc : 获取ap的开关状态
 * ret : ERR CODE
 */
int bsp_core_net_wifi_get_ap_status();

/*================================================ GPS ================================================*/
/**
 * desc : GPS开关
 * ret : ERR CODE
 */
int bsp_core_gps_enable(int enable);

/**
 * desc : 获取gps状态
 * ret : ERR CODE
 */
int bsp_core_gps_get_status();

/**
 * desc : 获取gps信息
 * ret : ERR CODE
 */
int bsp_core_gps_get_data();

/**
 * desc : 设置gps
 * mode : "gps" "network"
 * time_ms : 位置更新之间的最小时间间隔(以毫秒为单位)
 * distance_m : 位置更新之间的最小距离(以米为单位)
 * ret : ERR CODE
 */
int bsp_core_gps_setting(char* mode, long time_ms, float distance_m);

/**
 * desc : 检查开机动画是否启动完成，启动完成后才能启动第三方APP
 */
int bsp_core_check_bootanim_isok();


/*--------------------------------------------------------------------------------------------------------------------
--------------------------------------------------macro definition for old A2-------------------------------------
--------------------------------------------------------------------------------------------------------------------*/


struct bsp_ethernet_data{
    int mode;
    int phy;
    char ip[128];
    char gateway[128];
    char netmask[128];
    char dns1[128];
    char dns2[128];
};

typedef enum {
    BSP_CORE_ETHERNET_ETH0 = 0,
    BSP_CORE_ETHERNET_ETH1,
}BSP_CORE_ETHERNET_NUM;

typedef enum {
    BSP_CORE_ETHERNET_LINK_STAT = 0,
    BSP_CORE_ETHERNET_SPEED_STAT,
    BSP_CORE_ETHERNET_DHCP_STAT,
}BSP_CORE_ETHERNET_STAT_TYPE;

typedef enum {
    BSP_CORE_ETHERNET_LINK_DOWN = 0,
    BSP_CORE_ETHERNET_LINK_UP,
    BSP_CORE_ETHERNET_SPEED_10M,
    BSP_CORE_ETHERNET_SPEED_100M,
    BSP_CORE_ETHERNET_SPEED_1000M,
    BSP_CORE_ETHERNET_DHCP_ONGOING,
    BSP_CORE_ETHERNET_DHCP_END,
}BSP_CORE_ETHERNET_STAT_VALUE;


int bsp_core_ethernet_set_para(struct bsp_ethernet_data *bsp_data);
int bsp_core_ethernet_get_para(struct bsp_ethernet_data *bsp_data);
int bsp_core_ethernet_get_stat (int eth_num, int stat_type, int *stat_value);
int bsp_core_ethernet_set_single_para (struct bsp_ethernet_data *bsp_data);
int bsp_core_ethernet_get_link_stat(int eth_num, int *value);
int bsp_core_systemui_set_icon(int index, char *icon_name, char *icon_path);
int bsp_core_systemui_cancel_icon(int index,char *icon_name);

#define ERR_NO_ADDRESS -1
#define ERR_CONNECT    -2
#define ERR_SEND       -3
#define ERR_RECV       -4
#define ERR_NETMASK    -5
#define ERR_NO_IP      -6
#define ERR_POINTER    -7


/*================================================ APP ================================================*/

/**
 * desc : APP安装
 * app_path : 安装的app路径
 * package_name : 安装完成后返回app包名称
 * ret : ERR CODE
 */
int bsp_core_app_install(char *app_path, char *package_name);

/**
 * desc : APP卸载
 * package_name : app包名称
 * ret : ERR CODE
 */
int bsp_core_app_uninstall(char* package_name);

/**
 * desc : 启动APP
 * package_name : app包名称
 * ret : ERR CODE
 */
int bsp_core_app_start(char *package_name);

/**
 * desc : 关闭APP
 * package_name : app包名称
 * ret : ERR CODE
 */
int bsp_core_app_stop(char *package_name);

/**
 * desc : 获取APP信息
 * package_name : app包名称
 * stRuntime : struct bsp_app_info
 * ret : ERR CODE
 */
int bsp_core_app_info_get(char *package_name, struct bsp_app_info *app_info);

/**
 * desc : 获取APP信息
 * package_name : app包名称
 * 此接口和bsp_core_app_info_get只能同时用一个， 此接口依赖回调
 * ret : ERR CODE
 */
int bsp_core_app_info_get_new(char *package_name);


/**
 * desc : 获取APP列表
 * app_num: 已安装的第三方app数量
 * list_packages: 获取所有第三方app包名称
 * ret : ERR CODE
 */
int bsp_core_app_list_get(int *app_num, char list_packages[][PACKAGE_NAME_SIZE]);

/**
 * desc : 获取APP列表
 * ret : ERR CODE
 */
int bsp_core_app_list_get_new();

/**
 * desc : APK验签开关
 * enable: 0关闭 1打开
 * ret : ERR CODE
 */
int bsp_core_app_sign_check_enable(int enable);

/**
 * desc : 设置默认launcher APK
 * package_name: com.hik.acs.recognition 或 com.android.launcher3
 * ret : ERR CODE
 */
int bsp_core_default_launcher_set(char *package_name);

/*================================================ requires module version ================================================*/
struct bsp_requires_module{
    char name[128];
    char version[32];
    char note[128];
};

/**
 * desc : 获取依赖模块版本信息
 * list : 获取依赖模块信息列表
 * size : 依赖模块数组大小
 * ret : ERR CODE
 */
int bsp_get_requires_list(struct bsp_requires_module *list, int size);

#ifdef __cplusplus
}
#endif
#endif
