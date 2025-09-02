#!/bin/bash

set -e

echo "Building anAntaDigital for Linux..."

# Create build directory
mkdir -p build_linux
cd build_linux

# Configure with CMake
cmake .. \
    -DCMAKE_BUILD_TYPE=Release \
    -DBUILD_SHARED_LIBS=ON \
    -DBUILD_TESTS=ON \
    -DBUILD_EXAMPLES=ON \
    -DENABLE_QUANTUM_FEEDBACK=ON \
    -DCMAKE_INSTALL_PREFIX=/usr/local

# Build
make -j$(nproc)

# Run tests
make test

# Install
sudo make install

echo "Linux build completed successfully!"
echo "Library installed to /usr/local/lib"
echo "Headers installed to /usr/local/include/anantadigital"
