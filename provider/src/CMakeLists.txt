add_library(hello SHARED hello.c)
add_library(prompt SHARED prompt.c)
add_library(array SHARED array.c)
add_library(fieldAccess SHARED fieldAccess.c)
add_library(methodCall SHARED methodCall.c)
# 其实上面这些都可以直接打包到同一个.so库文件