#!/bin/bash

set -e

echo "Building anAntaDigital for iOS..."

# Check if Xcode is installed
if ! command -v xcodebuild &> /dev/null; then
    echo "Xcode not found. Please install Xcode first."
    exit 1
fi

# iOS deployment target
IOS_DEPLOYMENT_TARGET="11.0"

# Create build directory
mkdir -p build_ios
cd build_ios

# Configure for iOS simulator (arm64 + x86_64)
cmake .. \
    -DCMAKE_BUILD_TYPE=Release \
    -DBUILD_SHARED_LIBS=OFF \
    -DBUILD_TESTS=OFF \
    -DBUILD_EXAMPLES=OFF \
    -DENABLE_QUANTUM_FEEDBACK=ON \
    -DCMAKE_SYSTEM_NAME=iOS \
    -DCMAKE_OSX_DEPLOYMENT_TARGET=${IOS_DEPLOYMENT_TARGET} \
    -DCMAKE_OSX_ARCHITECTURES="arm64;x86_64" \
    -DCMAKE_XCODE_ATTRIBUTE_ONLY_ACTIVE_ARCH=NO \
    -DCMAKE_XCODE_ATTRIBUTE_ENABLE_BITCODE=NO \
    -DCMAKE_XCODE_ATTRIBUTE_VALIDATE_PRODUCT=YES \
    -DCMAKE_INSTALL_PREFIX=${PWD}/install

# Build
make -j$(sysctl -n hw.ncpu)

# Install
make install

echo "iOS build completed successfully!"
echo "Library installed to ${PWD}/install"
echo "Headers installed to ${PWD}/install/include/anantadigital"

# Create universal binary info
echo "Creating universal binary for iOS..."
lipo -info install/lib/libanantadigital_core.a
