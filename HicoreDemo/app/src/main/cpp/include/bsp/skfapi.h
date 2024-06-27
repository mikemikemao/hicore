/** 
* @file skfapi.h
* @brief 智能密码钥匙密码应用接口规范（GM/T 0016-2012）
* @author xdja
* @version 1.0.0.1
* @date 20141021
* @note
*/

#ifndef _INC_SKFAPI_H_
#define _INC_SKFAPI_H_

#ifdef __cplusplus
extern "C"
{
#endif

///错误代码定义和说明
#define SAR_OK                           0x00000000	 //成功
#define SAR_FAIL                         0x0A000001	 //失败
#define SAR_UNKNOWNER                    0x0A000002  //异常错误
#define SAR_NOSUPPORTYETERR              0x0A000003	 //不支持的服务
#define SAR_FILEERR                      0x0A000004	 //文件操作错误
#define SAR_INVALIDHANDLEERR             0x0A000005	 //无效的句柄
#define SAR_INVALIDPARAMERR              0x0A000006	 //无效的参数
#define SAR_READFILEERR                  0x0A000007	 //读文件错误
#define SAR_WRITEFILEERR                 0x0A000008	 //写文件错误
#define SAR_NAMELENERR                   0x0A000009	 //名称长度错误
#define SAR_KEYUSAGEERR                  0x0A00000A	 //密钥用途错误
#define SAR_MODULUSLENERR                0x0A00000B	 //模的长度错误
#define SAR_NOTINITIALIZEERR             0x0A00000C	 //未初始化
#define SAR_OBJERR                       0x0A00000D  //对象错误
#define SAR_MEMORYERR                    0x0A00000E	 //内存错误
#define SAR_TIMEOUTERR                   0x0A00000F	 //超时
#define SAR_INDATALENERR                 0x0A000010	 //输入数据长度错误
#define SAR_INDATAERR                    0x0A000011	 //输入数据错误
#define SAR_GENRANDERR                   0x0A000012	 //生成随机数错误
#define SAR_HASHOBJERR                   0x0A000013	 //HASH对象错误
#define SAR_HASHERR                      0x0A000014	 //HASH运算错误
#define SAR_GENRSAKEYERR                 0x0A000015	 //产生RSA密钥错误
#define SAR_RSAMODULUSLENERR             0x0A000016	 //RSA密钥模长错误
#define SAR_CSPIMPRTPUBKEYERR            0x0A000017  //CSP服务导入公钥错误
#define SAR_RSAENCERR                    0x0A000018	 //RSA加密错误
#define SAR_RSADECERR                    0x0A000019	 //RSA解密错误
#define SAR_HASHNOTEQUALERR              0x0A00001A	 //HASH值不相等
#define SAR_KEYNOTFOUNTERR               0x0A00001B	 //密钥未发现
#define SAR_CERTNOTFOUNTERR              0x0A00001C	 //证书未发现
#define SAR_NOTEXPORTERR                 0x0A00001D	 //对象未导出
#define SAR_DECRYPTPADERR                0x0A00001E	 //解密时做补丁错误
#define SAR_MACLENERR                    0x0A00001F	 //MAC长度错误
#define SAR_BUFFER_TOO_SMALL             0x0A000020	 //缓冲区不足
#define SAR_KEYINFOTYPRERR               0x0A000021	 //密钥类型错误
#define SAR_NOT_EVENTERR                 0x0A000022	 //无事件错误
#define SAR_DEVICE_REMOVED               0x0A000023	 //设备已移除
#define SAR_PIN_INCORRECT                0x0A000024	 //PIN不正确
#define SAR_PIN_LOCKED                   0x0A000025	 //PIN被锁死
#define SAR_PIN_INVALID                  0x0A000026	 //PIN无效
#define SAR_PIN_LEN_RANGE                0x0A000027	 //PIN长度错误
#define SAR_USER_ALREADY_LOGGED_IN       0x0A000028	 //用户已经登录
#define SAR_USER_PIN_NOT_INITIALIZED     0x0A000029	 //没有初始化用户口令
#define SAR_USER_TYPE_INVALID            0x0A00002A	 //PIN类型错误
#define SAR_APPLICATION_NAME_INVALID     0x0A00002B	 //应用名称无效
#define SAR_APPLICATION_EXISTS           0x0A00002C	 //应用已经存在
#define SAR_USER_NOT_LOGGED_IN           0x0A00002D	 //用户没有登录
#define SAR_APPLICATION_NOT_EXISTS       0x0A00002E	 //应用不存在
#define SAR_FILE_ALREADY_EXIST           0x0A00002F	 //文件已经存在
#define SAR_NO_ROOM                      0x0A000030	 //空间不足
#define SAR_FILE_NOT_EXIST               0x0A000031	 //文件不存在
#define SAR_REACH_MAX_CONTAINER_COUNT    0x0A000032  //已达到最大可管理容器数
#define SAR_NOCREATEFILE_RIGHT           0x0A000033	 //没有创建文件的权限

#define SAR_FP_NOT_EXIST                 0x0A000034	 //指纹不存在
#define SAR_FP_ENROLLING                 0x0A000035	 //当前正在进行指纹录入操作，如需执行其它操作需取消当前状态
#define SAR_FP_VERIFYING                 0x0A000036	 //当前正在进行指纹验证操作，如需执行其它操作需取消当前状态
#define SAR_FP_NOT_MATCH                 0x0A000037	 //指纹不匹配，验证失败
#define SAR_FP_CANCEL                    0x0A000038	 //指纹取消失败
#define SAR_FP_CONDITION_NOTMET          0x0A000039  //使用条件不满足
#define SAR_FP_WAITE_ENROLL              0x0A000040	 //等待指纹录入
#define SAR_FP_QUERYWAITE                0x0A000041	 //未查询到指纹状态，请等待

///基本数据类型
typedef signed char INT8;
typedef signed short INT16;
typedef signed int INT32;
typedef unsigned char UINT8;
typedef unsigned short UINT16;
typedef unsigned int UINT32;
typedef int BOOL;
typedef UINT8 BYTE;
typedef UINT8 CHAR;
typedef INT16 SHORT;
typedef UINT16 USHORT;
typedef INT32 LONG;
typedef UINT32 ULONG;
typedef UINT32 UINT;
typedef UINT16 WORD;
typedef UINT32 DWORD;
typedef CHAR *LPSTR;
typedef void *HANDLE;
typedef HANDLE DEVHANDLE;
typedef HANDLE HAPPLICATION;
typedef HANDLE HCONTAINER;

///常量定义
#ifdef WIN32
#define DEVAPI _stdcall
#else
#define DEVAPI
#endif
#define TRUE 0x00000001
#define FALSE 0x00000000
#define ADMIN_TYPE 0 //管理员PIN类型
#define USER_TYPE 1	 //用户PIN类型

///算法标识
//分组密码算法标识
#define SGD_SM1_ECB 0x00000101	 //SM1算法ECB加密模式
#define SGD_SM1_CBC 0x00000102	 //SM1算法CBC加密模式
#define SGD_SM1_CFB 0x00000104	 //SM1算法CFB加密模式
#define SGD_SM1_OFB 0x00000108	 //SM1算法0FB加密模式
#define SGD_SM1_MAC 0x00000110	 //SM1算法MAC运算
#define SGD_SSF33_ECB 0x00000201 //SSF33算法ECB加密模式
#define SGD_SSF33_CBC 0x00000202 //SSF33算法CBC加密模式
#define SGD_SSF33_CFB 0x00000204 //SSF33算法CFB加密模式
#define SGD_SSF33_OFB 0x00000208 //SSF33算法0FB加密模式
#define SGD_SSF33_MAC 0x00000210 //SSF33算法MAC运算
#define SGD_SM4_ECB 0x00000401	 //SM4算法ECB加密模式
#define SGD_SM4_CBC 0x00000402	 //SM4算法CBC加密模式
#define SGD_SM4_CFB 0x00000404	 //SM4算法CFB加密模式
#define SGD_SM4_OFB 0x00000408	 //SM4算法0FB加密模式
#define SGD_SM4_MAC 0x00000410	 //SM4算法MAC运算
#define SGD_ZUC_EEA3 0x00000801	 //ZUC祖冲之机密性算法128-EEA3算法
#define SGD_ZUC_EIA3 0x00000802	 //ZUC祖冲之完整性算法128-EIA3算法

//扩展的其他算法标识
#define SGD_3DES_ECB 0x80000101	  //3DES-128算法ECB加密模式
#define SGD_3DES_CBC 0x80000102	  //3DES-128算法CBC加密模式
#define SGD_3DES24_ECB 0x80000201 //3DES-192算法ECB加密模式
#define SGD_3DES24_CBC 0x80000202 //3DES-192算法CBC加密模式
#define SGD_AES_ECB 0x80000401	  //AES-128算法ECB加密模式
#define SGD_AES_CBC 0x80000402	  //AES-128算法CBC加密模式

//非对称密码算法标识
#define SGD_RSA 0x00010000	 //RSA算法
#define SGD_SM2 0x00020100	 //SM2椭圆曲线密码算法
#define SGD_SM2_1 0x00020200 //SM2椭圆曲线签名算法
#define SGD_SM2_2 0x00020400 //SM2椭圆曲线密钥交换协议
#define SGD_SM2_3 0x00020800 //SM2椭圆曲线加密算法

#define SGD_ECC 0x00040100		//ECC椭圆曲线
#define SGD_ECC_P256 0x00040200 //ECC P256椭圆曲线
#define SGD_ECC_P384 0x00040300 //ECC P384椭圆曲线
#define SGD_ECC_P521 0x00040400 //ECC P521椭圆曲线

//密码杂凑算法标识
#define SGD_SM3 0x00000001	  //SM3杂凑算法
#define SGD_SHA1 0x00000002	  //SHA_1杂凑算法
#define SGD_SHA256 0x00000004 //SHA_256杂凑算法
#define SGD_SHA384 0x00000005 //SHA_384杂凑算法
#define SGD_SHA512 0x00000006 //SHA_512杂凑算法

//签名算法标识
#define SGD_SM3_RSA 0x00010001	  //基于SM3算法和RSA算法的签名
#define SGD_SHA1_RSA 0x00010002	  //基于SHA_1算法和RSA算法的签名
#define SGD_SHA256_RSA 0x00010004 //基于SHA_256算法和RSA算法的签名
#define SGD_SM3_SM2 0x00020201	  //基于SM3算法和SM2算法的签名

#pragma pack(1)

///复合数据类型
//版本
typedef struct Struct_Version
{
	BYTE major;
	BYTE minor;
} VERSION;
//设备信息
typedef struct Struct_DEVINFO
{
	VERSION Version;		 //数据结构版本号,本结构版本号1.0
	CHAR Manufacturer[64];	 //设备厂商信息,以 '\0'结束的ASCII字符串
	CHAR Issuer[64];		 //发行厂商信息,以 '\0'结束的ASCII字符串
	CHAR Label[32];			 //设备标签,以 '\0'结束的ASCII字符串
	CHAR SerialNumber[32];	 //序列号,以 '\0'结束的ASCII字符串
	VERSION HWVerison;		 //设备硬件版本
	VERSION FirmwareVersion; //设备本身固件版本
	ULONG AlgSymCap;		 //分组密码算法标识
	ULONG AlgAsymCap;		 //非对称密码算法标识
	ULONG AlgHashCap;		 //密码杂凑算法标识
	ULONG DevAuthAlgId;		 //设备认证时使用的分组密码算法标识
	ULONG TotalSpace;		 //设备总空间大小
	ULONG FreeSpace;		 //用户可用空间大小
	ULONG MaxECCBufferSize;	 //能够处理的ECC加密数据大小
	ULONG MaxBufferSize;	 //能够处理的分组运算和杂凑运算的数据大小
	BYTE Reserved[64];		 //保留扩展
} DEVINFO, *PDEVINFO;
#define SKF_DEVINFO
	//RSA公钥数据结构
#define MAX_RSA_MODULUS_LEN 256
#define MAX_RSA_EXPONENT_LEN 4
typedef struct Struct_RSAPUBLICKEYBLOB
{
	ULONG AlgID;							   //算法标识号
	ULONG BitLen;							   //模数的实际位长度,必须是8的倍数
	BYTE Modulus[MAX_RSA_MODULUS_LEN];		   //模数 n = p * q ,实际长度为BitLen/8字节
	BYTE PublicExponent[MAX_RSA_EXPONENT_LEN]; //公开密钥 e 一般为 00010001
} RSAPUBLICKEYBLOB, *PRSAPUBLICKEYBLOB;
//RSA私钥数据结构
typedef struct Struct_RSAPRIVATEKEYBLOB
{
	ULONG AlgID;								  //算法标识号
	ULONG BitLen;								  //模数的实际位长度,必须是8的倍数
	BYTE Modulus[MAX_RSA_MODULUS_LEN];			  //模数 n = p * q,实际长度为 BitLen/8字节
	BYTE PublicExponent[MAX_RSA_EXPONENT_LEN];	  //公开密钥e,一般为010001
	BYTE PrivateExponent[MAX_RSA_MODULUS_LEN];	  //私有密钥d,实际长度为BitLen/8字节
	BYTE Prime1[MAX_RSA_MODULUS_LEN / 2];		  //素数 p,实际长度为BitLen/16字节
	BYTE Prime2[MAX_RSA_MODULUS_LEN / 2];		  //素数 q,实际长度为BitLen/16字节
	BYTE Prime1Exponent[MAX_RSA_MODULUS_LEN / 2]; //d mod (p-1)的值,实际长度为BitLen/16字节
	BYTE Prime2Exponent[MAX_RSA_MODULUS_LEN / 2]; //d mod (q -1)的值,实际长度为BitLen/16字节
	BYTE Coefficient[MAX_RSA_MODULUS_LEN / 2];	  //q模p的乘法逆元,实际长度为BitLen/16字节
} RSAPRIVATEKEYBLOB, *PRSAPRIVATEKEYBLOB;
//ECC公钥数据结构
#define ECC_MAX_XCOORDINATE_BITS_LEN 512
#define ECC_MAX_YCOORDINATE_BITS_LEN 512
typedef struct Struct_ECCPUBLICKEYBLOB
{
	ULONG BitLen;										//模数的实际位长度
	BYTE XCoordinate[ECC_MAX_XCOORDINATE_BITS_LEN / 8]; //曲线上X的坐标 , 约定：SM2数据结构长64字节,有效位后32字节
	BYTE YCoordinate[ECC_MAX_YCOORDINATE_BITS_LEN / 8]; //曲线上Y的坐标
} ECCPUBLICKEYBLOB, *PECCPUBLICKEYBLOB;
//ECC私钥数据结构
#define ECC_MAX_MODULUS_BITS_LEN 512
typedef struct Struct_ECCPRIVATEKEYBLOB
{
	ULONG BitLen;								   //模数的实际位长度
	BYTE PrivateKey[ECC_MAX_MODULUS_BITS_LEN / 8]; //私有密钥
} ECCPRIVATEKEYBLOB, *PECCPRIVATEKEYBLOB;
//ECC密文数据结构
typedef struct Struct_ECCCIPHERBLOB
{
	BYTE XCoordinate[ECC_MAX_XCOORDINATE_BITS_LEN / 8]; //与y组成椭圆曲线上的点(x,y)
	BYTE YCoordinate[ECC_MAX_YCOORDINATE_BITS_LEN / 8]; //
	BYTE HASH[32];										//密文的杂凑值
	ULONG CipherLen;									//密文数据长度
	BYTE Cipher[1];										//密文数据,实际长度为CipherLen
} ECCCIPHERBLOB, *PECCCIPHERBLOB;
//ECC签名数据结构
typedef struct Struct_ECCSIGNATUREBLOB
{
	BYTE r[ECC_MAX_XCOORDINATE_BITS_LEN / 8]; //签名结果的r部分
	BYTE s[ECC_MAX_XCOORDINATE_BITS_LEN / 8]; //签名结果的s部分
} ECCSIGNATUREBLOB, *PECCSIGNATUREBLOB;
//分组密码参数
#define MAX_IV_LEN 32
typedef struct Struct_BLOCKCIPHERPARAM
{
	BYTE IV[MAX_IV_LEN]; //初始向量
	ULONG IVLen;		 //初始向量长度（按字节计算）
	ULONG PaddingType;	 //填充方法，0表示不填充，1表示按照PKCS#5方式填充
	ULONG FeedBitLen;	 //反馈值的位长度（按位计算）
} BLOCKCIPHERPARAM, *PBLOCKCIPHERPARAM;
//ECC加密密钥对保护结构
typedef struct SKF_ENVELOPEDKEYBLOB
{
	ULONG Version;				 //当前版本为1
	ULONG ulSymmAlgID;			 //对称算法标识，限定ECB模式
	ULONG ulBits;				 //加密密钥对的密钥位长度
	BYTE cbEncryptedPriKey[64];	 //加密密钥对私钥的密文
	ECCPUBLICKEYBLOB PubKey;	 //加密密钥对的公钥
	ECCCIPHERBLOB ECCCipherBlob; //用保护公钥加密的对称密钥密文
} ENVELOPEDKEYBLOB, *PENVELOPEDKEYBLOB;
//文件属性
typedef struct Struct_FILEATTRIBUTE
{
	CHAR FileName[32];
	ULONG FileSize;
	ULONG ReadRights;
	ULONG WriteRights;
} FILEATTRIBUTE, *PFILEATTRIBUTE;
#pragma pack()

//权限类型
#define SECURE_NEVER_ACCOUNT 0x00000000	 //不允许
#define SECURE_ADM_ACCOUNT 0x00000001	 //管理员权限
#define SECURE_USER_ACCOUNT 0x00000010	 //用户权限
#define SECURE_ANYONE_ACCOUNT 0x000000ff //任何人
//设备状态
#define DEV_ABSENT_STATE 0x00000000	 //设备不存在
#define DEV_PRESENT_STATE 0x00000001 //设备存在
#define DEV_UNKNOW_STATE 0x00000002	 //设备状态未知

//扩展
#define RSA_MODULUS_LEN_EX 512
//RSA公钥数据扩展结构
typedef struct Struct_RSAPUBLICKEYBLOBX
{
	ULONG AlgID;							   //算法标识号
	ULONG BitLen;							   //模数的实际位长度,必须是8的倍数
	BYTE Modulus[RSA_MODULUS_LEN_EX];	   //模数 n = p * q ,实际长度为BitLen/8字节
	BYTE PublicExponent[MAX_RSA_EXPONENT_LEN]; //公开密钥 e 一般为 00010001
} RSAPUBLICKEYBLOBEX, *PRSAPUBLICKEYBLOBEX;
//RSA私钥数据扩展结构
typedef struct Struct_RSAPRIVATEKEYBLOBEX
{
	ULONG AlgID;									 //算法标识号
	ULONG BitLen;									 //模数的实际位长度,必须是8的倍数
	BYTE Modulus[RSA_MODULUS_LEN_EX];			 //模数 n = p * q,实际长度为 BitLen/8字节
	BYTE PublicExponent[MAX_RSA_EXPONENT_LEN];		 //公开密钥e,一般为010001
	BYTE PrivateExponent[RSA_MODULUS_LEN_EX];	 //私有密钥d,实际长度为BitLen/8字节
	BYTE Prime1[RSA_MODULUS_LEN_EX / 2];		 //素数 p,实际长度为BitLen/16字节
	BYTE Prime2[RSA_MODULUS_LEN_EX / 2];		 //素数 q,实际长度为BitLen/16字节
	BYTE Prime1Exponent[RSA_MODULUS_LEN_EX / 2]; //d mod (p-1)的值,实际长度为BitLen/16字节
	BYTE Prime2Exponent[RSA_MODULUS_LEN_EX / 2]; //d mod (q -1)的值,实际长度为BitLen/16字节
	BYTE Coefficient[RSA_MODULUS_LEN_EX / 2];	 //q模p的乘法逆元,实际长度为BitLen/16字节
} RSAPRIVATEKEYBLOBEX, *PRSAPRIVATEKEYBLOBEX;

//ECDSA公钥数据结构
#define ECDSA_MAX_MODULUS_BITS_LEN 1024
typedef struct Struct_ECDSAPUBLICKEYBLOB
{
	ULONG BitLen;									  //模数的实际位长度
	BYTE XCoordinate[ECDSA_MAX_MODULUS_BITS_LEN / 8]; //曲线上X的坐标 , 约定:有效位后填充
	BYTE YCoordinate[ECDSA_MAX_MODULUS_BITS_LEN / 8]; //曲线上Y的坐标
} ECDSAPUBLICKEYBLOB, *PECDSAPUBLICKEYBLOB;
//ECDSA私钥数据结构
typedef struct Struct_ECDSACPRIVATEKEYBLOB
{
	ULONG BitLen;									 //模数的实际位长度
	BYTE PrivateKey[ECDSA_MAX_MODULUS_BITS_LEN / 8]; //私有密钥
} ECDSAPRIVATEKEYBLOB, *PECDSAPRIVATEKEYBLOB;
//ECDSA签名数据结构
typedef struct Struct_ECDSASIGNATUREBLOB
{
	BYTE r[ECDSA_MAX_MODULUS_BITS_LEN / 8]; //签名结果的r部分
	BYTE s[ECDSA_MAX_MODULUS_BITS_LEN / 8]; //签名结果的s部分
} ECDSASIGNATUREBLOB, *PECDSASIGNATUREBLOB;

	//-------------------------设备管理系列函数--------------------------------------
	/**
* @brief 等待设备插拔事件
* @note  功能描述：该函数等待设备插入或者拔除事件。szDevName 返回发生事件的设备名称。
* 
* @param[OUT]     szDevName       发生事件的设备名称。  
* @param[IN,OUT]  pulDevNameLen   输入/输出参数，当输入时表示缓冲区长度，输出时表示设备名称的有效长度,长度包含字符串结束符。
* @param[OUT]     pulEvent        事件类型。1 表示插入，2 表示拔出。
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*/
ULONG DEVAPI SKF_WaitForDevEvent(LPSTR szDevName, ULONG *pulDevNameLen, ULONG *pulEvent);
	/**
* @brief 取消等待设备插拔事件
* @note  功能描述：该函数取消等待设备插入或者拔除事件。
* 
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*/
ULONG DEVAPI SKF_CancelWaitForDevEvent();
	/**
* @brief 枚举设备
* @note  功能描述：获得当前系统中的设备列表。
* 
* @param[IN]      bPresent     为TRUE表示取当前设备状态为存在的设备列表。为FALSE表示取当前驱动支持的设备列表。  
* @param[OUT]     szNameList   设备列表名称。如果参数为NULL，将由pulSize返回所需要的空间大小。每个设备的名称以单个'\0'结束，以双'\0'表示列表结束。
* @param[IN,OUT]  pulSize      输入时表示设备名称列表的缓冲区长度,输出时表示szNameList所占用的空间大小。
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*/
ULONG DEVAPI SKF_EnumDev(BOOL bPresent, LPSTR szNameList, ULONG *pulSize);
	/**
* @brief 连接设备
* @note  功能描述：通过设备名连接设备，返回设备的句柄。
*        
* @param[IN]      szName      设备名称。
* @param[OUT]     phDev       返回设备操作句柄。
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*/
ULONG DEVAPI SKF_ConnectDev(LPSTR szName, DEVHANDLE *phDdev);
	/**
* @brief 断开连接
* @note  功能描述：断开一个已经连接的设备，病释放句柄。
*        
* @param[IN]      hDev       连接设备时返回的设备句柄。
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
* 
* @remark 备注：如果该设备已被锁定，函数应首先解锁该设备。断开连接操作并不影响设备的权限状态。
*/
ULONG DEVAPI SKF_DisConnectDev(DEVHANDLE hDev);
	/**
* @brief 获取设备状态
* @note  功能描述：获取设备是否存在的状态。
*        
* @param[IN]      szDevName      设备名称。 
* @param[OUT]     pulDevState    返回设备状态。
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*/
ULONG DEVAPI SKF_GetDevState(LPSTR szDevName, ULONG *pulDevState);
	/**
* @brief 设置设备标签
* @note  功能描述：设置设备标签。
*        
* @param[IN]      hDdev       连接设备时返回的设备句柄。   
* @param[IN]      szLabel     设备标签字符串。该字符串应小于 32 字节。
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*/
ULONG DEVAPI SKF_SetLabel(DEVHANDLE hDev, LPSTR szLabel);
	/**
* @brief 获取设备信息
* @note  功能描述：获取设备的一些特征信息，包括设备标签、厂商信息、支持的算法等。
*        
* @param[IN]      hDdev       连接设备时返回的设备句柄。   
* @param[OUT]     pDevInfo    返回的设备信息。
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*/
ULONG DEVAPI SKF_GetDevInfo(DEVHANDLE hDev, DEVINFO *pDevInfo);
	/**
* @brief 锁定设备
* @note  功能描述：获得设备的独占使用权。
*        
* @param[IN]      hDdev       连接设备时返回的设备句柄。   
* @param[IN]      pDevInfo    超时时间，单位为毫秒。如果为 0xFFFFFFFF 表示无限等待。
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*/
ULONG DEVAPI SKF_LockDev(DEVHANDLE hDev, ULONG ulTimeOut);
	/**
* @brief 解锁设备
* @note  功能描述：释放对设备的独占使用权。
*        
* @param[IN]      hDdev       连接设备时返回的设备句柄。   
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*/
ULONG DEVAPI SKF_UnlockDev(DEVHANDLE hDev);
	/**
* @brief 设备命令传输
* @note  将命令直接发送给设备，并返回结果。
*        
* @param[IN]      hDdev         设备句柄。
* @param[IN]      pbCommand     设备命令。
* @param[IN]      ulCommandLen  命令长度。
* @param[OUT]     pbData        返回结果数据。
* @param[IN,OUT]  pulDataLen    输入时表示结果数据缓冲区长度，输出时表示结果数据实际长度。
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*/
ULONG DEVAPI SKF_Transmit(DEVHANDLE hDev, BYTE *pbCommand, ULONG ulCommandLen, BYTE *pbData, ULONG *pulDataLen);

	///访问控制系列函数
	/**
* @brief 修改设备认证密钥
*        
* @param[IN]      hDdev       连接设备时返回的设备句柄。
* @param[IN]      pbKeyValue  密钥值。 
* @param[IN]      ulKeyLen    密钥长度。 
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*
* @remark 权限要求：设备认证成功后才能使用。
*/
ULONG DEVAPI SKF_ChangeDevAuthKey(DEVHANDLE hDev, BYTE *pbKeyValue, ULONG ulKeyLen);
	/**
* @brief 设备认证
* @note  认证过程：被认证方获取8字节随机数RND,填充0至16字节得到D0,加密得到结果D1,设备收到D1验证是否正确。
*        
* @param[IN]      hDdev       连接设备时返回的设备句柄。
* @param[IN]      pbAuthData  认证数据。
* @param[IN]      ulLen       认证数据长度。
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*/
ULONG DEVAPI SKF_DevAuth(DEVHANDLE hDev, BYTE *pbAuthData, ULONG ulLen);
	/**
* @brief 修改PIN
* @note  功能描述：调用该函数可以修改Administrator PIN和User PIN。
*        如果原PIN码错误导致验证失败,该函数会返回相应PIN的剩余重试次数，当剩余次数为0时，表示PIN已经锁死。
*        
* @param[IN]      hApplication    应用句柄。
* @param[IN]      ulPINType       PIN类型, 可为ADMIN_TYPE或USER_TYPE。
* @param[IN]      szOldPin        原PIN值。
* @param[IN]      szNewPin        原PIN值。
* @param[OUT]     pulRetryCount   出错后的重试次数。
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*/
ULONG DEVAPI SKF_ChangePIN(HAPPLICATION hApplication, ULONG ulPINType, LPSTR szOldPin, LPSTR szNewPin, ULONG *pulRetryCount);
	/**
* @brief 获取PIN信息
* @note  功能描述：包括最大重试次数、当前剩余重试次数，以及当前PIN是否为出厂默认PIN码。
*        
* @param[IN]      hApplication         应用句柄。
* @param[IN]      ulPINType            PIN类型, 可为ADMIN_TYPE或USER_TYPE。 
* @param[OUT]     pulMaxRetryCount     最大重试次数。
* @param[OUT]     pulRemainRetryCount  当前剩余重试次数，当为0时表示已锁死。
* @param[OUT]     pbDefaultPin         是否为出厂默认PIN码。
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*/
ULONG DEVAPI SKF_GetPINInfo(HAPPLICATION hApplication, ULONG ulPINType, ULONG *pulMaxRetryCount, ULONG *pulRemainRetryCount, BOOL *pbDefaultPin);
	/**
* @brief 校验PIN
* @note  功能描述：校验成功后，会获得相应的权限，如果PIN码错误，会返回PIN码重试次数，当次数为0时表示PIN码已锁死。
*        
* @param[IN]      hApplication     应用句柄。
* @param[IN]      ulPINType       PIN类型, 可为ADMIN_TYPE或USER_TYPE。
* @param[IN]      pulRetryCount   PIN码。
* @param[OUT]     pulRetryCount   出错后的重试次数。
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*/
ULONG DEVAPI SKF_VerifyPIN(HAPPLICATION hApplication, ULONG ulPINType, LPSTR szPIN, ULONG *pulRetryCount);
	/**
* @brief 解锁PIN
* @note  功能描述：当用户的 PIN 码锁死后，通过调用该函数来解锁用户 PIN 码。 解锁后，用户 PIN 码被设置成新值，用户 PIN 码的重试次数也恢复到原值。
*        
* @param[IN]      hApplication    应用句柄。
* @param[IN]      szAdminPIN      管理员 PIN 码。
* @param[IN]      szNewUserPIN    新的用户 PIN 码。
* @param[OUT]     pulRetryCount   管理员 PIN 码错误时，返回剩余重试次数。
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*
* @remark  权限要求：验证完管理员 PIN 才能够解锁用户 PIN 码，如果输入的 Administrator PIN不正确或者已经锁死，会调用失败，并返回 Administrator PIN 的重试次数。 
*/
ULONG DEVAPI SKF_UnblockPIN(HAPPLICATION hApplication, LPSTR szAdminPIN, LPSTR szNewUserPIN, ULONG *pulRetryCount);
	/**
* @brief 清除应用安全状态
*         
* @param[IN]      hApplication     应用句柄。
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*/
ULONG DEVAPI SKF_ClearSecureState(HAPPLICATION hApplication);

	///----------------------------应用管理系列函数-------------------------------
	/**
* @brief 创建应用
*
* @param[IN]      hDdev                连接设备时返回的设备句柄。
* @param[IN]      szAppName            应用名称。
* @param[IN]      szAdminPin           管理员PIN。
* @param[IN]      dwAdminPinRetryCount 管理员PIN最大重试次数。
* @param[IN]      szUserPin            用户PIN。
* @param[IN]      dwUserPinRetryCount  用户PIN最大重试次数。
* @param[IN]      dwCreateFileRights   在该应用下创建文件和容器的权限。
* @param[OUT]     phApplication        应用的句柄。
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*
* @remark  权限要求：需要设备权限
*/
ULONG DEVAPI SKF_CreateApplication(DEVHANDLE hDev, LPSTR szAppName, LPSTR szAdminPin, DWORD dwAdminPinRetryCount, LPSTR szUserPin, DWORD dwUserPinRetryCount, DWORD dwCreateFileRights, HAPPLICATION *phApplication);
	/**
* @brief 枚举应用
*        
* @param[IN]      hDdev         连接设备时返回的设备句柄。 
* @param[OUT]     szAppName     返回应用名称列表,如果参数为空，将由pulSize返回所需内存大小。每个应用以单个'\0'结束,以双'\0'表示列表结束。
* @param[IN,OUT]  pulSize       输入时表示缓冲区长度，输出时返回占用空间大小。
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*/
ULONG DEVAPI SKF_EnumApplication(DEVHANDLE hDev, LPSTR szAppName, ULONG *pulSize);
	/**
* @brief 删除应用 
*        
* @param[IN]      hDdev         连接设备时返回的设备句柄。 
* @param[IN]      szAppName     应用名称。
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*
* @remark 权限要求：需要设备权限
*/
ULONG DEVAPI SKF_DeleteApplication(DEVHANDLE hDev, LPSTR szAppName);
	/**
* @brief 打开应用
*        
* @param[IN]      hDdev         连接设备时返回的设备句柄。 
* @param[IN]      szAppName     应用名称。
* @param[OUT]     phApplication 应用的句柄。
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*/
ULONG DEVAPI SKF_OpenApplication(DEVHANDLE hDev, LPSTR szAppName, HAPPLICATION *phApplication);
	/**
* @brief 关闭应用
*        
* @param[IN]     hApplication    应用句柄。 
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*
* @remark 备注：此函数不影响应用安全状态。
*/
ULONG DEVAPI SKF_CloseApplication(HAPPLICATION hApplication);

	///-----------------------------文件管理系列函数---------------------------------
	/**
* @brief 创建文件
* @note  功能描述：创建文件时要指定文件的名称、大小，以及读写权限。
*        
* @param[IN]     hApplication    应用句柄。 
* @param[IN]     szFileName      文件名称，长度不得大于32个字节。 
* @param[IN]     ulFileSize      文件大小。
* @param[IN]     ulReadRights    文件读权限。
* @param[IN]     ulWriteRights   文件写权限。
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*
* @remark 权限要求：创建文件需要应用指定的创建文件权限。
*/
ULONG DEVAPI SKF_CreateFile(HAPPLICATION hApplication, LPSTR szFileName, ULONG ulFileSize, ULONG ulReadRights, ULONG ulWriteRights);
	/**
* @brief 删除文件
* @note  功能描述：文件删除后，文件中写入的所有信息将丢失。文件在设备中占用的空间将被释放。
*        
* @param[IN]     hApplication    要删除的文件所在的应用句柄。 
* @param[IN]     szFileName      要删除的文件的名称。 
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*
* @remark 权限要求：删除一个文件应具有对该文件的创建权限。
*/
ULONG DEVAPI SKF_DeleteFile(HAPPLICATION hApplication, LPSTR szFileName);
	/**
* @brief 枚举文件
*        
* @param[IN]     hApplication    应用句柄。
* @param[OUT]    szFileList      返回文件名称列表，,如果参数为空，将由pulSize返回所需内存大小。每个文件名称以单个'\0'结束,以双'\0'表示列表结束。
* @param[IN,OUT] pulSize         输入时表示缓冲区长度，输出时返回占用空间大小。
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*/
ULONG DEVAPI SKF_EnumFiles(HAPPLICATION hApplication, LPSTR szFileList, ULONG *pulSize);
	/**
* @brief 获取文件属性
*        
* @param[IN]     hApplication    应用句柄。 
* @param[IN]     szFileName      文件名称。
* @param[OUT]    pFileInfo       文件信息。 
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*/
ULONG DEVAPI SKF_GetFileInfo(HAPPLICATION hApplication, LPSTR szFileName, FILEATTRIBUTE *pFileInfo);
	/**
* @brief 读文件
*        
* @param[IN]     hApplication    应用句柄。 
* @param[IN]     szFileName      文件名称。
* @param[IN]     ulOfffset       文件读取偏移位置。
* @param[IN]     ulSize          要读取文件的长度。
* @param[OUT]    pbOutData       返回数据的缓冲区。
* @param[IN,OUT] pulOutLen       输入时表示缓冲区长度，输出时表示实际读取返回的数据大小。
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*
* @remark 权限要求：须具备该文件的读权限。
*/
ULONG DEVAPI SKF_ReadFile(HAPPLICATION hApplication, LPSTR szFileName, ULONG ulOfffset, ULONG ulSize, BYTE *pbOutData, ULONG *pulOutLen);
	/**
* @brief 写文件      
*        
* @param[IN]     hApplication    应用句柄。 
* @param[IN]     szFileName      文件名称。
* @param[IN]     ulOfffset       写入文件的偏移量。
* @param[IN]     pbData          写入数据的缓冲区。
* @param[IN]     ulSize          写入数据的大小。
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*
* @remark 权限要求：须具备该文件的读权限。
*/
ULONG DEVAPI SKF_WriteFile(HAPPLICATION hApplication, LPSTR szFileName, ULONG ulOfffset, BYTE *pbData, ULONG ulSize);

	///-----------------------------容器管理系列函数----------------------------------
	/**
* @brief 创建容器
* @note  功能描述：在应用下建立制度名称的容器并返回容器句柄。    
*     
* @param[IN]     hApplication    应用句柄。
* @param[IN]     szContainerName 容器名称,ASCII字符串，最大长度不超过64字节。
* @param[OUT]    pbContainer     返回所建立的容器句柄。
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*
* @remark 权限要求：需要用户权限
*/
ULONG DEVAPI SKF_CreateContainer(HAPPLICATION hApplication, LPSTR szContainerName, HCONTAINER *pbContainer);
	/**
* @brief 删除容器    
*        
* @param[IN]     hApplication    应用句柄。
* @param[IN]     szContainerName 指向删除容器的名称。 
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*
* @remark 权限要求：需要用户权限
*/
ULONG DEVAPI SKF_DeleteContainer(HAPPLICATION hApplication, LPSTR szContainerName);

	/*
* @brief 枚举容器
* @note  功能描述：枚举应用下的所有容器并返回容器名称列表。
*        
* @param[IN]     hApplication    应用句柄。
* @param[OUT]    szContainerName 指向容器名称列表缓冲区，如果此参数为 NULL 时，pulSize表示返回数据所需要缓冲区的长度，如果此参数不为 NULL 时，返回容器名称列表，每个容器名以单个‘\0’为结束，列表以双‘\0’结束。
* @param[IN,OUT] pulSize         调用前表示 szContainerName 缓冲区的长度，返回容器名称列表的长度。
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*/
ULONG DEVAPI SKF_EnumContainer(HAPPLICATION hApplication, LPSTR szContainerName, ULONG *pulSize);
	/**
* @brief 打开容器
*        
* @param[IN]     hApplication    应用句柄。
* @param[IN]     szContainerName 容器名称。
* @param[OUT]    pbContainer     返回打开的的容器句柄。
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*/
ULONG DEVAPI SKF_OpenContainer(HAPPLICATION hApplication, LPSTR szContainerName, HCONTAINER *pbContainer);
	/**
* @brief 关闭容器
*        
* @param[IN]      hContainer     容器句柄。
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*/
ULONG DEVAPI SKF_CloseContainer(HCONTAINER hContainer);
	/**
* @brief 获得容器类型
*        
* @param[IN]      hContainer       容器句柄。
* @param[OUT]     pulContainerType 容器类型，指针指向的值为0表示未定、尚未分配类型或者空容器，为1表示RSA容器，为2表示SM2容器 
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*/
ULONG DEVAPI SKF_GetContainerType(HCONTAINER hContainer, ULONG *pulContainerType);
	/**
* @brief 导入数字证书
*        
* @param[IN]      hContainer       容器句柄。
* @param[IN]      bSignFlag        TRUE表示签名证书，FALSE表示加密证书。
* @param[IN]      pbCert           指向证书内容缓冲区。
* @param[IN]      ulCertLen        证书长度。
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*/
ULONG DEVAPI SKF_ImportCertificate(HCONTAINER hContainer, BOOL bSignFlag, BYTE *pbCert, ULONG ulCertLen);
	/**
* @brief 导出数字证书
*        
* @param[IN]      hContainer       容器句柄。
* @param[IN]      bSignFlag        TRUE表示签名证书，FALSE表示加密证书。
* @param[IN]      pbCert           指向证书内容缓冲区，如果此参数为NULL时，pulCertLen表示返回数据所需缓冲区长度，否则返回证书内容。
* @param[IN/OUT]  pulCertLen       输入时表示pbCert缓冲区的长度，输出时表示证书内容的长度。 
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*/
ULONG DEVAPI SKF_ExportCertificate(HCONTAINER hContainer, BOOL bSignFlag, BYTE *pbCert, ULONG *pulCertLen);

	///------------------------------密码服务系列函数-----------------------------------
	/**
* @brief 生成随机数
* @note  产生指定长度的随机数 
* 
* @param[IN]      hDev        设备句柄。
* @param[OUT]     pbRandom    返回的随机数。
* @param[IN]      ulRandomLen 随机数长度。
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*/
ULONG DEVAPI SKF_GenRandom(DEVHANDLE hDev, BYTE *pbRandom, ULONG ulRandomLen);
	/**
* @brief 生成外部RSA密钥对
* @note  由设备生成RSA密钥对并明文输出。
*        
* @param[IN]      hDev       设备句柄。
* @param[IN]      ulBitsLen  密钥模长。
* @param[OUT]	  pBlob      返回的私钥数据结构。    
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*
* @remark 生成的私钥只用于输出，接口内不做保留和计算。 
*/
ULONG DEVAPI SKF_GenExtRSAKey(DEVHANDLE hDev, ULONG ulBitsLen, RSAPRIVATEKEYBLOB *pBlob);
	/**
* @brief 生成RSA签名密钥对
* @note  生成RSA签名密钥对并输出签名公钥。
*        
* @param[IN]      hContainer       容器句柄。
* @param[IN]      ulBitsLen        密钥模长。
* @param[OUT]	  pBlob            返回的RSA公钥数据结构      
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*
* @remark 权限要求：须具备用户权限。
*/
ULONG DEVAPI SKF_GenRSAKeyPair(HCONTAINER hContainer, ULONG ulBitsLen, RSAPUBLICKEYBLOB *pBlob);
	/**
* @brief 导入RSA加密密钥对
* @note  导入RSA加密公私钥对
*        
* @param[IN]      hContainer         容器句柄。
* @param[IN]      ulSymAlgId         对称算法密钥标识。
* @param[IN]      pbWrappedKey       使用该容器内签名公钥保护的对称算法密钥。
* @param[IN]      ulWrappedKeyLen    保护的对称算法密钥长度
* @param[IN]      pbEncryptedData    对称算法密钥保护的 RSA 加密私钥。私钥的格式遵循 PKCS#1 v2.1: RSA Cryptography Standard 中的私钥格式定义。。
* @param[IN]      ulEncryptedDataLen 对称算法密钥保护的 RSA 加密公私钥对长度。
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*
* @remark 权限要求：须具备用户权限。
*/
ULONG DEVAPI SKF_ImportRSAKeyPair(HCONTAINER hContainer, ULONG ulSymAlgId, BYTE *pbWrappedKey, ULONG ulWrappedKeyLen, BYTE *pbEncryptedData, ULONG ulEncryptedDataLen);
	/**
* @brief RSA签名
* @note  使用hContainer指定容器的签名私钥，对指定数据 pbData 进行数字签名。签名后的结果存放到 pbSignature 缓冲区，设置 pulSignLen 为签名的长度。
*        
* @param[IN]      hContainer    用来签名的私钥所在容器句柄。
* @param[IN]      pbData        被签名的数据。
* @param[IN]      ulDataLen     签名数据长度，应不大于 RSA 密钥模长-11。
* @param[OUT]     pbSignature   存放签名结果的缓冲区指针，如果值为 NULL，用于取得签名结果长度。
* @param[IN,OUT]  pulSignLen    输入为签名结果缓冲区大小，输出为签名结果长度。
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*
* @remark 权限要求：须具备用户权限。
*/
ULONG DEVAPI SKF_RSASignData(HCONTAINER hContainer, BYTE *pbData, ULONG ulDataLen, BYTE *pbSignature, ULONG *pulSignLen);
	/**
* @brief RSA验签
* @note  验证RSA签名。用 pRSAPubKeyBlob 内的公钥值对待验签数据进行验签。 
*        
* @param[IN]      hDev            设备句柄。
* @param[IN]      pRSAPubKeyBlob  公钥数据结构。
* @param[IN]      pbData          待验证签名的数据。
* @param[IN]      ulDataLen       数据长度，应不大于公钥模长-11。
* @param[IN]      pbSignature     待验证的签名值。
* @param[IN]      ulSignLen       签名值长度，必须为公钥模长。
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*/
ULONG DEVAPI SKF_RSAVerify(DEVHANDLE hDev, RSAPUBLICKEYBLOB *pRSAPubKeyBlob, BYTE *pbData, ULONG ulDataLen, BYTE *pbSignature, ULONG ulSignLen);
	/**
* @brief RSA生成并导出会话密钥
* @note 生成会话密钥并用外部公钥加密输出。 
*        
* @param[IN]      hContainer      容器句柄。
* @param[IN]      ulAlgId         会话密钥算法标识。
* @param[IN]      pPubKey         加密会话密钥的 RSA 公钥数据结构。
* @param[OUT]     pbData          导出的加密会话密钥密文，按照 PKCS#1v1.5 要求封装。
* @param[IN,OUT]  pulDataLen      返回导出数据长度。
* @param[OUT]     phSessionKey    导出的密钥句柄。
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*/
ULONG DEVAPI SKF_RSAExportSessionKey(HCONTAINER hContainer, ULONG ulAlgId, RSAPUBLICKEYBLOB *pPubKey, BYTE *pbData, ULONG *pulDataLen, HANDLE *phSessionKey);
	/**
* @brief RSA外来公钥运算
* @note 使用外部传入的 RSA 公钥对输入数据做公钥运算并输出结果。
*        
* @param[IN]        hDev            设备句柄。
* @param[IN]        pRSAPubKeyBlob  RSA 公钥数据结构。
* @param[IN]        pbInput         指向待运算的原始数据缓冲区。
* @param[IN]        ulInputLen      待运算原始数据的长度，必须为公钥模长。
* @param[OUT]       pbOutput        指向 RSA 公钥运算结果缓冲区，如果该参数为NULL，则由 pulOutputLen 返回运算结果的实际长度。
* @param[IN,OUT]    pulOutputLen    调用前表示 pbOutput 缓冲区的长度，返回RSA 公钥运算结果的实际长度。
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*/
ULONG DEVAPI SKF_ExtRSAPubKeyOperation(DEVHANDLE hDev, RSAPUBLICKEYBLOB *pRSAPubKeyBlob, BYTE *pbInput, ULONG ulInputLen, BYTE *pbOutput, ULONG *pulOutputLen);
	/**
* @brief  RSA外来私钥运算
* @note   直接使用外部传入的 RSA 私钥对输入数据做私钥运算并输出结果。
*        
* @param[IN]        hDev            设备句柄。
* @param[IN]        pRSAPriKeyBlob  RSA 私钥数据结构,需要填充公钥信息。
* @param[IN]        pbInput         指向待运算数据缓冲区。
* @param[IN]        ulInputLen      待运算数据的长度，必须为公钥模长。
* @param[OUT]       pbOutput        RSA 私钥运算结果，如果该参数为 NULL，则由pulOutputLen 返回运算结果的实际长度。
* @param[IN,OUT]    pulOutputLen    调用前表示 pbOutput 缓冲区的长度，返回RSA 私钥运算结果的实际长度。
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*/
ULONG DEVAPI SKF_ExtRSAPriKeyOperation(DEVHANDLE hDev, RSAPRIVATEKEYBLOB *pRSAPriKeyBlob, BYTE *pbInput, ULONG ulInputLen, BYTE *pbOutput, ULONG *pulOutputLen);
	/**
* @brief  生成ECC签名密钥对
* @note   生成ECC签名密钥对并输出签名公钥   
*        
* @param[IN]      hContainer        密钥容器句柄。
* @param[IN]      ulAlgId           算法标识，只支持SGD_SM2_1算法。
* @param[OUT]     pBlob             返回ECC公钥数据结构。      
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*
* @remark 权限要求：需要用户权限
*/
ULONG DEVAPI SKF_GenECCKeyPair(HCONTAINER hContainer, ULONG ulAlgId, PECCPUBLICKEYBLOB pBlob);
	/**
* @brief 导入ECC公私钥对    
*        
* @param[IN]      hContainer        密钥容器句柄。
* @param[IN]      pEenvlopedKeyBlob 受保护的加密密钥对。
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*
* @remark 权限要求：需要用户权限
*/
ULONG DEVAPI SKF_ImportECCKeyPair(HCONTAINER hContainer, PENVELOPEDKEYBLOB pEenvlopedKeyBlob);
	/**
* @brief ECC签名
*        
* @param[IN]      hContainer        密钥容器句柄。
* @param[IN]      pbData            待签名的数据。
* @param[IN]      ulDataLen         待签名的数据长度，必须小于密钥模长。
* @param[OUT]     pSignature		签名值。
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*
* @remark 权限要求：需要用户权限。
*        输入数据位待签数据的杂凑值,使用SM2算法时,该输入数据位待签名数据经过SM2签名预处理的结果。
*/
ULONG DEVAPI SKF_ECCSignData(HCONTAINER hContainer, BYTE *pbData, ULONG ulDataLen, PECCSIGNATUREBLOB pSignature);
	/**
* @brief ECC验签
* @note  输入数据位待签数据的杂凑值,使用SM2算法时,该输入数据位待签名数据经过SM2签名预处理的结果。
*        
* @param[IN]      hDev            设备句柄。
* @param[IN]      pECCPubKeyBlob  ECC公钥数据结构。
* @param[IN]      pbData          待验证签名的数据。
* @param[IN]      ulDataLen       数据长度。
* @param[IN]      pSignature      待验证签名值。
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*/
ULONG DEVAPI SKF_ECCVerify(DEVHANDLE hDev, PECCPUBLICKEYBLOB pECCPubKeyBlob, BYTE *pbData, ULONG ulDataLen, PECCSIGNATUREBLOB pSignature);
	/**
* @brief ECC生成并到处会话密钥
* @note  功能描述：生成会话密钥并用外部公钥加密导出。
*        
* @param[IN]      hContainer        容器句柄。
* @param[IN]      ulAlgId           会话密钥算法标识。
* @param[IN]      pPubKey           外部输入的公钥结构。
* @param[OUT]     pData             会话密钥密文。
* @param[OUT]     phSessionKey      会话密钥句柄。
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*/
ULONG DEVAPI SKF_ECCExportSessionKey(HCONTAINER hContainer, ULONG ulAlgId, PECCPUBLICKEYBLOB pPubKey, PECCCIPHERBLOB pData, HANDLE *phSessionKey);
	/**
* @brief ECC外来公钥加密
* @note   功能描述:使用外部传入的 ECC 公钥对输入数据做加密运算并输出结果。
*        
* @param[IN]      hDev            设备句柄。
* @param[IN]      pECCPubkeyBlob  ECC公钥数据结构。
* @param[IN]      pbPlainText     待加密的明文数据。
* @param[IN]      ulPlainTextLen  待加密的明文数据长度。
* @param[OUT]     pCipherText     密文数据。    
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*/
ULONG DEVAPI SKF_ExtECCEncrypt(DEVHANDLE hDev, PECCPUBLICKEYBLOB pECCPubkeyBlob, BYTE *pbPlainText, ULONG ulPlainTextLen, PECCCIPHERBLOB pCipherText);
	/**
* @brief ECC外来私钥解密
* @note   功能描述:使用外部传入的 ECC 私钥对输入数据做解密运算并输出结果。
*        
* @param[IN]      hDev            设备句柄。
* @param[IN]      pECCPriKeyBlob  ECC 私钥数据结构。
* @param[IN]      pCipherText     待解密的密文数据。
* @param[OUT]     pbPlainText     返回明文数据，如果该参数为 NULL，则由pulPlainTextLen 返回明文数据的实际长度。
* @param[IN,OUT]  pulPlainTextLen 调用前表示pbPlainText 缓冲区的长度，返回明文数据的实际长度。 
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*/
ULONG DEVAPI SKF_ExtECCDecrypt(DEVHANDLE hDev, ECCPRIVATEKEYBLOB *pECCPriKeyBlob, PECCCIPHERBLOB pCipherText, BYTE *pbPlainText, ULONG *pulPlainTextLen);
	/**
* @brief ECC外来私钥签名
* @note   功能描述:使用外部传入的 ECC 私钥对输入数据做签名运算并输出结果。
*        
* @param[IN]      hDev            设备句柄。
* @param[IN]      pECCPriKeyBlob  ECC 私钥数据结构。
* @param[IN]      pbData          待签名数据。 
* @param[IN]      ulDataLen       待签名数据的长度。 
* @param[OUT]     pSignature      签名值。     
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*/
ULONG DEVAPI SKF_ExtECCSign(DEVHANDLE hDev, ECCPRIVATEKEYBLOB *pECCPriKeyBlob, BYTE *pbData, ULONG ulDataLen, PECCSIGNATUREBLOB pSignature);
	/**
* @brief ECC外来公钥验签
* @note   功能描述:外部使用传入的ECC公钥做签名验证。  
*
* @param[IN]     hDev           设备句柄。
* @param[IN]     pECCPubKeyBlob ECC公钥数据结构。
* @param[IN]     pbData         待验证数据。
* @param[IN]     ulDataLen      待验证数据的长度。 
* @param[IN]     pSignature     签名值。 
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*/
ULONG DEVAPI SKF_ExtECCVerify(DEVHANDLE hDev, PECCPUBLICKEYBLOB pECCPubKeyBlob, BYTE *pbData, ULONG ulDataLen, PECCSIGNATUREBLOB pSignature);
	/**
* @brief ECC生成密钥协商参数并输出
* @note  使用 ECC 密钥协商算法，为计算会话密钥而产生协商参数，返回临时 ECC 密钥对的公钥及协商句柄。   
*
* @param[IN]     hContainer           容器句柄。
* @param[IN]     ulAlgId              会话密钥算法标识。
* @param[OUT]    pTempECCPubKeyBlob   发起方临时 ECC 公钥。
* @param[IN]     pbID                 发起方的ID。
* @param[IN]     ulIDLen              发起方 ID 的长度，不大于 32。
* @param[OUT]    phAgreementHandle    返回的密钥协商句柄。
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
* 
* @remark 为协商会话密钥，协商的发起方应首先调用本函数
*/
ULONG DEVAPI SKF_GenerateAgreementDataWithECC(HCONTAINER hContainer, ULONG ulAlgId, ECCPUBLICKEYBLOB *pTempECCPubKeyBlob, BYTE *pbID, ULONG ulIDLen, HANDLE *phAgreementHandle);
	/**
* @brief ECC产生协商数据并计算会话密钥
* @note  使用 ECC 密钥协商算法，产生协商参数并计算会话密钥，输出临时 ECC 密钥对公钥，并返回产生的密钥句柄。    
*
* @param[IN]     hContainer                容器句柄。
* @param[IN]     ulAlgId                   会话密钥算法标识。
* @param[IN]     pSponsorECCPubKeyBlob     发起方的 ECC 公钥。
* @param[IN]     pSponsorTempECCPubKeyBlob 发起方的临时 ECC 公钥。
* @param[OUT]    pTempECCPubKeyBlob        响应方的临时 ECC 公钥。
* @param[IN]     pbID                      响应方的 ID。
* @param[IN]     ulIDLen                   响应方 ID 的长度，不大于 32。
* @param[IN]     pbSponsorID               发起方的 ID。
* @param[IN]     ulSponsorIDLen            发起方 ID 的长度，不大于 32。
* @param[OUT]     phKeyHandle              返回的对称算法密钥句柄。
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*
* @remark 本函数由响应方调用
*/
ULONG DEVAPI SKF_GenerateAgreementDataAndKeyWithECC(HANDLE hContainer, ULONG ulAlgId, ECCPUBLICKEYBLOB *pSponsorECCPubKeyBlob, ECCPUBLICKEYBLOB *pSponsorTempECCPubKeyBlob, ECCPUBLICKEYBLOB *pTempECCPubKeyBlob, BYTE *pbID, ULONG ulIDLen, BYTE *pbSponsorID, ULONG ulSponsorIDLen, HANDLE *phKeyHandle);
	/**
* @brief ECC计算会话密钥
* @note  使用 ECC 密钥协商算法，使用自身协商句柄和响应方的协商参数计算会话密钥，同时返回会话密钥句柄。    
*
* @param[IN]     hAgreementHandle    密钥协商句柄。
* @param[IN]     pECCPubKeyBlob      外部输入的响应方 ECC 公钥。
* @param[IN]     pTempECCPubKeyBlob  外部输入的响应方临时 ECC 公钥。
* @param[IN]     pbID                响应方的 ID。
* @param[IN]     ulIDLen             响应方 ID 的长度，不大于 32。
* @param[OUT]     phKeyHandle        返回的密钥句柄。
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*
* @remark 协商的发起方获得响应方的协商参数后调用本函数，计算会话密钥。
*/
ULONG DEVAPI SKF_GenerateKeyWithECC(HANDLE hAgreementHandle, ECCPUBLICKEYBLOB *pECCPubKeyBlob, ECCPUBLICKEYBLOB *pTempECCPubKeyBlob, BYTE *pbID, ULONG ulIDLen, HANDLE *phKeyHandle);
	/**
* @brief 导出公钥
* @note  功能描述：导出容器中的签名公钥或加密公钥
*        
* @param[IN]      hContainer        密钥容器句柄。
* @param[IN]      bSignFlag         TRUE表示导出签名公钥，FALSE表示导出加密公钥。
* @param[OUT]     pbBlob            指向RSA公钥结构或者ECC公钥结构，如果此参数为NULL，由pulBlobLen返回的长度
* @param[IN,OUT]  pulBlobLen        输入时表示pbBlob缓冲区长度，输出时表示导出公钥结构大小。
*
* @retval SAR_OK:              成功。
* @retval SAR_ BAD_SIGNATURE： 验证失败。
* @retval 其他：               错误码。
*/
ULONG DEVAPI SKF_ExportPublicKey(HCONTAINER hContainer, BOOL bSignFlag, BYTE *pbBlob, ULONG *pulBlobLen);
	/**
* @brief 导入会话密钥
* @note  功能描述：导入会话密钥密文，使用容器中加密私钥解密。
*        
* @param[IN]      hContainer        密钥容器句柄。
* @param[IN]      ulAlgId           会话密钥算法标识。
* @param[IN]      pbWrapedData      要导入的会话密钥密文。当容器为ECC类型时，此参数为ECCCIPHERBLOB密文数据,当容器为RSA类型时，此参数为RSA公钥加密后的数据。
* @param[IN]      ulWrapedLen       会话密钥密文长度。
* @param[OUT]     phKey             返回会话密钥句柄。
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*
* @remark 权限要求：用户权限。
*/
ULONG DEVAPI SKF_ImportSessionKey(HCONTAINER hContainer, ULONG ulAlgId, BYTE *pbWrapedData, ULONG ulWrapedLen, HANDLE *phKey);
	/**
* @brief 明文导入会话密码
* @note  功能描述：设置明文对称密钥，返回密钥句柄。 
*        
* @param[IN]      hDev       设备句柄。
* @param[IN]      pbKey      指向会话密钥值的缓冲区。
* @param[IN]      ulAlgID    会话密钥算法标识。
* @param[OUT]     phKey      返回会话密钥句柄。
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*/
ULONG DEVAPI SKF_SetSymmKey(DEVHANDLE hDev, BYTE *pbKey, ULONG ulAlgID, HANDLE *phKey);
	/**
* @brief 加密初始化
* @note  功能描述：设置数据加密的算法相关参数
*        
* @param[IN]      hKey         加密密钥句柄。
* @param[IN]      EncryptParam 分组密钥算法相关参数。
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*/
ULONG DEVAPI SKF_EncryptInit(HANDLE hKey, BLOCKCIPHERPARAM EncryptParam);
	/**
* @brief 单组数据加密
* @note  功能描述：单一分组数据的加密操作。在调用SKF_Encrypt之前必须先调用SKF_EncryptInit初始化。
*        
* @param[IN]      hKey            加密密钥句柄。
* @param[IN]      pbData          待加密数据。
* @param[IN]      ulDataLen       待加密数据长度。
* @param[OUT]     pbEncryptedData 加密后的数据缓冲区，可以为NULL，用于获得加密后数据长度。
* @param[IN,OUT]  pulEncryptedLen 输入时表示缓冲区长度，输出时表示结果数据实际长度。
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*/
ULONG DEVAPI SKF_Encrypt(HANDLE hKey, BYTE *pbData, ULONG ulDataLen, BYTE *pbEncryptedData, ULONG *pulEncryptedLen);
	/**
* @brief 多组数据加密
* @note  功能描述：对多个分组数据进行加密。在调用SKF_EncryptUpdate之前必须先调用SKF_EncryptInit，在调用SKF_EncryptUpdate之后，必须调用SKF_EncryptFinal。
*        
* @param[IN]      hKey            加密密钥句柄。
* @param[IN]      pbData          待加密数据。
* @param[IN]      ulDataLen       待加密数据长度。
* @param[OUT]     pbEncryptedData 加密后的数据缓冲区指针。
* @param[OUT]     pulEncryptedLen 返回加密后的数据长度。
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*/
ULONG DEVAPI SKF_EncryptUpdate(HANDLE hKey, BYTE *pbData, ULONG ulDataLen, BYTE *pbEncryptedData, ULONG *pulEncryptedLen);
	/**
* @brief 结束加密
* @note  功能描述：结束多个分组的数据加密，返回剩余加密结果。先调用SKF_EncryptInit初始化，再调用SKF_EncryptUpdate对多个分组加密，最后调用SKF_EncryptFinal结束多个分组数据加密。
*        
* @param[IN]      hKey            加密密钥句柄。
* @param[OUT]     pbEncryptedData 加密结果的缓冲区。
* @param[OUT]     pulEncryptedLen 加密结果的长度。
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*/
ULONG DEVAPI SKF_EncryptFinal(HANDLE hKey, BYTE *pbEncryptedData, ULONG *pulEncryptedLen);
	/**
* @brief 解密初始化
* @note  功能描述：设置数据解密的算法相关参数
*        
* @param[IN]      hKey         解密密钥句柄。
* @param[IN]      EncryptParam 分组密钥算法相关参数。
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*/
ULONG DEVAPI SKF_DecryptInit(HANDLE hKey, BLOCKCIPHERPARAM EncryptParam);
	/**
* @brief 单组数据解密
* @note  功能描述：单一分组数据的解密操作。在调用SKF_Decrypt之前必须先调用SKF_DecryptInit初始化。
*        
* @param[IN]      hKey            解密密钥句柄。
* @param[IN]      pbEncryptedData 待解密数据。
* @param[IN]      ulEncryptedLen  待解密数据长度。
* @param[OUT]     pbData          解密后的数据缓冲区，可以为NULL，用于获得加密后数据长度。
* @param[IN,OUT]  pulDataLen      输入时表示缓冲区长度，输出时表示结果数据实际长度。
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*/
ULONG DEVAPI SKF_Decrypt(HANDLE hKey, BYTE *pbEncryptedData, ULONG ulEncryptedLen, BYTE *pbData, ULONG *pulDataLen);
	/**
* @brief 分组数据解密
* @note  功能描述：对多个分组数据进行解密。在调用SKF_DecryptUpdate之前必须先调用SKF_DecryptInit，在调用SKF_DecryptUpdate之后，必须调用SKF_DecryptFinal。
*        
* @param[IN]      hKey            解密密钥句柄。
* @param[IN]      pbEncryptedData 待解密数据。
* @param[IN]      ulEncryptedLen  待解密数据长度。
* @param[OUT]     pbData          解密后的数据缓冲区指针。
* @param[IN,OUT]  pulDataLen      输入时表示缓冲区长度，输出时表示结果数据实际长度。
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*/
ULONG DEVAPI SKF_DecryptUpdate(HANDLE hKey, BYTE *pbEncryptedData, ULONG ulEncryptedLen, BYTE *pbData, ULONG *pulDataLen);
	/**
* @brief 结束多个分组的解密
* @note  功能描述：先调用SKF_DecryptInit初始化解密操作，再调用SKF_DecryptUpdate对多个分组进行解密，最后调用SKF_DecryptFinal结束多个分组数据的解密。
*        
* @param[IN]      hKey                解密密钥句柄。
* @param[OUT]     pbDecryptedData     指向解密结果的缓冲区，如果此参数为NULL时，由pulDecryptedDataLen返回解密结果的长度
* @param[IN,OUT]  pulDecryptedDataLen 输入时表示缓冲区长度，输出时表示解密结果长度。
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*/
ULONG DEVAPI SKF_DecryptFinal(HANDLE hKey, BYTE *pbDecryptedData, ULONG *pulDecryptedDataLen);
	/**
* @brief 密码杂凑初始化
*        
* @param[IN]      hDev        设备句柄。
* @param[IN]      ulAlgID     密码杂凑算法标识。
* @param[IN]      pPubKey     签名者公钥。当ulAlgID为SGD_SM3时有效。
* @param[IN]      pucID       签名者ID值。当ulAlgID为SGD_SM3时有效。
* @param[IN]      ulIDLen     签名者ID的长度。当ulAlgID为SGD_SM3时有效。
* @param[OUT]     phHash      密码杂凑对象句柄。 
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*
* @remark 当ulAlgID为SGD_SM3且ulIDLen不为0的情况下，pPubKey、pucID有效，执行SM2算法签名预处理1操作。
*/
ULONG DEVAPI SKF_DigestInit(DEVHANDLE hDev, ULONG ulAlgID, PECCPUBLICKEYBLOB pPubKey, unsigned char *pucID, ULONG ulIDLen, HANDLE *phHash);
	/**
* @brief 单组数据密码杂凑
* @note  功能描述：对单一分组的消息进行密码杂凑计算。调用SKF_Digest之前必须调用SKF_DigestInit初始化。
*        
* @param[IN]      hHash        杂凑对象句柄
* @param[IN]      pbData       指向消息数据的缓冲区
* @param[IN]      ulDataLen    消息数据的长度
* @param[OUT]     pbHashData   杂凑数据缓冲区指针，当此参数为NULL 时，由pulHashLen返回杂凑结果的长度
* @param[IN,OUT]  pulHashLen   调用时表示pbHashData 缓冲区的长度，返回杂凑结果的长度
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*
* @remark 调用 SKF_Digest 之前，必须调用 SKF_DigestInit 初始化杂凑计算操作。SKF_Digest等价于多次调用 SKF_DigestUpdate 之后再调用 SKF_DigestFinal。
*/
ULONG DEVAPI SKF_Digest(HANDLE hHash, BYTE *pbData, ULONG ulDataLen, BYTE *phHashData, ULONG *pulHashLen);
	/**
* @brief 分组数据密码杂凑
* @note  功能描述：对多个分组数据进行密码杂凑运算。调用SKF_DigestUpdate之前必须调用SKF_DigestInit；调用SKF_DigestUpdate之后必须调用SKF_DigestFinal。
*        
* @param[IN]      hHash        密码杂凑对象句柄。
* @param[IN]      pbData       指向消息数据的缓冲区。
* @param[IN]      ulDataLen    消息数据的长度。
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*
* @remark 调用 SKF_DigestUpdate 之前，必须调用 SKF_DigestInit 初始化杂凑计算操作；调用 SKF_DigestUpdate 之后，必须调用SKF_DigestFinal 结束杂凑计算操作。
*/
ULONG DEVAPI SKF_DigestUpdate(HANDLE hHash, BYTE *pbData, ULONG ulDataLen);
	/**
* @brief 结束密码杂凑
* @note  功能描述：结束多个分组的密码杂凑计算，将结果保存到指定的缓冲区。
*        
* @param[IN]      hHash        密码杂凑对象句柄。
* @param[OUT]     pHashData    返回的密码杂凑结果缓冲区指针，如果此参数为NULL，由pulHashLen返回杂凑结果长度。
* @param[IN,OUT]  pulHashLen   输入时表示缓冲区长度，输出时表示密码杂凑结果的长度。
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*
* @remark SKF_DigestFinal 必须用于 SKF_DigestUpdate 之后。
*/
ULONG DEVAPI SKF_DigestFinal(HANDLE hHash, BYTE *pHashData, ULONG *pulHashLen);
	/**
* @brief 消息鉴别码运算初始化
* @note  功能描述：初始化消息鉴别码计算操作，设置计算消息鉴别码的密钥参数，并返回消息鉴别码句柄。
*        
* @param[IN]      hKey       计算消息鉴别码的密钥句柄。
* @param[IN]      pMacParam  消息认证计算相关参数，包括初始向量、初始向量长度、填充方法等。 
* @param[OUT]     phMac      消息鉴别码对象句柄。
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*
* @remark 消息鉴别码计算采用分组加密算法的 CBC 模式，将加密结果的最后一块作为计算结果。待计算数据的长度必须是分组加密算法块长的倍数，接口内部不作数据填充。
*/
ULONG DEVAPI SKF_MacInit(HANDLE hKey, BLOCKCIPHERPARAM *pMacParam, HANDLE *phMac);
	/**
* @brief 单组数据消息鉴别码运算
* @note  功能描述：SKF_Mac 计算单一分组数据的消息鉴别码。
*        
* @param[IN]      hMac       消息鉴别码句柄。
* @param[IN]      pbData     指向待计算数据的缓冲区。 
* @param[IN]      ulDataLen  待计算数据的长度。
* @param[OUT]     pbMacData  指向计算后的 Mac 结果，如果此参数为 NULL 时，由 pulMacLen返回计算后 Mac 结果的长度。
* @param[IN,OUT]  pulMacLen  调用时表示 pbMacData 缓冲区的长度，返回计算 Mac 结果的长度。 
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*
* @remark 调用 SKF_Mac 之前，必须调用 SKF_MacInit 初始化消息鉴别码计算操作。SKF_Mac等价于多次调用 SKF_MacUpdate 之后再调用 SKF_MacFinal。
*/
ULONG DEVAPI SKF_Mac(HANDLE hMac, BYTE *pbData, ULONG ulDataLen, BYTE *pbMacData, ULONG *pulMacLen);
	/**
* @brief 多组数据消息鉴别码运算
* @note  功能描述：计算多个分组数据的消息鉴别码。
*        
* @param[IN]      hMac       消息鉴别码句柄。
* @param[IN]      pbData     指向待计算数据的缓冲区。 
* @param[IN]      ulDataLen  待计算数据的长度。
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*
* @remark 调用 SKF_MacUpdate 之前，必须调用 SKF_MacInit 初始化消息鉴别码计算操作；调用 SKF_MacUpdate 之后，必须调用 SKF_MacFinal 结束多个分组数据的消息鉴别码计算操作。
*/
ULONG DEVAPI SKF_MacUpdate(HANDLE hMac, BYTE *pbData, ULONG ulDataLen);
	/**
* @brief 结束消息鉴别码运算
* @note  功能描述：结束多个分组数据的消息鉴别码计算操作。
*        
* @param[IN]      hMac           消息鉴别码句柄。
* @param[OUT]     pbMacData      指向消息鉴别码的缓冲区，当此参数为 NULL 时，由pulMacDataLen 返回消息鉴别码返回的长度。  
* @param[OUT]     pulMacDataLen  调用时表示消息鉴别码缓冲区的最大长度，返回消息鉴别码的长度。 
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*
* @remark SKF_MacFinal 必须用于 SKF_MacUpdate 之后。
*/
ULONG DEVAPI SKF_MacFinal(HANDLE hMac, BYTE *pbMacData, ULONG *pulMacDataLen);
	/**
* @brief 关闭密码对象句柄
* @note  功能描述：关闭会话密钥、密码杂凑对象、MAC对象、ECC密钥协商等句柄
*        
* @param[IN]      hHandle        要关闭的对象句柄。
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*/
ULONG DEVAPI SKF_CloseHandle(HANDLE hHandle);

	///-------------------------非标准接口函数--------------------------------------

	/**
* @brief 验证指纹
* @note  功能描述：校验指纹获取对应权限
*
* @param[IN]      hApplication    应用句柄
* @param[IN]	  ulPINType		  PIN类型, 可为ADMIN_TYPE或USER_TYPE。
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*/
ULONG DEVAPI SKF_VerifyFinger(HAPPLICATION hApplication, ULONG ulPINType);

	/**
* @brief 取消指纹验证
* @note  功能描述：等待指纹验证状态下取消指纹验证
*
* @param[IN]      hApplication    应用句柄
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*/
ULONG DEVAPI SKF_CancelVerifyFinger(HAPPLICATION hApplication);

	/**
* @brief 查询指纹
* @note  功能描述：查询是否存在对应角色的指纹
*
* @param[IN]      hApplication    应用句柄
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*/
	BOOL DEVAPI SKF_HasFinger(HAPPLICATION hApplication, ULONG ulPINType);

	/**
* @brief RSA私钥解密
* @note  功能描述：使用内部RSA加密私钥对输入数据做解密运算并输出结果
*
* @param[IN]		hContainer			容器句柄
* @param[IN]		pbCipherText		待解密的密文数据
* @param[IN]		ulCipherTextLen		待解密密文数据长度
* @param[OUT]		pbPlainText			返回明文数据,如果该参数为NULL，则由pulPlainTextLen返回明文数据的实际长度。
* @param[IN，OUT]	pulPlainTextLen		输入时表示pbPlainText缓冲区的长度，输出时表示明文数据的实际长度。
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*/
ULONG DEVAPI SKF_RSADecrypt(HCONTAINER hContainer, BYTE *pbCipherText, ULONG ulCipherTextLen, BYTE *pbPlainText, ULONG *pulPlainTextLen);

	/**
* @brief ECC私钥解密
* @note  功能描述：使用内部ECC加密私钥对输入数据做解密运算并输出结果
*
* @param[IN]		hContainer			容器句柄
* @param[IN]		pCipherText			待解密的密文数据
* @param[OUT]		pbPlainText			返回明文数据,如果该参数为NULL，则由pulPlainTextLen返回明文数据的实际长度。
* @param[IN，OUT]	pulPlainTextLen		输入时表示pbPlainText缓冲区的长度，输出时表示明文数据的实际长度。
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*/
ULONG DEVAPI SKF_ECCDecrypt(HCONTAINER hContainer, PECCCIPHERBLOB pCipherText, BYTE *pbPlainText, ULONG *pulPlainTextLen);
ULONG DEVAPI SKF_ECCPrvKeyDecrypt(HCONTAINER hContainer, PECCCIPHERBLOB pCipherText, BYTE *pbData, ULONG *pulDataLen);

	/**
* @brief 导入CA证书
* @note  功能描述：向容器内导入CA数字证书
*
* @param[IN]		hContainer			容器句柄
* @param[IN]		pbCert				指向证书内容缓冲区
* @param[IN]		ulCertLen			证书长度
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*/
ULONG DEVAPI SKF_ImportCACertificate(HCONTAINER hContainer, BYTE *pbCert, ULONG ulCertLen);

	/**
* @brief 导出CA证书
* @note  功能描述：从容器内导出数字证书
*
* @param[IN]		hContainer			容器句柄
* @param[OUT]		pbCert				指向证书内容缓冲区，如果此参数为NULL时，pulCertLen表示返回数据所需要缓冲区的长度，如果此参数不为NULL时，返回数字证书内容
* @param[IN/OUT]	ulCertLen			输入时表示pbCert缓冲区的长度，输出时表示证书内容的长度
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*/
ULONG DEVAPI SKF_ExportCACertificate(HCONTAINER hContainer, BYTE *pbCert, ULONG *pulCertLen);

	/**
* @brief  生成ECC加密密钥对
* @note   生成ECC加密密钥对并输出加密公钥
*
* @param[IN]      hContainer        密钥容器句柄。
* @param[IN]      ulAlgId           算法标识，只支持SGD_SM2_3算法。
* @param[OUT]     pBlob             返回ECC公钥数据结构。
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*
* @remark 权限要求：需要用户权限
*/
ULONG DEVAPI SKF_GenECCKeyPairExch(HCONTAINER hContainer, ULONG ulAlgId, ECCPUBLICKEYBLOB *pBlob);

	/**
* @brief 生成RSA加密密钥对
* @note  生成RSA加密密钥对并输出加密公钥。
*
* @param[IN]      hContainer       容器句柄。
* @param[IN]      ulBitsLen        密钥模长。
* @param[OUT]	  pBlob            返回的RSA公钥数据结构
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*
* @remark 权限要求：须具备用户权限。
*/
ULONG DEVAPI SKF_GenRSAKeyPairExch(HCONTAINER hContainer, ULONG ulBitsLen, RSAPUBLICKEYBLOB *pBlob);

	/**
* @brief  生成ECDSA签名密钥对
* @note   生成ECDSA签名密钥对并输出公钥
*
* @param[IN]      hContainer        密钥容器句柄。
* @param[IN]      ulAlgId           算法标识，传入ECDSA对应算法ID。
* @param[OUT]     pBlob             返回ECC公钥数据结构。
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*
* @remark 权限要求：需要用户权限
*/
ULONG DEVAPI SKF_GenECDSAKeyPair(HCONTAINER hContainer, ULONG ulAlgId, PECDSAPUBLICKEYBLOB pBlob);

	/**
* @brief ECDSA签名
*
* @param[IN]      hContainer        密钥容器句柄。
* @param[IN]      ulAlgId           算法标识，传入ECDSA对应算法ID。
* @param[IN]      pbData            待签名的数据,HASH后数据。
* @param[IN]      ulDataLen         待签名的数据长度。
* @param[OUT]     pSignature		签名值。
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*
* @remark 权限要求：需要用户权限。
*/
ULONG DEVAPI SKF_ECDSASignData(HCONTAINER hContainer, ULONG ulAlgId, BYTE *pbData, ULONG ulDataLen, PECDSASIGNATUREBLOB pSignature);

	/**
* @brief ECDSA验签
* @note  输入数据位待签数据的杂凑值,使用SM2算法时,该输入数据位待签名数据经过SM2签名预处理的结果。
*
* @param[IN]      hDev            设备句柄。
* @param[IN]      pECCPubKeyBlob  ECDSA公钥数据结构。
* @param[IN]      pbData          待验证签名的数据。
* @param[IN]      ulDataLen       数据长度。
* @param[IN]      pSignature      待验证签名值。
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*/
ULONG DEVAPI SKF_ECDSAVerify(DEVHANDLE hDev, PECDSAPUBLICKEYBLOB pECCPubKeyBlob, BYTE *pbData, ULONG ulDataLen, PECDSASIGNATUREBLOB pSignature);

	/**
* @brief  明文导入密钥对
* @note   明文导入密钥对,测试接口
*
* @param[IN]      hContainer        密钥容器句柄。
* @param[IN]      bSignFlag         TRUE表示签名密钥对，FALSE表示加密密钥对。
* @param[IN]      eccPub			公钥值
* @param[IN]      eccPri			私钥值
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*
* @remark 权限要求：需要用户权限
*/
ULONG DEVAPI SKF_ImportECCKeyPairEx(HCONTAINER hContainer, BOOL bSignFlag, PECCPUBLICKEYBLOB eccPub, PECCPRIVATEKEYBLOB eccPri);

	/**
* @brief  生成RSA密钥对扩展
* @note   生成RSA密钥对并输出公钥
*
* @param[IN]      hContainer        密钥容器句柄。
* @param[IN]      bSignFlag			密钥类型，TRUE表示签名密钥对，FALSE表示加密密钥对。
* @param[IN]      ulBitsLen         密钥模长
* @param[OUT]     pBlob             返回RSA公钥数据结构。
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*
* @remark 权限要求：需要用户权限
*/
ULONG DEVAPI SKF_GenRSAKeyPairEx(HCONTAINER hContainer, BOOL bSignFlag, ULONG ulBitsLen, RSAPUBLICKEYBLOBEX *pBlob);

	/**
* @brief RSA验签
* @note  验证RSA签名。用 pRSAPubKeyBlob 内的公钥值对待验签数据进行验签。
*
* @param[IN]      hDev            设备句柄。
* @param[IN]      pRSAPubKeyBlob  公钥数据结构。
* @param[IN]      pbData          待验证签名的数据。
* @param[IN]      ulDataLen       数据长度，应不大于公钥模长-11。
* @param[IN]      pbSignature     待验证的签名值。
* @param[IN]      ulSignLen       签名值长度，必须为公钥模长。
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*/
ULONG DEVAPI SKF_RSAVerifyEx(DEVHANDLE hDev, RSAPUBLICKEYBLOBEX *pRSAPubKeyBlob, BYTE *pbData, ULONG ulDataLen, BYTE *pbSignature, ULONG ulSignLen);

	/**
* @brief RSA外来公钥运算
* @note 使用外部传入的 RSA 公钥对输入数据做公钥运算并输出结果。
*
* @param[IN]        hDev            设备句柄。
* @param[IN]        pRSAPubKeyBlob  RSA 公钥数据结构。
* @param[IN]        pbInput         指向待运算的原始数据缓冲区。
* @param[IN]        ulInputLen      待运算原始数据的长度，必须为公钥模长。
* @param[OUT]       pbOutput        指向 RSA 公钥运算结果缓冲区，如果该参数为NULL，则由 pulOutputLen 返回运算结果的实际长度。
* @param[IN,OUT]    pulOutputLen    调用前表示 pbOutput 缓冲区的长度，返回RSA 公钥运算结果的实际长度。
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*/
ULONG DEVAPI SKF_ExtRSAPubKeyOperationEx(DEVHANDLE hDev, RSAPUBLICKEYBLOBEX *pRSAPubKeyBlob, BYTE *pbInput, ULONG ulInputLen, BYTE *pbOutput, ULONG *pulOutputLen);

	/**
* @brief 导出公钥
* @note  功能描述：导出容器中的签名公钥或加密公钥
*
* @param[IN]      hContainer        密钥容器句柄。
* @param[IN]      bSignFlag         TRUE表示导出签名公钥，FALSE表示导出加密公钥。
* @param[OUT]     pbBlob            指向RSA公钥结构或者ECC公钥结构，如果此参数为NULL，由pulBlobLen返回的长度
* @param[IN,OUT]  pulBlobLen        输入时表示pbBlob缓冲区长度，输出时表示导出公钥结构大小。
*
* @retval SAR_OK:              成功。
* @retval SAR_ BAD_SIGNATURE： 验证失败。
* @retval 其他：               错误码。
*/
ULONG DEVAPI SKF_ExportPublicKeyEx(HCONTAINER hContainer, BOOL bSignFlag, BYTE *pbBlob, ULONG *pulBlobLen);

/**
* @brief  明文导入RSA密钥对
* @note   明文导入密钥对,测试接口
*
* @param[IN]      hContainer        密钥容器句柄。
* @param[IN]      bSignFlag         TRUE表示签名密钥对，FALSE表示加密密钥对。
* @param[IN]      pRsaPri			私钥值
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*
* @remark 权限要求：需要用户权限
*/
ULONG DEVAPI SKF_ImportRSAKeyPairEx(HCONTAINER hContainer, BOOL bSignFlag, PRSAPRIVATEKEYBLOBEX pRsaPri);

/**
* @brief  明文导入ECDSA密钥对
* @note   明文导入密钥对,测试接口
*
* @param[IN]      hContainer        密钥容器句柄。
* @param[IN]      bSignFlag         TRUE表示签名密钥对，FALSE表示加密密钥对。
* @param[IN]      ecdsaPub			公钥值
* @param[IN]      ecdsaPri			私钥值
*
* @retval SAR_OK:  成功。
* @retval 其他：   错误码。
*
* @remark 权限要求：需要用户权限
*/
ULONG DEVAPI SKF_ImportEcdsaKeyPairEx(HCONTAINER hContainer, BOOL bSignFlag, PECDSAPUBLICKEYBLOB ecdsaPub, PECDSAPRIVATEKEYBLOB ecdsaPri);

#ifdef __cplusplus
}
#endif
#endif
