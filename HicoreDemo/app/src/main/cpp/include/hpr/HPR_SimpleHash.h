/*
 * ====================================================================
 * Copyright 2007-2008 Hikvision Digital Technology Co., Ltd.
 *
 *        Filename:  HPR_SimpleHash.h
 *
 *     Description:  ��hash��ʵ��, ʵ����ȫ��Դ��glibc��hsearch_r.c�ļ���
 *                   ֻ�Ǽ��޸����£��Է���ʹ��
 *
 *          Author:  tyu, yutao NOSPAM hikvision DOT com
 *
 *            Date:  2009-11-27 17:47:03 �й���׼ʱ��
 *
 * Modification History:
 *            <version > <time> <author> <desc>
 * ====================================================================
 */

#ifndef __HPR_SIMPLE_HASH_H__
#define __HPR_SIMPLE_HASH_H__

#include "HPR_Config.h"
#include "HPR_Types.h"

typedef struct _HPR_ENTRY
{
    const char* key;
    HPR_VOIDPTR data;
}HPR_ITEM;

/**
 * Function:	HPR_SimpleHashCreate
 * Desc:		
 * Input:		@param 
 * Output:      @param
 * Return:		if success return HPR_OK, otherwise return HPR_ERROR.
 * */
HPR_DECLARE HPR_INT32 CALLBACK HPR_SimpleHashCreate(HPR_INT32 size, HPR_HANDLE* hash_handle);

/**
 * Function:	HPR_SimpleHashCreate
 * Desc:		
 * Input:		@param 
                @param 
 * Output:
 * Return:		if success return HPR_OK, otherwise return HPR_ERROR.
 * */
HPR_DECLARE HPR_INT32 CALLBACK HPR_SimpleHashEnter(HPR_ITEM* item, HPR_HANDLE hash_handle);

/**
 * Function:	HPR_SimpleHashCreate
 * Desc:		
 * Input:		@param 
                @param 
 * Output:      @param
 * Return:		if success return HPR_OK, otherwise return HPR_ERROR.
 * */
HPR_DECLARE HPR_INT32 CALLBACK HPR_SimpleHashFind(const char* key, HPR_VOIDPTR* data, HPR_HANDLE hash_handle);

/**
 * Function:	HPR_SimpleHashCreate
 * Desc:		
 * Input:		@param 
                @param 
 * Output:
 * Return:		if success return HPR_OK, otherwise return HPR_ERROR.
 * */
HPR_DECLARE HPR_INT32 CALLBACK HPR_SimpleHashRemove(const char* key, HPR_HANDLE hash_handle);

/**
 * Function:	HPR_SimpleHashDestroy
 * Desc:		
 * Input:		@param 
 * Output:
 * Return:		if success return HPR_OK, otherwise return HPR_ERROR.
 * */
HPR_DECLARE HPR_INT32 CALLBACK HPR_SimpleHashDestroy(HPR_HANDLE hash_handle);

#endif

