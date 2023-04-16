//
// Created by pirate
//
#include "jni.h"
#include "utils/LogUtil.h"

#include <eXosip2/eX_setup.h>

extern "C"
JNIEXPORT void JNICALL
Java_com_hikvision_ThridParty_native_1helloWorld(JNIEnv *env, jobject thiz) {
    // TODO: implement native_helloWorld()
    LOGCATE("hello world\n");
    int ret = 0;
    ret = eXosip_init();
    if(OSIP_SUCCESS != ret){
        LOGCATE("eXosip_init failed ret =%d \n",ret);
        return;
    }
    LOGCATD("eXosip_init success \n");
}