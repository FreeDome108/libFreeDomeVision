#!/bin/bash

set -e

echo "Building anAntaDigital for macOS..."

# Check if Homebrew is installed
if ! command -v brew &> /dev/null; then
    echo "Homebrew not found. Installing dependencies manually..."
    # Install dependencies manually if needed
else
    echo "Installing dependencies via Homebrew..."
    brew install portaudio libsndfile cmake
fi

# Create build directory
mkdir -p build_macos
cd build_macos

# Configure with CMake for macOS
cmake .. \
    -DCMAKE_BUILD_TYPE=Release \
    -DBUILD_SHARED_LIBS=ON \
    -DBUILD_TESTS=ON \
    -DBUILD_EXAMPLES=ON \
    -DENABLE_QUANTUM_FEEDBACK=ON \
    -DCMAKE_OSX_DEPLOYMENT_TARGET=10.14 \
    -DCMAKE_INSTALL_PREFIX=/usr/local

# Build
make -j$(sysctl -n hw.ncpu)

# Run tests
make test

# Install
sudo make install

echo "macOS build completed successfully!"
echo "Library installed to /usr/local/lib"
echo "Headers installed to /usr/local/include/anantadigital"
