/**
 * @note    : HangZhou Hikvision Digital Technology Co., Ltd. All Right Reserved.
 * @file    : file_encrypt.h
 * @brief   : �ļ�����ʵ��
 * @author  : caohaojie
 * @date    : 2019��11��11��
 * @note    : Create
 */
#ifndef __FILE_ENCRYPT_H__
#define __FILE_ENCRYPT_H__

/************************************************************************
 Included Header
 ************************************************************************/
#include "HPR_Types.h"
#include "HPR_Config.h"
#include "encrypt_algo_interface.h"
#include "sqlcipher_config.h"

#ifdef __cplusplus
extern "C" {
#endif

/************************************************************************
 Macros
 ************************************************************************/
/**  @brief: ������ �� ����ԭ���ַ���*/

typedef HPR_INT32 ERR_STATUS;
#define ERR_ERROR                          (-1)    //δ֪����
#define ERR_PROCESSING                     (-127)  //���ڽ���
#define ERR_OK                             (0)     //�ɹ�
#define ERR_UNKNOW                         (1)     //δ֪����
#define ERR_SPACE_NOT_ENOUGH               (2)     //�ռ䲻��
#define ERR_FILE_NOT_EXIT                  (3)     //�ļ�������
#define ERR_SAME_NAME_FILE_EXIT            (4)     //���ڲ��ɱ��滻��ͬ���ļ�
#define ERR_FILE_TYPE_NOT_MATCH            (5)     //�ļ����Ͳ�ƥ��
#define ERR_KEY_NOT_MATCH                  (6)     //��Կ��ƥ��
#define ERR_USB_MOUNT_FAIL                 (7)     //usb ����ʧ��
#define ERR_NO_ACCESS_TO_OPEARA            (8)     //ûȨ��ȥ����
#define ERR_FLASH_NOT_ENOUGH               (9)     //�ڴ治��
#define ERR_FILE_ERR                       (10)    //�ļ�����

#define ERR_SZ_SUCCESS                        ("�ɹ�")
#define ERR_SZ_UNKNOW                         ("δ֪����")
#define ERR_SZ_SPACE_NOT_ENOUGH               ("�ռ䲻��")
#define ERR_SZ_FILE_NOT_EXIT                  ("�ļ�������")
#define ERR_SZ_SAME_NAME_FILE_EXIT            ("���ڲ��ɱ��滻��ͬ���ļ�")
#define ERR_SZ_FILE_TYPE_NOT_MATCH            ("�ļ����Ͳ�ƥ��")
#define ERR_SZ_KEY_NOT_MATCH                  ("��Կ��ƥ��")
#define ERR_SZ_USB_MOUNT_FAIL                 ("usb ����ʧ��")
#define ERR_SZ_NO_ACCESS_TO_OPEARA            ("ûȨ��ȥ����")
#define ERR_SZ_FLASH_NOT_ENOUGH               ("�ڴ治��")
#define ERR_SZ_FILE_ERR                       ("�ļ�����")


#define FILE_SEC_TAIL_MAGIC                   ("SECF") //�����ļ����� 
#define FILE_SEC_TAIL_VERSION_1               (1)      //�����ļ��汾_1,ȫ������
#define FILE_SEC_TAIL_VERSION_2               (2)      //�����ļ��汾_2,֧�ֲ��ּ���
#define FILE_SEC_TAIL_DEFAULT_PACK_LEN        (512)    //�ļ�����Ĭ�Ϸְ�����
#define FILE_SEC_TAIL_DWALGNO_AES_128_CBC     (1)      //�����ļ��㷨���� aes-128-cbc 
#define FILE_SEC_TAIL_ALGNO_AES_128_GCM       (2)      //�ļ������㷨����
#define FILE_SEC_TAIL_DWPASSALGNO_PBKDF2_WITH_HAMC_SHA256     (1)      //��������㷨-PBKDF2_HMAC-SHA256 
#define FILE_SEC_TAIL_DWPASSITER_DEFULT       (5000)   //��Կ�����ĵ������� 
#define FILE_SEC_TAIL_PART_LEN_4K             (4096)   //���ܰ汾_2 ���ּ�����Ĭ�ϵļ��ܳ�������ֵ



/************************************************************************
 Type Definition
 ************************************************************************/
/*
   �ı���ʽ����β��Ϣ, �󲿷�,�ò����ֶη���β����Ϣ����ĩβ,�����Ͳ���
*/
typedef struct
{   
    HPR_UINT8 byaMagic[4];                      // ��ʶ��,�̶�Ϊ SECF
    HPR_INT32 dwVersion;                       // ������Ϣ�汾 1-ȫ�����ܣ�2-���ּ���
    HPR_INT32 dwTailLen;                       // ����β����Ϣ����,��������β��������Ϣ���� sizeof(FILE_SEC_TAIL)
    HPR_INT32 dwPlaintextLen;                  // ���ĳ���,��Ϊ����aes���ܻ���г��Ȳ��룬ʵ�ʳ����ø��ֶα�ʾ��
} FILE_SEC_TAIL_PART_LAST; //���� 16�ֽ�

/*
   �ı���ʽ����β��Ϣ, ǰ����,�ò����ֶζ����������Ű汾������չ
*/
typedef struct
{
    HPR_INT32 dwAlgNo;                        //�����㷨��ţ� ��ǰ 1-aes-128-cbc
    HPR_INT32 dwSecPakcLen;                   //�ļ��ӽ��ְܷ�����,Ϊ�˽�����ļ�һ��ӽ����ڴ���Ĵ�����⣬���зְ��ӽ��ܣ�Ĭ�ϳ���Ϊ512�ֽ�
    HPR_UINT8 byaTag[16];                      //��ʶ��, �����ж��ļ��Ƿ���ܳɹ� ���ֶ�����ܵ��ļ�һ��ӽ��ܣ�����ȷ����Կ��iv�������ܺ�Ӧ��Ϊ SECF
    HPR_INT32 dwPassAlgNo;                    //��������㷨��ţ����ڵ���������ﳤ���������,  ��ǰ 1-PBKDF2-HMAC-SHA256
    HPR_INT32 dwPassIter;                    //������������ĵ�������
    HPR_UINT8 byaPassSlat[64];                //��������㷨��ֵ
    HPR_UINT8 iv[16];                          //��ż����ļ��ĳ�ʼ������
    HPR_INT32 dwPartSecLimitLen;                     //���ܲ��ֳ��ȣ��� stLastPart.dwVersion = 2, ��ʱ��ʹ��, ��ʾ�ļ�ǰ�벿�ֲ��ּ��ܣ��ø��ֶα�ʾ���ܲ������ĵĳ���(һ��ΪdwSecPakcLen�ֽڵı���),�ļ����������ֲ����ܡ� ��Ҫ����ͼƬ�ļ�����ʱֻ��Ҫ����ǰ�����и�ʽ��Ϣ���ֶ�(һ�㶨Ϊ4k)�����Ч�ʡ�  
    HPR_UINT8 res[12];                         //Ԥ���ֶ�
} FILE_SEC_TAIL_PART_FRONT; //���� 128�ֽ�,�������ܻ�����

/*
   �ı���ʽ����β��Ϣ, ��2����,�ò����ֶζ����������Ű汾������չ
*/
typedef struct
{
    FILE_SEC_TAIL_PART_FRONT    stFrontPart;
    FILE_SEC_TAIL_PART_LAST     stLastPart;
} FILE_SEC_TAIL; //���� 144�ֽ�


/*
    �����ļ�ת������
*/
typedef struct
{
    HPR_UINT8 *pbyInKey;         // [in] : �����ļ�ԭ�е���Կ,  �����ΪNULL,��Կ����Ӧ��Ϊ128bit(16bytes),�����ַ���ʽ�� ���ΪNULL,����Ϊ�������ļ�
    HPR_UINT8 *pbyInIv;          // [in] : �����ļ�ԭ�м��ܵĳ�ʼ������ ���Ϊ��ΪNULL,��ʼ�����ĳ���Ӧ��Ϊ128bits(16bytes)�������ַ���ʽ, ���ΪNULL,����ʹ��Ĭ�ϳ�ʼ���� (128bit�ľ�Ϊ0)
    HPR_UINT8 *pbyOutKey;        // [in] : �����ļ����ܵ�����Կ,  �����ΪNULL,��Կ����Ӧ��Ϊ128bit(16bytes),�����ַ���ʽ, ���ΪNULL,����Ϊ�������ļ�
    HPR_UINT8 *pbyOutIv;         // [in] :  �����ļ����ܵ��³�ʼ������ ���Ϊ��ΪNULL,��ʼ�����ĳ���Ӧ��Ϊ128bits(16bytes)�������ַ���ʽ, ���ΪNULL,����ʹ��Ĭ�ϳ�ʼ����(128bit�ľ�Ϊ0)
    HPR_UINT8 *pbyInPath;    // [in] :  Դ���������ļ���
    HPR_UINT8 *pbyOutPath;   // [in] :  Ŀ�ļ��������ļ���
    HPR_INT8  sdwVersion;    // [in] :  �ļ����ܰ汾n 1-ȫ�����ݼ��� 2-�������ݼ��ܣ���ǰ���ܳ�������Ĭ��Ϊ FILE_SEC_TAIL_PART_LEN_4K(4096bytes)
    HPR_INT32 dwPartSecLimitLen;   // [in]  : dwVersion=2 ʱ,��Ҫ����ò�������ʾ�ļ�ǰ�벿�ּ��ܣ��ø��ֶα�ʾ��Ҫ���ܳ�������(������ֵ���ļ����Ȳ�����Ҫ����,һ��ΪdwSecPakcLen�ֽڵı���)�� ��Ҫ����ͼƬ�ļ�����ʱֻ��Ҫ����ǰ�����и�ʽ��Ϣ���ֶ�(һ�㶨Ϊ4k)�����Ч�ʡ�
    HPR_FLOAT *pfRate;        //  [out] : ���뵼������
    HPR_FLOAT fRateBegin;     //  [in] : ���뵼����ʼ����
    HPR_FLOAT fRateEnd;       //  [in] : ���뵼��������
} SEC_DEC_FILE_PARAM_ST, *SEC_DEC_FILE_PARAM_P;

/*
    ������Ϣ�ӽ��ܸ��²���
*/
typedef struct
{
    HPR_INT8                    *szDbName;      //  [in] : ���ݿ���
    HPR_FLOAT                   *pfRate;        //  [out] : ���뵼������
    HPR_FLOAT                   fRateBegin;     //  [in] : ���뵼����ʼ����
    HPR_FLOAT                   fRateEnd;       //  [in] : ���뵼��������
} ENCRYPT_UPDATE_PARAM_T, *ENCRYPT_UPDATE_PARAM_P;


/** ���ݿ�ת�� ����������Ϣ�ӽ��ܸ��µĻص�����,�������ڵ��뵼��ʱ�����ݿ��ڵ�������Ϣ�ֶδ�����Ƚ��и��¡�*/
typedef HPR_INT32(CALLBACK* ENCRYPT_UPDATE_CALLBACK)(ENCRYPT_UPDATE_PARAM_P pstParam);

/************************************************************************
 Function Declaration
 ************************************************************************/

/**
 * @fn       : generate_key_usr_code 
 * @brief    : �����û���������aes��Կ
 * @param    : szPass     [in]  : �û������ַ���
 * @param    : sdwPassLen [in]  : �����
 * @param    : sdwKeyLen  [in]  : ��Ҫ���������볤��
 * @param    : pbyKeyDst  [out] : ��Ų����������ַ
 * @return   : HPR_OK: success; other : fail 
 * @author   : caohaojie
 */
HPR_INT32 generate_key_usr_code(const HPR_UINT8 *szPass, HPR_INT32 sdwPassLen, HPR_INT32 sdwKeyLen, HPR_UINT8 *pbyKeyDst);

/**
 * @fn       : sec_dec_file_with_check 
 * @brief    : aes_128_cbc zeropaddingģʽ �ļ�ת�� (��ԭ�еļ����ļ����ݽ��ܺ�����������ܴ���)
 * @param    : pstParam [in] :ת������
 * @note     : pbyInPath �� pbyOutPath ����һ��
 * @return   : ERR_OK: success; other : fail 
 * @author   : caohaojie
 */
ERR_STATUS sec_dec_file_with_check(SEC_DEC_FILE_PARAM_P pstParam);

/**
 * @fn       : sec_dec_path_with_check 
 * @brief    : ��·����Ŀ¼�µ������ļ������ļ�Ϊ��λ����aes_128_cbc_zeropadding �ļ�ת�� (��ԭ�еļ����ļ����ݽ��ܺ�����������ܴ���)
 * @param    : pstParam [in] :ת������
 * @param    : pbyErrFileName     [out] :  ���ڼ�¼ʧ�ܷ���ʱ�Ĵ����ļ���
 * @param    : dwErrFileNameSize     [in] :  pbyErrFileName��ַ���õĿռ��С
 * @param    : pudwAllFileNum         [in] :  ��ʾ�ܹ���Ҫ������ļ�����
 * @param    : pdwSuccessFileNum     [in] :  ��ʾ�Ѿ��ɹ�������ļ�����
 * @note     : pbyInPath �� pbyOutPath ����һ��
 * @return   : HPR_OK: success; other : fail 
 * @author   : caohaojie
 */
ERR_STATUS sec_dec_path_with_check(SEC_DEC_FILE_PARAM_P pstParam, HPR_UINT8 *ppbyErrFileName, HPR_INT32 dwErrFileNameSize, HPR_UINT32 *pudwAllFileNum, HPR_UINT32* pdwSuccessFileNum);

/**
 * @fn       : sec_dec_db_with_check 
 * @brief    : sqlciher �������ݿ� ת�� (��ԭ�еļ����������ݿ���ܺ�����������ܴ���)
 * @param    : pstParam  : ���ṹ��SEC_DEC_DB_PARAM_P ����
 * @note     : pstParam->pbyInPath �� pstParam->pbyOutPath ������һ��
 * @return   : ERR_OK: success; other : fail 
 * @author   : caohaojie
 */
ERR_STATUS sec_dec_db_with_check(SEC_DEC_DB_PARAM_P pstParam);

/**
 * @fn       : sec_dec_db2file_with_check 
 * @brief    ���ȵ���sec_dec_db ���������ݿ�ת��Ϊ�Ǽ������ݿ�, �ٵ���sec_dec_file���Ǽ������ݿⰴ����ͨ�ļ�����aes_128_cbc����
 * @param    : pstParam  : ���ṹ��SEC_DEC_DB_PARAM_P ����
 * @param    : fnCallBackUpdate     [in] :  �������ݺ���(��Ա���ݿ���¼����ݿ⵱ǰ��Ҫ���ڲ���������Ϣ�ֶν��мӽ���
 * @note     : pstParam->pbyInPath �� pstParam->pbyOutPath ������һ��
 * @return   : ERR_OK: success; other : fail 
 * @author   : caohaojie
 */
ERR_STATUS sec_dec_db2file_with_check(SEC_DEC_DB_PARAM_P pstParam, ENCRYPT_UPDATE_CALLBACK fnCallBackUpdate);

/**
 * @fn       : sec_dec_file2db_with_check 
 * @brief    ���ȵ���sec_dec_file������ͨ�ļ�����aes_128_cbc�������ݿ�,ת���ɷǼ������ݿ⣬�ٵ���sec_dec_db,���Ǽ������ݿ�ת��Ϊ�������ݿ�
 * @param    : pstParam  : ���ṹ��SEC_DEC_DB_PARAM_ST ����
 * @param    : fnCallBackUpdate     [in] :  �������ݺ���(��Ա���ݿ���¼����ݿ⵱ǰ��Ҫ���ڲ���������Ϣ�ֶν��мӽ���
 * @note     : pstParam->pbyInPath �� pstParam->pbyOutPath ������һ��
 * @return   : ERR_OK: success; other : fail 
 * @author   : caohaojie
 */
ERR_STATUS sec_dec_file2db_with_check(SEC_DEC_DB_PARAM_P pstParam, ENCRYPT_UPDATE_CALLBACK fnCallBackUpdate);

/**
 * @fn       : check_file_pwd 
 * @brief    : ���ݼ����ļ�����β��ϢУ������ļ� �����Ƿ���ȷ
 * @param    : pbyFileName [in] : �ļ���
 * @param    : pbyKey [in]      : ����,���ΪNULL�������ַ�����Ϊ�� ����������
 * @return   : ERR_OK: success; other : fail 
 * @author   : caohaojie
 */
ERR_STATUS check_file_pwd(HPR_UINT8 *pbyFileName, HPR_UINT8 *pbyKey);
/**
 * @fn       : parse_sec_file_tail 
 * @brief    : ���������ļ�β��Ϣ
 * @param    : pstFileSecTail [out]: �����ļ�β��ϢĿ�ĵ�ַ
 * @param    : pBuf [in]           ���ļ�buuf
 * @param    : dwFileLen [in]      ���ļ��ܳ���
 * @param    : key:[in]  : ��Կ(16byte)
 * @param    : iv :[in]  : iv ����(16byte)
 * @return   : ERR_OK: success; other: fail
 * @author   : caohaojie
 */
ERR_STATUS parse_sec_file_tail(FILE_SEC_TAIL *pstFileSecTail, HPR_UINT8 *pBuf, HPR_INT32 dwFileLen, HPR_UINT8* key, HPR_UINT8* iv);

/**
 * @fn       : parse_sec_file_tail_by_fd 
 * @brief    : ���������ļ�β��Ϣ
 * @param    : pstFileSecTail [out]: �����ļ�β��ϢĿ�ĵ�ַ
 * @param    : dwFd [in]           ���ļ�������
 * @param    : key:[in]  : ��Կ(16byte)
 * @param    : iv :[in]  : iv ����(16byte)
 * @return   : ERR_OK: success; other: fail
 * @author   : caohaojie
 */
ERR_STATUS parse_sec_file_tail_by_fd(FILE_SEC_TAIL *pstFileSecTail, HPR_INT32 dwFd, HPR_UINT8* key, HPR_UINT8* iv);

/**
 * @fn       : gen_sec_file_tail 
 * @brief    : ���ɼ����ļ�β��Ϣ
 * @param    : pstFileSecTail      [out]: �����ļ�β��ϢĿ�ĵ�ַ
 * @param    : dwPlaintextLen      [in]: �����ļ�ԭ���ĳ���
 * @param    : dwPerPackLen        [in]: ���ְܷ����� 
 * @param    : dwVersion           [in]: ���ܰ汾 1-ȫ�����ܣ� 2-���ּ���
 * @param    : dwPartSecLimitLen   [in]: �� dwVersion=2 ʱ��Ч����ʾ���ּ��ܳ��ȵ�����ֵ,�����ó��Ȳ������ݲ�����
 * @param    : key:[in]  : ��Կ(16byte)
 * @param    : iv :[in]  : iv ����(16byte)
 * @return   : ERR_OK: success; other: fail
 * @author   : caohaojie
 */
ERR_STATUS gen_sec_file_tail(FILE_SEC_TAIL *pstFileSecTail, HPR_INT32 dwPlaintextLen, HPR_INT32 dwPerPackLen, HPR_INT32 dwVersion, HPR_INT32 dwSecPartLen, HPR_UINT8* key, HPR_UINT8* iv);

/**
 * @fn       : sec_file_in_buf 
 * @brief    : ���ļ��ֶν��ܹ�����м���buf
 * @param    : dwPartLen  [in]      : �ֶγ���
 * @param    : stSecParam [in/out]  : �ӽ��ܲ���
 * @param    : dwNeedSecLen [in]      : ��Ҫ���ܵĳ�������,����֧�ֲ��ּ��� version=2 ��ʵ��,��ֵ����ΪdwPartLen �������ߵ���pstSecParam->sdwSrcLenֵ
 * @note     ���ú���ִ�к󣬻��޸�iv����,�������ⲿ�������øýӿ�
 * @note     �����ֲ�����,�������һ������ ���� pstSecParam->sdwSrcLen����ΪdwPartLen ����
 * @return   : HPR_OK: success; other: fail
 * @author   : caohaojie
 */
ERR_STATUS sec_file_in_buf(HPR_INT32 dwPartLen, SEC_PARAM_P pstSecParam, HPR_INT32 dwNeedSecLen);

/**
 * @fn       : dec_file_in_buf 
 * @brief    : ���ļ��ֶν��ܹ�����н���buf
 * @param    : dwPartLen [in]: �ֶγ���
 * @param    : stSecParam [in/out]  : �ӽ��ܲ���
 * @param    : dwNeedDecLen [in]      : ��Ҫ���ܵĳ�������,����֧�ֲ��ּ��� version=2 ��ʵ��,��ֵ����ΪdwPartLen �������ߵ���pstSecParam->sdwSrcLenֵ
 * @note     ���ú���ִ�к󣬻��޸�iv����,�������ⲿ�������øýӿ�
 * @note     �����ֲ�����,�������һ������ ���� pstSecParam->sdwSrcLen����ΪdwPartLen ����
 * @return   : HPR_OK: success; other: fail
 * @author   : caohaojie
 */
ERR_STATUS dec_file_in_buf(HPR_INT32 dwPartLen, SEC_PARAM_P pstSecParam, HPR_INT32 dwNeedDecLen); 

/**
 * @fn       : get_file_enc_limit_len 
 * @brief    : ͨ���ļ�ͷ��Ϣ��ȡ�����ļ��ļ����ֶγ��� 
 * @param    : stFileSecTail     ��[in] : �ļ�β��Ԫ��Ϣ
 * @param    : sdwFileCipherLen  : [in] : �ļ����ĳ��ȣ�ָ�ļ��ĳ��ȼ�ȥ����Ԫ��Ϣ�ĳ���
 * @return   : success��version-1: ���� sdwFileCipherLen; version-2: ����stFrontPart.dwPartSecLimitLen;(ע���ֵ���ܱ��ļ������ĳ��ȴ�������������) fail: (-1)
 * @author   : caohaojie
 */
HPR_INT32 get_file_enc_limit_len(FILE_SEC_TAIL *pstFileSecTail, HPR_INT32 sdwFileCipherLen);



#ifdef __cplusplus
}
#endif
#endif /* __FILE_ENCRYPT_H__ END */
