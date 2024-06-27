/******************************************************************************
 @note HangZhou Hikvision Digital Technology Co., Ltd. All Right Reserved.
******************************************************************************
@file  : opdevsdk_hardware_ex.h
@brief : opdevsdk_hardware_ex.h header file
@warning : Special notes that need to pay attention to when using and modifying the file.
@history : <data>  <author>    <note>
    2021-4-7    baozhonghui   Create the file

******************************************************************************/

#ifndef __OPDEVSDK_HARDWARE_EX_H__
#define __OPDEVSDK_HARDWARE_EX_H__

/*----------------------------------------------*
* Included Header        *
*----------------------------------------------*/
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include "opdevsdk_hardware.h"
#ifdef __cplusplus
extern "C" {
#endif
#define OP_DEVSDK_GASAM_ID_DEV_NAME               "/dev/DDM/gsam"               //GASAM_ID节点
#define OP_DEVSDK_WDT_DEV_NAME              "/dev/DDM/wdt"               //wdt节点
#define OP_DEVSDK_SE_DEV_NAME              "/dev/DDM/se"               //se节点
#define OP_DEVSDK_SAM_DEV_NAME              "/dev/DDM/sam"               //se节点
#define OP_DEVSDK_FINGERPRINT_DEV_NAME            "/dev/DDM/fingerprint"  // finger节点

/*----------------------------------------------*
* Define          *
*----------------------------------------------*/


/*----------------------------------------------*
* Macros          *
*----------------------------------------------*/


typedef enum
{
    OPDEVSDK_EN_SEC_CAM_PARA = 0,  //摄像头标定信息
    OPDEVSDK_EN_SEC_SECRET_PARA,  //app根密钥信息
    OPDEVSDK_EN_SEC_TEMP_PARA,  //测温模块标定信息
    OPDEVSDK_EN_SEC_EZVIZ_INFO, //萤石DeviceID相关信息
    OPDEVSDK_EN_SEC_TOF_PARA,  //TOF标定信息
    OPDEVSDK_EN_SEC_VCM_PARA,
    OPDEVSDK_EN_SEC_ID_KEY,   //身份证秘钥信息
    OPDEVSDK_EN_SEC_INV,
} OPDEVSDK_EN_SEC_TYPE;

typedef enum
{
    OPDEVSDK_EN_SEC_READ = 0,
    OPDEVSDK_EN_SEC_WRITE,
} OPDEVSDN_EN_SEC_WR;

typedef struct
{
    OPDEVSDN_EN_SEC_WR eSecWr;
    OPDEVSDK_EN_SEC_TYPE eSecType;
    unsigned char *data;
    unsigned int  len;
} OPDEVSDK_ST_SEC_INFO;

/* fingerprint 输出参数集 */
typedef struct
{
    unsigned char   byFingerStatus;       //!<手指检测状态
    unsigned char   *pbyData;               //!<指纹数据
    unsigned char   byRes[6];              //!< reserved
} OPDEVSDK_ST_FP_GET_IMAGE;

/* fingerprint图像尺寸接口 */
typedef struct
{
    unsigned short  wWidth;
    unsigned short  wHeight;
    unsigned char   byBitWidth;
    unsigned int    iImageSize;
} OPDEVSDK_ST_FP_GET_IMAGE_SIZE;


typedef enum
{
    OPDEVSDK_EN_WDT_STATUS_STOP = 0,
    OPDEVSDK_EN_WDT_STATUS_RUNNING = 1
}OPDEVSDK_EN_WDT_STATUS;

/* LED工作模式 */
typedef enum
{
    OPDEVSDK_EN_LED_OPT_OFF,             //!< DDM_LEDMODE_OFF 直接关闭
    OPDEVSDK_EN_LED_OPT_ON,              //!< DDM_LEDMODE_ON  直接打开
    OPDEVSDK_EN_LED_OPT_BRT_OFF,         //!< DDM_LEDMODE_OFF 使用呼吸灯方式关闭
    OPDEVSDK_EN_LED_OPT_BRT_ON,          //!< DDM_LEDMODE_ON  使用呼吸灯方式开启
    OPDEVSDK_EN_LED_OPT_BRT_ALWAYS_ON,   //!< DDM_LEDMODE_ON  使用呼吸灯方式开启
    OPDEVSDK_EN_LED_OPT_UNKNOWN,         //!< 最大值 必须为最后一个
}OPDEVSDK_EN_LED_OPT;

/* LED工作环境 */
typedef enum
{
    OPDEVSDK_EN_LED_ENV_HIGH,        //!<  高照度
    OPDEVSDK_EN_LED_ENV_LOW,         //!<  低照度
    OPDEVSDK_EN_LED_ENV_MAX,        //!< 最大值 必须为最后一个
}OPDEVSDK_EN_LED_ENV;

/**@brief led type
*/
typedef enum
{
    OPDEVSDK_EN_LED_MESSAGE = 1,      //!< OPDEVSDK_EN_LED_MESSAGE  信息LED
    OPDEVSDK_EN_LED_ALARM,          //!< OPDEVSDK_EN_LED_ALARM 报警LED
    OPDEVSDK_EN_LED_UNLOCK,         //!< OPDEVSDK_EN_LED_UNLOCK解锁LED
    OPDEVSDK_EN_LED_KEY,            //!<OPDEVSDK_EN_LED_KEY 按键背光灯LED
    OPDEVSDK_EN_LED_LABLE,          //!<OPDEVSDK_EN_LED_LABLE 标签版背光灯LED
    OPDEVSDK_EN_LED_STATUS,         //!<OPDEVSDK_EN_LED_STATUS 状态显示LED
    OPDEVSDK_EN_LED_STATUS_RED,     //!<OPDEVSDK_EN_LED_STATUS_RED 状态显示LED
    OPDEVSDK_EN_LED_STATUS_BLUE,    //!<OPDEVSDK_EN_LED_STATUS_BLUE 状态显示LED
    OPDEVSDK_EN_LED_STATUS_GREEN,   //!<OPDEVSDK_EN_LED_STATUS_GREEN 状态显示LED
    OPDEVSDK_EN_LED_POWER,          //!<OPDEVSDK_EN_LED_POWER 电源显示LED
    OPDEVSDK_EN_LED_NETWORK,        //!<OPDEVSDK_EN_LED_NETWORK 网络显示LED
    OPDEVSDK_EN_LED_COMMUNICATION,  //!<OPDEVSDK_EN_LED_COMMUNICATION 对讲指示灯LED
    OPDEVSDK_EN_LED_OPENDOOR,       //!<OPDEVSDK_EN_LED_OPENDOOR 开门指示灯LED
    OPDEVSDK_EN_LED_CALL,           //!<OPDEVSDK_EN_LED_CALL 呼叫指示灯LED
    OPDEVSDK_EN_LED_CARD,           //!<OPDEVSDK_EN_LED_CARD 刷卡指示灯LED
    OPDEVSDK_EN_LED_TEL,            //!<OPDEVSDK_EN_LED_TEL 听筒指示灯LED
    OPDEVSDK_EN_LED_KEY_BULE,       //!<OPDEVSDK_EN_LED_KEY_BULE 蓝色按键背光灯LED
    OPDEVSDK_EN_LED_KEY_ORANGE,     //!<OPDEVSDK_EN_LED_KEY_ORANGE 橙色按键背光灯LED
    OPDEVSDK_EN_LED_STATUS_WHITE,   //!<OPDEVSDK_EN_LED_STATUS_WHITE 状态显示LED
    OPDEVSDK_EN_LED_MAX,            //!< 最大值 必须为最后一个
}OPDEVSDK_EN_LED_TYPE;

// 灯的颜色
typedef enum {
    OPDEVSDK_EN_LIGHT_COLOR_WHITE = 0,         //LED显示白色灯
    OPDEVSDK_EN_LIGHT_COLOR_RED,               //LED显示红色灯
    OPDEVSDK_EN_LIGHT_COLOR_GREEN,             //LED显示绿色灯
    OPDEVSDK_EN_LIGHT_COLOR_BLUE,              //LED显示蓝色灯
    OPDEVSDK_EN_LIGHT_COLOR_YELLOW,            //LED显示黄色灯
    OPDEVSDK_EN_LIGHT_COLOR_MAX,               //LED颜色最大值
} OPDEVSDK_EN_LIGHT_COLOR;
/**
* led 输出参数集
*/
typedef struct
{
    OPDEVSDK_EN_LED_TYPE  enumType;  //!<LED 功能
    OPDEVSDK_EN_LED_OPT   enumOpt;  //!< LED 工作模式 @see DDM_ledMode
    OPDEVSDK_EN_LED_ENV   enumEnv;  //!< LED 工作模式 @see DDM_ledMode
    unsigned char   byPwmDuty;   //!< LED PWM接口的占空比设置
    unsigned char    byCh;  //!< chanle
    unsigned char    res1[2];  //!< reserved
    OPDEVSDK_EN_LIGHT_COLOR enumColor; // LED颜色
    unsigned char    res[20];  //!< reserved
}OPDEVSDK_ST_LED_PARAM;

/**<指纹RGB灯的颜色状态*/
typedef enum
{
    OPDEVSDK_EN_FP_RGB_LIGHT_STATUSCLOSE  = 0, //RGB灯全关
    OPDEVSDK_EN_FP_RGB_LIGHT_STATUSRED    = 1, //RGB灯红色
    OPDEVSDK_EN_FP_RGB_LIGHT_STATUSBLUE   = 2, //RGB灯蓝色
    OPDEVSDK_EN_FP_RGB_LIGHT_STATUSGREEN  = 3, //RGB灯绿色
    OPDEVSDK_EN_FP_RGB_LIGHT_STATUSWHITE  = 4, //RGB灯白色
    OPDEVSDK_EN_FP_RGB_LIGHT_STATUSYELLOW = 5, //RGB灯黄色
    OPDEVSDK_EN_FP_RGB_LIGHT_STATUSCYAN   = 6, //RGB灯青色
    OPDEVSDK_EN_FP_RGB_LIGHT_STATUSPINK   = 7  //RGB灯粉色
} OPDEVSDK_EN_FP_RGB_LIGHT_STATUS;


/**
* wiegand信号引脚类型
*/
typedef enum
{
    OPDEVSDK_ST_WIEGAND_SINGAL_TYPE_MIN = 0,
    OPDEVSDK_ST_WIEGAND_SINGAL_TYPE_OK,                  // wiegand OK信号
    OPDEVSDK_ST_WIEGAND_SINGAL_TYPE_ERROR,               // wiegand error信号
    OPDEVSDK_ST_WIEGAND_SINGAL_TYPE_BUZZER,              // wiegand buzzer信号
    OPDEVSDK_ST_WIEGAND_SINGAL_TYPE_TAMPER,              // wiegand tamper信号
    OPDEVSDK_ST_WIEGAND_SINGAL_TYPE_MAX,
} OPDEVSDK_ST_WIEGAND_SINGAL_TYPE;

typedef enum
{
    OPDEVSDK_ST_TCIFLUSH = 0,  //刷新收到的数据但是不读
    OPDEVSDK_ST_TCOFLUSH,  //　刷新写入的数据但是不传送
    OPDEVSDK_ST_TCIOFLUSH,  //　同时刷新收到的数据但是不读，并且刷新写入的数据但是不传送
} OPDEVSDK_ST_TCFLUSH_TYPE;
/**
* wiegand信号引脚
*/
typedef struct
{
    OPDEVSDK_ST_WIEGAND_SINGAL_TYPE    struType;           // wiegand信号引脚类型
    int     iVal;            // 0 - 低电平  1 - 高电平
    int     iValMask;        // 当 struType == OPDEVSDK_ST_WIEGAND_SINGAL_TYPE_MIN该位有效 同时设置所有信号，每个位对应的信号含义参考 OPDEVSDK_ST_WIEGAND_SINGAL_TYPE
    unsigned char           byRes[60];    // Reserve
} OPDEVSDK_ST_WIEGAND_SINGAL_PIN;

typedef enum
{
    OPDEVSDK_EN_WIEGAND_WORK_MODE_PENETRATE = 0,    // 透传模式，上层由应用封装韦根发送数据和解析收到的数据，其余模式由bsp封装发送格式
    OPDEVSDK_EN_WIEGAND_WORK_MODE_KEY = 4,   // 按键模式
    OPDEVSDK_EN_WIEGAND_WORK_MODE_26 = 26,   // 韦根26
    OPDEVSDK_EN_WIEGAND_WORK_MODE_27 = 27,    // 韦根27
    OPDEVSDK_EN_WIEGAND_WORK_MODE_34 = 34,    // 韦根34
    OPDEVSDK_EN_WIEGAND_WORK_MODE_35 = 35,  // 韦根35
    OPDEVSDK_EN_WIEGAND_WORK_MODE_58 = 58,  // 韦根58
    OPDEVSDK_EN_WIEGAND_WORK_MODE_UNKNOWN,
}OPDEVSDK_EN_WIEGAND_WORK_MODE;

typedef enum
{
    OPDEVSDK_EN_SE_RSA_LEN_1024 = 0,
    OPDEVSDK_EN_SE_RSA_LEN_1280,
    OPDEVSDK_EN_SE_RSA_LEN_2048,
    OPDEVSDK_EN_SE_RSA_LEN_MAX,
}  OPDEVSDK_EN_SE_RSA_LEN;

typedef enum
{
    OPDEVSDK_EN_SE_RSA_EXP_65537 = 0,
    OPDEVSDK_EN_SE_RSA_EXP_3,
    OPDEVSDK_EN_SE_RSA_EXP_MAX,
} OPDEVSDK_EN_SE_RSA_EXP;

typedef enum
{
    OPDEVSDK_EN_SE_RANDOMS_LEN_4  = 4,
    OPDEVSDK_EN_SE_RANDOMS_LEN_8  = 8,
    OPDEVSDK_EN_SE_RANDOMS_LEN_10 = 10,
    OPDEVSDK_EN_SE_RANDOMS_LEN_MAX,
} OPDEVSDK_EN_SE_RANDOMS_LEN;

typedef enum
{
    OPDEVSDK_EN_TEMP_BIND_NONE,         //!< OPDEVSDK_EN_TEMP_BIND_NONE 无绑定
    OPDEVSDK_EN_TEMP_BIND_CPU,          //!< cpu附近温度
    OPDEVSDK_EN_TEMP_BIND_BATTERY,      //!< 电池附近温度
    OPDEVSDK_EN_TEMP_BIND_LCM,          //!< 显示屏附近温度
    OPDEVSDK_EN_TEMP_BIND_IRIS,         //!< 虹膜补光灯温度
    OPDEVSDK_EN_TEMP_BIND_DEV,         //!< 设备温度
    OPDEVSDK_EN_TEMP_BIND_MAX,          //!< OPDEVSDK_EN_TEMP_BIND_MAX 必须最后一个
}OPDEVSDK_EN_TEMP_BIND;
/*----------------------------------------------*
* Struct/Enum Definition      *
*----------------------------------------------*/

/**
* 指纹led 输出参数集
*/
typedef struct
{
    OPDEVSDK_EN_FP_RGB_LIGHT_STATUS  enumType;  //!<LED 颜色 byLedType = 0 有效
    unsigned char            byLedType;  //!<LED类型  0 - 状态灯  1 - 补光灯
    unsigned char            byPwmDuty;   //!< LED PWM接口的占空比设置 0~100 0表示关闭  byLedType = 1 有效
    unsigned char            res[30];  //!< reserved
}OPDEVSDK_ST_FINGER_LED_PARAM;


typedef struct
{
    unsigned int  iChannel;                  //!通道
    OPDEVSDK_EN_POWER_CTRL   enumOpt;  //!<  工作模式 @see OPDEVSDK_EN_POWER_CTRL
    unsigned int  iDelayTime;                  // 延迟时间
    unsigned char    res[32];       //!< reserved
}OPDEVSDK_ST_BEEP_CONTROL;



/**
* wifi模块控制参数
*/
typedef struct
{
    int           iEnable;   //    0 - 失能 1 - 使能
    unsigned int  iChannel;                  //!通道
    unsigned char byRes[32]; //!< reserved
} OPDEVSDK_ST_WIFI_CTRL_PARAM;



typedef struct
{
    unsigned int  iChannel;                  //!通道
    OPDEVSDK_EN_POWER_CTRL   enumOpt;  //!<  工作模式 @see OPDEVSDK_EN_POWER_CTRL
    unsigned int  iDelayTime;                  // 延迟时间
    unsigned char    res[32];       //!< reserved
}OPDEVSDK_ST_IDENTITY_POWER;

typedef struct
{
    unsigned int  iChannel;                  //!通道
    OPDEVSDK_EN_POWER_CTRL   enumOpt;  //!<  工作模式 @see OPDEVSDK_EN_POWER_CTRL
    unsigned int  iDelayTime;                  // 延迟时间
    unsigned char    res[32];       //!< reserved
}OPDEVSDK_ST_WIFI_POWER;

typedef struct
{
    unsigned int  iChannel;                  //!通道 当iModel = 0有效
    OPDEVSDK_EN_POWER_CTRL   enumOpt;  //!<  工作模式 @see OPDEVSDK_EN_POWER_CTRL
    unsigned int  iDelayTime;                  // 延迟时间
    unsigned char iModel;       //复位模式 0 - 指定通道模式 1 - 指定节点名 2 -指定vendor product
    unsigned char  res[3];       //!< reserved
    unsigned int   iVendor;                //设备VID 当 iModel = 2有效
    unsigned int   iProduct;                //设备PID 当 iModel = 2有效
    unsigned char * pbyNodeName;    //节点名，不超过32字节 当iModel = 1有效
    unsigned int   iNodeLen;                //节点名长度 当 iModel = 1有效
    unsigned char    res1[16];       //!< reserved
}OPDEVSDK_ST_USB_POWER;


typedef struct
{
    OPDEVSDK_EN_POWER_CTRL   enumOpt;  //!<  工作模式 @see OPDEVSDK_EN_POWER_CTRL
    unsigned int  iDelayTime;                  // 延迟时间
    unsigned char    res[32];       //!< reserved
}OPDEVSDK_ST_FINGER_POWER;

typedef struct
{
    OPDEVSDK_EN_POWER_CTRL   enumOpt;  //!<  工作模式 @see OPDEVSDK_EN_POWER_CTRL
    unsigned int  iDelayTime;                  // 延迟时间
    unsigned char byCh; // 第几路mcu 从0开始
    unsigned char    res[31];       //!< reserved
}OPDEVSDK_ST_MCU_POWER;

typedef struct
{
    OPDEVSDK_EN_POWER_CTRL   enumOpt;  //!<  工作模式 @see OPDEVSDK_EN_POWER_CTRL
    unsigned int  iDelayTime;                  // 延迟时间
    unsigned char    res[32];       //!< reserved
}OPDEVSDK_ST_RF_POWER;


/* 射频反复制选项设置 */
typedef struct
{
    unsigned char byEMCardEnable;        // em卡识别使能  0-失能  1-使能
    unsigned char byM1CardEnable;        // mifare卡识别使能 0-失能  1-使能
    unsigned char byCPUCardEnable;       // CPU卡识别使能 0-失能  1-使能
    unsigned char byIDCardEnable;        // 身份证识别使能 0-失能  1-使能
    unsigned char byEnableNFC;           // 防NFC复制使能 0-失能  1-使能
    unsigned char byEnableM1EncCheck;    // m1卡加密验证功能开启 0-失能  1-使能
    unsigned char byM1EncCheckSectionID; // m1卡加密验证扇区ID （0-100）
    unsigned char byCpuCardReadType;     // cpu卡读卡模式，0-读卡号，1-读文件
    unsigned char byDesfireCardEnable;   // desfire卡识别使能 0-失能  1-使能
    unsigned char byFelicaCardEnable;   // Felica卡识别使能 0-失能  1-使能
    char          byRes[62];
}OPDEVSDK_ST_RF_ANTI_COPY_CFG;

/**@brief upgrade mcu data
 */
typedef struct
{
    char * pbyUpgradeFile;  // 升级包
    unsigned int iUpgradeLen; // 升级包长度
    int *piUpdateStatus;  // 升级过程中接口会修改该值，外部调用请初始化为 2 ， 0 - 升级成功 1 - 升级失败 2 - 升级中
    unsigned char *pbyPercent; // 升级过程会修改改值， 0 - 100
    char byRes[32];
}OPDEVSDK_ST_UPGRADE_MCU_DATA;

typedef struct
{
    char* pbyOutVersion;
    unsigned int iBuffLen;
    char byRes[32];
}OPDEVSDK_ST_MCU_VERSION;

typedef struct
{
    int dwTextLen;     // 由调用者执行text的buffer总长，函数内部返回实际的长度
    char* pbyText;        // 身份证文字内容buffer
    int dwFacePicLen;     // 由调用者执行人脸图片的buffer总长，函数内部返回实际的长度
    char* pbyFacePic;        // 身份证文字内容buffer
    int dwFpLen;     // 由调用者执行指纹内容的buffer总长，函数内部返回实际的长度
    char* pbyFp;        // 身份证指纹内容buffer
    char byRes[64];
}OPDEVSDK_ST_GASAM_ID_DATA;


/**< 指纹算法授权交互的结构体 */
typedef struct
{
    unsigned char byCode;           // 任务代码：0x00用于秘钥交换第一步加密,
                                    //           0x01用于秘钥交换第二步还原秘钥
                                    //           0x02用于信息加解密
    unsigned char res[3];           // 保留
    unsigned int  len;              // 输入数据长度
    unsigned char *data;            // 实际数据
}OPDEVSDK_ST_FP_AUTHORIZE_IN;

typedef OPDEVSDK_ST_FP_AUTHORIZE_IN OPDEVSDK_ST_FP_AUTHORIZE_OUT;

//指纹算法函数
typedef int (*OPDEVSDK_FP_ALGO_AWARD)(OPDEVSDK_ST_FP_AUTHORIZE_IN *pstruInBuffer,  OPDEVSDK_ST_FP_AUTHORIZE_OUT *pstruOutBuffer);

typedef struct
{
    unsigned char byDisableMcu; //是否禁用mcu控制线程 0：启用 1：禁用； 选择不使能，接口连接在mcu上的失效。
    unsigned char byDisableCardIdentify; //是否禁用卡识别线程 0：启用 1：禁用； 选择不使能，应用自主控制卡片识别逻辑，卡识别相关接口失效。
    char byRes[66];
}OPDEVSDK_ST_INIT_OPTIONS;

typedef struct{
    unsigned char   byTagType[2];
    unsigned char   bySnr[15];
    unsigned char   bySak[3];
}OPDEVSDK_ST_TYPTA_ACTIVE;

typedef struct{
    unsigned char   byUidLen[1];
    unsigned char   byUid[16];
    unsigned char   byCardSn[4];
}OPDEVSDK_ST_TYPTB_ACTIVE;

typedef struct{
    unsigned char   byUidLen;
    unsigned char   byUid[16];
}OPDEVSDK_ST_TYPTC_ACTIVE;

typedef struct{
    unsigned char   byMode;               //认证模式（0：key A认证，1：key B认证）
    unsigned char   bySector;             //认证的扇区号（0~15）
    unsigned char   byKey[6];             //6字节认证密钥数组
    unsigned char   byUid[4];             //4字节卡片UID数组
}OPDEVSDK_ST_MIFARE_AUTH;

typedef struct{
    unsigned char   byBlockId;            // 读的块号（0x00~0x3F）
    unsigned char   byData[16];
}OPDEVSDK_ST_MIFARE_BLOCK_READ;

typedef struct{
    unsigned char   byBlockId;            // 读的块号（0x00~0x3F）
    unsigned char   byData[16];
}OPDEVSDK_ST_MIFARE_BLOCK_WRITE;

typedef struct {
    unsigned char   byBlockId;
    unsigned char   byData[4];
}OPDEVSDK_ST_ULTRA_DATA;

typedef struct{
    unsigned char   byFsdi;
    unsigned char   byCid;
    unsigned char   byReceLen;
    unsigned char   byReceBuf[20];
}OPDEVSDK_ST_CPU_RATS;

typedef struct{
    unsigned char   bySendLen;
    unsigned char   bySendBuf[251];
    unsigned char   byReceLen;
    unsigned char   byReceBuf[251];
}OPDEVSDK_ST_CPU_I_BLOCK;

typedef struct{
    unsigned char   byReceLen;
    unsigned char   byReceBuf[100];
}OPDEVSDK_ST_CPU_R_BLOCK;

typedef struct {
    unsigned int        len;
    unsigned char       data[251];
} OPDEVSDK_ST_SAM_ARG_DATA;

typedef struct {
    OPDEVSDK_ST_SAM_ARG_DATA    struTxData;
    OPDEVSDK_ST_SAM_ARG_DATA    struRxData;
} OPDEVSDK_ST_SAM_ARG;

typedef struct
{
    unsigned short  wRxLen;
    unsigned char   byRxBuff[256];
} OPDEVSDK_ST_SE_ARG_DATA_RX;

typedef struct
{
    unsigned short  wTxLen;
    unsigned char   byTxBuff[256];
} OPDEVSDK_ST_SE_ARG_DATA_TX;

typedef struct
{
    OPDEVSDK_ST_SE_ARG_DATA_TX  struTxData;
    OPDEVSDK_ST_SE_ARG_DATA_RX  struRxData;
} OPDEVSDK_ST_SE_ARG;

typedef struct
{
    unsigned short      wFileId;
    OPDEVSDK_ST_SE_ARG_DATA_RX  struRxData;
} OPDEVSDK_ST_SE_ARG_SEL_FILE;

typedef struct
{
    unsigned short      wReadOffset;
    unsigned short      wReadLen;
    OPDEVSDK_ST_SE_ARG_DATA_RX  struRxData;
} OPDEVSDK_ST_SE_ARG_READ;

typedef struct
{
    OPDEVSDK_EN_SE_RANDOMS_LEN  enumRandomsLen;
    OPDEVSDK_ST_SE_ARG_DATA_RX  struRxData;
} OPDEVSDK_ST_SE_ARG_GET_RANDOMS;

typedef struct
{
    unsigned short wPubKey;
    unsigned short wPriKey;
} OPDEVSDK_ST_SE_KEY_PAIR;

typedef struct
{
    OPDEVSDK_ST_SE_KEY_PAIR     struFileIds;
    OPDEVSDK_ST_SE_ARG_DATA_RX  struRxData;
} OPDEVSDK_ST_SE_ARG_GEN_KEY_PAIR, OPDEVSDK_ST_SE_ARG_GEN_SM2_KEY_PAIR;

typedef struct
{
    OPDEVSDK_EN_SE_RSA_LEN      enumRsaLen;
    OPDEVSDK_EN_SE_RSA_EXP      enumRsaExp;
    OPDEVSDK_ST_SE_KEY_PAIR     struFileIds;
    OPDEVSDK_ST_SE_ARG_DATA_RX  struRxData;
} OPDEVSDK_ST_SE_ARG_GEN_RSA_KEY_PAIR;

typedef struct
{
    unsigned char       byKeyUsage;
    unsigned char       byKeyVersion;
    OPDEVSDK_ST_SE_ARG_DATA_TX  struTxData;
} OPDEVSDK_ST_SE_ARG_INIT_DES;

typedef struct
{
    unsigned char       byP1;
    unsigned char       byP2;
    OPDEVSDK_ST_SE_ARG          struData;
} OPDEVSDK_ST_SE_ARG_CAL_KEY, OPDEVSDK_ST_SE_ARG_IPT_SES_KEY, OPDEVSDK_ST_SE_ARG_EN_DECRYPT;




typedef struct
{
    int iValue;                     // 获取到温度值
    unsigned char byCh;           //!< 通道号
    unsigned char byBind;         //!< 获取绑定的功能类型 @see OPDEVSDK_EN_TEMP_BIND
    unsigned char byRes[2];      //预留字节
}OPDEVSDK_ST_GET_TEMP;

typedef struct
{
    unsigned int    iCrc;           //!<   校验值CRC32
    unsigned int    iFlags;         //!<  分区划分配置状态 @see DDM_partinfo flags
    unsigned int    iConfigSize;    //!< config分区大小
    unsigned int    iHeopSize;      //!< heop分区大小
    unsigned int    iEmmcSize;      //!<  emmc容量大小
    unsigned int    res;            //!<   预留
} OPDEVSDK_ST_PART_PARA;

/*----------------------------------------------*
* Function Declare         *
*----------------------------------------------*/


/*******************************************
以下开始为基础接口
*******************************************/

/* @fn  : opdevsdk_hwif_basic_init_by_options
*  @brief ：hardware basic init
        user can call this function to get the capabilities of hardware

* @param ：pstruParam
* @return : -1--error, 0--ok
*/
int opdevsdk_hwif_basic_init_by_options(OPDEVSDK_ST_INIT_OPTIONS* pstruParam);

/** @fn   : opdevsdk_hwif_rtc_set
* @brief  : set rtc time
* @param[in] : OPDEVSDK_ST_RTC *pRtc
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_rtc_set(struct    tm *pTm);

/** @fn   : opdevsdk_hwif_temperature_get
* @brief  : get device temperature
* @param[in] : OPDEVSDK_ST_RTC *pRtc
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_temperature_get(OPDEVSDK_ST_GET_TEMP *pstruParam);

/** @fn   : opdevsdk_hwif_wdt_open
* @brief  : open wdt
* @param[in] : *pathName  OP_DEVSDK_WDT_DEV_NAME
* @return  : fd
*/
int opdevsdk_hwif_wdt_open(const char *pathName);

/** @fn   : opdevsdk_hwif_wdt_close
* @brief  : close wdt
* @param[in] : fd
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_wdt_close(int fd);

/** @fn   : opdevsdk_hwif_wdt_set_timeout
* @brief  : set wdt timeout
* @param[in] : fd
* @param[in] : iTimeOut (s)
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_wdt_set_timeout(int fd, int iTimeOut);

/** @fn   : opdevsdk_hwif_wdt_feed
* @brief  : set wdt fees
* @param[in] : fd
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_wdt_feed(int fd);


/** @fn   : opdevsdk_hwif_wdt_set_status
* @brief  : set wdt status
* @param[in] : fd
* @param[in] : enumType
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_wdt_set_status(int fd, OPDEVSDK_EN_WDT_STATUS enumType);

/** @fn      : opdevsdk_hwif_get_print_level
* @brief   : set opdevsdk lib print level
* @return  : level: DGB  INFO CRIT ERROR
*/
char opdevsdk_hwif_get_print_level(void);

/*******************************************
以下开始为beep接口
*******************************************/
/** @fn      : opdevsdk_hwif_beep_control
* @brief   : 蜂鸣器控制
* @param[in]  : pstruLedParam
* @return  :  op_devsdk_errno_code
*/
int opdevsdk_hwif_beep_control(OPDEVSDK_ST_BEEP_CONTROL* pstruParam);
/*******************************************
以下开始为led灯接口
*******************************************/
/** @fn      : opdevsdk_hwif_led_set_status
* @brief   : set led status
* @param[in]  : pstruLedParam
* @return  :  op_devsdk_errno_code
*/
int opdevsdk_hwif_led_set_status(OPDEVSDK_ST_LED_PARAM* pstruLedParam);


/*******************************************
以下开始为指纹接口
*******************************************/
/** @fn      : opdevsdk_hwif_finger_power_ctrl
* @brief   : 指纹 电源控制
* @param[in]  : pstruParam
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_finger_power_ctrl(OPDEVSDK_ST_FINGER_POWER* pstruParam );

/** @fn      : opdevsdk_hwif_set_finger_led
* @brief   : set finger led status
* @param[in]  : pstruFingerLedParam
* @return  :  op_devsdk_errno_code
*/
int opdevsdk_hwif_set_finger_led(OPDEVSDK_ST_FINGER_LED_PARAM*  pstruFingerLedParam);

/** @fn   : opdevsdk_hwif_finger_open
* @brief  : open finger
* @param[in] : *pathName  OP_DEVSDK_FINGERPRINT_DEV_NAME
* @return  : fd
*/
int opdevsdk_hwif_finger_open(const char *pathName);

/** @fn   : opdevsdk_hwif_finger_init
* @brief  :  finger init
* @param[in] : fd
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_finger_init(int fd);

/** @fn   : opdevsdk_hwif_finger_reset
* @brief  :  finger reset
* @param[in] : fd
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_finger_reset(int fd);

/** @fn   : opdevsdk_hwif_finger_get_image_size
* @brief  :  finger get image size
* @param[in] : fd
* @param[in] : *pathName
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_finger_get_image_size(int fd, OPDEVSDK_ST_FP_GET_IMAGE_SIZE* pstruParam);

/** @fn   : opdevsdk_hwif_finger_get_image
* @brief  :  finger get image
* @param[in] : fd
* @param[in] : *pathName
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_finger_get_image(int fd , OPDEVSDK_ST_FP_GET_IMAGE* pstruParam );

/** @fn   : opdevsdk_hwif_finger_close
* @brief  :  finger close
* @param[in] : fd
* @param[in] : *pathName
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_finger_close(int fd);

/*******************************************
以下开始为USB接口
*******************************************/
#define OPDEVSDK_USB_MCU_VENDOR_ID      		(0xfff0)  //mcu外设扩展板VID
#define OPDEVSDK_USB_MCU_PRODUCT_ID      		(0xfff0)  //mcu外设扩展板PID
#define OPDEVSDK_USB_TEMP_VENDOR_ID      		(0x2bdf)  //测温VID
#define OPDEVSDK_USB_TEMP_PRODUCT_ID      		(0x0101)  //测温PID

/** @fn      : opdevsdk_hwif_usb_power_ctrl
* @brief   : usb 电源控制
* @param[in]  : pstruParam
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_usb_power_ctrl(OPDEVSDK_ST_USB_POWER* pstruParam );
/*******************************************
以下开始为4g接口
*******************************************/

/**
* 4G模块控制参数
*/
typedef struct
{
    int           iEnable;   //    0 - 失能 1 - 使能
    unsigned int  iChannel;                  //!通道
    unsigned char byRes[32]; //!< reserved
} OPDEVSDK_ST_4G_CTRL_PARAM;

typedef struct
{
    unsigned int  iChannel;                  //!通道
    OPDEVSDK_EN_POWER_CTRL   enumOpt;  //!<  工作模式 @see OPDEVSDK_EN_POWER_CTRL
    unsigned int  iDelayTime;                  // 延迟时间
    unsigned char    res[32];       //!< reserved
}OPDEVSDK_ST_4G_POWER;

/** @fn      : opdevsdk_hwif_4g_ctrl
* @brief   : 4g module ctrl
* @param[in]  : pstruParam
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_4g_ctrl(OPDEVSDK_ST_4G_CTRL_PARAM* pstruParam );

/** @fn      : opdevsdk_hwif_4g_power_ctrl
* @brief   : 4g 电源控制
* @param[in]  : pstruParam
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_4g_power_ctrl(OPDEVSDK_ST_4G_POWER* pstruParam );

/*******************************************
以下开始为5g接口
*******************************************/
typedef struct
{
    unsigned int  iChannel;                  //!通道
    OPDEVSDK_EN_POWER_CTRL   enumOpt;  //!<  工作模式 @see OPDEVSDK_EN_POWER_CTRL
    unsigned int  iDelayTime;                  // 延迟时间
    unsigned char    res[32];       //!< reserved
}OPDEVSDK_ST_5G_POWER;

/** @fn      : opdevsdk_hwif_4g_power_ctrl
* @brief   : 4g 电源控制
* @param[in]  : pstruParam
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_5g_power_ctrl(OPDEVSDK_ST_5G_POWER* pstruParam );
/*******************************************
以下开始为wifi接口
*******************************************/
/** @fn      : opdevsdk_hwif_wifi_ctrl
* @brief   : wifi module ctrl
* @param[in]  : pstruParam
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_wifi_ctrl(OPDEVSDK_ST_WIFI_CTRL_PARAM *pstruParam);

/** @fn      : opdevsdk_hwif_wifi_power_ctrl
* @brief   : wifi 电源控制
* @param[in]  : pstruParam
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_wifi_power_ctrl(OPDEVSDK_ST_WIFI_POWER *pstruParam);

/*******************************************
以下开始为韦根接口
*******************************************/

/** @fn      : opdevsdk_hwif_wiegand_set_signal_pin_status
* @brief   : set wiegand signal pin status
* @param[in]  : fd
* @param[in]  : pstruParam
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_wiegand_set_signal_pin_status(int fd,OPDEVSDK_ST_WIEGAND_SINGAL_PIN* pstruParam );

/** @fn      : opdevsdk_hwif_wiegand_get_signal_pin_status
* @brief   : get wiegand signal pin status
* @param[in]  : fd
* @param[in]  : pstruParam
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_wiegand_get_signal_pin_status(int fd,OPDEVSDK_ST_WIEGAND_SINGAL_PIN* pstruParam );

/*******************************************
以下开始为韦根接口(仅当韦根连接在SOC有效)
*******************************************/

/** @fn      : opdevsdk_hwif_wiegand_get_w0_status
* @brief   : get wiegand w0 status
* @param[in]  : fd
* @return  : w0 status (0 or 1)
*/
int opdevsdk_hwif_wiegand_get_w0_status(int fd);

/** @fn      : opdevsdk_hwif_wiegand_get_w1_status
* @brief   : get wiegand w1 status
* @param[in]  : fd
* @return  : w1 status (0 or 1)
*/
int opdevsdk_hwif_wiegand_get_w1_status(int fd);

/** @fn      : opdevsdk_hwif_wiegand_get_signal_pin_status
* @brief   : 设置韦根工作模式，默认为透传模式
* @param[in]  : fd
* @param[in]  : pstruParam
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_wiegand_set_work_mode(int fd,OPDEVSDK_EN_WIEGAND_WORK_MODE* pstruParam );

/** @fn      : opdevsdk_hwif_wiegand_get_signal_pin_status
* @brief   : 设置韦根工作模式，默认为透传模式
* @param[in]  : fd
* @param[out]  : pbyStatus  输出状态，0：结束 1：未结束
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_wiegand_get_output_status(int fd,unsigned char *pbyStatus );


/*******************************************
以下开始为卡识别接口
*******************************************/

/** @fn   : opdevsdk_hwif_rf_power_ctrl
 * @brief  :射频 电源控制
 * @param[in] : fd
 * @param[in] : pstruParam
 * @return  : op_devsdk_errno_code
 */
int opdevsdk_hwif_rf_power_ctrl(int fd, OPDEVSDK_ST_RF_POWER *pstruParam);

/** @fn      : opdevsdk_hwif_rf_set_anti_copy_cfg
* @brief   : set rf anti-copy config
* @param[in]  : pstruParam
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_rf_set_anti_copy_cfg(OPDEVSDK_ST_RF_ANTI_COPY_CFG* pstruParam );

/** @fn      : opdevsdk_hwif_rf_get_anti_copy_cfg
* @brief   : set rf anti-copy config
* @param[in]  : pstruParam
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_rf_get_anti_copy_cfg(OPDEVSDK_ST_RF_ANTI_COPY_CFG* pstruParam );

/** @fn   : opdevsdk_hwif_gasam_id_open
* @brief  : open gasam_id dev
* @param[in] : *pathName  OP_DEVSDK_GASAM_ID_DEV_NAME
* @return  : fd
*/
int opdevsdk_hwif_gasam_id_open(const char *pathName);

/** @fn   : opdevsdk_hwif_gasam_id_close
* @brief  : close gasam_id dev
* @param[in] : fd
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_gasam_id_close(int fd);


/** @fn   : opdevsdk_hwif_gasam_id_read
* @brief  : read gasam_id data
* @param[in] : fd
* @param[in] : timeval *timeout
* @param[out] : OPDEVSDK_ST_GASAM_ID_DATA *pstruGasamIdData
* @return  : -1--error, 0--timeout  1---成功
*/
int opdevsdk_hwif_gasam_id_read(int fd, OPDEVSDK_ST_GASAM_ID_DATA *pstruGasamIdData, int iTimeMs);

/*******************************************
以下开始为射频操作接口（仅支持射频天线连接在soc的情况，且不启动卡识别线程的情况下）
*******************************************/

typedef struct  {
    unsigned int    iLen;
    char            *pbyData;
    char            reserve[64];
} OPDEVSDK_ST_RF_ARG_BASE;

typedef struct {
    OPDEVSDK_ST_RF_ARG_BASE  struTx;
    OPDEVSDK_ST_RF_ARG_BASE  struRx;
    char           reserve[64];
} OPDEVSDK_ST_RF_TYPEB_DATA;

/** @fn      : opdevsdk_hwif_rf_active_typeA
 * @brief   : TYPEA卡片激活
 * @param   : fd 文件描述符
 * @param   : *pstruParam
 * @return  : op_devsdk_errno_code
 */
int opdevsdk_hwif_rf_active_typeA(int fd, OPDEVSDK_ST_TYPTA_ACTIVE *pstruParam);

/** @fn      : opdevsdk_hwif_rf_halt_typeA
 * @brief   : TYPEA协议停止
 * @param   : fd 文件描述符
 * @return  : op_devsdk_errno_code
 */
int opdevsdk_hwif_rf_halt_typeA(int fd);

/** @fn      : opdevsdk_hwif_rf_active_typeB
 * @brief   : TYPEB卡片激活
 * @param   : fd 文件描述符
 * @param   : *pstruParam
 * @return  : op_devsdk_errno_code
 */
int opdevsdk_hwif_rf_active_typeB(int fd, OPDEVSDK_ST_TYPTB_ACTIVE *pstruParam);

/** @fn      : opdevsdk_hwif_rf_active_typeC
 * @brief   : TYPEC卡片激活
 * @param   : fd 文件描述符
 * @param   : *pstruParam
 * @return  : op_devsdk_errno_code
 */
int opdevsdk_hwif_rf_active_typeC(int fd, OPDEVSDK_ST_TYPTC_ACTIVE *pstruParam);

/** @fn      : opdevsdk_hwif_rf_mifare_auth
 * @brief   : Mifare_Auth卡片认证
 * @param   : fd 文件描述符
 * @param   : *pstruParam
 * @return  : op_devsdk_errno_code
 */
int opdevsdk_hwif_rf_mifare_auth(int fd, OPDEVSDK_ST_MIFARE_AUTH *pstruParam);

/** @fn      : opdevsdk_hwif_rf_mifare_block_read
 * @brief   : Mifare卡片读块操作
 * @param   : fd 文件描述符
 * @param   : *pstruParam
 * @return  : op_devsdk_errno_code
 */
int opdevsdk_hwif_rf_mifare_block_read(int fd, OPDEVSDK_ST_MIFARE_BLOCK_READ *pstruParam);

/** @fn      : opdevsdk_hwif_rf_mifare_block_write
 * @brief   : Mifare卡片写块操作
 * @param   : fd 文件描述符
 * @param   : *pstruParam
 * @return  : op_devsdk_errno_code
 */
int opdevsdk_hwif_rf_mifare_block_write(int fd, OPDEVSDK_ST_MIFARE_BLOCK_WRITE *pstruParam);

/** @fn      : opdevsdk_hwif_rf_judge_uid
 * @brief   : 验证是否为UID卡
 * @param   : fd 文件描述符
 * @param   : *pstruParam
 * @return  : 0 ：成功 -1：失败
 */
int opdevsdk_hwif_rf_judge_uid(int fd);

/** @fn      : opdevsdk_hwif_rf_typeA_ultra_read
 * @brief   : UltraLight卡块读取接口
 * @param   : fd 文件描述符
 * @param   : *pstruParam
 * @return  : op_devsdk_errno_code
 */
int opdevsdk_hwif_rf_typeA_ultra_read(int fd, OPDEVSDK_ST_ULTRA_DATA *pstruParam);

/** @fn      : opdevsdk_hwif_rf_cpu_rats
 * @brief   : CPU卡复位接口
 * @param   : fd 文件描述符
 * @param   : *pstruParam
 * @return  : op_devsdk_errno_code
 */
int opdevsdk_hwif_rf_cpu_rats(int fd, OPDEVSDK_ST_CPU_RATS *pstruParam);

/** @fn      : opdevsdk_hwif_rf_cpu_r_block
 * @brief   : CPU卡 R block通信
 * @param   : fd 文件描述符
 * @param   : *pstruParam
 * @return  : op_devsdk_errno_code
 */
int opdevsdk_hwif_rf_cpu_r_block(int fd, OPDEVSDK_ST_CPU_R_BLOCK *pstruParam);

/** @fn      : opdevsdk_hwif_rf_cpu_i_block
 * @brief   : CPU卡 I block通信
 * @param   : fd 文件描述符
 * @param   : *pstruParam
 * @return  : op_devsdk_errno_code
 */
int opdevsdk_hwif_rf_cpu_i_block(int fd, OPDEVSDK_ST_CPU_I_BLOCK *pstruParam);

/** @fn      : opdevsdk_hwif_rf_typeB_card_transeive
 * @brief   : TypeB 透传接口，身份证软解使用
 * @param   : fd 文件描述符
 * @param   : *pstruParam
 * @return  : op_devsdk_errno_code
 */
int opdevsdk_hwif_rf_typeB_card_transeive(int fd, OPDEVSDK_ST_RF_TYPEB_DATA *pstruParam);


/*******************************************
以下开始为sam模块接口（仅支持射频天线连接在soc的情况，且不启动卡识别线程的情况下）
*******************************************/

/** @fn   : opdevsdk_hwif_sam_open
* @brief  : open se
* @param[in] : *pathName  OP_DEVSDK_SAM_DEV_NAME
* @return  : fd
*/
int opdevsdk_hwif_sam_open(const char *pathName);

/** @fn   : opdevsdk_hwif_sam_close
* @brief  : close se
* @param[in] : fd
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_sam_close(int fd);

/** @fn      : opdevsdk_hwif_sam_i_block
    * @brief   : CPU卡 I block通信
    * @param   : fd 文件描述符
    * @param   : *pstruParam
    * @return  : op_devsdk_errno_code
    */
int opdevsdk_hwif_sam_i_block(int fd, OPDEVSDK_ST_SAM_ARG *pstruParam);

/** @fn   : opdevsdk_hwif_sam_reset
    * @brief  :sam 电源控制
    * @param[in] : pstruParam
    * @return  : op_devsdk_errno_code
    */
int opdevsdk_hwif_sam_reset(int fd);

/*******************************************
以下开始为se模块接口（仅支持射频天线连接在soc的情况，且不启动卡识别线程的情况下）
*******************************************/

/** @fn   : opdevsdk_hwif_se_open
* @brief  : open se
* @param[in] : *pathName  OP_DEVSDK_SE_DEV_NAME
* @return  : fd
*/
int opdevsdk_hwif_se_open(const char *pathName);

/** @fn   : opdevsdk_hwif_se_close
* @brief  : close se
* @param[in] : fd
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_se_close(int fd);

/** @fn   : opdevsdk_hwif_se_select_file
* @brief  : SE 文件选择
* @param[in] : fd
* @param[in] : pstruParam
* @return  : fd
*/
int opdevsdk_hwif_se_select_file(int fd, OPDEVSDK_ST_SE_ARG_SEL_FILE *pstruParam);

/** @fn   : opdevsdk_hwif_se_read_binary
* @brief  : SE 读取二进制
* @param[in] : fd
* @param[in] : pstruParam
* @return  : fd
*/
int opdevsdk_hwif_se_read_binary(int fd, OPDEVSDK_ST_SE_ARG_READ *pstruParam);

/** @fn   : opdevsdk_hwif_se_get_randoms
* @brief  : SE 获取随机数
* @param[in] : fd
* @param[in] : pstruParam
* @return  : fd
*/
int opdevsdk_hwif_se_get_randoms(int fd, OPDEVSDK_ST_SE_ARG_GET_RANDOMS *pstruParam);

/** @fn   : opdevsdk_hwif_se_verify_pin
* @brief  : SE 口令校验
* @param[in] : fd
* @param[in] : pstruParam
* @return  : fd
*/
int opdevsdk_hwif_se_verify_pin(int fd, OPDEVSDK_ST_SE_ARG *pstruParam);

/** @fn   : opdevsdk_hwif_se_init_des
* @brief  : se DES计算初始化
* @param[in] : fd
* @param[in] : pstruParam
* @return  : fd
*/
int opdevsdk_hwif_se_init_des(int fd, OPDEVSDK_ST_SE_ARG_INIT_DES *pstruParam);

/** @fn   : opdevsdk_hwif_se_init_des
* @brief  : se des 计算
* @param[in] : fd
* @param[in] : pstruParam
* @return  : fd
*/
int opdevsdk_hwif_se_calc_des(int fd, OPDEVSDK_ST_SE_ARG *pstruParam);

/*******************************************
以下开始为485操作接口
*******************************************/
#define OP_DEVSDK_DEV_TTY_ANALOG_NAME         "/dev/DDM/tty_analog"

/** @fn   : opdevsdk_hwif_rs485_tcflush
* @brief  : write rs485 data
* @param[in] : fd
* @param[in] : enumType
* @return  : -1--error, 0 --- OK
*/
int opdevsdk_hwif_rs485_tcflush(int fd, OPDEVSDK_ST_TCFLUSH_TYPE enumType);

/** @fn   : opdevsdk_hwif_rs485_tcflush
* @brief  : write rs485 data
* @param[in] : fd
* @param[in] : byDirection : 0 :接收 1：发送
* @return  : -1--error, 0 --- OK
*/
int opdevsdk_hwif_rs485_set_direction(int fd, unsigned char byDirection);

/*******************************************
以下为蓝牙接口
*******************************************/
#define OP_DEVSDK_DEV_TTY_BLE_NAME            "/dev/DDM/tty_ble"  // 485蓝牙通信节点
#define OP_DEVSDK_DEV_BLE_NAME                "/dev/DDM/ble"     // 蓝牙控制节点，复位等命令需要打开该节点

typedef struct
{
    OPDEVSDK_EN_POWER_CTRL   enumOpt;  //!<  工作模式 @see OPDEVSDK_EN_POWER_CTRL
    unsigned int  iDelayTime;                  // 延迟时间
    char byFdFalg;        //是否指定句柄进行复位，2.0仅支持指定复位
    int iFd;            //蓝牙句柄
    unsigned char    res[32];       //!< reserved
}OPDEVSDK_ST_BLUETOOTH_POWER;

// 固件升级参数
typedef struct
{
    char byFwPath[100];                  // 固件路径
    int reserve;                        // 保留
} OPDEVSDK_ST_BLE_SET_FW_ARGS;


// 蓝牙接口类型
typedef enum
{
    OPDEVSDK_EN_BLE_INFTYPE_SPI= 0,             // SPI接口类型
    OPDEVSDK_EN_BLE_INFTYPE_TTY,                // 串口接口类型
    OPDEVSDK_EN_BLE_INFTYPE_MAX,                // 最大值 必须为最后一个
} OPDEVSDK_EN_BLE_GET_INF_TYPE;


/** @fn   : opdevsdk_hwif_ble_open
* @brief  : 打开蓝牙
* @param[in] : *pathName  OP_DEVSDK_DEV_TTY_BLE_NAME or OP_DEVSDK_DEV_BLE_NAME
* @return  : fd
*/
int opdevsdk_hwif_ble_open(const char *pathName);

/** @fn   : opdevsdk_hwif_se_close
* @brief  : 关闭蓝牙
* @param[in] : fd
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_ble_close(int fd);

/** @fn   : opdevsdk_hwif_ble_update_fw
* @brief  : 下载蓝牙固件，仅spi接口使用
* @param[in] : fd
* @param[in] : pstruParam
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_ble_update_fw(int fd , OPDEVSDK_ST_BLE_SET_FW_ARGS  *pstruParam);

/** @fn   : opdevsdk_hwif_ble_clear_rx_buffer
* @brief  : 清除接收缓存，仅限spi接口蓝牙使用
* @param[in] : fd
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_ble_clear_rx_buffer(int fd );

/** @fn   : opdevsdk_hwif_ble_prepare_update
* @brief  : 蓝牙固件升级前时序环境准备（包括上电复位等逻辑）仅串口接口蓝牙模块调用
* @param[in] : fd
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_ble_prepare_update(int fd );

/** @fn   : opdevsdk_hwif_ble_get_interface_type
* @brief  : 获取蓝牙硬件接口
* @param[in] : fd
* @param[in] : penumType
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_ble_get_interface_type(int fd , OPDEVSDK_EN_BLE_GET_INF_TYPE *penumType);

/** @fn   : opdevsdk_hwif_bluetooth_power_ctrl
    * @brief  : 蓝牙 电源控制
    * @param[in] : pstruParam
    * @return  : op_devsdk_errno_code
    */
int opdevsdk_hwif_bluetooth_power_ctrl(OPDEVSDK_ST_BLUETOOTH_POWER *pstruParam);

/*******************************************
以下为MCU接口（初始化需启用启用mcu才能使用）
*******************************************/
/** @fn   : opdevsdk_hwif_upgrade_mcu
    * @brief  : upgrade mcu
    * @param[in] : pUpgradeData
    * @return  : op_devsdk_errno_code
    */
int opdevsdk_hwif_upgrade_mcu(OPDEVSDK_ST_UPGRADE_MCU_DATA *pstruUpgradeData);


/** @fn   : opdevsdk_hwif_mcu_get_version
    * @brief  : get mcu version
    * @param[in] : pstruData
    * @return  : op_devsdk_errno_code
    */
int opdevsdk_hwif_mcu_get_version(OPDEVSDK_ST_MCU_VERSION *pstruData);

/*******************************************
以下为MCU接口（初始化不启用mcu的情况下可以使用）
*******************************************/

/** @fn   : opdevsdk_hwif_mcu_power_ctrl
    * @brief  : mcu 电源控制
    * @param[in] : pstruParam
    * @return  : op_devsdk_errno_code
    */
int opdevsdk_hwif_mcu_power_ctrl(OPDEVSDK_ST_MCU_POWER *pstruParam);

/** @fn   : opdevsdk_hwif_get_fp_algo_award_fn
* @brief  : get  fp algo award func
* @return  : NULL or func
*/
OPDEVSDK_FP_ALGO_AWARD opdevsdk_hwif_get_fp_algo_award_fn();

/*******************************************
以下开始为IO操作接口
*******************************************/
/** @fn   : opdevsdk_hwif_shutdown_button_get_status
* @brief  : get shutdown button status
* @param[in] : NA
* @return  : -1--error, 0--no trigger, 1--trigger
*/
int opdevsdk_hwif_shutdown_button_get_status(void);

/** @fn   : opdevsdk_hwif_shutdown_button_get_status
* @brief  : 消防输入状态获取
* @param[in] : index 序号 从1 开始
* @return  : -1--error, 0--no trigger, 1--trigger
*/
int opdevsdk_hwif_fire_fighting_get_status(int index);

/** @fn   : opdevsdk_hwif_shutdown_button_get_status
* @brief  : 恢复出厂按钮状态获取
* @param[in] : index 序号 从1 开始
* @return  : -1--error, 0--no trigger, 1--trigger
*/
int opdevsdk_hwif_reset_get_status(int index);

typedef struct
{
    unsigned int iInnum;                 // GPIO类输入通道数量
    unsigned int iOutnum;                // GPIO类输出通道数量
    unsigned int iRelaynum;              // 继电器输出通道数量
    unsigned int reserve[5];            // 保留
} OPDEVSDK_ST_EXIO_GET_NUM;

/** @fn   : opdevsdk_hwif_exio_get_num
* @brief  : 获取外部输入输出io数量
* @param[in] : pstruParam
* @return  : -1--error, 0--no trigger, 1--trigger
*/
int opdevsdk_hwif_exio_get_num(OPDEVSDK_ST_EXIO_GET_NUM *pstruParam);

/*******************************************
以下开始为出厂flash内容读写接口
*******************************************/
/** @fn   : opdevsdk_hwif_get_boot_param
* @brief  :
* @param[in] : pstSecParam:
* @return  : none
*/
int opdevsdk_hwif_sec_info(OPDEVSDK_ST_SEC_INFO *pstSecParam);

/** @fn   : opdevsdk_hwif_read_part_info
* @brief  : 读取分区信息
* @param[in] : pstSecParam:
* @return  : none
*/
int opdevsdk_hwif_read_part_info(OPDEVSDK_ST_PART_PARA *pstSecParam);

/** @fn   : opdevsdk_hwif_read_part_info
* @brief  : 写入分区信息
* @param[in] : pstSecParam:
* @return  : none
*/
int opdevsdk_hwif_wirte_part_info(OPDEVSDK_ST_PART_PARA *pstSecParam);

/*******************************************
以下开始为身份证阅读器接口
*******************************************/
/** @fn      : opdevsdk_hwif_identity_power_ctrl
* @brief   : 身份证阅读器 电源控制
* @param[in]  : pstruParam
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_identity_power_ctrl(OPDEVSDK_ST_IDENTITY_POWER* pstruParam );


/*******************************************
以下开始为ICR接口
*******************************************/

//ICR 状态
typedef enum
{
    OPDEVSDK_EN_ICR_STATE_DAY,                  //   白天
    OPDEVSDK_EN_ICR_STATE_NIGHT,                //  夜晚
    OPDEVSDK_EN_ICR_STATE_MAX,
} OPDEVSDK_EN_ICR_STATE;
/** @fn      : opdevsdk_hwif_icr_set_status
* @brief   : 设置icr 状态
* @param[in]  : iStatus 见 OPDEVSDK_EN_ICR_STATE
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_icr_set_status(unsigned int iStatus);

/** @fn      : opdevsdk_hwif_icr_get_status
* @brief   : 获取icr 状态
* @return  : -1--error, 其他-状态值
*/
int opdevsdk_hwif_icr_get_status(void);

/*******************************************
以下开始为音频接口
*******************************************/

//功放增益设置结构体
typedef struct
{
    unsigned int iChannel;               // 配置表中对应的通道号
    unsigned int iGain;                  // 功放增益
} OPDEVSDK_ST_SOUND_AMP_GAIN;

typedef enum
{
    OPDEVSDK_EN_SOUND_OUTPATH_EXT_SPK = 0,                    //切换至外接音箱
    OPDEVSDK_EN_SOUND_OUTPATH_LOCAL_SPK,                      //切换至本地spk
    OPDEVSDK_EN_SOUND_OUTPATH_HP_SPK,                         //切换耳机输出
    OPDEVSDK_EN_SOUND_OUTPATH_LOCAL_PLATFORM,                 //平台间输出电路切换到本地端soc（双芯片产品适用）
    OPDEVSDK_EN_SOUND_OUTPATH_REMOTE_PLATFORM,                //平台间输出电路切换到远端soc（双芯片产品适用）
    OPDEVSDK_EN_SOUND_OUTPATH_MAX,
} OPDEVSDK_EN_SOUND_OUTPUT_PATH;

typedef enum
{
    OPDEVSDK_EN_SOUND_INPATH_EXT_MIC = 0,                    //切换至外接MIC
    OPDEVSDK_EN_SOUND_INPATH_LOCAL_MIC,                      //切换至本地MIC
    OPDEVSDK_EN_SOUND_INPATH_LOOPBACK,                       //切换至回采
    OPDEVSDK_EN_SOUND_INTPATH_HP_MIC,                        //切换至耳机输入
    OPDEVSDK_EN_SOUND_INPATH_LOCAL_PLATFORM,                 //平台间输入电路切换本地端soc（双芯片产品适用）
    OPDEVSDK_EN_SOUND_INPATH_REMOTE_PLATFORM,                //平台间输入电路切换远端soc（双芯片产品适用）
    OPDEVSDK_EN_SOUND_INPATH_MAX,
} OPDEVSDK_EN_SOUND_INPUT_PATH;


//外接音频路径设置结构体
typedef struct
{
    unsigned int iPathChannel;           // 设置的路径通道号
    unsigned int iType;                  // 路径类型
    unsigned int iStatus;                // 连通状态
} OPDEVSDK_ST_SOUND_PATH;

//功放增益设置结构体
typedef struct
{
    unsigned int iPathChannel;               // 具体是哪个路径
    unsigned int iPath;                 // 需要设置的音量路径名字
    unsigned int iVol;                  // 功放增益
} OPDEVSDK_ST_SOUND_VOLUME;

#define OPDEVSDK_BIT(nr)			(1UL << (nr))
/* 音频采样率 8K 到 192K，具体看各个codec芯片支持的范围 */
typedef enum
{
    OPDEVSDK_EN_SND_SOC_PCM_RATE_8000    = (8000),
    OPDEVSDK_EN_SND_SOC_PCM_RATE_11025   = (11025),
    OPDEVSDK_EN_SND_SOC_PCM_RATE_12000   = (12000),
    OPDEVSDK_EN_SND_SOC_PCM_RATE_16000   = (16000),
    OPDEVSDK_EN_SND_SOC_PCM_RATE_22050   = (22050),
    OPDEVSDK_EN_SND_SOC_PCM_RATE_24000   = (24000),
    OPDEVSDK_EN_SND_SOC_PCM_RATE_32000   = (32000),
    OPDEVSDK_EN_SND_SOC_PCM_RATE_44100   = (44100),
    OPDEVSDK_EN_SND_SOC_PCM_RATE_48000   = (48000),
    OPDEVSDK_EN_SND_SOC_PCM_RATE_96000   = (96000),
    OPDEVSDK_EN_SND_SOC_PCM_RATE_192000  = (192000),
}OPDEVSDK_EN_SND_PCMRATE;

typedef enum
{
    OPDEVSDK_EN_SND_SOC_PCM_FORMAT_S8                       = OPDEVSDK_BIT(0),
    OPDEVSDK_EN_SND_SOC_PCM_FORMAT_S16                      = OPDEVSDK_BIT(1),
    OPDEVSDK_EN_SND_SOC_PCM_FORMAT_S20                      = OPDEVSDK_BIT(2),
    OPDEVSDK_EN_SND_SOC_PCM_FORMAT_S24                      = OPDEVSDK_BIT(3),
    OPDEVSDK_EN_SND_SOC_PCM_FORMAT_S32                      = OPDEVSDK_BIT(4),
    OPDEVSDK_EN_SND_SOC_PCM_FORMAT_MSB_S24                  = OPDEVSDK_BIT(5),
}OPDEVSDK_EN_SND_PCM_BITWIDTH;

//功放增益设置结构体
typedef struct
{
    unsigned int iPathDirection;        // path的方向，0代表输入 1代表输出
    unsigned int iPath;                  // 需要设置的音量路径名字 具体参考 OPDEVSDK_EN_SOUND_INPUT_PATH 与  OPDEVSDK_EN_SOUND_INPUT_PATH
    unsigned int iPathChannel;          // 相同路径名称的具体哪个路径，譬如：板子上有2个耳机，要控制左声道，就要区分耳机1和耳机2,channel就是1跟2.具体值要配合项目和bsp沟通
    unsigned int iRate;                  // 采样率
    unsigned int iBitWidth;             // 位宽
    unsigned int iBClk;                 // 位时钟
} OPDEVSDK_ST_SOUND_FORMAT;

/** @fn      : opdevsdk_hwif_mic_open
* @brief   : 打开mic
* @param[in]  : iChannel 通道
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_mic_open(unsigned int iChannel);

/** @fn      : opdevsdk_hwif_mic_close
* @brief   : 关闭mic
* @param[in]  : iChannel 通道
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_mic_close(unsigned int iChannel);

/** @fn      : opdevsdk_hwif_sound_set_amp_gain
* @brief   : 设置功放增益
* @param[in]  : iChannel 通道
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_sound_set_amp_gain(OPDEVSDK_ST_SOUND_AMP_GAIN* pstruParam);

/** @fn      : opdevsdk_hwif_sound_get_amp_gain
* @brief   : 获取功放增益
* @param[in]  : iChannel 通道
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_sound_get_amp_gain(OPDEVSDK_ST_SOUND_AMP_GAIN* pstruParam);

/** @fn      : opdevsdk_hwif_sound_set_format
* @brief   : 设置音频codec芯片的采样参数，比特率和位宽
* @param[in]  : iChannel 通道
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_sound_set_format(OPDEVSDK_ST_SOUND_FORMAT* pstruParam);

/** @fn      : opdevsdk_hwif_sound_get_format
* @brief   : 获取音频codec芯片的采样参数，比特率和位宽
* @param[in]  : iChannel 通道
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_sound_get_format(OPDEVSDK_ST_SOUND_FORMAT* pstruParam);

/** @fn      : opdevsdk_hwif_amp_open
* @brief   : 打开功放
* @param[in]  : iChannel 通道
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_amp_open(unsigned int iChannel);

/** @fn      : opdevsdk_hwif_amp_close
* @brief   : 关闭功放
* @param[in]  : iChannel 通道
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_amp_close(unsigned int iChannel);

/** @fn      : opdevsdk_hwif_sound_set_output_channel
* @brief   : 设置外接音频路径
* @param[in]  : iChannel 通道
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_sound_set_output_channel(OPDEVSDK_ST_SOUND_PATH* pstruParam);

/** @fn      : opdevsdk_hwif_sound_get_output_channel
* @brief   : 获取外接音频路径状态
* @param[in]  : iChannel 通道
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_sound_get_output_channel(OPDEVSDK_ST_SOUND_PATH* pstruParam);

/** @fn      : opdevsdk_hwif_sound_set_input_channel
* @brief   : 设置外接音频路径
* @param[in]  : iChannel 通道
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_sound_set_input_channel(OPDEVSDK_ST_SOUND_PATH* pstruParam);

/** @fn      : opdevsdk_hwif_sound_get_input_channel
* @brief   : 获取外接音频路径状态
* @param[in]  : iChannel 通道
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_sound_get_input_channel(OPDEVSDK_ST_SOUND_PATH* pstruParam);

/** @fn      : opdevsdk_hwif_sound_set_output_volume
* @brief   : 设置输出音量
* @param[in]  : iChannel 通道
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_sound_set_output_volume(OPDEVSDK_ST_SOUND_VOLUME* pstruParam);

/** @fn      : opdevsdk_hwif_sound_get_output_volume
* @brief   : 获取输出音量
* @param[in]  : iChannel 通道
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_sound_get_output_volume(OPDEVSDK_ST_SOUND_VOLUME* pstruParam);

/** @fn      : opdevsdk_hwif_sound_set_input_volume
* @brief   : 设置输入音量
* @param[in]  : iChannel 通道
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_sound_set_input_volume(OPDEVSDK_ST_SOUND_VOLUME* pstruParam);

/** @fn      : opdevsdk_hwif_sound_get_input_volume
* @brief   : 获取输入音量
* @param[in]  : iChannel 通道
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_sound_get_input_volume(OPDEVSDK_ST_SOUND_VOLUME* pstruParam);



/*******************************************
以下开始为加热模块接口
*******************************************/
//heat 模块设置参数
typedef struct
{
    unsigned char byPower;            // 电源 取值0关/1开
    unsigned char byCh;               // 通道号 从0开始
    unsigned char reserve[6];       // 预留
} OPDEVSDK_ST_HEAT_ARGS;

/** @fn      : opdevsdk_hwif_heat_lens_ctrl
* @brief   : 设置Camera Lans加热开关
* @param[in]  : pstruParam
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_heat_lens_ctrl(OPDEVSDK_ST_HEAT_ARGS * pstruParam );

/** @fn      : opdevsdk_hwif_heat_cpu_ctrl
* @brief   : 设置CPU加热开关
* @param[in]  : pstruParam
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_heat_cpu_ctrl(OPDEVSDK_ST_HEAT_ARGS * pstruParam );

/** @fn      : opdevsdk_hwif_heat_battery_ctrl
* @brief   : 设置电池加热开关
* @param[in]  : pstruParam
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_heat_battery_ctrl(OPDEVSDK_ST_HEAT_ARGS * pstruParam );

/*******************************************
以下开始触屏接口
*******************************************/

#define OP_DEVSDK_DEV_TS_NAME                 "/dev/DDM/ts"   //主屏幕
#define OP_DEVSDK_DEV_TS_VICE_NAME            "/dev/DDM/ts_vice" //副屏幕

// 固件升级参数
typedef struct
{
    char byFwPath[100];                  // 固件路径
    int reserve;                        // 保留
} OPDEVSDK_ST_TS_SET_FW_ARGS;

// 获取固件版本
typedef struct
{
    unsigned int  iLen;
    unsigned char byVersion[20];
} OPDEVSDK_ST_TS_GET_VERSION;

/** @fn      : opdevsdk_hwif_ts_open
* @brief   : 打开触摸屏句柄
* @param[in]  : byName
* @return  : fd
*/
int opdevsdk_hwif_ts_open(char *byName);

/** @fn      : opdevsdk_hwif_ts_open
* @brief   : 关闭触摸屏句柄
* @param[in]  : fd
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_ts_close(int fd );


/** @fn      : opdevsdk_hwif_ts_update_fw
* @brief   : 触摸屏升级接口
* @param[in]  : fd
* @param[in]  : pstruParam
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_ts_update_fw(int fd,OPDEVSDK_ST_TS_SET_FW_ARGS * pstruParam );

/** @fn      : opdevsdk_hwif_ts_get_chipid
* @brief   : 获取芯片ID
* @param[in]  : fd
* @return  : -1--error, 其他- 芯片id
*/
int opdevsdk_hwif_ts_get_chipid(int fd);

/** @fn      : opdevsdk_hwif_ts_do_calibration
* @brief   : 芯片校准
* @param[in]  : fd
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_ts_do_calibration(int fd);

/** @fn      : opdevsdk_hwif_ts_get_version
* @brief   : 获取固件版本信息
* @param[in]  : pstruParam
* @param[in]  : fd
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_ts_get_version(int fd, OPDEVSDK_ST_TS_GET_VERSION * pstruParam );

/*******************************************
以下开始测温接口
*******************************************/

typedef struct
{
    unsigned int  iChannel;                  //!通道
    OPDEVSDK_EN_POWER_CTRL   enumOpt;  //!<  工作模式 @see OPDEVSDK_EN_POWER_CTRL
    unsigned int  iDelayTime;                  // 延迟时间
    unsigned char    res[32];       //!< reserved
}OPDEVSDK_ST_TEMP_MEASURE_POWER;

/** @fn      : opdevsdk_hwif_temp_measure_power_ctrl
* @brief   : 测温模块 电源控制
* @param[in]  : pstruParam
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_temp_measure_power_ctrl(OPDEVSDK_ST_TEMP_MEASURE_POWER* pstruParam );

#ifdef __cplusplus
}
#endif

#endif
