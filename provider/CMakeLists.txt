cmake_minimum_required(VERSION 3.23)
project(provider)

set(CMAKE_CXX_STANDARD 20)

if(DEFINED ENV{JAVA_HOME})
    message("JAVA_HOME: $ENV{JAVA_HOME}")
else()
    message("NOT DEFINED JAVA_HOME VARIABLES")
    #TODO $ENV{JAVA_HOME} 已经配置了为何识别不到
    set(ENV{JAVA_HOME} "/usr/lib/jvm/java-1.8.0-openjdk-amd64")
endif()
# 引入JNI依赖的头文件和库
# libjawt.so libjvm.so 没找到哪里有说这两个是库是做什么的，不过JNI编译确实需要它们
set(JAVA_AWT_LIBRARY "$ENV{JAVA_HOME}/lib/amd64/libjawt.so")
set(JAVA_JVM_LIBRARY "$ENV{JAVA_HOME}/jre/lib/amd64/server/libjvm.so")
set(JAVA_INCLUDE_PATH "$ENV{JAVA_HOME}/include")
set(JAVA_INCLUDE_PATH2 "$ENV{JAVA_HOME}/include/linux")
set(JAVA_AWT_INCLUDE_PATH "$ENV{JAVA_HOME}/include")

find_package(JNI REQUIRED)

include_directories(${JNI_INCLUDE_DIRS} ${JAVA_INCLUDE_PATH} ${JAVA_INCLUDE_PATH2})

include_directories(jni)

add_subdirectory(src)
