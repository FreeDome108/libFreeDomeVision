#!/bin/bash

echo "Building anAntaDigital for Avrora..."

# Create build directory
mkdir -p build_avrora
cd build_avrora

# Configure for Avrora
cmake .. \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_SYSTEM_NAME=Avrora \
    -DCMAKE_CXX_COMPILER=avr-g++ \
    -DCMAKE_C_COMPILER=avr-gcc \
    -DCMAKE_CXX_FLAGS="-mmcu=atmega328p -Os -Wall -Wextra" \
    -DCMAKE_C_FLAGS="-mmcu=atmega328p -Os -Wall -Wextra" \
    -DBUILD_SHARED_LIBS=OFF \
    -DBUILD_TESTS=OFF \
    -DBUILD_EXAMPLES=OFF \
    -DENABLE_QUANTUM_FEEDBACK=ON

# Build
make -j$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)

if [ $? -eq 0 ]; then
    echo "Avrora build successful!"
else
    echo "Avrora build failed!"
    exit 1
fi

echo "Avrora build completed!"
