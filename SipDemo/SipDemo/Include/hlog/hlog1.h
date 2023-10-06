/** @file   hlog1.h
 *  @note   HangZhou Hikvision System Technology Co., Ltd. All Right Reserved.
 *  @brief  ���ǿ�ɽӿ�
 *          
 *  @note   create file
 *  @author wangjingyf@hikvision.com
 *  @date   2012/09/05 15:30:44
 *
 *  @change log
 *
 */
#ifndef __HLOG1_H__
#define __HLOG1_H__

#include "hlogconfig.h"

#ifdef __cplusplus
extern "C"
{
#endif

    typedef void (HLOG_API *HLOG_CB)(HLOG_LEVEL level, const char* message);

    /** @fn void hlog_init(const char* name, char async = false)
    *   @brief ���ݾɽӿڣ���ִ���κβ���
    */
#ifdef __cplusplus
    HLOG_DECLARE int HLOG_API hlog_init(const char* name, char async = false);
#else
    HLOG_DECLARE int HLOG_API hlog_init(const char* name, char async);
#endif

    /** @fn void hlog_ocx_init(const char* name, const char* path, char async = false)
    *   @brief ���ݾɽӿڣ���ִ���κβ���
    */
#ifdef __cplusplus
    HLOG_DECLARE int HLOG_API hlog_ocx_init(const char* name, const char* path, char async = false);
#else
    HLOG_DECLARE int HLOG_API hlog_ocx_init(const char* name, const char* path, char async);
#endif

    /** @fn void hlog_fini()
    *   @brief ���ݾɽӿڣ���ִ���κβ���
    */
    HLOG_DECLARE int HLOG_API hlog_fini();

    /** @fn void hlog_set_callback(HLOG_CB callback)
    *   @brief ������־�Ļص�����
    *   @param callback ���ڴ�����־��Ϣ�Ļص�����
    */
    HLOG_DECLARE int HLOG_API hlog_set_callback(HLOG_CB callback);

    /** @fn void hlog_level(HLOG_LEVEL level)
    *   @brief ���ݾɽӿڣ���ִ���κβ���
    */
    HLOG_DECLARE int HLOG_API hlog_level(HLOG_LEVEL level);

    /** @fn void hlog_format(HLOG_LEVEL level, const char* module, const char* format, ...)
    *   @brief д��־��ʽ������
    *   @param level ��־����
    *   @param module ��־ģ��
    *   @param format ��־��ʽ���ַ�������ӿɱ����
    *   @note hlog_format�����hlog_set_callback����Ļص�����
    */
    HLOG_DECLARE int HLOG_API hlog_format(HLOG_LEVEL level, const char* module, const char* format, ...) LOG_CHECK_FMT(3, 4);

    /** @fn void hlog_message(HLOG_LEVEL level, const char* module, const char* message)
    *   @brief д��־�ַ���
    *   @param level ��־����
    *   @param module ��־ģ��
    *   @param message ��־�ַ���
    *   @note hlog_message�������hlog_set_callback����Ļص�����
    */
    HLOG_DECLARE int HLOG_API hlog_message(HLOG_LEVEL level, const char* module, const char* message);

#ifdef __cplusplus
}
#endif

// ���Ǽ����ԣ�������log_printf_def��log_printf_dst
#if (defined _WIN32 || defined _WIN64)
#define log_printf_def(level, format, ...)      hlog_format(level, "", format, ##__VA_ARGS__)
#else
#define log_printf_def(level, format, args...)  hlog_format(level, "", format, ##args)
#endif
#define log_printf_dst hlog_format

// for defualt module
#if (defined _WIN32 || defined _WIN64)
    #define LOG_ERROR(fmt, ...)         hlog_format(HLOG_LEVEL_ERROR, "default", "<%d>\t<%s>,"fmt, __LINE__, __FUNCTION__, ##__VA_ARGS__)
    #define LOG_WARN(fmt, ...)          hlog_format(HLOG_LEVEL_WARN, "default", "<%d>\t<%s>,"fmt,  __LINE__, __FUNCTION__, ##__VA_ARGS__)    
    #define LOG_INFO(fmt, ...)          hlog_format(HLOG_LEVEL_INFO, "default", "<%d>\t<%s>,"fmt,  __LINE__, __FUNCTION__, ##__VA_ARGS__)    
    #define LOG_DEBUG(fmt, ...)         hlog_format(HLOG_LEVEL_DEBUG, "default", "<%d>\t<%s>,"fmt, __LINE__, __FUNCTION__, ##__VA_ARGS__)    
    #define LOG_TRACE(fmt, ...)         hlog_format(HLOG_LEVEL_TRACE, "default", "<%d>\t<%s>,"fmt, __LINE__, __FUNCTION__, ##__VA_ARGS__)    
#else
    #define LOG_ERROR(fmt, args...)     hlog_format(HLOG_LEVEL_ERROR, "default", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
    #define LOG_WARN(fmt, args...)      hlog_format(HLOG_LEVEL_WARN, "default", "<%s>|<%d>\t<%s>,"fmt,  __FILE__, __LINE__, __FUNCTION__, ##args)
    #define LOG_INFO(fmt, args...)      hlog_format(HLOG_LEVEL_INFO, "default", "<%s>|<%d>\t<%s>,"fmt,  __FILE__, __LINE__, __FUNCTION__, ##args)
    #define LOG_DEBUG(fmt, args...)     hlog_format(HLOG_LEVEL_DEBUG, "default", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
    #define LOG_TRACE(fmt, args...)     hlog_format(HLOG_LEVEL_TRACE, "default", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
#endif

// for HPP module
#if (defined _WIN32 || defined _WIN64)
    #define HPP_ERROR(fmt, ...)         hlog_format(HLOG_LEVEL_ERROR, "HPP", "<%d>\t<%s>,"fmt, __LINE__, __FUNCTION__, ##__VA_ARGS__)
    #define HPP_WARN(fmt, ...)          hlog_format(HLOG_LEVEL_WARN, "HPP", "<%d>\t<%s>,"fmt,  __LINE__, __FUNCTION__, ##__VA_ARGS__)    
    #define HPP_INFO(fmt, ...)          hlog_format(HLOG_LEVEL_INFO, "HPP", "<%d>\t<%s>,"fmt,  __LINE__, __FUNCTION__, ##__VA_ARGS__)    
    #define HPP_DEBUG(fmt, ...)         hlog_format(HLOG_LEVEL_DEBUG, "HPP", "<%d>\t<%s>,"fmt, __LINE__, __FUNCTION__, ##__VA_ARGS__)    
    #define HPP_TRACE(fmt, ...)         hlog_format(HLOG_LEVEL_TRACE, "HPP", "<%d>\t<%s>,"fmt, __LINE__, __FUNCTION__, ##__VA_ARGS__)    
#else
    #define HPP_ERROR(fmt, args...)     hlog_format(HLOG_LEVEL_ERROR, "HPP", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
    #define HPP_WARN(fmt, args...)      hlog_format(HLOG_LEVEL_WARN, "HPP", "<%s>|<%d>\t<%s>,"fmt,  __FILE__, __LINE__, __FUNCTION__, ##args)
    #define HPP_INFO(fmt, args...)      hlog_format(HLOG_LEVEL_INFO, "HPP", "<%s>|<%d>\t<%s>,"fmt,  __FILE__, __LINE__, __FUNCTION__, ##args)
    #define HPP_DEBUG(fmt, args...)     hlog_format(HLOG_LEVEL_DEBUG, "HPP", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
    #define HPP_TRACE(fmt, args...)     hlog_format(HLOG_LEVEL_TRACE, "HPP", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
#endif

// for MQ module
#if (defined _WIN32 || defined _WIN64)
    #define MQ_ERROR(fmt, ...)          hlog_format(HLOG_LEVEL_ERROR, "MQ", "<%d>\t<%s>,"fmt, __LINE__, __FUNCTION__, ##__VA_ARGS__)
    #define MQ_WARN(fmt, ...)           hlog_format(HLOG_LEVEL_WARN, "MQ", "<%d>\t<%s>,"fmt,  __LINE__, __FUNCTION__, ##__VA_ARGS__)    
    #define MQ_INFO(fmt, ...)           hlog_format(HLOG_LEVEL_INFO, "MQ", "<%d>\t<%s>,"fmt,  __LINE__, __FUNCTION__, ##__VA_ARGS__)    
    #define MQ_DEBUG(fmt, ...)          hlog_format(HLOG_LEVEL_DEBUG, "MQ", "<%d>\t<%s>,"fmt, __LINE__, __FUNCTION__, ##__VA_ARGS__)    
    #define MQ_TRACE(fmt, ...)          hlog_format(HLOG_LEVEL_TRACE, "MQ", "<%d>\t<%s>,"fmt, __LINE__, __FUNCTION__, ##__VA_ARGS__)    
#else
    #define MQ_ERROR(fmt, args...)      hlog_format(HLOG_LEVEL_ERROR, "MQ", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
    #define MQ_WARN(fmt, args...)       hlog_format(HLOG_LEVEL_WARN, "MQ", "<%s>|<%d>\t<%s>,"fmt,  __FILE__, __LINE__, __FUNCTION__, ##args)
    #define MQ_INFO(fmt, args...)       hlog_format(HLOG_LEVEL_INFO, "MQ", "<%s>|<%d>\t<%s>,"fmt,  __FILE__, __LINE__, __FUNCTION__, ##args)
    #define MQ_DEBUG(fmt, args...)      hlog_format(HLOG_LEVEL_DEBUG, "MQ", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
    #define MQ_TRACE(fmt, args...)      hlog_format(HLOG_LEVEL_TRACE, "MQ", "<%s>|<%d>\t<%s>,"fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
#endif

#endif
