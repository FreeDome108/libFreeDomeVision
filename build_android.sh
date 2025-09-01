#!/bin/bash

echo "Building anAntaDigital for Android..."

# Android NDK path (update this to your NDK path)
ANDROID_NDK="${ANDROID_NDK_HOME:-$HOME/Android/Sdk/ndk/25.2.9519653}"

if [ ! -d "$ANDROID_NDK" ]; then
    echo "Android NDK not found at $ANDROID_NDK"
    echo "Please set ANDROID_NDK_HOME environment variable or update the path in this script"
    exit 1
fi

# Android API level
ANDROID_API_LEVEL=21

# Create build directory
mkdir -p build_android
cd build_android

# Configure for Android
cmake .. \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_SYSTEM_NAME=Android \
    -DCMAKE_SYSTEM_VERSION=${ANDROID_API_LEVEL} \
    -DCMAKE_ANDROID_ARCH_ABI=arm64-v8a \
    -DCMAKE_ANDROID_NDK=${ANDROID_NDK} \
    -DCMAKE_ANDROID_NDK_TOOLCHAIN_VERSION=clang \
    -DCMAKE_ANDROID_STL_TYPE=c++_shared \
    -DBUILD_SHARED_LIBS=ON \
    -DBUILD_TESTS=OFF \
    -DBUILD_EXAMPLES=OFF \
    -DENABLE_QUANTUM_FEEDBACK=ON

# Build
make -j$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)

if [ $? -eq 0 ]; then
    echo "Android build successful!"
else
    echo "Android build failed!"
    exit 1
fi

echo "Android build completed!"
