/**
 * @copyright  HangZhou Hikvision Digital Technology Co., Ltd. All Right Reserved.
 * @file       aip_utils_file_process.h
 * @brief      和文件、文件夹操作相关的基础函数
**/

#ifndef __AIP_UTILS_FILE_PROCESS_H__
#define __AIP_UTILS_FILE_PROCESS_H__

/************************************************************************
 Included Header
 ************************************************************************/
#include "common/aip_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/************************************************************************
 Macros
 ************************************************************************/

/************************************************************************
 Type Definition
 ************************************************************************/


/************************************************************************
 Function Declaration
 ************************************************************************/

/**
 * @fn     AIP_EXTERN HPR_BOOL aip_check_is_dir(const HPR_INT8 *szPathName);
 * @brief  判断路径是不是目录
 * @param  [in] szPathName : # 目录或文件名称
 * @return HPR_TRUE: 路径是目录;  HPR_FALSE: 路径不存在路径或不是目录
*/
AIP_EXTERN HPR_BOOL aip_check_is_dir(const HPR_INT8 *szPathName);

/**
 * @fn         AIP_EXTERN HPR_INT32 aip_common_mkdir_p(const HPR_INT8 *pDir)
 * @brief      递归创建目录
 * @param[in]  szDir : 要创建的目录, see COMMON_PATH_LEN
 * @return     HPR_OK: success; other : fail
 * @note       输入的目录为绝对路径，目录存在时函数返回HPR_OK, 所创建的目录名与已存在的文件名相同时创建失败
**/
AIP_EXTERN HPR_INT32 aip_common_mkdir_p(const HPR_INT8 *szDir);

/**
 * @fn         AIP_EXTERN HPR_INT32 common_rm_r(const HPR_INT8 *szPathName)
 * @brief      删除文件，若是文件直接删除，若是目录 递归删除目录下以及子目录下的所有文件和目录
 * @param[in]  szPathName : 要删除的路径, see COMMON_PATH_LEN define
 * @return     HPR_OK: success(包括删成功和文件本身就不存在); other: fail
**/
AIP_EXTERN HPR_INT32 aip_common_rm_r(const HPR_INT8 *szPathName);

/**
 * @fn          AIP_EXTERN HPR_INT32 aip_common_cp_r(HPR_INT8* szSrcPath, HPR_INT8* szDstPath)
 * @brief       拷贝文件(类似于 cp -r 的命令)， 支持目录和文件
 * @param[in]   szSrcPath: 源文件 , see COMMON_PATH_LEN define
 * @param[in]   szDstPath: 目的文件,不允许与szSrcPath一致, see COMMON_PATH_LEN define
 * @return      HPR_OK : success; other : fail
**/
AIP_EXTERN HPR_INT32 aip_common_cp_r(HPR_INT8* szSrcPath, HPR_INT8* szDstPath);

/**
 * @fn         AIP_EXTERN HPR_INT32 aip_common_mv(HPR_INT8 *szSrcPath, HPR_INT8 *szDstPath)
 * @brief      移动文件或目录(均可)
 * @param[in]  szSrcPath : 源文件地址, see COMMON_PATH_LEN define
 * @param[out] szDstPath : 目标文件地址,see COMMON_PATH_LEN define
 * @note       如果szDstPath存在，失败
 * @return     HPR_OK : success; other : fail
**/
AIP_EXTERN HPR_INT32 aip_common_mv(HPR_INT8 *szSrcPath, HPR_INT8 *szDstPath);

/**
 * @fn         AIP_EXTERN HPR_INT32 aip_common_get_file_size(HPR_INT8 *szFileName);
 * @brief      获取文件大小
 * @param[in]  szFileName : 文件名, , see COMMON_PATH_LEN define
 * @return     success:文件大小(单位 bytes); fail: -1
 * @note       若文件是目录 则只返回目录本身的大小,不包含目录下的文件的大小
 * @note       若文件是软连接，返回软连接指向的实际文件的大小
**/
AIP_EXTERN HPR_INT32 aip_common_get_file_size(HPR_INT8 *szFileName);

/**
 * @fn         AIP_EXTERN AIP_DEPRECATE HPR_INT32 aip_common_get_dir_size(HPR_INT8 *szDirPath, HPR_UINT32 *pdwDirSize, HPR_UINT32 *pdwFileNum)
 * @brief      获取目录所谓分区大小
 * @param[in]  pDirPath : 目录所在路径, see COMMON_PATH_LEN
 * @param[out] pdwDirSize : 若不为NULL，将返回目录所占分区大小
 * @param[out] pdwFileNum : 若不为NULL,将返回目录内普通文件数量
 * @note       不允许pdwDirSize和pdwFileNum 同时为NULL, 因为这没有意义
 * @return     HPR_OK: success; other : fail
 * @note       函数出参pdwDirSize是目录中的文件大小加上目录的大小(4096)
 * @note       只适用总大小小于4GB的目录，建议使用aip_common_get_dir_size_ext
**/
AIP_EXTERN AIP_DEPRECATE_MSG("replace by aip_common_get_dir_size_v2") HPR_INT32 aip_common_get_dir_size(HPR_INT8 *szDirPath, HPR_UINT32 *pdwDirSize, HPR_UINT32 *pdwFileNum);

/**
 * @fn         AIP_EXTERN HPR_INT32 aip_common_get_dir_size_v2(HPR_INT8 *szDirPath, HPR_UINT64 *pldwDirSize, HPR_UINT32 *pdwFileNum)
 * @brief      获取目录所谓分区大小
 * @param[in]  pDirPath : 目录所在路径, see COMMON_PATH_LEN
 * @param[out] pldwDirSize : 若不为NULL，将返回目录所占分区大小
 * @param[out] pdwFileNum : 若不为NULL,将返回目录内普通文件数量
 * @note       不允许pldwDirSize和pdwFileNum 同时为NULL, 因为这没有意义
 * @return     HPR_OK: success; other : fail
 * @note       函数出参pldwDirSize是目录中的文件大小加上目录的大小(4096)
**/
AIP_EXTERN HPR_INT32 aip_common_get_dir_size_v2(HPR_INT8 *szDirPath, HPR_UINT64 *pldwDirSize, HPR_UINT32 *pdwFileNum);

/**
 * @fn         AIP_EXTERN HPR_INT32 aip_common_count_reg_file_num(HPR_INT8 *szDirPath);
 * @brief      统计指定目录下常规文件个数
 * @param[in]  szDirPath : 目录所在路径, see COMMON_PATH_LEN
 * @return     success: 常规文件的个数(应当是一个大于等于0的值); fail: -1
 * @note       reg file 指常规文件(不包含软连接、目录等), 仅统计第一层，不会递归统计
**/
AIP_EXTERN HPR_INT32 aip_common_count_reg_file_num(HPR_INT8 *szDirPath);

/**
 * @fn         AIP_EXTERN HPR_BOOL aip_common_check_dir_is_empty(HPR_INT8 *szDirPath);
 * @brief      判断制定目录下是否为空
 * @param[in]  szDirPath : 目录所在路径, see COMMON_PATH_LEN
 * @return     HPR_TRUE: 为空；HPR_FALSE: 不为空 (该目录不存在视为空)
**/
AIP_EXTERN HPR_BOOL aip_common_check_dir_is_empty(HPR_INT8 *szDirPath);


/**
 * @fn         AIP_EXTERN HPR_INT32 aip_common_get_disk_volume(HPR_INT8 *szPath, HPR_UINT64 *pllTotalVolume, HPR_UINT64 *pllFreeVolume)
 * @brief      获取目录所在磁盘分区空间信息
 * @param[in]  szPath : 目录所在的路径, see COMMON_PATH_LEN define
 * @param[out] pllTotalVolume : 磁盘总空间大小(单位bytes)
 * @param[out] pllFreeVolume : 磁盘剩余空间大小(单位bytes)
 * @return     HPR_OK/HPR_ERROR
**/
AIP_EXTERN HPR_INT32 aip_common_get_disk_volume(HPR_INT8 *szPath, HPR_UINT64 *pllTotalVolume, HPR_UINT64 *pllFreeVolume);

/**
 * @fn         AIP_EXTERN HPR_INT32 aip_common_dir_or_file_exist(HPR_INT8 *szPath)
 * @brief      判断文件或目录是否存在
 * @param[in]  szPath : 文件或目录的路径, see COMMON_PATH_LEN define
 * @return     HPR_OK: 存在该目录或文件;  HPR_ERROR: 不存在该目录或文件
**/
AIP_EXTERN HPR_INT32 aip_common_dir_or_file_exist(HPR_INT8 *szPath);

/**
 * @fn         AIP_EXTERN HPR_INT32 aip_common_write_file(HPR_INT8 *szFilePath, HPR_INT8 *pbySrc, HPR_UINT32 dwLen)
 * @brief      将指定数据写入到指定文件, 要求指定的文件目录已经存在
 *             若文件不存在，先创建. (不会递归创建, 即父目录要存在.)
 *             若文件已经存在，则会先清空文件
 * @param[in]  szFilePath : 文件路径, see COMMON_PATH_LEN define
 * @param[in]  pbySrc : 文件buff
 * @param[in]  dwLen : 数据长度
 * @return     HPR_OK : success; other : fail
**/
AIP_EXTERN HPR_INT32 aip_common_write_file(HPR_INT8 *szFilePath, HPR_INT8 *pbySrc, HPR_INT32 dwLen);

/**
 * @fn         AIP_EXTERN HPR_INT32 aip_common_read_file(HPR_INT8 *szFilePath, HPR_INT8 **ppBuf, HPR_UINT32 *pdwOutLen);
 * @brief      读取指定文件的所有内容
 * @param[in]  szFilePath : 文件路径, see COMMON_PATH_LEN define
 * @param[out] pbyBuf : success 时返回存放的数据buf地址
 * @param[out] dwBufSize : buf的有效长度
 * @note       当文件的长度不超过dwBufSize 时，将会读取文件长度的数据，并将超出文件长度部分的buf置为'\0'
 *             当文件长度超过dwBufSife，将会读取dwBufSize长度的数据。
 * @return      success: 实际读取的长度， fail : -1 (如文件不存在)
**/
AIP_EXTERN HPR_INT32 aip_common_read_file(HPR_INT8 *szFilePath, HPR_INT8 *pbyBuf, HPR_UINT32 dwBufSize);

/**
 * @fn         AIP_EXTERN HPR_INT32 aip_common_read_file(HPR_INT8 *szFilePath, HPR_INT8 **ppBuf, HPR_UINT32 *pdwOutLen);
 * @brief      读取指定文件的所有内容
 * @param[in]  szFilePath : 文件路径, see COMMON_PATH_LEN define
 * @param[out] ppBuf : success 时返回存放的数据buf地址，在结束生命周期时，外部需要调用free进行释放
 * @param[out] pdwOutLen : 读取到的文件长度
 * @return     HPR_OK: success， other(如文件不存在、文件长度为0):fail
**/
AIP_EXTERN HPR_INT32 aip_common_read_file_all(HPR_INT8 *szFilePath, HPR_INT8 **ppBuf, HPR_UINT32 *pdwOutLen);


#ifdef __cplusplus
}
#endif
#endif /* __AIP_UTILS_FILE_PROCESS_H__ END */
