
#ifndef _INCupFile_h
#define _INCupFile_h
#include "bootflash.h"
#ifdef __cplusplus
extern "C" {
#endif


#define MAX_FILE_NUMS	    32
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



#define UPGRADE_VERSION_1			0xFE
#define CURRENT_UPGRADE_VERSION		UPGRADE_VERSION_1	/* 当前升级版本号*/

#define UPGRADE_MODE_FTP  	0
#define UPGRADE_MODE_DEV    1			
#define UPGRADE_MODE_BAK  	2
#define UPGRADE_MODE_NET  	3
#define UPGRADE_MODE_BUF  	4
#define UPGRADE_MODE_NET_WEB 5
#define UPGRADE_MODE_HTTP	6
#define UPGRADE_MODE_NET_EXTEND  	7        /* 网络升级扩展模式，主要用于IE升级 */
#define UPGRADE_MODE_ONVIF			8		/*通过ONVIF升级*/

typedef enum {
    SYS_UPG_PROC_STEP_GET = 0x00,
    SYS_UPG_PROC_READ_DATA = 0x01,
    SYS_UPG_PROC_UPGRADE = 0x02,
    SYS_UPG_PROC_BACKUP = 0x03,
    SYS_UPG_PROC_INVALID = 0xff,
}SYS_UPG_PROC_STEP;

typedef struct
{
    char pURL[512];               /*文件url   http://domainname/filepatch or ftp://*/
	char pUser[64];               /* 登入用户名 */
    char pPwd[64];               /* 登入密码 */
	HPR_UINT16 ulHttpPort;
	int iBufLen;
	int maxtrytimes;/*失败重试次数*/
} UPGRADE_ONLINE_PARAM_T;

typedef enum {
    SYS_UPG_PROC_TYPE_MAIN = 0x00,//主程序
    SYS_UPG_PROC_TYPE_ZIGBEE = 0x01,//zigbee程序
}SYS_UPG_PROC_TYPE;//升级类型

typedef struct{
    HPR_UINT8 updateMode;
	HPR_UINT8 programType;//详见SYS_UPG_PROC_TYPE
    HPR_UINT8 res[2];
    HPR_UINT32 iUserID;
    HPR_UINT32 serverIp;
	HPR_UINT16 serverPort;
	char *pUserName;
	char *pPassword;
    HPR_INT64 iSrcfd;
    char *pFnName;
    char *pDataBuf;
    HPR_INT32 iBufLen;
    HPR_INT8 *pcReadDataBuf;            /* 已读数据指针 */
    HPR_INT32 iReadLen;                 /* 已读数据长度 */
    HPR_INT32 iBufHaveLen;
	HPR_UINT32 maxRetry;
	UPGRADE_ONLINE_PARAM_T struParam;
}SYS_UPG_PARAM;

typedef struct{
	char        fileName[32];		/* 文件名 */
	UINT32      startOffset;		/* 起始位置 */
	UINT32      fileLen;			/* 文件长度 */
	UINT32      checkSum;			/* 校验和 */
}UPGRADE_FILE_HEADER;

typedef enum 
{
	UPGRADE_INVALID_VERSION = 0,
	UPGRADE_STD_VERSION = 1,
	UPGRADE_NEU_VERSION = 2,
}UPGRADE_STDNEU_VERSION;

/* file header of digicap.mav */
typedef struct
{   /* 64 bytes */
    UINT32      magic_number;       /* 0x484b5753 */
    UINT32      header_check_sum;   /* 文件头校验和 */
    UINT32      header_length;      /* 文件头长度 */
    UINT32      file_nums;          /* 文件个数 */
    UINT32      language;           /* 语言 */
    UINT32      device_class;       /* 1 – DS9000 DVR */
    UINT32      oemCode;            /* 1 – hikvision  */
	UINT8		up_type;			/* 升级类型 */
    UINT8       res_feature[RESERVED_FEA_NUMS];    /* 保留字段 */
	unsigned char	res[11];
	unsigned char	std_neu;			/* 标准版，中性版 UPGRADE_STDNEU_VERSION*/
    UINT32      soft_version;           /* 软件版本: V1.3.0 => 1<<24 + 3<<16 + 0<<0  */  
    UINT32      soft_builddate;         /* 构建日期: 160908 => 16<<16 + 9<<8 + 8<<0 */
    UPGRADE_FILE_HEADER  fileHeader[0];
}FIRMWARE_HEADER;

typedef struct
{
    HPR_INT8 *pcData;
    HPR_UINT32 uiDataLen;
    HPR_UINT32 uiReadSumLen;
}SYS_NET_EXTEND_DATA_T;

int getUpgradPercent();
SYS_UPG_PROC_STEP sys_upg_step(SYS_UPG_PROC_STEP enumUpgStep);
int sys_upgrade(SYS_UPG_PARAM *pUpgParam);
int sys_upgrade_ex(SYS_UPG_PARAM *pUpgParam, BOOL bHicoreStarted);
HPR_INT32 upgrade_online_by_http(UPGRADE_ONLINE_PARAM_T *pstruParam);



#ifdef __cplusplus
}
#endif


#endif

