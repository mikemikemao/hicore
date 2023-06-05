/******************************************************************************
  @note HangZhou Hikvision Digital Technology Co., Ltd. All Right Reserved.
 ******************************************************************************
  @file     : variable_info.h
  @brief    : 变量信息头文件
  @warning  :
  @history  : <data>        <author>       <note>
			  2020-11-13    geruiyi       Create the file

******************************************************************************/

#ifndef _VARIABLE_INFO_H_
#define _VARIABLE_INFO_H_

/*----------------------------------------------*
 * Included Header                              *
 *----------------------------------------------*/
#ifdef __cplusplus
extern "C" {
#endif

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

/*----------------------------------------------*
 * Macros                                       *
 *----------------------------------------------*/
#ifndef NULL
#define NULL ((void *)0)
#endif

typedef int VAR_TYPE_E;
#define VART_UNKNOW		(0x00)//
/*     VARC_INTEGER and VARC_FLOAT 	*/
#define VART_CHAR		(0x10)// char
#define VART_SCHAR		(0x11)// signed char
#define VART_UCHAR		(0x12)// unsigned char
#define VART_SHORT		(0x13)// short
#define VART_USHORT		(0x14)// unsigned short
#define VART_INT		(0x15)// int
#define VART_UINT		(0x16)// unsigned int
#define VART_LONG		(0x17)// long
#define VART_ULONG		(0x18)// unsigned long
#define VART_LONGLONG	(0x19)// long long
#define VART_ULONGLONG	(0x1a)// unsigned long long
#define VART_FLOAT		(0x1b)// float
#define VART_DOUBLE		(0x1c)// double
/* 			VARC_POINT				*/
#define VART_CHARP		(0x30)// char *
#define VART_SCHARP		(0x31)// signed char *
#define VART_UCHARP		(0x32)// unsigned char *
#define VART_SHORTP		(0x33)// short *
#define VART_USHORTP	(0x34)// unsigned short *
#define VART_INTP		(0x35)// int *
#define VART_UINTP		(0x36)// unsigned int *
#define VART_LONGP		(0x37)// long *
#define VART_ULONGP		(0x38)// unsigned long *
#define VART_LONGLONGP	(0x39)// long long *
#define VART_ULONGLONGP	(0x3a)// unsigned long long *
#define VART_FLOATP		(0x3b)// float *
#define VART_DOUBLEP	(0x3c)// double *
/* 			VARC_CPOINT				*/
#define VART_CCHARP		(0x40)// const char *
#define VART_CSCHARP	(0x41)// const signed char *
#define VART_CUCHARP	(0x42)// const unsigned char *
#define VART_CSHORTP	(0x43)// const short *
#define VART_CUSHORTP	(0x44)// const unsigned short *
#define VART_CINTP		(0x45)// const int *
#define VART_CUINTP		(0x46)// const unsigned int *
#define VART_CLONGP		(0x47)// const long *
#define VART_CULONGP	(0x48)// const unsigned long *
#define VART_CLONGLONGP	(0x49)// const long long *
#define VART_CULONGLONGP (0x4a)// const unsigned long long *
#define VART_CFLOATP	(0x4b)// const float *
#define VART_CDOUBLEP	(0x4c)// const double *
/* 			VARC_ARRAY				*/
#define VART_CHARA		(0x50)// char []
#define VART_SCHARA		(0x51)// signed char []
#define VART_UCHARA		(0x52)// unsigned char []
#define VART_SHORTA		(0x53)// short []
#define VART_USHORTA	(0x54)// unsigned short []
#define VART_INTA		(0x55)// int []
#define VART_UINTA		(0x56)// unsigned int []
#define VART_LONGA		(0x57)// long []
#define VART_ULONGA		(0x58)// unsigned long []
#define VART_LONGLONGA	(0x59)// long long []
#define VART_ULONGLONGA	(0x5a)// unsigned long long []
#define VART_FLOATA		(0x5b)// float []
#define VART_DOUBLEA	(0x5c)// double []
/* 			VARC_CONST				*/
#define CONST_CHARA		(0xF0)// 字符串常量(类型同char []),如"123"

#define VART_COMPARE(x, y) 	__builtin_types_compatible_p(x, y)	// 类型比较
#define VART_CONST(x)		__builtin_constant_p(x)				// 是否是常量
#define GET_TYPE(x) ( \
		VART_COMPARE(typeof(x), char 				  ) ? VART_CHAR 		: \
		VART_COMPARE(typeof(x), signed char 	 	  ) ? VART_SCHAR 		: \
		VART_COMPARE(typeof(x), unsigned char 	 	  ) ? VART_UCHAR 		: \
		VART_COMPARE(typeof(x), short 			 	  ) ? VART_SHORT 		: \
		VART_COMPARE(typeof(x), unsigned short     	  ) ? VART_USHORT 		: \
		VART_COMPARE(typeof(x), int                	  ) ? VART_INT 			: \
		VART_COMPARE(typeof(x), unsigned int       	  ) ? VART_UINT 		: \
		VART_COMPARE(typeof(x), long               	  ) ? VART_LONG 		: \
		VART_COMPARE(typeof(x), unsigned long      	  ) ? VART_ULONG 		: \
		VART_COMPARE(typeof(x), long long          	  ) ? VART_LONGLONG 	: \
		VART_COMPARE(typeof(x), unsigned long long 	  ) ? VART_ULONGLONG	: \
		VART_COMPARE(typeof(x), float              	  ) ? VART_FLOAT 		: \
		VART_COMPARE(typeof(x), double             	  ) ? VART_DOUBLE 		: \
				\
		VART_COMPARE(typeof(x), char 				 *) ? VART_CHARP		: \
		VART_COMPARE(typeof(x), signed char 	 	 *) ? VART_SCHARP		: \
		VART_COMPARE(typeof(x), unsigned char 	 	 *) ? VART_UCHARP		: \
		VART_COMPARE(typeof(x), short 			 	 *) ? VART_SHORTP		: \
		VART_COMPARE(typeof(x), unsigned short     	 *) ? VART_USHORTP		: \
		VART_COMPARE(typeof(x), int                	 *) ? VART_INTP			: \
		VART_COMPARE(typeof(x), unsigned int       	 *) ? VART_UINTP		: \
		VART_COMPARE(typeof(x), long               	 *) ? VART_LONGP		: \
		VART_COMPARE(typeof(x), unsigned long      	 *) ? VART_ULONGP		: \
		VART_COMPARE(typeof(x), long long          	 *) ? VART_LONGLONGP	: \
		VART_COMPARE(typeof(x), unsigned long long 	 *) ? VART_ULONGLONGP	: \
		VART_COMPARE(typeof(x), float              	 *) ? VART_FLOATP		: \
		VART_COMPARE(typeof(x), double             	 *) ? VART_DOUBLEP		: \
				\
		VART_COMPARE(typeof(x), const char 			 *) ? VART_CCHARP		: \
		VART_COMPARE(typeof(x), const signed char 	 *) ? VART_CSCHARP		: \
		VART_COMPARE(typeof(x), const unsigned char  *) ? VART_CUCHARP		: \
		VART_COMPARE(typeof(x), const short 		 *) ? VART_CSHORTP		: \
		VART_COMPARE(typeof(x), const unsigned short *) ? VART_CUSHORTP		: \
		VART_COMPARE(typeof(x), const int            *) ? VART_CINTP		: \
		VART_COMPARE(typeof(x), const unsigned int   *) ? VART_CUINTP		: \
		VART_COMPARE(typeof(x), const long           *) ? VART_CLONGP		: \
		VART_COMPARE(typeof(x), const unsigned long  *) ? VART_CULONGP		: \
		VART_COMPARE(typeof(x), const long long      *) ? VART_CLONGLONGP	: \
		VART_COMPARE(typeof(x), const unsigned long long *) ? VART_CULONGLONGP	: \
		VART_COMPARE(typeof(x), const float          *) ? VART_CFLOATP		: \
		VART_COMPARE(typeof(x), const double         *) ? VART_CDOUBLEP		: \
				\
		VART_COMPARE(typeof(x), char 				[]) ? 	\
				(VART_CONST(x) ? CONST_CHARA : VART_CHARA	)	: \
		VART_COMPARE(typeof(x), signed char 	 	[]) ? VART_SCHARA		: \
		VART_COMPARE(typeof(x), unsigned char 	 	[]) ? VART_UCHARA		: \
		VART_COMPARE(typeof(x), short 			 	[]) ? VART_SHORTA		: \
		VART_COMPARE(typeof(x), unsigned short     	[]) ? VART_USHORTA		: \
		VART_COMPARE(typeof(x), int                	[]) ? VART_INTA			: \
		VART_COMPARE(typeof(x), unsigned int       	[]) ? VART_UINTA		: \
		VART_COMPARE(typeof(x), long               	[]) ? VART_LONGA		: \
		VART_COMPARE(typeof(x), unsigned long      	[]) ? VART_ULONGA		: \
		VART_COMPARE(typeof(x), long long          	[]) ? VART_LONGLONGA	: \
		VART_COMPARE(typeof(x), unsigned long long 	[]) ? VART_ULONGLONGA	: \
		VART_COMPARE(typeof(x), float              	[]) ? VART_FLOATA		: \
		VART_COMPARE(typeof(x), double             	[]) ? VART_DOUBLEA		: \
				\
		/*VART_COMPARE(typeof(x), char             *	[]) ? 100		: \*/\
		VART_UNKNOW )


#define GET_ADDR(x) ((void *)&(x))

#define VAR_INFO(x)	{GET_TYPE(x), GET_ADDR(x), sizeof(x)}

#define VAR_FTYPE(type, x) (*(type *)&(x)) // 将x的类型强转为type类型，非所有类型支持，不支持时会编译出错

/*----------------------------------------------*
 * Struct/Enum Definition                       *
 *----------------------------------------------*/

typedef int VAR_CLASSIFY_E;
#define VARC_UNKNOW		(0x00)// unknow classify
#define VARC_INTEGER	(0x01)// char,short,int,long,long long
#define VARC_FLOAT		(0x02)// float,double
#define VARC_POINT		(0x03)// char * ...
#define VARC_ARRAY		(0x04)// char [] ...
#define VARC_CPOINT		(0x05)// const char * ...
#define VARC_CONST		(0x06)// 常量

/* 打印调试信息级别 */
typedef int VAR_DBG_NOTE_E;
#define VAR_DBG_NOTE_NONE		(0)	// 不打印任何信息
#define VAR_DBG_NOTE_ERR		(1)	// 仅打印错误信息(执行失败有打印信息)
//#define VAR_DBG_NOTE_INFO		(2) // 打印错误和执行信息(有执行失败、执行结果信息)
//#define VAR_DBG_NOTE_HINT		(3) // 打印错误、执行和提示信息(各种详细的执行信息)

typedef int VAR_RTN;
#define	VAR_OK					(0x00) // Operation success
#define	VAR_ERR_INPUT_NULL		(0x01) // Input pointer variable is null
#define	VAR_ERR_ADDR_NULL		(0x02) // Addr of variable is null
#define	VAR_ERR_ZERO_SIZE		(0x03) // Size of variable is zero
#define	VAR_ERR_SIZE_TOO_SMALL	(0x04) // Size of variable is too small
#define	VAR_ERR_TYPE_UNKNOWN	(0x05) // Type of variable is unknown
#define	VAR_ERR_TYPE_UNSUPPORT 	(0x06) // Type of variable is not supported by this interface

typedef struct
{
	VAR_TYPE_E eType;	// 类型
	void *addr;			// 地址
	int size;			// 大小
}VAR_INFO_T;

/*----------------------------------------------*
 * Function Declare                              *
 *----------------------------------------------*/
/**	@fn      : var_get_version
  *	@brief   : 获取组件版本
  *	@param[o]: pVersion 	: 组件版本号，格式为x.y.z.svn
  *	@param[o]: pBuildTime 	: 组件编译时间,格式为 %Y-%m-%d %H:%M:%S
  *	@return  : VAR_RTN
  *	@author  : geruiyi
  */
VAR_RTN var_get_version(char **pVersion, char **pBuildTime);

/**	@fn      : var_strerror
  *	@brief   : 组件错误码转为字符串
  *	@param[i]: eRtn
  *	@return  : 错误码字符串
  *	@author  : geruiyi
  */
char *var_strerror(VAR_RTN eRtn);

/**	@fn      : var_strtype
  *	@brief   : 获取类型定义字符串描述
  *	@param[i]: eRtn
  *	@return  : 类型定义对应的字符串描述
  *	@author  : geruiyi
  */
char *var_strtype(VAR_TYPE_E eType);

/**	@fn      : var_classify
  *	@brief   : 变量类型分类
  *	@param[i]: eType
  *	@return  : VAR_CLASSIFY_E
  *	@author  : geruiyi
  */
VAR_CLASSIFY_E var_classify(VAR_TYPE_E eType);

/**	@fn      : var_set_integer
  *	@brief   : 将值写入变量
  *	@note    : 变量只支持数值型，类型不匹配时会强转
  *	@param[i]: pstVar	: 需要赋值的变量信息
  *	@param[i]: value	: 写入的值，若赋值浮点型会丢失所有小数
  *	@return  : VAR_RTN
  *	@author  : geruiyi
  */
VAR_RTN var_set_integer(VAR_INFO_T *pstVar, long long value);

/**	@fn      : var_set_double
  *	@brief   : 将值写入变量
  *	@note    : 变量只支持数值型，类型不匹配时会强转
  *	@param[i]: pstVar	: 需要赋值的变量信息
  *	@param[i]: value	: 写入的值，若赋值long long型会有精度损失
  *	@return  : VAR_RTN
  *	@author  : geruiyi
  */
VAR_RTN var_set_double (VAR_INFO_T *pstVar, double value);

/**	@fn      : var_set_string
  *	@brief   : 将字符串写入变量
  *	@note    : 变量类型只支持char[]\char *\unsigned char[]\unsigned char *
  *	@note    : 变量为数组时，可存的字符串长度为容量-1，超过后会报错
  *	@param[i]: pstVar	: 需要赋值的变量信息
  *	@param[i]: value	: 字符串地址
  *	@return  : VAR_RTN
  *	@author  : geruiyi
  */
VAR_RTN var_set_string (VAR_INFO_T *pstVar, char *value);

/**	@fn      : var_set_array
  *	@brief   : 将数组写入变量
  *	@note    : 支持所有一维指针和一维数组
  *	@note    : 变量为数组时，赋值大小超过容量后会报错
  *	@param[i]: pstVar	: 需要赋值的变量信息
  *	@param[i]: value	: 数组地址
  *	@param[i]: size		: 数组大小
  *	@return  : VAR_RTN
  *	@author  : geruiyi
  */
VAR_RTN var_set_array  (VAR_INFO_T *pstVar, void *value, int size);

/**	@fn      : var_get_integer
  *	@brief   : 从变量中获取整形数据
  *	@note    : 类型不匹配时会强转
  *	@param[i]: pstVar	: 需要获取的变量信息
  *	@param[i]: value	: 获取到的整形数据
  *	@return  : VAR_RTN
  *	@author  : geruiyi
  */
VAR_RTN var_get_integer(VAR_INFO_T *pstVar, long long *value);

/**	@fn      : var_get_double
  *	@brief   : 从变量中获取浮点型数据
  *	@note    : 类型不匹配时会强转
  *	@param[i]: pstVar	: 需要获取的变量信息
  *	@param[i]: value	: 获取到的浮点型数据
  *	@return  : VAR_RTN
  *	@author  : geruiyi
  */
VAR_RTN var_get_double (VAR_INFO_T *pstVar, double *value);

/**	@fn      : var_get_string
  *	@brief   : 从变量获取字符串数据
  *	@note    : 变量类型只支持char[]\char *\unsigned char[]\unsigned char *
  *	@param[i]: pstVar	: 需要获取的变量信息
  *	@param[i]: value	: 获取到字符串地址
  *	@return  : VAR_RTN
  *	@author  : geruiyi
  */
VAR_RTN var_get_string (VAR_INFO_T *pstVar, char **value);

/**	@fn      : debug_var_note_level
  *	@brief   : 设置调试打印等级
  *	@param[i]: eDbgNoteLevel 打印等级
  *	@return  : void
  *	@author  : geruiyi
  */
void debug_var_note_level(VAR_DBG_NOTE_E eDbgNoteLevel);

/**	@fn      : debug_var_info
  *	@brief   : 打印变量信息
  *	@param[i]: stVar	: 需要打印的变量信息
  *	@return  : void
  *	@author  : geruiyi
  */
void debug_var_info(VAR_INFO_T stVar);

#ifdef __cplusplus
}
#endif

#endif /* _VARIABLE_INFO_H_ */
