add_library(hello SHARED hello.c)
add_library(prompt SHARED prompt.c)
add_library(array SHARED array.c)
add_library(fieldAccess SHARED fieldAccess.c)
add_library(methodCall SHARED methodCall.c)
# 其实上面这些都可以直接打包到同一个.so库文件
add_library(family SHARED catchThrow.c)

message(STATUS "JNI_LIBRARIES = " ${JNI_LIBRARIES})

add_executable(invoke invoke.c)
target_link_libraries(invoke ${JNI_LIBRARIES})  # 还得手动Link

add_executable(attach attach.c)
find_package(Threads)
target_link_libraries(attach ${JNI_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})