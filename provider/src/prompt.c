#include "top_kwseeker_jni_prompt_Prompt.h"
#include <jni.h>
#include <stdio.h>

JNIEXPORT jstring JNICALL Java_top_kwseeker_jni_prompt_Prompt_getLine
        (JNIEnv *env, jobject obj, jstring prompt) {
    char buf[128];
    //const jbyte *str = (*env)->GetStringUTFChars(env, prompt, NULL);
    const char *str = (*env)->GetStringUTFChars(env, prompt, NULL);     //GetStringUTFChars会做内存分配，所以后面要ReleaseStringUTFChars释放内存
    if (str == NULL) {
        return NULL;    //还会抛出一个 OutOfMemoryError的异常
    }
    printf("%s", str);
    (*env)->ReleaseStringUTFChars(env, prompt, str);

    /*We assume here that the user does not type more than 127 characters */
    scanf("%s", buf);
    return (*env)->NewStringUTF(env, buf);
}

/**
 * 将数据读到预先分配的缓冲，GetStringUTFRegion 不会做内存分配，不存在内存溢出的可能
 */
JNIEXPORT jstring JNICALL Java_top_kwseeker_jni_prompt_Prompt_getLine2
        (JNIEnv *env, jobject obj, jstring prompt) {
    /* assume the prompt string and user input has less than 128 characters */
    char out_buf[128], in_buf[128];
    int len = (*env)->GetStringLength(env, prompt);
    (*env)->GetStringUTFRegion(env, prompt, 0, len, out_buf);
    printf("%s", out_buf);

    scanf("%s", in_buf);
    return (*env)->NewStringUTF(env, in_buf);
}

//void GetReleaseStringCriticalExample(JNIEnv *env, jstring jstr1, jstring jstr2) {
//    jchar *s1 = (*env)->GetStringCritical(env, jstr1);
//    if (!s1) {
//        /* error handling */
//    }
//    jchar *s2 = (*env)->GetStringCritical(env, jstr2);
//    if (!s2) {
//        (*env)->ReleaseStringCritical(env, jstr1, s1);
//        /* error handling */
//    }
//    /* use s1 and s2 */
//    (*env)->ReleaseStringCritical(env, jstr1, s1);
//    (*env)->ReleaseStringCritical(env, jstr2, s2);
//}
