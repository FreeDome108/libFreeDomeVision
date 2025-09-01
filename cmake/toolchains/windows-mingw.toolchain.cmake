# Windows MinGW Cross-Compilation Toolchain for anAntaDigital
# Usage: cmake -DCMAKE_TOOLCHAIN_FILE=cmake/toolchains/windows-mingw.toolchain.cmake

# Set minimum CMake version
cmake_minimum_required(VERSION 3.16)

# MinGW prefix
if(NOT DEFINED MINGW_PREFIX)
    set(MINGW_PREFIX x86_64-w64-mingw32)
endif()

# Set system name
set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_PROCESSOR x86_64)

# Set compilers
set(CMAKE_C_COMPILER ${MINGW_PREFIX}-gcc)
set(CMAKE_CXX_COMPILER ${MINGW_PREFIX}-g++)
set(CMAKE_RC_COMPILER ${MINGW_PREFIX}-windres)

# Set find root path mode
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

# Windows-specific definitions
add_definitions(-DWIN32)
add_definitions(-D_WIN32)
add_definitions(-DWIN64)
add_definitions(-D_WIN64)
add_definitions(-D_WINDOWS)

# Set compiler flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -O3")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O3")

# Set linker flags
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -static-libgcc -static-libstdc++")

# Windows libraries
set(WINDOWS_LIBS
    kernel32
    user32
    gdi32
    winspool
    shell32
    ole32
    oleaut32
    uuid
    comctl32
    comdlg32
    advapi32
    ws2_32
    msvcrt
    m
    z
)

# Set Windows link libraries
set(CMAKE_CXX_STANDARD_LIBRARIES ${WINDOWS_LIBS})

# Windows-specific include paths
include_directories(
    /usr/${MINGW_PREFIX}/include
    /usr/${MINGW_PREFIX}/include/c++/$(shell ${MINGW_PREFIX}-gcc -dumpversion)
)

# Windows-specific link directories
link_directories(
    /usr/${MINGW_PREFIX}/lib
    /usr/${MINGW_PREFIX}/lib64
)

# Set Windows-specific properties
set_property(GLOBAL PROPERTY TARGET_SUPPORTS_SHARED_LIBS TRUE)

# Windows DLL export/import definitions
if(BUILD_SHARED_LIBS)
    add_definitions(-DANANTADIGITAL_EXPORTS)
else()
    add_definitions(-DANANTADIGITAL_STATIC)
endif()

# Windows-specific compiler definitions
add_definitions(-D_CRT_SECURE_NO_WARNINGS)
add_definitions(-D_WINSOCK_DEPRECATED_NO_WARNINGS)

# Windows-specific linker definitions
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-D_DEBUG)
    add_definitions(-DDEBUG)
endif()

# Windows-specific optimization flags
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -DNDEBUG")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -DNDEBUG")
endif()
