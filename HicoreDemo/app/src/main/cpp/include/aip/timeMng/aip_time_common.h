/**
 * @copyright HangZhou Hikvision Digital Technology Co., Ltd. All Right Reserved.
 * @file      aip_time_common.h
 * @brief     时间结构体定义
 */

#ifndef __AIP_TIME_COMMON_H__
#define __AIP_TIME_COMMON_H__

/************************************************************************
 Included Header
 ************************************************************************/
#include "HPR_Types.h"

#ifdef __cplusplus
extern "C"{
#endif

/************************************************************************
 Macros
 ************************************************************************/
#define LEAP_YEAR(x)            (x&3) ? 0 : (x%100 ? 1 : (x%400?0:1)) /*  闰年判断 */

/************************************************************************
 Type Definition
 ************************************************************************/

/**
 * @brief： 时间结构体
**/
typedef struct AIP_TIME_T
{
    HPR_UINT16 wYear;       //公历年(0-65536), 如2000年将会表示为2000，而不是30
    HPR_UINT8 byMonth;      //月(1-12)
    HPR_UINT8 byDay;        //日(1-31)
    HPR_UINT8 byHour;       //时(0-23)
    HPR_UINT8 byMinute;     //分(0-59)
    HPR_UINT8 bySecond;     //秒(0-59)
    HPR_UINT16 wMiliSecond; //毫秒(0-999)
    HPR_UINT8 byWeekDay;    //星期(0周日-6周六)
    HPR_UINT8 byRes[2]; 
} AIP_TIME_T, *AIP_TIME_P;

/**
 * @brief： 时间类型
**/
typedef enum TIME_TYPE_E
{
    E_TIME_TYPE_UTC   = 0, //UTC时间，即0时区时间
    E_TIME_TYPE_LOCAL = 1, //local时间,受时区影响
} TIME_TYPE_E;

#define AIP_TIME_ERR_FORMAT     (-2)    //时间格式不正确
#define AIP_TIME_ERR_RANGE      (-3)    //时间范围不正确

/************************************************************************
  Function Declaration
 ************************************************************************/


#ifdef __cplusplus
}
#endif

#endif /* __AIP_TIME_COMMON_H__ */
