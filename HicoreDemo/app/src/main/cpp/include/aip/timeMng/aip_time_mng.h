/**
 * @copyright HangZhou Hikvision Digital Technology Co., Ltd. All Right Reserved.
 * @file      aip_time_mng.h
 * @brief     时间管理模块
**/

#ifndef __AIP_TIME_MNG_H__
#define __AIP_TIME_MNG_H__

/************************************************************************
 Included Header
 ************************************************************************/
#include <time.h>
#include <sys/time.h>
#include "common/aip_common.h"
#include "common/aip_common_event.h"
#include "timeMng/aip_time_common.h"
#include "lstLib.h"

#ifdef __cplusplus
extern "C"{
#endif

/************************************************************************
 Macros
 ************************************************************************/
#define AIP_MAX_TIMEZONE_NAME_LEN    128

/************************************************************************
 Type Definition
 ************************************************************************/

/**
 * @brief      时间管理模块回调类型
**/
typedef enum
{
    TIME_EVENT_ADJUST_NORMAL        = 1,    // 普通校时
                                      //入参:NULL
                                      //出参:NULL
                                      //返回值: HPR_OK
                                      //        HPR_FALSE
    TIME_EVENT_ADJUST_NTP           = 2,    // NTP校时
                                      //入参:NULL
                                      //出参:NULL
                                      //返回值: HPR_OK
                                      //        HPR_FALSE
    TIME_EVENT_SUMMER_TIME_BEGIN    = 3,    // 进入夏令时
                                      //入参:TIME_DST_P, 夏令时参数
                                      //出参:NULL
                                      //返回值: HPR_OK
                                      //        HPR_FALSE
    TIME_EVENT_SUMMER_TIME_END      = 4,    // 退出夏令时
                                      //入参:TIME_DST_P, 夏令时参数
                                      //出参:NULL
                                      //返回值: HPR_OK
                                      //        HPR_FALSE
    TIME_EVENT_NTP_SERVICE_START    = 5,    // ntp服务启动(T1需要该状态)
                                      //入参:NULL
                                      //出参:NULL
                                      //返回值: HPR_OK
                                      //        HPR_FALSE
    TIME_EVENT_TIME_ZONE_SYNC       = 6,    // 时区信息同步(三方配置同步给hicore)
                                      //入参:TIME_TIMEZONE_P, 时区参数
                                      //出参:NULL
                                      //返回值: HPR_OK
                                      //        HPR_FALSE
}TIME_EVENT_CMD_E;

/**
 *  @brief 时间模块事件回调
 */
typedef AIP_EVENT_CALLBACK_FUN TIME_EVENT_CALLBACK_FUN ;

/**
 * @brief  时区信息
**/
typedef struct
{
    HPR_INT8   byTimeDiffH;     /* 与国际标准时间的时差（小时）时区H，-12 ... +13 */
    HPR_UINT8  byTimeDiffM;     /* 与国际标准时间的时差（分钟）时区M，0, 30, 45 */
    HPR_INT8   byTimeCity[AIP_MAX_TIMEZONE_NAME_LEN]; /* 时区标识 IANA 例如 Asia/Shanghai windows例如China Standard Time*/
    HPR_INT8   byType;          /* 时区类型 0 - IANA时区 ， 1- windows时区     */
    HPR_INT8   byRes[5];
} TIME_TIMEZONE_T, *TIME_TIMEZONE_P;

/**
 * @brief      夏令时起止时间结构体
**/
typedef struct
{
    HPR_UINT8       byMonth;    //月份(1-12)
    HPR_UINT8       byWeekNo;   //该月的第X周(1-5)
    HPR_UINT8       byWeekday;  //周日(0)-周六(6)
    HPR_UINT8       byHour;     //时(0-23)
    HPR_UINT8       byMin;      //分(0-59)
    HPR_UINT16      wYear;      //公历年(0-65536) 如2000年将会表示为2000，而不是30(一般夏令时配置不用配该字段)
    HPR_UINT8       byRes[1];
} DST_POINT_T;

/**
 * @brief      夏令时配置参数
               安卓系统可以不用设置，系统管理
**/
typedef struct
{
    HPR_UINT8       byEnableDST;                    // 启用夏令时      0-不启用，1-启用
    HPR_UINT8       bySummerTimeFlag;               // 是否已处于夏令时标志
    HPR_UINT8       byRes[2];
    HPR_UINT32      dwDSTBias;                      // 时间调整值 单位(分钟)
    DST_POINT_T     stBeginpoint;                   // 夏令时起始时间(当地时间) 
    DST_POINT_T     stEndpoint;                     // 夏令时结束时间(当地时间)
} TIME_DST_T, *TIME_DST_P;

/**
 * @brief      NTP配置结构体
 * @note       NTP客户端不能同步NTP服务器的时区，NTP只同步UTC时间,因此无需关注NTP服务器时区
**/
typedef struct
{
    HPR_UINT8       byEnable;               // 启用NTP校时     0-不启用，1-启用
    HPR_UINT8       byNTPServer[64];        // NTP服务器域名或者IP地址 
    HPR_UINT8       byRes[3];              
    HPR_UINT16      wNtpPort;               // NTP服务器端口号
    HPR_UINT16      wInterval;              // 校时间隔时间（单位:分钟）
} TIME_NTP_SERVICE_PARAM_T, *TIME_NTP_SERVICE_PARAM_P;


/**
 * @brief      时间初始化结构体
**/
typedef struct
{
    TIME_TIMEZONE_T             stTimeZone; // 设备时区信息
    TIME_DST_T                  stDSTParam; // 设备夏令时参数
    TIME_NTP_SERVICE_PARAM_T    stNtpParam; // 设备NTP校时服务器参数
    TIME_TYPE_E                 enTimeType; // 系统/RTC时间类型, 0-UTC时间(默认), 1-LOCAL时间(仅Linux有效).
} TIME_INIT_T;

/**
 * @brief      IANA时区列表结构体
**/
typedef struct
{
    HPR_INT8 * pbyName;          //城市名称
    HPR_INT8 * pbyIANAZone;      //iana时区标志
} TIME_IANA_ZONE_T;

/**
 * @brief: IANA时区链表节点
**/
typedef struct
{
    NODE                            node;              //链表节点
    TIME_IANA_ZONE_T stInfo;
} TIME_IANA_ZONE_NODE_T, *TIME_IANA_ZONE_NODE_P;

typedef LIST TIME_IANA_INFO_LIST;         /* IANA节点列表，每个链表节点结构体为 TIME_IANA_ZONE_NODE_T */

/************************************************************************
  Function Declaration
 ************************************************************************/

/**
 * @fn         AIP_EXTERN HPR_INT32 aip_time_mng_init(TIME_INIT_T* pstInitParam);
 * @brief      时间管理模块初始化
 * @param[in]  pstInitParam: 初始化参数
 * @param      fnCbFun, 回调函数
 * @return     HPR_OK: success； other:fail
 * @note       每次初始化会重置启动的utc时间
**/
AIP_EXTERN HPR_INT32 aip_time_mng_init(TIME_INIT_T* pstInitParam, TIME_EVENT_CALLBACK_FUN fnCbFun);

/**
 * @fn         AIP_EXTERN HPR_INT32 time_mng_uninit(HPR_VOID);
 * @brief      时间管理模块反初始化
 * @return     HPR_OK: success； other:fail
**/
AIP_EXTERN HPR_INT32 aip_time_mng_uninit(HPR_VOID);

/**
 * @fn         AIP_EXTERN HPR_VOID aip_time_adjust_request(time_t ldwTimeToAdjuest);
 * @brief      手动校时请求
 * @param[in]  ldwTimeToAdjuest: UTC时间戳
**/
AIP_EXTERN HPR_VOID aip_time_adjust_request(time_t ldwTimeToAdjuest);

/**
 * @fn         AIP_EXTERN HPR_INT32 aip_time_set_ntp_service_config(TIME_NTP_SERVICE_PARAM_T stNtpCfg);
 * @brief      ntp服务参数配置
 * @param[in]  pstNtpCfg: ntp服务参数
 * @return     HPR_OK: success； other:fail
**/
AIP_EXTERN HPR_INT32 aip_time_set_ntp_service_config(TIME_NTP_SERVICE_PARAM_T stNtpCfg);

/**
 * @fn         AIP_EXTERN HPR_INT32 aip_time_get_ntp_service_config(TIME_NTP_SERVICE_PARAM_T* pstNtpCfg);
 * @brief      ntp服务参数获取
 * @param[out] pstNtpCfg: ntp服务参数
 * @return     HPR_OK: success； other:fail
**/
AIP_EXTERN HPR_INT32 aip_time_get_ntp_service_config(TIME_NTP_SERVICE_PARAM_T* pstNtpCfg);

/**
 * @fn         AIP_EXTERN HPR_INT32 aip_time_set_timezone(TIME_TIMEZONE_T stTimeZone)
 * @brief      设置时区
 * @param[in]  stTimeZone : 时区
 * @return     HPR_OK: success； other:fail
**/
AIP_EXTERN HPR_INT32 aip_time_set_timezone(TIME_TIMEZONE_T stTimeZone);

/**
 * @fn         AIP_EXTERN HPR_INT32 aip_time_get_timezone(TIME_TIMEZONE_P pstTimeZone)
 * @brief      获取时区
 * @param[out] pstTimeZone : 时区
 * @return     HPR_OK: success； other:fail
**/
AIP_EXTERN HPR_INT32 aip_time_get_timezone(TIME_TIMEZONE_P pstTimeZone);

/**
 * @fn         AIP_EXTERN HPR_INT32 aip_time_set_summer_time(TIME_DST_T stDST)
 * @brief      设置夏令时
 * @param[in]  stDST: 夏令时参数
 * @return     HPR_OK: success； other:fail
**/
AIP_EXTERN HPR_INT32 aip_time_set_summer_time(TIME_DST_T stDST);

/**
 * @fn         AIP_EXTERN HPR_INT32 aip_time_get_summer_time(TIME_DST_P pstDST)
 * @brief      获取夏令时
 * @param[out] pstDST: 夏令时参数
 * @return     HPR_OK: success； other:fail
**/
AIP_EXTERN HPR_INT32 aip_time_get_summer_time(TIME_DST_P pstDST);

/**
 * @fn         AIP_EXTERN time_t aip_time_boot_get(HPR_VOID);
 * @brief      获取设备启动时间的utc时间(实际是aip_time_mng_init的时间)
 * @return     时间戳/HPR_ERROR 
 * @note       aip_time_mng_init 之后方有效
**/
AIP_EXTERN time_t aip_time_boot_get(HPR_VOID);


/**
 * @fn         AIP_EXTERN TIME_IANA_INFO_LIST* aip_time_get_iana_list(HPR_INT8* pbyLanguage);
 * @brief      获取语言对应的iana及地区链表
 * @param[in]  pbyLanguage: 语言enum:[chinese#（简体）中文, english#英语, spanish#西班牙语, portuguese#葡萄牙语, italian#意大利语, french#法语, russian#俄语, 
 * turkish#土耳其语, greek#希腊语, czech#捷克语, brazilianPortuguese#巴西葡萄牙语, slovenian#斯洛文尼亚语, swedish#瑞典语, norwegian#挪威语, german#德语,
 * arabic#阿拉伯语, japanese#日语, dutch#荷兰语, polish#波兰语, romanian#罗马尼亚语, slovak#斯洛伐克语, serbian#塞尔维亚语, hungarian#匈牙利语, danish#丹麦语, 
 * finnish#芬兰语, thai#泰语, vietnamese#越南语, korean#韩语, southAmericanSpanish#南美西班牙语, ukrainian#乌克兰语, croatian#克罗地亚语, irish#爱尔兰语, 
 * bulgarian#保加利亚语, hebrew#希伯来语, indonesian#印尼语, traditionalChinese#（台湾）繁体中文, lithuanian#立陶宛语, anglicism#英式英语, estonian#爱沙尼亚语, 
 * latvian#拉脱维亚语, EURSpanish#西班牙语（欧洲）, uzbek#乌兹别克语, kazak#哈萨克语, kirghiz#吉尔吉斯语, farsi#波斯语, azerbaidzhan#阿塞拜疆语, burmese#缅甸语,
 * mongolian#蒙古语, HKTraditionalChinese#中国香港繁体中文]
 * @return     时区列表 
**/
AIP_EXTERN TIME_IANA_INFO_LIST* aip_time_get_iana_list(HPR_INT8* pbyLanguage);

/**
 * @fn         AIP_EXTERN HPR_INT32 aip_time_release_iana_list(TIME_IANA_INFO_LIST* pList);
 * @brief      释放时区链表
 * @param[in]  pList: 要释放的时区链表
 * @return     HPR_OK: success; other:fail 
**/
AIP_EXTERN HPR_INT32 aip_time_release_iana_list(TIME_IANA_INFO_LIST* pList);

/**
 * @fn: 校验时区信息的有效性
 * @description: 
 * @return HPR_OK 成功/ HPR_ERROR-失败
 * @param [in] byType 时区类型 0 - IANA时区 ， 1- windows时区
 * @param [in] pbyTimeCity 时区标识 IANA 例如 Asia/Shanghai windows例如China Standard Time
 */
HPR_INT32 aip_time_check_timezone(HPR_INT8 byType,HPR_INT8* pbyTimeCity);

#ifdef __cplusplus
}
#endif

#endif /* __AIP_TIME_MNG_H__ */
