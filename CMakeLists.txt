# 指定cmake版本
cmake_minimum_required(VERSION 3.10)

# 设置项目名称
project(LinuxLearning)

# 添加编译参数 -O0  -fno-elide-constructors 
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g  -fno-elide-constructors -Wall ")    
#-O2 可能会优化代码结构，
#不便于调试-fno-elide-constructors: 主要对临时变量的优化效果
# -fno-elide-constructors

# 设置代码构建级别为 Debug 方式
# set(CMAKE_BUILD_TYPE Debug)

#message(${CMAKE_CXX_FLAGS})

# 包含目录 头文件目录
include_directories( ${CMAKE_SOURCE_DIR}/include )
include_directories( ${CMAKE_SOURCE_DIR}/src )
#include_directories( include )

#message( ${CMAKE_SOURCE_DIR})
#link_directories(/usr/lib/mylibfolder ./lib)



# add_executable(fileTest  src/file.cpp)
# target_compile_definitions(fileTest PRIVATE  DEBUG)

# add_executable(processTest  src/process.cpp)
# target_compile_definitions(processTest PRIVATE  DEBUG)

# add_executable(tempTest  src/test.cpp)
# target_compile_definitions(tempTest PRIVATE  DEBUG)

# add_executable(pthreadTest  src/pthread.cpp)
# target_compile_definitions(pthreadTest PRIVATE  DEBUG)
# target_link_libraries(pthreadTest log4cpp pthread)

add_executable(serverTest  src/server.cpp)
target_compile_definitions(serverTest PRIVATE  DEBUG ) #NETWORK

add_executable(clinetTest  src/client.cpp)
target_compile_definitions(clinetTest PRIVATE  DEBUG ) #NETWORK