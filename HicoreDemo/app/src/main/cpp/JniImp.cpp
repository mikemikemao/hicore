//
// Created by pirate
//
#include <sys/endian.h>
#include "jni.h"
#include "utils/LogUtil.h"
#include "upFile.h"
#include "string.h"
#include "stdlib.h"
#define NATIVE_HICORE_CLASS_NAME "com/hikvision/Hicore"

int iSrcfd = 1;

int ezviz_sys_upg_down(int iSrcfd)
{
	int ret = 0;
	int len = 0;
	int iFileNum = 0;
	int headsLen = 0;
	UPGRADE_NEW_FIRMWARE_HEADER_T decryFirmHead;
	memset(&decryFirmHead,0x00,sizeof(UPGRADE_NEW_FIRMWARE_HEADER_T));
	UPGRADE_NEW_FIRMWARE_HEADER_T encryFirmHead;
	memset(&encryFirmHead,0x00,sizeof(UPGRADE_NEW_FIRMWARE_HEADER_T));
	char* firmHeadFileHeads = NULL;
	int firmHeadFileHeadsLen = 0;
	int devTypeListFileIndex = 0;
	unsigned char byaSha256Sum[SHA256SUM_BY_BYTES_LEN] = {0};
	unsigned char byaKey[AES_256_KEY_LEN_BY_BYTE] = {0};
	UPGRADE_FILE_HEADER_P pstFileHeader   = NULL;
	if(iSrcfd <= 0)
	{
		return UPGRADE_NO_FILE;
	}
	//第一步 获取固件头
	ret = checkFirmwareHead(iSrcfd,&decryFirmHead,&encryFirmHead);
	if(ret != 0)
	{
		APP_ERR("checkFirmwareHead failed ret =%d\n",ret);
		return ret;
	}
	//2.第二部获取固件头和文件头
	firmHeadFileHeadsLen = ntohl(decryFirmHead.dwUpgradeHeaderLen);
	firmHeadFileHeads = (char*) malloc (firmHeadFileHeadsLen);
	ret = getEncryptFirmHeadFileHeads(iSrcfd, &encryFirmHead,firmHeadFileHeads,firmHeadFileHeadsLen);
	if(ret != 0)
	{
		APP_ERR("getEncryptFirmHeadFileHeads failed ret =%d\n",ret);
		goto err;
	}
	//3.获取固件头和文件头的摘要值
	APP_PRT("getHeadersSha256\n");
	ret = getFirmHeadFileHeadsSha256(firmHeadFileHeads, firmHeadFileHeadsLen, byaSha256Sum);
	if(ret != 0)
	{
		APP_ERR("getSha256 failed ret =%d\n",ret);
		goto err;
	}
	//4.获取明文
	ret = getPlainFirmHeadFileHeads(firmHeadFileHeads, firmHeadFileHeadsLen);
	if(ret != 0)
	{
		APP_ERR("getPlainFirmHeadFileHeads failed ret =%d\n",ret);
		goto err;
	}
	//5、获取会话密钥
	APP_PRT("getSessionKey\n");
	ret = getSessionKey(decryFirmHead.byaKeyRandom,byaKey);
	if(ret != 0)
	{
		APP_ERR("getSha256 failed ret =%d\n",ret);
		goto err;
	}
	//6获取文件头指针
	pstFileHeader = getFileHeads(firmHeadFileHeads,firmHeadFileHeadsLen,&decryFirmHead);
	if(pstFileHeader == NULL)
	{
		APP_ERR("getFileHeads failed\n");
		goto err;
	}
	iFileNum = ntohl(decryFirmHead.dwFileNumber);
	devTypeListFileIndex = ntohl(decryFirmHead.dwDevTypeListFileIndex);
	for(int i = 0; i <  iFileNum; i++)
	{
		APP_PRT("byaFileName:%s\n",pstFileHeader[i].byaFileName);
		APP_PRT("dwStartOffset:%u\n",ntohl(pstFileHeader[i].dwStartOffset));
		APP_PRT("dwFileEncryptLen:%u\n",ntohl(pstFileHeader[i].dwFileEncryptLen));
		APP_PRT("enPackageType:%d\n",ntohl(pstFileHeader[i].enPackageType));
        if(devTypeListFileIndex == i+1)
        {
            ret = unpack_dev_type_info(iSrcfd, &pstFileHeader[i], byaKey);
            if (ret != 0)
            {
                APP_ERR("unpack_dev_type_info failed ret =%d\n",ret);
                goto err;
            }
        }else
        {
            ret = unpack_file_data_each(iSrcfd, &pstFileHeader[i], byaKey);
            if (ret != 0)
            {
                APP_ERR("unpack_file_data_each failed ret =%d\n",ret);
                goto err;
            }
        }

	}
	//校验验签

	//设置升级标志位
err:
	if(firmHeadFileHeads != NULL)
	{
		free(firmHeadFileHeads);
		firmHeadFileHeads = NULL;
	}
	return 0;

}

JNIEXPORT void JNICALL helloHicore(JNIEnv *env, jobject instance)
{
	LOGCATE("hello hicore");
	ezviz_sys_upg_down(iSrcfd);

}


//mediacodec相关
static JNINativeMethod g_HicoreMethods[] = {
		{"native_helloHicore",                       "()V",                             (void *)(helloHicore)}
};



static int RegisterNativeMethods(JNIEnv *env, const char *className, JNINativeMethod *methods, int methodNum)
{
	LOGCATE("RegisterNativeMethods");
	jclass clazz = env->FindClass(className);
	if (clazz == NULL)
	{
		LOGCATE("RegisterNativeMethods fail. clazz == NULL");
		return JNI_FALSE;
	}
	if (env->RegisterNatives(clazz, methods, methodNum) < 0)
	{
		LOGCATE("RegisterNativeMethods fail");
		return JNI_FALSE;
	}
	return JNI_TRUE;
}

static void UnregisterNativeMethods(JNIEnv *env, const char *className)
{
	LOGCATE("UnregisterNativeMethods");
	jclass clazz = env->FindClass(className);
	if (clazz == NULL)
	{
		LOGCATE("UnregisterNativeMethods fail. clazz == NULL");
		return;
	}
	if (env != NULL)
	{
		env->UnregisterNatives(clazz);
	}
}

// call this func when loading lib
extern "C" jint JNI_OnLoad(JavaVM *jvm, void *p)
{
	LOGCATE("===== JNI_OnLoad =====");
	jint jniRet = JNI_ERR;
	JNIEnv *env = NULL;
	if (jvm->GetEnv((void **) (&env), JNI_VERSION_1_6) != JNI_OK)
	{
		return jniRet;
	}
	//视频预览相关操作
	jint regRet = RegisterNativeMethods(env, NATIVE_HICORE_CLASS_NAME, g_HicoreMethods,
										sizeof(g_HicoreMethods) /
										sizeof(g_HicoreMethods[0]));
	if (regRet != JNI_TRUE)
	{
		return JNI_ERR;
	}

	return JNI_VERSION_1_6;
}

extern "C" void JNI_OnUnload(JavaVM *jvm, void *p)
{
	JNIEnv *env = NULL;
	if (jvm->GetEnv((void **) (&env), JNI_VERSION_1_6) != JNI_OK)
	{
		return;
	}
	UnregisterNativeMethods(env, NATIVE_HICORE_CLASS_NAME);
}
