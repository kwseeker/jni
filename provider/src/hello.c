#include "top_kwseeker_jni_hello_HelloJNI.h"
#include <jni.h>
#include <stdio.h>

JNIEXPORT void JNICALL Java_top_kwseeker_jni_hello_HelloJNI_sayHello(JNIEnv *env, jobject obj) {
    printf("Hello JNI!\n");
}