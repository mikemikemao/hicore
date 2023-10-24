#ifndef __HPR_ERROR_H__
#define __HPR_ERROR_H__

#include "HPR_Config.h"
#include "HPR_Types.h"

#define HPR_ERROR_BASE 40000

#define HPR_EPERM		(HPR_ERROR_BASE+1)	//Ȩ�޲���
#define HPR_EBADARG		(HPR_ERROR_BASE+2)	//�������Ϸ�
#define HPR_EDISORDER	(HPR_ERROR_BASE+3)	//����˳�򲻶�
#define HPR_ENORESOURCE	(HPR_ERROR_BASE+4)	//��Դ����
#define HPR_ENOMEM		(HPR_ERROR_BASE+5)	//û���ڴ�
#define HPR_EWOULDBLOCK	(HPR_ERROR_BASE+6)	//��ʱ������ɣ���Ҫ����
#define HPR_ETIMEO		(HPR_ERROR_BASE+7)	//��ʱ
#define HPR_EEOF		(HPR_ERROR_BASE+8)	//EOF
#define HPR_EBUSY		(HPR_ERROR_BASE+9)	//ϵͳæ
#define HPR_EINIT		(HPR_ERROE_BASE+10)	//��ʼ������
#define HPR_ENOTFOUND	(HPR_ERROR_BASE+11)	//û���ҵ�
#define HPR_EBADPATH	(HPR_ERROR_BASE+12)	//·������
#define HPR_EBADIP		(HPR_ERROR_BASE+13)	//���Ϸ���IP��ַ
#define HPR_EBADMASK	(HPR_ERROR_BASE+14)	//��Ч����
#define HPR_EINVALIDSOCK (HPR_ERROR_BASE+15)//��Ч�׽���
#define HPR_ESOCKET		(HPR_ERROR_BASE+16)	//�׽��ֳ���
#define HPR_ESOCKCLOSE	(HPR_ERROR_BASE+17)	//�׽��ֹر�


HPR_DECLARE HPR_UINT32 CALLBACK HPR_GetLastError();

HPR_DECLARE HPR_UINT32 CALLBACK HPR_SetLastError(HPR_UINT32 nErrno);

HPR_DECLARE HPR_UINT32 CALLBACK HPR_GetSystemLastError();

HPR_DECLARE HPR_VOID   CALLBACK HPR_SetSystemLastError(HPR_UINT32 nError);

#endif

