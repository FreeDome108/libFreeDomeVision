#!/bin/bash

set -e

echo "Building anAntaDigital for Avrora..."

# Check if Avrora tools are available
if ! command -v avr-gcc &> /dev/null; then
    echo "AVR-GCC not found. Please install AVR toolchain:"
    echo "On Ubuntu/Debian: sudo apt-get install gcc-avr avr-libc"
    echo "On macOS: brew install avr-libc"
    echo "On Windows: Download AVR Studio or WinAVR"
    exit 1
fi

# Create build directory
mkdir -p build_avrora
cd build_avrora

# Configure for Avrora
cmake .. \
    -DCMAKE_BUILD_TYPE=Release \
    -DBUILD_SHARED_LIBS=OFF \
    -DBUILD_TESTS=OFF \
    -DBUILD_EXAMPLES=OFF \
    -DENABLE_QUANTUM_FEEDBACK=ON \
    -DCMAKE_SYSTEM_NAME=Avrora \
    -DCMAKE_C_COMPILER=avr-gcc \
    -DCMAKE_CXX_COMPILER=avr-g++ \
    -DCMAKE_INSTALL_PREFIX=${PWD}/install

# Build
make -j$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)

# Install
make install

echo "Avrora build completed successfully!"
echo "Library installed to ${PWD}/install"
echo "Headers installed to ${PWD}/install/include/anantadigital"

# Show library information
echo "AVR library created:"
ls -la install/lib/
