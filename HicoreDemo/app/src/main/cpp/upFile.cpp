#include <stdint.h>
#include <memory.h>
#include <malloc.h>
#include <endian.h>
#include "upFile.h"
//#include "prtUtil.h"
#include "arpa/inet.h"
//#include "ezviz_app_common_tools.h"
//#include "openssl/evp.h"
//#include "openssl/aes.h"
//#include "openssl/sha.h"

//#include "securec_api.h"
#include "FileOp.h"
//#include "paramLib.h"
#include "FileOp.h"

#define APP_PACK_NAME "digicap"

#include "LogUtil.h"

#define SOFT_MAJOR_VERSION  1
#define SOFT_MINOR_VERSION  0
#define SOFT_REVISION       0
#define MAJOR_SHIFT 	24
#define MINOR_SHIFT 	16
#define REVISION_SHIFT 0

#define DEVICE_CLASS   1018
#define SUPPORT_LANGUAGE 2  //֧������

#define FILE_PATH "/sdcard/digicap.dav"


unsigned int getSoftVersion(char *buf)
{
    if (buf)
    {
        sprintf(buf, "V%d.%d.%d", SOFT_MAJOR_VERSION, SOFT_MINOR_VERSION, SOFT_REVISION);
    }
    return (((SOFT_MAJOR_VERSION)<<(MAJOR_SHIFT)) | ((SOFT_MINOR_VERSION)<<(MINOR_SHIFT)) |((SOFT_REVISION)<<(REVISION_SHIFT)));
}

unsigned int getDeviceClass(){
    return DEVICE_CLASS;
}

unsigned int getLanguage(){
    return SUPPORT_LANGUAGE;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////
///С����
/*+++++++++++++++++++++++++
 * Function:       convertData
 * Description:   ���ü򵥵����������ݱ任�����������ļ��Ĵ���ͽ��  
 * Input:          src - source data
                       len - data length
 * Output:     dst - destination  data
 * Return:     0 -- OK / -1 -- Failed      
 *-----------------------------*/
static int convertData(char *src, char *dst, int len)
{
    /* �̶��Ļ������������任 */
    unsigned char magic[] = {0xba, 0xcd, 0xbc, 0xfe, 0xd6, 0xca, 0xdd, 0xd3,
                    0xba, 0xb9, 0xa3, 0xab, 0xbf, 0xcb, 0xb5, 0xbe};
    int i, j;
    int magiclen, startmagic;

    if(src==NULL || dst==NULL)
    {
        APP_ERR("Invalid input param: src = 0x%x, dst = 0x%x\n", src, dst);
        return -1;
    }

    magiclen = sizeof(magic);
    

    i = startmagic = 0;
    while(i < len)
    {
        /* ��startmagic����ÿ����ѭ��magic����ʼλ�� */
        for(j=0; j<magiclen && i<len; j++, i++)
        {
            *dst++ = *src++ ^ magic[(startmagic+j)%magiclen];   /* �������任 */
        }
        startmagic = (startmagic+1) % magiclen;
    }
    return 0;
}



static int decAesCbc(unsigned char* sessionKey, unsigned char* iv,unsigned char* encrypData,int encrypDataLen, unsigned char* plainData)
{
    int ret  = 0;
    /*EVP_CIPHER_CTX *pstCtx  = NULL;
    int sdwDecryptLen = 0;
    
    pstCtx = EVP_CIPHER_CTX_new();
    if (NULL == pstCtx)
    {
        APP_ERR("EVP_CIPHER_CTX_new fail\n");
        ret = UPGRADE_PROG_ERR;
        goto err;
    }

    ret = EVP_DecryptInit_ex(pstCtx, EVP_aes_256_cbc(), NULL, sessionKey, iv);
    if (1 != ret)
    {
        APP_ERR("EVP_DecryptInit_ex fail\n");
        ret = UPGRADE_PROG_ERR;
        goto err;
    }
    EVP_CIPHER_CTX_set_padding(pstCtx, 1);

    EVP_DecryptUpdate(pstCtx, plainData, &sdwDecryptLen, (unsigned char*)encrypData, encrypDataLen); //������16�ֽ������ݽ��м���

    EVP_DecryptFinal(pstCtx, plainData + sdwDecryptLen, &sdwDecryptLen);
err:
    if (NULL != pstCtx)
    {
        EVP_CIPHER_CTX_free(pstCtx);
        pstCtx = NULL;
    }
    return ret;*/
    return 0;
}


static int getSha256(char* buff,int buffLen,unsigned char* byaSha256Sum)
{
    int ret = 0;
    /*SHA256_CTX stSha256Ctx;
    
    SHA256_Init(&stSha256Ctx);
    SHA256_Update(&stSha256Ctx, buff, buffLen);
    SHA256_Final(byaSha256Sum ,&stSha256Ctx);*/

    return 0;
}

static int getFileData(int iSrcfd,char* data,int dataLen)
{
#if 0
    int len = http_read_line(iSrcfd, data, dataLen);
    if(len != dataLen)
    {
        APP_ERR("ezdev_http_read_msg failed revlen =%d needlen =%d\n",len,sizeof(UPGRADE_NEW_FIRMWARE_HEADER_T));
        return UPGRADE_DATA_LEN_CHECK;
    }
#endif
    static int current = 0;
    int ret = 0;
    ret = FileOp::GetDataSize(FILE_PATH);
    if(ret < 0)
    {
        APP_ERR("GetDataSize failed ret =%d\n",ret);
        return ret;
    }
    APP_PRT("fileLen =%d\n",ret);
    char* buff = (char*) malloc(ret);
    ret = FileOp::ReadData(FILE_PATH,(unsigned char*)buff,ret);
    if(ret != 0)
    {
        APP_ERR("ReadData failed ret =%d\n",ret);
        goto err;
    }
    memcpy(data,buff+current,dataLen);
    current = current + dataLen;
err:
    if (buff)
    {
        free(buff);
        buff = NULL;
    }
    return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
///ҵ�����ʵ��
static int checkGetFirmwareHeads(UPGRADE_NEW_FIRMWARE_HEADER_T* pEecryFirmHead, unsigned int dwDeviceClass, unsigned char byaLanguage[FIRMWARE_LANGUAGE_LEN],
                                 UPGRADE_NEW_FIRMWARE_HEADER_T* pDecryFirmHead){
    int ret = 0;
    int iFileNum = 0;
    int iFileHeadLen = 0;
    int iHeadTotalLen = 0;
    unsigned int curVersion = 0;
    char szVersion[14] = {0};
    unsigned char byaLanguageTmp[FIRMWARE_LANGUAGE_LEN] = {0};

    if (NULL == pEecryFirmHead || NULL == pDecryFirmHead){
        return UPGRADE_DATA_PARA_CHECK;
    }

    if (0 != convertData((char *)pEecryFirmHead, (char *)pDecryFirmHead,
        sizeof(UPGRADE_NEW_FIRMWARE_HEADER_T)))
    {
        APP_ERR("convert firmHeader error!!!\n");
        return UPGRADE_DATA_ERROR;
    }

    /**@brief: ħ�����ж� */
    if (0 != memcmp((const void*)pDecryFirmHead->byaMagicNumber,(const void*)FIRMWARE_MAGIC_NUMBER, FIRMWARE_MAGIC_LEN))
    {
        APP_ERR("magic number not corret[%s][%s]\n",FIRMWARE_MAGIC_NUMBER,pDecryFirmHead->byaMagicNumber);
        return UPGRADE_DATA_ERROR;
    }

    /**@brief: �豸�ͺŲ�ƥ��*/
    if (dwDeviceClass != ntohl(pDecryFirmHead->dwDeviceClass))
    {
        APP_ERR("dev class dismatch,[%u], [%u]\n", dwDeviceClass, ntohl(pDecryFirmHead->dwDeviceClass));
        return UPGRADE_DEVICE_ERR;
    }

    curVersion = getSoftVersion(szVersion);
    if(ntohl(pDecryFirmHead->dwSoftVersion) < curVersion)
    {
        APP_ERR("Upgrade failed, downgrading is not supported, cur version: 0x%x, upgraded version: 0x%x!\n",
                    curVersion,ntohl(pDecryFirmHead->dwSoftVersion));
        return UPGRADE_VERSION_ERR;
    }

    /**@brief: ����У�����(����������������ֶ�ȫ����bootparam�������ֶΣ����ڻ���ڣ���ͨ��) */
    /**@note: �Ȱ�λ���ٺ�bootparam�ڵ������ֶν��бȽ�*/
    for (int sdwIndex = 0; sdwIndex < FIRMWARE_LANGUAGE_LEN; sdwIndex++)
    {
        byaLanguageTmp[sdwIndex] = byaLanguage[sdwIndex] & pDecryFirmHead->byaLanguage[sdwIndex];
    }
    ret = memcmp(byaLanguageTmp, byaLanguage, FIRMWARE_LANGUAGE_LEN);
    if (0 != ret)
    {
        APP_ERR("languagr dismatch language = %d \n",pDecryFirmHead->byaLanguage[0]);
        return UPGRADE_LANG_MIS;
    }

    return UPGRADE_OK;
} 


static int saveAppPack()
{
    return 0;
}



///////////////////////////////////////////////////////////////////////////////////////////////////////
///ҵ���߼�
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
int checkFirmwareHead(int iSrcfd,UPGRADE_NEW_FIRMWARE_HEADER_T* pDecryFirmHead,UPGRADE_NEW_FIRMWARE_HEADER_T* pEncryFirmHead)
{
    int ret = 0;
    unsigned int dwDeviceClass = 0;
    unsigned char byaLanguage[FIRMWARE_LANGUAGE_LEN] = {0};

    if (NULL == pDecryFirmHead || NULL == pEncryFirmHead)
    {
        return UPGRADE_DATA_PARA_CHECK;
    }
    //��ȡ����
    ret = getFileData(iSrcfd,(char*)pEncryFirmHead,sizeof(UPGRADE_NEW_FIRMWARE_HEADER_T));
    if(ret != 0)
    {
        APP_ERR("getFileData failed ret =%d \n",ret);
        return ret;
    }
    
    dwDeviceClass = getDeviceClass();
    byaLanguage[0] = getLanguage();//Ӣ��
    ret = checkGetFirmwareHeads(pEncryFirmHead,dwDeviceClass, byaLanguage,pDecryFirmHead);
    if (ret != 0){
        APP_ERR("checkGetFirmwareHeads failed ret =%d!\n",ret);
        return UPGRADE_VERSION_ERR;
    }

    return UPGRADE_OK;
}


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
int getEncryptFirmHeadFileHeads(int iSrcfd,UPGRADE_NEW_FIRMWARE_HEADER_T* pEncryFirmHead, char* firmHeadFileHeads,int firmHeadFileHeadsLen)
{
    int ret = 0;
    int fileHeadsLen = firmHeadFileHeadsLen - sizeof(UPGRADE_NEW_FIRMWARE_HEADER_T);
    if (NULL == pEncryFirmHead || NULL == firmHeadFileHeads)
    {
        return UPGRADE_DATA_PARA_CHECK;
    }

    memcpy(firmHeadFileHeads, pEncryFirmHead, sizeof(UPGRADE_NEW_FIRMWARE_HEADER_T));
    //��ȡ����
    ret = getFileData(iSrcfd,firmHeadFileHeads+sizeof(UPGRADE_NEW_FIRMWARE_HEADER_T),fileHeadsLen);
    if(ret != 0)
    {
        APP_ERR("getFileData failed ret =%d \n",ret);
        return ret;
    }
    
    return UPGRADE_OK;
}

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
int getFirmHeadFileHeadsSha256(char* firmHeadFileHeads,int firmHeadFileHeadsLen,unsigned char* byaSha256Sum)
{
    if (NULL == firmHeadFileHeads || NULL == byaSha256Sum)
    {
        return UPGRADE_DATA_PARA_CHECK;
    }
    return getSha256(firmHeadFileHeads,firmHeadFileHeadsLen,byaSha256Sum);
}


/*******************************************************************************
* ������  : getPlainFirmHeadFileHeads
* ��  ��  : ��ȡ���ĵĹ̼�ͷ���ļ�ͷ
* ��  ��  : - firmHeadFileHeads   :���ܵĹ̼�ͷ���ļ�ͷ�ڴ�ռ�
*       : - firmHeadFileHeadsLen:���ܵĹ̼�ͷ���ļ�ͷ�ڴ�ռ䳤��
*       : - byaSha256Sum        :ժҪֵ
* ��  ��  : ��
* ����ֵ  : 0     : �ɹ�
*         ���� : ʧ��
*******************************************************************************/
int getPlainFirmHeadFileHeads(char* firmHeadFileHeads,int firmHeadFileHeadsLen)
{
    if (NULL == firmHeadFileHeads)
    {
        return UPGRADE_DATA_PARA_CHECK;
    }
    
    if (0 != convertData(firmHeadFileHeads,firmHeadFileHeads,firmHeadFileHeadsLen))
    {
        APP_ERR("convert firmHeader error!!!\n");
        return UPGRADE_DATA_ERROR;
    }

    return 0;
}


int getSessionKey(unsigned char* random,unsigned char*byaKey)
{
    return 0;
}

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
UPGRADE_FILE_HEADER_P getFileHeads(char* firmHeadFileHeads,int firmHeadFileHeadsLen, UPGRADE_NEW_FIRMWARE_HEADER_T* pDecryFirmHead)
{
    if (NULL == firmHeadFileHeads || NULL == pDecryFirmHead)
    {
        return NULL;
    }
    
    int devfile_filehead_idx = ntohl(pDecryFirmHead->dwDevTypeListFileIndex);
    APP_PRT("devfile_filehead_idx = %d \n",devfile_filehead_idx);
    return (UPGRADE_FILE_HEADER_P)(firmHeadFileHeads + ntohl(pDecryFirmHead->dwFileHeaderOffset));
}

/*
int savePackFile(int iSrcfd, UPGRADE_NEW_FILE_HEADER_T* fileHead)
{
    int ret = 0;
    int diff = 0;
    char* buff = NULL;
    char filePath[100] = {0};
    unsigned char byaIv[AES_256_KEY_LEN_BY_BYTE]  = {0};
    unsigned char byaSha256Sum[SHA256SUM_BY_BYTES_LEN] = {0};
    
    if(NULL == fileHead)
    {
        return UPGRADE_DATA_PARA_CHECK;
    }
    
    buff = (char*)malloc(fileHead->dwFileEncryptLen);
    if (NULL == buff)
    {
        APP_ERR("malloc failed !\n");
        return UPGRADE_NO_MEM;
    }

    //��ȡ����
    unsigned int len = http_read_line(iSrcfd, buff, fileHead->dwFileEncryptLen);
    if(len != fileHead->dwFileEncryptLen )
    {
        APP_ERR("ezdev_http_read_msg failed revlen =%d needlen =%d\n",len,sizeof(UPGRADE_NEW_FIRMWARE_HEADER_T));
        ret = UPGRADE_DATA_LEN_CHECK;
        goto err;
    }

    //����
    ret = decAesCbc(byaSha256Sum, byaIv, (unsigned char*)buff, len, (unsigned char*)buff);
    if(ret != 0)
    {
        APP_ERR("decAesCbc failed ret =%d\n",ret);
        ret = UPGRADE_DATA_DEC_CHECK;
        goto err;
    }

    //SHA256У��
    getSha256(buff,len,byaSha256Sum);

    if (memcmp_sec(byaSha256Sum, SHA256SUM_BY_BYTES_LEN, fileHead->byaSha256Sum, SHA256SUM_BY_BYTES_LEN, &diff))
    {
        APP_ERR("sha256 check failed ret =%d\n",ret);
        ret = UPGRADE_DATA_ERROR;
        goto err;
    }

    if (0 == memcmp_sec(fileHead->byaFileName, sizeof(APP_PACK_NAME), APP_PACK_NAME, sizeof(APP_PACK_NAME), &diff))
    {
        ret = saveAppPack();
    }
    else
    {
        sprintf(filePath, "U://%s", fileHead->byaFileName);
        ret = writeFile(filePath, buff, len);
        if(ret != 0)
        {
            APP_ERR("writeFile failed ret =%d\n",ret);
            ret = UPGRADE_DATA_ERROR;
            goto err;
        }
    }

err:
    if(NULL != buff)
    {
        free(buff);
        buff = NULL;
    }
    return ret;
}*/

