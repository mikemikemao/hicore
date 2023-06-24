
#ifndef UP_FILE_H
#define UP_FILE_H


#define RESERVED_FEA_NUMS	16


#ifdef __cplusplus
extern "C" {
#endif


#define MAX_FILE_NUMS	    5
#define UPGRADE_FILE_MD5_LEN (16)   //升级包里的最后16字节为MD5值

#define UPGRADE_PROG_ERR	-1      /*程序执行出错*/      
#define UPGRADE_OK  		0			
#define UPGRADE_NO_DEVICE  	1		/*没有设备*/
#define UPGRADE_NO_FILE  	2		/*没有找到升级文件*/
#define UPGRADE_DATA_ERROR  3		/*升级文件数据不兼容*/
#define UPGRADE_PROCESSING  4       /*升级正在进行*/
#define UPGRADE_NO_MEM      5       /*内存不足*/
#define UPGRADE_LINK_ERR    6       /*与FTP 服务器连接失败*/
#define UPGRADE_LANG_MIS    7       /*升级包语言不匹配*/
#define UPGRADE_DEVICE_ERR  8       /*设备类型不匹配*/
#define UPGRADE_OEMCODE_ERR 9       /*oemCode 不匹配*/
#define UPGRADE_VERSION_ERR	10		/*升级版本不匹配*/
#define UPGRADE_FLASH_ERR	11		/*flash 不足*/
#define UPGRADE_RAM_ERR		12		/*ram 不足*/
#define UPGRADE_DSP_RAM_ERR	13		/*dsp ram 不足*/
#define UPGRADE_CANCEL_UPDATE	14		/*下载后删除下载的版本*/
#define UPGRADE_DATA_LEN_CHECK	15		/*数据长度不够*/
#define UPGRADE_DATA_PARA_CHECK	16		/*数据参数错误*/
#define UPGRADE_DATA_DEC_CHECK	17		/*数据解密错误*/




#define UPGRADE_VERSION_1			0xFE
#define CURRENT_UPGRADE_VERSION		UPGRADE_VERSION_1	/* 当前升级版本号*/

/** @brief:  文件数据加密类型 */
typedef enum _UPGRADE_SEC_TYPE_E_
{
    E_UPGRADE_SEC_AES_256_CBC_PKCS7    = 0,         /* aes_256_cbc_pkcs7 */
    E_UPGRADE_SEC_NONE                 = 1,         /* 不加密*/
    E_UPGRADE_SEC_TYPE_INVALID         = 2,         /* 无效值 */
} UPGRADE_SEC_TYPE_E;


typedef enum {
    SYS_UPG_PROC_STEP_GET = 0x00,
    SYS_UPG_PROC_READ_DATA = 0x01,
    SYS_UPG_PROC_UPGRADE = 0x02,
    SYS_UPG_PROC_BACKUP = 0x03,
    SYS_UPG_PROC_INVALID = 0xff,
}SYS_UPG_PROC_STEP;

#define FIRMWARE_MAGIC_NUMBER   ("HKSU")  // 升级包固件头魔术字'0x484b5355'
#define FIRMWARE_MAGIC_LEN      (4)           // 魔术字长度
#define FIRMWARE_VERSION        (2)           // 升级包版本
#define FIRMWARE_HEADER_RES_LEN (40)          // 固件头保留字段字节数
#define KEY_RANDOM_LEN          (4)           // 文件数据密钥经过加密后的长度
#define FIRMWARE_LANGUAGE_LEN   (16)
#define FILENAME_LEN            (32)          // 文件名长度

#define AES_256_KEY_LEN_BY_BYTE (32)          // AES加密密钥
#define SHA256SUM_BY_BYTES_LEN  (32)          // sha256sum字节数
#define FILE_HEADER_RES_LEN     (20)          // 文件头保留字节

#define FILE_PATH_LEN               (128)          //

typedef enum _UPGRADE_PACK_TYPE_E_
{
    E_MAIN_PROGRAM                     = 0,         /* 主程序升级包 */
    E_MAIN_PROGRAM_SERVICE_PACKAGE     = 1,         /* 主程序补丁包 */
    E_MAIN_PROGRAM_READER_PACKAGE      = 2,         /* 外接读卡器升级包 */
    E_MAIN_PROGRAM_MCU_PACKAGE         = 3,         /* mcu升级包 */
    E_MAIN_PROGRAM_FINGERPRINT_PACKAGE = 4,         /* 指纹模组升级包 */
    E_MAIN_PROGRAM_OTA_PACKAGE         = 5,         /* 主程序OTA升级包 */
    E_FIRMWARW_PARTITION               = 6,         /* 固件分区镜像 */
    E_UPGRDE_DEV_TYPE_LIST             = 7,         /* 支持升级设备型号列表 */
    E_TTS_PARTITION                    = 8,         /* TTS资源分区镜像 */
    E_ROOTFS_PARTITION                 = 9,         /* 主程序根文件系统分区镜像 */
    E_KERNEL_PARTITION                 = 10,        /* 内核分区镜像 */
    E_WIFI_MODULE_PACKAGE              = 11,        /* WIFI模块升级文件 */
    E_UPGRADE_PACKAGE_TYPE_INVALID,                 /* 无效值 */
} UPGRADE_PACKAGE_TYPE_E;


/**
 * @brief:  升级包固件头
 * @note :  128 bytes
 **/
typedef struct _UPGRADE_NEW_FIRMWARE_HEADER_T_
{
    unsigned char           byaMagicNumber[FIRMWARE_MAGIC_LEN];             // FIRMWARE_MAGIC_NUMBER-0x484b5355
    unsigned int            dwVersion;                                      // 升级包版本：V2.3 => 3 <<16 + 2 <<0
    unsigned int            dwUpgradeHeaderLen;                             // 升级包头长度,包括固件头和所有文件头长度总和
    unsigned int            dwDeviceClass;                                  // 设备类型
    unsigned char           byaLanguage[FIRMWARE_LANGUAGE_LEN];             /*16 各个位对应的语言，1表示支持，0表示不支持，可以多种组合
                                                                              language[0]:bit0： 英语    language[0]:bit1：简体中文   language[0]:bit2：繁体中文   language[0]:bit3：日语     language[0]:bit4：朝鲜语     language[0]:bit5：印度语     language[0]:bit6：蒙古语       language[0]:bit7：越南
                                                                              language[1]:bit0： 马来文  language[1]:bit1：泰国       language[1]:bit2：菲律宾     language[1]:bit3：印尼文   language[1]:bit4：孟加拉文   language[1]:bit5：老挝文     language[1]:bit6：尼泊尔文     language[1]:bit7：丹麦文 
                                                                              language[2]:bit0：乌克兰文 language[2]:bit1：乌茲别克语 language[2]:bit2：亚美尼亚语 language[2]:bit3：俄语     language[2]:bit4：保加利亚文 language[2]:bit5：克罗地亚文 language[2]:bit6：冰岛语       language[2]:bit7：加泰罗尼亚文 
                                                                              language[3]:bit0：匈牙利语 language[3]:bit1：吉尔吉斯语 language[3]:bit2：土库曼语   language[3]:bit3：土耳其文 language[3]:bit4：塞尔维亚文 language[3]:bit5：塞索托语   language[3]:bit6：希伯来语     language[3]:bit7：希腊语 
                                                                              language[4]:bit0：德语     language[4]:bit1：意大利语   language[4]:bit2：意第绪语   language[4]:bit3：拉丁文   language[4]:bit4：拉脱维亚语 language[4]:bit5：挪威文     language[4]:bit6：捷克语       language[4]:bit7：斯洛伐克文
                                                                              language[5]:bit0：法语     language[5]:bit1：波兰语     language[5]:bit2：波斯语     language[5]:bit3：爱尔兰语 language[5]:bit4：爱沙尼亚语 language[5]:bit5：瑞典语     language[5]:bit6：瓜拉尼语     language[5]:bit7：立陶宛语 
                                                                              language[6]:bit0：索马里语 language[6]:bit1：罗马尼亚语 language[6]:bit2：芬兰语     language[6]:bit3：荷兰语   language[6]:bit4：葡萄牙语   language[6]:bit5：西班牙语   language[6]:bit6：阿尔巴尼亚文 language[6]:bit7：阿拉伯文 
                                                                              language[7]:bit0：马其顿文 language[7]:bit1：马耳他文*/ 
    unsigned int            dwSupBackup;                                    // 是否支持备份分区
    unsigned int            dwFileNumber;                                   // 文件个数
    unsigned int            dwSoftVersion;                                  // 软件版本: V1.3.0 => 1<<24 + 3<<16 + 0<<0
    unsigned int            dwSoftBuildDate;                                // 构建日期: 160908 => 16<<16 + 9<<8 + 8<<0
    unsigned int            dwSignOffset;                                   // 签名信息偏移位置 
    unsigned char           byaKeyRandom[KEY_RANDOM_LEN];                   // 对称秘钥派生随机数

    unsigned int            dwSupHeop;                                      // 是否支持HEOP
    unsigned int            UpgradePackLen;                                 // 升级包总长度
    UPGRADE_SEC_TYPE_E      eUpgradeSecType;                                // 文件数据加密类型 
    unsigned int            dwFileHeaderOffset;                             // 表示第一个文件头基于升级包起始位置的偏移(便于后续兼容扩展，读取文件头应该依赖该偏移位置，而不应该直接采用固件头长度偏移获取)

    unsigned int            dwDevTypeListFileIndex;                         //  因此提供该字段标识第几个文件时设备型号列表，便于识别处理。不存在设备型号列表时该值为0 （不强制规定设备型号列表作为第一个文件的原因是基于V2.1升级包结构编写的应用升级程序无法兼容）
	unsigned int            dwAvailableSoftVersion; 						//  固件从该版本降级
    unsigned int            dwAvailableBeginTime;                           //  固件从该日期开始生效
	unsigned int            dwAvailableDay; 								//  固件有效期
	unsigned char           byaResFeature[FIRMWARE_HEADER_RES_LEN];         // 保留字段 

} UPGRADE_NEW_FIRMWARE_HEADER_T, *UPGRADE_NEW_FIRMWARE_HEADER_P;


/**
 * @brief:  升级包文件头
 * @note :  96 bytes
 **/
typedef struct _UPGRADE_FILE_HEADER_T_
{
    char                    byaFileName[FILENAME_LEN];                // 文件名
    unsigned int            dwStartOffset;                            // 起始位置
    unsigned int            dwFileEncryptLen;                         // 文件长度
    unsigned char           byaSha256Sum[SHA256SUM_BY_BYTES_LEN];     // 文件数据明文hash值，采用sha256算法。
    UPGRADE_PACKAGE_TYPE_E  enPackageType;                            // 升级包类型
    unsigned char           byaResFeature[FILE_HEADER_RES_LEN];       // 保留字段
} UPGRADE_FILE_HEADER_T, *UPGRADE_FILE_HEADER_P;

/*************************************************
Function: 		hex2string
Description: 	hex字符数组转换成string字符串，用于printf显示等
Input: 			hex:原字符数组
                len:hex数组的长度
Return:
*************************************************/
int tool_print_hex(char *pbySrc, int sdwLen);

/*******************************************************************************
* 函数名  : checkFirmwareHead
* 描  述  : 获取包头 并进行校验
* 输  入  : - iSrcfd              :http句柄
*       : - pDecryFirmHead      :解密后的固件头
*       : - pEncryFirmHead      :加密后的固件头
* 输  出  : 无
* 返回值  : 0     : 成功
*         其他 : 失败
*******************************************************************************/
int checkFirmwareHead(int iSrcfd,UPGRADE_NEW_FIRMWARE_HEADER_T* pDecryFirmHead,UPGRADE_NEW_FIRMWARE_HEADER_T* pEncryFirmHead);


/*******************************************************************************
* 函数名  : getEncryptFirmHeadFileHeads
* 描  述  : 获取加密的固件头和文件头
* 输  入  : - iSrcfd              :http句柄
*       : - pEncryFirmHead      :加密后的固件头
*       : - firmHeadFileHeads   :加密的固件头和文件头内存空间
*       : - firmHeadFileHeadsLen:加密的固件头和文件头内存空间长度
* 输  出  : 无
* 返回值  : 0     : 成功
*         其他 : 失败
*******************************************************************************/
int getEncryptFirmHeadFileHeads(int iSrcfd,UPGRADE_NEW_FIRMWARE_HEADER_T* pEncryFirmHead, char* firmHeadFileHeads,int firmHeadFileHeadsLen);


/*******************************************************************************
* 函数名  : getFirmHeadFileHeadsSha256
* 描  述  : 获取加密的固件头和文件头摘要值
* 输  入  : - firmHeadFileHeads   :加密的固件头和文件头内存空间
*       : - firmHeadFileHeadsLen:加密的固件头和文件头内存空间长度
*       : - byaSha256Sum        :摘要值
* 输  出  : 无
* 返回值  : 0     : 成功
*         其他 : 失败
*******************************************************************************/
int getFirmHeadFileHeadsSha256(char* firmHeadFileHeads,int firmHeadFileHeadsLen,unsigned char* byaSha256Sum);

/*******************************************************************************
* 函数名  : getPlainFirmHeadFileHeads
* 描  述  : 获取明文的固件头和文件头摘要值
* 输  入  : - firmHeadFileHeads   :加密的固件头和文件头内存空间
*       : - firmHeadFileHeadsLen:加密的固件头和文件头内存空间长度
*       : - byaSha256Sum        :摘要值
* 输  出  : 无
* 返回值  : 0     : 成功
*         其他 : 失败
*******************************************************************************/
int getPlainFirmHeadFileHeads(char* firmHeadFileHeads,int firmHeadFileHeadsLen);


/*******************************************************************************
* 函数名  : getFileHeads
* 描  述  : 获取文件头
* 输  入  : - firmHeadFileHeads                    :加密的固件头和文件头内存空间
*       : - firmHeadFileHeadsLen                 :加密的固件头和文件头内存空间长度
*       : - UPGRADE_NEW_FIRMWARE_HEADER_T        :固件头
* 输  出  : 无
* 返回值  : UPGRADE_FILE_HEADER_P
*   
*******************************************************************************/
UPGRADE_FILE_HEADER_P getFileHeads(char* firmHeadFileHeads,int firmHeadFileHeadsLen, UPGRADE_NEW_FIRMWARE_HEADER_T* pDecryFirmHead);

/*******************************************************************************
* 函数名  : getSessionKey
* 描  述  : 获取会话密钥
* 输  入  : - random                               :升级包中所带的随机数
*        : - byaKey                               :生成的会话密钥
* 输  出  : 无
* 返回值  : 0     : 成功
*         其他 : 失败
*******************************************************************************/
int getSessionKey(unsigned char* random,unsigned char* byaKey);

/*******************************************************************************
* 函数名  : unpack_file_data_each
* 描  述  : 处理每个升级文件
* 输  入  : - pstFileHeader                        :文件头
*        : - byaKey                               :会话密钥
* 输  出  : 无
* 返回值  : 0     : 成功
*         其他 : 失败
*******************************************************************************/
int unpack_file_data_each(int iSrcfd,UPGRADE_FILE_HEADER_P pstFileHeader, unsigned char byaKey[AES_256_KEY_LEN_BY_BYTE]);

/*******************************************************************************
* 函数名  : unpack_dev_type_info
* 描  述  : 解析设备型号列表数据
* 输  入  : - pstFileHeader                        :文件头
*        : - byaKey                               :会话密钥
* 输  出  : 无
* 返回值  : 0     : 成功
*         其他 : 失败
*******************************************************************************/
int unpack_dev_type_info(int iSrcfd,UPGRADE_FILE_HEADER_P pstFileHeader, unsigned char byaKey[AES_256_KEY_LEN_BY_BYTE]);

#ifdef __cplusplus
}
#endif


#endif

