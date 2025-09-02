# Avrora toolchain file for anAntaDigital
set(CMAKE_SYSTEM_NAME Avrora)
set(CMAKE_SYSTEM_PROCESSOR avr)

# Set AVR compiler
set(CMAKE_C_COMPILER avr-gcc)
set(CMAKE_CXX_COMPILER avr-g++)

# Set AVR flags
set(CMAKE_C_FLAGS "-mmcu=atmega328p -Os -Wall -Wextra")
set(CMAKE_CXX_FLAGS "-mmcu=atmega328p -Os -Wall -Wextra")

# Disable shared libraries for AVR
set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build shared libraries" FORCE)

# Disable tests and examples for AVR
set(BUILD_TESTS OFF CACHE BOOL "Build tests" FORCE)
set(BUILD_EXAMPLES OFF CACHE BOOL "Build examples" FORCE)
