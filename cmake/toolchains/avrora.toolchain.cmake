# Avrora/AVR Toolchain for anAntaDigital
# Usage: cmake -DCMAKE_TOOLCHAIN_FILE=cmake/toolchains/avrora.toolchain.cmake

# Set minimum CMake version
cmake_minimum_required(VERSION 3.16)

# AVR microcontroller
if(NOT DEFINED AVR_MCU)
    set(AVR_MCU atmega328p)
endif()

# AVR frequency
if(NOT DEFINED AVR_FREQ)
    set(AVR_FREQ 16000000)
endif()

# AVR programmer
if(NOT DEFINED AVR_PROGRAMMER)
    set(AVR_PROGRAMMER usbasp)
endif()

# Set system name
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR avr)

# Set compilers
set(CMAKE_C_COMPILER avr-gcc)
set(CMAKE_CXX_COMPILER avr-g++)

# Set find root path mode
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

# AVR-specific definitions
add_definitions(-DAVR)
add_definitions(-DF_CPU=${AVR_FREQ}UL)
add_definitions(-D__AVR_ATmega328P__)

# Set compiler flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mmcu=${AVR_MCU} -Os -Wall -Wextra")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mmcu=${AVR_MCU} -Os -Wall -Wextra")

# Set linker flags
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mmcu=${AVR_MCU} -Wl,--gc-sections")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -mmcu=${AVR_MCU} -Wl,--gc-sections")

# AVR libraries
set(AVR_LIBS
    m
    c
    gcc
)

# Set AVR link libraries
set(CMAKE_CXX_STANDARD_LIBRARIES ${AVR_LIBS})

# AVR-specific include paths
include_directories(
    /usr/avr/include
    /usr/local/avr/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# AVR-specific link directories
link_directories(
    /usr/avr/lib
    /usr/local/avr/lib
)

# Set AVR-specific properties
set_property(GLOBAL PROPERTY TARGET_SUPPORTS_SHARED_LIBS FALSE)

# AVR size command
set(AVR_SIZE_COMMAND avr-size)

# AVR objcopy command
set(AVR_OBJCOPY_COMMAND avr-objcopy)

# AVR upload command
set(AVR_UPLOAD_COMMAND avrdude)

# Function to create AVR hex file
function(create_avr_hex TARGET_NAME)
    add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
        COMMAND ${AVR_OBJCOPY_COMMAND} -O ihex -R .eeprom $<TARGET_FILE:${TARGET_NAME}> ${TARGET_NAME}.hex
        COMMENT "Creating hex file for ${TARGET_NAME}"
    )
endfunction()

# Function to upload to AVR
function(upload_to_avr TARGET_NAME)
    add_custom_target(upload_${TARGET_NAME}
        COMMAND ${AVR_UPLOAD_COMMAND} -c ${AVR_PROGRAMMER} -p ${AVR_MCU} -U flash:w:${TARGET_NAME}.hex:i
        DEPENDS ${TARGET_NAME}
        COMMENT "Uploading ${TARGET_NAME} to ${AVR_MCU}"
    )
endfunction()
