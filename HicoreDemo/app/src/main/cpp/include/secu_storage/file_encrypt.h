/**
 * @note    : HangZhou Hikvision Digital Technology Co., Ltd. All Right Reserved.
 * @file    : file_encrypt.h
 * @brief   : 文件加密实现
 * @author  : caohaojie
 * @date    : 2019年11月11日
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
/**  @brief: 错误码 和 错误原因字符串*/

typedef HPR_INT32 ERR_STATUS;
#define ERR_ERROR                          (-1)    //未知错误
#define ERR_PROCESSING                     (-127)  //正在进行
#define ERR_OK                             (0)     //成功
#define ERR_UNKNOW                         (1)     //未知错误
#define ERR_SPACE_NOT_ENOUGH               (2)     //空间不足
#define ERR_FILE_NOT_EXIT                  (3)     //文件不存在
#define ERR_SAME_NAME_FILE_EXIT            (4)     //存在不可被替换的同名文件
#define ERR_FILE_TYPE_NOT_MATCH            (5)     //文件类型不匹配
#define ERR_KEY_NOT_MATCH                  (6)     //密钥不匹配
#define ERR_USB_MOUNT_FAIL                 (7)     //usb 挂载失败
#define ERR_NO_ACCESS_TO_OPEARA            (8)     //没权限去操作
#define ERR_FLASH_NOT_ENOUGH               (9)     //内存不足
#define ERR_FILE_ERR                       (10)    //文件错误

#define ERR_SZ_SUCCESS                        ("成功")
#define ERR_SZ_UNKNOW                         ("未知错误")
#define ERR_SZ_SPACE_NOT_ENOUGH               ("空间不足")
#define ERR_SZ_FILE_NOT_EXIT                  ("文件不存在")
#define ERR_SZ_SAME_NAME_FILE_EXIT            ("存在不可被替换的同名文件")
#define ERR_SZ_FILE_TYPE_NOT_MATCH            ("文件类型不匹配")
#define ERR_SZ_KEY_NOT_MATCH                  ("密钥不匹配")
#define ERR_SZ_USB_MOUNT_FAIL                 ("usb 挂载失败")
#define ERR_SZ_NO_ACCESS_TO_OPEARA            ("没权限去操作")
#define ERR_SZ_FLASH_NOT_ENOUGH               ("内存不足")
#define ERR_SZ_FILE_ERR                       ("文件错误")


#define FILE_SEC_TAIL_MAGIC                   ("SECF") //加密文件幻数 
#define FILE_SEC_TAIL_VERSION_1               (1)      //加密文件版本_1,全部加密
#define FILE_SEC_TAIL_VERSION_2               (2)      //加密文件版本_2,支持部分加密
#define FILE_SEC_TAIL_DEFAULT_PACK_LEN        (512)    //文件加密默认分包长度
#define FILE_SEC_TAIL_DWALGNO_AES_128_CBC     (1)      //加密文件算法索引 aes-128-cbc 
#define FILE_SEC_TAIL_ALGNO_AES_128_GCM       (2)      //文件加密算法定义
#define FILE_SEC_TAIL_DWPASSALGNO_PBKDF2_WITH_HAMC_SHA256     (1)      //密码迭代算法-PBKDF2_HMAC-SHA256 
#define FILE_SEC_TAIL_DWPASSITER_DEFULT       (5000)   //秘钥产生的迭代次数 
#define FILE_SEC_TAIL_PART_LEN_4K             (4096)   //加密版本_2 部分加密下默认的加密长度限制值



/************************************************************************
 Type Definition
 ************************************************************************/
/*
   文本形式加密尾信息, 后部分,该部分字段放在尾部信息的最末尾,定义后就不变
*/
typedef struct
{   
    HPR_UINT8 byaMagic[4];                      // 标识码,固定为 SECF
    HPR_INT32 dwVersion;                       // 加密信息版本 1-全部加密，2-部分加密
    HPR_INT32 dwTailLen;                       // 加密尾部信息长度,包括整个尾部加密信息长度 sizeof(FILE_SEC_TAIL)
    HPR_INT32 dwPlaintextLen;                  // 明文长度,因为个别aes加密会进行长度补齐，实际长度用该字段表示。
} FILE_SEC_TAIL_PART_LAST; //长度 16字节

/*
   文本形式加密尾信息, 前部分,该部分字段定义后可能随着版本更迭扩展
*/
typedef struct
{
    HPR_INT32 dwAlgNo;                        //加密算法编号， 当前 1-aes-128-cbc
    HPR_INT32 dwSecPakcLen;                   //文件加解密分包长度,为了解决大文件一起加解密内存损耗大的问题，进行分包加解密，默认长度为512字节
    HPR_UINT8 byaTag[16];                      //标识符, 用于判断文件是否解密成功 该字段随加密的文件一起加解密，用正确的密钥和iv向量解密后应当为 SECF
    HPR_INT32 dwPassAlgNo;                    //密码迭代算法编号，用于迭代密码短语长身产生密码,  当前 1-PBKDF2-HMAC-SHA256
    HPR_INT32 dwPassIter;                    //密码迭代产生的迭代次数
    HPR_UINT8 byaPassSlat[64];                //密码迭代算法盐值
    HPR_UINT8 iv[16];                          //存放加密文件的初始化向量
    HPR_INT32 dwPartSecLimitLen;                     //加密部分长度，当 stLastPart.dwVersion = 2, 的时候使用, 表示文件前半部分部分加密，用该字段表示加密部分密文的长度(一定为dwSecPakcLen字节的倍数),文件的其他部分不加密。 主要用于图片文件加密时只需要加密前部带有格式信息的字段(一般定为4k)。提高效率。  
    HPR_UINT8 res[12];                         //预留字段
} FILE_SEC_TAIL_PART_FRONT; //长度 128字节,后续可能会扩增

/*
   文本形式加密尾信息, 第2部分,该部分字段定义后可能随着版本更迭扩展
*/
typedef struct
{
    FILE_SEC_TAIL_PART_FRONT    stFrontPart;
    FILE_SEC_TAIL_PART_LAST     stLastPart;
} FILE_SEC_TAIL; //长度 144字节


/*
    加密文件转换参数
*/
typedef struct
{
    HPR_UINT8 *pbyInKey;         // [in] : 加密文件原有的密钥,  如果不为NULL,密钥长度应当为128bit(16bytes),无需字符形式， 如果为NULL,代表为不加密文件
    HPR_UINT8 *pbyInIv;          // [in] : 加密文件原有加密的初始向量， 如果为不为NULL,初始向量的长度应当为128bits(16bytes)，无需字符形式, 如果为NULL,代表使用默认初始向量 (128bit的均为0)
    HPR_UINT8 *pbyOutKey;        // [in] : 加密文件加密的新密钥,  如果不为NULL,密钥长度应当为128bit(16bytes),无需字符形式, 如果为NULL,代表为不加密文件
    HPR_UINT8 *pbyOutIv;         // [in] :  加密文件加密的新初始向量， 如果为不为NULL,初始向量的长度应当为128bits(16bytes)，无需字符形式, 如果为NULL,代表使用默认初始向量(128bit的均为0)
    HPR_UINT8 *pbyInPath;    // [in] :  源加密数据文件名
    HPR_UINT8 *pbyOutPath;   // [in] :  目的加密数据文件名
    HPR_INT8  sdwVersion;    // [in] :  文件加密版本n 1-全部数据加密 2-部分数据加密，当前加密长度限制默认为 FILE_SEC_TAIL_PART_LEN_4K(4096bytes)
    HPR_INT32 dwPartSecLimitLen;   // [in]  : dwVersion=2 时,需要输入该参数，表示文件前半部分加密，用该字段表示需要加密长度限制(超过该值的文件长度不再需要加密,一定为dwSecPakcLen字节的倍数)。 主要用于图片文件加密时只需要加密前部带有格式信息的字段(一般定为4k)。提高效率。
    HPR_FLOAT *pfRate;        //  [out] : 导入导出进度
    HPR_FLOAT fRateBegin;     //  [in] : 导入导出起始进度
    HPR_FLOAT fRateEnd;       //  [in] : 导入导出最大进度
} SEC_DEC_FILE_PARAM_ST, *SEC_DEC_FILE_PARAM_P;

/*
    敏感信息加解密更新参数
*/
typedef struct
{
    HPR_INT8                    *szDbName;      //  [in] : 数据库名
    HPR_FLOAT                   *pfRate;        //  [out] : 导入导出进度
    HPR_FLOAT                   fRateBegin;     //  [in] : 导入导出起始进度
    HPR_FLOAT                   fRateEnd;       //  [in] : 导入导出最大进度
} ENCRYPT_UPDATE_PARAM_T, *ENCRYPT_UPDATE_PARAM_P;


/** 数据库转换 用于敏感信息加解密更新的回调函数,　用于在导入导出时对数据库内的敏感信息字段处理进度进行更新。*/
typedef HPR_INT32(CALLBACK* ENCRYPT_UPDATE_CALLBACK)(ENCRYPT_UPDATE_PARAM_P pstParam);

/************************************************************************
 Function Declaration
 ************************************************************************/

/**
 * @fn       : generate_key_usr_code 
 * @brief    : 根据用户口令生成aes密钥
 * @param    : szPass     [in]  : 用户口令字符串
 * @param    : sdwPassLen [in]  : 口令长度
 * @param    : sdwKeyLen  [in]  : 需要产生的密码长度
 * @param    : pbyKeyDst  [out] : 存放产生的密码地址
 * @return   : HPR_OK: success; other : fail 
 * @author   : caohaojie
 */
HPR_INT32 generate_key_usr_code(const HPR_UINT8 *szPass, HPR_INT32 sdwPassLen, HPR_INT32 sdwKeyLen, HPR_UINT8 *pbyKeyDst);

/**
 * @fn       : sec_dec_file_with_check 
 * @brief    : aes_128_cbc zeropadding模式 文件转换 (将原有的加密文件数据解密后用新密码加密储存)
 * @param    : pstParam [in] :转换参数
 * @note     : pbyInPath 和 pbyOutPath 可以一致
 * @return   : ERR_OK: success; other : fail 
 * @author   : caohaojie
 */
ERR_STATUS sec_dec_file_with_check(SEC_DEC_FILE_PARAM_P pstParam);

/**
 * @fn       : sec_dec_path_with_check 
 * @brief    : 按路径将目录下的所有文件都以文件为单位进行aes_128_cbc_zeropadding 文件转换 (将原有的加密文件数据解密后用新密码加密储存)
 * @param    : pstParam [in] :转换参数
 * @param    : pbyErrFileName     [out] :  用于记录失败发生时的处理文件名
 * @param    : dwErrFileNameSize     [in] :  pbyErrFileName地址可用的空间大小
 * @param    : pudwAllFileNum         [in] :  表示总共需要处理的文件个数
 * @param    : pdwSuccessFileNum     [in] :  表示已经成功处理的文件个数
 * @note     : pbyInPath 和 pbyOutPath 可以一致
 * @return   : HPR_OK: success; other : fail 
 * @author   : caohaojie
 */
ERR_STATUS sec_dec_path_with_check(SEC_DEC_FILE_PARAM_P pstParam, HPR_UINT8 *ppbyErrFileName, HPR_INT32 dwErrFileNameSize, HPR_UINT32 *pudwAllFileNum, HPR_UINT32* pdwSuccessFileNum);

/**
 * @fn       : sec_dec_db_with_check 
 * @brief    : sqlciher 加密数据库 转换 (将原有的加密数据数据库解密后用新密码加密储存)
 * @param    : pstParam  : 见结构体SEC_DEC_DB_PARAM_P 定义
 * @note     : pstParam->pbyInPath 和 pstParam->pbyOutPath 不可以一致
 * @return   : ERR_OK: success; other : fail 
 * @author   : caohaojie
 */
ERR_STATUS sec_dec_db_with_check(SEC_DEC_DB_PARAM_P pstParam);

/**
 * @fn       : sec_dec_db2file_with_check 
 * @brief    ：先调用sec_dec_db 将加密数据库转换为非加密数据库, 再调用sec_dec_file将非加密数据库按照普通文件进行aes_128_cbc加密
 * @param    : pstParam  : 见结构体SEC_DEC_DB_PARAM_P 定义
 * @param    : fnCallBackUpdate     [in] :  更新数据函数(人员数据库和事件数据库当前需要对内部的敏感信息字段进行加解密
 * @note     : pstParam->pbyInPath 和 pstParam->pbyOutPath 不可以一致
 * @return   : ERR_OK: success; other : fail 
 * @author   : caohaojie
 */
ERR_STATUS sec_dec_db2file_with_check(SEC_DEC_DB_PARAM_P pstParam, ENCRYPT_UPDATE_CALLBACK fnCallBackUpdate);

/**
 * @fn       : sec_dec_file2db_with_check 
 * @brief    ：先调用sec_dec_file按照普通文件进行aes_128_cbc解密数据库,转化成非加密数据库，再调用sec_dec_db,将非加密数据库转化为加密数据库
 * @param    : pstParam  : 见结构体SEC_DEC_DB_PARAM_ST 定义
 * @param    : fnCallBackUpdate     [in] :  更新数据函数(人员数据库和事件数据库当前需要对内部的敏感信息字段进行加解密
 * @note     : pstParam->pbyInPath 和 pstParam->pbyOutPath 不可以一致
 * @return   : ERR_OK: success; other : fail 
 * @author   : caohaojie
 */
ERR_STATUS sec_dec_file2db_with_check(SEC_DEC_DB_PARAM_P pstParam, ENCRYPT_UPDATE_CALLBACK fnCallBackUpdate);

/**
 * @fn       : check_file_pwd 
 * @brief    : 根据加密文件加密尾信息校验加密文件 密码是否正确
 * @param    : pbyFileName [in] : 文件名
 * @param    : pbyKey [in]      : 密码,如果为NULL或密码字符长度为空 则代表空密码
 * @return   : ERR_OK: success; other : fail 
 * @author   : caohaojie
 */
ERR_STATUS check_file_pwd(HPR_UINT8 *pbyFileName, HPR_UINT8 *pbyKey);
/**
 * @fn       : parse_sec_file_tail 
 * @brief    : 解析加密文件尾信息
 * @param    : pstFileSecTail [out]: 加密文件尾信息目的地址
 * @param    : pBuf [in]           ：文件buuf
 * @param    : dwFileLen [in]      ：文件总长度
 * @param    : key:[in]  : 密钥(16byte)
 * @param    : iv :[in]  : iv 向量(16byte)
 * @return   : ERR_OK: success; other: fail
 * @author   : caohaojie
 */
ERR_STATUS parse_sec_file_tail(FILE_SEC_TAIL *pstFileSecTail, HPR_UINT8 *pBuf, HPR_INT32 dwFileLen, HPR_UINT8* key, HPR_UINT8* iv);

/**
 * @fn       : parse_sec_file_tail_by_fd 
 * @brief    : 解析加密文件尾信息
 * @param    : pstFileSecTail [out]: 加密文件尾信息目的地址
 * @param    : dwFd [in]           ：文件描述符
 * @param    : key:[in]  : 密钥(16byte)
 * @param    : iv :[in]  : iv 向量(16byte)
 * @return   : ERR_OK: success; other: fail
 * @author   : caohaojie
 */
ERR_STATUS parse_sec_file_tail_by_fd(FILE_SEC_TAIL *pstFileSecTail, HPR_INT32 dwFd, HPR_UINT8* key, HPR_UINT8* iv);

/**
 * @fn       : gen_sec_file_tail 
 * @brief    : 生成加密文件尾信息
 * @param    : pstFileSecTail      [out]: 加密文件尾信息目的地址
 * @param    : dwPlaintextLen      [in]: 加密文件原明文长度
 * @param    : dwPerPackLen        [in]: 加密分包长度 
 * @param    : dwVersion           [in]: 加密版本 1-全部加密； 2-部分加密
 * @param    : dwPartSecLimitLen   [in]: 仅 dwVersion=2 时有效，表示部分加密长度的限制值,超过该长度部分数据不加密
 * @param    : key:[in]  : 密钥(16byte)
 * @param    : iv :[in]  : iv 向量(16byte)
 * @return   : ERR_OK: success; other: fail
 * @author   : caohaojie
 */
ERR_STATUS gen_sec_file_tail(FILE_SEC_TAIL *pstFileSecTail, HPR_INT32 dwPlaintextLen, HPR_INT32 dwPerPackLen, HPR_INT32 dwVersion, HPR_INT32 dwSecPartLen, HPR_UINT8* key, HPR_UINT8* iv);

/**
 * @fn       : sec_file_in_buf 
 * @brief    : 按文件分段解密规则进行加密buf
 * @param    : dwPartLen  [in]      : 分段长度
 * @param    : stSecParam [in/out]  : 加解密参数
 * @param    : dwNeedSecLen [in]      : 需要加密的长度限制,用于支持部分加密 version=2 的实现,该值必须为dwPartLen 倍数或者等于pstSecParam->sdwSrcLen值
 * @note     ：该函数执行后，会修改iv向量,以用与外部连续调用该接口
 * @note     ：若分步调用,除非最后一个包， 否则 pstSecParam->sdwSrcLen必须为dwPartLen 倍数
 * @return   : HPR_OK: success; other: fail
 * @author   : caohaojie
 */
ERR_STATUS sec_file_in_buf(HPR_INT32 dwPartLen, SEC_PARAM_P pstSecParam, HPR_INT32 dwNeedSecLen);

/**
 * @fn       : dec_file_in_buf 
 * @brief    : 按文件分段解密规则进行解密buf
 * @param    : dwPartLen [in]: 分段长度
 * @param    : stSecParam [in/out]  : 加解密参数
 * @param    : dwNeedDecLen [in]      : 需要解密的长度限制,用于支持部分加密 version=2 的实现,该值必须为dwPartLen 倍数或者等于pstSecParam->sdwSrcLen值
 * @note     ：该函数执行后，会修改iv向量,以用与外部连续调用该接口
 * @note     ：若分步调用,除非最后一个包， 否则 pstSecParam->sdwSrcLen必须为dwPartLen 倍数
 * @return   : HPR_OK: success; other: fail
 * @author   : caohaojie
 */
ERR_STATUS dec_file_in_buf(HPR_INT32 dwPartLen, SEC_PARAM_P pstSecParam, HPR_INT32 dwNeedDecLen); 

/**
 * @fn       : get_file_enc_limit_len 
 * @brief    : 通过文件头信息获取加密文件的加密字段长度 
 * @param    : stFileSecTail     ：[in] : 文件尾部元信息
 * @param    : sdwFileCipherLen  : [in] : 文件密文长度，指文件的长度减去加密元信息的长度
 * @return   : success：version-1: 返回 sdwFileCipherLen; version-2: 返回stFrontPart.dwPartSecLimitLen;(注意该值可能比文件的密文长度大，属于正常现象) fail: (-1)
 * @author   : caohaojie
 */
HPR_INT32 get_file_enc_limit_len(FILE_SEC_TAIL *pstFileSecTail, HPR_INT32 sdwFileCipherLen);



#ifdef __cplusplus
}
#endif
#endif /* __FILE_ENCRYPT_H__ END */
