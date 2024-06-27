/******************************************************************************
  @note HangZhou Hikvision Digital Technology Co., Ltd. All Right Reserved.
 ******************************************************************************
  @file : securec_api_macro.h
  @brief : Security Functions  Headers（For tracing of the call）
  @author : ccy
  @date : 2022/10/5
  @note : Create
******************************************************************************/

#ifndef _HIK_SAFE_MACRO_H_
#define _HIK_SAFE_MACRO_H_

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */
 
 /*----------------------------------------------*
 * Included Header                              *
 *----------------------------------------------*/
#include "libsafefunc/hprsafefunc.h"

/*----------------------------------------------*
 * Macros                                       *
 *----------------------------------------------*/
 
/*******************MEMSET_SEC*******************/

#define MEMSET_SEC(dest, destMax, c, count)    scurec_default_err_handle_cb_Judgment(); \
HPR_MEMSET_S(dest, destMax, c, count)

#define MEMSET_NATIVE_S(dest, destMax, c, count)    HPR_MEMSET_NATIVE_S(dest, destMax, c, count)

/*******************MEMMOVE_SEC*******************/

#define MEMMOVE_SEC(dest, destMax, src, count)    scurec_default_err_handle_cb_Judgment(); \
HPR_MEMMOVE_S(dest, destMax, src, count)

#define MEMMOVE_NATIVE_SEC(dest, destMax, src, count)    HPR_MEMMOVE_NATIVE_S(dest, destMax, src, count)

/*******************MEMCPY_SEC*******************/

#define MEMCPY_SEC(dest, destMax, src, count)    scurec_default_err_handle_cb_Judgment(); \
HPR_MEMCPY_S(dest, destMax, src, count)

#define MEMCPY_NATIVE_SEC(dest, destMax, src, count)    HPR_MEMCPY_NATIVE_S(dest, destMax, src, count)

/*******************STRCPY_SEC*******************/

#define STRCPY_SEC(strDest, destMax, strSrc)    scurec_default_err_handle_cb_Judgment(); \
HPR_STRCPY_S(strDest, destMax, strSrc)

#define STRCPY_NATIVE_SEC(strDest, destMax, strSrc)    HPR_STRCPY_NATIVE_S(strDest, destMax, strSrc)

/*******************STRNCPY_SEC*******************/

#define STRNCPY_SEC(strDest, destMax, strSrc, count)    scurec_default_err_handle_cb_Judgment(); \
HPR_STRNCPY_S(strDest, destMax, strSrc, count)

#define STRNCPY_NATIVE_SEC(strDest, destMax, strSrc, count)    HPR_STRNCPY_NATIVE_S(strDest, destMax, strSrc, count)

/*******************STRCAT_SEC*******************/

#define STRCAT_SEC(strDest, destMax, strSrc)    scurec_default_err_handle_cb_Judgment(); \
HPR_STRCAT_S(strDest, destMax, strSrc)

#define STRCAT_NATIVE_SEC(strDest, destMax, strSrc)    HPR_STRCAT_NATIVE_S(strDest, destMax, strSrc)

/*******************STRNCAT_SEC*******************/

#define STRNCAT_SEC(strDest, destMax, strSrc, count)    scurec_default_err_handle_cb_Judgment(); \
HPR_STRNCAT_S(strDest, destMax, strSrc, count)

#define STRNCAT_NATIVE_SEC(strDest, destMax, strSrc, count)    HPR_STRNCAT_NATIVE_S(strDest, destMax, strSrc, count)

/*******************VSPRINTF_SEC*******************/

#define VSPRINTF_SEC(strDest, destMax, format, ...)    scurec_default_err_handle_cb_Judgment(); \
HPR_VSPRINTF_S(strDest, destMax, format, ##__VA_ARGS__)

#define VSPRINTF_NATIVE_SEC(strDest, destMax, format, ...)    HPR_VSPRINTF_NATIVE_S(strDest, destMax, format, ##__VA_ARGS__)

/*******************SPRINTF_SEC*******************/

#define SPRINTF_SEC(strDest, destMax, format, ...)    scurec_default_err_handle_cb_Judgment(); \
HPR_SPRINTF_S(strDest, destMax, format, ##__VA_ARGS__)

#define SPRINTF_NATIVE_SEC(strDest, destMax, format, ...)    HPR_SPRINTF_NATIVE_S(strDest, destMax, format, ##__VA_ARGS__)

/*******************VSNPRINTF_SEC*******************/

#define VSNPRINTF_SEC(strDest, destMax, count, format, ...)    scurec_default_err_handle_cb_Judgment(); \
HPR_VSNPRINTF_S(strDest, destMax, count, format, ##__VA_ARGS__)

#define VSNPRINTF_NATIVE_SEC(strDest, destMax, count, format, ...)    HPR_VSNPRINTF_NATIVE_S(strDest, destMax, count, format, ##__VA_ARGS__)

/*******************SNPRINTF_SEC*******************/

#define SNPRINTF_SEC(strDest, destMax, count, format, ...)    scurec_default_err_handle_cb_Judgment(); \
HPR_SNPRINTF_S(strDest, destMax, count, format, ##__VA_ARGS__)

#define SNPRINTF_NATIVE_SEC(strDest, destMax, count, format, ...)    HPR_SNPRINTF_NATIVE_S(strDest, destMax, count, format, ##__VA_ARGS__)

/*******************SCANF_SEC*******************/

#define SCANF_SEC(format, ...)    scurec_default_err_handle_cb_Judgment(); \
HPR_SCANF_S(format, ##__VA_ARGS__)

#define SCANF_NATIVE_SEC(format, ...)    HPR_SCANF_NATIVE_S(format, ##__VA_ARGS__)

/*******************VSCANF_SEC*******************/

#define VSCANF_SEC(format, ...)    scurec_default_err_handle_cb_Judgment(); \
HPR_VSCANF_S(format, ##__VA_ARGS__)

#define VSCANF_NATIVE_SEC(format, ...)    HPR_VSCANF_NATIVE_S(format, ##__VA_ARGS__)

/*******************SSCANF_SEC*******************/

#define SSCANF_SEC(buffer, format, ...)    scurec_default_err_handle_cb_Judgment(); \
HPR_SSCANF_S(buffer, format, ##__VA_ARGS__)

#define SSCANF_NATIVE_SEC(buffer, format, ...)    HPR_SSCANF_NATIVE_S(buffer, format, ##__VA_ARGS__)

/*******************VSSCANF_SEC*******************/

#define VSSCANF_SEC(buffer, format, ...)    scurec_default_err_handle_cb_Judgment(); \
HPR_VSSCANF_S(buffer, format, ##__VA_ARGS__)

#define VSSCANF_NATIVE_SEC(buffer, format, ...)    HPR_VSSCANF_NATIVE_S(buffer, format, ##__VA_ARGS__)

/*******************FSCANF_SEC*******************/

#define FSCANF_SEC(stream, format, ...)    scurec_default_err_handle_cb_Judgment(); \
HPR_FSCANF_S(stream, format, ##__VA_ARGS__)

#define FSCANF_NATIVE_SEC(stream, format, ...)    HPR_FSCANF_NATIVE_S(stream, format, ##__VA_ARGS__)

/*******************VFSCANF_SEC*******************/

#define VFSCANF_SEC(stream, format, ...)    scurec_default_err_handle_cb_Judgment(); \
HPR_VFSCANF_S(stream, format, ##__VA_ARGS__)

#define VFSCANF_NATIVE_SEC(stream, format, ...)    HPR_VFSCANF_NATIVE_S(stream, format, ##__VA_ARGS__)

/*******************STRTOK_SEC*******************/

#define STRTOK_SEC(strToken, strDelimit, context)    scurec_default_err_handle_cb_Judgment(); \
HPR_STRTOK_S(strToken, strDelimit, context)

#define STRTOK_NATIVE_SEC(strToken, strDelimit, context)    HPR_STRTOK_NATIVE_S(strToken, strDelimit, context)

/*******************GETS_SEC*******************/

#define GETS_SEC(buffer, destMax)    scurec_default_err_handle_cb_Judgment(); \
HPR_GETS_S(buffer, destMax)

#define GETS_NATIVE_SEC(buffer, destMax)    HPR_GETS_NATIVE_S(buffer, destMax)

/*******************WMEMCPY_SEC*******************/

#define WMEMCPY_SEC(dest, destMax, src, count)    scurec_default_err_handle_cb_Judgment(); \
HPR_WMEMCPY_S(dest, destMax, src, count)

#define WMEMCPY_NATIVE_SEC(dest, destMax, src, count)    HPR_WMEMCPY_NATIVE_S(dest, destMax, src, count)

/*******************WMEMMOVE_SEC*******************/

#define WMEMMOVE_SEC(dest, destMax, src, count)    scurec_default_err_handle_cb_Judgment(); \
HPR_WMEMMOVE_S(dest, destMax, src, count)

#define WMEMMOVE_NATIVE_SEC(dest, destMax, src, count)    HPR_WMEMMOVE_NATIVE_S(dest, destMax, src, count)

/*******************WCSCPY_SEC*******************/

#define WCSCPY_SEC(strDest, destMax, strSrc)    scurec_default_err_handle_cb_Judgment(); \
HPR_WCSCPY_S(strDest, destMax, strSrc)

#define WCSCPY_NATIVE_SEC(strDest, destMax, strSrc)    HPR_WCSCPY_NATIVE_S(strDest, destMax, strSrc)

/*******************WCSNCPY_SEC*******************/

#define WCSNCPY_SEC(strDest, destMax, strSrc, count)    scurec_default_err_handle_cb_Judgment(); \
HPR_WCSNCPY_S(strDest, destMax, strSrc, count)

#define WCSNCPY_NATIVE_SEC(strDest, destMax, strSrc, count)    HPR_WCSNCPY_NATIVE_S(strDest, destMax, strSrc, count)

/*******************WCSCAT_SEC*******************/

#define WCSCAT_SEC(strDest, destMax, strSrc)    scurec_default_err_handle_cb_Judgment(); \
HPR_WCSCAT_S(strDest, destMax, strSrc)

#define WCSCAT_NATIVE_SEC(strDest, destMax, strSrc)    HPR_WCSCAT_NATIVE_S(strDest, destMax, strSrc)

/*******************WCSNCAT_SEC*******************/

#define WCSNCAT_SEC(strDest, destMax, strSrc, count)    scurec_default_err_handle_cb_Judgment(); \
HPR_WCSNCAT_S(strDest, destMax, strSrc, count)

#define WCSNCAT_NATIVE_SEC(strDest, destMax, strSrc, count)    HPR_WCSNCAT_NATIVE_S(strDest, destMax, strSrc, count)

/*******************WCSTOK_SEC*******************/

#define WCSTOK_SEC(strToken, strDelimit, context)    scurec_default_err_handle_cb_Judgment(); \
HPR_WCSTOK_S(strToken, strDelimit, context)

#define WCSTOK_NATIVE_SEC(strToken, strDelimit, context)    HPR_WCSTOK_NATIVE_S(strToken, strDelimit, context)

/*******************VSWPRINTF_SEC*******************/

#define VSWPRINTF_SEC(strDest, destMax, format, ...)    scurec_default_err_handle_cb_Judgment(); \
HPR_VSWPRINTF_S(strDest, destMax, format, ##__VA_ARGS__)

#define VSWPRINTF_NATIVE_SEC(strDest, destMax, format, ...)    HPR_VSWPRINTF_NATIVE_S(strDest, destMax, format, ##__VA_ARGS__)

/*******************SWPRINTF_SEC*******************/

#define SWPRINTF_SEC(strDest, destMax, format, ...)    scurec_default_err_handle_cb_Judgment(); \
HPR_SWPRINTF_S(strDest, destMax, format, ##__VA_ARGS__)

#define SWPRINTF_NATIVE_SEC(strDest, destMax, format, ...)    HPR_SWPRINTF_NATIVE_S(strDest, destMax, format, ##__VA_ARGS__)

/*******************FWSCANF_SEC*******************/

#define FWSCANF_SEC(stream, format, ...)    scurec_default_err_handle_cb_Judgment(); \
HPR_FWSCANF_S(stream, format, ##__VA_ARGS__)

#define FWSCANF_NATIVE_SEC(stream, format, ...)    HPR_FWSCANF_NATIVE_S(stream, format, ##__VA_ARGS__)

/*******************HPR_VFWSCANF_SEC*******************/

#define HPR_VFWSCANF_SEC(stream, format, ...)    scurec_default_err_handle_cb_Judgment(); \
HPR_VFWSCANF_S(stream, format, ##__VA_ARGS__)

#define HPR_VFWSCANF_NATIVE_SEC(stream, format, ...)    HPR_VFWSCANF_NATIVE_S(stream, format, ##__VA_ARGS__)

/*******************WSCANF_SEC*******************/

#define WSCANF_SEC(format, ...)    scurec_default_err_handle_cb_Judgment(); \
HPR_WSCANF_S(format, ##__VA_ARGS__)

#define WSCANF_NATIVE_SEC(format, ...)    HPR_WSCANF_NATIVE_S(format, ##__VA_ARGS__)

/*******************VWSCANF_SEC*******************/

#define VWSCANF_SEC(format, ...)    scurec_default_err_handle_cb_Judgment(); \
HPR_VWSCANF_S(format, ##__VA_ARGS__)

#define VWSCANF_NATIVE_SEC(format, ...)    HPR_VWSCANF_NATIVE_S(format, ##__VA_ARGS__)

/*******************SWSCANF_SEC*******************/

#define SWSCANF_SEC(buffer, format, ...)    scurec_default_err_handle_cb_Judgment(); \
HPR_SWSCANF_S(buffer, format, ##__VA_ARGS__)

#define SWSCANF_NATIVE_SEC(buffer, format, ...)    HPR_SWSCANF_NATIVE_S(buffer, format, ##__VA_ARGS__)

/*******************VSWSCANF_SEC*******************/

#define VSWSCANF_SEC(buffer, format, ...)    scurec_default_err_handle_cb_Judgment(); \
HPR_VSWSCANF_S(buffer, format, ##__VA_ARGS__)

#define VSWSCANF_NATIVE_SEC(buffer, format, ...)    HPR_VSWSCANF_NATIVE_S(buffer, format, ##__VA_ARGS__)


/*******************MEMCMP_SEC_EX*******************/
#define MEMCMP_SEC_EX(dest, dmax, src, smax, count, diff)    (__hpr_safec_errno_t = memcmp_sec_ex(dest, dmax, src, smax, count, diff));\
do{\
    if(EOK != __hpr_safec_errno_t)\
    {\
        scurec_default_err_handle_cb_Judgment();\
        __hpr_safec_error_handle(__FILE__, __LINE__, __FUNCTION__, "MEMCMP_SEC_EX", __hpr_safec_errno_t);\
    }\
}while(0);

#define MEMCMP_SEC_NATIVE_EX(dest, dmax, src, smax, count, diff)   memcmp_sec_ex(dest, dmax, src, smax, count, diff)

/*******************MEMCMP_SEC*******************/
#define MEMCMP_SEC(dest, dmax, src, smax, diff)    (__hpr_safec_errno_t = memcmp_sec(dest, dmax, src, smax, diff));\
do{\
    if(EOK != __hpr_safec_errno_t)\
    {\
        scurec_default_err_handle_cb_Judgment();\
        __hpr_safec_error_handle(__FILE__, __LINE__, __FUNCTION__, "MEMCMP_SEC", __hpr_safec_errno_t);\
    }\
}while(0);

#define MEMCMP_NATIVE_SEC(dest, dmax, src, smax, diff)    memcmp_sec(dest, dmax, src, smax, diff)

/*******************MEMZERO_SEC*******************/
#define MEMZERO_SEC(dest, len)    (__hpr_safec_errno_t = memzero_sec(dest, len));\
do{\
    if(EOK != __hpr_safec_errno_t)\
    {\
        scurec_default_err_handle_cb_Judgment();\
        __hpr_safec_error_handle(__FILE__, __LINE__, __FUNCTION__, "MEMZERO_SEC", __hpr_safec_errno_t);\
    }\
}while(0);

#define MEMZERO_NATIVE_SEC(dest, len)    memzero_sec(dest, len)

/*******************STRCASECMP_SEC*******************/
#define STRCASECMP_SEC(dest, dmax, src, indicator)    (__hpr_safec_errno_t = strcasecmp_sec(dest, dmax, src, indicator));\
do{\
    if(EOK != __hpr_safec_errno_t)\
    {\
        scurec_default_err_handle_cb_Judgment();\
        __hpr_safec_error_handle(__FILE__, __LINE__, __FUNCTION__, "STRCASECMP_SEC", __hpr_safec_errno_t);\
    }\
}while(0);

#define STRCASECMP_NATIVE_SEC(dest, dmax, src, indicator)    strcasecmp_sec(dest, dmax, src, indicator)

/*******************STRCASESTR_SEC*******************/
#define STRCASESTR_SEC(dest, dmax, src, slen, substring)    (__hpr_safec_errno_t = strcasestr_sec(dest, dmax, src, slen, substring));\
do{\
    if(EOK != __hpr_safec_errno_t)\
    {\
        scurec_default_err_handle_cb_Judgment();\
        __hpr_safec_error_handle(__FILE__, __LINE__, __FUNCTION__, "STRCASESTR_SEC", __hpr_safec_errno_t);\
    }\
}while(0);

#define STRCASESTR_NATIVE_SEC(dest, dmax, src, slen, substring)    strcasestr_sec(dest, dmax, src, slen, substring)

/*******************STRCMP_SEC*******************/
#define STRCMP_SEC(dest, dmax, src, indicator)    (__hpr_safec_errno_t = strcmp_sec(dest, dmax, src, indicator));\
do{\
    if(EOK != __hpr_safec_errno_t)\
    {\
        scurec_default_err_handle_cb_Judgment();\
        __hpr_safec_error_handle(__FILE__, __LINE__, __FUNCTION__, "STRCMP_SEC", __hpr_safec_errno_t);\
    }\
}while(0);

#define STRCMP_NATIVE_SEC(dest, dmax, src, indicator)    strcmp_sec(dest, dmax, src, indicator)

/*******************STRCMPFLD_SEC*******************/
#define STRCMPFLD_SEC(dest, dmax, src, indicator)    (__hpr_safec_errno_t = strcmpfld_sec(dest, dmax, src, indicator));\
do{\
    if(EOK != __hpr_safec_errno_t)\
    {\
        scurec_default_err_handle_cb_Judgment();\
        __hpr_safec_error_handle(__FILE__, __LINE__, __FUNCTION__, "STRCMPFLD_SEC", __hpr_safec_errno_t);\
    }\
}while(0);

#define STRCMPFLD_NATIVE_SEC(dest, dmax, src, indicator)    strcmpfld_sec(dest, dmax, src, indicator)

/*******************STRCPYFLD_SEC*******************/
#define STRCPYFLD_SEC(dest, dmax, src, slen)    (__hpr_safec_errno_t = strcpyfld_sec(dest, dmax, src, slen));\
do{\
    if(EOK != __hpr_safec_errno_t)\
    {\
        scurec_default_err_handle_cb_Judgment();\
        __hpr_safec_error_handle(__FILE__, __LINE__, __FUNCTION__, "STRCPYFLD_SEC", __hpr_safec_errno_t);\
    }\
}while(0);

#define STRCPYFLD_NATIVE_SEC(dest, dmax, src, slen)    strcpyfld_sec(dest, dmax, src, slen)

/*******************STRCPYFLDIN_SEC*******************/
#define STRCPYFLDIN_SEC(dest, dmax, src, slen)    (__hpr_safec_errno_t = strcpyfldin_sec(dest, dmax, src, slen));\
do{\
    if(EOK != __hpr_safec_errno_t)\
    {\
        scurec_default_err_handle_cb_Judgment();\
        __hpr_safec_error_handle(__FILE__, __LINE__, __FUNCTION__, "STRCPYFLDIN_SEC", __hpr_safec_errno_t);\
    }\
}while(0);

#define STRCPYFLDIN_NATIVE_SEC(dest, dmax, src, slen)    strcpyfldin_sec(dest, dmax, src, slen)

/*******************STRCPYFLDOUT_SEC*******************/
#define STRCPYFLDOUT_SEC(dest, dmax, src, slen)    (__hpr_safec_errno_t = strcpyfldout_sec(dest, dmax, src, slen));\
do{\
    if(EOK != __hpr_safec_errno_t)\
    {\
        scurec_default_err_handle_cb_Judgment();\
        __hpr_safec_error_handle(__FILE__, __LINE__, __FUNCTION__, "STRCPYFLDOUT_SEC", __hpr_safec_errno_t);\
    }\
}while(0);

#define STRCPYFLDOUT_NATIVE_SEC(dest, dmax, src, slen)    strcpyfldout_sec(dest, dmax, src, slen)

/*******************STRCSPN_SEC*******************/
#define STRCSPN_SEC(dest, dmax, src, slen, count)    (__hpr_safec_errno_t = strcspn_sec(dest, dmax, src, slen, count));\
do{\
    if(EOK != __hpr_safec_errno_t)\
    {\
        scurec_default_err_handle_cb_Judgment();\
        __hpr_safec_error_handle(__FILE__, __LINE__, __FUNCTION__, "STRCSPN_SEC", __hpr_safec_errno_t);\
    }\
}while(0);

#define STRCSPN_NATIVE_SEC(dest, dmax, src, slen, count)    strcspn_sec(dest, dmax, src, slen, count)

/*******************STRFIRSTCHAR_SEC*******************/
#define STRFIRSTCHAR_SEC(dest, dmax, c, first)    (__hpr_safec_errno_t = strfirstchar_sec(dest, dmax, c, first));\
do{\
    if(EOK != __hpr_safec_errno_t)\
    {\
        scurec_default_err_handle_cb_Judgment();\
        __hpr_safec_error_handle(__FILE__, __LINE__, __FUNCTION__, "STRFIRSTCHAR_SEC", __hpr_safec_errno_t);\
    }\
}while(0);

#define STRFIRSTCHAR_NATIVE_SEC(dest, dmax, c, first)    strfirstchar_sec(dest, dmax, c, first)

/*******************STRFIRSTDIFF_SEC*******************/
#define STRFIRSTDIFF_SEC(dest, dmax, src, index)    (__hpr_safec_errno_t = strfirstdiff_sec(dest, dmax, src, index));\
do{\
    if(EOK != __hpr_safec_errno_t)\
    {\
        scurec_default_err_handle_cb_Judgment();\
        __hpr_safec_error_handle(__FILE__, __LINE__, __FUNCTION__, "STRFIRSTDIFF_SEC", __hpr_safec_errno_t);\
    }\
}while(0);

#define STRFIRSTDIFF_NATIVE_SEC(dest, dmax, src, index)    strfirstdiff_sec(dest, dmax, src, index)

/*******************STRFIRSTSAME_SEC*******************/
#define STRFIRSTSAME_SEC(dest, dmax, src, index)    (__hpr_safec_errno_t = strfirstsame_sec(dest, dmax, src, index));\
do{\
    if(EOK != __hpr_safec_errno_t)\
    {\
        scurec_default_err_handle_cb_Judgment();\
        __hpr_safec_error_handle(__FILE__, __LINE__, __FUNCTION__, "STRFIRSTSAME_SEC", __hpr_safec_errno_t);\
    }\
}while(0);

#define STRFIRSTSAME_NATIVE_SEC(dest, dmax, src, index)    strfirstsame_sec(dest, dmax, src, index)

/*******************STRISALPHANUMERIC_SEC*******************/
#define STRISALPHANUMERIC_SEC(dest, dmax, src, index)    (__hpr_safec_errno_t = strisalphanumeric_sec(dest, dmax, src, index));\
do{\
    if(true != __hpr_safec_errno_t)\
    {\
        scurec_default_err_handle_cb_Judgment();\
        __hpr_safec_error_handle(__FILE__, __LINE__, __FUNCTION__, "STRISALPHANUMERIC_SEC", __hpr_safec_errno_t);\
    }\
}while(0);

#define STRISALPHANUMERIC_NATIVE_SEC(dest, dmax, src, index)    strisalphanumeric_sec(dest, dmax, src, index)

/*******************STRISASCII_SEC*******************/
#define STRISASCII_SEC(dest, dmax)    (__hpr_safec_errno_t = strisascii_sec(dest, dmax));\
do{\
    if(true != __hpr_safec_errno_t)\
    {\
        scurec_default_err_handle_cb_Judgment();\
        __hpr_safec_error_handle(__FILE__, __LINE__, __FUNCTION__, "STRISASCII_SEC", __hpr_safec_errno_t);\
    }\
}while(0);

#define STRISASCII_NATIVE_SEC(dest, dmax)    strisascii_sec(dest, dmax)

/*******************STRISDIGIT_SEC*******************/
#define STRISDIGIT_SEC(dest, dmax)    (__hpr_safec_errno_t = strisdigit_sec(dest, dmax));\
do{\
    if(true != __hpr_safec_errno_t)\
    {\
        scurec_default_err_handle_cb_Judgment();\
        __hpr_safec_error_handle(__FILE__, __LINE__, __FUNCTION__, "STRISDIGIT_SEC", __hpr_safec_errno_t);\
    }\
}while(0);

#define STRISDIGIT_NATIVE_SEC(dest, dmax)    strisdigit_sec(dest, dmax)

/*******************STRISHEX_SEC*******************/
#define STRISHEX_SEC(dest, dmax)    (__hpr_safec_errno_t = strishex_sec(dest, dmax));\
do{\
    if(true != __hpr_safec_errno_t)\
    {\
        scurec_default_err_handle_cb_Judgment();\
        __hpr_safec_error_handle(__FILE__, __LINE__, __FUNCTION__, "STRISHEX_SEC", __hpr_safec_errno_t);\
    }\
}while(0);

#define STRISHEX_NATIVE_SEC(dest, dmax)    strishex_sec(dest, dmax)

/*******************STRISLOWERCASE_SEC*******************/
#define STRISLOWERCASE_SEC(dest, dmax)    (__hpr_safec_errno_t = strislowercase_sec(dest, dmax));\
do{\
    if(true != __hpr_safec_errno_t)\
    {\
        scurec_default_err_handle_cb_Judgment();\
        __hpr_safec_error_handle(__FILE__, __LINE__, __FUNCTION__, "STRISLOWERCASE_SEC", __hpr_safec_errno_t);\
    }\
}while(0);

#define STRISLOWERCASE_NATIVE_SEC(dest, dmax)    strislowercase_sec(dest, dmax)

/*******************STRISMIXEDCASE_SEC*******************/
#define STRISMIXEDCASE_SEC(dest, dmax)    (__hpr_safec_errno_t = strismixedcase_sec(dest, dmax));\
do{\
    if(true != __hpr_safec_errno_t)\
    {\
        scurec_default_err_handle_cb_Judgment();\
        __hpr_safec_error_handle(__FILE__, __LINE__, __FUNCTION__, "STRISMIXEDCASE_SEC", __hpr_safec_errno_t);\
    }\
}while(0);

#define STRISMIXEDCASE_NATIVE_SEC(dest, dmax)    strismixedcase_sec(dest, dmax)

/*******************STRISPASSWORD_SEC*******************/
#define STRISPASSWORD_SEC(dest, dmax)    (__hpr_safec_errno_t = strispassword_sec(dest, dmax));\
do{\
    if(true != __hpr_safec_errno_t)\
    {\
        scurec_default_err_handle_cb_Judgment();\
        __hpr_safec_error_handle(__FILE__, __LINE__, __FUNCTION__, "STRISPASSWORD_SEC", __hpr_safec_errno_t);\
    }\
}while(0);

#define STRISPASSWORD_NATIVE_SEC(dest, dmax)    strispassword_sec(dest, dmax)

/*******************STRISUPPERCASE_SEC*******************/
#define STRISUPPERCASE_SEC(dest, dmax)    (__hpr_safec_errno_t = strisuppercase_sec(dest, dmax));\
do{\
    if(true != __hpr_safec_errno_t)\
    {\
        scurec_default_err_handle_cb_Judgment();\
        __hpr_safec_error_handle(__FILE__, __LINE__, __FUNCTION__, "STRISUPPERCASE_SEC", __hpr_safec_errno_t);\
    }\
}while(0);

#define STRISUPPERCASE_NATIVE_SEC(dest, dmax)    strisuppercase_sec(dest, dmax)

/*******************STRLASTCHAR_SEC*******************/
#define STRLASTCHAR_SEC(dest, dmax, c, last)    (__hpr_safec_errno_t = strlastchar_sec(dest, dmax, c, last));\
do{\
    if(EOK != __hpr_safec_errno_t)\
    {\
        scurec_default_err_handle_cb_Judgment();\
        __hpr_safec_error_handle(__FILE__, __LINE__, __FUNCTION__, "STRLASTCHAR_SEC", __hpr_safec_errno_t);\
    }\
}while(0);

#define STRLASTCHAR_NATIVE_SEC(dest, dmax, c, last)    strlastchar_sec(dest, dmax, c, last)

/*******************STRLASTDIFF_SEC*******************/
#define STRLASTDIFF_SEC(dest, dmax, src, index)    (__hpr_safec_errno_t = strlastdiff_sec(dest, dmax, src, index));\
do{\
    if(EOK != __hpr_safec_errno_t)\
    {\
        scurec_default_err_handle_cb_Judgment();\
        __hpr_safec_error_handle(__FILE__, __LINE__, __FUNCTION__, "STRLASTDIFF_SEC", __hpr_safec_errno_t);\
    }\
}while(0);

#define STRLASTDIFF_NATIVE_SEC(dest, dmax, src, index)    strlastdiff_sec(dest, dmax, src, index)

/*******************STRLASTSAME_SEC*******************/
#define STRLASTSAME_SEC(dest, dmax, src, index)    (__hpr_safec_errno_t = strlastsame_sec(dest, dmax, src, index));\
do{\
    if(EOK != __hpr_safec_errno_t)\
    {\
        scurec_default_err_handle_cb_Judgment();\
        __hpr_safec_error_handle(__FILE__, __LINE__, __FUNCTION__, "STRLASTSAME_SEC", __hpr_safec_errno_t);\
    }\
}while(0);

#define STRLASTSAME_NATIVE_SEC(dest, dmax, src, index)    strlastsame_sec(dest, dmax, src, index)

/*******************STRLJUSTIFY_SEC*******************/
#define STRLJUSTIFY_SEC(dest, dmax)    (__hpr_safec_errno_t = strljustify_sec(dest, dmax));\
do{\
    if(EOK != __hpr_safec_errno_t)\
    {\
        scurec_default_err_handle_cb_Judgment();\
        __hpr_safec_error_handle(__FILE__, __LINE__, __FUNCTION__, "STRLJUSTIFY_SEC", __hpr_safec_errno_t);\
    }\
}while(0);

#define STRLJUSTIFY_NATIVE_SEC(dest, dmax)    strljustify_sec(dest, dmax)

/*******************STRNLEN_SEC*******************/
#define STRNLEN_SEC(dest, dmax)    (__hpr_safec_errno_t = strnlen_sec(dest, dmax));\
do{\
    if(0 == __hpr_safec_errno_t)\
    {\
        scurec_default_err_handle_cb_Judgment();\
        __hpr_safec_error_handle(__FILE__, __LINE__, __FUNCTION__, "STRNLEN_SEC", __hpr_safec_errno_t);\
    }\
}while(0);

#define STRNLEN_NATIVE_SEC(dest, dmax)    strnlen_sec(dest, dmax)

/*******************STRNTERMINATE_SEC*******************/
#define STRNTERMINATE_SEC(dest, dmax)    (__hpr_safec_errno_t = strnterminate_sec(dest, dmax));\
do{\
    if(0 == __hpr_safec_errno_t)\
    {\
        scurec_default_err_handle_cb_Judgment();\
        __hpr_safec_error_handle(__FILE__, __LINE__, __FUNCTION__, "STRNTERMINATE_SEC", __hpr_safec_errno_t);\
    }\
}while(0);

#define STRNTERMINATE_NATIVE_SEC(dest, dmax)    strnterminate_sec(dest, dmax)

/*******************STRPBRK_SEC*******************/
#define STRPBRK_SEC(dest, dmax, src, slen, first)    (__hpr_safec_errno_t = strpbrk_sec(dest, dmax, src, slen, first));\
do{\
    if(EOK != __hpr_safec_errno_t)\
    {\
        scurec_default_err_handle_cb_Judgment();\
        __hpr_safec_error_handle(__FILE__, __LINE__, __FUNCTION__, "STRPBRK_SEC", __hpr_safec_errno_t);\
    }\
}while(0);

#define STRPBRK_NATIVE_SEC(dest, dmax, src, slen, first)    strpbrk_sec(dest, dmax, src, slen, first)

/*******************STRPREFIX_SEC*******************/
#define STRPREFIX_SEC(dest, dmax, src)    (__hpr_safec_errno_t = strprefix_sec(dest, dmax, src));\
do{\
    if(EOK != __hpr_safec_errno_t)\
    {\
        scurec_default_err_handle_cb_Judgment();\
        __hpr_safec_error_handle(__FILE__, __LINE__, __FUNCTION__, "STRPREFIX_SEC", __hpr_safec_errno_t);\
    }\
}while(0);

#define STRPREFIX_NATIVE_SEC(dest, dmax, src)    strprefix_sec(dest, dmax, src)

/*******************STRREMOVEWS_SEC*******************/
#define STRREMOVEWS_SEC(dest, dmax)    (__hpr_safec_errno_t = strremovews_sec(dest, dmax));\
do{\
    if(EOK != __hpr_safec_errno_t)\
    {\
        scurec_default_err_handle_cb_Judgment();\
        __hpr_safec_error_handle(__FILE__, __LINE__, __FUNCTION__, "STRREMOVEWS_SEC", __hpr_safec_errno_t);\
    }\
}while(0);

#define STRREMOVEWS_NATIVE_SEC(dest, dmax)    strremovews_sec(dest, dmax)

/*******************STRSPN_SEC*******************/
#define STRSPN_SEC(dest, dmax, src, slen, count)    (__hpr_safec_errno_t = strspn_sec(dest, dmax, src, slen, count));\
do{\
    if(EOK != __hpr_safec_errno_t)\
    {\
        scurec_default_err_handle_cb_Judgment();\
        __hpr_safec_error_handle(__FILE__, __LINE__, __FUNCTION__, "STRSPN_SEC", __hpr_safec_errno_t);\
    }\
}while(0);

#define STRSPN_NATIVE_SEC(dest, dmax, src, slen, count)    strspn_sec(dest, dmax, src, slen, count)

/*******************STRSTR_SEC*******************/
#define STRSTR_SEC(dest, dmax, src, slen, substring)    (__hpr_safec_errno_t = strstr_sec(dest, dmax, src, slen, substring));\
do{\
    if(EOK != __hpr_safec_errno_t)\
    {\
        scurec_default_err_handle_cb_Judgment();\
        __hpr_safec_error_handle(__FILE__, __LINE__, __FUNCTION__, "STRSTR_SEC", __hpr_safec_errno_t);\
    }\
}while(0);

#define STRSTR_NATIVE_SEC(dest, dmax, src, slen, substring)    strstr_sec(dest, dmax, src, slen, substring)

/*******************STRTOLOWERCASE_SEC*******************/
#define STRTOLOWERCASE_SEC(dest, dmax)    (__hpr_safec_errno_t = strtolowercase_sec(dest, dmax));\
do{\
    if(EOK != __hpr_safec_errno_t)\
    {\
        scurec_default_err_handle_cb_Judgment();\
        __hpr_safec_error_handle(__FILE__, __LINE__, __FUNCTION__, "STRTOLOWERCASE_SEC", __hpr_safec_errno_t);\
    }\
}while(0);

#define STRTOLOWERCASE_NATIVE_SEC(dest, dmax)    strtolowercase_sec(dest, dmax)

/*******************STRTOUPPERCASE_SEC*******************/
#define STRTOUPPERCASE_SEC(dest, dmax)    (__hpr_safec_errno_t = strtouppercase_sec(dest, dmax));\
do{\
    if(EOK != __hpr_safec_errno_t)\
    {\
        scurec_default_err_handle_cb_Judgment();\
        __hpr_safec_error_handle(__FILE__, __LINE__, __FUNCTION__, "STRTOUPPERCASE_SEC", __hpr_safec_errno_t);\
    }\
}while(0);

#define STRTOUPPERCASE_NATIVE_SEC(dest, dmax)    strtouppercase_sec(dest, dmax)

/*******************STRZERO_SEC*******************/
#define STRZERO_SEC(dest, dmax)    (__hpr_safec_errno_t = strzero_sec(dest, dmax));\
do{\
    if(EOK != __hpr_safec_errno_t)\
    {\
        scurec_default_err_handle_cb_Judgment();\
        __hpr_safec_error_handle(__FILE__, __LINE__, __FUNCTION__, "STRZERO_SEC", __hpr_safec_errno_t);\
    }\
}while(0);

#define STRZERO_NATIVE_SEC(dest, dmax)    strzero_sec(dest, dmax)

#define SECUREC_ERRHANDLE errorhandle
/*----------------------------------------------*
 * Type Definition                              *
 *----------------------------------------------*/

/*----------------------------------------------*
 * Function Header                              *
 *----------------------------------------------*/
 

/*
 * Description: Used to set the output interface of the error message when the security function error returns, 
 * each business department set their own implementation
 * Parameter: none
 * Return:    void
 */
void scurec_set_err_handle_cb(SECUREC_ERRHANDLE errhandle);

/*
 * Description: If no callback function is set, the default callback is used
 * Parameter: none
 * Return:    void
 */
void scurec_default_err_handle_cb_Judgment(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif //_HIK_SAFE_MACRO_H_

