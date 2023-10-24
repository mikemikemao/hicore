/*
 * CopyRight:	HangZhou Hikvision System Technology Co., Ltd. All	Right Reserved.
 * FileName:	HRP_Hpr.h
 * Desc:		OS Layer Component.
 * Author:		schina
 * Date:		2009-03-02
 * Contact:		zhaoyiji@hikvision.com.cn
 * History:		Created By Zhaoyiji 2009-03-02
 * */

/*! 
	\file HPR_Hpr.h
	\brief HPR Hpr Manager.

	Details.
*/

#ifndef __HPR_HPR_H__
#define __HPR_HPR_H__

#include "HPR_Config.h"
#include "HPR_Types.h"

/**
 * HPR_Init ��ʼ��HPR��,ʹ��HPR��������ȵ����������
 * @param void
 * @return 0�ɹ���-1ʧ�ܡ�
 * @sa HPR_Fini().
 */
HPR_DECLARE HPR_INT32 CALLBACK HPR_Init();
HPR_DECLARE HPR_INT32 CALLBACK HPR_InitEx();

/**
 * HPR_Fini ����HPR��,������
 * @param void
 * @return void
 * @sa HPR_Init().
 */
HPR_DECLARE HPR_VOID CALLBACK HPR_Fini();
HPR_DECLARE HPR_VOID CALLBACK HPR_FiniEx();


/**
* HPR_GetHPRVersion ��ȡHPR��ǰ�汾��
* @param void
* @return HPR_UINT32���ͣ��汾��0.5.2.0������0x00050200
*/
HPR_DECLARE HPR_UINT32 CALLBACK HPR_GetHPRVersion();

#endif
