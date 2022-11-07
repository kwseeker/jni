# JNI 编程指南

## JNI的作用

用于支持调用本地代码（本地代码个人理解应该是指的平台相关的代码，即系统本地提供的底层能力的接口等），通过调用本地代码克服一些内存管理、性能问题以及借用底层能力。

如果想从 Java 上层深入到 JVM 底层，甚至 Linux 底层，JNI是绕不过去的。

> 之前做Android驱动开发时，Android 设备 Service 和 底层 Linux 设备驱动全部是通过JNI连接的。

本Demo代码全部来自后面的资料。



## JNI工作原理

### 原理

暂时没找到实现原理相关资料。

不过从已有的资料看，**JNI的工作很简单就是作为Java和本地代码之间的桥梁，将Java调用转成本地调用**（单纯从使用上看跟RPC好像），包括：

Java调用本地方法时，将Java参数类型转成本地方法类型，执行本地方法后，将结果从本地类型转成Java类型返回；

其中可能还涉及一些语言差异而额外需要的操作，比如：

1）变量内存分配、释放

2）各种方法和数据类型的细节处理

3）引用管理

4）异常处理

5）附加本地线程

### 优缺点

优点：

+ 可以使用Java不提供的特殊的本地系统环境能力
+ 直接使用本地库高性能代码，降低性能损耗

缺点：

+ 程序不再跨平台（JDK自带的本地方法也是依赖不同平台的JVM, 或者说在每种平台上都有一套实现）
+ 程序不再绝对安全（本地代码的不当使用可能导致整个程序崩溃）

避免使用JNI的一些方法：

+ 比如使用TCP/IP、IPC等通信技术（这些本身也是要通过JNI调用实现，但是可以减少JNI的使用）

  比如数据库驱动JDBC API其实核心也是网络通信。

## JNI开发

### 开发环境搭建 & JNI调试配置

用的 IDEA + Clion CMake 的方式，搭建教程网上随便搜，主要是可能需要了解下CMake的使用，以及CMakeLists的编写。

配置CMake的时候遇到了个坑，就是本地环境变量明明配置了JAVA_HOME，但是 $ENV{JAVA_HOME} 的识别还是为空，最后只能手动再set一下。

```cmake
if(DEFINED ENV{JAVA_HOME})
    message("JAVA_HOME: $ENV{JAVA_HOME}")
else()
    message("NOT DEFINED JAVA_HOME VARIABLES")
    # TODO $ENV{JAVA_HOME} 已经配置了为何识别不到
    set(ENV{JAVA_HOME} "/usr/lib/jvm/java-1.8.0-openjdk-amd64")
endif()
# 引入JNI本地库编译依赖的头文件和库
set(JAVA_AWT_LIBRARY "$ENV{JAVA_HOME}/lib/amd64/libjawt.so")
set(JAVA_JVM_LIBRARY "$ENV{JAVA_HOME}/jre/lib/amd64/server/libjvm.so")
set(JAVA_INCLUDE_PATH "$ENV{JAVA_HOME}/include")
set(JAVA_INCLUDE_PATH2 "$ENV{JAVA_HOME}/include/linux")
set(JAVA_AWT_INCLUDE_PATH "$ENV{JAVA_HOME}/include")
```

调试的话，IDEA开启调试模式，然后将CLion调试器关联到Java进程即可（搜索 “Attach to Process ...”）。

一键生成本地方法头文件（External Tools配置）：

```tex
$JDKPath$/bin/javah
-jni -classpath $OutputPath$ -d ./jni $FileClass$
$ProjectFileDir$
```

### JNI开发流程

1. 创建一个 Java 类声明本地方法；

   ```java
   private native void sayHello();
   ```

2. 使用 javac 编译源文件，获取 class 文件，使用 javah -jni 指令生成 C 语言头文件，头文件包含本地方法函数原型；

   ```c
   JNIEXPORT void JNICALL Java_top_kwseeker_jni_hello_HelloJNI_sayHello
     (JNIEnv *, jobject);
   ```

3. 用 C/C++ 实现函数原型；

   ```c
   JNIEXPORT void JNICALL Java_top_kwseeker_jni_hello_HelloJNI_sayHello(JNIEnv *env, jobject obj) {
       printf("Hello JNI!\n");
   }
   ```

4. 编译 C/C++ 函数实现为本地库（Linux下是so文件，Window下是dll文件）；

5. 使用 System.loadLibrary() 加载本地库并执行。

   ```java
   System.loadLibrary("hello")
   ```

### JNI接口定义 & 调用

#### JNI函数定义

```C
//					   Java_<.....Java调用者全限定类名......>_<方法名称> 
JNIEXPORT void JNICALL Java_top_kwseeker_jni_hello_HelloJNI_sayHello(JNIEnv *, jobject, ...);
// JNIEXPORT JNICALL 这两个宏确保函数在本地库外可见
// JNIEnv* 指向一个个函数表，函数表中每一个入口指向一个JNI函数，本地方法通过这些函数访问JVM中的数据结构
// jobject Java方法如果是非静态的就是this对象引用，否则是Java类引用
```

**数据类型映射**：

jni类型就是在jni头文件中定义的，对于基本类型的jni类型C/C++可以直接使用（看定义就能理解为何可以直接用了）。比如

```c
typedef int jint;
typedef signed char jbyte;
typedef unsigned char   jboolean;
typedef unsigned short  jchar;
typedef jint            jsize;
```

由于非基本类型传递到C/C++是指针类型，指针类型访问内部数据需要先知道数据结构，这里就需要使用函数表中的函数将jni非基本类型转成C/C++具体类型。

```c
struct _jobject;
typedef struct _jobject *jobject;	//抽象的结构体指针类型

typedef jobject jclass;
typedef jobject jthrowable;
typedef jobject jstring;
typedef jobject jarray;

typedef jarray jbooleanArray;
typedef jarray jbyteArray;
typedef jarray jcharArray;
typedef jarray jshortArray;
typedef jarray jintArray;
typedef jarray jlongArray;
typedef jarray jfloatArray;
typedef jarray jdoubleArray;
typedef jarray jobjectArray;
```

映射表：

| java    | jni header   | c/c++           | java                | jni header                                                   | c/c++           |
| ------- | ------------ | --------------- | ------------------- | ------------------------------------------------------------ | --------------- |
| int     | jint / jsize | jint (直接使用) | java.lang.Class     | jclass                                                       |                 |
| byte    | jbyte        | 同上            | java.lang.String    | jstring                                                      | char * / string |
| short   | jshort       | 同上            | java.lang.Throwable | jthrowable                                                   |                 |
| long    | jlong        | 同上            | T[]                 | jintArray, jbyteArray, jshortArray, <br />jlongArray, jfloatArray, jdoubleArray, jcharArray, jbooleanArray, jobjectArray | int[] ...       |
| float   | jfloat       | 同上            | Java.lang.Object    | jobject                                                      |                 |
| double  | jdouble      | 同上            |                     |                                                              |                 |
| char    | jchar        | 同上            |                     |                                                              |                 |
| boolean | jboolean     | 同上            |                     |                                                              |                 |

**数据类型转换：**

相关的处理函数全部在 jni.h 中定义，实现没有搜到在哪里。

```c
// jni jstring -> c char*
char *inCStr = (*env)->GetStringUTFChars(env, inJNIStr, NULL);
(*env)->ReleaseStringUTFChars(env, inJNIStr, inCStr);	//还要释放资源
// c char* -> jni jstring
jstring outJNIStr = (*env)->NewStringUTF(env, outCStr);


```





## 参考资料

+ [Java Native Interface Specification Contents](https://docs.oracle.com/en/java/javase/18/docs/specs/jni/)
+ [Java Programming Tutorial Java Native Interface (JNI)](https://www3.ntu.edu.sg/home/ehchua/programming/java/JavaNativeInterface.html)

+ 《JNI编程指南》
+ 《Java JNI 编程进阶》