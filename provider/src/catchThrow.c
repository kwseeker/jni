#include "top_kwseeker_jni_exception_CatchThrow.h"
#include <jni.h>

void JNU_ThrowByName(JNIEnv *env, const char* name, const char* msg){
    jclass cls = (*env)->FindClass(env, name);
    /*if cls is NULL, an exception has already been thrown */
    if(cls){
        (*env)->ThrowNew(env, cls, msg);
    }
    /* free the local ref */
    (*env)->DeleteLocalRef(env, cls);
}

/*
 * Class:     top_kwseeker_jni_exception_CatchThrow
 * Method:    doIt
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_top_kwseeker_jni_exception_CatchThrow_doIt
        (JNIEnv * env, jobject obj){
    jthrowable exc;
    jclass cls = (*env)->GetObjectClass(env, obj);
    jmethodID mid = (*env)->GetMethodID(env, cls, "callback", "()V");
    if(!mid){
        return;
    }
    (*env)->CallVoidMethod(env, obj, mid);

    exc = (*env)->ExceptionOccurred(env);
    if(exc){
        //打印异常信息，然后清空异常信息，最后抛出新的异常 IllegalArgumentException
        (*env)->ExceptionDescribe(env);
        (*env)->ExceptionClear(env);
        JNU_ThrowByName(env, "java/lang/IllegalArgumentException", "Throw from C code");
    }
}

jvalue JNU_CallMethodByName(JNIEnv *env, jboolean * hasException, jobject obj, const char * name, const char *descriptor, ...){
    va_list args;
    jclass clazz;
    jmethodID mid;
    jvalue result;
    result.l = NULL;
    if((*env)->EnsureLocalCapacity(env, 2) == JNI_OK) {
        clazz = (*env)->GetObjectClass(env, obj);
        mid = (*env)->GetMethodID(env, clazz, name, descriptor);
        if(mid){
            const char *p = descriptor;
            /*skip over argument types to find out the return type */
            while(*p != ')') p++;
            /* skip ')' */
            p ++;
            va_start(args, descriptor);
            switch(*p){
                case 'V':
                    (*env)->CallVoidMethod(env, obj, mid, args);
                    break;
                case '[':
                case 'L':
                    result.l = (*env)->CallObjectMethodV(env, obj, mid, args);
                    break;
                case 'Z':
                    result.z = (*env)->CallBooleanMethodV(env, obj, mid, args);
                    break;
                case 'B':
                    result.b = (*env)->CallByteMethodV(env, obj, mid, args);
                    break;
                case 'C':
                    result.c = (*env)->CallCharMethodV(env, obj, mid, args);
                    break;
                case 'S':
                    result.s = (*env)->CallShortMethodV(env, obj, mid, args);
                    break;
                case 'I':
                    result.i = (*env)->CallIntMethodV(env, obj, mid, args);
                    break;
                case 'J':
                    result.j = (*env)->CallLongMethodV(env, obj, mid, args);
                    break;
                case 'F':
                    result.f = (*env)->CallFloatMethodV(env, obj, mid, args);
                    break;
                case 'D':
                    result.d = (*env)->CallDoubleMethodV(env, obj, mid, args);
                    break;
                default:
                    (*env)->FatalError(env, "illegal descriptor");
            }
            va_end(args);
        }
        (*env)->DeleteLocalRef(env, clazz);
    }
    if(hasException){
        *hasException = (*env)->ExceptionCheck(env);
    }
    return result;
}