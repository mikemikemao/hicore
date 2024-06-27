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
#define OP_DEVSDK_GASAM_ID_DEV_NAME               "/dev/DDM/gsam"               //GASAM_ID�ڵ�
#define OP_DEVSDK_WDT_DEV_NAME              "/dev/DDM/wdt"               //wdt�ڵ�
#define OP_DEVSDK_SE_DEV_NAME              "/dev/DDM/se"               //se�ڵ�
#define OP_DEVSDK_SAM_DEV_NAME              "/dev/DDM/sam"               //se�ڵ�
#define OP_DEVSDK_FINGERPRINT_DEV_NAME            "/dev/DDM/fingerprint"  // finger�ڵ�

/*----------------------------------------------*
* Define          *
*----------------------------------------------*/


/*----------------------------------------------*
* Macros          *
*----------------------------------------------*/


typedef enum
{
    OPDEVSDK_EN_SEC_CAM_PARA = 0,  //����ͷ�궨��Ϣ
    OPDEVSDK_EN_SEC_SECRET_PARA,  //app����Կ��Ϣ
    OPDEVSDK_EN_SEC_TEMP_PARA,  //����ģ��궨��Ϣ
    OPDEVSDK_EN_SEC_EZVIZ_INFO, //өʯDeviceID�����Ϣ
    OPDEVSDK_EN_SEC_TOF_PARA,  //TOF�궨��Ϣ
    OPDEVSDK_EN_SEC_VCM_PARA,
    OPDEVSDK_EN_SEC_ID_KEY,   //���֤��Կ��Ϣ
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

/* fingerprint ��������� */
typedef struct
{
    unsigned char   byFingerStatus;       //!<��ָ���״̬
    unsigned char   *pbyData;               //!<ָ������
    unsigned char   byRes[6];              //!< reserved
} OPDEVSDK_ST_FP_GET_IMAGE;

/* fingerprintͼ��ߴ�ӿ� */
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

/* LED����ģʽ */
typedef enum
{
    OPDEVSDK_EN_LED_OPT_OFF,             //!< DDM_LEDMODE_OFF ֱ�ӹر�
    OPDEVSDK_EN_LED_OPT_ON,              //!< DDM_LEDMODE_ON  ֱ�Ӵ�
    OPDEVSDK_EN_LED_OPT_BRT_OFF,         //!< DDM_LEDMODE_OFF ʹ�ú����Ʒ�ʽ�ر�
    OPDEVSDK_EN_LED_OPT_BRT_ON,          //!< DDM_LEDMODE_ON  ʹ�ú����Ʒ�ʽ����
    OPDEVSDK_EN_LED_OPT_BRT_ALWAYS_ON,   //!< DDM_LEDMODE_ON  ʹ�ú����Ʒ�ʽ����
    OPDEVSDK_EN_LED_OPT_UNKNOWN,         //!< ���ֵ ����Ϊ���һ��
}OPDEVSDK_EN_LED_OPT;

/* LED�������� */
typedef enum
{
    OPDEVSDK_EN_LED_ENV_HIGH,        //!<  ���ն�
    OPDEVSDK_EN_LED_ENV_LOW,         //!<  ���ն�
    OPDEVSDK_EN_LED_ENV_MAX,        //!< ���ֵ ����Ϊ���һ��
}OPDEVSDK_EN_LED_ENV;

/**@brief led type
*/
typedef enum
{
    OPDEVSDK_EN_LED_MESSAGE = 1,      //!< OPDEVSDK_EN_LED_MESSAGE  ��ϢLED
    OPDEVSDK_EN_LED_ALARM,          //!< OPDEVSDK_EN_LED_ALARM ����LED
    OPDEVSDK_EN_LED_UNLOCK,         //!< OPDEVSDK_EN_LED_UNLOCK����LED
    OPDEVSDK_EN_LED_KEY,            //!<OPDEVSDK_EN_LED_KEY ���������LED
    OPDEVSDK_EN_LED_LABLE,          //!<OPDEVSDK_EN_LED_LABLE ��ǩ�汳���LED
    OPDEVSDK_EN_LED_STATUS,         //!<OPDEVSDK_EN_LED_STATUS ״̬��ʾLED
    OPDEVSDK_EN_LED_STATUS_RED,     //!<OPDEVSDK_EN_LED_STATUS_RED ״̬��ʾLED
    OPDEVSDK_EN_LED_STATUS_BLUE,    //!<OPDEVSDK_EN_LED_STATUS_BLUE ״̬��ʾLED
    OPDEVSDK_EN_LED_STATUS_GREEN,   //!<OPDEVSDK_EN_LED_STATUS_GREEN ״̬��ʾLED
    OPDEVSDK_EN_LED_POWER,          //!<OPDEVSDK_EN_LED_POWER ��Դ��ʾLED
    OPDEVSDK_EN_LED_NETWORK,        //!<OPDEVSDK_EN_LED_NETWORK ������ʾLED
    OPDEVSDK_EN_LED_COMMUNICATION,  //!<OPDEVSDK_EN_LED_COMMUNICATION �Խ�ָʾ��LED
    OPDEVSDK_EN_LED_OPENDOOR,       //!<OPDEVSDK_EN_LED_OPENDOOR ����ָʾ��LED
    OPDEVSDK_EN_LED_CALL,           //!<OPDEVSDK_EN_LED_CALL ����ָʾ��LED
    OPDEVSDK_EN_LED_CARD,           //!<OPDEVSDK_EN_LED_CARD ˢ��ָʾ��LED
    OPDEVSDK_EN_LED_TEL,            //!<OPDEVSDK_EN_LED_TEL ��Ͳָʾ��LED
    OPDEVSDK_EN_LED_KEY_BULE,       //!<OPDEVSDK_EN_LED_KEY_BULE ��ɫ���������LED
    OPDEVSDK_EN_LED_KEY_ORANGE,     //!<OPDEVSDK_EN_LED_KEY_ORANGE ��ɫ���������LED
    OPDEVSDK_EN_LED_STATUS_WHITE,   //!<OPDEVSDK_EN_LED_STATUS_WHITE ״̬��ʾLED
    OPDEVSDK_EN_LED_MAX,            //!< ���ֵ ����Ϊ���һ��
}OPDEVSDK_EN_LED_TYPE;

// �Ƶ���ɫ
typedef enum {
    OPDEVSDK_EN_LIGHT_COLOR_WHITE = 0,         //LED��ʾ��ɫ��
    OPDEVSDK_EN_LIGHT_COLOR_RED,               //LED��ʾ��ɫ��
    OPDEVSDK_EN_LIGHT_COLOR_GREEN,             //LED��ʾ��ɫ��
    OPDEVSDK_EN_LIGHT_COLOR_BLUE,              //LED��ʾ��ɫ��
    OPDEVSDK_EN_LIGHT_COLOR_YELLOW,            //LED��ʾ��ɫ��
    OPDEVSDK_EN_LIGHT_COLOR_MAX,               //LED��ɫ���ֵ
} OPDEVSDK_EN_LIGHT_COLOR;
/**
* led ���������
*/
typedef struct
{
    OPDEVSDK_EN_LED_TYPE  enumType;  //!<LED ����
    OPDEVSDK_EN_LED_OPT   enumOpt;  //!< LED ����ģʽ @see DDM_ledMode
    OPDEVSDK_EN_LED_ENV   enumEnv;  //!< LED ����ģʽ @see DDM_ledMode
    unsigned char   byPwmDuty;   //!< LED PWM�ӿڵ�ռ�ձ�����
    unsigned char    byCh;  //!< chanle
    unsigned char    res1[2];  //!< reserved
    OPDEVSDK_EN_LIGHT_COLOR enumColor; // LED��ɫ
    unsigned char    res[20];  //!< reserved
}OPDEVSDK_ST_LED_PARAM;

/**<ָ��RGB�Ƶ���ɫ״̬*/
typedef enum
{
    OPDEVSDK_EN_FP_RGB_LIGHT_STATUSCLOSE  = 0, //RGB��ȫ��
    OPDEVSDK_EN_FP_RGB_LIGHT_STATUSRED    = 1, //RGB�ƺ�ɫ
    OPDEVSDK_EN_FP_RGB_LIGHT_STATUSBLUE   = 2, //RGB����ɫ
    OPDEVSDK_EN_FP_RGB_LIGHT_STATUSGREEN  = 3, //RGB����ɫ
    OPDEVSDK_EN_FP_RGB_LIGHT_STATUSWHITE  = 4, //RGB�ư�ɫ
    OPDEVSDK_EN_FP_RGB_LIGHT_STATUSYELLOW = 5, //RGB�ƻ�ɫ
    OPDEVSDK_EN_FP_RGB_LIGHT_STATUSCYAN   = 6, //RGB����ɫ
    OPDEVSDK_EN_FP_RGB_LIGHT_STATUSPINK   = 7  //RGB�Ʒ�ɫ
} OPDEVSDK_EN_FP_RGB_LIGHT_STATUS;


/**
* wiegand�ź���������
*/
typedef enum
{
    OPDEVSDK_ST_WIEGAND_SINGAL_TYPE_MIN = 0,
    OPDEVSDK_ST_WIEGAND_SINGAL_TYPE_OK,                  // wiegand OK�ź�
    OPDEVSDK_ST_WIEGAND_SINGAL_TYPE_ERROR,               // wiegand error�ź�
    OPDEVSDK_ST_WIEGAND_SINGAL_TYPE_BUZZER,              // wiegand buzzer�ź�
    OPDEVSDK_ST_WIEGAND_SINGAL_TYPE_TAMPER,              // wiegand tamper�ź�
    OPDEVSDK_ST_WIEGAND_SINGAL_TYPE_MAX,
} OPDEVSDK_ST_WIEGAND_SINGAL_TYPE;

typedef enum
{
    OPDEVSDK_ST_TCIFLUSH = 0,  //ˢ���յ������ݵ��ǲ���
    OPDEVSDK_ST_TCOFLUSH,  //��ˢ��д������ݵ��ǲ�����
    OPDEVSDK_ST_TCIOFLUSH,  //��ͬʱˢ���յ������ݵ��ǲ���������ˢ��д������ݵ��ǲ�����
} OPDEVSDK_ST_TCFLUSH_TYPE;
/**
* wiegand�ź�����
*/
typedef struct
{
    OPDEVSDK_ST_WIEGAND_SINGAL_TYPE    struType;           // wiegand�ź���������
    int     iVal;            // 0 - �͵�ƽ  1 - �ߵ�ƽ
    int     iValMask;        // �� struType == OPDEVSDK_ST_WIEGAND_SINGAL_TYPE_MIN��λ��Ч ͬʱ���������źţ�ÿ��λ��Ӧ���źź���ο� OPDEVSDK_ST_WIEGAND_SINGAL_TYPE
    unsigned char           byRes[60];    // Reserve
} OPDEVSDK_ST_WIEGAND_SINGAL_PIN;

typedef enum
{
    OPDEVSDK_EN_WIEGAND_WORK_MODE_PENETRATE = 0,    // ͸��ģʽ���ϲ���Ӧ�÷�װΤ���������ݺͽ����յ������ݣ�����ģʽ��bsp��װ���͸�ʽ
    OPDEVSDK_EN_WIEGAND_WORK_MODE_KEY = 4,   // ����ģʽ
    OPDEVSDK_EN_WIEGAND_WORK_MODE_26 = 26,   // Τ��26
    OPDEVSDK_EN_WIEGAND_WORK_MODE_27 = 27,    // Τ��27
    OPDEVSDK_EN_WIEGAND_WORK_MODE_34 = 34,    // Τ��34
    OPDEVSDK_EN_WIEGAND_WORK_MODE_35 = 35,  // Τ��35
    OPDEVSDK_EN_WIEGAND_WORK_MODE_58 = 58,  // Τ��58
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
    OPDEVSDK_EN_TEMP_BIND_NONE,         //!< OPDEVSDK_EN_TEMP_BIND_NONE �ް�
    OPDEVSDK_EN_TEMP_BIND_CPU,          //!< cpu�����¶�
    OPDEVSDK_EN_TEMP_BIND_BATTERY,      //!< ��ظ����¶�
    OPDEVSDK_EN_TEMP_BIND_LCM,          //!< ��ʾ�������¶�
    OPDEVSDK_EN_TEMP_BIND_IRIS,         //!< ��Ĥ������¶�
    OPDEVSDK_EN_TEMP_BIND_DEV,         //!< �豸�¶�
    OPDEVSDK_EN_TEMP_BIND_MAX,          //!< OPDEVSDK_EN_TEMP_BIND_MAX �������һ��
}OPDEVSDK_EN_TEMP_BIND;
/*----------------------------------------------*
* Struct/Enum Definition      *
*----------------------------------------------*/

/**
* ָ��led ���������
*/
typedef struct
{
    OPDEVSDK_EN_FP_RGB_LIGHT_STATUS  enumType;  //!<LED ��ɫ byLedType = 0 ��Ч
    unsigned char            byLedType;  //!<LED����  0 - ״̬��  1 - �����
    unsigned char            byPwmDuty;   //!< LED PWM�ӿڵ�ռ�ձ����� 0~100 0��ʾ�ر�  byLedType = 1 ��Ч
    unsigned char            res[30];  //!< reserved
}OPDEVSDK_ST_FINGER_LED_PARAM;


typedef struct
{
    unsigned int  iChannel;                  //!ͨ��
    OPDEVSDK_EN_POWER_CTRL   enumOpt;  //!<  ����ģʽ @see OPDEVSDK_EN_POWER_CTRL
    unsigned int  iDelayTime;                  // �ӳ�ʱ��
    unsigned char    res[32];       //!< reserved
}OPDEVSDK_ST_BEEP_CONTROL;



/**
* wifiģ����Ʋ���
*/
typedef struct
{
    int           iEnable;   //    0 - ʧ�� 1 - ʹ��
    unsigned int  iChannel;                  //!ͨ��
    unsigned char byRes[32]; //!< reserved
} OPDEVSDK_ST_WIFI_CTRL_PARAM;



typedef struct
{
    unsigned int  iChannel;                  //!ͨ��
    OPDEVSDK_EN_POWER_CTRL   enumOpt;  //!<  ����ģʽ @see OPDEVSDK_EN_POWER_CTRL
    unsigned int  iDelayTime;                  // �ӳ�ʱ��
    unsigned char    res[32];       //!< reserved
}OPDEVSDK_ST_IDENTITY_POWER;

typedef struct
{
    unsigned int  iChannel;                  //!ͨ��
    OPDEVSDK_EN_POWER_CTRL   enumOpt;  //!<  ����ģʽ @see OPDEVSDK_EN_POWER_CTRL
    unsigned int  iDelayTime;                  // �ӳ�ʱ��
    unsigned char    res[32];       //!< reserved
}OPDEVSDK_ST_WIFI_POWER;

typedef struct
{
    unsigned int  iChannel;                  //!ͨ�� ��iModel = 0��Ч
    OPDEVSDK_EN_POWER_CTRL   enumOpt;  //!<  ����ģʽ @see OPDEVSDK_EN_POWER_CTRL
    unsigned int  iDelayTime;                  // �ӳ�ʱ��
    unsigned char iModel;       //��λģʽ 0 - ָ��ͨ��ģʽ 1 - ָ���ڵ��� 2 -ָ��vendor product
    unsigned char  res[3];       //!< reserved
    unsigned int   iVendor;                //�豸VID �� iModel = 2��Ч
    unsigned int   iProduct;                //�豸PID �� iModel = 2��Ч
    unsigned char * pbyNodeName;    //�ڵ�����������32�ֽ� ��iModel = 1��Ч
    unsigned int   iNodeLen;                //�ڵ������� �� iModel = 1��Ч
    unsigned char    res1[16];       //!< reserved
}OPDEVSDK_ST_USB_POWER;


typedef struct
{
    OPDEVSDK_EN_POWER_CTRL   enumOpt;  //!<  ����ģʽ @see OPDEVSDK_EN_POWER_CTRL
    unsigned int  iDelayTime;                  // �ӳ�ʱ��
    unsigned char    res[32];       //!< reserved
}OPDEVSDK_ST_FINGER_POWER;

typedef struct
{
    OPDEVSDK_EN_POWER_CTRL   enumOpt;  //!<  ����ģʽ @see OPDEVSDK_EN_POWER_CTRL
    unsigned int  iDelayTime;                  // �ӳ�ʱ��
    unsigned char byCh; // �ڼ�·mcu ��0��ʼ
    unsigned char    res[31];       //!< reserved
}OPDEVSDK_ST_MCU_POWER;

typedef struct
{
    OPDEVSDK_EN_POWER_CTRL   enumOpt;  //!<  ����ģʽ @see OPDEVSDK_EN_POWER_CTRL
    unsigned int  iDelayTime;                  // �ӳ�ʱ��
    unsigned char    res[32];       //!< reserved
}OPDEVSDK_ST_RF_POWER;


/* ��Ƶ������ѡ������ */
typedef struct
{
    unsigned char byEMCardEnable;        // em��ʶ��ʹ��  0-ʧ��  1-ʹ��
    unsigned char byM1CardEnable;        // mifare��ʶ��ʹ�� 0-ʧ��  1-ʹ��
    unsigned char byCPUCardEnable;       // CPU��ʶ��ʹ�� 0-ʧ��  1-ʹ��
    unsigned char byIDCardEnable;        // ���֤ʶ��ʹ�� 0-ʧ��  1-ʹ��
    unsigned char byEnableNFC;           // ��NFC����ʹ�� 0-ʧ��  1-ʹ��
    unsigned char byEnableM1EncCheck;    // m1��������֤���ܿ��� 0-ʧ��  1-ʹ��
    unsigned char byM1EncCheckSectionID; // m1��������֤����ID ��0-100��
    unsigned char byCpuCardReadType;     // cpu������ģʽ��0-�����ţ�1-���ļ�
    unsigned char byDesfireCardEnable;   // desfire��ʶ��ʹ�� 0-ʧ��  1-ʹ��
    unsigned char byFelicaCardEnable;   // Felica��ʶ��ʹ�� 0-ʧ��  1-ʹ��
    char          byRes[62];
}OPDEVSDK_ST_RF_ANTI_COPY_CFG;

/**@brief upgrade mcu data
 */
typedef struct
{
    char * pbyUpgradeFile;  // ������
    unsigned int iUpgradeLen; // ����������
    int *piUpdateStatus;  // ���������нӿڻ��޸ĸ�ֵ���ⲿ�������ʼ��Ϊ 2 �� 0 - �����ɹ� 1 - ����ʧ�� 2 - ������
    unsigned char *pbyPercent; // �������̻��޸ĸ�ֵ�� 0 - 100
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
    int dwTextLen;     // �ɵ�����ִ��text��buffer�ܳ��������ڲ�����ʵ�ʵĳ���
    char* pbyText;        // ���֤��������buffer
    int dwFacePicLen;     // �ɵ�����ִ������ͼƬ��buffer�ܳ��������ڲ�����ʵ�ʵĳ���
    char* pbyFacePic;        // ���֤��������buffer
    int dwFpLen;     // �ɵ�����ִ��ָ�����ݵ�buffer�ܳ��������ڲ�����ʵ�ʵĳ���
    char* pbyFp;        // ���ָ֤������buffer
    char byRes[64];
}OPDEVSDK_ST_GASAM_ID_DATA;


/**< ָ���㷨��Ȩ�����Ľṹ�� */
typedef struct
{
    unsigned char byCode;           // ������룺0x00������Կ������һ������,
                                    //           0x01������Կ�����ڶ�����ԭ��Կ
                                    //           0x02������Ϣ�ӽ���
    unsigned char res[3];           // ����
    unsigned int  len;              // �������ݳ���
    unsigned char *data;            // ʵ������
}OPDEVSDK_ST_FP_AUTHORIZE_IN;

typedef OPDEVSDK_ST_FP_AUTHORIZE_IN OPDEVSDK_ST_FP_AUTHORIZE_OUT;

//ָ���㷨����
typedef int (*OPDEVSDK_FP_ALGO_AWARD)(OPDEVSDK_ST_FP_AUTHORIZE_IN *pstruInBuffer,  OPDEVSDK_ST_FP_AUTHORIZE_OUT *pstruOutBuffer);

typedef struct
{
    unsigned char byDisableMcu; //�Ƿ����mcu�����߳� 0������ 1�����ã� ѡ��ʹ�ܣ��ӿ�������mcu�ϵ�ʧЧ��
    unsigned char byDisableCardIdentify; //�Ƿ���ÿ�ʶ���߳� 0������ 1�����ã� ѡ��ʹ�ܣ�Ӧ���������ƿ�Ƭʶ���߼�����ʶ����ؽӿ�ʧЧ��
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
    unsigned char   byMode;               //��֤ģʽ��0��key A��֤��1��key B��֤��
    unsigned char   bySector;             //��֤�������ţ�0~15��
    unsigned char   byKey[6];             //6�ֽ���֤��Կ����
    unsigned char   byUid[4];             //4�ֽڿ�ƬUID����
}OPDEVSDK_ST_MIFARE_AUTH;

typedef struct{
    unsigned char   byBlockId;            // ���Ŀ�ţ�0x00~0x3F��
    unsigned char   byData[16];
}OPDEVSDK_ST_MIFARE_BLOCK_READ;

typedef struct{
    unsigned char   byBlockId;            // ���Ŀ�ţ�0x00~0x3F��
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
    int iValue;                     // ��ȡ���¶�ֵ
    unsigned char byCh;           //!< ͨ����
    unsigned char byBind;         //!< ��ȡ�󶨵Ĺ������� @see OPDEVSDK_EN_TEMP_BIND
    unsigned char byRes[2];      //Ԥ���ֽ�
}OPDEVSDK_ST_GET_TEMP;

typedef struct
{
    unsigned int    iCrc;           //!<   У��ֵCRC32
    unsigned int    iFlags;         //!<  ������������״̬ @see DDM_partinfo flags
    unsigned int    iConfigSize;    //!< config������С
    unsigned int    iHeopSize;      //!< heop������С
    unsigned int    iEmmcSize;      //!<  emmc������С
    unsigned int    res;            //!<   Ԥ��
} OPDEVSDK_ST_PART_PARA;

/*----------------------------------------------*
* Function Declare         *
*----------------------------------------------*/


/*******************************************
���¿�ʼΪ�����ӿ�
*******************************************/

/* @fn  : opdevsdk_hwif_basic_init_by_options
*  @brief ��hardware basic init
        user can call this function to get the capabilities of hardware

* @param ��pstruParam
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
���¿�ʼΪbeep�ӿ�
*******************************************/
/** @fn      : opdevsdk_hwif_beep_control
* @brief   : ����������
* @param[in]  : pstruLedParam
* @return  :  op_devsdk_errno_code
*/
int opdevsdk_hwif_beep_control(OPDEVSDK_ST_BEEP_CONTROL* pstruParam);
/*******************************************
���¿�ʼΪled�ƽӿ�
*******************************************/
/** @fn      : opdevsdk_hwif_led_set_status
* @brief   : set led status
* @param[in]  : pstruLedParam
* @return  :  op_devsdk_errno_code
*/
int opdevsdk_hwif_led_set_status(OPDEVSDK_ST_LED_PARAM* pstruLedParam);


/*******************************************
���¿�ʼΪָ�ƽӿ�
*******************************************/
/** @fn      : opdevsdk_hwif_finger_power_ctrl
* @brief   : ָ�� ��Դ����
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
���¿�ʼΪUSB�ӿ�
*******************************************/
#define OPDEVSDK_USB_MCU_VENDOR_ID      		(0xfff0)  //mcu������չ��VID
#define OPDEVSDK_USB_MCU_PRODUCT_ID      		(0xfff0)  //mcu������չ��PID
#define OPDEVSDK_USB_TEMP_VENDOR_ID      		(0x2bdf)  //����VID
#define OPDEVSDK_USB_TEMP_PRODUCT_ID      		(0x0101)  //����PID

/** @fn      : opdevsdk_hwif_usb_power_ctrl
* @brief   : usb ��Դ����
* @param[in]  : pstruParam
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_usb_power_ctrl(OPDEVSDK_ST_USB_POWER* pstruParam );
/*******************************************
���¿�ʼΪ4g�ӿ�
*******************************************/

/**
* 4Gģ����Ʋ���
*/
typedef struct
{
    int           iEnable;   //    0 - ʧ�� 1 - ʹ��
    unsigned int  iChannel;                  //!ͨ��
    unsigned char byRes[32]; //!< reserved
} OPDEVSDK_ST_4G_CTRL_PARAM;

typedef struct
{
    unsigned int  iChannel;                  //!ͨ��
    OPDEVSDK_EN_POWER_CTRL   enumOpt;  //!<  ����ģʽ @see OPDEVSDK_EN_POWER_CTRL
    unsigned int  iDelayTime;                  // �ӳ�ʱ��
    unsigned char    res[32];       //!< reserved
}OPDEVSDK_ST_4G_POWER;

/** @fn      : opdevsdk_hwif_4g_ctrl
* @brief   : 4g module ctrl
* @param[in]  : pstruParam
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_4g_ctrl(OPDEVSDK_ST_4G_CTRL_PARAM* pstruParam );

/** @fn      : opdevsdk_hwif_4g_power_ctrl
* @brief   : 4g ��Դ����
* @param[in]  : pstruParam
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_4g_power_ctrl(OPDEVSDK_ST_4G_POWER* pstruParam );

/*******************************************
���¿�ʼΪ5g�ӿ�
*******************************************/
typedef struct
{
    unsigned int  iChannel;                  //!ͨ��
    OPDEVSDK_EN_POWER_CTRL   enumOpt;  //!<  ����ģʽ @see OPDEVSDK_EN_POWER_CTRL
    unsigned int  iDelayTime;                  // �ӳ�ʱ��
    unsigned char    res[32];       //!< reserved
}OPDEVSDK_ST_5G_POWER;

/** @fn      : opdevsdk_hwif_4g_power_ctrl
* @brief   : 4g ��Դ����
* @param[in]  : pstruParam
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_5g_power_ctrl(OPDEVSDK_ST_5G_POWER* pstruParam );
/*******************************************
���¿�ʼΪwifi�ӿ�
*******************************************/
/** @fn      : opdevsdk_hwif_wifi_ctrl
* @brief   : wifi module ctrl
* @param[in]  : pstruParam
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_wifi_ctrl(OPDEVSDK_ST_WIFI_CTRL_PARAM *pstruParam);

/** @fn      : opdevsdk_hwif_wifi_power_ctrl
* @brief   : wifi ��Դ����
* @param[in]  : pstruParam
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_wifi_power_ctrl(OPDEVSDK_ST_WIFI_POWER *pstruParam);

/*******************************************
���¿�ʼΪΤ���ӿ�
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
���¿�ʼΪΤ���ӿ�(����Τ��������SOC��Ч)
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
* @brief   : ����Τ������ģʽ��Ĭ��Ϊ͸��ģʽ
* @param[in]  : fd
* @param[in]  : pstruParam
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_wiegand_set_work_mode(int fd,OPDEVSDK_EN_WIEGAND_WORK_MODE* pstruParam );

/** @fn      : opdevsdk_hwif_wiegand_get_signal_pin_status
* @brief   : ����Τ������ģʽ��Ĭ��Ϊ͸��ģʽ
* @param[in]  : fd
* @param[out]  : pbyStatus  ���״̬��0������ 1��δ����
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_wiegand_get_output_status(int fd,unsigned char *pbyStatus );


/*******************************************
���¿�ʼΪ��ʶ��ӿ�
*******************************************/

/** @fn   : opdevsdk_hwif_rf_power_ctrl
 * @brief  :��Ƶ ��Դ����
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
* @return  : -1--error, 0--timeout  1---�ɹ�
*/
int opdevsdk_hwif_gasam_id_read(int fd, OPDEVSDK_ST_GASAM_ID_DATA *pstruGasamIdData, int iTimeMs);

/*******************************************
���¿�ʼΪ��Ƶ�����ӿڣ���֧����Ƶ����������soc��������Ҳ�������ʶ���̵߳�����£�
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
 * @brief   : TYPEA��Ƭ����
 * @param   : fd �ļ�������
 * @param   : *pstruParam
 * @return  : op_devsdk_errno_code
 */
int opdevsdk_hwif_rf_active_typeA(int fd, OPDEVSDK_ST_TYPTA_ACTIVE *pstruParam);

/** @fn      : opdevsdk_hwif_rf_halt_typeA
 * @brief   : TYPEAЭ��ֹͣ
 * @param   : fd �ļ�������
 * @return  : op_devsdk_errno_code
 */
int opdevsdk_hwif_rf_halt_typeA(int fd);

/** @fn      : opdevsdk_hwif_rf_active_typeB
 * @brief   : TYPEB��Ƭ����
 * @param   : fd �ļ�������
 * @param   : *pstruParam
 * @return  : op_devsdk_errno_code
 */
int opdevsdk_hwif_rf_active_typeB(int fd, OPDEVSDK_ST_TYPTB_ACTIVE *pstruParam);

/** @fn      : opdevsdk_hwif_rf_active_typeC
 * @brief   : TYPEC��Ƭ����
 * @param   : fd �ļ�������
 * @param   : *pstruParam
 * @return  : op_devsdk_errno_code
 */
int opdevsdk_hwif_rf_active_typeC(int fd, OPDEVSDK_ST_TYPTC_ACTIVE *pstruParam);

/** @fn      : opdevsdk_hwif_rf_mifare_auth
 * @brief   : Mifare_Auth��Ƭ��֤
 * @param   : fd �ļ�������
 * @param   : *pstruParam
 * @return  : op_devsdk_errno_code
 */
int opdevsdk_hwif_rf_mifare_auth(int fd, OPDEVSDK_ST_MIFARE_AUTH *pstruParam);

/** @fn      : opdevsdk_hwif_rf_mifare_block_read
 * @brief   : Mifare��Ƭ�������
 * @param   : fd �ļ�������
 * @param   : *pstruParam
 * @return  : op_devsdk_errno_code
 */
int opdevsdk_hwif_rf_mifare_block_read(int fd, OPDEVSDK_ST_MIFARE_BLOCK_READ *pstruParam);

/** @fn      : opdevsdk_hwif_rf_mifare_block_write
 * @brief   : Mifare��Ƭд�����
 * @param   : fd �ļ�������
 * @param   : *pstruParam
 * @return  : op_devsdk_errno_code
 */
int opdevsdk_hwif_rf_mifare_block_write(int fd, OPDEVSDK_ST_MIFARE_BLOCK_WRITE *pstruParam);

/** @fn      : opdevsdk_hwif_rf_judge_uid
 * @brief   : ��֤�Ƿ�ΪUID��
 * @param   : fd �ļ�������
 * @param   : *pstruParam
 * @return  : 0 ���ɹ� -1��ʧ��
 */
int opdevsdk_hwif_rf_judge_uid(int fd);

/** @fn      : opdevsdk_hwif_rf_typeA_ultra_read
 * @brief   : UltraLight�����ȡ�ӿ�
 * @param   : fd �ļ�������
 * @param   : *pstruParam
 * @return  : op_devsdk_errno_code
 */
int opdevsdk_hwif_rf_typeA_ultra_read(int fd, OPDEVSDK_ST_ULTRA_DATA *pstruParam);

/** @fn      : opdevsdk_hwif_rf_cpu_rats
 * @brief   : CPU����λ�ӿ�
 * @param   : fd �ļ�������
 * @param   : *pstruParam
 * @return  : op_devsdk_errno_code
 */
int opdevsdk_hwif_rf_cpu_rats(int fd, OPDEVSDK_ST_CPU_RATS *pstruParam);

/** @fn      : opdevsdk_hwif_rf_cpu_r_block
 * @brief   : CPU�� R blockͨ��
 * @param   : fd �ļ�������
 * @param   : *pstruParam
 * @return  : op_devsdk_errno_code
 */
int opdevsdk_hwif_rf_cpu_r_block(int fd, OPDEVSDK_ST_CPU_R_BLOCK *pstruParam);

/** @fn      : opdevsdk_hwif_rf_cpu_i_block
 * @brief   : CPU�� I blockͨ��
 * @param   : fd �ļ�������
 * @param   : *pstruParam
 * @return  : op_devsdk_errno_code
 */
int opdevsdk_hwif_rf_cpu_i_block(int fd, OPDEVSDK_ST_CPU_I_BLOCK *pstruParam);

/** @fn      : opdevsdk_hwif_rf_typeB_card_transeive
 * @brief   : TypeB ͸���ӿڣ����֤���ʹ��
 * @param   : fd �ļ�������
 * @param   : *pstruParam
 * @return  : op_devsdk_errno_code
 */
int opdevsdk_hwif_rf_typeB_card_transeive(int fd, OPDEVSDK_ST_RF_TYPEB_DATA *pstruParam);


/*******************************************
���¿�ʼΪsamģ��ӿڣ���֧����Ƶ����������soc��������Ҳ�������ʶ���̵߳�����£�
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
    * @brief   : CPU�� I blockͨ��
    * @param   : fd �ļ�������
    * @param   : *pstruParam
    * @return  : op_devsdk_errno_code
    */
int opdevsdk_hwif_sam_i_block(int fd, OPDEVSDK_ST_SAM_ARG *pstruParam);

/** @fn   : opdevsdk_hwif_sam_reset
    * @brief  :sam ��Դ����
    * @param[in] : pstruParam
    * @return  : op_devsdk_errno_code
    */
int opdevsdk_hwif_sam_reset(int fd);

/*******************************************
���¿�ʼΪseģ��ӿڣ���֧����Ƶ����������soc��������Ҳ�������ʶ���̵߳�����£�
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
* @brief  : SE �ļ�ѡ��
* @param[in] : fd
* @param[in] : pstruParam
* @return  : fd
*/
int opdevsdk_hwif_se_select_file(int fd, OPDEVSDK_ST_SE_ARG_SEL_FILE *pstruParam);

/** @fn   : opdevsdk_hwif_se_read_binary
* @brief  : SE ��ȡ������
* @param[in] : fd
* @param[in] : pstruParam
* @return  : fd
*/
int opdevsdk_hwif_se_read_binary(int fd, OPDEVSDK_ST_SE_ARG_READ *pstruParam);

/** @fn   : opdevsdk_hwif_se_get_randoms
* @brief  : SE ��ȡ�����
* @param[in] : fd
* @param[in] : pstruParam
* @return  : fd
*/
int opdevsdk_hwif_se_get_randoms(int fd, OPDEVSDK_ST_SE_ARG_GET_RANDOMS *pstruParam);

/** @fn   : opdevsdk_hwif_se_verify_pin
* @brief  : SE ����У��
* @param[in] : fd
* @param[in] : pstruParam
* @return  : fd
*/
int opdevsdk_hwif_se_verify_pin(int fd, OPDEVSDK_ST_SE_ARG *pstruParam);

/** @fn   : opdevsdk_hwif_se_init_des
* @brief  : se DES�����ʼ��
* @param[in] : fd
* @param[in] : pstruParam
* @return  : fd
*/
int opdevsdk_hwif_se_init_des(int fd, OPDEVSDK_ST_SE_ARG_INIT_DES *pstruParam);

/** @fn   : opdevsdk_hwif_se_init_des
* @brief  : se des ����
* @param[in] : fd
* @param[in] : pstruParam
* @return  : fd
*/
int opdevsdk_hwif_se_calc_des(int fd, OPDEVSDK_ST_SE_ARG *pstruParam);

/*******************************************
���¿�ʼΪ485�����ӿ�
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
* @param[in] : byDirection : 0 :���� 1������
* @return  : -1--error, 0 --- OK
*/
int opdevsdk_hwif_rs485_set_direction(int fd, unsigned char byDirection);

/*******************************************
����Ϊ�����ӿ�
*******************************************/
#define OP_DEVSDK_DEV_TTY_BLE_NAME            "/dev/DDM/tty_ble"  // 485����ͨ�Žڵ�
#define OP_DEVSDK_DEV_BLE_NAME                "/dev/DDM/ble"     // �������ƽڵ㣬��λ��������Ҫ�򿪸ýڵ�

typedef struct
{
    OPDEVSDK_EN_POWER_CTRL   enumOpt;  //!<  ����ģʽ @see OPDEVSDK_EN_POWER_CTRL
    unsigned int  iDelayTime;                  // �ӳ�ʱ��
    char byFdFalg;        //�Ƿ�ָ��������и�λ��2.0��֧��ָ����λ
    int iFd;            //�������
    unsigned char    res[32];       //!< reserved
}OPDEVSDK_ST_BLUETOOTH_POWER;

// �̼���������
typedef struct
{
    char byFwPath[100];                  // �̼�·��
    int reserve;                        // ����
} OPDEVSDK_ST_BLE_SET_FW_ARGS;


// �����ӿ�����
typedef enum
{
    OPDEVSDK_EN_BLE_INFTYPE_SPI= 0,             // SPI�ӿ�����
    OPDEVSDK_EN_BLE_INFTYPE_TTY,                // ���ڽӿ�����
    OPDEVSDK_EN_BLE_INFTYPE_MAX,                // ���ֵ ����Ϊ���һ��
} OPDEVSDK_EN_BLE_GET_INF_TYPE;


/** @fn   : opdevsdk_hwif_ble_open
* @brief  : ������
* @param[in] : *pathName  OP_DEVSDK_DEV_TTY_BLE_NAME or OP_DEVSDK_DEV_BLE_NAME
* @return  : fd
*/
int opdevsdk_hwif_ble_open(const char *pathName);

/** @fn   : opdevsdk_hwif_se_close
* @brief  : �ر�����
* @param[in] : fd
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_ble_close(int fd);

/** @fn   : opdevsdk_hwif_ble_update_fw
* @brief  : ���������̼�����spi�ӿ�ʹ��
* @param[in] : fd
* @param[in] : pstruParam
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_ble_update_fw(int fd , OPDEVSDK_ST_BLE_SET_FW_ARGS  *pstruParam);

/** @fn   : opdevsdk_hwif_ble_clear_rx_buffer
* @brief  : ������ջ��棬����spi�ӿ�����ʹ��
* @param[in] : fd
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_ble_clear_rx_buffer(int fd );

/** @fn   : opdevsdk_hwif_ble_prepare_update
* @brief  : �����̼�����ǰʱ�򻷾�׼���������ϵ縴λ���߼��������ڽӿ�����ģ�����
* @param[in] : fd
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_ble_prepare_update(int fd );

/** @fn   : opdevsdk_hwif_ble_get_interface_type
* @brief  : ��ȡ����Ӳ���ӿ�
* @param[in] : fd
* @param[in] : penumType
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_ble_get_interface_type(int fd , OPDEVSDK_EN_BLE_GET_INF_TYPE *penumType);

/** @fn   : opdevsdk_hwif_bluetooth_power_ctrl
    * @brief  : ���� ��Դ����
    * @param[in] : pstruParam
    * @return  : op_devsdk_errno_code
    */
int opdevsdk_hwif_bluetooth_power_ctrl(OPDEVSDK_ST_BLUETOOTH_POWER *pstruParam);

/*******************************************
����ΪMCU�ӿڣ���ʼ������������mcu����ʹ�ã�
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
����ΪMCU�ӿڣ���ʼ��������mcu������¿���ʹ�ã�
*******************************************/

/** @fn   : opdevsdk_hwif_mcu_power_ctrl
    * @brief  : mcu ��Դ����
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
���¿�ʼΪIO�����ӿ�
*******************************************/
/** @fn   : opdevsdk_hwif_shutdown_button_get_status
* @brief  : get shutdown button status
* @param[in] : NA
* @return  : -1--error, 0--no trigger, 1--trigger
*/
int opdevsdk_hwif_shutdown_button_get_status(void);

/** @fn   : opdevsdk_hwif_shutdown_button_get_status
* @brief  : ��������״̬��ȡ
* @param[in] : index ��� ��1 ��ʼ
* @return  : -1--error, 0--no trigger, 1--trigger
*/
int opdevsdk_hwif_fire_fighting_get_status(int index);

/** @fn   : opdevsdk_hwif_shutdown_button_get_status
* @brief  : �ָ�������ť״̬��ȡ
* @param[in] : index ��� ��1 ��ʼ
* @return  : -1--error, 0--no trigger, 1--trigger
*/
int opdevsdk_hwif_reset_get_status(int index);

typedef struct
{
    unsigned int iInnum;                 // GPIO������ͨ������
    unsigned int iOutnum;                // GPIO�����ͨ������
    unsigned int iRelaynum;              // �̵������ͨ������
    unsigned int reserve[5];            // ����
} OPDEVSDK_ST_EXIO_GET_NUM;

/** @fn   : opdevsdk_hwif_exio_get_num
* @brief  : ��ȡ�ⲿ�������io����
* @param[in] : pstruParam
* @return  : -1--error, 0--no trigger, 1--trigger
*/
int opdevsdk_hwif_exio_get_num(OPDEVSDK_ST_EXIO_GET_NUM *pstruParam);

/*******************************************
���¿�ʼΪ����flash���ݶ�д�ӿ�
*******************************************/
/** @fn   : opdevsdk_hwif_get_boot_param
* @brief  :
* @param[in] : pstSecParam:
* @return  : none
*/
int opdevsdk_hwif_sec_info(OPDEVSDK_ST_SEC_INFO *pstSecParam);

/** @fn   : opdevsdk_hwif_read_part_info
* @brief  : ��ȡ������Ϣ
* @param[in] : pstSecParam:
* @return  : none
*/
int opdevsdk_hwif_read_part_info(OPDEVSDK_ST_PART_PARA *pstSecParam);

/** @fn   : opdevsdk_hwif_read_part_info
* @brief  : д�������Ϣ
* @param[in] : pstSecParam:
* @return  : none
*/
int opdevsdk_hwif_wirte_part_info(OPDEVSDK_ST_PART_PARA *pstSecParam);

/*******************************************
���¿�ʼΪ���֤�Ķ����ӿ�
*******************************************/
/** @fn      : opdevsdk_hwif_identity_power_ctrl
* @brief   : ���֤�Ķ��� ��Դ����
* @param[in]  : pstruParam
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_identity_power_ctrl(OPDEVSDK_ST_IDENTITY_POWER* pstruParam );


/*******************************************
���¿�ʼΪICR�ӿ�
*******************************************/

//ICR ״̬
typedef enum
{
    OPDEVSDK_EN_ICR_STATE_DAY,                  //   ����
    OPDEVSDK_EN_ICR_STATE_NIGHT,                //  ҹ��
    OPDEVSDK_EN_ICR_STATE_MAX,
} OPDEVSDK_EN_ICR_STATE;
/** @fn      : opdevsdk_hwif_icr_set_status
* @brief   : ����icr ״̬
* @param[in]  : iStatus �� OPDEVSDK_EN_ICR_STATE
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_icr_set_status(unsigned int iStatus);

/** @fn      : opdevsdk_hwif_icr_get_status
* @brief   : ��ȡicr ״̬
* @return  : -1--error, ����-״ֵ̬
*/
int opdevsdk_hwif_icr_get_status(void);

/*******************************************
���¿�ʼΪ��Ƶ�ӿ�
*******************************************/

//�����������ýṹ��
typedef struct
{
    unsigned int iChannel;               // ���ñ��ж�Ӧ��ͨ����
    unsigned int iGain;                  // ��������
} OPDEVSDK_ST_SOUND_AMP_GAIN;

typedef enum
{
    OPDEVSDK_EN_SOUND_OUTPATH_EXT_SPK = 0,                    //�л����������
    OPDEVSDK_EN_SOUND_OUTPATH_LOCAL_SPK,                      //�л�������spk
    OPDEVSDK_EN_SOUND_OUTPATH_HP_SPK,                         //�л��������
    OPDEVSDK_EN_SOUND_OUTPATH_LOCAL_PLATFORM,                 //ƽ̨�������·�л������ض�soc��˫оƬ��Ʒ���ã�
    OPDEVSDK_EN_SOUND_OUTPATH_REMOTE_PLATFORM,                //ƽ̨�������·�л���Զ��soc��˫оƬ��Ʒ���ã�
    OPDEVSDK_EN_SOUND_OUTPATH_MAX,
} OPDEVSDK_EN_SOUND_OUTPUT_PATH;

typedef enum
{
    OPDEVSDK_EN_SOUND_INPATH_EXT_MIC = 0,                    //�л������MIC
    OPDEVSDK_EN_SOUND_INPATH_LOCAL_MIC,                      //�л�������MIC
    OPDEVSDK_EN_SOUND_INPATH_LOOPBACK,                       //�л����ز�
    OPDEVSDK_EN_SOUND_INTPATH_HP_MIC,                        //�л�����������
    OPDEVSDK_EN_SOUND_INPATH_LOCAL_PLATFORM,                 //ƽ̨�������·�л����ض�soc��˫оƬ��Ʒ���ã�
    OPDEVSDK_EN_SOUND_INPATH_REMOTE_PLATFORM,                //ƽ̨�������·�л�Զ��soc��˫оƬ��Ʒ���ã�
    OPDEVSDK_EN_SOUND_INPATH_MAX,
} OPDEVSDK_EN_SOUND_INPUT_PATH;


//�����Ƶ·�����ýṹ��
typedef struct
{
    unsigned int iPathChannel;           // ���õ�·��ͨ����
    unsigned int iType;                  // ·������
    unsigned int iStatus;                // ��ͨ״̬
} OPDEVSDK_ST_SOUND_PATH;

//�����������ýṹ��
typedef struct
{
    unsigned int iPathChannel;               // �������ĸ�·��
    unsigned int iPath;                 // ��Ҫ���õ�����·������
    unsigned int iVol;                  // ��������
} OPDEVSDK_ST_SOUND_VOLUME;

#define OPDEVSDK_BIT(nr)			(1UL << (nr))
/* ��Ƶ������ 8K �� 192K�����忴����codecоƬ֧�ֵķ�Χ */
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

//�����������ýṹ��
typedef struct
{
    unsigned int iPathDirection;        // path�ķ���0�������� 1�������
    unsigned int iPath;                  // ��Ҫ���õ�����·������ ����ο� OPDEVSDK_EN_SOUND_INPUT_PATH ��  OPDEVSDK_EN_SOUND_INPUT_PATH
    unsigned int iPathChannel;          // ��ͬ·�����Ƶľ����ĸ�·����Ʃ�磺��������2��������Ҫ��������������Ҫ���ֶ���1�Ͷ���2,channel����1��2.����ֵҪ�����Ŀ��bsp��ͨ
    unsigned int iRate;                  // ������
    unsigned int iBitWidth;             // λ��
    unsigned int iBClk;                 // λʱ��
} OPDEVSDK_ST_SOUND_FORMAT;

/** @fn      : opdevsdk_hwif_mic_open
* @brief   : ��mic
* @param[in]  : iChannel ͨ��
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_mic_open(unsigned int iChannel);

/** @fn      : opdevsdk_hwif_mic_close
* @brief   : �ر�mic
* @param[in]  : iChannel ͨ��
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_mic_close(unsigned int iChannel);

/** @fn      : opdevsdk_hwif_sound_set_amp_gain
* @brief   : ���ù�������
* @param[in]  : iChannel ͨ��
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_sound_set_amp_gain(OPDEVSDK_ST_SOUND_AMP_GAIN* pstruParam);

/** @fn      : opdevsdk_hwif_sound_get_amp_gain
* @brief   : ��ȡ��������
* @param[in]  : iChannel ͨ��
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_sound_get_amp_gain(OPDEVSDK_ST_SOUND_AMP_GAIN* pstruParam);

/** @fn      : opdevsdk_hwif_sound_set_format
* @brief   : ������ƵcodecоƬ�Ĳ��������������ʺ�λ��
* @param[in]  : iChannel ͨ��
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_sound_set_format(OPDEVSDK_ST_SOUND_FORMAT* pstruParam);

/** @fn      : opdevsdk_hwif_sound_get_format
* @brief   : ��ȡ��ƵcodecоƬ�Ĳ��������������ʺ�λ��
* @param[in]  : iChannel ͨ��
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_sound_get_format(OPDEVSDK_ST_SOUND_FORMAT* pstruParam);

/** @fn      : opdevsdk_hwif_amp_open
* @brief   : �򿪹���
* @param[in]  : iChannel ͨ��
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_amp_open(unsigned int iChannel);

/** @fn      : opdevsdk_hwif_amp_close
* @brief   : �رչ���
* @param[in]  : iChannel ͨ��
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_amp_close(unsigned int iChannel);

/** @fn      : opdevsdk_hwif_sound_set_output_channel
* @brief   : ���������Ƶ·��
* @param[in]  : iChannel ͨ��
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_sound_set_output_channel(OPDEVSDK_ST_SOUND_PATH* pstruParam);

/** @fn      : opdevsdk_hwif_sound_get_output_channel
* @brief   : ��ȡ�����Ƶ·��״̬
* @param[in]  : iChannel ͨ��
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_sound_get_output_channel(OPDEVSDK_ST_SOUND_PATH* pstruParam);

/** @fn      : opdevsdk_hwif_sound_set_input_channel
* @brief   : ���������Ƶ·��
* @param[in]  : iChannel ͨ��
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_sound_set_input_channel(OPDEVSDK_ST_SOUND_PATH* pstruParam);

/** @fn      : opdevsdk_hwif_sound_get_input_channel
* @brief   : ��ȡ�����Ƶ·��״̬
* @param[in]  : iChannel ͨ��
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_sound_get_input_channel(OPDEVSDK_ST_SOUND_PATH* pstruParam);

/** @fn      : opdevsdk_hwif_sound_set_output_volume
* @brief   : �����������
* @param[in]  : iChannel ͨ��
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_sound_set_output_volume(OPDEVSDK_ST_SOUND_VOLUME* pstruParam);

/** @fn      : opdevsdk_hwif_sound_get_output_volume
* @brief   : ��ȡ�������
* @param[in]  : iChannel ͨ��
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_sound_get_output_volume(OPDEVSDK_ST_SOUND_VOLUME* pstruParam);

/** @fn      : opdevsdk_hwif_sound_set_input_volume
* @brief   : ������������
* @param[in]  : iChannel ͨ��
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_sound_set_input_volume(OPDEVSDK_ST_SOUND_VOLUME* pstruParam);

/** @fn      : opdevsdk_hwif_sound_get_input_volume
* @brief   : ��ȡ��������
* @param[in]  : iChannel ͨ��
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_sound_get_input_volume(OPDEVSDK_ST_SOUND_VOLUME* pstruParam);



/*******************************************
���¿�ʼΪ����ģ��ӿ�
*******************************************/
//heat ģ�����ò���
typedef struct
{
    unsigned char byPower;            // ��Դ ȡֵ0��/1��
    unsigned char byCh;               // ͨ���� ��0��ʼ
    unsigned char reserve[6];       // Ԥ��
} OPDEVSDK_ST_HEAT_ARGS;

/** @fn      : opdevsdk_hwif_heat_lens_ctrl
* @brief   : ����Camera Lans���ȿ���
* @param[in]  : pstruParam
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_heat_lens_ctrl(OPDEVSDK_ST_HEAT_ARGS * pstruParam );

/** @fn      : opdevsdk_hwif_heat_cpu_ctrl
* @brief   : ����CPU���ȿ���
* @param[in]  : pstruParam
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_heat_cpu_ctrl(OPDEVSDK_ST_HEAT_ARGS * pstruParam );

/** @fn      : opdevsdk_hwif_heat_battery_ctrl
* @brief   : ���õ�ؼ��ȿ���
* @param[in]  : pstruParam
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_heat_battery_ctrl(OPDEVSDK_ST_HEAT_ARGS * pstruParam );

/*******************************************
���¿�ʼ�����ӿ�
*******************************************/

#define OP_DEVSDK_DEV_TS_NAME                 "/dev/DDM/ts"   //����Ļ
#define OP_DEVSDK_DEV_TS_VICE_NAME            "/dev/DDM/ts_vice" //����Ļ

// �̼���������
typedef struct
{
    char byFwPath[100];                  // �̼�·��
    int reserve;                        // ����
} OPDEVSDK_ST_TS_SET_FW_ARGS;

// ��ȡ�̼��汾
typedef struct
{
    unsigned int  iLen;
    unsigned char byVersion[20];
} OPDEVSDK_ST_TS_GET_VERSION;

/** @fn      : opdevsdk_hwif_ts_open
* @brief   : �򿪴��������
* @param[in]  : byName
* @return  : fd
*/
int opdevsdk_hwif_ts_open(char *byName);

/** @fn      : opdevsdk_hwif_ts_open
* @brief   : �رմ��������
* @param[in]  : fd
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_ts_close(int fd );


/** @fn      : opdevsdk_hwif_ts_update_fw
* @brief   : �����������ӿ�
* @param[in]  : fd
* @param[in]  : pstruParam
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_ts_update_fw(int fd,OPDEVSDK_ST_TS_SET_FW_ARGS * pstruParam );

/** @fn      : opdevsdk_hwif_ts_get_chipid
* @brief   : ��ȡоƬID
* @param[in]  : fd
* @return  : -1--error, ����- оƬid
*/
int opdevsdk_hwif_ts_get_chipid(int fd);

/** @fn      : opdevsdk_hwif_ts_do_calibration
* @brief   : оƬУ׼
* @param[in]  : fd
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_ts_do_calibration(int fd);

/** @fn      : opdevsdk_hwif_ts_get_version
* @brief   : ��ȡ�̼��汾��Ϣ
* @param[in]  : pstruParam
* @param[in]  : fd
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_ts_get_version(int fd, OPDEVSDK_ST_TS_GET_VERSION * pstruParam );

/*******************************************
���¿�ʼ���½ӿ�
*******************************************/

typedef struct
{
    unsigned int  iChannel;                  //!ͨ��
    OPDEVSDK_EN_POWER_CTRL   enumOpt;  //!<  ����ģʽ @see OPDEVSDK_EN_POWER_CTRL
    unsigned int  iDelayTime;                  // �ӳ�ʱ��
    unsigned char    res[32];       //!< reserved
}OPDEVSDK_ST_TEMP_MEASURE_POWER;

/** @fn      : opdevsdk_hwif_temp_measure_power_ctrl
* @brief   : ����ģ�� ��Դ����
* @param[in]  : pstruParam
* @return  : op_devsdk_errno_code
*/
int opdevsdk_hwif_temp_measure_power_ctrl(OPDEVSDK_ST_TEMP_MEASURE_POWER* pstruParam );

#ifdef __cplusplus
}
#endif

#endif
