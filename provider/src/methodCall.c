#include "top_kwseeker_jni_method_MethodCall.h"
#include <jni.h>

//使用全局变量缓存方法ID
jmethodID MID_InstanceMethodCall_callback;
jmethodID MID_StaticMethodCall_staticCallback;

/*
 * Class:     top_kwseeker_jni_method_MethodCall
 * Method:    initIDs
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_top_kwseeker_jni_method_MethodCall_initIDs
        (JNIEnv *env, jclass cls) {
    MID_InstanceMethodCall_callback = (*env)->GetMethodID(env, cls, "callback", "()V");
    MID_StaticMethodCall_staticCallback = (*env)->GetStaticMethodID(env, cls, "staticCallback", "()V");
}

/*
 * 本地方法中调用实例方法
 * Class:     top_kwseeker_jni_method_MethodCall
 * Method:    nativeMethod
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_top_kwseeker_jni_method_MethodCall_nativeMethod
        (JNIEnv *env, jobject obj) {
    printf("In C\n");
    (*env)->CallVoidMethod(env, obj, MID_InstanceMethodCall_callback);
}

/*
 * 本地方法中调用静态方法
 * Class:     top_kwseeker_jni_method_MethodCall
 * Method:    nativeStaticMethod
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_top_kwseeker_jni_method_MethodCall_nativeStaticMethod
        (JNIEnv *env, jobject obj) {
    printf("In C\n");
    (*env)->CallStaticVoidMethod(env, obj, MID_StaticMethodCall_staticCallback);
}

/*
 * 本地中调用父类方法
 * Class:     top_kwseeker_jni_method_MethodCall
 * Method:    nativeCallPMethod
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_top_kwseeker_jni_method_MethodCall_nativeCallPMethod
        (JNIEnv *env, jobject obj) {
    jclass cls = (*env)->GetObjectClass(env, obj);
    //获取父类的类对象
    jclass pCls = (*env)->GetSuperclass(env, cls);
    //jclass pCls = (*env)->FindClass(env, "java/lang/Runnable");       // That's call interface method rather than call parent class method
    //jclass pCls = (*env)->FindClass(env, "top/kwseeker/jni/method/Task");
    if (pCls == NULL) {
        return;
    }
    jmethodID mId = (*env)->GetMethodID(env, pCls, "run", "()V");
    //(*env)->CallVoidMethod(env, obj, mId);    // didn't work
    (*env)->CallNonvirtualVoidMethod(env, obj, pCls, mId);
}

jstring NewString(JNIEnv *env, const jchar *chars, jint len) {
    jclass stringCls = (*env) -> FindClass(env, "java/lang/String");
    if (stringCls == NULL) {
        return NULL;
    }
    //调用 String(char[])
    jmethodID constructorId = (*env)->GetMethodID(env, stringCls, "<init>", "([C)V");
    if (constructorId == NULL) {
        return NULL;
    }

    jcharArray eleArr = (*env)->NewCharArray(env, len);
    (*env)->SetCharArrayRegion(env, eleArr, 0, len, chars);

    //jstring result = (*env)->NewObjectA(env, stringCls, constructorId, chars);  //pointer type not match
    jstring result = (*env)->NewObject(env, stringCls, constructorId, eleArr);

    (*env)->DeleteLocalRef(env, eleArr);
    (*env)->DeleteLocalRef(env, stringCls);
    return result;
}

/*
 * 调用JDK库中类的构造器方法
 * Class:     top_kwseeker_jni_method_MethodCall
 * Method:    nativeNewString
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_top_kwseeker_jni_method_MethodCall_nativeNewString
        (JNIEnv *env, jobject obj, jstring str) {
    const jchar *chars = (*env)->GetStringChars(env, str, NULL);
    jsize len = (*env)->GetStringLength(env, str);
    jstring result = NewString(env, chars, len);

    (*env)->ReleaseStringChars(env, str, chars);
    return result;
}
