# Sets the minimum version of CMake required to build the native library.
cmake_minimum_required(VERSION 3.10.2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++17")

set(jnilibs ${CMAKE_SOURCE_DIR}/../jniLibs)
set(libname hicore)

include_directories(
        ${CMAKE_SOURCE_DIR}/
        ${CMAKE_SOURCE_DIR}/utils
        ${CMAKE_SOURCE_DIR}/include
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

set(native-libs
        android
        log
        mediandk
        binder_ndk
        m
        z
        )

find_library (
        binder_ndk-lib
        binder_ndk
)
add_library(
        libixml
        STATIC
        IMPORTED
)
add_library(
        libcrypto
        STATIC
        IMPORTED
)
add_library(
        libssl
        STATIC
        IMPORTED
)

#指明 so 库的路径，CMAKE_SOURCE_DIR 表示 CMakeLists.txt 的路径
set_target_properties(
        libixml
        PROPERTIES IMPORTED_LOCATION
        ${CMAKE_SOURCE_DIR}/../jniLibs/arm64-v8a/libixml.a)
#指明 so 库的路径，CMAKE_SOURCE_DIR 表示 CMakeLists.txt 的路径
set_target_properties(
        libcrypto
        PROPERTIES IMPORTED_LOCATION
        ${CMAKE_SOURCE_DIR}/../jniLibs/arm64-v8a/libcrypto.a)
#指明 so 库的路径，CMAKE_SOURCE_DIR 表示 CMakeLists.txt 的路径
set_target_properties(
        libssl
        PROPERTIES IMPORTED_LOCATION
        ${CMAKE_SOURCE_DIR}/../jniLibs/arm64-v8a/libssl.a)


target_link_libraries( # Specifies the target library.
        ${libname}
        # Links the target library to the log library
        # included in the NDK.
        libixml
        libcrypto
        libssl
        ${log-lib}
        ${native-libs}
        )