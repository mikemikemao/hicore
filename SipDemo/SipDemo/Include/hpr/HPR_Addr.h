/*
 * CopyRight:	HangZhou Hikvision System Technology Co., Ltd. All	Right Reserved.
 * FileName:	HRP_Addr.h
 * Desc:		OS Layer Component.
 * Author:		schina
 * Date:		2009-03-02
 * Contact:		zhaoyiji@hikvision.com.cn
 * History:		Created By Zhaoyiji 2009-03-02
 * */

/*! 
	\file HPR_Addr.h
	\brief HPR Network Address Manager.

	Details.
*/

#ifndef __HPR_ADDR_H__
#define __HPR_ADDR_H__

#include "HPR_Config.h"
#include "HPR_Types.h"


#if defined(OS_WINDOWS)
	typedef SOCKET HPR_SOCK_T;
	#if (_MSC_VER < 1310)
		#ifndef s6_addr
			struct in6_addr {
				union {
					u_char Byte[16];
					u_short Word[8];
				} u;
			};
			#define in_addr6 in6_addr
			/*
			** Defines to match RFC 2553.
			*/
			#define _S6_un     u
			#define _S6_u8     Byte
			#define s6_addr    _S6_un._S6_u8
			/*
			** Defines for our implementation.
			*/
			#define s6_bytes   u.Byte
			#define s6_words   u.Word
		#endif

		typedef struct {
			short   sin6_family;        /* AF_INET6 */
			u_short sin6_port;          /* Transport level port number */
			u_long  sin6_flowinfo;      /* IPv6 flow information */
			struct in6_addr sin6_addr;  /* IPv6 address */
			u_long sin6_scope_id;       /* set of interfaces for a scope */
		}sockaddr_in6_hpr;
	#else
		typedef sockaddr_in6 sockaddr_in6_hpr;
	#endif
#elif defined(OS_POSIX)
	typedef int HPR_SOCK_T;
	typedef sockaddr_in6 sockaddr_in6_hpr;
#else
	#error OS Not Implement Yet.
#endif



/**
 * struct HPR_ADDR_T
 */
typedef struct HPR_ADDR_T
{
	union
	{
		sockaddr_in sin4;	/**< IPV4 ��ַ*/
#if defined(OS_SUPPORT_IPV6)
		sockaddr_in6_hpr sin6;	/**< IPV6 ��ַ*/
#endif
	}SA;
}HPR_ADDR_T;

typedef struct HPR_ADDR_EXP_T
{
	HPR_INT32 iAf;				/**< ��ַ�� AF_INET��AF_INET6*/
	union
	{
		HPR_UINT32 nAddr4;		/**< IPV4���ε�ַ (�����ֽ���)*/
		HPR_UINT8 nAddr6[16];	/**< IPV6���ε�ַ (�����ֽ���)*/
	}ADDR;
	HPR_UINT16 nPort;			/**< �˿ں�(�����ֽ���)*/
	HPR_UINT16 nReserved;		/**< ����*/
}HPR_ADDR_EXP_T;

#define HPR_AF_INET		AF_INET
#if defined(OS_SUPPORT_IPV6)
#define HPR_AF_INET6	AF_INET6
#endif

/**
 * HPR_MakeAddrByString ͨ����ַ������,�ַ�����ʽ�ĵ�ַ���˿ں��齨HPR�����ַ�ṹ.
 * @param iAf (IN) ��ַ�����ͣ�AF_INET �� AF_INET6��.
 * @param pAddr (IN) ��'\0'��β���ַ�����ʽ�����ַ.
 * @param nPort (IN) ����˿ں�(�����ֽ���).
 * @param pHprAddr (OUT) HPR�����ַ�ṹ.
 * @return 0 �ɹ�, -1 ʧ��.
 * @sa HPR_MakeAddr4ByInt(), HPR_MakeAddr6ByInt(), HPR_MakeAddr()
 */
HPR_DECLARE HPR_INT32 CALLBACK HPR_MakeAddrByString(HPR_INT32 iAf, const char* pAddr, HPR_UINT16 nPort, HPR_ADDR_T* pHprAddr);

/**
 * HPR_MakeAddr4ByInt ͨ�����ε�ַ���˿ں��齨HPR�����ַ�ṹ��IPV4��.
 * @param nAddr (IN) ���������ַ.
 * @param nPort (IN) ����˿ںţ������ֽ���.
 * @param pHprAddr (OUT) HPR�����ַ�ṹ.
 * @return 0 �ɹ�, -1 ʧ��.
 * @sa HPR_MakeAddrByString(), HPR_MakeAddr6ByInt(), HPR_MakeAddr()
 */
HPR_DECLARE HPR_INT32 CALLBACK HPR_MakeAddr4ByInt(HPR_UINT32 nAddr, HPR_UINT16 nPort, HPR_ADDR_T* pHprAddr);

#if defined(OS_SUPPORT_IPV6)
/**
 * HPR_MakeAddr6ByInt ͨ�����ε�ַ���˿ں��齨HPR�����ַ�ṹ��IPV6��.
 * @param nAddr (IN) ���������ַ.
 * @param nPort (IN) ����˿ںţ������ֽ���.
 * @param pHprAddr (OUT) HPR�����ַ�ṹ.
 * @return 0 �ɹ�, -1 ʧ��.
 * @sa HPR_MakeAddrByString(), HPR_MakeAddr4ByInt(), HPR_MakeAddr()
 */
HPR_DECLARE HPR_INT32 CALLBACK HPR_MakeAddr6ByInt(HPR_UINT8 nAddr[16], HPR_UINT16 nPort, HPR_ADDR_T* pHprAddr);
#endif

/**
 * HPR_SetAddrPort ����HPR�����ַ�ṹ�˿ں�.
 * @param pHprAddr (IN) HPR�����ַ�ṹ��.
 * @param nPort (IN) ����˿ں�(�����ֽ���).
 * @return 0�ɹ���-1ʧ��.
 * @sa HPR_GetAddrPort().
 */
HPR_DECLARE HPR_INT32 CALLBACK HPR_SetAddrPort(HPR_ADDR_T* pHprAddr, HPR_UINT16 nPort);

/**
 * HPR_GetAddrType ͨ��HPR�����ַ�ṹ��ȡ��ַ�壨AF_INET��AF_INET6��.
 * @param pHprAddr (IN) HPR�����ַ�ṹָ��.
 * @return -1ʧ�ܣ����򷵻�AF_INET��AF_INET6.
 * @sa HPR_MakeAddr6ByInt(), HPR_MakeAddr4ByInt(), HPR_MakeAddr(), HPR_MakeAddrByString().
 */
HPR_DECLARE HPR_INT32 CALLBACK HPR_GetAddrType(HPR_ADDR_T* pHprAddr);

/**
 * HPR_MakeAddr ͨ��SOCKADDR�ṹ�齨HPR�����ַ�ṹ.
 * @param pSockAddr (IN) SOCKADDR��ַ�ṹָ��.
 * @param iSockAddrLen (IN) SOCKADDR��ַ�ṹ����.
 * @param pHprAddr (OUT) HPR�����ַ�ṹָ��.
 * @return 0 �ɹ�, -1 ʧ��.
 * @sa HPR_MakeAddrByString(), HPR_MakeAddr4ByInt(), HPR_MakeAddr46ByInt()
 */
HPR_DECLARE HPR_INT32 CALLBACK HPR_MakeAddr(HPR_VOIDPTR pSockAddr, HPR_INT32 iSockAddrLen, HPR_ADDR_T* pHprAddr);

/**
 * HPR_GetAddrString ͨ��HPR�����ַ�ṹ��ȡ�ַ�����ʽ��ַ.
 * @param pHprAddr (IN) HPR�����ַ�ṹ.
 * @return NULLʧ�ܣ����򷵻���'\0'�ַ�����ʽ�����ַ.
 * @sa HPR_GetAddrBySockFd(),HPR_GetAddrPort().
 */
HPR_DECLARE const char* CALLBACK HPR_GetAddrString(HPR_ADDR_T* pHprAddr);

/**
 * HPR_GetAddrPort ��ȡ��ַ�ṹ������˿ں�.
 * @param pHprAddr (IN) HPR�����ַ�ṹ���ϲ��û��Լ����ָ����Ч��.
 * @return ����˿ں�(�����ֽ���).
 * @sa HPR_GetAddrString(),HPR_GetAddr4Int(),HPR_GetAddr6Int(),HPR_GetAddrInfo().
 */
HPR_DECLARE HPR_UINT16 CALLBACK HPR_GetAddrPort(HPR_ADDR_T* pHprAddr);

/**
 * HPR_GetAddr4Int ��ȡ��ַ�ṹIPV4���α�ʾ�������ַ.
 * @param pHprAddr (IN) HPR��ʽ�����ַ�ṹ.
 * @param nAddr (OUT) ���������ַ�������ֽ���.
 * @return 0�ɹ���-1ʧ��.
 * @sa HPR_GetAddr6Int(),HPR_GetAddrPort(),HPR_GetAddrInfo().
 */
HPR_DECLARE HPR_INT32 CALLBACK HPR_GetAddr4Int(HPR_ADDR_T* pHprAddr, HPR_UINT32* nAddr);

#if defined (OS_SUPPORT_IPV6)
/**
 * HPR_GetAddr6Int ��ȡ��ַ�ṹIPV6���α�ʾ�������ַ.
 * @param pHprAddr (IN) HPR��ʽ�����ַ�ṹ.
 * @param nAddr (OUT) ���������ַ�������ֽ���.
 * @return 0�ɹ���-1ʧ��.
 * @sa HPR_GetAddr4Int(),HPR_GetAddrInfo(),HPR_GetAddrPort().
 */
HPR_DECLARE HPR_INT32 CALLBACK HPR_GetAddr6Int(HPR_ADDR_T* pHprAddr, HPR_UINT8 nAddr[16]);
#endif

/**
 * HPR_GetAddrInfo ��ȡ�����ַ�ṹ��Ϣ.
 * @param pHprAddr (IN) HPR��ʽ�����ַ�ṹ.
 * @param pHprExp (OUT) �����ַ�ṹ.
 * @return 0�ɹ���-1ʧ��.
 * @sa HPR_GetAddrPort(),HPR_GetAddr4Int(),HPR_GetAddr6Int().
 */
HPR_DECLARE HPR_INT32 CALLBACK HPR_GetAddrInfo(HPR_ADDR_T* pHprAddr, HPR_ADDR_EXP_T* pHprExp);

/**
 * HPR_GetAddrBySockFd ͨ��socket �׽��ֻ�ȡ���ػ�Զ�˵�����ַ�ṹ.
 * @param iSockFd (IN) socket �׽���.
 * @param pHprLocal (OUT) HPR���������ַ.
 * @param pRemote (OUT) HPR����Զ�˵�ַ.
 * @return 0 �ɹ�, -1 ʧ��.
 * @sa HPR_GetAddrString(),HPR_MakeAddr4ByInt(),HPR_MakeAddr6ByInt(),HPR_MakeAddr().
 */
HPR_DECLARE HPR_INT32 CALLBACK HPR_GetAddrBySockFd(HPR_SOCK_T iSockFd,HPR_ADDR_T* pHprLocal, HPR_ADDR_T* pRemote);


HPR_DECLARE HPR_INT32 CALLBACK HPR_InetPton(const char* pSrc, HPR_VOIDPTR pDst);

HPR_DECLARE const char* CALLBACK HPR_InetNtop(HPR_INT32 iAf, const unsigned char* pSrc, char* pDst, int iCnt);

#endif
