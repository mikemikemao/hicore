/**
 * @copyright  HangZhou Hikvision Digital Technology Co., Ltd. All Right Reserved.
 * @file       aip_utils_string_deal.h
 * @brief      和字符串处理相关的函数
**/
#ifndef __AIP_UTILS_STRING_DEAL_H__
#define __AIP_UTILS_STRING_DEAL_H__

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
 * @fn         AIP_EXTERN HPR_INT32 aip_common_hash_value_to_str(HPR_INT8* pbySrc, HPR_UINT32 dwSrcLen,HPR_INT8* pbyDst, HPR_UINT32 dwBufLen)
 * @brief      将hash 值转换为对应的字符串 0-9 a-f 小写
 * @param[in]  pbySrc : hash 值地址
 * @param[in]  dwSrcLen : hash 值所占的地址大小
 * @param[out] pDst : hash 字符串输出地址，输出长度固定为2 *dwSrcLen
 * @param[in]  dwBufLen : hash 字符串输出地址长度(要求至少为 2*dwSrcLen +1 (包含截断符))
 * @return     HPR_OK: success; other: 失败
**/
AIP_EXTERN HPR_INT32 aip_common_hash_value_to_str(HPR_INT8* pbySrc, HPR_UINT32 dwSrcLen, HPR_INT8* pbyDst, HPR_UINT32 dwBufLen);

/**
 * @fn         AIP_EXTERN HPR_INT32 aip_common_string_tolower(const HPR_INT8* pbySrc, HPR_INT8* pbyDst, HPR_UINT32 dwLen)
 * @brief      字符串转小写, 数字、特殊符号、原小写字母不受影响
 * @param[in]  pbySrc : 源字符串
 * @param[out] pbyDst : 目的字符串
 * @param[in]  dwLen : 字符串长度
 * @return     success : HPR_OK; other : fail
**/
AIP_EXTERN HPR_INT32 aip_common_string_tolower(const HPR_INT8* pbySrc, HPR_INT8* pbyDst, HPR_UINT32 dwLen);

/**
 * @fn         AIP_EXTERN HPR_INT32 aip_common_string_toupper(const HPR_INT8* pbySrc, HPR_INT8* pbyDst, HPR_INT32 dwLen)
 * @brief      字符串小写转为大写
 * @param[in]  pbySrc : 源字符串
 * @param[out] pbyDst : 目的字符串
 * @param[in]  dwLen : 字符串长度
 * @return     success : HPR_OK; other : fail
**/
AIP_EXTERN HPR_INT32 aip_common_string_toupper(const HPR_INT8* pbySrc, HPR_INT8* pbyDst, HPR_INT32 dwLen);

/**
 * @fn          AIP_EXTERN HPR_BOOL aip_check_is_digitstr(const HPR_INT8 *szStr);
 * @brief       判断字符串里的字符是否全部是数字
 * @param[in]   szStr    : 要检验的字符串
 * @return      HPR_TRUE:  字符串里的字符全部是数字, HPR_FALSE: 字符串里的字符不全是数字
**/
AIP_EXTERN HPR_BOOL aip_check_is_digitstr(const HPR_INT8 *szStr);

/**
 * @fn         AIP_EXTERN HPR_INT32 aip_str_replace(HPR_INT8 *szStr, HPR_UINT32 dwStrSize, HPR_INT8 *szOldStr, HPR_INT8 *szNewStr)
 * @brief      字符串替代，将字符串中的旧字符串替代为新字符串
 * @param[out] szStr : 字符串
 * @param[in]  dwStrSize : 字符串缓冲区大小
 * @param[in]  szOldStr : 旧字符串
 * @param[in]  szNewStr : 新字符串
 * @return     success: 进行了替代的个数; fail: -1
 * @note       需注意当新字符串长度大于要被替换的旧字符串时。有可能因为dwStrSize不足而未替换完全
**/
AIP_EXTERN HPR_INT32 aip_str_replace(HPR_INT8 *szStr, HPR_UINT32 dwStrSize, HPR_INT8 *szOldStr, HPR_INT8 *szNewStr);

#ifdef __cplusplus
}
#endif
#endif /* __AIP_UTILS_STRING_DEAL_H__ END */
