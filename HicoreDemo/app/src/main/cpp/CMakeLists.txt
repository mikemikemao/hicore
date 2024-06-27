# Sets the minimum version of CMake required to build the native library.
cmake_minimum_required(VERSION 3.10.2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++17")

set(jnilibs ${CMAKE_SOURCE_DIR}/../jniLibs)
set(libname hicore)

include_directories(
        ${CMAKE_SOURCE_DIR}/
        ${CMAKE_SOURCE_DIR}/utils
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/include/hpr
        ${CMAKE_SOURCE_DIR}/include/aip
        ${CMAKE_SOURCE_DIR}/include/lst
        ${CMAKE_SOURCE_DIR}/include/securec
        ${CMAKE_SOURCE_DIR}/include/cjson
        ${CMAKE_SOURCE_DIR}/include/hwsdk
        ${CMAKE_SOURCE_DIR}/include/iconv
        ${CMAKE_SOURCE_DIR}/include/openssl
        ${CMAKE_SOURCE_DIR}/include/posixWrapper
        ${CMAKE_SOURCE_DIR}/include/secu_storage
        ${CMAKE_SOURCE_DIR}/include/sntp
        ${CMAKE_SOURCE_DIR}/include/sqlcipher
        ${CMAKE_SOURCE_DIR}/include/util_encrypt
        ${CMAKE_SOURCE_DIR}/include/bsp
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
add_library(
        libaip
        STATIC
        IMPORTED
)
add_library(
        libhpr
        STATIC
        IMPORTED
)
add_library(
        liblst
        STATIC
        IMPORTED
)
add_library(
        libsecurec
        STATIC
        IMPORTED
)
add_library(
        libcjson
        STATIC
        IMPORTED
)
add_library(
        libddm
        SHARED
        IMPORTED
)
add_library(
        libhwsdk
        SHARED
        IMPORTED
)
add_library(
        libiconv
        STATIC
        IMPORTED
)
add_library(
        liblog4j
        STATIC
        IMPORTED
)
add_library(
        libposix_wrapper
        STATIC
        IMPORTED
)
add_library(
        libsecurity
        STATIC
        IMPORTED
)
add_library(
        libsntp
        STATIC
        IMPORTED
)
add_library(
        libsqlcipher
        STATIC
        IMPORTED
)
add_library(
        libutil_encrypt
        STATIC
        IMPORTED
)
add_library(
        libsafefunc
        SHARED
        IMPORTED
)

add_library(
        libbsp_data_encrypt
        SHARED
        IMPORTED
)
add_library(
        libbsp
        SHARED
        IMPORTED
)
add_library(
        libcrypto11
        SHARED
        IMPORTED
)
add_library(
        libssl11
        SHARED
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
set_target_properties(
        libaip
        PROPERTIES IMPORTED_LOCATION
        ${CMAKE_SOURCE_DIR}/../jniLibs/arm64-v8a/libaip.a)
set_target_properties(
        libhpr
        PROPERTIES IMPORTED_LOCATION
        ${CMAKE_SOURCE_DIR}/../jniLibs/arm64-v8a/libhpr.a)
set_target_properties(
        liblst
        PROPERTIES IMPORTED_LOCATION
        ${CMAKE_SOURCE_DIR}/../jniLibs/arm64-v8a/liblst.a)
set_target_properties(
        libsecurec
        PROPERTIES IMPORTED_LOCATION
        ${CMAKE_SOURCE_DIR}/../jniLibs/arm64-v8a/libsecurec.a)
set_target_properties(
        libcjson
        PROPERTIES IMPORTED_LOCATION
        ${CMAKE_SOURCE_DIR}/../jniLibs/arm64-v8a/libcjson.a)
set_target_properties(
        libddm
        PROPERTIES IMPORTED_LOCATION
        ${CMAKE_SOURCE_DIR}/lib/libddm.so)
set_target_properties(
        libhwsdk
        PROPERTIES IMPORTED_LOCATION
        ${CMAKE_SOURCE_DIR}/lib/libhwsdk.so)
set_target_properties(
        libiconv
        PROPERTIES IMPORTED_LOCATION
        ${CMAKE_SOURCE_DIR}/../jniLibs/arm64-v8a/libiconv.a)
set_target_properties(
        liblog4j
        PROPERTIES IMPORTED_LOCATION
        ${CMAKE_SOURCE_DIR}/../jniLibs/arm64-v8a/liblog4j.a)
set_target_properties(
        libposix_wrapper
        PROPERTIES IMPORTED_LOCATION
        ${CMAKE_SOURCE_DIR}/../jniLibs/arm64-v8a/libposix_wrapper.a)
set_target_properties(
        libsecurity
        PROPERTIES IMPORTED_LOCATION
        ${CMAKE_SOURCE_DIR}/../jniLibs/arm64-v8a/libsecurity.a)
set_target_properties(
        libsntp
        PROPERTIES IMPORTED_LOCATION
        ${CMAKE_SOURCE_DIR}/../jniLibs/arm64-v8a/libsntp.a)
set_target_properties(
        libsqlcipher
        PROPERTIES IMPORTED_LOCATION
        ${CMAKE_SOURCE_DIR}/../jniLibs/arm64-v8a/libsqlcipher.a)
set_target_properties(
        libutil_encrypt
        PROPERTIES IMPORTED_LOCATION
        ${CMAKE_SOURCE_DIR}/../jniLibs/arm64-v8a/libutil_encrypt.a)
set_target_properties(
        libsafefunc
        PROPERTIES IMPORTED_LOCATION
        ${CMAKE_SOURCE_DIR}/lib/libsafefunc.so)
set_target_properties(
        libbsp_data_encrypt
        PROPERTIES IMPORTED_LOCATION
        ${CMAKE_SOURCE_DIR}/lib/libbsp_data_encrypt.so)
set_target_properties(
        libbsp
        PROPERTIES IMPORTED_LOCATION
        ${CMAKE_SOURCE_DIR}/lib/libbsp.so)
set_target_properties(
        libcrypto11
        PROPERTIES IMPORTED_LOCATION
        ${CMAKE_SOURCE_DIR}/../jniLibs/arm64-v8a/libcrypto.so.1.1)
set_target_properties(
        libssl11
        PROPERTIES IMPORTED_LOCATION
        ${CMAKE_SOURCE_DIR}/../jniLibs/arm64-v8a//libssl.so.1.1)

target_link_libraries( # Specifies the target library.
        ${libname}
        # Links the target library to the log library
        # included in the NDK.
        libixml
        libcrypto
        libssl
        libaip
        libhpr
        liblst
        libsecurec
        libcjson
        libddm
        libhwsdk
        libiconv
        liblog4j
        libposix_wrapper
        libsecurity
        libsntp
        libsqlcipher
        libutil_encrypt
        libsafefunc
        libbsp_data_encrypt
        libbsp
        libcrypto11
        libssl11
        ${log-lib}
        ${native-libs}
        )