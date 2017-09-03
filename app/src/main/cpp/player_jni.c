#include <jni.h>

#include "libavcodec/avcodec.h"

JNIEXPORT jstring JNICALL
Java_think_reed_rfplayer_MainActivity_stringFromFFmpeg(JNIEnv *env, jobject instance) {

    // TODO
    char info[10000] = {0};
    sprintf(info, "%s\n", avcodec_configuration());

    return (*env)->NewStringUTF(env, info);
}