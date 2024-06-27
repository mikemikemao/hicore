/**
 * @copyright  HangZhou Hikvision Digital Technology Co., Ltd. All Right Reserved.
 * @file       aip_common.h
 * @brief      基础函数
**/

#ifndef __AIP_COMMON_H__
#define __AIP_COMMON_H__

/************************************************************************
 Included Header
 ************************************************************************/
#include "HPR_Types.h"

#ifdef __cplusplus
extern "C" {
#endif

/************************************************************************
 Macros
 ************************************************************************/
#ifdef __GNUC__
    #define GCC_VERSION_AT_LEAST(x,y) (__GNUC__ > (x) || __GNUC__ == (x) && __GNUC_MINOR__ >= (y))
#else
    #define GCC_VERSION_AT_LEAST(x,y) 0
#endif

#if GCC_VERSION_AT_LEAST(3,1)
    #define AIP_DEPRECATE        __attribute__((deprecated))
    #define AIP_DEPRECATE_MSG(x) __attribute__((deprecated(x)))
#else
    #define AIP_DEPRECATE
    #define AIP_DEPRECATE_MSG
#endif

#define AIP_EXTERN __attribute__ ((visibility("default")))

#ifndef USER_NAME_LEN
#define USER_NAME_LEN    (32)    /* 用户 用户名最长长度(不包含截断符) */
#endif

#ifndef USER_PWD_LEN
#define USER_PWD_LEN     (32)    /* 用户 密码长度最长长度(不包含截断符) */
#endif

#ifndef USER_SALT_LEN
#define USER_SALT_LEN    (64)  /* 用户 salt值（恒定长度，不包含截断符） */
#endif

#ifndef USER_IRREVERSIBLE_PWD_LEN
#define USER_IRREVERSIBLE_PWD_LEN    (64)    /* 用户 不可逆密码长度（恒定长度，不包含截断符） */
#endif

#ifndef USER_MD5_PWD_LEN
#define USER_MD5_PWD_LEN    (32)    /* 用户 md5类型的摘要密码长度（恒定长度，不包含截断符） */
#endif

#ifndef USER_REAML_LEN
#define USER_REAML_LEN      (12)    /* 用户 摘要认证的reaml长度（恒定长度，不包含截断符） */
#endif

#ifndef COMMON_PATH_LEN
#define COMMON_PATH_LEN                                           (512) //文件名/路径名最长限制，(包含截断符)
#endif

#ifndef OPERATE_NAME_LEN
#define OPERATE_NAME_LEN (64)    /* 关键操作名最大长度(不包含截断符) */
#endif

#define GETFILENAME(x) strrchr(x,'/')?strrchr(x,'/')+1:x
#define FILENAME (GETFILENAME(__FILE__))                         //文件名宏


#ifndef CMD_LEN
#define CMD_LEN                                           (512) //shell命令最大长度
#endif

/************************************************************************
 Type Definition
 ************************************************************************/



/************************************************************************
 Function Declaration
 ************************************************************************/

#ifdef __cplusplus
}
#endif
#endif /* __AIP_COMMON_H__ END */
