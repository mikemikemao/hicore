/******************************************************************************
  @note HangZhou Hikvision Digital Technology Co., Ltd. All Right Reserved.
 ******************************************************************************
  @file     : json_interface.h
  @brief    : 头文件
  @warning  :
  @history  : <data>        <author>       <note>
			  2020-11-21    geruiyi       Create the file

******************************************************************************/

#ifndef _JSON_INTERFACE_H_
#define _JSON_INTERFACE_H_

/*----------------------------------------------*
 * Included Header                              *
 *----------------------------------------------*/
#include "variable_info.h"
#include "cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif



/*----------------------------------------------*
 * Macros                                       *
 *----------------------------------------------*/
#ifndef ARR_SIZE
#define ARR_SIZE(_x) (sizeof(_x) / sizeof(_x[0]))
#endif
#ifndef JSTR
#define _jsif_const_mkstr_(a)  #a
#define JSTR(a)  _jsif_const_mkstr_(a)	// 将输入变为字符串常量
#endif

#define JSIF_LEVEL_MAX 	 	(32) 	// cjson报文最大嵌套层数，从根节点开始算
#define JSIF_LEVEL_ARRAY 	(10) 	// 数组最大嵌套层数
#define JSIF_ERRMSG_SIZE	(256)	// 错误信息缓存大小

typedef int JSIF_FEATURE_T;	// 节点属性，只支持0-15
#define JFDEF 	(0)	// default默认(会继承父节点特性)
#define JFOPT 	(1)	// optional可选(根节点默认为可选)
#define JFREQ 	(2)	// require必填
#define JFINV	(3)	// invalid无效,该item及下属的所有item都不处理

#define JCON_TRUE	+1U+1.0f	// 布尔型常量ture，配合JMCON使用
#define JCON_FALSE	-0U-0.0f  	// 布尔型常量false，配合JMCON使用

#define JSTM(structure, member) (((structure*)0)->member) // 获取结构体成员相对地址偏移

/* 成员信息，数组使用JSIF_ARR,bool使用JSIF_BOL,OBJECT不配置,其他使用JSIF_MEM */
//#define JSIF_NON			.stMember = {JSIF_NONE,	  {0}}
#define JMNOR(x)	.stMember = {JSIF_NORMAL, VAR_INFO(x)}	// 一般类型（json member normal）
#define JMBOL(x)	.stMember = {JSIF_BOOL,   VAR_INFO(x)}	// 布尔类型（json member bool）
#define JMARR(a)	.stMember = {JSIF_ARRAY,  {0}, (void *)a, sizeof(a[0]), ARR_SIZE(a)} // 数组类型（json member array）
#define JMARC(a,c) 	.stMember = {JSIF_ARRAY,  VAR_INFO(c), (void *)a, sizeof(a[0]), ARR_SIZE(a)} // 数组类型带数量（json member array count）
/*#define JMEXT(x)	.stMember = {JSIF_EXIST,  {0}, \
		VART_COMPARE(typeof(x), JSIF_EXIST_COLLECTION_T) ? &x : NULL}	// 特殊功能类型(存在信息集合),只允许再配置表第一行*/ // 此功能先屏蔽掉待优化完成后再开放
#define JMCFG(a,r)	.stMember = {JSIF_CFG,  VAR_INFO(r), a, sizeof(a[0]), ARR_SIZE(a)} // 特殊功能类型(相对位置的配置表嵌套，和宏JSTM配合使用)
#define JMCON(x)	.stMember = {JSIF_CONST,  VAR_INFO(JSTR(x)), NULL, GET_TYPE(x)} // 常量，只支持编码

/* 节点限制 JSON LIMIT，JSON报文解码时使用*/
#define JL(...) 	.stLimit = {__VA_ARGS__}// 限制配置宏
#define JLBLT		.flag.boolTrue = 1		// 表示节点必须为cJSON_True,否则报错
#define JLBLF		.flag.boolFalse = 1 	// 表示节点必须为cJSON_False,否则报错
#define JLMIN(x)	.flag.min=1, .minValue=x// 数值类型时为最小值限制，字符串时为最小长度限制(>=通过)，其他类型不校验
#define JLMAX(x)	.flag.max=1, .maxValue=x// 数值类型时为最大值限制，字符串时为最大长度限制(<=通过)，其他类型不校验
#define JLFEA(x)	.flag.feature = x		// 节点属性赋值：JFOPT-可选，JFREQ-必填，JFINV-无效(无效属性编码时也有效)
#define JLFEA_OPT	JLFEA(JFOPT)			// 可选属性
#define JLFEA_REQ	JLFEA(JFREQ)			// 必填属性
#define JLDEP(x)	.sDependent = x			// 依赖关系(编码和解码均有效)，赋值字符串,可选依赖最后加:opt
#define JLENUM(a)	.flag.enumNum=ARR_SIZE(a), .enumArr0=VAR_INFO(a[0]) // 枚举成员限制
#define JLENUC(a,c)	.flag.enumNum=c, .enumArr0=VAR_INFO(a[0]) 			// 枚举成员限制,带枚举数组数量
#define JLNZERO		.flag.noZero = 1		// 表示节点不支持0进行编码，支持对数值型为0、字符串地址或长度为0、数组大小为0进行过滤(仅编码有效)
#define JLSTRNCPY	.flag.strncpy = 1		// 编解码时支持字符串末尾无'\0'的场景:编码时需要拷贝到更大空间，解码时数组空间刚刚好能存下数据但不够补'\0'也支持
#define JLREG(x)	.sRegular = x			// 正则表达式约束(只能对字符串类型生效，其他类型使用会报错)

/* 存在节点赋值 */
#define JEX(x)		.pExist = GET_ADDR(x) // x需为数值型

/* 打印调试信息级别 */
typedef int JSIF_DBG_NOTE_E;
#define JSIF_DBG_NOTE_NONE		(0)	// 不打印任何信息
#define JSIF_DBG_NOTE_ERR		(1)	// 仅打印错误信息(执行失败有打印信息)
#define JSIF_DBG_NOTE_INFO		(2) // 打印错误和执行信息(有执行失败、执行结果信息)
#define JSIF_DBG_NOTE_HINT		(3) // 打印错误、执行和提示信息(各种详细的执行信息)

/* 执行结果 */
typedef int JSIF_RTN;
#define JSIF_OK					(0x00) // 执行成功
#define JSIF_ERROR				(0x01) // 执行失败
#define JSIF_INVAL_JSON_FORMAT	(0x02) // 无效的JSON报文格式
#define JSIF_MSG_PARAM_LACK		(0x03) // JSON报文必填节点缺失
#define JSIF_ITEM_TYPE_MISMATCH	(0x04) // JSON报文节点类型不匹配
#define JSIF_ARRAY_OVERFLOW		(0x05) // 解析到的数组节点超容量
#define JSIF_DEF_OUTSIDE_ARRAY	(0x06) // 数组内成员定义在数组外部（配置表配置错误）
#define JSIF_EXT_NOT_ENOUGH		(0x07) // 存在集合容量不够（扩展配置表解决，支持尾端添加空行）
#define JSIF_LIMIT_BOOL_TRUE	(0x10) // 约束校验失败：布尔TRUE校验不通过
#define JSIF_LIMIT_BOOL_FALSE	(0x11) // 约束校验失败：布尔FALSE校验不通过
#define JSIF_LIMIT_LESSER_MIN	(0x12) // 约束校验失败：小于最小值
#define JSIF_LIMIT_BIGGER_MAX	(0x13) // 约束校验失败：大于最大值
#define JSIF_LIMIT_ENUM_MISMATCH (0x14)// 约束校验失败：枚举类型不匹配
#define JSIF_LIMIT_MIS_DEP_ITEM (0x15) // 约束校验失败：依赖节点缺失
#define JSIF_LIMIT_REGULAR 		(0x16) // 约束校验失败：正则表达式
/*----------------------------------------------*
 * Struct/Enum Definition                       *
 *----------------------------------------------*/
typedef struct
{
#define JSIF_NONE 	0x00  // 未知或未配置类型，如object节点无需 配置
#define JSIF_NORMAL 0x01  // 普通类型，根据变量类型自动解析
#define JSIF_ARRAY 	0x02  // 数组类型，需配置数组参数，变量配置数组数量成员
#define JSIF_BOOL 	0x03  // 布尔类型，c语言无bool类型，需自行定义
//#define JSIF_EXIST 	0x04  // 特殊功能类型(存在信息集合功能)，此功能先屏蔽掉待优化完成后再开放
#define JSIF_CFG 	0x05  // 特殊功能类型(配置表嵌套)
#define JSIF_CONST	0x06  // 常量，只支持编码,解码时不处理也不报错
	int eCfgType; // 配置类型(见上面的宏定义)
	VAR_INFO_T var;	// 变量信息，存放对应结构体变量信息
	void *pArr;		// 数组地址
	int dwArr0Size;	// 数组元素0的大小
	int dwArrCnt;	// 数组容量
}JSIF_MEMBER_T;

typedef struct
{
	struct
	{
		unsigned int boolTrue : 1;
		unsigned int boolFalse : 1;
		unsigned int min : 1;
		unsigned int max : 1;
		unsigned int feature : 4;
		unsigned int enumNum : 8;
		unsigned int noZero : 1;
		unsigned int strncpy: 1;
	}flag;
	char *sDependent;
	double minValue;
	double maxValue;
	VAR_INFO_T enumArr0;	// 枚举数组元素0信息
	char *sRegular; 		// 正则表达式规则
}JSIF_LIMIT_T;

typedef struct
{
	char *sName;		// item名字
	char byLevel;		// 从1开始相对于OBJECT或ARRAY的绝对嵌套级别,'{'或'['相对级别+1,  '}'或']'每存在一个相对级别-1
	char byRes[3];		// 预留
	JSIF_MEMBER_T stMember; // 变量信息，使用JMNOR、JMBOL、JMARR、JMARC赋值，自动解析
	JSIF_LIMIT_T stLimit;// 节点限制，使用宏JL赋值
	char *pExist;		 // 是否解析到该Item(编码时无效)，使用宏JEX赋值，需特别注意数组内使用时变量需定义在数组内
}JSIF_CFG_T;

//typedef struct
//{
//	JSIF_CFG_T *pstCfg;	// 配置表
//	int dwCfgNum;		// 配置表数量
//}JSIF_EXIST_COLLECTION_T; // 使用JMEXT赋值

/*----------------------------------------------*
 * Function Declare                              *
 *----------------------------------------------*/
/**	@fn      : jsif_get_version
  *	@brief   : 获取组件版本
  *	@param[o]: pVersion 	: 组件版本号，格式为x.y.z.svn
  *	@param[o]: pBuildTime 	: 组件编译时间,格式为 %Y-%m-%d %H:%M:%S
  *	@return  : JSIF_RTN
  *	@author  : geruiyi
  */
JSIF_RTN jsif_get_version(char **pVersion, char **pBuildTime);

/**	@fn      : jsif_data2str
 *	@brief   : 编码：数据转JSON格式
 *	@param[i]: pstCfg 配置表地址
 *	@param[i]: dwCfgNum 配置表数量
 *	@param[o]: pStr 编码后的字符串存储地址
 *	@param[i]: dwSize 存储空间大小，字符串最大长度=dwSize - 1
 *	@return  : JSIF_RTN
 *	@author  : geruiyi
 */
JSIF_RTN jsif_data2str(JSIF_CFG_T *pstCfg, int dwCfgNum, char *pStr, int dwSize);

/**	@fn      : jsif_data2str_unformatted
 *	@brief   : 编码：数据转JSON格式, JSON不进行格式化
 *	@param[i]: pstCfg 配置表地址
 *	@param[i]: dwCfgNum 配置表数量
 *	@param[o]: pStr 编码后的字符串存储地址
 *	@param[i]: dwSize 存储空间大小，字符串最大长度=dwSize - 1
 *	@return  : JSIF_RTN
 *	@author  : geruiyi
 */
JSIF_RTN jsif_data2str_unformatted(JSIF_CFG_T *pstCfg, int dwCfgNum, char *pStr, int dwSize);

/**	@fn      : jsif_str2data
 *	@brief   : 解码：JSON转成结构体数据
 *	@param[i]: pstCfg 配置表地址
 *	@param[i]: dwCfgNum 配置表数量
 *	@param[i]: pStr 需要解码的JSON字符串
 *	@param[o]: errMsg 解码时返回的错误信息,不关心时支持NULL入参
 *	@return  : JSIF_RTN
 *	@author  : geruiyi
 */
JSIF_RTN jsif_str2data(JSIF_CFG_T *pstCfg, int dwCfgNum, const char *byStr, char errMsg[JSIF_ERRMSG_SIZE]);

/**	@fn      : jsif_data2root
  *	@brief   : 编码-将配置表数据添加到根节点
  *	@param[i]: pstCfg 配置表地址
  *	@param[i]: dwCfgNum 配置表数量
  *	@param[o]: pRoot 编码的根节点
  *	@return  : JSIF_RTN
  *	@author  : geruiyi
  */
JSIF_RTN jsif_data2root(JSIF_CFG_T *pstCfg, int dwCfgNum, cJSON *pRoot);

/**	@fn      : jsif_root2data
  *	@brief   : 解码：JSON根节点转为结构体数据
  *	@param[i]: pstCfg 配置表地址
  *	@param[i]: dwCfgNum 配置表数量
  *	@param[i]: pRoot 需要解码的JSON根节点
  *	@param[o]: errMsg 解码时返回的错误信息,不关心时支持NULL入参
  *	@return  : JSIF_RTN
  *	@author  : geruiyi
  */
JSIF_RTN jsif_root2data(JSIF_CFG_T *pstCfg, int dwCfgNum, cJSON *pRoot, char errMsg[JSIF_ERRMSG_SIZE]);

/**	@fn      : jsif_nstCfg_to_rootCfg
  *	@brief   : 将嵌套配置表关联上变量地址等信息，返回根配置表
  *	@param[i]: pstNstCfg 嵌套配置表
  *	@param[i]: dwCfgNum 嵌套配置表大小
  *	@param[i]: pData 关联变量的地址
  *	@param[i]: dwDataSize 关联变量的大小,通过该变量检测嵌套配置是否异常，支持赋值为0则不检查
  *	@return  : JSIF_CFG_T(已关联好的配置表)
  *	@author  : geruiyi
  */
JSIF_CFG_T jsif_nstCfg_to_rootCfg(JSIF_CFG_T *pstNstCfg, int dwCfgNum, void *pData, int dwDataSize);

/**	@fn      : debug_jsif_note_level
  *	@brief   : 设置调试打印等级
  *	@param[i]: eDbgNoteLevel 打印等级
  *	@return  : void
  *	@author  : geruiyi
  */
void debug_jsif_note_level(JSIF_DBG_NOTE_E eDbgNoteLevel);
/**	@fn      : debug_jsif_cfg_printf
  *	@brief   : 调试接口-打印配置表各成员信息
  *	@param[i]: pstCfg 配置表地址
  *	@param[i]: dwCfgNum 配置表数量
  *	@return  : void
  *	@author  : geruiyi
  */
void debug_jsif_cfg_printf(JSIF_CFG_T *pstCfg, int dwCfgNum);

///**	@fn      : jsif_isExist
//  *	@brief   : 根据地址解析变量是JSON报文解析出来的
//  *	@note    : 数组或结构体是不支持的，返回相同地址的成员存在信息（由于C语言无法根据地址区分数据类型）
//  *	@note    : 存在信息集合的数据存放在配置表中，调用本接口需保证配置表信息依旧存在
//  *	@param[i]: stExist 存在信息集合
//  *	@param[i]: pVarAddr 变量地址
//  *	@return  : true：存在 false：不存在
//  *	@author  : geruiyi
//  */
//int jsif_isExist(JSIF_EXIST_COLLECTION_T stExist, void *pVarAddr);


#ifdef __cplusplus
}
#endif

#endif /* _JSON_INTERFACE_H_ */
