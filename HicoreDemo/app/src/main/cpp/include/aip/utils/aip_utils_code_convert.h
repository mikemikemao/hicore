/**
 * @copyright  HangZhou Hikvision Digital Technology Co., Ltd. All Right Reserved.
 * @file       aip_utils_code_convert.h
 * @brief      编码格式转换
 * @note       UTF-8与GB2312编码格式之间相互转换
**/

#ifndef __AIP_UTILS_CODE_CONVERT_H__
#define __AIP_UTILS_CODE_CONVERT_H__

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
#define COMMON_ENCODE_UTF8_MIN_LEN            1 // utf8 编码最小占用字节
#define COMMON_ENCODE_UTF8_MAX_LEN            4 // utf8 编码最大占用字节
#define COMMON_ENCODE_GBK                     2 // gbk/gb2312 编码占用字节

#define COMMON_ENCODE_UTF8_2_GBK_CONVERT_LEN(x)   (COMMON_ENCODE_GBK * (x/ COMMON_ENCODE_UTF8_MIN_LEN))   //utf8转换为gbk后的长度(取可能的最大值)，x为源数据长度
#define COMMON_ENCODE_GBK_2_UTF8_CONVERT_LEN(x)   (COMMON_ENCODE_UTF8_MAX_LEN * (x/ COMMON_ENCODE_GBK))   //gbk转换为utf8后的长度(取可能的最大值)，x为源数据长度

/************************************************************************
 Type Definition
 ************************************************************************/


/************************************************************************
 Function Declaration
 ************************************************************************/

/**
 * @fn         AIP_EXTERN HPR_INT32 aip_common_code_convert_utf8_to_gb2312(HPR_INT8 *pbySrc, HPR_INT32 dwSrcLen, HPR_INT8 *pbyDst, HPR_INT32 dwDstBufSize)
 * @brief      UTF-8编码转换为GB2312编码
 * @note       未在输出编码中找到输出字符编码将会采用音译的方式选择相似字符, 结果按成功返回
 * @note       未在输入编码中找到输入字符编码将返回-1
 * @param[in]  pbySrc : 源字符串地址
 * @param[in]  dwSrcLen : 源字符串长度
 * @param[out] pbyDst : 转换后的目标字符串地址
 * @param[in]  dwDstBufSize : 目的地址buffsize
 * @return     success: 转换后的长度; -1: fail
**/
AIP_EXTERN HPR_INT32 aip_common_code_convert_utf8_to_gb2312(HPR_INT8 *pbySrc, HPR_INT32 dwSrcLen, HPR_INT8 *pbyDst, HPR_INT32 dwDstBufSize);

/**
 * @fn         AIP_EXTERN HPR_INT32 aip_common_code_convert_gb2312_to_utf8(HPR_INT8 *pbySrc, HPR_INT32 dwSrcLen, HPR_INT8 *pbyDst, HPR_INT32 dwDstBufSize)
 * @brief      GB2312编码转换为UTF-8编码
 * @note       未在输出编码中找到输出字符编码将会采用音译的方式选择相似字符, 结果按成功返回
 * @note       未在输入编码中找到输入字符编码将返回-1
 * @param      pbySrc : 源字符串地址
 * @param      dwSrcLen : 源字符串长度
 * @param      pbyDst : 转换后的目标字符串地址
 * @param[in]  dwDstBufSize : 目的地址buffsize
 * @return     success: 转换后的长度; -1: fail
**/
AIP_EXTERN HPR_INT32 aip_common_code_convert_gb2312_to_utf8(HPR_INT8 *pbySrc, HPR_INT32 dwSrcLen, HPR_INT8 *pbyDst, HPR_INT32 dwDstBufSize);


/**
 * @fn         AIP_EXTERN HPR_INT32 aip_common_code_convert_utf8_to_gbk(HPR_INT8 *pbySrc, HPR_INT32 dwSrcLen, HPR_INT8 *pbyDst, HPR_INT32 dwDstBufSize)
 * @brief      UTF-8编码转换为GBK编码
 * @note       未在输出编码中找到输出字符编码将会采用音译的方式选择相似字符, 结果按成功返回
 * @note       未在输入编码中找到输入字符编码将返回-1
 * @param[in]  pbySrc : 源字符串地址
 * @param[in]  dwSrcLen : 源字符串长度
 * @param[out] pbyDst : 转换后的目标字符串地址
 * @param[in]  dwDstBufSize : 目的地址buffsize
 * @return     success: 转换后的长度; -1: fail
**/
AIP_EXTERN HPR_INT32 aip_common_code_convert_utf8_to_gbk(HPR_INT8 *pbySrc, HPR_INT32 dwSrcLen, HPR_INT8 *pbyDst, HPR_INT32 dwDstBufSize);

/**
 * @fn         AIP_EXTERN HPR_INT32 aip_common_code_convert_gbk_to_utf8(HPR_INT8 *pbySrc, HPR_INT32 dwSrcLen, HPR_INT8 *pbyDst, HPR_INT32 dwDstBufSize)
 * @brief      GBK编码转换为UTF-8编码
 * @note       未在输出编码中找到输出字符编码将会采用音译的方式选择相似字符, 结果按成功返回
 * @note       未在输入编码中找到输入字符编码将返回-1
 * @param      pbySrc : 源字符串地址
 * @param      dwSrcLen : 源字符串长度
 * @param      pbyDst : 转换后的目标字符串地址
 * @param[in]  dwDstBufSize : 目的地址buffsize
 * @return     success: 转换后的长度; -1: fail
**/
AIP_EXTERN HPR_INT32 aip_common_code_convert_gbk_to_utf8(HPR_INT8 *pbySrc, HPR_INT32 dwSrcLen, HPR_INT8 *pbyDst, HPR_INT32 dwDstBufSize);

/**
 * @fn         AIP_EXTERN HPR_INT32 aip_common_code_convert_utf8_to_utf16le(HPR_INT8 *pbySrc, HPR_INT32 dwSrcLen, HPR_INT8 *pbyDst, HPR_INT32 dwDstBufSize)
 * @brief      UTF-8编码转换为UTF-16LE编码
 * @note       未在输出编码中找到输出字符编码将会采用音译的方式选择相似字符, 结果按成功返回
 * @note       未在输入编码中找到输入字符编码将返回-1
 * @param[in]  pbySrc : 源字符串地址
 * @param[in]  dwSrcLen : 源字符串长度
 * @param[out] pbyDst : 转换后的目标字符串地址
 * @param[in]  dwDstBufSize : 目的地址buffsize
 * @return     success: 转换后的长度; -1: fail
**/
AIP_EXTERN HPR_INT32 aip_common_code_convert_utf8_to_utf16le(HPR_INT8 *pbySrc, HPR_INT32 dwSrcLen, HPR_INT8 *pbyDst, HPR_INT32 dwDstBufSize);

/**
 * @fn         AIP_EXTERN HPR_INT32 aip_common_code_convert_utf16le_to_utf8(HPR_INT8 *pbySrc, HPR_INT32 dwSrcLen, HPR_INT8 *pbyDst, HPR_INT32 dwDstBufSize)
 * @brief      UTF-16LE编码转换为UTF-8编码
 * @note       未在输出编码中找到输出字符编码将会采用音译的方式选择相似字符, 结果按成功返回
 * @note       未在输入编码中找到输入字符编码将返回-1
 * @param      pbySrc : 源字符串地址
 * @param      dwSrcLen : 源字符串长度
 * @param      pbyDst : 转换后的目标字符串地址
 * @param[in]  dwDstBufSize : 目的地址buffsize
 * @return     success: 转换后的长度; -1: fail
**/
AIP_EXTERN HPR_INT32 aip_common_code_convert_utf16le_to_utf8(HPR_INT8 *pbySrc, HPR_INT32 dwSrcLen, HPR_INT8 *pbyDst, HPR_INT32 dwDstBufSize);


/**
 * @fn         AIP_EXTERN HPR_INT32 aip_common_xml_entity_refer_encode(HPR_INT8 *pbySrc, HPR_INT32 dwSrcLen, HPR_INT8 *pbyDst, HPR_INT32 dwDstBufSize)
 * @brief      xml特殊字符转义(将xml特殊字符转换为实体引用)
 * @param      pbySrc : 源字符串地址
 * @param      dwSrcLen : 源字符串长度
 * @param      pbyDst : 转换后的目标字符串地址
 * @param[in]  dwDstBufSize : 目的地址buffsize, 至少应该为dwSrcLen + 1长度（或更长）
 * @return     success: 转换后的长度; -1: fail
**/
AIP_EXTERN HPR_INT32 aip_common_xml_entity_refer_encode(HPR_INT8 *pbySrc, HPR_UINT32 dwSrcLen, HPR_INT8 *pbyDst, HPR_UINT32 dwDstBufSize);

/**
 * @fn         * @fn         AIP_EXTERN HPR_INT32 aip_common_xml_entity_refer_decode(HPR_INT8 *pbySrc, HPR_INT32 dwSrcLen, HPR_INT8 *pbyDst, HPR_INT32 dwDstBufSize)
 * @brief      xml特殊字符反转义(将xml特殊字符实体引用转换为常规字符)
 * @param      pbySrc : 源字符串地址
 * @param      dwSrcLen : 源字符串长度
 * @param      pbyDst : 转换后的目标字符串地址
 * @param[in]  dwDstBufSize : 目的地址buffsize, 至少应该为dwSrcLen + 1长度（或更长）
 * @return     success: 转换后的长度; -1: fail
**/
AIP_EXTERN HPR_INT32 aip_common_xml_entity_refer_decode(HPR_INT8 *pbySrc, HPR_UINT32 dwSrcLen, HPR_INT8 *pbyDst, HPR_UINT32 dwDstBufSize);

#ifdef __cplusplus
}
#endif
#endif /* __AIP_UTILS_CODE_CONVERT_H__ END */
