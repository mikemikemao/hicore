/******************************************************************************
 @note HangZhou Hikvision Digital Technology Co., Ltd. All Right Reserved.
******************************************************************************
@file  : opdevsdk_hardware.h
@brief : opdevsdk_hardware.h header file
@warning : Special notes that need to pay attention to when using and modifying the file.
@history : <data>  <author>    <note>
            2020-5-16    koumingshun   Create the file

******************************************************************************/

#ifndef __OPDEVSDK_HARDWARE_H__
#define __OPDEVSDK_HARDWARE_H__

/*----------------------------------------------*
* Included Header        *
*----------------------------------------------*/
#include "stdio.h"
#include <stdarg.h>
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif


/*----------------------------------------------*
* Define          *
*----------------------------------------------*/
/**@brief errno
 */
#define OPDEVSDK_ERR_HWIF_OK               (0)     //操作成功
#define OPDEVSDK_ERR_ERR_HWIF_DEV_ERR      (-1)     //操作失败


/**@brief RF
 */
#define OP_DEVSDK_RF_DEV_NAME               "/dev/DDM/rf"               //13.56M射频节点
#define OP_DEVSDK_RF_125_DEV_NEAME          "/dev/DDM/rf125k"           //125k射频节点


/**@brief RS485
 */
#define OP_DEVSDK_RS485_DEV_NAME            "/dev/DDM/rs485"           //第一轮RS485节点
#define OP_DEVSDK_RS485_2_DEV_NAME           "/dev/DDM/rs485_2"           //第二路RS485节点

/**@brief weigand
 */
#define OP_DEVSDK_WIEGAND_DEV_NAME             "/dev/DDM/wiegand"           //第一路weigand节点
#define OP_DEVSDK_WIEGAND_2_DEV_NAME           "/dev/DDM/wiegand_2"         //第二路weigand节点
#define OP_DEVSDK_WIEGAND_3_DEV_NAME           "/dev/DDM/wiegand_3"         //第三路weigand节点
#define OP_DEVSDK_WIEGAND_4_DEV_NAME           "/dev/DDM/wiegand_4"         //第四路weigand节点


/*----------------------------------------------*
* Macros          *
*----------------------------------------------*/


/*----------------------------------------------*
* Struct/Enum Definition      *
*----------------------------------------------*/

/**@brief rtc time
    */
typedef struct
{
    unsigned short year;   //!< year [1970, 65535]   HPR_UINT16
    unsigned char month;   //!< month [1 ~ 12]
    unsigned char day;    //!< day [1 ~ 31]
    unsigned char hour;    //!< hour [0 ~ 23]
    unsigned char minute;   //!< minute [0 ~ 59]
    unsigned char second;   //!< second [0, 59]
    unsigned char rfu[5];   //!< rfu reserved for future use
}OPDEVSDK_ST_RTC;

/**@brief alarm in 报警输入的最大值 < OPDEVSDK_EN_ALARM_IN_MAX，防拆的最小值 > OPDEVSDK_EN_ALARM_IN_MIN
    */
typedef enum
{
    OPDEVSDK_EN_ALARM_IN_MIN = -3,
    OPDEVSDK_EN_ALARM_IN_TAMPER3 = -2,     // 防拆3
    OPDEVSDK_EN_ALARM_IN_TAMPER2 = -1,     // 防拆2
    OPDEVSDK_EN_ALARM_IN_TAMPER = 0,     // 防拆
    OPDEVSDK_EN_ALARM_IN_NUM1 = 1,      // 报警输入1
    OPDEVSDK_EN_ALARM_IN_NUM2 = 2,      // 报警输入2
    OPDEVSDK_EN_ALARM_IN_NUM3 = 3,      // 报警输入3
    OPDEVSDK_EN_ALARM_IN_NUM4 = 4,      // 报警输入4
    OPDEVSDK_EN_ALARM_IN_NUM5 = 5,      // 报警输入5
    OPDEVSDK_EN_ALARM_IN_NUM6 = 6,      // 报警输入6
    OPDEVSDK_EN_ALARM_IN_NUM7 = 7,      // 报警输入7
    OPDEVSDK_EN_ALARM_IN_NUM8 = 8,      // 报警输入8
    OPDEVSDK_EN_ALARM_IN_MAX = 33
}OPDEVSDK_EN_ALARM_IN_TYPE;

/**@brief alarm out 报警输出的最大值 < OPDEVSDK_EN_ALARM_OUT_MAX
    */
typedef enum
{
    OPDEVSDK_EN_ALARM_OUT_NUM1 = 1,      // 报警输出1
    OPDEVSDK_EN_ALARM_OUT_NUM2 = 2,      // 报警输出2
    OPDEVSDK_EN_ALARM_OUT_NUM3 = 3,      // 报警输出3
    OPDEVSDK_EN_ALARM_OUT_NUM4 = 4,      // 报警输出4
    OPDEVSDK_EN_ALARM_OUT_MAX = 33,
}OPDEVSDK_EN_ALARM_OUT_TYPE;



/**@brief door sensor
    */
typedef enum
{
    OPDEVSDK_EN_DOOR_SENSOR_NUM1 = 1,      // 门磁输入检测1
    OPDEVSDK_EN_DOOR_SENSOR_NUM2 = 2,      // 门磁输入检测2
    OPDEVSDK_EN_DOOR_SENSOR_NUM3 = 3,      // 门磁输入检测3
    OPDEVSDK_EN_DOOR_SENSOR_NUM4 = 4,      // 门磁输入检测4
    OPDEVSDK_EN_DOOR_SENSOR_MAX
}OPDEVSDK_EN_DOOR_SENSOR_TYPE;

/**@brief door button
    */
typedef enum
{
    OPDEVSDK_EN_DOOR_BUTTON_NUM1 = 1,      // 开门按钮1
    OPDEVSDK_EN_DOOR_BUTTON_NUM2 = 2,      // 开门按钮2
    OPDEVSDK_EN_DOOR_BUTTON_NUM3 = 3,      // 开门按钮3
    OPDEVSDK_EN_DOOR_BUTTON_NUM4 = 4,      // 开门按钮4
    OPDEVSDK_EN_DOOR_BUTTON_MAX
}OPDEVSDK_EN_DOOR_BUTTON_TYPE;

/**@brief door lock
    */
typedef enum
{
    OPDEVSDK_EN_DOOR_LOCK_CLOSE = 0,    // 关锁
    OPDEVSDK_EN_DOOR_LOCK_OPEN = 1,     // 开锁
    OPDEVSDK_EN_DOOR_LOCK_UNKNOWN,
}OPDEVSDK_EN_DOOR_LOCK_OPT;


/*卡片安全认证结果，lihongwei6*/
typedef enum
{
    OPDEVSDK_EN_RF_ANTI_COPY_AUTH_OK               = 0, //认证通过
    OPDEVSDK_EN_RF_ANTI_COPY_AUTH_M1_FAIL          = 1, // M1秘钥校验失败
    OPDEVSDK_EN_RF_ANTI_COPY_AUTH_UID_CARD         = 2, // UID卡
    OPDEVSDK_EN_RF_ANTI_COPY_AUTH_NFC_CARD         = 3, // NFC卡
    OPDEVSDK_EN_RF_ANTI_COPY_AUTH_READ_FIEL_FAIL   = 5, // 读内容失败
    OPDEVSDK_EN_RF_ANTI_COPY_AUTH_RESULT_E_DISABLE = 6, // EM卡失能
    OPDEVSDK_EN_RF_ANTI_COPY_AUTH_RESULT_M_DISABLE = 7, // M1卡失能
    OPDEVSDK_EN_RF_ANTI_COPY_AUTH_RESULT_C_DISABLE = 8, // CPU卡失能
    OPDEVSDK_EN_RF_ANTI_COPY_AUTH_RESULT_S_DISABLE = 9, // ID卡失能
    OPDEVSDK_EN_RF_ANTI_COPY_UNKNOW,
} OPDEVSDK_EN_RF_ANTI_COPY;

/**@brief rf card type
    */
typedef enum
{
    OPDEVSDK_EN_RF_CARD_TYPE_CPU = 0,    // CPU卡
    OPDEVSDK_EN_RF_CARD_TYPE_MIFARE = 1,   // MIFARE卡
    OPDEVSDK_EN_RF_CARD_TYPE_EM = 2,    // EM卡
    OPDEVSDK_EN_RF_CARD_TYPE_ID = 3,    // ID卡
    OPDEVSDK_EN_RF_CARD_TYPE_FELICA = 4,    // Felica卡
    OPDEVSDK_EN_RF_CARD_TYPE_DESFIRE = 5,    // Desfire卡
    OPDEVSDK_EN_RF_CARD_TYPE_UNKNOWN,
}OPDEVSDK_EN_RF_CARD_TYPE;

/**@brief rf data
    */
typedef struct
{
    OPDEVSDK_EN_RF_CARD_TYPE enumType;    // 卡类型
    char byDataBuf[128];    // 用于存储卡号缓冲区
    int  iBuflen;        // 存储卡号缓冲区的长度
    OPDEVSDK_EN_RF_ANTI_COPY enumAntiCopyResult;
    char byRes[64];
}OPDEVSDK_ST_RF_DATA;

/**@brief rs485 param
    */
typedef struct
{
    unsigned int dwBaudRate;    // 波特率(bps)，0-50，1-75，2-110，3-150，4-300，5-600，6-1200，7-2400，8-4800，9-9600，10-19200，11-38400，12-57600，13-76800，14-115.2k
    char byDataBit;       // 数据有几位：0-5位，1-6位，2-7位，3-8位
    char byStopBit;       // 停止位：0-1位，1-2位
    char byParity;       // 是否校验：0-无校验，1-奇校验，2-偶校验
    char byFlowcontrol;      // 是否流控：0-无，1-软流控,2-硬流控
    char byDuplex;       // 0 - 半双工1- 全双工 只有通道可以是全双工其他都只能是半双工
    char byAddress;       // 485地址
    char res[6];
}OPDEVSDK_ST_RS485_PARAM;

typedef struct
{ /* 8 bytes */
    unsigned char byWiegandEnable;   // 韦根使能
    unsigned char byCommunicateDirection; //0: 接收  1:发送
    unsigned char byRes1[2];
    unsigned int  dwPulseWide;    //韦根输出负脉冲宽度 单位  us(部分设备精度只能达到10us，该情况向下取整)  默认值为 50us 设置成0为默认值
    unsigned int  dwPulseGap;    //韦根脉冲输出间隔时间 单位 us(部分设备精度只能达到100us，该情况向下取整) 默认值为  2ms  设置成0位默认值
    unsigned char byRes[4];
}OPDEVSDK_ST_WIEGAND_PARAM;

/**@brief light type
*/
typedef enum
{
    OPDEVSDK_EN_LIGHT_TYPE_VIS = 1,
	OPDEVSDK_EN_LIGHT_TYPE_IR,
	OPDEVSDK_EN_LIGHT_TYPE_IRIS,
    OPDEVSDK_EN_LIGHT_TYPE_UNKNOWN,
}OPDEVSDK_EN_LIGHT_TYPE;

typedef enum
{
    OPDEVSDK_PRINT_LEVEL_INVALID = -1,   //无效的等级
    OPDEVSDK_PRINT_LEVEL_DBG = 0,
    OPDEVSDK_PRINT_LEVEL_INFO,
    OPDEVSDK_PRINT_LEVEL_CRIT,
    OPDEVSDK_PRINT_LEVEL_ERROR,
}OPDEVSDK_PRINT_LEVEL;


typedef enum
{
    OPDEVSDK_EN_POWER_CTRL_STOP = 0, //关闭
    OPDEVSDK_EN_POWER_CTRL_START = 1, //开启
    OPDEVSDK_EN_POWER_CTRL_DELAY = 2, // 延迟复位
    OPDEVSDK_EN_POWER_CTRL_RESET = 3, // 直接复位
}OPDEVSDK_EN_POWER_CTRL;

/*----------------------------------------------*
* Function Declare         *
*----------------------------------------------*/

/* @fn  : opdevsdk_hwif_basic_init
*  @brief ：hardware basic init
        user can call this function to get the capabilities of hardware

* @return : -1--error, 0--ok
*/
int opdevsdk_hwif_basic_init(void);


/** @fn   : opdevsdk_hwif_rtc_get
* @brief  : get rtc time
* @param[in] : NA
* @param[out] : OPDEVSDK_ST_RTC *pRtc
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_rtc_get(struct    tm *pTm);

/** @fn   : opdevsdk_hwif_alarm_in_get_status
* @brief  : get alarm in status
* @param[in] : OPDEVSDK_EN_ALARM_IN_TYPE enumType
* @return  : -1--error, 0--no trigger, 1--trigger
*/
int opdevsdk_hwif_alarm_in_get_status(OPDEVSDK_EN_ALARM_IN_TYPE enumType);


/** @fn   : opdevsdk_hwif_alarm_out_set_status
* @brief  : set alarm out status
* @param[in] : OPDEVSDK_EN_ALARM_OUT_TYPE enumType
* @param[in] : value 报警输出状态值 0-无报警，1-有报警
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_alarm_out_set_status(OPDEVSDK_EN_ALARM_OUT_TYPE enumType, int value);


/** @fn   : opdevsdk_hwif_door_sensor_get_status
* @brief  : get door sensor status
* @param[in] : NA
* @return  : -1--error, 0--door close, 1--door open
*/
int opdevsdk_hwif_door_sensor_get_status(void);

/** @fn   : opdevsdk_hwif_door_sensor_get_status_ex
* @brief  : get door sensor status
* @param[in] : OPDEVSDK_EN_DOOR_SENSOR_TYPE
* @return  : -1--error, 0--door close, 1--door open
*/
int opdevsdk_hwif_door_sensor_get_status_ex(OPDEVSDK_EN_DOOR_SENSOR_TYPE enumType);


/** @fn   : opdevsdk_hwif_door_button_get_status
* @brief  : get door button status
* @param[in] : NA
* @return  : -1--error, 0--no trigger, 1--trigger
*/
int opdevsdk_hwif_door_button_get_status(void);

/** @fn   : opdevsdk_hwif_door_button_get_status_ex
* @brief  : get door button status
* @param[in] : OPDEVSDK_EN_DOOR_BUTTON_TYPE
* @return  : -1--error, 0--no trigger, 1--trigger
*/
int opdevsdk_hwif_door_button_get_status_ex(OPDEVSDK_EN_DOOR_BUTTON_TYPE enumType);


/** @fn   : opdevsdk_hwif_door_lock_set_status
* @brief  : set door lock status
* @param[in] : OPDEVSDK_EN_DOOR_LOCK_OPT enumOpt
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_door_lock_set_status(OPDEVSDK_EN_DOOR_LOCK_OPT enumOpt);

/** @fn   : opdevsdk_hwif_door_lock_set_status
* @brief  : set door lock status
* @param[in] : byCh 通道 从1 开始
* @param[in] : OPDEVSDK_EN_DOOR_LOCK_OPT enumOpt
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_door_lock_set_status_ex(int byCh, OPDEVSDK_EN_DOOR_LOCK_OPT enumOpt);


/** @fn   : opdevsdk_hwif_lcd_set_backlight
* @brief  : set lcd backlight value
* @param[in] : value 0~99
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_lcd_set_backlight(int value);


/** @fn   : opdevsdk_hwif_light_set_value
* @brief  : set lighte bright value
* @param[in] : OPDEVSDK_EN_LIGHT_TYPE enumType
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_light_set_value(OPDEVSDK_EN_LIGHT_TYPE enumType, int value);


/** @fn   : opdevsdk_hwif_rf_open
* @brief  : open rf dev
* @param[in] : *pathName  OP_DEVSDK_RF_DEV_NAME/OP_DEVSDK_RF_125_DEV_NEAME
* @return  : fd
*/
int opdevsdk_hwif_rf_open(const char *pathName);


/** @fn   : opdevsdk_hwif_rf_close
* @brief  : close rf dev
* @param[in] : fd
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_rf_close(int fd);


/** @fn   : opdevsdk_hwif_rf_read
* @brief  : read rf data
* @param[in] : fd
* @param[in] : timeval *timeout
* @param[out] : OPDEVSDK_ST_RF_DATA *pRfData
* @return  : -1--error, 其他值：表示读到的卡号数据长度
*/
int opdevsdk_hwif_rf_read(int fd, OPDEVSDK_ST_RF_DATA *pRfData, int iTimeMs);


/** @fn   : opdevsdk_hwif_rs485_open
* @brief  : open rs485 dev
* @param[in] : *pathName  OP_DEVSDK_RS485_DEV_NAME
* @return  : fd
*/
int opdevsdk_hwif_rs485_open(const char *pathName);


/** @fn   : opdevsdk_hwif_rs485_close
* @brief  : close rs485 dev
* @param[in] : fd
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_rs485_close(int fd);


/** @fn   : opdevsdk_hwif_rs485_read
* @brief  : read rs485 data
* @param[in] : fd
* @param[in] : len, support max len, default 128
* @param[in] : timeval *timeout
* @param[out] : *pBuf
* @return  : -1--error, 其他值：表示读到的数据长度
*/
int opdevsdk_hwif_rs485_read(int fd, char *pBuf, int len, int iTimeMs);


/** @fn   : opdevsdk_hwif_rs485_write
* @brief  : write rs485 data
* @param[in] : fd
* @param[in] : *pBuf
* @param[in] : len, data len
* @return  : -1--error, 其他值：表示写入的数据长度
*/
int opdevsdk_hwif_rs485_write(int fd, char *pBuf, int len);


/** @fn   : opdevsdk_hwif_rs485_get_param
* @brief  : get rs485 params
* @param[in] : fd
* @param[out] : *param
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_rs485_get_param(int fd, OPDEVSDK_ST_RS485_PARAM *param);


/** @fn   : opdevsdk_hwif_rs485_set_param
* @brief  : set rs485 params
* @param[in] : fd
* @param[in] : *param
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_rs485_set_param(int fd, OPDEVSDK_ST_RS485_PARAM *param);


/** @fn   : opdevsdk_hwif_wiegand_open
* @brief  : open wiegand dev
* @param[in] : *pathName  OP_DEVSDK_RS485_DEV_NAME
* @return  : success:fd  fail:-1
*/
int opdevsdk_hwif_wiegand_open(char *pathName);


/** @fn   : opdevsdk_hwif_wiegand_close
* @brief  : close wiegand dev
* @param[in] : fd
* @return  : op_devsdk_errno_code
*/

int opdevsdk_hwif_wiegand_close(int fd);


/** @fn   : opdevsdk_hwif_wiegand_read
* @brief  : 读取wiegand bit 流，格式如下
            bitSize:缓存的数据长度
            假设读取到pBuf[0]:00111101
            pBuf[1]:10010011
            pBuf[2]:00000100
            return bitlen = 11
            则 原数据为：100 10010011 00111101

* @param[in] : fd:wiegand设备的fd
                pBuf:bit数据流缓存
                iByteLen:缓存数据长度
* @param[out] : *pBuf
* @return  :  -1：读取失败，0：iTimeMs    >0:读到的位(bit)长度
*/

int opdevsdk_hwif_wiegand_read(int fd, char *pBuf, int iByteLen, int iTimeMs);


/** @fn   : opdevsdk_hwif_wiegand_write
* @brief  : 发送wiegand bit 流，格式如下
            假设原数据bit流：100 10010011 00111101
            则 pBuf[0]:00111101
                pBuf[1]:10010011
                pBuf[2]:00000100
            bitSize:11

* @param[in] : fd
* @param[in] : *pBuf
* @param[in] : iBitLen, data len
* @return  : -1--error, 0--success
*/
int opdevsdk_hwif_wiegand_write(int fd,char *pBuf, int iBitLen);



/** @fn   : opdevsdk_hwif_wiegand_get_param
* @brief  : get wiegand params
* @param[in] : fd
                OP_DEVSDK_WIEGAND_CFG_T *pCfg
* @param[out] : *param
* @return  : fail:-1  suc:0
*/

int opdevsdk_hwif_wiegand_get_param(int fd, OPDEVSDK_ST_WIEGAND_PARAM *param);


/** @fn   : opdevsdk_hwif_wiegand_set_param
* @brief  : set wiegand params
* @param[in] : fd
* @param[in] : OPDEVSDK_ST_WIEGAND_PARAM *pCfg
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_wiegand_set_param(int fd, OPDEVSDK_ST_WIEGAND_PARAM *param);

/** @fn   : opdevsdk_hwif_set_print_level
* @brief  : set opdevsdk lib print level
* @param[in] : level: DGB  INFO CRIT ERROR
* @return  : none
*/
void opdevsdk_hwif_set_print_level(OPDEVSDK_PRINT_LEVEL level);

/*******************************************
以下开始为二维码接口
*******************************************/

#define OP_DEVSDK_QRCODE_DEV_NAME            "/dev/DDM/qrcode"           //第一路二维码节点


typedef struct
{
    unsigned int  iChannel;                  //!通道
    OPDEVSDK_EN_POWER_CTRL   enumOpt;  //!<  工作模式 @see OPDEVSDK_EN_POWER_CTRL
    unsigned int  iDelayTime;                  // 延迟时间
    unsigned char    res[32];       //!< reserved
}OPDEVSDK_ST_QRCODE_POWER;


/** @fn      : opdevsdk_hwif_qrcode_power_ctrl
* @brief   : 二维码 电源控制
* @param[in]  : pstruParam
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_qrcode_power_ctrl(OPDEVSDK_ST_QRCODE_POWER* pstruParam );

/** @fn   : opdevsdk_hwif_qrcode_open
* @brief  : open qrcode dev
* @param[in] : *pathName  OP_DEVSDK_QRCODE_DEV_NAME
* @return  : fd
*/
int opdevsdk_hwif_qrcode_open(const char *pathName);


/** @fn   : opdevsdk_hwif_qrcode_close
* @brief  : close qrcode dev
* @param[in] : fd
* @return  : -1---error or 0-success
*/
int opdevsdk_hwif_qrcode_close(int fd);


/** @fn   : opdevsdk_hwif_qrcode_read
* @brief  : read qrcode data
* @param[in] : fd
* @param[in] : len, support max len, default 128
* @param[in] : timeval *timeout
* @param[out] : *pBuf
* @return  : -1--error, 其他值：表示读到的数据长度
*/
int opdevsdk_hwif_qrcode_read(int fd, char *pBuf, int len, int iTimeMs);

/** @fn   : opdevsdk_hwif_qrcode_get_uart_param
* @brief  : get qrcode uart params,仅对串口形式接入的二维码有效
* @param[in] : fd
* @param[out] : *param
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_qrcode_get_uart_param(int fd, OPDEVSDK_ST_RS485_PARAM *param);


/** @fn   : opdevsdk_hwif_qrcode_set_uart_param
* @brief  : set qrcode uart params,仅对串口形式接入的二维码有效
* @param[in] : fd
* @param[in] : *param
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_qrcode_set_uart_param(int fd, OPDEVSDK_ST_RS485_PARAM *param);

#ifdef __cplusplus
}
#endif

#endif