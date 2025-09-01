# Android NDK Toolchain for anAntaDigital
# Usage: cmake -DCMAKE_TOOLCHAIN_FILE=cmake/toolchains/android.toolchain.cmake

# Set minimum CMake version
cmake_minimum_required(VERSION 3.16)

# Android NDK path (can be overridden)
if(NOT DEFINED ANDROID_NDK)
    set(ANDROID_NDK $ENV{ANDROID_NDK})
endif()

if(NOT ANDROID_NDK)
    message(FATAL_ERROR "ANDROID_NDK not set. Please set ANDROID_NDK environment variable or pass -DANDROID_NDK=<path>")
endif()

# Android API level
if(NOT DEFINED ANDROID_API_LEVEL)
    set(ANDROID_API_LEVEL 21)
endif()

# Android ABI
if(NOT DEFINED ANDROID_ABI)
    set(ANDROID_ABI arm64-v8a)
endif()

# Android STL
if(NOT DEFINED ANDROID_STL)
    set(ANDROID_STL c++_shared)
endif()

# Set system name
set(CMAKE_SYSTEM_NAME Android)
set(CMAKE_SYSTEM_VERSION ${ANDROID_API_LEVEL})

# Set compilers
set(CMAKE_C_COMPILER ${ANDROID_NDK}/toolchains/llvm/prebuilt/linux-x86_64/bin/clang)
set(CMAKE_CXX_COMPILER ${ANDROID_NDK}/toolchains/llvm/prebuilt/linux-x86_64/bin/clang++)

# Set sysroot
set(CMAKE_SYSROOT ${ANDROID_NDK}/toolchains/llvm/prebuilt/linux-x86_64/sysroot)

# Set target environment
set(CMAKE_FIND_ROOT_PATH ${CMAKE_SYSROOT})

# Set compiler flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --target=${ANDROID_ABI}-none-linux-android${ANDROID_API_LEVEL}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --target=${ANDROID_ABI}-none-linux-android${ANDROID_API_LEVEL}")

# Set linker flags
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --target=${ANDROID_ABI}-none-linux-android${ANDROID_API_LEVEL}")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} --target=${ANDROID_ABI}-none-linux-android${ANDROID_API_LEVEL}")

# Set find root path mode
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

# Android-specific definitions
add_definitions(-DANDROID)
add_definitions(-D__ANDROID_API__=${ANDROID_API_LEVEL})

# Set pkg-config path
set(PKG_CONFIG_EXECUTABLE ${ANDROID_NDK}/toolchains/llvm/prebuilt/linux-x86_64/bin/pkg-config)

# Android NDK specific paths
set(ANDROID_NDK_INCLUDE_DIR ${ANDROID_NDK}/sources/cxx-stl/llvm-libc++/include)
set(ANDROID_NDK_LIB_DIR ${ANDROID_NDK}/sources/cxx-stl/llvm-libc++/libs/${ANDROID_ABI})

# Include directories
include_directories(${ANDROID_NDK_INCLUDE_DIR})
include_directories(${ANDROID_NDK}/sources/android/native_app_glue)

# Link directories
link_directories(${ANDROID_NDK_LIB_DIR})

# Set Android STL library
if(ANDROID_STL STREQUAL "c++_shared")
    set(ANDROID_STL_LIB c++_shared)
elseif(ANDROID_STL STREQUAL "c++_static")
    set(ANDROID_STL_LIB c++_static)
elseif(ANDROID_STL STREQUAL "gnustl_shared")
    set(ANDROID_STL_LIB gnustl_shared)
elseif(ANDROID_STL STREQUAL "gnustl_static")
    set(ANDROID_STL_LIB gnustl_static)
endif()

# Set Android libraries
set(ANDROID_LIBS
    ${ANDROID_STL_LIB}
    android
    log
    EGL
    GLESv3
    OpenSLES
)

# Set Android link libraries
set(CMAKE_CXX_STANDARD_LIBRARIES ${ANDROID_LIBS})
