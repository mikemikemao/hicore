
#ifndef UP_FILE_H
#define UP_FILE_H


#define RESERVED_FEA_NUMS	16


#ifdef __cplusplus
extern "C" {
#endif


#define MAX_FILE_NUMS	    5
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
#define UPGRADE_DATA_DEC_CHECK	17		/*���ݽ��ܴ���*/




#define UPGRADE_VERSION_1			0xFE
#define CURRENT_UPGRADE_VERSION		UPGRADE_VERSION_1	/* ��ǰ�����汾��*/

/** @brief:  �ļ����ݼ������� */
typedef enum _UPGRADE_SEC_TYPE_E_
{
    E_UPGRADE_SEC_AES_256_CBC_PKCS7    = 0,         /* aes_256_cbc_pkcs7 */
    E_UPGRADE_SEC_NONE                 = 1,         /* ������*/
    E_UPGRADE_SEC_TYPE_INVALID         = 2,         /* ��Чֵ */
} UPGRADE_SEC_TYPE_E;


typedef enum {
    SYS_UPG_PROC_STEP_GET = 0x00,
    SYS_UPG_PROC_READ_DATA = 0x01,
    SYS_UPG_PROC_UPGRADE = 0x02,
    SYS_UPG_PROC_BACKUP = 0x03,
    SYS_UPG_PROC_INVALID = 0xff,
}SYS_UPG_PROC_STEP;

#define FIRMWARE_MAGIC_NUMBER   ("HKSU")  // �������̼�ͷħ����'0x484b5355'
#define FIRMWARE_MAGIC_LEN      (4)           // ħ���ֳ���
#define FIRMWARE_VERSION        (2)           // �������汾
#define FIRMWARE_HEADER_RES_LEN (40)          // �̼�ͷ�����ֶ��ֽ���
#define KEY_RANDOM_LEN          (4)           // �ļ�������Կ�������ܺ�ĳ���
#define FIRMWARE_LANGUAGE_LEN   (16)
#define FILENAME_LEN            (32)          // �ļ�������

#define AES_256_KEY_LEN_BY_BYTE (32)          // AES������Կ
#define SHA256SUM_BY_BYTES_LEN  (32)          // sha256sum�ֽ���
#define FILE_HEADER_RES_LEN     (20)          // �ļ�ͷ�����ֽ�

#define FILE_PATH_LEN               (128)          //

typedef enum _UPGRADE_PACK_TYPE_E_
{
    E_MAIN_PROGRAM                     = 0,         /* ������������ */
    E_MAIN_PROGRAM_SERVICE_PACKAGE     = 1,         /* �����򲹶��� */
    E_MAIN_PROGRAM_READER_PACKAGE      = 2,         /* ��Ӷ����������� */
    E_MAIN_PROGRAM_MCU_PACKAGE         = 3,         /* mcu������ */
    E_MAIN_PROGRAM_FINGERPRINT_PACKAGE = 4,         /* ָ��ģ�������� */
    E_MAIN_PROGRAM_OTA_PACKAGE         = 5,         /* ������OTA������ */
    E_FIRMWARW_PARTITION               = 6,         /* �̼��������� */
    E_UPGRDE_DEV_TYPE_LIST             = 7,         /* ֧�������豸�ͺ��б� */
    E_TTS_PARTITION                    = 8,         /* TTS��Դ�������� */
    E_ROOTFS_PARTITION                 = 9,         /* ��������ļ�ϵͳ�������� */
    E_KERNEL_PARTITION                 = 10,        /* �ں˷������� */
    E_WIFI_MODULE_PACKAGE              = 11,        /* WIFIģ�������ļ� */
    E_UPGRADE_PACKAGE_TYPE_INVALID,                 /* ��Чֵ */
} UPGRADE_PACKAGE_TYPE_E;


/**
 * @brief:  �������̼�ͷ
 * @note :  128 bytes
 **/
typedef struct _UPGRADE_NEW_FIRMWARE_HEADER_T_
{
    unsigned char           byaMagicNumber[FIRMWARE_MAGIC_LEN];             // FIRMWARE_MAGIC_NUMBER-0x484b5355
    unsigned int            dwVersion;                                      // �������汾��V2.3 => 3 <<16 + 2 <<0
    unsigned int            dwUpgradeHeaderLen;                             // ������ͷ����,�����̼�ͷ�������ļ�ͷ�����ܺ�
    unsigned int            dwDeviceClass;                                  // �豸����
    unsigned char           byaLanguage[FIRMWARE_LANGUAGE_LEN];             /*16 ����λ��Ӧ�����ԣ�1��ʾ֧�֣�0��ʾ��֧�֣����Զ������
                                                                              language[0]:bit0�� Ӣ��    language[0]:bit1����������   language[0]:bit2����������   language[0]:bit3������     language[0]:bit4��������     language[0]:bit5��ӡ����     language[0]:bit6���ɹ���       language[0]:bit7��Խ��
                                                                              language[1]:bit0�� ������  language[1]:bit1��̩��       language[1]:bit2�����ɱ�     language[1]:bit3��ӡ����   language[1]:bit4���ϼ�����   language[1]:bit5��������     language[1]:bit6���Ჴ����     language[1]:bit7�������� 
                                                                              language[2]:bit0���ڿ����� language[2]:bit1����Ɲ����� language[2]:bit2������������ language[2]:bit3������     language[2]:bit4������������ language[2]:bit5�����޵����� language[2]:bit6��������       language[2]:bit7����̩�������� 
                                                                              language[3]:bit0���������� language[3]:bit1��������˹�� language[3]:bit2����������   language[3]:bit3���������� language[3]:bit4������ά���� language[3]:bit5����������   language[3]:bit6��ϣ������     language[3]:bit7��ϣ���� 
                                                                              language[4]:bit0������     language[4]:bit1���������   language[4]:bit2���������   language[4]:bit3��������   language[4]:bit4������ά���� language[4]:bit5��Ų����     language[4]:bit6���ݿ���       language[4]:bit7��˹�工����
                                                                              language[5]:bit0������     language[5]:bit1��������     language[5]:bit2����˹��     language[5]:bit3���������� language[5]:bit4����ɳ������ language[5]:bit5�������     language[5]:bit6����������     language[5]:bit7���������� 
                                                                              language[6]:bit0���������� language[6]:bit1������������ language[6]:bit2��������     language[6]:bit3��������   language[6]:bit4����������   language[6]:bit5����������   language[6]:bit6�������������� language[6]:bit7���������� 
                                                                              language[7]:bit0��������� language[7]:bit1���������*/ 
    unsigned int            dwSupBackup;                                    // �Ƿ�֧�ֱ��ݷ���
    unsigned int            dwFileNumber;                                   // �ļ�����
    unsigned int            dwSoftVersion;                                  // ����汾: V1.3.0 => 1<<24 + 3<<16 + 0<<0
    unsigned int            dwSoftBuildDate;                                // ��������: 160908 => 16<<16 + 9<<8 + 8<<0
    unsigned int            dwSignOffset;                                   // ǩ����Ϣƫ��λ�� 
    unsigned char           byaKeyRandom[KEY_RANDOM_LEN];                   // �Գ���Կ���������

    unsigned int            dwSupHeop;                                      // �Ƿ�֧��HEOP
    unsigned int            UpgradePackLen;                                 // �������ܳ���
    UPGRADE_SEC_TYPE_E      eUpgradeSecType;                                // �ļ����ݼ������� 
    unsigned int            dwFileHeaderOffset;                             // ��ʾ��һ���ļ�ͷ������������ʼλ�õ�ƫ��(���ں���������չ����ȡ�ļ�ͷӦ��������ƫ��λ�ã�����Ӧ��ֱ�Ӳ��ù̼�ͷ����ƫ�ƻ�ȡ)

    unsigned int            dwDevTypeListFileIndex;                         //  ����ṩ���ֶα�ʶ�ڼ����ļ�ʱ�豸�ͺ��б�����ʶ�����������豸�ͺ��б�ʱ��ֵΪ0 ����ǿ�ƹ涨�豸�ͺ��б���Ϊ��һ���ļ���ԭ���ǻ���V2.1�������ṹ��д��Ӧ�����������޷����ݣ�
	unsigned int            dwAvailableSoftVersion; 						//  �̼��Ӹð汾����
    unsigned int            dwAvailableBeginTime;                           //  �̼��Ӹ����ڿ�ʼ��Ч
	unsigned int            dwAvailableDay; 								//  �̼���Ч��
	unsigned char           byaResFeature[FIRMWARE_HEADER_RES_LEN];         // �����ֶ� 

} UPGRADE_NEW_FIRMWARE_HEADER_T, *UPGRADE_NEW_FIRMWARE_HEADER_P;


/**
 * @brief:  �������ļ�ͷ
 * @note :  96 bytes
 **/
typedef struct _UPGRADE_FILE_HEADER_T_
{
    char                    byaFileName[FILENAME_LEN];                // �ļ���
    unsigned int            dwStartOffset;                            // ��ʼλ��
    unsigned int            dwFileEncryptLen;                         // �ļ�����
    unsigned char           byaSha256Sum[SHA256SUM_BY_BYTES_LEN];     // �ļ���������hashֵ������sha256�㷨��
    UPGRADE_PACKAGE_TYPE_E  enPackageType;                            // ����������
    unsigned char           byaResFeature[FILE_HEADER_RES_LEN];       // �����ֶ�
} UPGRADE_FILE_HEADER_T, *UPGRADE_FILE_HEADER_P;

/*************************************************
Function: 		hex2string
Description: 	hex�ַ�����ת����string�ַ���������printf��ʾ��
Input: 			hex:ԭ�ַ�����
                len:hex����ĳ���
Return:
*************************************************/
int tool_print_hex(char *pbySrc, int sdwLen);

/*******************************************************************************
* ������  : checkFirmwareHead
* ��  ��  : ��ȡ��ͷ ������У��
* ��  ��  : - iSrcfd              :http���
*       : - pDecryFirmHead      :���ܺ�Ĺ̼�ͷ
*       : - pEncryFirmHead      :���ܺ�Ĺ̼�ͷ
* ��  ��  : ��
* ����ֵ  : 0     : �ɹ�
*         ���� : ʧ��
*******************************************************************************/
int checkFirmwareHead(int iSrcfd,UPGRADE_NEW_FIRMWARE_HEADER_T* pDecryFirmHead,UPGRADE_NEW_FIRMWARE_HEADER_T* pEncryFirmHead);


/*******************************************************************************
* ������  : getEncryptFirmHeadFileHeads
* ��  ��  : ��ȡ���ܵĹ̼�ͷ���ļ�ͷ
* ��  ��  : - iSrcfd              :http���
*       : - pEncryFirmHead      :���ܺ�Ĺ̼�ͷ
*       : - firmHeadFileHeads   :���ܵĹ̼�ͷ���ļ�ͷ�ڴ�ռ�
*       : - firmHeadFileHeadsLen:���ܵĹ̼�ͷ���ļ�ͷ�ڴ�ռ䳤��
* ��  ��  : ��
* ����ֵ  : 0     : �ɹ�
*         ���� : ʧ��
*******************************************************************************/
int getEncryptFirmHeadFileHeads(int iSrcfd,UPGRADE_NEW_FIRMWARE_HEADER_T* pEncryFirmHead, char* firmHeadFileHeads,int firmHeadFileHeadsLen);


/*******************************************************************************
* ������  : getFirmHeadFileHeadsSha256
* ��  ��  : ��ȡ���ܵĹ̼�ͷ���ļ�ͷժҪֵ
* ��  ��  : - firmHeadFileHeads   :���ܵĹ̼�ͷ���ļ�ͷ�ڴ�ռ�
*       : - firmHeadFileHeadsLen:���ܵĹ̼�ͷ���ļ�ͷ�ڴ�ռ䳤��
*       : - byaSha256Sum        :ժҪֵ
* ��  ��  : ��
* ����ֵ  : 0     : �ɹ�
*         ���� : ʧ��
*******************************************************************************/
int getFirmHeadFileHeadsSha256(char* firmHeadFileHeads,int firmHeadFileHeadsLen,unsigned char* byaSha256Sum);

/*******************************************************************************
* ������  : getPlainFirmHeadFileHeads
* ��  ��  : ��ȡ���ĵĹ̼�ͷ���ļ�ͷժҪֵ
* ��  ��  : - firmHeadFileHeads   :���ܵĹ̼�ͷ���ļ�ͷ�ڴ�ռ�
*       : - firmHeadFileHeadsLen:���ܵĹ̼�ͷ���ļ�ͷ�ڴ�ռ䳤��
*       : - byaSha256Sum        :ժҪֵ
* ��  ��  : ��
* ����ֵ  : 0     : �ɹ�
*         ���� : ʧ��
*******************************************************************************/
int getPlainFirmHeadFileHeads(char* firmHeadFileHeads,int firmHeadFileHeadsLen);


/*******************************************************************************
* ������  : getFileHeads
* ��  ��  : ��ȡ�ļ�ͷ
* ��  ��  : - firmHeadFileHeads                    :���ܵĹ̼�ͷ���ļ�ͷ�ڴ�ռ�
*       : - firmHeadFileHeadsLen                 :���ܵĹ̼�ͷ���ļ�ͷ�ڴ�ռ䳤��
*       : - UPGRADE_NEW_FIRMWARE_HEADER_T        :�̼�ͷ
* ��  ��  : ��
* ����ֵ  : UPGRADE_FILE_HEADER_P
*   
*******************************************************************************/
UPGRADE_FILE_HEADER_P getFileHeads(char* firmHeadFileHeads,int firmHeadFileHeadsLen, UPGRADE_NEW_FIRMWARE_HEADER_T* pDecryFirmHead);

/*******************************************************************************
* ������  : getSessionKey
* ��  ��  : ��ȡ�Ự��Կ
* ��  ��  : - random                               :�������������������
*        : - byaKey                               :���ɵĻỰ��Կ
* ��  ��  : ��
* ����ֵ  : 0     : �ɹ�
*         ���� : ʧ��
*******************************************************************************/
int getSessionKey(unsigned char* random,unsigned char* byaKey);

/*******************************************************************************
* ������  : unpack_file_data_each
* ��  ��  : ����ÿ�������ļ�
* ��  ��  : - pstFileHeader                        :�ļ�ͷ
*        : - byaKey                               :�Ự��Կ
* ��  ��  : ��
* ����ֵ  : 0     : �ɹ�
*         ���� : ʧ��
*******************************************************************************/
int unpack_file_data_each(int iSrcfd,UPGRADE_FILE_HEADER_P pstFileHeader, unsigned char byaKey[AES_256_KEY_LEN_BY_BYTE]);

/*******************************************************************************
* ������  : unpack_dev_type_info
* ��  ��  : �����豸�ͺ��б�����
* ��  ��  : - pstFileHeader                        :�ļ�ͷ
*        : - byaKey                               :�Ự��Կ
* ��  ��  : ��
* ����ֵ  : 0     : �ɹ�
*         ���� : ʧ��
*******************************************************************************/
int unpack_dev_type_info(int iSrcfd,UPGRADE_FILE_HEADER_P pstFileHeader, unsigned char byaKey[AES_256_KEY_LEN_BY_BYTE]);

#ifdef __cplusplus
}
#endif


#endif

