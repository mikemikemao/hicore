/******************************************************************************
  @note HangZhou Hikvision Digital Technology Co., Ltd. All Right Reserved.
 ******************************************************************************
  @file     : json_interface.h
  @brief    : ͷ�ļ�
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
#define JSTR(a)  _jsif_const_mkstr_(a)	// �������Ϊ�ַ�������
#endif

#define JSIF_LEVEL_MAX 	 	(32) 	// cjson�������Ƕ�ײ������Ӹ��ڵ㿪ʼ��
#define JSIF_LEVEL_ARRAY 	(10) 	// �������Ƕ�ײ���
#define JSIF_ERRMSG_SIZE	(256)	// ������Ϣ�����С

typedef int JSIF_FEATURE_T;	// �ڵ����ԣ�ֻ֧��0-15
#define JFDEF 	(0)	// defaultĬ��(��̳и��ڵ�����)
#define JFOPT 	(1)	// optional��ѡ(���ڵ�Ĭ��Ϊ��ѡ)
#define JFREQ 	(2)	// require����
#define JFINV	(3)	// invalid��Ч,��item������������item��������

#define JCON_TRUE	+1U+1.0f	// �����ͳ���ture�����JMCONʹ��
#define JCON_FALSE	-0U-0.0f  	// �����ͳ���false�����JMCONʹ��

#define JSTM(structure, member) (((structure*)0)->member) // ��ȡ�ṹ���Ա��Ե�ַƫ��

/* ��Ա��Ϣ������ʹ��JSIF_ARR,boolʹ��JSIF_BOL,OBJECT������,����ʹ��JSIF_MEM */
//#define JSIF_NON			.stMember = {JSIF_NONE,	  {0}}
#define JMNOR(x)	.stMember = {JSIF_NORMAL, VAR_INFO(x)}	// һ�����ͣ�json member normal��
#define JMBOL(x)	.stMember = {JSIF_BOOL,   VAR_INFO(x)}	// �������ͣ�json member bool��
#define JMARR(a)	.stMember = {JSIF_ARRAY,  {0}, (void *)a, sizeof(a[0]), ARR_SIZE(a)} // �������ͣ�json member array��
#define JMARC(a,c) 	.stMember = {JSIF_ARRAY,  VAR_INFO(c), (void *)a, sizeof(a[0]), ARR_SIZE(a)} // �������ʹ�������json member array count��
/*#define JMEXT(x)	.stMember = {JSIF_EXIST,  {0}, \
		VART_COMPARE(typeof(x), JSIF_EXIST_COLLECTION_T) ? &x : NULL}	// ���⹦������(������Ϣ����),ֻ���������ñ��һ��*/ // �˹��������ε����Ż���ɺ��ٿ���
#define JMCFG(a,r)	.stMember = {JSIF_CFG,  VAR_INFO(r), a, sizeof(a[0]), ARR_SIZE(a)} // ���⹦������(���λ�õ����ñ�Ƕ�ף��ͺ�JSTM���ʹ��)
#define JMCON(x)	.stMember = {JSIF_CONST,  VAR_INFO(JSTR(x)), NULL, GET_TYPE(x)} // ������ֻ֧�ֱ���

/* �ڵ����� JSON LIMIT��JSON���Ľ���ʱʹ��*/
#define JL(...) 	.stLimit = {__VA_ARGS__}// �������ú�
#define JLBLT		.flag.boolTrue = 1		// ��ʾ�ڵ����ΪcJSON_True,���򱨴�
#define JLBLF		.flag.boolFalse = 1 	// ��ʾ�ڵ����ΪcJSON_False,���򱨴�
#define JLMIN(x)	.flag.min=1, .minValue=x// ��ֵ����ʱΪ��Сֵ���ƣ��ַ���ʱΪ��С��������(>=ͨ��)���������Ͳ�У��
#define JLMAX(x)	.flag.max=1, .maxValue=x// ��ֵ����ʱΪ���ֵ���ƣ��ַ���ʱΪ��󳤶�����(<=ͨ��)���������Ͳ�У��
#define JLFEA(x)	.flag.feature = x		// �ڵ����Ը�ֵ��JFOPT-��ѡ��JFREQ-���JFINV-��Ч(��Ч���Ա���ʱҲ��Ч)
#define JLFEA_OPT	JLFEA(JFOPT)			// ��ѡ����
#define JLFEA_REQ	JLFEA(JFREQ)			// ��������
#define JLDEP(x)	.sDependent = x			// ������ϵ(����ͽ������Ч)����ֵ�ַ���,��ѡ��������:opt
#define JLENUM(a)	.flag.enumNum=ARR_SIZE(a), .enumArr0=VAR_INFO(a[0]) // ö�ٳ�Ա����
#define JLENUC(a,c)	.flag.enumNum=c, .enumArr0=VAR_INFO(a[0]) 			// ö�ٳ�Ա����,��ö����������
#define JLNZERO		.flag.noZero = 1		// ��ʾ�ڵ㲻֧��0���б��룬֧�ֶ���ֵ��Ϊ0���ַ�����ַ�򳤶�Ϊ0�������СΪ0���й���(��������Ч)
#define JLSTRNCPY	.flag.strncpy = 1		// �����ʱ֧���ַ���ĩβ��'\0'�ĳ���:����ʱ��Ҫ����������ռ䣬����ʱ����ռ�ոպ��ܴ������ݵ�������'\0'Ҳ֧��
#define JLREG(x)	.sRegular = x			// ������ʽԼ��(ֻ�ܶ��ַ���������Ч����������ʹ�ûᱨ��)

/* ���ڽڵ㸳ֵ */
#define JEX(x)		.pExist = GET_ADDR(x) // x��Ϊ��ֵ��

/* ��ӡ������Ϣ���� */
typedef int JSIF_DBG_NOTE_E;
#define JSIF_DBG_NOTE_NONE		(0)	// ����ӡ�κ���Ϣ
#define JSIF_DBG_NOTE_ERR		(1)	// ����ӡ������Ϣ(ִ��ʧ���д�ӡ��Ϣ)
#define JSIF_DBG_NOTE_INFO		(2) // ��ӡ�����ִ����Ϣ(��ִ��ʧ�ܡ�ִ�н����Ϣ)
#define JSIF_DBG_NOTE_HINT		(3) // ��ӡ����ִ�к���ʾ��Ϣ(������ϸ��ִ����Ϣ)

/* ִ�н�� */
typedef int JSIF_RTN;
#define JSIF_OK					(0x00) // ִ�гɹ�
#define JSIF_ERROR				(0x01) // ִ��ʧ��
#define JSIF_INVAL_JSON_FORMAT	(0x02) // ��Ч��JSON���ĸ�ʽ
#define JSIF_MSG_PARAM_LACK		(0x03) // JSON���ı���ڵ�ȱʧ
#define JSIF_ITEM_TYPE_MISMATCH	(0x04) // JSON���Ľڵ����Ͳ�ƥ��
#define JSIF_ARRAY_OVERFLOW		(0x05) // ������������ڵ㳬����
#define JSIF_DEF_OUTSIDE_ARRAY	(0x06) // �����ڳ�Ա�����������ⲿ�����ñ����ô���
#define JSIF_EXT_NOT_ENOUGH		(0x07) // ���ڼ���������������չ���ñ�����֧��β����ӿ��У�
#define JSIF_LIMIT_BOOL_TRUE	(0x10) // Լ��У��ʧ�ܣ�����TRUEУ�鲻ͨ��
#define JSIF_LIMIT_BOOL_FALSE	(0x11) // Լ��У��ʧ�ܣ�����FALSEУ�鲻ͨ��
#define JSIF_LIMIT_LESSER_MIN	(0x12) // Լ��У��ʧ�ܣ�С����Сֵ
#define JSIF_LIMIT_BIGGER_MAX	(0x13) // Լ��У��ʧ�ܣ��������ֵ
#define JSIF_LIMIT_ENUM_MISMATCH (0x14)// Լ��У��ʧ�ܣ�ö�����Ͳ�ƥ��
#define JSIF_LIMIT_MIS_DEP_ITEM (0x15) // Լ��У��ʧ�ܣ������ڵ�ȱʧ
#define JSIF_LIMIT_REGULAR 		(0x16) // Լ��У��ʧ�ܣ�������ʽ
/*----------------------------------------------*
 * Struct/Enum Definition                       *
 *----------------------------------------------*/
typedef struct
{
#define JSIF_NONE 	0x00  // δ֪��δ�������ͣ���object�ڵ����� ����
#define JSIF_NORMAL 0x01  // ��ͨ���ͣ����ݱ��������Զ�����
#define JSIF_ARRAY 	0x02  // �������ͣ����������������������������������Ա
#define JSIF_BOOL 	0x03  // �������ͣ�c������bool���ͣ������ж���
//#define JSIF_EXIST 	0x04  // ���⹦������(������Ϣ���Ϲ���)���˹��������ε����Ż���ɺ��ٿ���
#define JSIF_CFG 	0x05  // ���⹦������(���ñ�Ƕ��)
#define JSIF_CONST	0x06  // ������ֻ֧�ֱ���,����ʱ������Ҳ������
	int eCfgType; // ��������(������ĺ궨��)
	VAR_INFO_T var;	// ������Ϣ����Ŷ�Ӧ�ṹ�������Ϣ
	void *pArr;		// �����ַ
	int dwArr0Size;	// ����Ԫ��0�Ĵ�С
	int dwArrCnt;	// ��������
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
	VAR_INFO_T enumArr0;	// ö������Ԫ��0��Ϣ
	char *sRegular; 		// ������ʽ����
}JSIF_LIMIT_T;

typedef struct
{
	char *sName;		// item����
	char byLevel;		// ��1��ʼ�����OBJECT��ARRAY�ľ���Ƕ�׼���,'{'��'['��Լ���+1,  '}'��']'ÿ����һ����Լ���-1
	char byRes[3];		// Ԥ��
	JSIF_MEMBER_T stMember; // ������Ϣ��ʹ��JMNOR��JMBOL��JMARR��JMARC��ֵ���Զ�����
	JSIF_LIMIT_T stLimit;// �ڵ����ƣ�ʹ�ú�JL��ֵ
	char *pExist;		 // �Ƿ��������Item(����ʱ��Ч)��ʹ�ú�JEX��ֵ�����ر�ע��������ʹ��ʱ�����趨����������
}JSIF_CFG_T;

//typedef struct
//{
//	JSIF_CFG_T *pstCfg;	// ���ñ�
//	int dwCfgNum;		// ���ñ�����
//}JSIF_EXIST_COLLECTION_T; // ʹ��JMEXT��ֵ

/*----------------------------------------------*
 * Function Declare                              *
 *----------------------------------------------*/
/**	@fn      : jsif_get_version
  *	@brief   : ��ȡ����汾
  *	@param[o]: pVersion 	: ����汾�ţ���ʽΪx.y.z.svn
  *	@param[o]: pBuildTime 	: �������ʱ��,��ʽΪ %Y-%m-%d %H:%M:%S
  *	@return  : JSIF_RTN
  *	@author  : geruiyi
  */
JSIF_RTN jsif_get_version(char **pVersion, char **pBuildTime);

/**	@fn      : jsif_data2str
 *	@brief   : ���룺����תJSON��ʽ
 *	@param[i]: pstCfg ���ñ��ַ
 *	@param[i]: dwCfgNum ���ñ�����
 *	@param[o]: pStr �������ַ����洢��ַ
 *	@param[i]: dwSize �洢�ռ��С���ַ�����󳤶�=dwSize - 1
 *	@return  : JSIF_RTN
 *	@author  : geruiyi
 */
JSIF_RTN jsif_data2str(JSIF_CFG_T *pstCfg, int dwCfgNum, char *pStr, int dwSize);

/**	@fn      : jsif_data2str_unformatted
 *	@brief   : ���룺����תJSON��ʽ, JSON�����и�ʽ��
 *	@param[i]: pstCfg ���ñ��ַ
 *	@param[i]: dwCfgNum ���ñ�����
 *	@param[o]: pStr �������ַ����洢��ַ
 *	@param[i]: dwSize �洢�ռ��С���ַ�����󳤶�=dwSize - 1
 *	@return  : JSIF_RTN
 *	@author  : geruiyi
 */
JSIF_RTN jsif_data2str_unformatted(JSIF_CFG_T *pstCfg, int dwCfgNum, char *pStr, int dwSize);

/**	@fn      : jsif_str2data
 *	@brief   : ���룺JSONת�ɽṹ������
 *	@param[i]: pstCfg ���ñ��ַ
 *	@param[i]: dwCfgNum ���ñ�����
 *	@param[i]: pStr ��Ҫ�����JSON�ַ���
 *	@param[o]: errMsg ����ʱ���صĴ�����Ϣ,������ʱ֧��NULL���
 *	@return  : JSIF_RTN
 *	@author  : geruiyi
 */
JSIF_RTN jsif_str2data(JSIF_CFG_T *pstCfg, int dwCfgNum, const char *byStr, char errMsg[JSIF_ERRMSG_SIZE]);

/**	@fn      : jsif_data2root
  *	@brief   : ����-�����ñ�������ӵ����ڵ�
  *	@param[i]: pstCfg ���ñ��ַ
  *	@param[i]: dwCfgNum ���ñ�����
  *	@param[o]: pRoot ����ĸ��ڵ�
  *	@return  : JSIF_RTN
  *	@author  : geruiyi
  */
JSIF_RTN jsif_data2root(JSIF_CFG_T *pstCfg, int dwCfgNum, cJSON *pRoot);

/**	@fn      : jsif_root2data
  *	@brief   : ���룺JSON���ڵ�תΪ�ṹ������
  *	@param[i]: pstCfg ���ñ��ַ
  *	@param[i]: dwCfgNum ���ñ�����
  *	@param[i]: pRoot ��Ҫ�����JSON���ڵ�
  *	@param[o]: errMsg ����ʱ���صĴ�����Ϣ,������ʱ֧��NULL���
  *	@return  : JSIF_RTN
  *	@author  : geruiyi
  */
JSIF_RTN jsif_root2data(JSIF_CFG_T *pstCfg, int dwCfgNum, cJSON *pRoot, char errMsg[JSIF_ERRMSG_SIZE]);

/**	@fn      : jsif_nstCfg_to_rootCfg
  *	@brief   : ��Ƕ�����ñ�����ϱ�����ַ����Ϣ�����ظ����ñ�
  *	@param[i]: pstNstCfg Ƕ�����ñ�
  *	@param[i]: dwCfgNum Ƕ�����ñ��С
  *	@param[i]: pData ���������ĵ�ַ
  *	@param[i]: dwDataSize ���������Ĵ�С,ͨ���ñ������Ƕ�������Ƿ��쳣��֧�ָ�ֵΪ0�򲻼��
  *	@return  : JSIF_CFG_T(�ѹ����õ����ñ�)
  *	@author  : geruiyi
  */
JSIF_CFG_T jsif_nstCfg_to_rootCfg(JSIF_CFG_T *pstNstCfg, int dwCfgNum, void *pData, int dwDataSize);

/**	@fn      : debug_jsif_note_level
  *	@brief   : ���õ��Դ�ӡ�ȼ�
  *	@param[i]: eDbgNoteLevel ��ӡ�ȼ�
  *	@return  : void
  *	@author  : geruiyi
  */
void debug_jsif_note_level(JSIF_DBG_NOTE_E eDbgNoteLevel);
/**	@fn      : debug_jsif_cfg_printf
  *	@brief   : ���Խӿ�-��ӡ���ñ����Ա��Ϣ
  *	@param[i]: pstCfg ���ñ��ַ
  *	@param[i]: dwCfgNum ���ñ�����
  *	@return  : void
  *	@author  : geruiyi
  */
void debug_jsif_cfg_printf(JSIF_CFG_T *pstCfg, int dwCfgNum);

///**	@fn      : jsif_isExist
//  *	@brief   : ���ݵ�ַ����������JSON���Ľ���������
//  *	@note    : �����ṹ���ǲ�֧�ֵģ�������ͬ��ַ�ĳ�Ա������Ϣ������C�����޷����ݵ�ַ�����������ͣ�
//  *	@note    : ������Ϣ���ϵ����ݴ�������ñ��У����ñ��ӿ��豣֤���ñ���Ϣ���ɴ���
//  *	@param[i]: stExist ������Ϣ����
//  *	@param[i]: pVarAddr ������ַ
//  *	@return  : true������ false��������
//  *	@author  : geruiyi
//  */
//int jsif_isExist(JSIF_EXIST_COLLECTION_T stExist, void *pVarAddr);


#ifdef __cplusplus
}
#endif

#endif /* _JSON_INTERFACE_H_ */
