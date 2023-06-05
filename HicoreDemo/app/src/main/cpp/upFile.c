#include "upFile.h"
#include "prtUtil.h"
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
        APP_ERR("Invalid input param: src = 0x%x, dst = 0x%x\n", (unsigned int)src, (unsigned int)dst);
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


///////////////////////////////////////////////////////////////////////////////////////////////////////
///业务具体实现
static int checkFirmwareHeads(char* data, int dataLen,int* *pFileNum){
    int ret = 0;
    int iFileNum = 0;
    int iFileHeadLen = 0;
    int iHeadTotalLen = 0;
    FIRMWARE_HEADER decryFirmHead;
    memset(& decryFirmHead, 0x00, sizeof(FIRMWARE_HEADER))

    if(NULL == data){
        return UPGRADE_DATA_PARA_CHECK;
    }
    int firmwareHeadLen  = sizeof(FIRMWARE_HEADER);
    if(dataLen < firmwareHeadLen){
        return UPGRADE_DATA_LEN_CHECK;
    }

    if (OK != convertData((char *)&data, (char *)&decryFirmHead,
        sizeof(FIRMWARE_HEADER)))
    {
        APP_ERR("convert firmHeader error!!!\n");
        return UPGRADE_DATA_ERROR;
    }

    iFileNum = decryFirmHead.file_nums;
    *pFileNum = iFileNum;
    if((0 == iFileNum) || (iFileNum > MAX_FILE_NUMS))
    {
        APP_ERR("file numbers invalid!!!\n");
        return UPGRADE_DATA_ERROR;
    }

    iFileHeadLen = iFileNum*sizeof(UPGRADE_FILE_HEADER);
    iHeadTotalLen = sizeof(FIRMWARE_HEADER) + iFileHeadLen;
    *pHeadLen = iHeadTotalLen;
    UPGRA_INFO("iFileNum=%d, iHeadTotalLen=%d\n", iFileNum, iHeadTotalLen);
    if(!(pHeader = memalign(BUFF_ALIGNMENT, iHeadTotalLen)))
    {
        UPGRA_ERR("seem no memery!!!\n");
        return UPGRADE_NO_MEM;
    }
}


int sys_upg_match_firmware(char* data, int dataLen){
    int ret = 0;
    int firmwareHeadLen  = sizeof(FIRMWARE_HEADER);
}
