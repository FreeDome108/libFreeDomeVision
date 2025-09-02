#!/bin/bash

set -e

echo "Building anAntaDigital for Android..."

# Check if ANDROID_NDK is set
if [ -z "$ANDROID_NDK" ]; then
    echo "ANDROID_NDK environment variable not set."
    echo "Please set it to your Android NDK path:"
    echo "export ANDROID_NDK=/path/to/android-ndk"
    exit 1
fi

# Android API level
ANDROID_API_LEVEL=21

# Architectures to build for
ARCHITECTURES=("arm64-v8a" "armeabi-v7a" "x86" "x86_64")

# Create build directory
mkdir -p build_android
cd build_android

for arch in "${ARCHITECTURES[@]}"; do
    echo "Building for architecture: $arch"
    
    # Create architecture-specific build directory
    mkdir -p build_$arch
    cd build_$arch
    
    # Configure for Android
    cmake ../.. \
        -DCMAKE_BUILD_TYPE=Release \
        -DBUILD_SHARED_LIBS=ON \
        -DBUILD_TESTS=OFF \
        -DBUILD_EXAMPLES=OFF \
        -DENABLE_QUANTUM_FEEDBACK=ON \
        -DCMAKE_SYSTEM_NAME=Android \
        -DCMAKE_SYSTEM_VERSION=${ANDROID_API_LEVEL} \
        -DCMAKE_ANDROID_ARCH_ABI=$arch \
        -DCMAKE_ANDROID_NDK=${ANDROID_NDK} \
        -DCMAKE_ANDROID_NDK_TOOLCHAIN_VERSION=clang \
        -DCMAKE_ANDROID_STL_TYPE=c++_shared \
        -DCMAKE_INSTALL_PREFIX=${PWD}/../install/$arch
    
    # Build
    make -j$(nproc)
    
    # Install
    make install
    
    cd ..
done

echo "Android build completed successfully!"
echo "Libraries installed to build_android/install/"
echo "Headers installed to build_android/install/*/include/anantadigital"

# Show library information
for arch in "${ARCHITECTURES[@]}"; do
    echo "Library for $arch:"
    ls -la install/$arch/lib/
done
