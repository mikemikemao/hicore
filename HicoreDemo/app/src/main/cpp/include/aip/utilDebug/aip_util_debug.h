/**
 * @copyright HangZhou Hikvision Digital Technology Co., Ltd. All Right Reserved.
 * @file      aip_util_debug.h
 * @brief     打印控制
 * @note      依赖log4j组件
 */

#ifndef __AIP_UTIL_DEBUG_H__
#define __AIP_UTIL_DEBUG_H__


/************************************************************************
 Included Header
 ************************************************************************/
#include <stdio.h>
#include <stdarg.h>
#include "common/aip_common.h"
#include "aip_util_module.h"

#ifdef __cplusplus
extern "C" {
#endif

/************************************************************************
 Macros
 ************************************************************************/
#define DEBUG_FORBID_PRINT_SENSITIVE_INFO

/** @brief 不相关参数 宏定义，如果函数的参数并不需要使用，则调用该宏，避免出现编译告警 */
#define UTIL_UNREFERENCED_PARAMETER(x)    {(x) = (x);}

/** @brief 模块内部函数返回值  */
#ifndef DEBUG_RETURN
#define DEBUG_RETURN
    #define STATUS_TRUE         (1)   /*成功，返回值为bool型时使用*/
    #define STATUS_FALSE        (0)   /*失败，返回值为bool型时使用*/
#endif  //DEBUG_RETURN


/** @brief debug print Level */
#ifndef DEBUG_PRINT_LEVEL
#define DEBUG_PRINT_LEVEL
    /** debug Level */
    #define DBG_NONE                (-1)  /* may be used set by cmd */
    #define DBG_ERR                 (1)  /* error info */
    #define DBG_INFO                (3)  /* debug info*/
    #define DBG_HINT                (4)  /* hint info*/
    #define DBG_SETI                (6)  /* sensitive information info */
 
    /** 新增 代码禁止使用以下打印等级, 旧代码打印接口修改后，以下打印等级移除 */
    #define DBG_CRIT                (0)  /* critical info  */
    #define DBG_WARN                (2)  /* waring info */
    #define DBG_PRIT                (5)  /* print info*/

    /* debug Level num*/
    #define DBG_LEV_NUM             (7)
#endif //DEBUG_PRINT_LEVEL



/** @brief debug print information format */
#ifndef DEBUG_PRINT_INFO_FOTMAT
#define DEBUG_PRINT_INFO_FOTMAT
    /*information format*/
    #define DBG_FORMAT_NONE             (0)
    #define DBG_FORMAT_TIME             (1<<0) /*打印信息中是否要带时间信息*/
    #define DBG_FORMAT_PATH             (1<<1) /*打印信息中是否需要带文件路径*/
    #define DBG_FORMAT_FILE             (1<<2) /*打印信息中是否需要带文件名*/
    #define DBG_FORMAT_FUNCTION         (1<<3) /*打印信息中是否要带函数名*/
    #define DBG_FORMAT_LINE             (1<<4) /*打印信息中是否要带行号*/
    #define DBG_FORMAT_TID              (1<<5) /*打印信息中是否要带行号*/
#endif  //DEBUG_PRINT_INFO_FOTMAT


#define  UTIL_FILE          __FILE__
#define  UTIL_LINE          __LINE__

/*__VA_ARGS__ can only appear in the expansion of a C99 variadic macro*/
//#define  UTIL_VA_ARGS       __VA_ARGS__
#if defined(_WIN32)
    #if _MSC_VER >= 1200
        #define UTIL_FUNCTION        __FUNCTION__
    #else
        #define UTIL_FUNCTION        (const HPR_INT8 *)0
    #endif
#elif defined(__linux__)
    #if __GNUC__ >= 3
        #define UTIL_FUNCTION        __FUNCTION__
    #else
        #define UTIL_FUNCTION        (const HPR_INT8 *)0
    #endif
#elif defined(__FREERTOS__)
    #define UTIL_FUNCTION        __FUNCTION__
#endif

/**
 * @brief   判断指定模块是否开启, 如果开启：打印指定信息
 * @param    [in] DBG_T             [打印等级(宏定义)]
 * @param    [in] MODULE_IDX        [主模块序号(宏定义)]
 * @param    [in] MODULE_MASK       [子模块序号(宏定义)]
 */
#define UTIL_DEBUG(DBG_T, MODULE_IDX, MODULE_MASK, ...)\
{\
    if (aip_util_dbg_open(DBG_T, MODULE_IDX, MODULE_MASK))\
    {\
        aip_util_debug(UTIL_FILE, UTIL_LINE, UTIL_FUNCTION, DBG_T,MODULE_IDX,MODULE_MASK,__VA_ARGS__);\
    }\
}

/**
 * @brief   不判断指定模块是否开启,打印信息
 * @param    [in] DBG_T             [打印等级(宏定义)]
 * @param    [in] MODULE_IDX        [主模块序号(宏定义)]
 * @param    [in] MODULE_MASK       [子模块序号(宏定义)]
 */
#define USR_DBG(...)    \
    UTIL_DEBUG(DBG_PRIT, MODULE_DBG_FILE, MASK_DBG_FILE, __VA_ARGS__)

/**
 * @brief: 用户正常使用 需要打印的提示信息
 **/
#define UTIL_USER_INFO   \
    printf

/**
 * @brief   判断指定值如果为null值，return 指定值
 * @param    c          [指定的判断值]
 * @param    ret        [指定的return值]
 * @return              [description]
 */
#define usr_assert(c, ret)\
{\
    if(!(c))\
    {\
        UTIL_DEBUG(DBG_ERR, MODULE_DBG_FILE, MASK_DBG_FILE,\
            "[%s] Assertion: %s fail!\n", UTIL_FUNCTION, #c);\
        return (ret);\
    }\
}

/************************************************************************
 Type Definition
 ************************************************************************/

/**
 * @brief 认证回调接口类型
 * @:param szUserName： 管理员用户名
 * @:param szPassword： 管理员密码
 * @return HPR_OK: success; other:fail
 */
typedef HPR_INT32(*UTIL_DEBUG_AUTH_CB_FUN)(HPR_INT8* szUserName, HPR_INT8* szPassword);


/************************************************************************
  Function Declaration
 ************************************************************************/

/**
 * @fn      AIP_EXTERN HPR_INT32 aip_util_debug_init(HPR_VOID)
 * @brief   调试打印模块初始化
 * @note    默认的打印等级按以下优先级获取
 *           1.AIP_UTLI_DEBUG_LEVEL环境变量, 值支持 NONE|CRIT|ERRO|INFO|HINT
 *           2.aip_util_debug_set_default_level 接口设置的默认等级
 *           以上值都没有设置默认为DBG_INFO
 * @return  [success:STATUS_OK;   fail:STATUS_ERROR]
**/
AIP_EXTERN HPR_INT32 aip_util_debug_init(HPR_VOID);

/**
 * @fn      AIP_EXTERN HPR_VOID aip_util_debug_hex(HPR_UINT8 *pBuff, HPR_INT32 dwBufLen)
 * @brief   打印16进制字符，每16个字节打印一行。
 * @param   [in] pBuff      [需要打印的内容]
 * @param   [in] bufLen     [打印信息长度]
 */
AIP_EXTERN HPR_VOID aip_util_debug_hex(HPR_UINT8 *pBuff, HPR_INT32 dwBufLen);


/**
 * @fn      AIP_EXTERN HPR_INT32 aip_util_dbg_open(HPR_INT32 dwDbgLevel, HPR_INT32 dwModIdx, HPR_INT32 dwModMask);
 * @brief   判断指定的模块打印是否开启
 * @param    [in] dbgLevel   [打印级别]
 * @param    [in] modIdx     [主模块序号(宏定义)]
 * @param    [in] modMask    [子模块序号(宏定义)]
 * @return              [模块打印开启:STATUS_TRUE; 模块打印关闭:STATUS_FALSE;]
 */
AIP_EXTERN HPR_INT32 aip_util_dbg_open(HPR_INT32 dwDbgLevel, HPR_INT32 dwModIdx, HPR_INT32 dwModMask);

/** 
 * @fn       AIP_EXTERN HPR_VOID aip_util_debug(const HPR_INT8 *pFile, HPR_INT32 dwLine, const HPR_INT8 *pFunction, HPR_INT32 dwLevel, HPR_UINT32 dwModIdx, HPR_UINT32 dwModMask, const HPR_INT8 *fmt, ...);
 * @brief   打印指定字符串
 * @param    [in] file       [打印所在路径与文件名 __FILE__]
 * @param    [in] line       [打印所在行号 __LINE__]
 * @param    [in] function   [打印所在函数名 __FUNCTION]
 * @param    [in] level      [打印等级]
 * @param    [in] modIdx     [主模块序号]
 * @param    [in] modMask    [子模块序号]
 * @param    [in] fmt        [打印信息]
 */
AIP_EXTERN HPR_VOID aip_util_debug(const HPR_INT8 *pFile, HPR_INT32 dwLine, const HPR_INT8 *pFunction, HPR_INT32 dwLevel, HPR_UINT32 dwModIdx, HPR_UINT32 dwModMask, const HPR_INT8 *fmt, ...);

/**
 * @fn      AIP_EXTERN HPR_VOID aip_util_debug_va_list(const HPR_INT8 *pFile, HPR_INT32 dwLine, const HPR_INT8 *pFunction, HPR_INT32 dwLevel, HPR_UINT32 dwModIdx, HPR_UINT32 dwModMask, const HPR_INT8 *fmt, va_list stAp);
 * @brief   打印指定字符串
 * @param    [in] file       [打印所在路径与文件名 __FILE__]
 * @param    [in] line       [打印所在行号 __LINE__]
 * @param    [in] function   [打印所在函数名 __FUNCTION]
 * @param    [in] level      [打印等级]
 * @param    [in] modIdx     [主模块序号]
 * @param    [in] modMask    [子模块序号]
 * @param    [in] fmt        [打印信息格式]
 * @param    [in] ap         [打印信息]
 */
AIP_EXTERN HPR_VOID aip_util_debug_va_list(const HPR_INT8 *pFile, HPR_INT32 dwLine, const HPR_INT8 *pFunction, HPR_INT32 dwLevel, HPR_UINT32 dwModIdx, HPR_UINT32 dwModMask, const HPR_INT8 *fmt, va_list stAp);

/**
 * @fn      AIP_EXTERN HPR_INT32 aip_util_set_dbg_ctrl(const HPR_INT8 *pRecvBuf, HPR_INT32 dwRecvBufLen, HPR_INT8 *pSendBuf, HPR_INT32 dwSendBufLen)
 * @brief   调试等级设置接口，开放给shell模块使用
 * @param   [in] recvBuf
 * @param   [out] sendBuf
 * @return  STATUS_TRUE 成功，STATUS_FALSE 失败
**/
AIP_EXTERN HPR_INT32 aip_util_set_dbg_ctrl(const HPR_INT8 *pRecvBuf, HPR_INT32 dwRecvBufLen, HPR_INT8 *pSendBuf, HPR_INT32 dwSendBufLen);

/**
 * @fn      AIP_EXTERN HPR_VOID aip_util_debug_set_auth_fun(UTIL_DEBUG_AUTH_CB_FUN dwFnAuthFunc)
 * @brief   设置认证回调接口
 * @param   [in] fnAuthFunc 回调接口
**/
AIP_EXTERN HPR_VOID aip_util_debug_set_auth_fun(UTIL_DEBUG_AUTH_CB_FUN dwFnAuthFunc);


/**
 * @fn        AIP_EXTERN HPR_INT32 aip_util_debug_set_default_level(HPR_INT32 sdwLevel)
 * @brief     设置 默认打印等级, 不设置默认为DBG_ERR
 * @note      该接口使用无需初始化
 * @param[in] sdwLevel 要设置的[设置等级]， see DEBUG_PRINT_LEVEL
 * @return    [成功:STATUS_TRUE; 失败:STATUS_FALSE]
 */
AIP_EXTERN HPR_INT32 aip_util_debug_set_default_level(HPR_INT32 sdwLevel);

#ifdef __cplusplus
}
#endif

#endif //__AIP_UTIL_DEBUG_H__
