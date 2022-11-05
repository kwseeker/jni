# JNI 编程指南

## JNI的作用

用于支持调用本地代码（本地代码个人理解应该是指的平台相关的代码，即系统本地提供的底层能力的接口等），通过调用本地代码克服一些内存管理以及性能问题。



## JNI开发流程

### JNI接口定义 & 调用

JNI函数定义组成：

+ Java关键字
+ 调用者全限定类名
+ 方法名称

参数组成：

+ JNIEnv *

+ 如果本地方法是非静态的则是对象引用，否则是Java类引用

+ Java 本地方法的参数

  



## 参考资料

+ [Java Native Interface Specification Contents](https://docs.oracle.com/en/java/javase/18/docs/specs/jni/)
+ [Java Programming Tutorial Java Native Interface (JNI)](https://www3.ntu.edu.sg/home/ehchua/programming/java/JavaNativeInterface.html)

+ 《JNI编程指南》
+ 《Java JNI 编程进阶》