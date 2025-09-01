#!/bin/bash

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
    -DENABLE_QUANTUM_FEEDBACK=ON

# Build
make -j$(nproc)

# Run tests
if [ $? -eq 0 ]; then
    echo "Build successful! Running tests..."
    make test
else
    echo "Build failed!"
    exit 1
fi

# Install (optional)
echo "Installing to /usr/local..."
sudo make install

echo "Linux build completed!"
