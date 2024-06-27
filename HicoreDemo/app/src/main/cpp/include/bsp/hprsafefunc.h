/*
 * hprsafefunc.h是hikvision 基于hw boundcheck 安全函数库封装的适合hikvision使用的安全函数库
 * 当前版本号V1.0.0，初始创建版本，后续版本迭代记录在此增加说明
 *
 * V1.0.0 --初始版本,创建日期 2022-09-20
 */
 
#ifndef __HPR_SAFE_FUNC_H__
#define __HPR_SAFE_FUNC_H__

#include "hprsecurec.h"

#ifdef __cplusplus
extern "C" {
#endif

__attribute__((unused))  extern __thread int __hpr_safec_errno_t;
__attribute__((unused))  extern __thread char* __hpr_safec_str_t;
__attribute__((unused))  extern __thread wchar_t* __hpr_safec_str_wchar_t;

extern void __hpr_safec_error_handle(const char *filename, const int line, const char *function, const char *safefunc, int err);

/*用于设置安全函数错误返回时错误信息的输出接口,各业务部自行设置实现*/
void set_err_handle_cb(errorhandle errhandle);

/*******************HPR_MEMSET_S*******************/
#define HPR_MEMSET_S(dest, destMax, c, count)    (__hpr_safec_errno_t = HPR_Memset_s(dest, destMax, c, count));\
do{\
	if(EOK != __hpr_safec_errno_t)\
	{\
		__hpr_safec_error_handle(__FILE__, __LINE__, __FUNCTION__, "HPR_MEMSET_S", __hpr_safec_errno_t);\
	}\
}while(0);

#define HPR_MEMSET_NATIVE_S(dest, destMax, c, count)    HPR_Memset_s(dest, destMax, c, count)

/*******************HPR_MEMMOVE_S*******************/
#define HPR_MEMMOVE_S(dest, destMax, src, count)    (__hpr_safec_errno_t = HPR_Memmove_s(dest, destMax, src, count));\
do{\
	if(EOK != __hpr_safec_errno_t)\
	{\
		__hpr_safec_error_handle(__FILE__, __LINE__, __FUNCTION__, "HPR_MEMMOVE_S", __hpr_safec_errno_t);\
	}\
}while(0);

#define HPR_MEMMOVE_NATIVE_S(dest, destMax, src, count)    HPR_Memmove_s(dest, destMax, src, count)

/*******************HPR_MEMCPY_S*******************/
#define HPR_MEMCPY_S(dest, destMax, src, count)    (__hpr_safec_errno_t = HPR_Memcpy_s(dest, destMax, src, count));\
do{\
	if(EOK != __hpr_safec_errno_t)\
	{\
		__hpr_safec_error_handle(__FILE__, __LINE__, __FUNCTION__, "HPR_MEMCPY_S", __hpr_safec_errno_t);\
	}\
}while(0);

#define HPR_MEMCPY_NATIVE_S(dest, destMax, src, count)    HPR_Memcpy_s(dest, destMax, src, count)

/*******************HPR_STRCPY_S*******************/
#define HPR_STRCPY_S(strDest, destMax, strSrc)    (__hpr_safec_errno_t = HPR_Strcpy_s(strDest, destMax, strSrc));\
do{\
	if(EOK != __hpr_safec_errno_t)\
	{\
		__hpr_safec_error_handle(__FILE__, __LINE__, __FUNCTION__, "HPR_STRCPY_S", __hpr_safec_errno_t);\
	}\
}while(0);

#define HPR_STRCPY_NATIVE_S(strDest, destMax, strSrc)    HPR_Strcpy_s(strDest, destMax, strSrc)

/*******************HPR_STRNCPY_S*******************/
#define HPR_STRNCPY_S(strDest, destMax, strSrc, count)    (__hpr_safec_errno_t = HPR_Strncpy_s(strDest, destMax, strSrc, count));\
do{\
	if(EOK != __hpr_safec_errno_t)\
	{\
		__hpr_safec_error_handle(__FILE__, __LINE__, __FUNCTION__, "HPR_STRNCPY_S", __hpr_safec_errno_t);\
	}\
}while(0);

#define HPR_STRNCPY_NATIVE_S(strDest, destMax, strSrc, count)    HPR_Strncpy_s(strDest, destMax, strSrc, count)

/*******************HPR_STRCAT_S*******************/
#define HPR_STRCAT_S(strDest, destMax, strSrc)    (__hpr_safec_errno_t = HPR_Strcat_s(strDest, destMax, strSrc));\
do{\
	if(EOK != __hpr_safec_errno_t)\
	{\
		__hpr_safec_error_handle(__FILE__, __LINE__, __FUNCTION__, "HPR_STRCAT_S", __hpr_safec_errno_t);\
	}\
}while(0);

#define HPR_STRCAT_NATIVE_S(strDest, destMax, strSrc)    HPR_Strcat_s(strDest, destMax, strSrc)

/*******************HPR_STRNCAT_S*******************/
#define HPR_STRNCAT_S(strDest, destMax, strSrc, count)    (__hpr_safec_errno_t = HPR_Strncat_s(strDest, destMax, strSrc, count));\
do{\
	if(EOK != __hpr_safec_errno_t)\
	{\
		__hpr_safec_error_handle(__FILE__, __LINE__, __FUNCTION__, "HPR_STRNCAT_S", __hpr_safec_errno_t);\
	}\
}while(0);

#define HPR_STRNCAT_NATIVE_S(strDest, destMax, strSrc, count)    HPR_Strncat_s(strDest, destMax, strSrc, count)

/*******************HPR_VSPRINTF_S*******************/
#define HPR_VSPRINTF_S(strDest, destMax, format, ...)    (__hpr_safec_errno_t = HPR_Vsprintf_s(strDest, destMax, format, ##__VA_ARGS__));\
do{\
	if(0 > __hpr_safec_errno_t)\
	{\
		__hpr_safec_error_handle(__FILE__, __LINE__, __FUNCTION__, "HPR_VSPRINTF_S", __hpr_safec_errno_t);\
	}\
}while(0);

#define HPR_VSPRINTF_NATIVE_S(strDest, destMax, format, ...)    HPR_Vsprintf_s(strDest, destMax, format, ##__VA_ARGS__)

/*******************HPR_SPRINTF_S*******************/
#define HPR_SPRINTF_S(strDest, destMax, format, ...)    (__hpr_safec_errno_t = HPR_Sprintf_s(strDest, destMax, format, ##__VA_ARGS__));\
do{\
	if(0 > __hpr_safec_errno_t)\
	{\
		__hpr_safec_error_handle(__FILE__, __LINE__, __FUNCTION__, "HPR_SPRINTF_S", __hpr_safec_errno_t);\
	}\
}while(0);

#define HPR_SPRINTF_NATIVE_S(strDest, destMax, format, ...)    HPR_Sprintf_s(strDest, destMax, format, ##__VA_ARGS__)

/*******************HPR_VSNPRINTF_S*******************/
#define HPR_VSNPRINTF_S(strDest, destMax, count, format, ...)    (__hpr_safec_errno_t = HPR_Vsnprintf_s(strDest, destMax, count, format, ##__VA_ARGS__));\
do{\
	if(0 > __hpr_safec_errno_t)\
	{\
		__hpr_safec_error_handle(__FILE__, __LINE__, __FUNCTION__, "HPR_VSNPRINTF_S", __hpr_safec_errno_t);\
	}\
}while(0);

#define HPR_VSNPRINTF_NATIVE_S(strDest, destMax, count, format, ...)    HPR_Vsnprintf_s(strDest, destMax, count, format, ##__VA_ARGS__)

/*******************HPR_SNPRINTF_S*******************/
#define HPR_SNPRINTF_S(strDest, destMax, count, format, ...)    (__hpr_safec_errno_t = HPR_Snprintf_s(strDest, destMax, count, format, ##__VA_ARGS__));\
do{\
	if(0 > __hpr_safec_errno_t)\
	{\
		__hpr_safec_error_handle(__FILE__, __LINE__, __FUNCTION__, "HPR_SNPRINTF_S", __hpr_safec_errno_t);\
	}\
}while(0);

#define HPR_SNPRINTF_NATIVE_S(strDest, destMax, count, format, ...)    HPR_Snprintf_s(strDest, destMax, count, format, ##__VA_ARGS__)

/*******************HPR_SCANF_S*******************/
#define HPR_SCANF_S(format, ...)    (__hpr_safec_errno_t = HPR_Scanf_s(format, ##__VA_ARGS__));\
do{\
	if(0 > __hpr_safec_errno_t)\
	{\
		__hpr_safec_error_handle(__FILE__, __LINE__, __FUNCTION__, "HPR_SCANF_S", __hpr_safec_errno_t);\
	}\
}while(0);

#define HPR_SCANF_NATIVE_S(format, ...)    HPR_Scanf_s(format, ##__VA_ARGS__)

/*******************HPR_VSCANF_S*******************/
#define HPR_VSCANF_S(format, ...)    (__hpr_safec_errno_t = HPR_Vscanf_s(format, ##__VA_ARGS__));\
do{\
	if(0 > __hpr_safec_errno_t)\
	{\
		__hpr_safec_error_handle(__FILE__, __LINE__, __FUNCTION__, "HPR_VSCANF_S", __hpr_safec_errno_t);\
	}\
}while(0);

#define HPR_VSCANF_NATIVE_S(format, ...)    HPR_Vscanf_s(format, ##__VA_ARGS__)

/*******************HPR_SSCANF_S*******************/
#define HPR_SSCANF_S(buffer, format, ...)    (__hpr_safec_errno_t = HPR_Sscanf_s(buffer, format, ##__VA_ARGS__));\
do{\
	if(0 > __hpr_safec_errno_t)\
	{\
		__hpr_safec_error_handle(__FILE__, __LINE__, __FUNCTION__, "HPR_SSCANF_S", __hpr_safec_errno_t);\
	}\
}while(0);

#define HPR_SSCANF_NATIVE_S(buffer, format, ...)    HPR_Sscanf_s(buffer, format, ##__VA_ARGS__)

/*******************HPR_VSSCANF_S*******************/
#define HPR_VSSCANF_S(buffer, format, ...)    (__hpr_safec_errno_t = HPR_Vsscanf_s(buffer, format, ##__VA_ARGS__));\
do{\
	if(0 > __hpr_safec_errno_t)\
	{\
		__hpr_safec_error_handle(__FILE__, __LINE__, __FUNCTION__, "HPR_VSSCANF_S", __hpr_safec_errno_t);\
	}\
}while(0);

#define HPR_VSSCANF_NATIVE_S(buffer, format, ...)    HPR_Vsscanf_s(buffer, format, ##__VA_ARGS__)

/*******************HPR_FSCANF_S*******************/
#define HPR_FSCANF_S(stream, format, ...)    (__hpr_safec_errno_t = HPR_Fscanf_s(stream, format, ##__VA_ARGS__));\
do{\
	if(0 > __hpr_safec_errno_t)\
	{\
		__hpr_safec_error_handle(__FILE__, __LINE__, __FUNCTION__, "HPR_FSCANF_S", __hpr_safec_errno_t);\
	}\
}while(0);

#define HPR_FSCANF_NATIVE_S(stream, format, ...)    HPR_Fscanf_s(stream, format, ##__VA_ARGS__)

/*******************HPR_VFSCANF_S*******************/
#define HPR_VFSCANF_S(stream, format, ...)    (__hpr_safec_errno_t = HPR_Vfscanf_s(stream, format, ##__VA_ARGS__));\
do{\
	if(0 > __hpr_safec_errno_t)\
	{\
		__hpr_safec_error_handle(__FILE__, __LINE__, __FUNCTION__, "HPR_VFSCANF_S", __hpr_safec_errno_t);\
	}\
}while(0);

#define HPR_VFSCANF_NATIVE_S(stream, format, ...)    HPR_Vfscanf_s(stream, format, ##__VA_ARGS__)

/*******************HPR_STRTOK_S*******************/
#define HPR_STRTOK_S(strToken, strDelimit, context)    (__hpr_safec_str_t = HPR_Strtok_s(strToken, strDelimit, context));\
do{\
	if(NULL == __hpr_safec_str_t)\
	{\
		__hpr_safec_error_handle(__FILE__, __LINE__, __FUNCTION__, "HPR_STRTOK_S", 0);\
	}\
}while(0);

#define HPR_STRTOK_NATIVE_S(strToken, strDelimit, context)    HPR_Strtok_s(strToken, strDelimit, context)

/*******************HPR_GETS_S*******************/
#define HPR_GETS_S(buffer, destMax)    (__hpr_safec_str_t = HPR_Gets_s(buffer, destMax));\
do{\
	if(NULL == __hpr_safec_str_t)\
	{\
		__hpr_safec_error_handle(__FILE__, __LINE__, __FUNCTION__, "HPR_GETS_S", 0);\
	}\
}while(0);

#define HPR_GETS_NATIVE_S(buffer, destMax)    HPR_Gets_s(buffer, destMax)

/*******************HPR_WMEMCPY_S*******************/
#define HPR_WMEMCPY_S(dest, destMax, src, count)    (__hpr_safec_errno_t = HPR_Wmemcpy_s(dest, destMax, src, count));\
do{\
	if(EOK != __hpr_safec_errno_t)\
	{\
		__hpr_safec_error_handle(__FILE__, __LINE__, __FUNCTION__, "HPR_WMEMCPY_S", __hpr_safec_errno_t);\
	}\
}while(0);

#define HPR_WMEMCPY_NATIVE_S(dest, destMax, src, count)    HPR_Wmemcpy_s(dest, destMax, src, count)

/*******************HPR_WMEMMOVE_S*******************/
#define HPR_WMEMMOVE_S(dest, destMax, src, count)    (__hpr_safec_errno_t = HPR_Wmemmove_s(dest, destMax, src, count));\
do{\
	if(EOK != __hpr_safec_errno_t)\
	{\
		__hpr_safec_error_handle(__FILE__, __LINE__, __FUNCTION__, "HPR_WMEMMOVE_S", __hpr_safec_errno_t);\
	}\
}while(0);

#define HPR_WMEMMOVE_NATIVE_S(dest, destMax, src, count)    HPR_Wmemmove_s(dest, destMax, src, count)

/*******************HPR_WCSCPY_S*******************/
#define HPR_WCSCPY_S(strDest, destMax, strSrc)    (__hpr_safec_errno_t = HPR_Wcscpy_s(strDest, destMax, strSrc));\
do{\
	if(EOK != __hpr_safec_errno_t)\
	{\
		__hpr_safec_error_handle(__FILE__, __LINE__, __FUNCTION__, "HPR_WCSCPY_S", __hpr_safec_errno_t);\
	}\
}while(0);

#define HPR_WCSCPY_NATIVE_S(strDest, destMax, strSrc)    HPR_Wcscpy_s(strDest, destMax, strSrc)

/*******************HPR_WCSNCPY_S*******************/
#define HPR_WCSNCPY_S(strDest, destMax, strSrc, count)    (__hpr_safec_errno_t = HPR_Wcsncpy_s(strDest, destMax, strSrc, count));\
do{\
	if(EOK != __hpr_safec_errno_t)\
	{\
		__hpr_safec_error_handle(__FILE__, __LINE__, __FUNCTION__, "HPR_WCSNCPY_S", __hpr_safec_errno_t);\
	}\
}while(0);

#define HPR_WCSNCPY_NATIVE_S(strDest, destMax, strSrc, count)    HPR_Wcsncpy_s(strDest, destMax, strSrc, count)

/*******************HPR_WCSCAT_S*******************/
#define HPR_WCSCAT_S(strDest, destMax, strSrc)    (__hpr_safec_errno_t = HPR_Wcscat_s(strDest, destMax, strSrc));\
do{\
	if(EOK != __hpr_safec_errno_t)\
	{\
		__hpr_safec_error_handle(__FILE__, __LINE__, __FUNCTION__, "HPR_WCSCAT_S", __hpr_safec_errno_t);\
	}\
}while(0);

#define HPR_WCSCAT_NATIVE_S(strDest, destMax, strSrc)    HPR_Wcscat_s(strDest, destMax, strSrc)

/*******************HPR_WCSNCAT_S*******************/
#define HPR_WCSNCAT_S(strDest, destMax, strSrc, count)    (__hpr_safec_errno_t = HPR_Wcsncat_s(strDest, destMax, strSrc, count));\
do{\
	if(EOK != __hpr_safec_errno_t)\
	{\
		__hpr_safec_error_handle(__FILE__, __LINE__, __FUNCTION__, "HPR_WCSNCAT_S", __hpr_safec_errno_t);\
	}\
}while(0);

#define HPR_WCSNCAT_NATIVE_S(strDest, destMax, strSrc, count)    HPR_Wcsncat_s(strDest, destMax, strSrc, count)

/*******************HPR_WCSTOK_S*******************/
#define HPR_WCSTOK_S(strToken, strDelimit, context)    (__hpr_safec_str_wchar_t = HPR_Wcstok_s(strToken, strDelimit, context));\
do{\
	if(NULL == __hpr_safec_str_wchar_t)\
	{\
		__hpr_safec_error_handle(__FILE__, __LINE__, __FUNCTION__, "HPR_WCSTOK_S", 0);\
	}\
}while(0);

#define HPR_WCSTOK_NATIVE_S(strToken, strDelimit, context)    HPR_Wcstok_s(strToken, strDelimit, context)

/*******************HPR_VSWPRINTF_S*******************/
#define HPR_VSWPRINTF_S(strDest, destMax, format, ...)    (__hpr_safec_errno_t = HPR_Vswprintf_s(strDest, destMax, format, ##__VA_ARGS__));\
do{\
	if(0 > __hpr_safec_errno_t)\
	{\
		__hpr_safec_error_handle(__FILE__, __LINE__, __FUNCTION__, "HPR_VSWPRINTF_S", __hpr_safec_errno_t);\
	}\
}while(0);

#define HPR_VSWPRINTF_NATIVE_S(strDest, destMax, format, ...)    HPR_Vswprintf_s(strDest, destMax, format, ##__VA_ARGS__)

/*******************HPR_SWPRINTF_S*******************/
#define HPR_SWPRINTF_S(strDest, destMax, format, ...)    (__hpr_safec_errno_t = HPR_Swprintf_s(strDest, destMax, format, ##__VA_ARGS__));\
do{\
	if(0 > __hpr_safec_errno_t)\
	{\
		__hpr_safec_error_handle(__FILE__, __LINE__, __FUNCTION__, "HPR_SWPRINTF_S", __hpr_safec_errno_t);\
	}\
}while(0);

#define HPR_SWPRINTF_NATIVE_S(strDest, destMax, format, ...)    HPR_Swprintf_s(strDest, destMax, format, ##__VA_ARGS__)

/*******************HPR_FWSCANF_S*******************/
#define HPR_FWSCANF_S(stream, format, ...)    (__hpr_safec_errno_t = HPR_Fwscanf_s(stream, format, ##__VA_ARGS__));\
do{\
	if(0 > __hpr_safec_errno_t)\
	{\
		__hpr_safec_error_handle(__FILE__, __LINE__, __FUNCTION__, "HPR_FWSCANF_S", __hpr_safec_errno_t);\
	}\
}while(0);

#define HPR_FWSCANF_NATIVE_S(stream, format, ...)    HPR_Fwscanf_s(stream, format, ##__VA_ARGS__)

/*******************HPR_VFWSCANF_S*******************/
#define HPR_VFWSCANF_S(stream, format, ...)    (__hpr_safec_errno_t = HPR_Vfwscanf_s(stream, format, ##__VA_ARGS__));\
do{\
	if(0 > __hpr_safec_errno_t)\
	{\
		__hpr_safec_error_handle(__FILE__, __LINE__, __FUNCTION__, "HPR_VFWSCANF_S", __hpr_safec_errno_t);\
	}\
}while(0);

#define HPR_VFWSCANF_NATIVE_S(stream, format, ...)    HPR_Vfwscanf_s(stream, format, ##__VA_ARGS__)

/*******************HPR_WSCANF_S*******************/
#define HPR_WSCANF_S(format, ...)    (__hpr_safec_errno_t = HPR_Wscanf_s(format, ##__VA_ARGS__));\
do{\
	if(0 > __hpr_safec_errno_t)\
	{\
		__hpr_safec_error_handle(__FILE__, __LINE__, __FUNCTION__, "HPR_WSCANF_S", __hpr_safec_errno_t);\
	}\
}while(0);

#define HPR_WSCANF_NATIVE_S(format, ...)    HPR_Wscanf_s(format, ##__VA_ARGS__)

/*******************HPR_VWSCANF_S*******************/
#define HPR_VWSCANF_S(format, ...)    (__hpr_safec_errno_t = HPR_Vwscanf_s(format, ##__VA_ARGS__));\
do{\
	if(0 > __hpr_safec_errno_t)\
	{\
		__hpr_safec_error_handle(__FILE__, __LINE__, __FUNCTION__, "HPR_VWSCANF_S", __hpr_safec_errno_t);\
	}\
}while(0);

#define HPR_VWSCANF_NATIVE_S(format, ...)    HPR_Vwscanf_s(format, ##__VA_ARGS__)

/*******************HPR_SWSCANF_S*******************/
#define HPR_SWSCANF_S(buffer, format, ...)    (__hpr_safec_errno_t = HPR_Swscanf_s(buffer, format, ##__VA_ARGS__));\
do{\
	if(0 > __hpr_safec_errno_t)\
	{\
		__hpr_safec_error_handle(__FILE__, __LINE__, __FUNCTION__, "HPR_SWSCANF_S", __hpr_safec_errno_t);\
	}\
}while(0);

#define HPR_SWSCANF_NATIVE_S(buffer, format, ...)    HPR_Swscanf_s(buffer, format, ##__VA_ARGS__)

/*******************HPR_VSWSCANF_S*******************/
#define HPR_VSWSCANF_S(buffer, format, ...)    (__hpr_safec_errno_t = HPR_Vswscanf_s(buffer, format, ##__VA_ARGS__));\
do{\
	if(0 > __hpr_safec_errno_t)\
	{\
		__hpr_safec_error_handle(__FILE__, __LINE__, __FUNCTION__, "HPR_VSWSCANF_S", __hpr_safec_errno_t);\
	}\
}while(0);

#define HPR_VSWSCANF_NATIVE_S(buffer, format, ...)    HPR_Vswscanf_s(buffer, format, ##__VA_ARGS__)


#ifdef __cplusplus
}
#endif

#endif /*__HPR_SAFE_FUNC_H__*/

