# iOS Toolchain for anAntaDigital
# Usage: cmake -DCMAKE_TOOLCHAIN_FILE=cmake/toolchains/ios.toolchain.cmake

# Set minimum CMake version
cmake_minimum_required(VERSION 3.16)

# iOS deployment target
if(NOT DEFINED IOS_DEPLOYMENT_TARGET)
    set(IOS_DEPLOYMENT_TARGET 12.0)
endif()

# iOS architectures
if(NOT DEFINED IOS_ARCHITECTURES)
    set(IOS_ARCHITECTURES "arm64;x86_64")
endif()

# iOS platform (iphoneos, iphonesimulator)
if(NOT DEFINED IOS_PLATFORM)
    set(IOS_PLATFORM iphoneos)
endif()

# Set system name
set(CMAKE_SYSTEM_NAME iOS)

# Set deployment target
set(CMAKE_OSX_DEPLOYMENT_TARGET ${IOS_DEPLOYMENT_TARGET})

# Set architectures
set(CMAKE_OSX_ARCHITECTURES ${IOS_ARCHITECTURES})

# Set sysroot
if(IOS_PLATFORM STREQUAL "iphoneos")
    set(CMAKE_OSX_SYSROOT iphoneos)
elseif(IOS_PLATFORM STREQUAL "iphonesimulator")
    set(CMAKE_OSX_SYSROOT iphonesimulator)
endif()

# Set find root path mode
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

# iOS-specific definitions
add_definitions(-DIOS)
add_definitions(-DTARGET_OS_IPHONE=1)

# Set compiler flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fembed-bitcode")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fembed-bitcode")

# Set linker flags
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fembed-bitcode")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -fembed-bitcode")

# iOS frameworks
set(IOS_FRAMEWORKS
    Foundation
    CoreFoundation
    AudioToolbox
    AVFoundation
    CoreAudio
    Accelerate
    Security
    SystemConfiguration
)

# Set iOS libraries
set(IOS_LIBS
    ${IOS_FRAMEWORKS}
    c++
    m
    z
)

# Set iOS link libraries
set(CMAKE_CXX_STANDARD_LIBRARIES ${IOS_LIBS})

# iOS-specific include paths
include_directories(
    ${CMAKE_OSX_SYSROOT}/usr/include
    ${CMAKE_OSX_SYSROOT}/System/Library/Frameworks
)

# Set iOS-specific properties
set_property(GLOBAL PROPERTY TARGET_SUPPORTS_SHARED_LIBS FALSE)
