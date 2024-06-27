/**
 * @copyright  HangZhou Hikvision Digital Technology Co., Ltd. All Right Reserved.
 * @file       aip_time_utils.h
 * @brief      时间模块基础函数
               时间戳:1970年01月01日00时00分00秒起至现在的总秒数
**/

#ifndef __AIP_TIME_UTILS_H__
#define __AIP_TIME_UTILS_H__

/************************************************************************
 Included Header
 ************************************************************************/
#include <time.h>
#include "timeMng/aip_time_common.h"
#include "common/aip_common.h"

#ifdef __cplusplus
extern "C"{
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
 * @fn         AIP_EXTERN time_t aip_time_current_get_struct_utc(AIP_TIME_P pstTime);
 * @brief      获取结构体类型的utc时间
 * @param[out] pstTime: 结构体类型的utc时间
 * @return     HPR_OK/HPR_ERROR
**/
AIP_EXTERN HPR_INT32 aip_time_current_get_struct_utc(AIP_TIME_P pstTime);

/**
 * @fn         AIP_EXTERN time_t aip_time_current_get_struct_local(AIP_TIME_P pstTime);
 * @brief      获取结构体类型的local时间
 * @param[out] pstTime: 结构体类型的local时间
 * @return     HPR_OK/HPR_ERROR
**/
AIP_EXTERN HPR_INT32 aip_time_current_get_struct_local(AIP_TIME_P pstTime);

/**
 * @fn         AIP_EXTERN time_t aip_time_current_get_utc(HPR_VOID);
 * @brief      获取utc时间
 * @return     时间戳/HPR_ERROR
**/
AIP_EXTERN time_t aip_time_current_get_utc(HPR_VOID);

/**
 * @fn         AIP_EXTERN time_t aip_time_current_get_local(HPR_VOID);
 * @brief      获取local时间
 * @return     时间戳/HPR_ERROR 
**/
AIP_EXTERN time_t aip_time_current_get_local(HPR_VOID);

/**
 * @fn         AIP_EXTERN HPR_INT32 aip_time_utils_utc_to_local(time_t ldwUtc,time_t* pldwLocal);
 * @brief      将utc时间转化为local时间
 * @param[in]  ldwUtc: utc时间戳(0时区)
 * @param[out] pldwLocal: 本地时间戳
 * @return     HPR_OK: success； other:fail
**/
AIP_EXTERN HPR_INT32 aip_time_utils_utc_to_local(time_t ldwUtc,time_t* pldwLocal);

/**
 * @fn         AIP_EXTERN HPR_INT32 aip_time_utils_local_to_utc(time_t ldwLocal,time_t* pldwUtc);
 * @brief      将local时间转为utc时间
 * @param[in]  ldwLocal: 本地时间戳
 * @param[out] pldwUtc: utc时间戳(0时区)
 * @return     HPR_OK: success； other:fail
**/
AIP_EXTERN HPR_INT32 aip_time_utils_local_to_utc(time_t ldwLocal,time_t* pldwUtc);

/**
 * @fn         AIP_EXTERN HPR_INT32 aip_time_utils_utc_to_iso8601(time_t ldwUtc,TIME_TYPE_E eType,HPR_INT8* pbyIso8601,HPR_INT32 dwIos8601Len)
 * @brief      utc时间转iso8601格式字符
 * @param[in]  ldwUtc: utc时间戳(0时区)
 * @param[in]  eType: 时间类型，E_TIME_TYPE_UTC/E_TIME_TYPE_LOCAL
 * @param[out] pbyIso8601: iso8601时间格式 yyyy-MM-dd’T’HH:mm:ss.SSSXXX, e.g. "2000-1-1T00:00:00.000+08:00"
               eType 为local时，不带时区信息默认本地时区：2017-08-01T17:30:08；eType为UTC时，附带时区信息，如：2017-08-01T17:30:08+08:00
 * @param[in]  dwIos8601Len: 字符串buffer长度
 * @return     HPR_OK: success； other:fail
**/
AIP_EXTERN HPR_INT32 aip_time_utils_utc_to_iso8601(time_t ldwUtc,TIME_TYPE_E eType,HPR_INT8* pbyIso8601,HPR_INT32 dwIos8601Len);

/**
 * @fn         AIP_EXTERN HPR_INT32 aip_time_utils_utc_to_rfc_3339_seconds(time_t ldwUtc,TIME_TYPE_E eType,HPR_INT8* pbyOut,HPR_INT32 dwBufSize);
 * @brief      utc时间转rfc-3339格式字符
 * @param[in]  ldwUtc: utc时间戳(0时区)
 * @param[in]  eType: 时间类型，E_TIME_TYPE_UTC/E_TIME_TYPE_LOCAL
 * @param[out] pbyOut: rfc-3339时间格式 yyyy-MM-dd HH:mm:ss, e.g. "2000-1-1 00:00:00+08:00", 
 *             同`date * --rfc-3339=seconds`
 *             eType 为local时，不带时区信息默认本地时区：2017-08-01 17:30:08；eType为UTC时，附带时区信息，如：2017-08-01 17:30:08+08:00
 * @param[in]  dwBufSize: 字符串buffer长度
 * @return     HPR_OK: success； other:fail
**/
AIP_EXTERN HPR_INT32 aip_time_utils_utc_to_rfc_3339_seconds(time_t ldwUtc,TIME_TYPE_E eType,HPR_INT8* pbyOut,HPR_INT32 dwBufSize);

/**
 * @fn         AIP_EXTERN HPR_INT32 aip_time_utils_iso8601_to_utc(HPR_INT8* pbyIso8601,time_t* pldwUtc);
 * @brief      iso8601格式字符转utc时间戳
 * @param[in]  pbyIso8601: iso8601时间格式 yyyy-MM-dd’T’HH:mm:ss.SSSXXX, e.g. "2000-1-1T00:00:00.000+08:00"
 * @param[out] pldwUtc: utc时间戳(0时区)
 * @return     HPR_OK: success； other:fail
**/
AIP_EXTERN HPR_INT32 aip_time_utils_iso8601_to_utc(HPR_INT8* pbyIso8601,time_t* pldwUtc);

/**
 * @fn         AIP_EXTERN HPR_INT32 aip_time_utils_utc_to_struct(time_t ldwUtc,AIP_TIME_P pstTime)
 * @brief      将UTC时间戳转成结构体(与时区有关)
 * @param[in]  ldwUtc: posix/uinx时间戳 1970年01月01日00时00分00秒起至现在的总秒数
 * @param[out] pstTime: 时间结构体(本地时间)
 * @return     HPR_OK: success； other:fail
**/
AIP_EXTERN HPR_INT32 aip_time_utils_utc_to_struct(time_t ldwUtc,AIP_TIME_P pstTime);

/**
 * @fn         AIP_EXTERN HPR_INT32 aip_time_utils_struct_to_utc(AIP_TIME_P pstTime,time_t* pldwUtc)
 * @brief      将结构体转成UTC时间戳(与时区有关)
 * @param[in]  pstTime: 时间结构体(本地时间)
 * @param[out] pldwUtc: posix/uinx时间戳 1970年01月01日00时00分00秒起至现在的总秒数
 * @return     HPR_OK: success； other:fail
**/
AIP_EXTERN HPR_INT32 aip_time_utils_struct_to_utc(AIP_TIME_P pstTime,time_t* pldwUtc);

/**
 * @fn         AIP_EXTERN HPR_INT32 aip_time_utils_compare(TIME_T stBegin,TIME_T stEnd);
 * @brief      比较起止时间的有效性
 * @param[in]  stBegin: 开始时间
 * @param[in]  stEnd: 结束时间
 * @return     HPR_OK: success； other:fail
**/
AIP_EXTERN HPR_INT32 aip_time_utils_compare(AIP_TIME_T stBegin,AIP_TIME_T stEnd);

/**
 * @fn         AIP_EXTERN HPR_INT32 aip_time_utils_compare_out(TIME_T stBegin,TIME_T stEnd);
 * @brief      比较起止时间的有效性
 * @param[in]  stBegin: 开始时间
 * @param[in]  stEnd: 结束时间
 * @param[out] pdwDiff: 比较结果，0-相等 -1-开始比结束小 1-开始比结束大
 * @return     HPR_OK: success； other:fail
**/
AIP_EXTERN HPR_INT32 aip_time_utils_compare_out(AIP_TIME_T stBegin,AIP_TIME_T stEnd, HPR_INT32 *pdwDiff);

/**
 * @fn         AIP_EXTERN time_t aip_mk_utc_time(struct tm *tm)
 * @brief      执行mktime前线转换时区为0时区，兼容android和linux系统默认分区不一致问题
 * @param[in]  *tm: 系统时间结构体
 * @return     success: 转换后的时间戳; fail:-1
**/
AIP_EXTERN time_t aip_mk_utc_time(struct tm *tm);

#ifdef __cplusplus
}
#endif

#endif /* __AIP_TIME_UTILS_H__ */
