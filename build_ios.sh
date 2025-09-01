#!/bin/bash

echo "Building anAntaDigital for iOS..."

# iOS deployment target
IOS_DEPLOYMENT_TARGET="11.0"

# Create build directory
mkdir -p build_ios
cd build_ios

# Configure for iOS
cmake .. \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_SYSTEM_NAME=iOS \
    -DCMAKE_OSX_DEPLOYMENT_TARGET=${IOS_DEPLOYMENT_TARGET} \
    -DCMAKE_OSX_ARCHITECTURES="arm64;x86_64" \
    -DCMAKE_XCODE_ATTRIBUTE_ONLY_ACTIVE_ARCH=NO \
    -DCMAKE_XCODE_ATTRIBUTE_ENABLE_BITCODE=NO \
    -DCMAKE_XCODE_ATTRIBUTE_VALIDATE_PRODUCT=YES \
    -DBUILD_SHARED_LIBS=OFF \
    -DBUILD_TESTS=OFF \
    -DBUILD_EXAMPLES=OFF \
    -DENABLE_QUANTUM_FEEDBACK=ON

# Build
make -j$(sysctl -n hw.ncpu)

if [ $? -eq 0 ]; then
    echo "iOS build successful!"
else
    echo "iOS build failed!"
    exit 1
fi

echo "iOS build completed!"
