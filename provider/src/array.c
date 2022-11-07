#include "top_kwseeker_jni_array_Array.h"
#include <jni.h>
#include <stdio.h>

JNIEXPORT void JNICALL Java_top_kwseeker_jni_array_Array_sayHello(JNIEnv *env, jobject obj) {
    printf("Hello JNI!\n");
}

JNIEXPORT jint JNICALL Java_top_kwseeker_jni_array_Array_sumArray
        (JNIEnv *env, jobject obj, jintArray array) {
    // 1 处理固定长度数组，如果传递数组长度不是10,下面GetIntArrayRegion()会抛ArrayIndexOutOfBoundsException
    //jint buf[10];
    //jint i, sum = 0;
    ////把 array 从0开始10个元素赋值到 buf 数组, 这个函数适合固定长度的少量值的数组
    //(*env)->GetIntArrayRegion(env, array, 0, 10, buf);
    //for (i = 0; i < sizeof(buf) / sizeof(buf[0]); ++i) {
    //    sum += buf[i];
    //}
    //return sum;

    // 2 仍然需要知道数组长度，C/C++没法只通过指针判断数组长度
    jint *cArr;
    jint num = 0;
    //获取指向 jintArray类型数组的指针
    cArr = (*env)->GetIntArrayElements(env, array, NULL);
    if(cArr == NULL) {
        return 0;
    }
    for (int i = 0; i < 10; ++i) {
        num += cArr[i];
    }
    //释放指针
    //mode:0 刷新 Java 数组 , 释放 C/C++ 数组
    //mode:2 不刷新 Java 数组 , 释放 C/C++ 数组
    //(*env)->ReleaseIntArrayElements(env, array, cArr, 0);
    (*env)->ReleaseIntArrayElements(env, array, cArr, 2);
    return num;
}

/**
 * 静态本地方法，第二个参数是类对象，二维数组被当作 [I 对象的数组
 */
JNIEXPORT jobjectArray JNICALL Java_top_kwseeker_jni_array_Array_initInt2DArray
        (JNIEnv *env, jclass cls, jint size) {
    jobjectArray result;
    int i;

    //获取int类型二维数组类对象的引用
    jclass intArrCls = (*env)->FindClass(env, "[I");
    if (!intArrCls) {
        return NULL; /* exception thrown */
    }
    //分配对象数组，需要上面的intArrCls, JNI才知道要怎么分配内存
    result = (*env)->NewObjectArray(env, size, intArrCls, NULL);
    if (!result) {
        return NULL; /* out of memory error thrown */
    }
    for (i = 0; i < size; ++i) {
        jint tmp[256]; /* make sure it is large enough! */
        int j;
        //对象数组分配完成后每个对象内部也要分配内存
        jintArray iArr = (*env)->NewIntArray(env, size);
        if (!iArr) {
            return NULL;
        }
        for (j = 0; j < size; j++) {    //只是赋值
            tmp[j] = i + j;
        }

        (*env)->SetIntArrayRegion(env, iArr, 0, size, tmp);
        (*env)->SetObjectArrayElement(env, result, i, iArr);
        //本地引用还要手动释放，C++ 也需要释放局部引用么？
        (*env)->DeleteLocalRef(env, iArr);
    }
    return result;
}
