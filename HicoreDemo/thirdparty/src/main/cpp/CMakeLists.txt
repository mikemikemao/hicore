PROJECT(thirdparty C CXX)
CMAKE_MINIMUM_REQUIRED(VERSION 3.10.2)

ADD_SUBDIRECTORY(libosip2)
ADD_SUBDIRECTORY(libeXosip2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

set(jnilibs ${CMAKE_SOURCE_DIR}/../jniLibs)
set(libname thridparty)

include_directories(
        ${CMAKE_SOURCE_DIR}/
        ${CMAKE_SOURCE_DIR}/utils
        libosip2/include
        libeXosip2/include
)

link_directories(
        ${jnilibs}/${ANDROID_ABI}
)

file(GLOB src-files
        ${CMAKE_SOURCE_DIR}/*.cpp
        ${CMAKE_SOURCE_DIR}/utils/*.cpp
        )

add_library( # Sets the name of the library.
        ${libname}
        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        ${src-files}
        )

#导入第三方so包，并声明为 IMPORTED 属性，指明只是想把 so 导入到项目中
add_library(
        libeXosip2
        SHARED
        IMPORTED
)
add_library(
        libosip2
        SHARED
        IMPORTED
)
add_library(
        libosipparser2
        SHARED
        IMPORTED
)

#指明 so 库的路径，CMAKE_SOURCE_DIR 表示 CMakeLists.txt 的路径
set_target_properties(
        libeXosip2
        PROPERTIES IMPORTED_LOCATION
        ${CMAKE_SOURCE_DIR}/../jniLibs/arm64-v8a/libeXosip2.so)
set_target_properties(
        libosip2
        PROPERTIES IMPORTED_LOCATION
        ${CMAKE_SOURCE_DIR}/../jniLibs/arm64-v8a/libosip2.so)
set_target_properties(
        libosipparser2
        PROPERTIES IMPORTED_LOCATION
        ${CMAKE_SOURCE_DIR}/../jniLibs/arm64-v8a/libosipparser2.so)

#指明头文件路径，不然会提示找不到 so 的方法
include_directories(${CMAKE_SOURCE_DIR}/libosip2/include)
include_directories(${CMAKE_SOURCE_DIR}/libeXosip2/include)

set(native-libs
        android
        log
        mediandk
        binder_ndk
        m
        z
        )

target_link_libraries( # Specifies the target library.
        ${libname}
        libeXosip2
        libosip2
        libosipparser2
        # Links the target library to the log library
        # included in the NDK.
        ${log-lib}
        ${native-libs}
        )