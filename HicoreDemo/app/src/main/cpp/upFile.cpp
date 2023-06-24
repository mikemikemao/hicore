#include <stdint.h>
#include <memory.h>
#include <malloc.h>
#include <endian.h>
#include "upFile.h"
//#include "prtUtil.h"
#include "arpa/inet.h"
//#include "ezviz_app_common_tools.h"
#include "openssl/evp.h"
#include "openssl/aes.h"
#include "openssl/sha.h"

//#include "securec_api.h"
#include "FileOp.h"
//#include "paramLib.h"
#include "FileOp.h"

#include "LogUtil.h"
#include "include/openssl/ossl_typ.h"

typedef unsigned int UPGRADE_DEV_TYPE;

#define SOFT_MAJOR_VERSION  1
#define SOFT_MINOR_VERSION  0
#define SOFT_REVISION       0
#define MAJOR_SHIFT 	24
#define MINOR_SHIFT 	16
#define REVISION_SHIFT 0

#define DEVICE_CLASS   1018
#define SUPPORT_LANGUAGE 2  //支持中文

#define PROC_ENC_PER_BLOCK_LEN (100*1024)
#define AES_BLOCK_LEN_BY_BYTE  (16)



#define DIGICAP_FILE_PATH   "/sdcard/digicap.dav"

static char s_tmpSessionKey[AES_256_KEY_LEN_BY_BYTE] = {0x21,0xe6,0x4f,0xde,0xc6,0x1b,0x13,0x5a,0x45,0x9a,0x9b,0x27,0x75,0xe7,0x18,0xe6,0xf8,0xcc,0x5f,0x10,0x04,0x4f,0x49,0xe0,0x39,0x93,0xcd,0x6e,0x0a,0x24,0xab,0x56};


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
///小工具
/*+++++++++++++++++++++++++
 * Function:       convertData
 * Description:   利用简单的异或进行数据变换，用于升级文件的打包和解包  
 * Input:          src - source data
                       len - data length
 * Output:     dst - destination  data
 * Return:     0 -- OK / -1 -- Failed      
 *-----------------------------*/
static int convertData(char *src, char *dst, int len)
{
    /* 固定的幻数，用于异或变换 */
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
        /* 用startmagic控制每次内循环magic的起始位置 */
        for(j=0; j<magiclen && i<len; j++, i++)
        {
            *dst++ = *src++ ^ magic[(startmagic+j)%magiclen];   /* 进行异或变换 */
        }
        startmagic = (startmagic+1) % magiclen;
    }
    return 0;
}

/*************************************************
Function: 		hex2string
Description: 	hex字符数组转换成string字符串，用于printf显示等
Input: 			hex:原字符数组
                len:hex数组的长度
Return:
*************************************************/
int tool_print_hex(char *pbySrc, int sdwLen)
{
    int         sdwIndex   = 0;
    int         sdwMsb     = 0;
    int         sdwLsb     = 0;
    const char  c_byaTab[] = {'0', '1', '2', '3', '4', '5', '6', '7',
                              '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

    if (NULL == pbySrc || 0 > sdwLen)
    {
        APP_ERR("param err\n");
        return -1;
    }

    for (sdwIndex = 0; sdwIndex < sdwLen; sdwIndex++)
    {
        sdwMsb =((*(pbySrc + sdwIndex)) & 0xf0) >> 4;
        sdwLsb = (*(pbySrc + sdwIndex)) & 0xf;
        APP_PRT("0X%c%c ", c_byaTab[sdwMsb], c_byaTab[sdwLsb]);
    }

    APP_PRT("\n");

    return 0;
}

static EVP_CIPHER_CTX * aesInit(unsigned char* sessionKey,unsigned char* iv)
{
    int ret  = 0;
    EVP_CIPHER_CTX *pstCtx  = NULL;
    int sdwDecryptLen = 0;

    pstCtx = EVP_CIPHER_CTX_new();
    if (NULL == pstCtx)
    {
        APP_ERR("EVP_CIPHER_CTX_new fail\n");
        goto err;
    }

    ret = EVP_DecryptInit_ex(pstCtx, EVP_aes_256_cbc(), NULL, sessionKey, iv);
    if (1 != ret)
    {
        APP_ERR("EVP_DecryptInit_ex fail\n");
        goto err;
    }
    EVP_CIPHER_CTX_set_padding(pstCtx, 1);

    return pstCtx;

err:
    if (NULL != pstCtx)
    {
        EVP_CIPHER_CTX_free(pstCtx);
        pstCtx = NULL;
    }
    return NULL;
}

static void aesDeinit(EVP_CIPHER_CTX *pstCtx)
{
    if (NULL != pstCtx)
    {
        EVP_CIPHER_CTX_free(pstCtx);
        pstCtx = NULL;
    }
}


static int getSha256(char* buff,int buffLen,unsigned char* byaSha256Sum)
{
    int ret = 0;
    SHA256_CTX stSha256Ctx;

    SHA256_Init(&stSha256Ctx);
    SHA256_Update(&stSha256Ctx, buff, buffLen);
    SHA256_Final(byaSha256Sum ,&stSha256Ctx);

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
    ret = FileOp::GetDataSize(DIGICAP_FILE_PATH);
    if(ret < 0)
    {
        APP_ERR("GetDataSize failed ret =%d\n",ret);
        return ret;
    }
    APP_PRT("fileLen =%d\n",ret);
    char* buff = (char*) malloc(ret);
    ret = FileOp::ReadData(DIGICAP_FILE_PATH,(unsigned char*)buff,ret);
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


static int getFileDataEx(int iSrcfd,char* data,int offset,int dataLen)
{
#if 0
    int len = http_read_line(iSrcfd, data, dataLen);
    if(len != dataLen)
    {
        APP_ERR("ezdev_http_read_msg failed revlen =%d needlen =%d\n",len,sizeof(UPGRADE_NEW_FIRMWARE_HEADER_T));
        return UPGRADE_DATA_LEN_CHECK;
    }
#endif
    int ret = 0;
    ret = FileOp::GetDataSize(DIGICAP_FILE_PATH);
    if(ret < 0)
    {
        APP_ERR("GetDataSize failed ret =%d\n",ret);
        return ret;
    }
    APP_PRT("fileLen =%d\n",ret);
    char* buff = (char*) malloc(ret);
    ret = FileOp::ReadData(DIGICAP_FILE_PATH,(unsigned char*)buff,ret);
    if(ret != 0)
    {
        APP_ERR("ReadData failed ret =%d\n",ret);
        goto err;
    }
    memcpy(data,buff+offset,dataLen);

err:
    if (buff)
    {
        free(buff);
        buff = NULL;
    }
    return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
///业务具体实现
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

    /**@brief: 魔幻数判断 */
    if (0 != memcmp((const void*)pDecryFirmHead->byaMagicNumber,(const void*)FIRMWARE_MAGIC_NUMBER, FIRMWARE_MAGIC_LEN))
    {
        APP_ERR("magic number not corret[%s][%s]\n",FIRMWARE_MAGIC_NUMBER,pDecryFirmHead->byaMagicNumber);
        return UPGRADE_DATA_ERROR;
    }

    /**@brief: 设备型号不匹配*/
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

    /**@brief: 语言校验规则(如果升级包的语言字段全覆盖bootparam的语言字段（大于或等于）则通过) */
    /**@note: 先按位与再和bootparam内的语言字段进行比较*/
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


///////////////////////////////////////////////////////////////////////////////////////////////////////
///业务逻辑
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
int checkFirmwareHead(int iSrcfd,UPGRADE_NEW_FIRMWARE_HEADER_T* pDecryFirmHead,UPGRADE_NEW_FIRMWARE_HEADER_T* pEncryFirmHead)
{
    int ret = 0;
    unsigned int dwDeviceClass = 0;
    unsigned char byaLanguage[FIRMWARE_LANGUAGE_LEN] = {0};

    if (NULL == pDecryFirmHead || NULL == pEncryFirmHead)
    {
        return UPGRADE_DATA_PARA_CHECK;
    }
    //获取数据
    ret = getFileData(iSrcfd,(char*)pEncryFirmHead,sizeof(UPGRADE_NEW_FIRMWARE_HEADER_T));
    if(ret != 0)
    {
        APP_ERR("getFileData failed ret =%d \n",ret);
        return ret;
    }
    
    dwDeviceClass = getDeviceClass();
    byaLanguage[0] = getLanguage();//英文
    ret = checkGetFirmwareHeads(pEncryFirmHead,dwDeviceClass, byaLanguage,pDecryFirmHead);
    if (ret != 0){
        APP_ERR("checkGetFirmwareHeads failed ret =%d!\n",ret);
        return UPGRADE_VERSION_ERR;
    }

    return UPGRADE_OK;
}


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
int getEncryptFirmHeadFileHeads(int iSrcfd,UPGRADE_NEW_FIRMWARE_HEADER_T* pEncryFirmHead, char* firmHeadFileHeads,int firmHeadFileHeadsLen)
{
    int ret = 0;
    int fileHeadsLen = firmHeadFileHeadsLen - sizeof(UPGRADE_NEW_FIRMWARE_HEADER_T);
    if (NULL == pEncryFirmHead || NULL == firmHeadFileHeads)
    {
        return UPGRADE_DATA_PARA_CHECK;
    }

    memcpy(firmHeadFileHeads, pEncryFirmHead, sizeof(UPGRADE_NEW_FIRMWARE_HEADER_T));
    //获取数据
    ret = getFileData(iSrcfd,firmHeadFileHeads+sizeof(UPGRADE_NEW_FIRMWARE_HEADER_T),fileHeadsLen);
    if(ret != 0)
    {
        APP_ERR("getFileData failed ret =%d \n",ret);
        return ret;
    }
    
    return UPGRADE_OK;
}

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
int getFirmHeadFileHeadsSha256(char* firmHeadFileHeads,int firmHeadFileHeadsLen,unsigned char* byaSha256Sum)
{
    if (NULL == firmHeadFileHeads || NULL == byaSha256Sum)
    {
        return UPGRADE_DATA_PARA_CHECK;
    }
    return getSha256(firmHeadFileHeads,firmHeadFileHeadsLen,byaSha256Sum);
}


/*******************************************************************************
* 函数名  : getPlainFirmHeadFileHeads
* 描  述  : 获取明文的固件头和文件头
* 输  入  : - firmHeadFileHeads   :加密的固件头和文件头内存空间
*       : - firmHeadFileHeadsLen:加密的固件头和文件头内存空间长度
*       : - byaSha256Sum        :摘要值
* 输  出  : 无
* 返回值  : 0     : 成功
*         其他 : 失败
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


int getSessionKey(unsigned char* random,unsigned char* byaKey)
{
    if(NULL == random || NULL == byaKey)
    {
        return UPGRADE_DATA_PARA_CHECK;
    }
    memcpy(byaKey,s_tmpSessionKey,AES_256_KEY_LEN_BY_BYTE);
    return 0;
}

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
UPGRADE_FILE_HEADER_P getFileHeads(char* firmHeadFileHeads,int firmHeadFileHeadsLen, UPGRADE_NEW_FIRMWARE_HEADER_T* pDecryFirmHead)
{
    if (NULL == firmHeadFileHeads || NULL == pDecryFirmHead)
    {
        return NULL;
    }
    return (UPGRADE_FILE_HEADER_P)(firmHeadFileHeads + ntohl(pDecryFirmHead->dwFileHeaderOffset));
}

/*******************************************************************************
* 函数名  : unpack_file_data_each
* 描  述  : 处理每个升级文件
* 输  入  : - pstFileHeader                        :文件头
*        : - byaKey                               :会话密钥
* 输  出  : 无
* 返回值  : 0     : 成功
*         其他 : 失败
*******************************************************************************/
int unpack_file_data_each(int iSrcfd,UPGRADE_FILE_HEADER_P pstFileHeader, unsigned char byaKey[AES_256_KEY_LEN_BY_BYTE])
{
    int ret = 0;
    int sdwReadLen = 0;
    int sdwFileLeftLen = 0;
    int fileStartOffset = 0;
    int eUpgradeSecType = 0;
    int sdwDecryptLen = 0;
    int sdwPaddingLen = 0;
    unsigned char byaSha256Sum[SHA256SUM_BY_BYTES_LEN] = {0};
    unsigned char byaIv[AES_BLOCK_LEN_BY_BYTE]         = {0};
    memset(byaIv, 0x00, AES_BLOCK_LEN_BY_BYTE);
    unsigned int enPackageType = E_UPGRADE_PACKAGE_TYPE_INVALID;
    char *pbyReadBuf  = NULL;
    char *pbyDecBuf   = NULL;
    char *pbyWriteBuf = NULL;
    EVP_CIPHER_CTX * pstCtx = NULL;
    SHA256_CTX stSha256Ctx;
    memset(&stSha256Ctx,0x00,sizeof(stSha256Ctx));
    char filePath[FILE_PATH_LEN] = {0};
    snprintf(filePath,FILE_PATH_LEN,"/sdcard/%s",pstFileHeader->byaFileName);

    if (NULL == pstFileHeader)
    {
        APP_ERR("param err\n");
        return UPGRADE_DATA_PARA_CHECK;
    }

    pstCtx = aesInit(byaKey,byaIv);
    if (NULL == pstCtx)
    {
        APP_ERR("aesInit err\n");
        return UPGRADE_DATA_DEC_CHECK;
    }

    SHA256_Init(&stSha256Ctx);

    pbyReadBuf = (char*)malloc(PROC_ENC_PER_BLOCK_LEN);
    if (NULL == pbyReadBuf)
    {
        APP_ERR("malloc fail\n");
        ret = UPGRADE_NO_MEM;
        goto EXIT_PORT;
    }

    pbyDecBuf = (char*)malloc(PROC_ENC_PER_BLOCK_LEN + AES_BLOCK_LEN_BY_BYTE);
    if (NULL == pbyDecBuf)
    {
        APP_ERR("malloc fail\n");
        ret = UPGRADE_NO_MEM;
        goto EXIT_PORT;
    }

    enPackageType = ntohl(pstFileHeader->enPackageType);
    APP_PRT("enPackageType =%d\n", enPackageType);
    if (E_UPGRADE_PACKAGE_TYPE_INVALID <= enPackageType)
    {
        APP_ERR("not supported upgrade pack type %d\n", enPackageType);
        ret = UPGRADE_DATA_ERROR;
        goto EXIT_PORT;
    }
    fileStartOffset = ntohl(pstFileHeader->dwStartOffset);
    sdwFileLeftLen = ntohl(pstFileHeader->dwFileEncryptLen);

    /** @brief: 循环文件每个块大小数据*/
    while(sdwFileLeftLen > 0)
    {
        memset(pbyReadBuf, 0, PROC_ENC_PER_BLOCK_LEN);
        memset(pbyDecBuf, 0, PROC_ENC_PER_BLOCK_LEN + AES_BLOCK_LEN_BY_BYTE);
        sdwReadLen = sdwFileLeftLen > PROC_ENC_PER_BLOCK_LEN ? PROC_ENC_PER_BLOCK_LEN : sdwFileLeftLen;
        sdwFileLeftLen -= sdwReadLen;
        ret = getFileData(iSrcfd,pbyReadBuf,sdwReadLen);
        if (ret != 0)
        {
            APP_ERR("get file data failed ret = %d\n",ret);
            ret = UPGRADE_DATA_ERROR;
            goto EXIT_PORT;
        }
        //默认为E_UPGRADE_SEC_AES_256_CBC_PKCS7 加密方式
        EVP_DecryptUpdate(pstCtx, (unsigned char*)pbyDecBuf, &sdwDecryptLen, (unsigned char*)pbyReadBuf, sdwReadLen); //对满足16字节组数据进行加密
        if (0 == sdwFileLeftLen)
        {
            EVP_DecryptFinal(pstCtx, (unsigned char*)pbyDecBuf + sdwDecryptLen, &sdwPaddingLen); //对满足16字节组数据进行加密
            sdwDecryptLen += sdwPaddingLen;
        }

        SHA256_Update(&stSha256Ctx, pbyDecBuf, sdwDecryptLen);
        if (0 == sdwFileLeftLen)
        {
            SHA256_Final(byaSha256Sum ,&stSha256Ctx);

            if (0 != memcmp(pstFileHeader->byaSha256Sum, byaSha256Sum, SHA256SUM_BY_BYTES_LEN))
            {
                APP_ERR("sha256 check fail \n");
                ret = UPGRADE_DATA_ERROR;
                goto EXIT_PORT;
            }
        }
        //保存数据到本地
        ret = FileOp::SaveDataApp(filePath, (unsigned char*)pbyDecBuf,sdwDecryptLen);
        if(ret != 0)
        {
            APP_ERR("SaveDataApp fail \n");
            ret = UPGRADE_DATA_ERROR;
            goto EXIT_PORT;
        }
    }

EXIT_PORT:
    if(pbyReadBuf != NULL)
    {
        free(pbyReadBuf);
        pbyReadBuf = NULL;
    }
    if(pbyDecBuf != NULL)
    {
        free(pbyDecBuf);
        pbyDecBuf = NULL;
    }
    if(pstCtx != NULL)
    {
        aesDeinit(pstCtx);
        pstCtx = NULL;
    }

    return ret;
}



/*******************************************************************************
* 函数名  : unpack_dev_type_info
* 描  述  : 解析设备型号列表数据
* 输  入  : - pstFileHeader                        :文件头
*        : - byaKey                               :会话密钥
* 输  出  : 无
* 返回值  : 0     : 成功
*         其他 : 失败
*******************************************************************************/
int unpack_dev_type_info(int iSrcfd,UPGRADE_FILE_HEADER_P pstFileHeader, unsigned char byaKey[AES_256_KEY_LEN_BY_BYTE])
{
    int ret = 0;
    int sdwReadLen = 0;
    int sdwFileLeftLen = 0;
    int fileStartOffset = 0;
    int eUpgradeSecType = 0;
    int sdwDecryptLen = 0;
    int sdwPaddingLen = 0;
    unsigned char byaSha256Sum[SHA256SUM_BY_BYTES_LEN] = {0};
    unsigned char byaIv[AES_BLOCK_LEN_BY_BYTE]         = {0};
    memset(byaIv, 0x00, AES_BLOCK_LEN_BY_BYTE);
    unsigned int enPackageType = E_UPGRADE_PACKAGE_TYPE_INVALID;
    char *pbyReadBuf  = NULL;
    char *pbyDecBuf   = NULL;
    char *pbyWriteBuf = NULL;
    EVP_CIPHER_CTX * pstCtx = NULL;
    SHA256_CTX stSha256Ctx;
    memset(&stSha256Ctx,0x00,sizeof(stSha256Ctx));
    int devListNum = 0;

    if (NULL == pstFileHeader)
    {
        APP_ERR("param err\n");
        return UPGRADE_DATA_PARA_CHECK;
    }

    pstCtx = aesInit(byaKey,byaIv);
    if (NULL == pstCtx)
    {
        APP_ERR("aesInit err\n");
        return UPGRADE_DATA_DEC_CHECK;
    }

    SHA256_Init(&stSha256Ctx);

    pbyReadBuf = (char*)malloc(PROC_ENC_PER_BLOCK_LEN);
    if (NULL == pbyReadBuf)
    {
        APP_ERR("malloc fail\n");
        ret = UPGRADE_NO_MEM;
        goto EXIT_PORT;
    }

    pbyDecBuf = (char*)malloc(PROC_ENC_PER_BLOCK_LEN + AES_BLOCK_LEN_BY_BYTE);
    if (NULL == pbyDecBuf)
    {
        APP_ERR("malloc fail\n");
        ret = UPGRADE_NO_MEM;
        goto EXIT_PORT;
    }

    enPackageType = ntohl(pstFileHeader->enPackageType);
    APP_PRT("enPackageType =%d\n", enPackageType);
    if (E_UPGRDE_DEV_TYPE_LIST != enPackageType)
    {
        APP_ERR("not supported upgrade pack type %d\n", enPackageType);
        ret = UPGRADE_DATA_ERROR;
        goto EXIT_PORT;
    }

    fileStartOffset = ntohl(pstFileHeader->dwStartOffset);
    sdwFileLeftLen = ntohl(pstFileHeader->dwFileEncryptLen);

    memset(pbyReadBuf, 0, PROC_ENC_PER_BLOCK_LEN);
    memset(pbyDecBuf, 0, PROC_ENC_PER_BLOCK_LEN + AES_BLOCK_LEN_BY_BYTE);

    ret = getFileData(iSrcfd,pbyReadBuf,sdwFileLeftLen);
    if (ret != 0)
    {
        APP_ERR("get file data failed ret = %d\n",ret);
        ret = UPGRADE_DATA_ERROR;
        goto EXIT_PORT;
    }
    //默认为E_UPGRADE_SEC_AES_256_CBC_PKCS7 加密方式
    EVP_DecryptUpdate(pstCtx, (unsigned char*)pbyDecBuf, &sdwDecryptLen, (unsigned char*)pbyReadBuf, sdwFileLeftLen); //对满足16字节组数据进行加密
    EVP_DecryptFinal(pstCtx, (unsigned char*)pbyDecBuf + sdwDecryptLen, &sdwPaddingLen); //对满足16字节组数据进行加密
    sdwDecryptLen += sdwPaddingLen;

    SHA256_Update(&stSha256Ctx, pbyDecBuf, sdwDecryptLen);
    SHA256_Final(byaSha256Sum ,&stSha256Ctx);

    if (0 != memcmp(pstFileHeader->byaSha256Sum, byaSha256Sum, SHA256SUM_BY_BYTES_LEN))
    {
        APP_ERR("sha256 check fail \n");
        ret = UPGRADE_DATA_ERROR;
        goto EXIT_PORT;
    }

    devListNum = sdwDecryptLen / sizeof (UPGRADE_DEV_TYPE);
    APP_PRT("supportNum = %d\n",devListNum);
    APP_PRT("DevList:\n");
    for(int i = 0; i < devListNum; i++)
    {
        int tmp = 0;
        memcpy(&tmp,pbyDecBuf+i*4,4);
        APP_PRT("    %x\n",tmp);
    }

EXIT_PORT:
    if(pbyReadBuf != NULL)
    {
        free(pbyReadBuf);
        pbyReadBuf = NULL;
    }
    if(pbyDecBuf != NULL)
    {
        free(pbyDecBuf);
        pbyDecBuf = NULL;
    }
    if(pstCtx != NULL)
    {
        aesDeinit(pstCtx);
        pstCtx = NULL;
    }

    return ret;
}