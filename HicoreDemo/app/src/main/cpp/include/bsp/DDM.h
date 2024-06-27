/**
 * @File: DDM.h
 * @Module: DDM头文件
 * @Author: zhengtao6@hikvision.com.cn
 * @Created: 2021年3月31日
 *
 * @Description: DDM头文件，对内被DDM实现代码引用，对外被上层应用程序应用
 *
 * @Note : DDM V2.0的头文件版本采用如下规则进行管理：
 *         主版本号.次版本号.修订号：X.Y.R
 *         主版本号(X):当进行重大框架性升级后，递增主版本号，次版本号和修订号归零；
 *         次版本号(Y):当对API进行了不能向前兼容的修改或删除后（如删除子模块或修改IOCTL命令），递增次版本号，修订号归零；
 *         修订号  (R):当对API进行了能向前兼容的修改或新增后（如新增子模块或新增IOCTL命令），递增修订号
 *
 *         原则上，DDM V2.0的头文件只允许新增接口，不允许删除或修改已有的接口。
 *
 * @Usage:
 *
 */

#ifndef INCLUDE_DDM_H_
#define INCLUDE_DDM_H_

#define DDM_HEADER_VERSION                  2
#define DDM_HEADER_PATCHLEVEL               1
#define DDM_HEADER_SUBLEVEL                 2

#define DDM_VERSION(v,p,s)                  (((v) << 16) + ((p) << 8) + (s))

/****************************** 通用宏定义 ******************************/
//电源管理模式
typedef enum
{
    DDM_PM_NORMAL= 0,                   // 正常工作模式
    DDM_PM_LOWPOWER,                    // 低功耗模式
    DDM_PM_POWEROFF,                    // 关闭电源模式
    DDM_PM_MAX,                         // 最大值
} DDM_PmMode;

/*********************************************************************
 ******************************* DDM_ble ******************************
 *********************************************************************/

/******************************* 宏定义 ******************************/
#define DDM_DEV_TTY_BLE_NAME            "/dev/DDM/tty_ble"
#define DDM_DEV_BLE_NAME                "/dev/DDM/ble"
#define DDM_IOC_BLE_MNUM                'B'
//下载蓝牙固件，仅限SPI接口蓝牙使用
#define DDM_IOC_BLE_UPDATE_FW           _IOW(DDM_IOC_BLE_MNUM, 0, DDM_bleSetFwArgs)
// 清除接收缓存，仅限spi接口蓝牙使用
#define DDM_IOC_BLE_CLEAR_RXBUFFER      _IO(DDM_IOC_BLE_MNUM, 1)
// 蓝牙异常复位接口（预留接口，暂不使用）
#define DDM_IOC_BLE_RESET_CHIP          _IO(DDM_IOC_BLE_MNUM, 2)
// 蓝牙固件升级前时序环境准备（包括上电复位等逻辑）仅串口接口蓝牙模块调用
#define DDM_IOC_BLE_PREPARE_UPDATE      _IO(DDM_IOC_BLE_MNUM, 3)
// 蓝牙模块电源管理模式设置
#define DDM_IOC_BLE_SET_POWER           _IOW(DDM_IOC_BLE_MNUM, 4, DDM_PmMode)
// 获取蓝牙接口类型
#define DDM_IOC_BLE_GET_INFTYPE         _IOR(DDM_IOC_BLE_MNUM, 5, DDM_bleGetInftype)


/******************************* 数据结构 ******************************/
// 固件升级参数
typedef struct tagDDM_bleSetFwArgs
{
    char fw_path[100];                  // 固件路径
    int reserve;                        // 保留
} DDM_bleSetFwArgs;

// 蓝牙接口类型
typedef enum
{
    DDM_BLE_INFTYPE_SPI= 0,             // SPI接口类型
    DDM_BLE_INFTYPE_TTY,                // 串口接口类型
    DDM_BLE_INFTYPE_MAX,                // 最大值 必须为最后一个
} DDM_bleGetInftype;

/*********************************************************************
 ******************************* DDM_display ******************************
 *********************************************************************/

/******************************* 宏定义 ******************************/
#define DDM_DEV_DISPLAY_NAME            "/dev/DDM/display"
#define DDM_IOC_DISPLAY_MNUM            'D'
//设置显示屏背光亮度,有效值1-100
#define DDM_IOC_DISPLAY_SET_BRIGHTNESS  _IOW(DDM_IOC_DISPLAY_MNUM, 0, unsigned int)
//开关显示屏电源
#define DDM_IOC_DISPLAY_SET_POWER       _IOW(DDM_IOC_DISPLAY_MNUM, 1, DDM_PmMode)
//获取显示屏ID
#define DDM_IOC_DISPLAY_GET_LCDID       _IOR(DDM_IOC_DISPLAY_MNUM, 2, int)
/******************************* 数据结构 ******************************/

/*********************************************************************
 ******************************* DDM_exio ******************************
 *********************************************************************/
/******************************* 宏定义 ******************************/
#define DDM_DEV_EXIO_NAME               "/dev/DDM/exio"
#define DDM_IOC_EXIO_MNUM               'E'
//获取EXIO通道数
#define DDM_IOC_EXIO_GET_NUM            _IOR(DDM_IOC_EXIO_MNUM, 0, DDM_exioGetNum)
//获取GPIO类输入通道状态
#define DDM_IOC_EXIO_GET_INPUT          _IOR(DDM_IOC_EXIO_MNUM, 1, unsigned int)
//设置GPIO类输出通道状态
#define DDM_IOC_EXIO_SET_OUTPUT         _IOW(DDM_IOC_EXIO_MNUM, 2, DDM_exioSetValue)
//设置继电器输出通道状态
#define DDM_IOC_EXIO_SET_RELAY          _IOW(DDM_IOC_EXIO_MNUM, 3, DDM_exioSetValue)
//获取防拆状态
#define DDM_IOC_EXIO_GET_TAMPER         _IOR(DDM_IOC_EXIO_MNUM, 4, unsigned int)
//获取报警输入状态
#define DDM_IOC_EXIO_GET_ALARM          _IOR(DDM_IOC_EXIO_MNUM, 5, DDM_exioGetAlarm)
//设置报警输出状态
#define DDM_IOC_EXIO_SET_ALARM          _IOW(DDM_IOC_EXIO_MNUM, 6, DDM_exioSetAlarm)
//获取门磁输入状态
#define DDM_IOC_EXIO_GET_DOORSENSOR     _IOR(DDM_IOC_EXIO_MNUM, 7, DDM_exioGetDoorSensor)
//设置门锁输出状态
#define DDM_IOC_EXIO_SET_DOORSENSOR     _IOW(DDM_IOC_EXIO_MNUM, 8, DDM_exioSetDoorSensor)
//获取开门按钮输入状态
#define DDM_IOC_EXIO_GET_DOORKEY        _IOR(DDM_IOC_EXIO_MNUM, 9, DDM_exioGetDoorKey)
//设置钱箱输出状态
#define DDM_IOC_EXIO_SET_CASHBOX        _IOW(DDM_IOC_EXIO_MNUM, 10, DDM_exioSetCashBox)
//获取消防输入状态
#define DDM_IOC_EXIO_GET_FIREFIGHTING   _IOW(DDM_IOC_EXIO_MNUM, 11, DDM_exioGetFireFighting)
/******************************* 数据结构 ******************************/
typedef struct
{
    unsigned int innum;                 // GPIO类输入通道数量
    unsigned int outnum;                // GPIO类输出通道数量
    unsigned int relaynum;              // 继电器输出通道数量
    unsigned int reserve[5];            // 保留
} DDM_exioGetNum;

typedef struct
{
    unsigned char ch;                   // 设置的通道编号
    unsigned char value;                // 设置的值
    unsigned char reserve[2];           // 保留
} DDM_exioSetValue;

typedef struct
{
    unsigned char index;                // 索引编号,从0开始,默认保持与丝印对应,即0对应报警输入1的io
    unsigned char level;                // 索引编号对应io的电平值
} DDM_exioGetLevel;

typedef struct
{
    unsigned char index;                // 索引编号,从0开始,默认保持与丝印对应,即0对应报警输出1的io
    unsigned char level;                // 索引编号对应io的电平值
    unsigned char flag;                 // 0表示忽略对应index操作,1表示设置对应index的电平值为level
    unsigned char reserve[1];           // 预留
} DDM_exioSetLevel;

typedef struct {
    int number;                         // 硬件层面指出的最大输入路数,bsp上传上来的
    DDM_exioGetLevel in[16];            // 最大支持16路输入
} DDM_exioGetAlarm;

typedef struct {
    int number;                         // 硬件层面指出的最大输出路数,bsp上传上来的
    DDM_exioSetLevel out[16];           // 最大支持16路报警输出
} DDM_exioSetAlarm;

typedef struct {
    int number;                         // 硬件层面指出的最大输入路数,bsp上传上来的
    DDM_exioGetLevel in[4];             // 最大支持4路输入
} DDM_exioGetDoorSensor;

typedef struct {
    int number;                         // 硬件层面指出的最大输出路数,bsp上传上来的
    DDM_exioSetLevel out[4];            // 最大支持4路输入
} DDM_exioSetDoorSensor;

typedef struct {
    int number;                         // 硬件层面指出的最大输出路数,bsp上传上来的
    DDM_exioSetLevel out[4];            // 最大支持4路输入
} DDM_exioSetCashBox;

typedef struct {
    int number;                         // 硬件层面指出的最大输入路数,bsp上传上来的
    DDM_exioGetLevel in[4];             // 最大支持4路输入
} DDM_exioGetDoorKey;

typedef struct {
    int number;                         // 硬件层面指出的最大输入路数,bsp上传上来的
    DDM_exioGetLevel in[4];             // 最大支持4路输入
} DDM_exioGetFireFighting;

/*********************************************************************
 ******************************* DDM_fan ******************************
 *********************************************************************/

/******************************* 宏定义 ******************************/
#define DDM_DEV_FAN_NAME                "/dev/DDM/fan"
#define DDM_IOC_FAN_MNUM                'F'
//设置风扇转速(0-100)
#define DDM_IOC_FAN_SET_VAL             _IOW(DDM_IOC_FAN_MNUM, 0, unsigned char)

/******************************* 数据结构 ******************************/

/*********************************************************************
 ******************************* DDM_fingerprint ******************************
 *********************************************************************/

/******************************* 宏定义 ******************************/
//对于串口方案的fingerprint模块，APP通过如下标准串口节点与fingerprint模块进行数据交互
#define DDM_DEV_TTY_FINGERPRINT_NAME    "/dev/DDM/tty_fingerprint"
#define DDM_DEV_FINGERPRINT_NAME        "/dev/DDM/fingerprint"
#define DDM_IOC_FINGERPRINT_MNUM        'F'
// 芯片复位<仅针对TTY方案>
#define DDM_IOC_FINGERPRINT_RESET_CHIP      _IO(DDM_IOC_FINGERPRINT_MNUM, 0)
// 获取图像大小信息
#define DDM_IOC_FINGERPRINT_GET_IMAGE_SIZE  _IOR(DDM_IOC_FINGERPRINT_MNUM, 1, DDM_fingerprintGetSize)
// 直接获取图像
#define DDM_IOC_FINGERPRINT_GET_IMAGE_DATA  _IOR(DDM_IOC_FINGERPRINT_MNUM, 2, DDM_fingerprintGetImage)
/******************************* 数据结构 ******************************/
typedef struct
{
    unsigned int        width;          // 指纹图像长度
    unsigned int        height;         // 指纹图像宽度
    unsigned int        image_size;     // 指纹图像大小
    unsigned char       bit_width;      // 指纹图像位深
    unsigned char       res[3];         // 保留
} DDM_fingerprintGetSize;

typedef struct
{
    unsigned char   finger_status;      // 手指检测状态
    unsigned char   *data;              // 指纹图像数据
    unsigned char   res[6];             // 保留
} DDM_fingerprintGetImage;


/*********************************************************************
 ******************************* DDM_gprs ******************************
 *********************************************************************/

/******************************* 宏定义 ******************************/
// gprs模块电源与复位控制通道
#define DDM_DEV_GPRS_NAME               "/dev/DDM/gprs"
// gprs模块串口AT指令通道
#define DDM_DEV_TTY_GPRS_NAME           "/dev/DDM/tty_gprs"
#define DDM_IOC_GPRS_MNUM               'G'

// gprs异常硬件复位(预留)
#define DDM_IOC_GPRS_RESET_CHIP         _IO(DDM_IOC_GPRS_MNUM, 0)
// gprs低功耗设置
#define DDM_IOC_GPRS_SET_POWER          _IOW(DDM_IOC_GPRS_MNUM, 1, DDM_PmMode)

/******************************* 数据结构 ******************************/


/*********************************************************************
 ******************************* DDM_icr ******************************
 *********************************************************************/

/******************************* 宏定义 ******************************/
#define DDM_DEV_ICR_NAME                "/dev/DDM/icr"
#define DDM_IOC_ICR_MNUM                'I'
//获取ICR 当前状态
#define DDM_IOC_ICR_GET_STATE           _IOR(DDM_IOC_ICR_MNUM, 0, unsigned int)
//设置ICR 状态
#define DDM_IOC_ICR_SET_STATE           _IOW(DDM_IOC_ICR_MNUM, 1, unsigned int)

/******************************* 数据结构 ******************************/
//ICR 状态
typedef enum
{
    DDM_ICR_STATE_DAY,                  // DDM_ICRSTATE_DAY  白天
    DDM_ICR_STATE_NIGHT,                // DDM_ICRSTATE_NIGHT 夜晚
    DDM_ICR_STATE_MAX,
} DDM_icrState;

/*********************************************************************
 ******************************* DDM_info *****************************
 *********************************************************************/

/******************************* 宏定义 ******************************/
#define DDM_DEV_INFO_NAME               "/dev/DDM/info"
#define DDM_IOC_INFO_MNUM               'I'
// 写入v2.0版本加密产品信息(仅加密模式下提供)
#define DDM_IOC_INFO_WRITE_PRODUCT_INFO _IOW(DDM_IOC_INFO_MNUM, 0, BOOT_PARAMS_V20)
// 读取v2.0版本加密产品信息
#define DDM_IOC_INFO_READ_PRODUCT_INFO  _IOR(DDM_IOC_INFO_MNUM, 1, BOOT_PARAMS_V20)
// 写入HDB信息(仅加密模式下提供)
#define DDM_IOC_INFO_WRITE_HARDWRE_INFO _IOW(DDM_IOC_INFO_MNUM, 2, hdb_info)
// 读取HDB信息
#define DDM_IOC_INFO_READ_HARDWRE_INFO  _IOR(DDM_IOC_INFO_MNUM, 3, hdb_info)
// 获取密钥状态
#define DDM_IOC_INFO_READ_KEYSTATE      _IOR(DDM_IOC_INFO_MNUM, 4, DDM_infoKey)
// 写入密钥(仅加密模式下提供)
#define DDM_IOC_INFO_WRITE_KEY          _IOW(DDM_IOC_INFO_MNUM, 5, DDM_infoKey)
// 读取密钥
#define DDM_IOC_INFO_READ_KEY           _IOR(DDM_IOC_INFO_MNUM, 6, DDM_infoKey)
// 写入摄像头标定信息
#define DDM_IOC_INFO_WRITE_CAMPARA      _IOW(DDM_IOC_INFO_MNUM, 7, DDM_infoCamInfo)
// 读取摄像头标定信息
#define DDM_IOC_INFO_READ_CAMPARA       _IOR(DDM_IOC_INFO_MNUM, 8, DDM_infoCamInfo)
// 写入app根密钥信息(仅加密模式下提供,针对假的、保存在flash中的根密钥操作,app不需要使用)
#define DDM_IOC_INFO_WRITE_ROOTKEY      _IOW(DDM_IOC_INFO_MNUM, 9, DDM_infoRootkeyInfo)
// 读取app根密钥信息(针对假的、保存在flash中的根密钥操作,app不需要使用)
#define DDM_IOC_INFO_READ_ROOTKEY       _IOR(DDM_IOC_INFO_MNUM, 10, DDM_infoRootkeyInfo)
// 写入测温模块标定信息
#define DDM_IOC_INFO_WRITE_TEMPPARA     _IOW(DDM_IOC_INFO_MNUM, 11, DDM_infoTempInfo)
// 读取测温模块标定信息
#define DDM_IOC_INFO_READ_TEMPPARA      _IOR(DDM_IOC_INFO_MNUM, 12, DDM_infoTempInfo)
// 写萤石DeviceID相关信息
#define DDM_IOC_INFO_WRITE_EZVIZINFO    _IOW(DDM_IOC_INFO_MNUM, 13, DDM_infoEzvizInfo)
// 读萤石DeviceID相关信息
#define DDM_IOC_INFO_READ_EZVIZINFO     _IOR(DDM_IOC_INFO_MNUM, 14, DDM_infoEzvizInfo)
// 写TOF标定信息
#define DDM_IOC_INFO_WRITE_TOFPARA      _IOW(DDM_IOC_INFO_MNUM, 15, DDM_infoTofInfo)
// 读TOF标定信息
#define DDM_IOC_INFO_READ_TOFPARA       _IOR(DDM_IOC_INFO_MNUM, 16, DDM_infoTofInfo)
// 读取DDM版本信息
#define DDM_IOC_INFO_GET_VERSION        _IOR(DDM_IOC_INFO_MNUM, 17, DDM_infoGetVersion)
// 写身份证秘钥信息
#define DDM_IOC_INFO_WRITE_IDKEY        _IOW(DDM_IOC_INFO_MNUM, 18, DDM_infoIdkeyInfo)
// 读身份证秘钥信息
#define DDM_IOC_INFO_READ_IDKEY         _IOR(DDM_IOC_INFO_MNUM, 19, DDM_infoIdkeyInfo)
// 存入设备参数信息
#define DDM_IOC_INFO_WRITE_CALIB        _IOR(DDM_IOC_INFO_MNUM, 20, DDM_infoVlaueCalib)
// 读取设备参数信息
#define DDM_IOC_INFO_READ_CALIB         _IOR(DDM_IOC_INFO_MNUM, 21, DDM_infoVlaueCalib)
//写HEOP分区大小信息
#define DDM_IOC_INFO_WRITE_HEOP_PARA	_IOW(DDM_IOC_INFO_MNUM, 22, DDM_heopPara)
//读HEOP分区大小信息
#define DDM_IOC_INFO_READ_HEOP_PARA		_IOR(DDM_IOC_INFO_MNUM, 23, DDM_heopPara)

#ifndef HDB_MAGIC
#define HKVS_MAGIC  0x53564b48          //HKVS
#define SVKH_MAGIC  0x484b5653          //SVKH
#endif

#ifndef CFG_MAGIC
#define CFG_MAGIC   0x484b5753          //HKWS
#endif
/******************************* 数据结构 ******************************/
typedef enum
{
    DDM_INFO_STATE_UNWRITE  = 0,        // 信息未写入
    DDM_INFO_STATE_WRITEED  = 1,        // 信息已写入
    DDM_INFO_STATE_ERROR    = 2,        // 信息错误(损坏情况、预留)
    DDM_INFO_STATE_MAX,
} DDM_infoKeyState;

typedef enum
{
    DDM_INFO_TYPE_BOOTKEY   = 0,        // 启动密钥,长度32字节
    DDM_INFO_TYPE_ALGKEY    = 1,        // 算法密钥,长度32字节
    DDM_INFO_TYPE_ROOTKEY   = 2,        // 设备数据存储根密钥,长度32字节
    DDM_INFO_TYPE_AUTHKEY   = 3,        // 认证密钥或者数字签名,长度32字节
    DDM_INFO_TYPE_APPKEY    = 4,        // 应用程序密钥(预留)
    DDM_INFO_TYPE_MAX,
} DDM_infoKeyType;

typedef struct
{
    DDM_infoKeyType  type;              // 密钥类型 参考DDM_infoKeyType
    DDM_infoKeyState state;             // 密钥状态 参考DDM_infoKeyState
    unsigned char    data[32];          // 数据,最大长度为32字节
    unsigned int     len;               // 数据长度
} DDM_infoKey;

typedef struct
{
    unsigned int    data_len;           // 数据长度,最大支持4KB长度
    void *          data;               // 数据
} DDM_infoVlaue;

typedef struct {
	unsigned int    crc;    		//!<  校验值CRC32
    unsigned int    flags;			//!<  分区划分配置状态 
    unsigned int    config_size;    //!<  config分区大小 MB
    unsigned int    heop_size;		//!<  heop分区大小	MB
    unsigned int    emmc_size;		//!<  emmc容量大小	MB
	unsigned int	res;          	//!<  预留
} DDM_heopPara;

typedef DDM_infoVlaue DDM_infoCamInfo;
typedef DDM_infoVlaue DDM_infoRootkeyInfo;
typedef DDM_infoVlaue DDM_infoTempInfo;
typedef DDM_infoVlaue DDM_infoEzvizInfo;
typedef DDM_infoVlaue DDM_infoTofInfo;
typedef DDM_infoVlaue DDM_infoIdkeyInfo;

typedef struct
{
	unsigned int        index; 				// 标定信息类型对应的索引值
	unsigned int		calib_checksum; 	// 标定信息有效数据和校验
    unsigned int   	 	data_len;           // 标定信息有效数据长度,最大支持256KB长度,单位字节
    void *          	data;               // 标定信息有效数据
} DDM_infoVlaueCalib;

typedef struct
{
    unsigned char    major;             // 主版本号
    unsigned char    minor;             // 子版本号
    unsigned char    revision;          // 修订号
    unsigned char    rev[1];            // 预留
} DDM_infoGetVersion;

/* 使用预留字段时，保证4字节对齐 */
typedef struct
{
    /*结构体头 共16字节*/
    unsigned int    magic_number;               //0 幻数  有效值0x484b5753
    unsigned int    para_checksum;              //4 结构体校验和
    unsigned int    para_length;                //8 结构长度  ，长度从'encryptVer'开始计算
    unsigned int    encrypt_ver;                //12 加密版本:用于控制此结构的更改 当前是0x00020000(V20)

    /*设备基本信息  共256字节*/
    unsigned char   language[16];               /*16 各个位对应的语言，1表示支持，0表示不支持，可以多种组合
bit0：英语 bit1：简体中文 bit2：繁体中文 bit3：日语 bit4：朝鲜语 bit5：印度语 bit6：蒙古语 bit7：越南 bit8：马来文 bit9：泰国
bit10：菲律宾 bit11：印尼文 bit12：孟加拉文 bit13：老挝文 bit14：尼泊尔文 bit15：丹麦文 bit16：乌克兰文 bit17：乌茲别克语 bit18：亚美尼亚语 bit19：俄语
bit20：保加利亚文 bit21：克罗地亚文 bit22：冰岛语 bit23：加泰罗尼亚文 bit24：匈牙利语 bit25：吉尔吉斯语 bit26：土库曼语 bit27：土耳其文 bit28：塞尔维亚文 bit29：塞索托语
bit30：希伯来语 bit31：希腊语 bit32：德语 bit33：意大利语 bit34：意第绪语 bit35：拉丁文 bit36：拉脱维亚语 bit37：挪威文 bit38：捷克语 bit39：斯洛伐克文
bit40：法语 bit41：波兰语 bit42：波斯语 bit43：爱尔兰语 bit44：爱沙尼亚语 bit45：瑞典语 bit46：瓜拉尼语 bit47：立陶宛语 bit48：索马里语 bit49：罗马尼亚语
bit50：芬兰语 bit51：荷兰语 bit52：葡萄牙语 bit53：西班牙语 bit54：阿尔巴尼亚文 bit55：阿拉伯文 bit56：马其顿文 bit57：马耳他文*/
    unsigned int    device_update_type;         //32 设备升级类型，门禁：850-999；对讲：1000-1200，升级包校验时用
    unsigned int    device_sdk_type;            //36 设备网络类型，门禁：850-899 10501-11000 对讲：602-700 11001-11500 ,返回给SDK使用
    unsigned int    device_sadp_type;           //40 设备SADP类型,门禁:目前维护:0xd0000-0xdffff 对讲：0xe000-0xe3ff
    unsigned int    mcu_device_update_type;     //44 mcu的设备类型，用于mcu升级校验，范围跟device_update_type一样
    unsigned char   dev_model[64];              //48 产品自定义型号 字符串
    unsigned int    oem_code;                   //112 0-无效，1-海康，2-中性 ，预留当前未实际使用
    unsigned char   prod_date[8];               //116 设备生产日期 年月日（4位年份+2位月份+2位日）
    unsigned char   prod_no[16];                //124 设备序列号，数字+字母  扩充到16 ，目前仅用9位
    unsigned char   random_code[6];             //140 萤石随机码
    unsigned char   platform_type;              //146 硬件平台，类型有AI2,AI3等平台代号，加密工具根据该字段从服务器上获取相应平台的加密资源
    unsigned char   sale_type;                       //147 销售类型  1:经销，2:行业
    unsigned int    person_num;                      //148 人员数量 0:表示无效
    unsigned int    face_num;                        //152 人脸数量 0:表示无效
    unsigned int    card_num;                        //156 卡片数量 0:表示无效
    unsigned int    finger_num;                      //160 指纹数量 0:表示无效
    unsigned int    iris_num;                        //164 虹膜数量 0:表示无效
    unsigned int    voice_num;                       //168 声纹数量 0:表示无效
    unsigned int    sale_area;                       //172 销售区域（不同地区的行业规范存在差异） 0:表示无效 
                                                            //28:安提瓜和巴布达 32：阿根廷 44:巴哈马 52:巴巴多斯 56:比利时 68:玻利维亚 76:巴西 84:伯利兹 92:英属维尔京群岛 100:保加利亚
                                                            //152:智利 170: 哥伦比亚 188:哥斯答黎加 191:克罗地亚
                                                            //203:捷克 208:丹麦 212:多米尼克 214:多米尼加共和国 218：厄瓜多尔 222:萨尔瓦多233:爱沙尼亚 250：法国 254:法属圭亚那 276:德国 
                                                            //300:希腊 308:格林纳达 320:危地马拉 328:圭亚那 332:海地 340:洪都拉斯 348:匈牙利 376:以色列 380:意大利 388:牙买加
                                                            //440:立陶宛 484:墨西哥
                                                            //642:罗马尼亚
                                                            //528:荷兰 558:尼加拉瓜 578:挪威 591:巴拿马
                                                            //600:巴拉圭 604:秘鲁 618:波兰 620:葡萄牙 643:俄罗斯 662:圣卢西亚 666:圣文森特和格林纳丁斯 659:圣基茨和尼维斯
                                                            //703:斯洛伐克 705:斯洛文尼亚 724：西班牙 740:苏里南 752:瑞典 780:特立尼达/多巴哥 792:土耳其
                                                            //804:乌克兰 826:英国 858:乌拉圭 862:委内瑞拉 891:塞尔维亚
	unsigned char	access_code[16];			//176 访问码（HD二线制门口机&室内机等项目使用，用于设备即插即用自动激活）
	unsigned char   res1[80];                   //192 设备基本信息预留字段

    /*算法校验信息  共128字节*/
    unsigned int    encrypt_alg_dev_class;      //272 用于研究院算法校验字段，默认和deviceUpdateType相等
    unsigned char   encrypt_algorithm;          //276 是否支持研究院算法（确认）加密：0不支持 1支持，加密工具需要通过该字段进行研究院算法加密流程
    unsigned char   self_algorithm;             //277 是否支持业务部算法加密：0不支持 1支持，加密工具需要通过该字段进行算法加密流程
    unsigned char   self_algo_auth[32];         //278 业务部算法认证密钥,后续指纹算法库内部直接通过这个字段认证，应用无需感知，目前实际使用16字节预留16字节
    unsigned char   crypto;                     //310 设备是否进行过加密 1：是，0：否 ，防止设备出厂再加密的情况。
    unsigned char   res2[89];                   //311 算法校验信息预留字段

    /*DSP相关能力 共128字节*/
    unsigned int    dsp_mem;                    //400 DSP使用的内存大小，单位MB，BSP用于分配DSP内存
    unsigned char   encode_chans;               //404 编码路数，SDK/ISAPI协议中，返回的通道个数，使用的是该值
    unsigned char   decode_chans;               //405 解码路数
    unsigned char   vo_nums;                    //406 支持vo个数: 0,1,2
    unsigned char   res3[121];                  //407 DSP相关能力预留字段

    /*硬件信息，用于定义CPLD中无法描述或者确认的硬件信息，作为CPLD硬件信息的补充  共128字节*/
    unsigned int    display_lcd_type;           //528 显示屏类型：0 - 三目宝(213&211)/利尔达(214&215)/广泰(233)； 1 - 视安通(313)，虚拟物料，产线根据不同批次使用不同的屏幕类型，bsp做相应的设置（1个字节就够了，0或者0xff表示无效值）
    unsigned char   net_num;                    //532 网口数 最大4路
    unsigned char   mac_addr[4][6];             //533 设备mac地址
    unsigned char   id_set_enable;              //557 身份证设置使能位（调制解调器使能位） 0-失能 1-使能， 当整机的身份读卡器刷卡无效时，可能使能该标志位，设置相应的rfcfgReg，gsnonReg，cwgspReg，modgspReg寄存器值，应用可以获取该值，配置给读卡器，是读卡器正常工作
    unsigned char   rfcfg_reg;                  //558 身份证读卡器寄存器26 （0x00~0x3F）
    unsigned char   gsnon_reg;                  //559 身份证读卡器寄存器27 （0x00~0x3F）
    unsigned char   cwgsp_reg;                  //560 身份证读卡器寄存器28 （0x00~0x3F）
    unsigned char   modgsp_reg;                 //561 身份证读卡器寄存器29 （0x00~0x3F）
    unsigned char   res4[94];                   //562 硬件信息预留字段

    /* 预留 */
    unsigned char   device_whole_name[128];         //656 ，设备整机命名,目前仅通道产品使用,如通道设备型号为DS-K3M204-S,组装完的通道命名为DS-K3B961TX-L/EPiQL-Dp60,通道产品通过该字段解析产品出厂时的装配信息。
    unsigned char   res5[240];                      //784 ，预留字节，其他分类预留不够时使用该预留空间共1024个字节

}BOOT_PARAMS_V20;

#pragma pack (4)                        //设置在内存中按照4字节对齐
typedef struct {
    unsigned char    major;             //主版本号
    unsigned char    minor;             //次版本号
    unsigned char    revision;          //修订号
    unsigned char    res[1];
} version_t;

typedef struct {
    unsigned char    year;              //年 默认前置20,如数值为19表示2019年
    unsigned char    month;             //月
    unsigned char    day;               //日
    unsigned char    res[5];
} date_t;

typedef struct {
    unsigned char    major;             //主版本号
    unsigned char    minor;             //次版本号
    unsigned char    revision;          //修订号
    unsigned char    res[1];
} board_t;

typedef struct {
    unsigned char    volume;            //主SOC外置DDR总容量 0-0MB,1-8MB,2-16MB,3-32MB,4-64MB,5-128MB,6-256MB,7-512MB,8-1GB,9-2GB,10-4GB,11-8GB
    unsigned char    num;               //主SOC外置DDR数量   0-无,1-1片外置,2-2片外置,4-4片外置,6-6片外置,8-8片外置
    unsigned char    res[6];
} ddr_t;

typedef struct {
    unsigned char    spk_func;          //spk功能 0-无,1-SPK1对讲,2-SPK1对讲+SPK2广播高音+SPK3广播低音
    unsigned char    mic_func;          //mic功能 0-无,1-MIC1对讲
    unsigned char    aec;               //是否硬件消回音 0-无,1-是
    unsigned char    res[5];
} audio_t;

typedef struct {
    unsigned char    type;              //摄像头类型 0-无,1-可见光,2-红外,3-虹膜,4-TOF,5-结构光,6-热成像
    unsigned char    chip;              /*摄像头芯片
                                          0-无,1-OS02K10 200W,2-OS02D10 200W,3-IMX307 200W,4-OS05A20 500W,5-MN34422 200W,6-OPN8008
                                        */
    unsigned char    rotation;          //摄像头旋转角度 0-0,1-90°,2-180°,3-270° 旋转方向为顺时针方向
    unsigned char    cam_lens;          /*镜头类型
                                          0-无效
                                          1-STF28S5F
                                          2-STF04Y5F
                                          3-STP37S1F
                                          4-STF04P6F
                                          5-STF28S5F_3MPIR
                                          6-STF04Y5F_3MPIR
                                          7-STF02S1F_2MPIR
                                          8-ACS-STF15SY1F-5MP
                                        */
    unsigned char    res[8];
} sensor_t;
typedef struct {
    unsigned char    resolution;        /*显示屏分辨率
                                          0-无,
                                          1-240*320,
                                          2-320*480,
                                          3-480*272,
                                          4-480*800,
                                          5-640*480,
                                          6-600*1024,
                                          7-1024*600,
                                          8-800*1280,
                                          9-1280*800,
                                          10-1366*768,
                                          11-1920*1080
                                        */
    unsigned char    rotation;          //显示屏旋转角度 0-0°,1-90°,2-180°,3-270° 旋转方向为顺时针方向
    unsigned char    touchscreen;       //触摸屏 0-无,1-有 正视图触摸屏原点坐标为左上角(x0,y0)
    unsigned char    size;              //实际尺寸 * 10，最大支持25.5寸(对应255)
    unsigned char    res[4];
} lcd_t;

typedef struct {
    unsigned char    rf1356;            //13.56M RF芯片 0-无,1-有
    unsigned char    rf125k;            //125K RF芯片   0-无,1-有
    unsigned char    wifi_module;       //WIFI模组      0-无,1-有
    unsigned char    wifi_probe;        //WIFI探针      0-无,1-有
    unsigned char    bluetooth;         //蓝牙芯片      0-无,1-有
    unsigned char    mcm;               //移动通信模组(mobile communication module) 0-无,1-有
    unsigned char    sub1g;             //Sub1G RF芯片  0-无,1-有
    unsigned char    zigbee;            //ZigBee芯片    0-无,1-有
    unsigned char    gps;               //定位模块      0-无,1-有
    unsigned char    res[7];
} wireless_t;

typedef struct {
    unsigned char    out_num;           //整机IO类输出接口的总数(三极管对外电平控制,xxx数值表示个数)
    unsigned char    in_num;            //整机IO类输入接口的总数(报警输入,门磁,开门按钮,xxx数值表示个数)
    unsigned char    relay_num;         //继电器输出总数(报警,门锁)
    unsigned char    res[5];
} exio_t;

typedef struct {
    /* 0x000 */ unsigned int     magic;             //魔幻数 HKVS
    /* 0x004 */ unsigned int     checksum;          //结构体CRC校验和,预留暂不用
    /* 0x008 */ version_t        version;           //结构体版本信息
    /* 0x00C */ date_t           date;              //结构体制作日期

    /* 0x014 */ unsigned int     pcb;               //板子的pcb号
    /* 0x018 */ board_t          board_attr;        //主板型号 硬件的版本1.0.A 1.1.B的定义

    /* 0x01C */ unsigned char    res1[4];

    /* 0x020 */ ddr_t            ddr_attr;          //内存信息
    /* 0x028 */ audio_t          audio_attr;        //音频信息
    /* 0x030 */ unsigned int     sensor_num;        //sensor个数   最大支持4个
    /* 0x034 */ sensor_t         sensor_attr[4];    //sensor信息
    /* 0x064 */ lcd_t            main_lcd;          //主屏信息
    /* 0x06C */ lcd_t            secondary_lcd;     //副屏信息
    /* 0x074 */ unsigned int     external_interface;//外接显示器的接口 0-无,1-HDMI,2-VGA,3-HDMI+VGA
    /* 0x078 */ unsigned char    res2[24];

    /* 0x090 */ unsigned int     se_type;           //加密芯片类型 0-无,1-CPU卡认证,2-Desfire认证,3-CPU卡认证+Desfire认证
    /* 0x094 */ wireless_t       wireless_attr;     //无线外设信息
    /* 0x0A4 */ exio_t           exio_attr;         //整机对外输入输出IO信息
    /* 0x0AC */ unsigned char    net_num;           //有线网络个数 0-10
    /* 0x0AD */ unsigned char    usb_num;           //USB个数      0-10
    /* 0x0AE */ unsigned char    rs485_num;         //RS485个数    0-10
    /* 0x0AF */ unsigned char    rs232_num;         //RS232个数    0-10
    /* 0x0B0 */ unsigned char    wiegand_num;       //韦根个数     0-10
	/* 0x0B1 */ unsigned char    sata_num;          //sata个数 0-10
	/* 0x0B2 */ unsigned char    phy_speed;         //网卡类型，用于识别10M 100M 1000M,应用配置协商速率 0-10M 1-100M 2-1000M
    /* 0x0B3 */ unsigned char    res3[13];

    /* 0x0C0 */ unsigned char    board_temp;        //主板温度传感器 0-无,1-有
    /* 0x0C1 */ unsigned char    thermopile_temp;   //热电堆测温     0-无,1-有
    /* 0x0C2 */ unsigned char    ambient_temp;      //环境温度传感器 0-无,1-有
    /* 0x0C3 */ unsigned char    env_humidity;      //环境湿度传感器 0-无,1-有
    /* 0x0C4 */ unsigned char    pm2p5;             //PM2.5传感器    0-无,1-有
    /* 0x0C5 */ unsigned char    res4[27];

    /* 0x0E0 */ unsigned char    poe;               //POE          0-无,1-有
    /* 0x0E1 */ unsigned char    touchkey_num;      //按键芯片上的按键个数 0-16
    /* 0x0E2 */ unsigned char    fp_interface;      //指纹接口     0-无,1-SPI,2-8080,3-DVP,4-MIPI,5-USB,6-UART,7-RS485,8-RS232
    /* 0x0E3 */ unsigned char    tamper;            //是否支持防拆 0-无,1-有
    /* 0x0E4 */ unsigned char    tf;                //TF卡         0-无,1-有
    /* 0x0E5 */ unsigned char    beep;              //蜂鸣器       0-无,1-有
    /* 0x0E6 */ unsigned char    qr_code;           //二维码(Quick Response Code)模组   0-无,1-有
	/* 0x0E7 */ unsigned char    mcu_type;          //mcu类型 0-ST 1-ES 2-STM
	/* 0x0E8 */ unsigned char    mic_num;           //音频输入数量,最大支持4路 0-4
	/* 0x0E9 */ unsigned char    spk_num;           //音频输出数量,最大支持4路 0-4
	/* 0x0EA */ unsigned char	 res5[22];

    /* 0x100 */ unsigned char    res6[256];
} hdb_info;
#pragma pack ()                         //取消4字节对齐方式,恢复缺省对齐

/*********************************************************************
 ******************************* DDM_light ******************************
 *********************************************************************/

/******************************* 宏定义 ******************************/
#define DDM_DEV_LIGHT_NAME              "/dev/DDM/light"
#define DDM_IOC_LIGHT_MNUM              'L'

#define DDM_LIGHT_INVALID_ARGS          (-1)      //无效值

// 氛围灯模式、颜色等设置
#define DDM_IOC_LIGHT_SET_ATMOSPHERE    _IOW(DDM_IOC_LIGHT_MNUM, 0, DDM_lightSetArgs)
// 音量灯显示数量设置
#define DDM_IOC_LIGHT_SET_VOLUME        _IOW(DDM_IOC_LIGHT_MNUM, 1, DDM_lightSetArgs)
// 报警指示灯亮灭设置
#define DDM_IOC_LIGHT_SET_ALARM         _IOW(DDM_IOC_LIGHT_MNUM, 2, DDM_lightSetArgs)
// 信息指示灯亮灭设置
#define DDM_IOC_LIGHT_SET_MESSAGE       _IOW(DDM_IOC_LIGHT_MNUM, 3, DDM_lightSetArgs)
// 红外指示灯设置,包括亮灭和频率设置
#define DDM_IOC_LIGHT_SET_IRLED         _IOW(DDM_IOC_LIGHT_MNUM, 4, DDM_lightSetArgs)
// 按键背光灯亮灭设置
#define DDM_IOC_LIGHT_SET_KEY           _IOW(DDM_IOC_LIGHT_MNUM, 5, DDM_lightSetArgs)
// 对讲指示灯亮灭设置
#define DDM_IOC_LIGHT_SET_INTERCOM      _IOW(DDM_IOC_LIGHT_MNUM, 6, DDM_lightSetArgs)
// 开门指示灯亮灭设置
#define DDM_IOC_LIGHT_SET_OPENDOOR      _IOW(DDM_IOC_LIGHT_MNUM, 7, DDM_lightSetArgs)
// 摄像头白光补光灯设置
#define DDM_IOC_LIGHT_SET_WHITELED      _IOW(DDM_IOC_LIGHT_MNUM, 8, DDM_lightSetArgs)
// 指纹补光灯设置(FP:FINGERPRINT)
#define DDM_IOC_LIGHT_SET_FP_FILL       _IOW(DDM_IOC_LIGHT_MNUM, 9, DDM_lightSetArgs)
// 指纹状态指示灯设置(FP:FINGERPRINT)
#define DDM_IOC_LIGHT_SET_FP_STATE      _IOW(DDM_IOC_LIGHT_MNUM, 10, DDM_lightSetArgs)
// 呼叫指示灯设置
#define DDM_IOC_LIGHT_SET_CALL			_IOW(DDM_IOC_LIGHT_MNUM, 11, DDM_lightSetArgs)
// 刷卡指示灯设置
#define DDM_IOC_LIGHT_SET_CARD			_IOW(DDM_IOC_LIGHT_MNUM, 12, DDM_lightSetArgs)
// 电池电量指示设置
#define DDM_IOC_LIGHT_SET_BATTERY		_IOW(DDM_IOC_LIGHT_MNUM, 13, DDM_lightSetArgs)
// 占线指示设置
#define DDM_IOC_LIGHT_SET_BUSY			_IOW(DDM_IOC_LIGHT_MNUM, 14, DDM_lightSetArgs)

/******************************* 数据结构 ******************************/
// LED颜色显示集
typedef enum {
    DDM_LIGHT_COLOR_WHITE = 0,         //LED显示白色灯
    DDM_LIGHT_COLOR_RED,               //LED显示红色灯
    DDM_LIGHT_COLOR_GREEN,             //LED显示绿色灯
    DDM_LIGHT_COLOR_BLUE,              //LED显示蓝色灯
    DDM_LIGHT_COLOR_YELLOW,            //LED显示黄色灯
    DDM_LIGHT_COLOR_MAX,               //LED颜色最大值
}DDM_lightColor;

// 氛围灯模式控制集
typedef enum {
    DDM_LIGHT_ATMOSPHERE_NORMAL = 0,    //普通模式（全亮）
    DDM_LIGHT_ATMOSPHERE_BREATH,        //呼吸模式
    DDM_LIGHT_ATMOSPHERE_MAX,           //最大值
}DDM_lightAtmosphere;

typedef struct light_control            // 结构体中成员如果设置成DDM_LIGHT_INVALID_ARGS(-1),则表示不修改(保持上一次的设置)
{
    int  light_brihgtiness;             // light 灯亮度设置(0~100)0代表熄灭
    int  light_steps;                   // light 音量灯等级显示 (0~100)传入数值对应相同数量的灯
    int  light_color;                   // light 灯颜色设置
    int  light_atmosphere;              // light 氛围设置(呼吸灯、跑马灯等), 参考DDM_lightAtmosphere配置
    int  light_frequency;               // light 频率设置(红外灯PWM控制的频率)
}DDM_lightControl;

// DDM_light参数集
typedef struct
{
    unsigned int      ch;               // ch 同类灯逻辑通道，譬如: 设备上2个呼吸灯带，需与bsp确认ch和灯带对应关系
    DDM_lightControl  control;          // LED控制结构体，主要控制亮度、颜色、氛围灯效等
    unsigned char     res[4];           // 保留
} DDM_lightSetArgs;

/*********************************************************************
 ******************************* DDM_mcu ******************************
 *********************************************************************/

/******************************* 宏定义 ******************************/
//对于串口方案的mcu模块，APP通过如下标准串口节点与mcu模块进行数据交互
#define DDM_DEV_TTY_MCU_NAME            "/dev/DDM/tty_mcu"
#define DDM_DEV_MCU_NAME                "/dev/DDM/mcu"
#define DDM_IOC_MCU_MNUM                'M'

// mcu异常复位接口
#define DDM_IOC_MCU_RESET_CHIP          _IO(DDM_IOC_MCU_MNUM, 0)
//获取SPI接口mcu是否处于数据发送就绪状态，0表示未就绪，1表示就绪
#define DDM_IOC_MCU_GET_READY_STATE     _IOR(DDM_IOC_MCU_MNUM, 1, unsigned int )

/*********************************************************************
 ******************************* DDM_radio ******************************
 *********************************************************************/

/******************************* 宏定义 ******************************/
#define DDM_DEV_RADIO_NAME              "/dev/DDM/radio"
#define DDM_IOC_RADIO_MNUM              'R'
//radio模块异常复位接口(预留)
#define DDM_IOC_RADIO_RESET_CHIP        _IO(DDM_IOC_RADIO_MNUM, 0)
//设置支持的设备类型，默认设备类型是RADIO_DEVICE_TYPE_GFSK，没有特殊的应用时，不用可以设置，保持默认即可
#define DDM_IOC_RADIO_SET_DEVICE_TYPE   _IOW(DDM_IOC_RADIO_MNUM, 1, DDM_radioDeviceType)
//获取当前设置的设备类型
#define DDM_IOC_RADIO_GET_DEVICE_TYPE   _IOR(DDM_IOC_RADIO_MNUM, 2, unsigned int)
//清空接收缓存
#define DDM_IOC_RADIO_WIPE_RXBUFFER     _IO(DDM_IOC_RADIO_MNUM, 3)
//设置中心频率，底层驱动已配好默认中心频率，没有特殊应用，不用设置
#define DDM_IOC_RADIO_SET_FREQUENCY     _IOW(DDM_IOC_RADIO_MNUM, 4, unsigned int)
//获取中心频率
#define DDM_IOC_RADIO_GET_FREQUENCY     _IOR(DDM_IOC_RADIO_MNUM, 5, unsigned int)
//设置接收待机模式，嗅探或普通模式 ，嗅探模式时radio模块功耗较小，默认工作在正常模式下，无低功耗需求不用设置
#define DDM_IOC_RADIO_SET_RECEIVE_MODE  _IOW(DDM_IOC_RADIO_MNUM, 6, DDM_radioReceiveMode)
//获取接收待机模式，低功耗或普通模式
#define DDM_IOC_RADIO_GET_RECEIVE_MODE  _IOR(DDM_IOC_RADIO_MNUM, 7, unsigned int)
//设置发送模式，低功耗或普通模式，如果发出数据的接收方处于接收嗅探模式，则发送方也要同步配置发送嗅探模式
#define DDM_IOC_RADIO_SET_SEND_MODE     _IOW(DDM_IOC_RADIO_MNUM, 8, DDM_radioSendMode)
//获取发送模式，低功耗或普通模式
#define DDM_IOC_RADIO_GET_SEND_MODE     _IOR(DDM_IOC_RADIO_MNUM, 9, unsigned int)
//获取当前接收状态信道的信号强度
#define DDM_IOC_RADIO_GET_RSSI_VALUE    _IOR(DDM_IOC_RADIO_MNUM, 10, unsigned int)
//设置硬件检测空闲信道RSSI阈值
#define DDM_IOC_RADIO_SET_RSSI_THRESHOLD    _IOW(DDM_IOC_RADIO_MNUM, 11, unsigned int)
//获取硬件检测空闲信道RSSI阈值
#define DDM_IOC_RADIO_GET_RSSI_THRESHOLD    _IOR(DDM_IOC_RADIO_MNUM, 12, unsigned int)
//设置重复发送数据包次数
#define DDM_IOC_RADIO_SET_SEND_REPEAT_TIME  _IOW(DDM_IOC_RADIO_MNUM, 13, unsigned int)
//获取重复发送数据包次数
#define DDM_IOC_RADIO_GET_SEND_REPEAT_TIME  _IOR(DDM_IOC_RADIO_MNUM, 14, unsigned int)
//获取信道繁忙状态
#define DDM_IOC_RADIO_GET_CHANNEL_STATE     _IOR(DDM_IOC_RADIO_MNUM, 15, unsigned int)

/******************************* 数据结构 ******************************/
// radio接收数据模式枚举体，正常模式或
typedef enum
{
    DDM_RADIO_RECEIVE_NORMAL = 0,       //待机接收正常模式
    DDM_RADIO_RECEIVE_SNIFF,            //待机接收嗅探模式，适应低功耗需求
    DDM_RADIO_RECEIVE_TOTAL_MAX,
} DDM_radioReceiveMode;

// radio发送数据模式枚举体，正常模式或
typedef enum
{
    DDM_RADIO_SEND_NORMAL = 0,          //发送正常模式，与接收方接收待机模式相匹配
    DDM_RADIO_SEND_SNIFF,               //发送嗅探模式，与接收方接收待机模式相匹配
    DDM_RADIO_SEND_TOTAL_MAX,
} DDM_radioSendMode;

// radio支持的设备类型
typedef enum
{
    DDM_RADIO_DEVICE_ASK = 0,           //互联网中心参数，支持萤石终端的ASK调制模式的设备类型
    DDM_RADIO_DEVICE_GFSK,              //门禁报警组参数，GFSK调制模式的设备类型
    DDM_RADIO_DEVICE_BELL,              //对接门铃机的设备类型
    DDM_RADIO_DEVICE_TPT,               //用于发射功率测试的设备类型
    DDM_RADIO_DEVICE_RST,               //用于接收灵敏度和频偏测试的设备类型
    DDM_RADIO_DEVICE_LORA,              //Lora调制模式设备类型
    DDM_RADIO_DEVICE_FLRC,              //Flrc调制模式设备类型
    DDM_RADIO_DEVICE_FIX_LENGTH_MODE,   //自配置ID长度,按键数目的设备类型
    DDM_RADIO_DEVICE_TOTAL_MAX,
} DDM_radioDeviceType;

/*********************************************************************
 ******************************* DDM_rf ******************************
 *********************************************************************/

/******************************* 宏定义 ******************************/
#define DDM_DEV_RF_NAME                 "/dev/DDM/rf"
#define DDM_IOC_RF_MNUM                 'R'

#define DDM_RF_FRAME_SIZE_MAX       251         // 251 Byete

//TYPEA卡片激活
#define DDM_IOC_RF_ACTIVATE_TYPEA   			_IOWR(DDM_IOC_RF_MNUM, 0, DDM_rfTypeA)
//TypeA卡片停止
#define DDM_IOC_RF_HALT_TYPEA         			_IO(DDM_IOC_RF_MNUM, 1)
//Mifare卡片认证
#define DDM_IOC_RF_AUTHENTICATE_MIFARE          _IOWR(DDM_IOC_RF_MNUM, 2, DDM_rfMifareAuth)
//Mifare卡片读块操作
#define DDM_IOC_RF_READ_MIFARE_BLOCK     		_IOWR(DDM_IOC_RF_MNUM, 3, DDM_rfMifareBlock)
//Mifare卡片写块操作
#define DDM_IOC_RF_WRITE_MIFARE_BLOCK    		_IOWR(DDM_IOC_RF_MNUM, 4, DDM_rfMifareBlock)
//Mifare卡UID卡判断
#define DDM_IOC_RF_CHECK_MIFARE_UID           	_IO(DDM_IOC_RF_MNUM, 5)
//发送CPU卡的RATS命令
#define DDM_IOC_RF_SEND_CPU_RATS             	_IOWR(DDM_IOC_RF_MNUM, 6, DDM_rfCpuRats)
//发送CPU I BLOCK数据包
#define DDM_IOC_RF_SEND_CPU_I_BLOCK          	_IOWR(DDM_IOC_RF_MNUM, 7, DDM_rfCpuIBlock)
//接收CPU R BLOCK数据包
#define DDM_IOC_RF_RECEIVE_CPU_R_BLOCK          _IOWR(DDM_IOC_RF_MNUM, 8, DDM_rfCpuRBlock)
//TypeB卡片激活
#define DDM_IOC_RF_ACTIVATE_TYPEB    			_IOWR(DDM_IOC_RF_MNUM, 9, DDM_rfTypeB)
//Flica卡片激活
#define DDM_IOC_RF_ACTIVATE_FLICA    			_IOWR(DDM_IOC_RF_MNUM, 10, DDM_rfFlica)
// Ultra卡read
#define DDM_RF_TYPEA_ULTRA_READ                 _IOW(DDM_IOC_RF_MNUM, 11, DDM_UltraData)
// 硬件复位
#define DDM_RF_HARD_RESET                       _IO(DDM_IOC_RF_MNUM,  12)
// TypeB 透传接口，身份证软解使用
#define DDM_RF_TYPEB_CARD_TRANSEIVE             _IOW(DDM_IOC_RF_MNUM, 13, DDM_rfTypeBData)

/******************************* 数据结构 ******************************/
typedef struct {
	unsigned char   TagType[2];
	unsigned char   Snr[15];
	unsigned char   Sak[3];
} DDM_rfTypeA;

typedef struct {
	unsigned char   uid_len[1];
	unsigned char   uid[16];
	unsigned char   card_sn[4];
} DDM_rfTypeB;


typedef struct {
	unsigned char   uid_len;
	unsigned char   uid[16];
} DDM_rfFlica;


typedef struct {
	unsigned char   Mode; //认证模式（0：key A认证，1：key B认证）
	unsigned char   Sector; //认证的扇区号（0~15）
	unsigned char   Key[6]; //6字节认证密钥数组
	unsigned char   Uid[4]; //4字节卡片UID数组
} DDM_rfMifareAuth;


typedef struct {
	unsigned char   BlockId; // 读的块号（0x00~0x3F）
	unsigned char   Data[16];
} DDM_rfMifareBlock;

typedef struct {
	unsigned char   Fsdi;
	unsigned char   Cid;
	unsigned char   ReceLen;
	unsigned char   ReceBuf[20];
} DDM_rfCpuRats;


typedef struct {
	unsigned char   SendLen;
	unsigned char   SendBuf[DDM_RF_FRAME_SIZE_MAX];
	unsigned char   ReceLen;
	unsigned char   ReceBuf[DDM_RF_FRAME_SIZE_MAX];
} DDM_rfCpuIBlock;

typedef struct {
	unsigned char   ReceLen;
	unsigned char   ReceBuf[100];
} DDM_rfCpuRBlock;


typedef struct {
    unsigned char   BlockId;
    unsigned char   Data[4];
} DDM_UltraData;

typedef struct  {
	unsigned int    len;
	char            *data;
	char            reserve[64];
} DDM_rfArgBase;

typedef struct {
	 DDM_rfArgBase  tx;
	 DDM_rfArgBase  rx;
	 char           reserve[64];
} DDM_rfTypeBData;

/*********************************************************************
 ******************************* DDM_rf125k ******************************
 *********************************************************************/

/******************************* 宏定义 ******************************/
#define DDM_DEV_RF125K_NAME             "/dev/DDM/rf125k"
#define DDM_IOC_RF125K_MNUM             'R'
// 设置工作模式
#define DDM_IOC_RF125K_SET_POWER        _IOW(DDM_IOC_RF125K_MNUM, 0, DDM_PmMode)
/******************************* 数据结构 ******************************/


/*********************************************************************
 ******************************* DDM_rtc ******************************
 *********************************************************************/

/******************************* 宏定义 ******************************/
#define DDM_DEV_RTC_NAME                "/dev/DDM/rtc"
#define DDM_IOC_RTC_MNUM                'R'

// 获取RTC芯片电池低电压标志位值：0表示正常，1表示出现过低电压状态
#define DDM_IOC_RTC_GET_ERR_STATUS      _IOR(DDM_IOC_RTC_MNUM, 0, unsigned char)


/*********************************************************************
 ******************************* DDM_se ******************************
 *********************************************************************/

/******************************* 宏定义 ******************************/
#ifndef ENUM_DUMMY4WORD
#define ENUM_DUMMY4WORD(name)   E_##name = 0x10000000
#endif

#define DDM_DEV_SE_NAME                 "/dev/DDM/se"
#define DDM_DEV_SAM_NAME                "/dev/DDM/sam"
#define DDM_IOC_SE_MNUM                 'S'

#define DDM_IOC_SE_V04_SET_POWER        _IOW (DDM_IOC_SE_MNUM, 40, DDM_se_v04_arg_power)           // 电源控制
#define DDM_IOC_SE_V04_GET_ATR          _IOR (DDM_IOC_SE_MNUM, 41, DDM_se_v04_arg_base)            // 获取ATR信息
#define DDM_IOC_SE_V04_GET_VERSION      _IOR (DDM_IOC_SE_MNUM, 42, DDM_se_v04_arg_version)         // 获取设备信息
#define DDM_IOC_SE_V04_APDU_PAIR        _IOWR(DDM_IOC_SE_MNUM, 43, DDM_se_v04_arg_apdu_pair)       // APDU 命令、应答成对接口

#define ISO7816_4_APDU_HEADER_SIZE      4
#define ISO7816_4_APDU_INF_SIZE_MAX     255
#define ISO7816_4_APDU_BODY_S_SIZE_MAX  (ISO7816_4_APDU_INF_SIZE_MAX + 2)                               // | Lc | Data | Le |
#define ISO7816_4_APDU_S_SIZE_MAX       (ISO7816_4_APDU_HEADER_SIZE + ISO7816_4_APDU_BODY_S_SIZE_MAX)   // | CLA | INS | P1 | P2 | Lc | Data | Le |
#define ISO7816_4_APDU_RESP_S_SIZE_MAX  256

/******************************* 数据结构 ******************************/
/**********************************************************************
 * 枚举
 **********************************************************************/
typedef enum {
	DDM_SE_V04_PWR_TYPE_SW,
	DDM_SE_V04_PWR_TYPE_HW,
	DDM_SE_V04_PWR_TYPE_MAX,
	ENUM_DUMMY4WORD(DDM_SE_V04_PWR_TYPE),
} DDM_se_v04_pwr_type;

typedef enum {
	DDM_SE_V04_PWR_ACT_ON,
	DDM_SE_V04_PWR_ACT_OFF,
	DDM_SE_V04_PWR_ACT_RESET,
	DDM_SE_V04_PWR_ACT_MAX,
	ENUM_DUMMY4WORD(DDM_SE_V04_PWR_ACT),
} DDM_se_v04_pwr_act;

typedef enum {
	DDM_SE_V04_DATA_TYPE_ARRAY,
	DDM_SE_V04_DATA_TYPE_POINTER,
	DDM_SE_V04_DATA_TYPE_MAX,
	ENUM_DUMMY4WORD(DDM_SE_V04_DATA_TYPE),
} DDM_se_v04_data_type;

typedef enum {
	DDM_SE_V04_CHIP_TYPE_FM_SE,
	DDM_SE_V04_CHIP_TYPE_NXP_SAM,
	DDM_SE_V04_CHIP_TYPE_MAX,
	ENUM_DUMMY4WORD(DDM_SE_V04_CHIP_TYPE),
} DDM_se_v04_chip_type;

/**********************************************************************
 * 结构体
 **********************************************************************/
typedef struct se_v04_power {
	DDM_se_v04_pwr_type type;
	DDM_se_v04_pwr_act  act;
	char                reserve[64];
} DDM_se_v04_arg_power;

typedef struct se_v04_arg_base {
    union {
        char                data[ISO7816_4_APDU_S_SIZE_MAX];
        char                *buff;
    };
    unsigned int            len;
    DDM_se_v04_data_type    type;
    char                    reserve[63];
} DDM_se_v04_arg_base;

typedef struct se_v04_arg_version {
	DDM_se_v04_chip_type    type;
	DDM_se_v04_arg_base     info;
	char                    reserve[64];
} DDM_se_v04_arg_version;

typedef struct se_v04_apdu_cmd {
	unsigned char       cla;
	unsigned char       ins;
	unsigned char       p1;
	unsigned char       p2;
	char                body[ISO7816_4_APDU_BODY_S_SIZE_MAX];
	char                reserve[61];
} DDM_se_v04_apdu_cmd;

typedef struct se_v04_apdu_pair {
	DDM_se_v04_apdu_cmd cmd;
	unsigned long       cmd_len;
	char                rsp[ISO7816_4_APDU_RESP_S_SIZE_MAX];
	unsigned int        rsp_len;
	char                reserve[62];
} DDM_se_v04_arg_apdu_pair;

#if 1
/** TO DO
 *    To be removed.
 */
#define ISO_7816_3_FRAME_SIZE_MAX       254

#define DDM_IOC_SE_SET_POWER            _IOW(DDM_IOC_SE_MNUM, 0, DDM_seSetPower)                // 电源控制

// SE
#define DDM_IOC_SE_GET_RANDOM           _IOWR(DDM_IOC_SE_MNUM,  3, DDM_se_arg_get_randoms)      // 获取随机数
#define DDM_IOC_SE_INIT_DES             _IOW(DDM_IOC_SE_MNUM,  12, DDM_se_arg_init_des)         // 通用计算初始化
#define DDM_IOC_SE_CALC_DES             _IOWR(DDM_IOC_SE_MNUM, 13, DDM_se_arg)                  // 通用计算执行
#define DDM_IOC_SE_APDU_PACK            _IOWR(DDM_IOC_SE_MNUM, 15, DDM_se_arg_apduPack)         // FMSE APDU 通用协议接口
#define DDM_IOC_SE_SEL_FILE             _IOWR(DDM_IOC_SE_MNUM, 16, DDM_se_arg_sel_file)        // 文件选择
#define DDM_IOC_SE_READ_BINARY          _IOWR(DDM_IOC_SE_MNUM, 17, DDM_se_arg_read)            // 驱动二进制文件

// SE && SAM
#define DDM_IOC_SE_CTRL_POWER           _IOWR(DDM_IOC_SE_MNUM, 30, DDM_se_arg_power)
#define DDM_IOC_SE_GET_VERSION          _IOR( DDM_IOC_SE_MNUM, 31, DDM_se_arg_version)
#define DDM_IOC_SE_I_BLOCK              _IOWR(DDM_IOC_SE_MNUM, 32, DDM_se_arg_i_block)


/** TO DO
 *    To be removed.
 */
#define DDM_IOC_SE_SET_TIMEOUT          _IOW( DDM_IOC_SE_MNUM,  1, DDM_seSetTmout)                // 超时控制
#define DDM_IOC_SE_GET_INFO             _IOR( DDM_IOC_SE_MNUM,  2, DDM_seGetInfo)                 // 设备信息
#define DDM_IOC_SE_GEN_RSA_KEY_PAIR     _IOWR(DDM_IOC_SE_MNUM,  4, DDM_se_arg_gen_rsa_key_pair) // 生成RSA秘钥对
#define DDM_IOC_SE_CAL_RSA_PUB_KEY      _IOWR(DDM_IOC_SE_MNUM,  5, DDM_se_arg_cal_key)          // RSA公钥加密
#define DDM_IOC_SE_CAL_RSA_PRI_KEY      _IOWR(DDM_IOC_SE_MNUM,  6, DDM_se_arg_cal_key)          // RSA私钥解密
#define DDM_IOC_SE_GEN_SM2_KEY_PAIR     _IOWR(DDM_IOC_SE_MNUM,  7, DDM_se_arg_gen_sm2_key_pair) // 生成SM2秘钥对
#define DDM_IOC_SE_CAL_SM2_PUB_KEY      _IOWR(DDM_IOC_SE_MNUM,  8, DDM_se_arg_cal_key)          // SM2公钥加密
#define DDM_IOC_SE_CAL_SM2_PRI_KEY      _IOWR(DDM_IOC_SE_MNUM,  9, DDM_se_arg_cal_key)          // SM2私钥解密
#define DDM_IOC_SE_IMPT_SESSION_KEY     _IOWR(DDM_IOC_SE_MNUM, 10, DDM_se_arg_ipt_ses_key)      // 导入会话秘钥
#define DDM_IOC_SE_EN_DECRYPT_DATA      _IOWR(DDM_IOC_SE_MNUM, 11, DDM_se_arg_en_decrypt)       // 使用会话秘钥加密、解密
#define DDM_IOC_SE_WRITE_KEY            _IOW(DDM_IOC_SE_MNUM,  14, DDM_se_arg_write_key)        // 装载、修改密钥
#define DDM_IOC_SE_VERIFY_PIN           _IOWR(DDM_IOC_SE_MNUM, 18, DDM_se_arg)                  // 口令校验


/******************************* 数据结构 ******************************/

/*******************************************************************************
 * 枚举
 ***************************************************************************/
typedef enum {
	SE_PWR_TYPE_SW,
	SE_PWR_TYPE_HW,
	SE_PWR_TYPE_MAX,
	ENUM_DUMMY4WORD(SE_PWR_TYPE),
} se_pwr_type;

typedef enum {
	SE_PWR_ACT_ON,
	SE_PWR_ACT_OFF,
	SE_PWR_ACT_RESET,
	SE_PWR_ACT_MAX,
	ENUM_DUMMY4WORD(SE_PWR_ACT),
} se_pwr_act;

typedef enum {
	SE_CHIP_TYPE_FM_SE,
	SE_CHIP_TYPE_NXP_SAM,
	SE_CHIP_TYPE_MAX,
	ENUM_DUMMY4WORD(SE_CHIP_TYPE),
} se_chip_type;

typedef enum tagDDM_se_randoms_len {
    DDM_SE_RAN_4  = 4,
    DDM_SE_RAN_8  = 8,
    DDM_SE_RAN_10 = 10,
    DDM_SE_RAN_MAX,
} DDM_se_randoms_len;

/*******************************************************************************
 * 结构体
 *******************************************************************************/
 typedef struct rf_power {
	se_pwr_type     type;
	se_pwr_act      act;
	char            reserve[64];
} DDM_se_arg_power, DDM_seSetPower;

 typedef struct {
	unsigned int    len;
	char            *data;
	char            reserve[64];
} DDM_se_arg_base;

typedef struct tagSE_data {
	unsigned short  len;
    unsigned char   buff[ISO_7816_3_FRAME_SIZE_MAX];
} DDM_se_arg_data, DDM_se_arg_data_tx, DDM_se_arg_data_rx;

typedef struct {
	se_chip_type    type;
	DDM_se_arg_base version;
	char            reserve[64];
} DDM_se_arg_version;

typedef struct tagApduPack {
	unsigned char   cla;
	unsigned char   ins;
	unsigned char   p1;
	unsigned char   p2;
	union{
		unsigned char   lc;
		unsigned char   le;
	} p3;
	unsigned char   data[ISO_7816_3_FRAME_SIZE_MAX];
	unsigned char   le;
    char            reserve[61];
} apduPack_t, DDM_se_apdu_head;

typedef struct {
    union {
     	DDM_se_apdu_head    data;
        unsigned short      len;
    };
	DDM_se_arg_base         rx;
	char                    reserve[63];
} DDM_se_arg_apdu;

typedef union {
	struct {
		char    sad     :3;
		char    dpct1   :1;     // deprecated
		char    dad     :3;
		char    dpct2   :1;     // deprecated
	} bits;
	char    val;
} se_iso7816_3_nad;

typedef struct {
	se_iso7816_3_nad    nad;    // 1 byte long prologue field of NAD
	DDM_se_arg_base     tx;
	DDM_se_arg_base     rx;
	char                reserve[63];
} DDM_se_arg_i_block;

typedef struct {
    DDM_se_randoms_len  randoms_len;
    DDM_se_arg_data     rx;
} DDM_se_arg_get_randoms;

typedef struct {
    union {
        unsigned short  file_id;
        unsigned short  id;
    };
    DDM_se_arg_data     rx;
} DDM_se_arg_sel_file;

typedef struct tagSE_read_binary {
    union {
        unsigned short  read_offset;
        unsigned int    offset;
    };
    union {
        unsigned short  read_len;
        unsigned int    len;
    };
    DDM_se_arg_data     rx;
} DDM_se_arg_read;

typedef struct tagSE_arg_apduPack {
	apduPack_t      apdu;
	unsigned short  tx_len;
	unsigned short  rx_len;
} DDM_se_arg_apduPack;

/** TO DO
 *    To be removed.
 */
typedef enum tagDDM_se_rsa_lenth {
    DDM_SE_RSA1024 = 0,
    DDM_SE_RSA1280,
    DDM_SE_RSA2048,
    DDM_SE_RSA_LEN_MAX,
} DDM_se_rsa_len;

typedef enum tagDDM_se_rsa_exp {
    DDM_SE_RSA_EXP65537 = 0,
    DDM_SE_RSA_EXP3,
    DDM_SE_RSA_EXP_MAX,
} DDM_se_rsa_exp;

typedef enum
{
    SE_MANUFACT_FMCOS_SE,               // 芯片，FMCOS SE
    SE_MANUFACT_NXP_SAM,                // 芯片，NXP SAM
} se_manfact;

typedef struct
{
    se_manfact          device;     // 芯片型号
    unsigned char       res[60];
} DDM_seGetInfo;

typedef struct
{
    struct {
	    long    tv_sec;		/* seconds */
	    long    tv_usec;	/* microseconds */
    } interval;   // 超时，循环间隔
    struct {
	    long    tv_sec;		/* seconds */
	    long    tv_usec;	/* microseconds */
    } expires;    // 超时，溢出时间
} DDM_seSetTmout;

typedef struct tagSE_general_arg {
    DDM_se_arg_data     tx;
    DDM_se_arg_data     rx;
} DDM_se_arg;

typedef struct tag_key_pair {
    unsigned short      pub_key;
    unsigned short      pri_key;
} DDM_se_key_pair;

typedef struct tag_se_arg_gen_key_pair {
    DDM_se_key_pair     file_ids;
    DDM_se_arg_data     rx;
} DDM_se_arg_gen_key_pair, DDM_se_arg_gen_sm2_key_pair;

typedef struct tagSE_arg_gen_rsa_key_pair {
    DDM_se_rsa_len      rsa_len;
    DDM_se_rsa_exp      rsa_exp;
    DDM_se_key_pair     file_ids;
    DDM_se_arg_data     rx;
} DDM_se_arg_gen_rsa_key_pair;

typedef struct tagSE_arg_write_key {
    unsigned char       p1;
    unsigned char       p2;
    DDM_se_arg_data     tx;
} DDM_se_arg_write_key;

typedef struct tagSE_arg_init_des {
    unsigned char      	key_usage;
    unsigned char       key_version;
    DDM_se_arg_data     tx;
} DDM_se_arg_init_des;

typedef struct tagSE_arg_cal_key {
    unsigned char       p1;
    unsigned char       p2;
    DDM_se_arg          data;
} DDM_se_arg_cal_key, DDM_se_arg_ipt_ses_key, DDM_se_arg_en_decrypt;

#undef ENUM_DUMMY4WORD
#endif

/*********************************************************************
 ******************************* DDM_sensor ******************************
 *********************************************************************/

/******************************* 宏定义 ******************************/
#define DDM_DEV_SENSOR_NAME             "/dev/DDM/sensor"
#define DDM_IOC_SENSOR_MNUM             'S'

//获取设备内部温度值，单位摄氏度，精度0.01，int参数除以100后为实际数据
#define DDM_IOC_SENSOR_GET_DEV_TEMP     _IOR(DDM_IOC_SENSOR_MNUM, 0, int)
//获取cpu附近温度值，单位摄氏度，精度0.01，int参数除以100后为实际数据
#define DDM_IOC_SENSOR_GET_CPU_TEMP     _IOR(DDM_IOC_SENSOR_MNUM, 1, int)
//获取环境温度值，单位摄氏度，精度0.01，int参数除以100后为实际数据
#define DDM_IOC_SENSOR_GET_AMBIENT_TEMP _IOR(DDM_IOC_SENSOR_MNUM, 2, int)
//获取lcd附近温度值，单位摄氏度，精度0.01，int参数除以100后为实际数据
#define DDM_IOC_SENSOR_GET_LCD_TEMP     _IOR(DDM_IOC_SENSOR_MNUM, 3, int)
//获取相对湿度值，单位百分比，精度0.01，int参数除以100后为实际数据
#define DDM_IOC_SENSOR_GET_HUMIDITY     _IOR(DDM_IOC_SENSOR_MNUM, 4, int)
//获取PM2.5值，单位微克每立方米，精度0.01，int参数除以100后为实际数据
#define DDM_IOC_SENSOR_GET_PM25         _IOR(DDM_IOC_SENSOR_MNUM, 5, int)
//获取电压值，单位毫伏
#define DDM_IOC_SENSOR_GET_VOLTAGE      _IOR(DDM_IOC_SENSOR_MNUM, 6, DDM_sensorVoltage)

/******************************* 数据结构 ******************************/
// 获取电压值
typedef struct {
	unsigned char      ch;
    unsigned char    type;
    unsigned char    res[2];
	unsigned int     data;
} DDM_sensorVoltage;   

typedef enum tagDDM_sensorVoltageType{
    DDM_SENSOR_VOLTAGE_TYPE_PWR = 0,
    DDM_SENSOR_VOLTAGE_TYPE_BAT,
    DDM_SENSOR_VOLTAGE_TYPE_MAX,
} DDM_sensorVoltageType;

/*********************************************************************
 ******************************* DDM_sound ******************************
 *********************************************************************/

/******************************* 宏定义 ******************************/
#define DDM_DEV_SOUND_NAME              "/dev/DDM/sound"
#define DDM_IOC_SOUND_MNUM              'S'

//关闭功放
#define DDM_IOC_SOUND_CLOSE_AMP         _IOW(DDM_IOC_SOUND_MNUM, 0, unsigned int)
//打开功放
#define DDM_IOC_SOUND_OPEN_AMP          _IOW(DDM_IOC_SOUND_MNUM, 1, unsigned int)
//设置功放增益
#define DDM_IOC_SOUND_SET_AMP_GAIN      _IOW(DDM_IOC_SOUND_MNUM, 2, DDM_soundAmpGain)
//获取功放增益
#define DDM_IOC_SOUND_GET_AMP_GAIN      _IOR(DDM_IOC_SOUND_MNUM, 3, DDM_soundAmpGain)
//设置音频codec芯片的采样参数，比特率和位宽
#define DDM_IOC_SOUND_SET_FORMAT        _IOW(DDM_IOC_SOUND_MNUM, 5, DDM_soundFormat)
//获取音频codec芯片的采样参数，比特率和位宽
#define DDM_IOC_SOUND_GET_FORMAT        _IOR(DDM_IOC_SOUND_MNUM, 6, DDM_soundFormat)
//关闭mic
#define DDM_IOC_SOUND_CLOSE_MIC         _IOW(DDM_IOC_SOUND_MNUM, 10, unsigned int)
//打开mic
#define DDM_IOC_SOUND_OPEN_MIC          _IOW(DDM_IOC_SOUND_MNUM, 11, unsigned int)
//设置外接音频路径
#define DDM_IOC_SOUND_SET_OUTPUT_CHANNEL      _IOW(DDM_IOC_SOUND_MNUM, 12, DDM_soundPath)
//获取外接音频路径状态
#define DDM_IOC_SOUND_GET_OUTPUT_CHANNEL      _IOR(DDM_IOC_SOUND_MNUM, 13, DDM_soundPath)
//设置外接音频路径
#define DDM_IOC_SOUND_SET_INPUT_CHANNEL       _IOW(DDM_IOC_SOUND_MNUM, 14, DDM_soundPath)
//获取外接音频路径状态
#define DDM_IOC_SOUND_GET_INPUT_CHANNEL       _IOR(DDM_IOC_SOUND_MNUM, 15, DDM_soundPath)
//设置外接音频路径
#define DDM_IOC_SOUND_SET_OUTPUT_VOLUME      _IOW(DDM_IOC_SOUND_MNUM, 16, DDM_soundVolume)
//获取外接音频路径状态
#define DDM_IOC_SOUND_GET_OUTPUT_VOLUME      _IOR(DDM_IOC_SOUND_MNUM, 17, DDM_soundVolume)
//设置外接音频路径
#define DDM_IOC_SOUND_SET_INPUT_VOLUME       _IOW(DDM_IOC_SOUND_MNUM, 18, DDM_soundVolume)
//获取外接音频路径状态
#define DDM_IOC_SOUND_GET_INPUT_VOLUME       _IOR(DDM_IOC_SOUND_MNUM, 19, DDM_soundVolume)



//功放增益设置结构体
typedef struct
{
    unsigned int channel;               // 配置表中对应的通道号
    unsigned int gain;                  // 功放增益
} DDM_soundAmpGain;

typedef enum
{
    DDM_SOUND_OUTPATH_EXT_SPK = 0,                    //切换至外接音箱
    DDM_SOUND_OUTPATH_LOCAL_SPK,                      //切换至本地spk
    DDM_SOUND_OUTPATH_HP_SPK,                         //切换耳机输出
    DDM_SOUND_OUTPATH_LOCAL_PLATFORM,                 //平台间输出电路切换到本地端soc（双芯片产品适用）
    DDM_SOUND_OUTPATH_REMOTE_PLATFORM,                //平台间输出电路切换到远端soc（双芯片产品适用）
    DDM_SOUND_OUTPATH_MAX,
} DDM_soundOutputPath;

typedef enum
{
    DDM_SOUND_INPATH_EXT_MIC = 0,                    //切换至外接MIC
    DDM_SOUND_INPATH_LOCAL_MIC,                      //切换至本地MIC
    DDM_SOUND_INPATH_LOOPBACK,                       //切换至回采
    DDM_SOUND_INTPATH_HP_MIC,                        //切换至耳机输入
    DDM_SOUND_INPATH_LOCAL_PLATFORM,                 //平台间输入电路切换本地端soc（双芯片产品适用）
    DDM_SOUND_INPATH_REMOTE_PLATFORM,                //平台间输入电路切换远端soc（双芯片产品适用）
    DDM_SOUND_INPATH_MAX,
} DDM_soundInputPath;

//外接音频路径设置结构体
typedef struct
{
    unsigned int path_channel;               // 设置的路径通道号
    unsigned int type;                  // 路径类型
    unsigned int status;                // 连通状态
} DDM_soundPath;


//功放增益设置结构体
typedef struct
{
    unsigned int path_channel;               // 具体是哪个路径
    unsigned int path;                 // 需要设置的音量路径名字
    unsigned int vol;                  // 功放增益
} DDM_soundVolume;

#define BIT(nr)			(1UL << (nr))
/* 音频采样率 8K 到 192K，具体看各个codec芯片支持的范围 */
typedef enum
{
    SND_SOC_PCM_RATE_8000    = (8000),
    SND_SOC_PCM_RATE_11025   = (11025),
    SND_SOC_PCM_RATE_12000   = (12000),
    SND_SOC_PCM_RATE_16000   = (16000),
    SND_SOC_PCM_RATE_22050   = (22050),
    SND_SOC_PCM_RATE_24000   = (24000),
    SND_SOC_PCM_RATE_32000   = (32000),
    SND_SOC_PCM_RATE_44100   = (44100),
    SND_SOC_PCM_RATE_48000   = (48000),
    SND_SOC_PCM_RATE_96000   = (96000),
    SND_SOC_PCM_RATE_192000  = (192000),
}SND_PcmRate;

typedef enum
{
    SND_SOC_PCM_FORMAT_S8                       = BIT(0),
    SND_SOC_PCM_FORMAT_S16                      = BIT(1),
    SND_SOC_PCM_FORMAT_S20                      = BIT(2),
    SND_SOC_PCM_FORMAT_S24                      = BIT(3),
    SND_SOC_PCM_FORMAT_S32                      = BIT(4),
    SND_SOC_PCM_FORMAT_MSB_S24                  = BIT(5),
}SND_PcmBitwidth;


/*********************************************************************
 ******************************* 枚举 ********************************
 *********************************************************************/

/* 采样音频数据的宽度 16bit 20bit 24bit 32bit 前提是芯片支持这种传输方式 */
typedef enum
{
    /* 增加位时钟频率设置 */
    SND_SOC_PCM_FORMAT_32FS                     = (32),
    SND_SOC_PCM_FORMAT_48FS                     = (48),
    SND_SOC_PCM_FORMAT_64FS                     = (64),
	SND_SOC_PCM_FORMAT_128FS                    = (128),
    SND_SOC_PCM_FORMAT_256FS                    = (256),
    SND_SOC_PCM_FORMAT_512FS                    = (512),
}SND_PcmBclk;

//功放增益设置结构体
typedef struct
{
    unsigned int path_direction;        // path的方向，0代表输入 1代表输出
    unsigned int path;                  // 需要设置的音量路径名字 具体参考 DDM_soundOutputPath与 DDM_soundInputPath
    unsigned int path_channel;          // 相同路径名称的具体哪个路径，譬如：板子上有2个耳机，要控制左声道，就要区分耳机1和耳机2,channel就是1跟2.具体值要配合项目和bsp沟通
    unsigned int rate;                  // 采样率
    unsigned int bit_width;             // 位宽
    unsigned int b_clk;                 // 位时钟
} DDM_soundFormat;


/*********************************************************************
 ******************************* DDM_ts ******************************
 *********************************************************************/

/******************************* 宏定义 ******************************/
#define DDM_DEV_TS_NAME                 "/dev/DDM/ts"
#define DDM_DEV_TS_VICE_NAME            "/dev/DDM/ts_vice"
#define DDM_IOC_TS_MNUM                 'T'

// 固件升级
#define DDM_IOC_TS_UPDATE_FW            _IOW(DDM_IOC_TS_MNUM, 1, DDM_tsSetFwArgs)
// 获取芯片ID
#define DDM_IOC_TS_GET_CHIPID           _IOR(DDM_IOC_TS_MNUM, 2, unsigned int)
// 芯片校准
#define DDM_IOC_TS_DO_CALIBRATION       _IO(DDM_IOC_TS_MNUM, 3)
// 获取固件版本信息
#define DDM_IOC_TS_GET_VERSION          _IOR(DDM_IOC_TS_MNUM, 4, DDM_tsGetVersion)
/******************************* 数据结构 ******************************/
// 固件升级参数
typedef struct
{
    char fw_path[100];                  // 固件路径
    int reserve;                        // 保留
} DDM_tsSetFwArgs;

// 获取固件版本
typedef struct
{
    unsigned int  len;
    unsigned char version[20];
} DDM_tsGetVersion;

/*********************************************************************
 ******************************* DDM_tty_rs485 ************************
 *********************************************************************/

/******************************* 宏定义 ******************************/
#define DDM_DEV_TTY_RS4851_NAME         "/dev/DDM/tty_rs485_1"
#define DDM_DEV_TTY_RS4852_NAME         "/dev/DDM/tty_rs485_2"
#define DDM_DEV_TTY_RS4853_NAME         "/dev/DDM/tty_rs485_3"
#define DDM_DEV_TTY_RS4854_NAME         "/dev/DDM/tty_rs485_4"
#define DDM_DEV_TTY_RS4855_NAME         "/dev/DDM/tty_rs485_5"
#define DDM_DEV_TTY_RS4856_NAME         "/dev/DDM/tty_rs485_6"
#define DDM_DEV_TTY_RS4857_NAME         "/dev/DDM/tty_rs485_7"
/******************************* 模拟485 ******************************/
#define DDM_DEV_TTY_ANALOG_NAME         "/dev/DDM/tty_analog"

/*********************************************************************
 ******************************* DDM_tty_rs232 ************************
 *********************************************************************/

/******************************* 宏定义 ******************************/
#define DDM_DEV_TTY_RS2321_NAME         "/dev/DDM/tty_rs232_1"
#define DDM_DEV_TTY_RS2322_NAME         "/dev/DDM/tty_rs232_2"

/*********************************************************************
 ******************************* DDM_vsync ******************************
 *********************************************************************/

/******************************* 宏定义 ******************************/
#define DDM_DEV_VSYNC_NAME              "/dev/DDM/vsync"
#define DDM_IOC_VSYNC_MNUM              'V'

// vsync 输出信号低电平对于下降沿中断的时间, 单位us
#define DDM_IOC_VSYNC_SET_LOW_TIME      _IOW(DDM_IOC_VSYNC_MNUM, 0, unsigned int)
// vsync 输出信号高电平对于下降沿中断的时间, 单位us
#define DDM_IOC_VSYNC_SET_DELAY_TIME    _IOW(DDM_IOC_VSYNC_MNUM, 1, unsigned int)
//关闭帧同步，可设置默认灯的状态(开还是关)
#define DDM_IOC_VSYNC_CLOSE             _IOW(DDM_IOC_VSYNC_MNUM, 2, DDM_vsyncOutput)
//开启帧同步
#define DDM_IOC_VSYNC_OPEN              _IO(DDM_IOC_VSYNC_MNUM, 3)

typedef enum
{
    DDM_VSYNC_LIGHT_OPEN = 0,           //默认常开
    DDM_VSYNC_LIGHT_CLOSE,              //默认常关
} DDM_vsyncOutput;

/******************************* 数据结构 ******************************/


/*********************************************************************
 ******************************* DDM_wiegand *************************
 *********************************************************************/
/********************************* 宏定义*******************************/
#define DDM_DEV_WIEGAND_NAME                    "/dev/DDM/wiegand"
#define DDM_IOC_WIEGAND_MNUM                    'W'

#define DDM_DEV_WIEGAND_CH0_NAME                "/dev/DDM/wiegand"
#define DDM_DEV_WIEGAND_CH1_NAME                "/dev/DDM/wiegand1"
#define DDM_DEV_WIEGAND_CH2_NAME                "/dev/DDM/wiegand2"
#define DDM_DEV_WIEGAND_CH3_NAME                "/dev/DDM/wiegand3"

// wiegand 设置工作模式
#define DDM_IOC_WIEGAND_SET_MODE                _IOW(DDM_IOC_WIEGAND_MNUM, 0, DDM_wiegandMode)
// wiegand 获取工作模式
#define DDM_IOC_WIEGAND_GET_MODE                _IOR(DDM_IOC_WIEGAND_MNUM, 1, DDM_wiegandMode)
// wiegand 设置信号
#define DDM_IOC_WIEGAND_SET_SIGNAL              _IOW(DDM_IOC_WIEGAND_MNUM, 2, DDM_wiegandSignal)
// wiegand 获取信号
#define DDM_IOC_WIEGAND_GET_SIGNAL              _IOR(DDM_IOC_WIEGAND_MNUM, 3, DDM_wiegandSignal)
// wiegand 设置 方向 脉冲配置
#define DDM_IOC_WIEGAND_SET_TIMING              _IOW(DDM_IOC_WIEGAND_MNUM, 4, DDM_wiegandTiming)
// wiegand 获取 方向 脉冲配置
#define DDM_IOC_WIEGAND_GET_TIMING              _IOR(DDM_IOC_WIEGAND_MNUM, 5, DDM_wiegandTiming)
// wiegand 输出结束判断
#define DDM_IOC_WIEGAND_OUTPUT_DONE             _IOW(DDM_IOC_WIEGAND_MNUM, 6, unsigned char)
// wiegand  清除数据接受缓存
#define DDM_IOC_WIEGAND_CLEAR_RXBUFFER          _IO(DDM_IOC_WIEGAND_MNUM, 7)
// wiegand T1自环测
#define DDM_IOC_WIEGAND_T1_TEST                 _IO(DDM_IOC_WIEGAND_MNUM, 8)
// wiegand T1测试,获取W0脚电平
#define DDM_IOC_WIEGAND_GET_W0_LEVEL_T1         _IOR(DDM_IOC_WIEGAND_MNUM, 9, DDM_wiegandSignalVal)
// wiegand T1测试,获取W1脚电平
#define DDM_IOC_WIEGAND_GET_W1_LEVEL_T1         _IOR(DDM_IOC_WIEGAND_MNUM, 10, DDM_wiegandSignalVal)


#if !defined(WG_ENUM_DUMMY4WORD)
#define WG_ENUM_DUMMY4WORD(name)                   E_##name = (01UL << 28)
#endif

#define DDM_WIEGAND_PACK_DATA_SIZE             (01UL << 6)
/*********************************************************************
 ******************************* 枚举 ********************************
 *********************************************************************/
typedef enum
{
	DDM_WIEGAND_DATA_INPUT = 0,             //wiegand data input
	DDM_WIEGAND_DATA_OUTPUT,                //wiegand data output
	WG_ENUM_DUMMY4WORD(WIEGAND_DIRECTION),
} DDM_wiegandDirection;

typedef enum
{
	DDM_WIEGAND_SIGNAL_DEACTIVE = 0,         //wiegand disable level
	DDM_WIEGAND_SIGNAL_ACTIVE,               //wiegand envable level
	WG_ENUM_DUMMY4WORD(WIEGAND_SIGNAL_VAL),
} DDM_wiegandSignalVal;

typedef enum
{
	DDM_WIEGAND_SIGNAL_MIN = 0,
	DDM_WIEGAND_SIGNAL_OK,                  // wiegand OK信号
	DDM_WIEGAND_SIGNAL_ERROR,               // wiegand error信号
	DDM_WIEGAND_SIGNAL_BUZZER,              // wiegand buzzer信号
	DDM_WIEGAND_SIGNAL_TAMPER,              // wiegand tamper信号
	DDM_WIEGAND_SIGNAL_MAX,
	WG_ENUM_DUMMY4WORD(WIEGAND_SIGNAL_TYPE),
} DDM_wiegandSignalType;

typedef enum
{
	DDM_WIEGAND_MODE_CUSTOM = 0,            // wiegand mode: custom mode
	DDM_WIEGAND_MODE_KEY    = 4,            // wiegand mode: Key, 4 bits;
	DDM_WIEGAND_MODE_26     = 26,           // wiegand mode: Even, bit[0]; Data, 24 bit[1:24]; Odd, 1bit[25]
	DDM_WIEGAND_MODE_27     = 27,           // wiegand mode: Even, bit[0]; Data, 24 bit[1:24]; Odd, 2bit[25:26]
	DDM_WIEGAND_MODE_34     = 34,           // wiegand mode: Even, bit[0]; Data, 32 bit[1:32]; Odd, 1bit[33]
	DDM_WIEGAND_MODE_35     = 35,           // wiegand mode: Even, bit[0]; Data, 32 bit[1:32]; Odd, 2bit[33:34]
	DDM_WIEGAND_MODE_58     = 58,           // wiegand mode: Even, bit[0]; Data, 56 bit[1:56]; Odd, 1bit[57]
	WG_ENUM_DUMMY4WORD(WIEGAND_MODE),
} DDM_wiegandMode;

/*********************************************************************
 ******************************* 结构体 ******************************
 *********************************************************************/

typedef struct {
	 unsigned char          w_ok;           // wiegand OK
	 unsigned char          w_err;          // wiegand error
	 unsigned char          w_buz;          // wiegand buzzer
	 unsigned char          w_tam;          // wiegand tamper
} DDM_wiegand_signal;

typedef struct
{
	DDM_wiegandSignalType   type;           // wiegand mode see @DDM_wiegandMode
	DDM_wiegandSignalVal    val;            // number of bits in the command data field @DDM_wiegandSignalVal
	unsigned char           reserve[64];    // Reserve
} DDM_wiegandSignal;

typedef struct
{
	DDM_wiegandDirection    direct;         // wiegand data dir
	unsigned int            period_l;       // low_level period,  unit us, default 50us
	unsigned int            period_h;       // hith_level period, unit us, default 2000us
	unsigned int            period_i;       // interval period,   unit us, default 100000us
	unsigned char           reserve[64];    // Reserve
} DDM_wiegandTiming;

typedef struct
{
	DDM_wiegandMode         mode;                             // wiegand mode see @DDM_wiegandMode
	unsigned char           bits;                             // number of bits in the command data field, not necessary for send mode
	unsigned char           data[DDM_WIEGAND_PACK_DATA_SIZE]; // command data, big-endian byte stream, big-endian bit stream(MSB)
	unsigned char           reserve[63];                      // Reserve
} DDM_wiegandPack;

#undef WG_ENUM_DUMMY4WORD

/*********************************************************************
 ******************************* DDM_wifi ******************************
 *********************************************************************/

/******************************* 宏定义 ******************************/
#define DDM_DEV_WIFI_NAME               "/dev/DDM/wifi"
#define DDM_IOC_WIFI_MNUM               'W'

// wifi异常硬件复位(预留)
#define DDM_IOC_WIFI_RESET_CHIP         _IO(DDM_IOC_WIFI_MNUM, 0)
// wifi低功耗设置
#define DDM_IOC_WIFI_SET_POWER          _IOW(DDM_IOC_WIFI_MNUM, 1, DDM_PmMode)
/******************************* 数据结构 ******************************/

/*********************************************************************
 ******************************* DDM_zigbee ******************************
 *********************************************************************/

/******************************* 宏定义 ******************************/
//对于串口方案的zigbee模块，APP通过如下标准串口节点与zigbee模块进行数据交互
#define DDM_DEV_TTY_ZIGBEE_NAME         "/dev/DDM/tty_zigbee"
//zigbee字符设备节点节点，主要用于复位、功耗等控制
#define DDM_DEV_ZIGBEE_NAME             "/dev/DDM/zigbee"
#define DDM_IOC_ZIGBEE_MNUM             'Z'

//zigbee模块异常硬件复位
#define DDM_IOC_ZIGBEE_RESET_CHIP       _IO(DDM_IOC_ZIGBEE_MNUM,  0)
//zigbee功耗模式设置
#define DDM_IOC_ZIGBEE_SET_POWER        _IOW(DDM_IOC_ZIGBEE_MNUM, 1, DDM_PmMode)
//zigbee获取模块类型
#define DDM_IOC_ZIGBEE_GET_MODTYPE      _IOR(DDM_IOC_ZIGBEE_MNUM, 2, unsigned int)

/******************************* 数据结构 ******************************/
// zigbee模块类型
typedef enum
{
    DDM_ZIGBEE_MODTYPE_TLINK,           // 泰凌微模块
    DDM_ZIGBEE_MODTYPE_REXENSE,         // 瑞瀛模块
    DDM_ZIGBEE_MODTYPE_MAX,             //最大值 必须为最后一个
} DDM_zigbeeGetModtype;

/*********************************************************************
 ******************************* DDM_sysrq ******************************
 *********************************************************************/

/******************************* 宏定义 ******************************/
#define DDM_DEV_SYSRQ_NAME              "/dev/DDM/sysrq"
#define DDM_IOC_SYSRQ_MNUM              'S'

//sysrq增加线程信息
#define DDM_IOC_SYSRQ_ADD_THREAD        _IOW(DDM_IOC_SYSRQ_MNUM, 0, DDM_sysrqInfo)
//sysrq删除线程信息
#define DDM_IOC_SYSRQ_DEL_THREAD        _IOW(DDM_IOC_SYSRQ_MNUM, 1, unsigned int)
/******************************* 数据结构 ******************************/
typedef struct
{
    unsigned int    id;                 // id键名称
    unsigned char   name[32];           // name值
    unsigned char   rfu[4];             // 预留
} DDM_sysrqInfo;

/*********************************************************************
 ******************************* DDM_beep ******************************
 *********************************************************************/

/******************************* 宏定义 ******************************/
#define DDM_DEV_BEEP_NAME              	"/dev/DDM/beep"
#define DDM_IOC_BEEP_MNUM              	'B'

// 打开beep
#define DDM_IOC_BEEP_ON    				_IOW(DDM_IOC_BEEP_MNUM, 0, unsigned int)
// 关掉beep
#define DDM_IOC_BEEP_OFF    			_IOW(DDM_IOC_BEEP_MNUM, 1, unsigned int)


/*********************************************************************
 ******************************* DDM_usb ******************************
 *********************************************************************/

/******************************* 宏定义 ******************************/
#define DDM_DEV_USB_NAME              	"/dev/DDM/usb"
#define DDM_IOC_USB_MNUM              	'U'

// 通过端口号设置USB电源参数
#define DDM_IOC_USB_SET_POWER_BY_PORT   _IOW(DDM_IOC_USB_MNUM, 0, DDM_usbSetPort)
// 通过节点名设置USB电源参数
#define DDM_IOC_USB_SET_POWER_BY_NODE   _IOW(DDM_IOC_USB_MNUM, 1, DDM_usbSetNode)
// 通过VID&PID设置USB电源参数
#define DDM_IOC_USB_SET_POWER_BY_ID   	_IOW(DDM_IOC_USB_MNUM, 2, DDM_usbSetID)


/******************************* 数据结构 ******************************/

typedef struct
{
	unsigned char  port;				//usb端口
	unsigned char  val;					//电源开关
}DDM_usbSetPort;

typedef struct
{
	unsigned char  node[32];		    //usb设备挂载的节点名
	unsigned char  val;					//电源开关
}DDM_usbSetNode;

typedef struct
{
	unsigned int   vendor;				//设备VID
	unsigned int   product;				//设备PID
	unsigned char  val;					//电源开关
}DDM_usbSetID;

/*********************************************************************
 ******************************* DDM_camera ******************************
 *********************************************************************/
/* ！！！注意：此模块仅供DSP同事使用，APP同事请勿使用 */
/******************************* 宏定义 ******************************/
#define DDM_DEV_CAMERA_NAME              "/dev/DDM/camera"
#define DDM_IOC_CAMERA_MNUM              'C'
//camera 复位、休眠、使能管理
#define DDM_IOC_CAMERA_POWER_MANAGE      _IOW(DDM_IOC_CAMERA_MNUM, 0, DDM_CamPmArgs)
//camera MIPI通道切换
#define DDM_IOC_CAMERA_SWITCH_CHANNEL    _IOW(DDM_IOC_CAMERA_MNUM, 1, DDM_CamSwArgs)

/******************************* 数据结构 ******************************/
//电源管理模式
typedef enum
{
    DDM_CAM_VISIBLE= 0,                 // 可见光
    DDM_CAM_INFRARED,                   // 红外
    DDM_CAM_IRIS,                    	// 虹膜
    DDM_CAM_QR,                    	    // 二维码
    DDM_CAM_TYPE_MAX,                     // 最大值
} DDM_camType;

typedef enum
{
    DDM_CAM_PM_RESET= 0,                // 复位管理
    DDM_CAM_PM_PWDN,                    // 休眠管理
    DDM_CAM_PM_EN,                    	// 使能管理
    DDM_CAM_PM_MAX,                     // 最大值
} DDM_camPmMode;

typedef struct
{
    unsigned char index;                // 同类型摄像头索引编号,从0开始
    unsigned char level;                // 索引编号对应io的电平值
    unsigned char reserve[6];           // 预留
} DDM_camSetLevel;

typedef struct
{
    unsigned char index;                // 索引编号,从0开始
    unsigned char sel;                	// 索引编号对应sel电平值
	unsigned char xsd;           		// 索引编号对应xsd电平值
	unsigned char reserve[5];           // 预留
} DDM_camSwitchChannel;

//camera 电源管理参数
typedef struct
{
    unsigned char   type;               // 摄像头类型，@see DDM_camType
	unsigned char 	mode;				// 管脚类型，@see DDM_camPmMode
	unsigned char reserve[6];   		// 预留
    DDM_camSetLevel level; 			    // 电平配置
} DDM_CamPmArgs;

//camera MIPI通道切换参数
typedef struct
{
    DDM_camSwitchChannel sw[4];			// 最大支持4路sensor
	unsigned char reserve[16];   		// 预留
} DDM_CamSwArgs;

/*********************************************************************
 ******************************* DDM_heat ******************************
 *********************************************************************/

/******************************* 宏定义 ******************************/
#define DDM_DEV_HEAT_NAME             "/dev/DDM/heat"
#define DDM_IOC_HEAT_MNUM             'H'

//设置Camera Lans加热开关
#define DDM_IOC_HEAT_LENS     	_IOW(DDM_IOC_HEAT_MNUM, 0, DDM_HeatArgs)
//设置CPU加热开关
#define DDM_IOC_HEAT_CPU        _IOW(DDM_IOC_HEAT_MNUM, 1, DDM_HeatArgs)
//设置电池加热开关
#define DDM_IOC_HEAT_BATTERY    _IOW(DDM_IOC_HEAT_MNUM, 2, DDM_HeatArgs)

/******************************* 数据结构 ******************************/
//heat 模块设置参数
typedef struct
{
    unsigned char power;            // 电源 取值0关/1开
	unsigned char ch;               // 通道号 从0开始
	unsigned char reserve[6];       // 预留
} DDM_HeatArgs;

/*********************************************************************
 ******************************* DDM_motor ******************************
 *********************************************************************/

/******************************* 宏定义 ******************************/
#define DDM_DEV_MOTOR_NAME        "/dev/DDM/motor"
#define DDM_IOC_MOTOR_MNUM        'M'
// 电机微步控制
#define DDM_IOC_MOTOR_MICROSTEP        _IOW(DDM_IOC_MOTOR_MNUM, 0, DDM_MotorArgs)
// 电机连续控制
#define DDM_IOC_MOTOR_CONTINUESTEP     _IOW(DDM_IOC_MOTOR_MNUM, 1, DDM_MotorArgs)
// 电机停机
#define DDM_IOC_MOTOR_STOP             _IOW(DDM_IOC_MOTOR_MNUM, 2, DDM_MotorSTArgs)
// 电机刹车
#define DDM_IOC_MOTOR_BRAKE            _IOW(DDM_IOC_MOTOR_MNUM, 3, DDM_MotorSTArgs)
// 电机参数配置
#define DDM_IOC_MOTOR_CONFIGURE        _IOW(DDM_IOC_MOTOR_MNUM, 4, DDM_MotorCFArgs)
// 电机归零
#define DDM_IOC_MOTOR_RETURN_TO_ZERO   _IOW(DDM_IOC_MOTOR_MNUM, 5, DDM_MotorChanel)
// 获取光电门值
#define DDM_IOC_MOTOR_GET_PHOTOGATE    _IOW(DDM_IOC_MOTOR_MNUM, 6, DDM_MotorPhotoGate)
// 获取电机状态
#define DDM_IOC_MOTOR_GET_STATE        _IOW(DDM_IOC_MOTOR_MNUM, 7, DDM_MotorState)
/******************************* 数据结构 ******************************/

//电机通道
typedef enum
{
    chanel_1 = 1,                                   //通道1
    chanel_2,                                       //通道2
} DDM_MotorChanel;

//电机状态
typedef enum
{
    MOTOR_NORMAL = 0,                               //正常状态
    MOTOR_STOP,                                     //停止状态
    MOTOR_BRAKE,                                    //刹车状态
    MOTOR_ROTATION,                                 //转动状态
    MOTOR_ERROR,                                    //异常状态
} DDM_MotorState;

//电机转向
typedef enum
{
    FORWARD_ROTATION = 0,                           //正转
    REVERSE_ROTATION,                               //反转
} DDM_MotorDirection;

//光电门值
typedef struct
{
    unsigned int          value_1;                  //第一路电机光电门值
    unsigned int          value_2;
    unsigned int          value_3;
    unsigned char         reserve[4];               // 预留
} DDM_MotorPhotoGate;

//Motor 状态参数
typedef struct
{
    DDM_MotorChanel         motor_chanel;           // 电机通道
    DDM_MotorState          state;                  // 电机状态
    unsigned char           reserve[8];             // 预留
} DDM_MotorSTArgs;

//Motor 配置参数
typedef struct
{
    DDM_MotorChanel         motor_chanel;           // 电机通道
    unsigned int            stepping_config;        // 步进数
    unsigned int            step_period_config;     // 步进周期
    unsigned int            current_output_config;  // 输出电流
    unsigned char           reserve[8];             // 预留
} DDM_MotorCFArgs;

//Motor 运动参数
typedef struct
{
    DDM_MotorChanel         motor_chanel;           // 电机通道
    unsigned int            step_count;             // 步数
    unsigned int            stepping_config;        // 步进数
    unsigned int            step_period_config;     // 步进周期
    unsigned int            VD_count;               // VD脉冲数
    DDM_MotorDirection      direction;              // 转向
    unsigned char           reserve[8];             // 预留
} DDM_MotorArgs;

/*********************************************************************
 ******************************* DDM_switch ******************************
 *********************************************************************/

/******************************* 宏定义 ******************************/
#define DDM_DEV_SWITCH_NAME             "/dev/DDM/switch"
#define DDM_IOC_SWITCH_MNUM             'S'

//获取拨码开关通道个数
#define DDM_IOC_SWITCH_GET_NUM          _IOR(DDM_IOC_SWITCH_MNUM, 0, unsigned int)
//获取指定通道拨码开关码值
#define DDM_IOC_SWITCH_GET_CODE         _IOR(DDM_IOC_SWITCH_MNUM, 1, DDM_SwitchGetCode)

/******************************* 数据结构 ******************************/
//switch 模块设置参数
typedef struct
{
    unsigned int ch;             // 拨码开关通道 从0开始
    unsigned int code;           // 拨码开关码值
    unsigned char reserve[4];    // 预留
} DDM_SwitchGetCode;

#endif
