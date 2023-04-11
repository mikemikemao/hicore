//
// Created by pirate
//
#include <android/binder_ibinder.h>
#include "jni.h"
#include "utils/LogUtil.h"

extern "C"
JNIEXPORT void JNICALL
Java_com_hikvision_ThridParty_native_1helloWorld(JNIEnv *env, jobject thiz) {
    // TODO: implement native_helloWorld()
    LOGCATE("hello world\n");
}