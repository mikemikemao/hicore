/*
 * CopyRight:	HangZhou Hikvision System Technology Co., Ltd. All	Right Reserved.
 * FileName:	HPR_Netdb.h
 * Desc:		define ByteOrder/Addr/MACAddr files.
 * Author:		schina
 * Date:		2009-03-02
 * Contact:		zhaoyiji@hikvision.com.cn
 * History:		Created By Zhaoyiji 2009-03-02
 * */

#ifndef __HPR_NETDB_H__
#define __HPR_NETDB_H__

#include "HPR_Config.h"
#include "HPR_Types.h"
#include "HPR_Addr.h"

// #if defined(OS_WINDOWS)
// #include "iptypes.h" 

// #define HPR_MAX_ADAPTER_NAME_LEN MAX_ADAPTER_NAME_LENGTH
// #define HPR_MAX_ADAPTER_ADDRESS_LEN MAX_ADAPTER_ADDRESS_LENGTH
// #define HPR_MAX_DESCRIPTION_LEN MAX_ADAPTER_DESCRIPTION_LENGTH
// #define HPR_MAX_IP_ADDRESS_LEN	16
// #define HPR_MAX_NIC_NUM			16
// #define HPR_DEF_ADAPTER_ADDRESS_LEN 6
// #elif defined (OS_POSIX)
#define HPR_MAX_ADAPTER_NAME_LEN 256
#define HPR_MAX_ADAPTER_ADDRESS_LEN 8
#define HPR_MAX_DESCRIPTION_LEN 128
#define HPR_MAX_IP_ADDRESS_LEN	16
#define HPR_MAX_NIC_NUM			16
#define HPR_DEF_ADAPTER_ADDRESS_LEN 6
/*#endif*/

/**
 *	IP��ַ�ṹ
 */
struct HPR_IPADDR_STRING
{
	char szIPAddr[HPR_MAX_IP_ADDRESS_LEN];	//IP��ַ
	char szNetMask[HPR_MAX_IP_ADDRESS_LEN];	//����
};

/**
 * IP��ַ�б�
 */
struct HPR_IPADDRESS
{
	HPR_IPADDRESS* pNext; //��ǰָ��
	HPR_IPADDR_STRING struIpAddrString;//IP��ַ��Ϣ
};

/******************************************************************************
 * windows �������� MIB_IF_TYPE_OTHER/ETHERNET/TOKEN_RING/FDDI/PPP/LOOPBACK/SLIP
 * ��windows �Ļ�ȡ������Ϣ��ȣ���������������
 * 1��WINS Server(Windwos) ��windows �����ַת����
 * 2��DHCP���ʱ�估����ʱ��
 ******************************************************************************/
struct HPR_ADAPTER_INFO
{
	HPR_ADAPTER_INFO* pNext;						//��ǰָ��
	HPR_INT32 iIndex;								//���������ţ���0��ʼ��
	char szAdapterName[HPR_MAX_ADAPTER_NAME_LEN+4];	//��������
	char szDescription[HPR_MAX_DESCRIPTION_LEN+4];	//��������
	HPR_UINT32 nMacAddrLen;							//������ַ����
	unsigned char szMacAddr[HPR_MAX_ADAPTER_ADDRESS_LEN];	//������ַ
	HPR_UINT32 nType;								//�������� (POSIX��Ч)
	HPR_UINT32 nDhcpEnabled;						//�Ƿ���DHCP(POSIX��Ч)
	HPR_IPADDRESS* pIpAddrList;						//IPv4��ַ�б�
	HPR_IPADDRESS* pGatawayList;					//���ص�ַ�б�(POSIX��Ч)
	HPR_IPADDRESS* pDhcpServerList;					//DHCP�������б�(POSIX��Ч)
	HPR_IPADDRESS* pIpAddrv6List;					//IPv6��ַ�б�
};

struct HPR_ADDRESS_INFO
{
	HPR_INT32              iFlags;
	HPR_INT32              iFamily;
	HPR_INT32              iSockType;
	HPR_INT32              iProtocol;
	HPR_ADDR_T             Address;
	char                   *sCanonName;
	HPR_ADDRESS_INFO       *pNext;
};


HPR_DECLARE HPR_INT32 CALLBACK HPR_GetHostName(char* pName, HPR_INT32 iNameLen);

#if 1
HPR_DECLARE HPR_INT32 CALLBACK HPR_GetMacAddr(const char* pLocalIP, unsigned char* pMacAddr, HPR_INT32* iMacAddrlen);
HPR_DECLARE HPR_INT32 CALLBACK HPR_GetAdapterInfo(HPR_ADAPTER_INFO** pAdaterInfo);
HPR_DECLARE HPR_INT32 CALLBACK HPR_FreeAdapterInfo(HPR_ADAPTER_INFO* pAdaterInfo);
#endif

HPR_DECLARE hostent* CALLBACK HPR_GetAddressByName(const char* pName);

HPR_DECLARE HPR_UINT16 CALLBACK HPR_Htons(HPR_UINT16 nHostShort);

HPR_DECLARE HPR_UINT16 CALLBACK HPR_Ntohs(HPR_UINT16 nNetShort);

HPR_DECLARE HPR_UINT32 CALLBACK HPR_Htonl(HPR_UINT32 nHostLong);

HPR_DECLARE HPR_UINT32 CALLBACK HPR_Ntohl(HPR_UINT32 nNetLong);

//������������
HPR_DECLARE HPR_INT32 CALLBACK HPR_GetAddressInfo(const char *sNodeName, const char *sServerName, HPR_ADDRESS_INFO *Hints, HPR_ADDRESS_INFO **pRes);
HPR_DECLARE HPR_INT32 CALLBACK HPR_FreeAddressInfo(HPR_ADDRESS_INFO *pAddressInfo);

#endif
