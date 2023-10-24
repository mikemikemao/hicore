/*
 * ====================================================================
 * Copyright 2007-2008 Hikvision Digital Technology Co., Ltd.
 *
 *        Filename:  HPR_AlignMem.h
 * 
 *     Description:  ��ָ���ֽڶ�������ڴ�
 * 
 *          Author:  tyu, yutao NOSPAM hikvision DOT com
 *
 *            Date:  2009-10-22 10:56:48 �й���׼ʱ��
 *
 * Modification History:
 *            <version > <time> <author> <desc>
 * ====================================================================
 */
#ifndef __HPR_ALIGN_MEM_H__
#define __HPR_ALIGN_MEM_H__

#include "HPR_Config.h"
#include "HPR_Types.h"

HPR_DECLARE HPR_VOIDPTR HPR_AlignedMalloc(HPR_INT32 size, HPR_INT32 alignment);
HPR_DECLARE HPR_VOID HPR_AlignedFree(HPR_VOIDPTR ptr);

#endif

