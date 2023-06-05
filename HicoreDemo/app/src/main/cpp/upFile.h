
#ifndef _INCupFile_h
#define _INCupFile_h
#include "bootflash.h"
#ifdef __cplusplus
extern "C" {
#endif


#define MAX_FILE_NUMS	    32
#define UPGRADE_FILE_MD5_LEN (16)   //������������16�ֽ�ΪMD5ֵ

#define UPGRADE_PROG_ERR	-1      /*����ִ�г���*/      
#define UPGRADE_OK  		0			
#define UPGRADE_NO_DEVICE  	1		/*û���豸*/
#define UPGRADE_NO_FILE  	2		/*û���ҵ������ļ�*/
#define UPGRADE_DATA_ERROR  3		/*�����ļ����ݲ�����*/
#define UPGRADE_PROCESSING  4       /*�������ڽ���*/
#define UPGRADE_NO_MEM      5       /*�ڴ治��*/
#define UPGRADE_LINK_ERR    6       /*��FTP ����������ʧ��*/
#define UPGRADE_LANG_MIS    7       /*���������Բ�ƥ��*/
#define UPGRADE_DEVICE_ERR  8       /*�豸���Ͳ�ƥ��*/
#define UPGRADE_OEMCODE_ERR 9       /*oemCode ��ƥ��*/
#define UPGRADE_VERSION_ERR	10		/*�����汾��ƥ��*/
#define UPGRADE_FLASH_ERR	11		/*flash ����*/
#define UPGRADE_RAM_ERR		12		/*ram ����*/
#define UPGRADE_DSP_RAM_ERR	13		/*dsp ram ����*/
#define UPGRADE_CANCEL_UPDATE	14		/*���غ�ɾ�����صİ汾*/
#define UPGRADE_DATA_LEN_CHECK	15		/*���ݳ��Ȳ���*/
#define UPGRADE_DATA_PARA_CHECK	16		/*���ݲ�������*/



#define UPGRADE_VERSION_1			0xFE
#define CURRENT_UPGRADE_VERSION		UPGRADE_VERSION_1	/* ��ǰ�����汾��*/

#define UPGRADE_MODE_FTP  	0
#define UPGRADE_MODE_DEV    1			
#define UPGRADE_MODE_BAK  	2
#define UPGRADE_MODE_NET  	3
#define UPGRADE_MODE_BUF  	4
#define UPGRADE_MODE_NET_WEB 5
#define UPGRADE_MODE_HTTP	6
#define UPGRADE_MODE_NET_EXTEND  	7        /* ����������չģʽ����Ҫ����IE���� */
#define UPGRADE_MODE_ONVIF			8		/*ͨ��ONVIF����*/

typedef enum {
    SYS_UPG_PROC_STEP_GET = 0x00,
    SYS_UPG_PROC_READ_DATA = 0x01,
    SYS_UPG_PROC_UPGRADE = 0x02,
    SYS_UPG_PROC_BACKUP = 0x03,
    SYS_UPG_PROC_INVALID = 0xff,
}SYS_UPG_PROC_STEP;

typedef struct
{
    char pURL[512];               /*�ļ�url   http://domainname/filepatch or ftp://*/
	char pUser[64];               /* �����û��� */
    char pPwd[64];               /* �������� */
	HPR_UINT16 ulHttpPort;
	int iBufLen;
	int maxtrytimes;/*ʧ�����Դ���*/
} UPGRADE_ONLINE_PARAM_T;

typedef enum {
    SYS_UPG_PROC_TYPE_MAIN = 0x00,//������
    SYS_UPG_PROC_TYPE_ZIGBEE = 0x01,//zigbee����
}SYS_UPG_PROC_TYPE;//��������

typedef struct{
    HPR_UINT8 updateMode;
	HPR_UINT8 programType;//���SYS_UPG_PROC_TYPE
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
    HPR_INT8 *pcReadDataBuf;            /* �Ѷ�����ָ�� */
    HPR_INT32 iReadLen;                 /* �Ѷ����ݳ��� */
    HPR_INT32 iBufHaveLen;
	HPR_UINT32 maxRetry;
	UPGRADE_ONLINE_PARAM_T struParam;
}SYS_UPG_PARAM;

typedef struct{
	char        fileName[32];		/* �ļ��� */
	UINT32      startOffset;		/* ��ʼλ�� */
	UINT32      fileLen;			/* �ļ����� */
	UINT32      checkSum;			/* У��� */
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
    UINT32      header_check_sum;   /* �ļ�ͷУ��� */
    UINT32      header_length;      /* �ļ�ͷ���� */
    UINT32      file_nums;          /* �ļ����� */
    UINT32      language;           /* ���� */
    UINT32      device_class;       /* 1 �C DS9000 DVR */
    UINT32      oemCode;            /* 1 �C hikvision  */
	UINT8		up_type;			/* �������� */
    UINT8       res_feature[RESERVED_FEA_NUMS];    /* �����ֶ� */
	unsigned char	res[11];
	unsigned char	std_neu;			/* ��׼�棬���԰� UPGRADE_STDNEU_VERSION*/
    UINT32      soft_version;           /* ����汾: V1.3.0 => 1<<24 + 3<<16 + 0<<0  */  
    UINT32      soft_builddate;         /* ��������: 160908 => 16<<16 + 9<<8 + 8<<0 */
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

