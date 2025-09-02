# Android toolchain file for anAntaDigital
set(CMAKE_SYSTEM_NAME Android)
set(CMAKE_SYSTEM_VERSION 21)
set(CMAKE_ANDROID_ARCH_ABI arm64-v8a)
set(CMAKE_ANDROID_NDK_TOOLCHAIN_VERSION clang
set(CMAKE_ANDROID_STL_TYPE c++_shared

# Set compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -Wall -Wextra -O3")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC -Wall -Wextra -O3")

# Disable tests and examples for Android
set(BUILD_TESTS OFF CACHE BOOL "Build tests" FORCE)
set(BUILD_EXAMPLES OFF CACHE BOOL "Build examples" FORCE)
