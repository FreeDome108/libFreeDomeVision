#!/bin/bash

echo "Building anAntaDigital for macOS..."

# Create build directory
mkdir -p build_macos
cd build_macos

# Configure with CMake
cmake .. \
    -DCMAKE_BUILD_TYPE=Release \
    -DBUILD_SHARED_LIBS=ON \
    -DBUILD_TESTS=ON \
    -DBUILD_EXAMPLES=ON \
    -DENABLE_QUANTUM_FEEDBACK=ON \
    -DCMAKE_OSX_DEPLOYMENT_TARGET=10.14

# Build
make -j$(sysctl -n hw.ncpu)

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

echo "macOS build completed!"
