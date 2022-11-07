#include "top_kwseeker_jni_field_FieldAccess.h"
#include <jni.h>

/**
 * 访问实例字段
 * 读取字段值、改写字段值
 */
JNIEXPORT void JNICALL Java_top_kwseeker_jni_field_FieldAccess_accessInstanceField
        (JNIEnv *env, jobject obj) {
    jfieldID fid; /* store the field ID */
    jstring jStr;
    const char* str;

    /* Get a reference to obj class */
    jclass cls = (*env)->GetObjectClass(env, obj);
    fid = (*env)->GetFieldID(env, cls, "s", "Ljava/lang/String;");
    if(!fid) {
        return; /* failed to find the field ！*/
    }

    /* Read the instance field s */
    jStr = (*env)->GetObjectField(env, obj, fid);
    str = (*env)->GetStringUTFChars(env, jStr, NULL);
    if(!str) {
        return; /* out of memory */
    }
    printf("    c.s = \"%s\"\n", str);
    (*env)->ReleaseStringUTFChars(env, jStr, str);

    /* Create a new string and overwrite the instance field */
    jStr = (*env)->NewStringUTF(env, "123");
    if(!jStr) {
        return; /*out of memory */
    }
    (*env)->SetObjectField(env, obj, fid, jStr);
}

JNIEXPORT void JNICALL Java_top_kwseeker_jni_field_FieldAccess_accessStaticField
        (JNIEnv *env, jobject obj) {
    jfieldID fid; /* store the field ID */
    jint si;

    /* Get a reference to obj class */
    jclass cls = (*env)->GetObjectClass(env, obj);
    printf("In C:\n");
    /* Look for the static field si in cls */
    fid = (*env)->GetStaticFieldID(env, cls, "si", "I");
    if(!fid) {
        return; /* field not found */
    }

    /* Access the static field si */
    si = (*env)->GetStaticIntField(env, cls, fid);
    printf("  StaticFieldAccess.si = %d\n", si);
    (*env)->SetStaticIntField(env, cls, fid, 200);
}