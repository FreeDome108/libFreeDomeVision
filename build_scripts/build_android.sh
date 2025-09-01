#!/bin/bash

# Android Build Script for anAntaDigital

set -e

# Colors for output
GREEN='\033[0;32m'
RED='\033[0;31m'
BLUE='\033[0;34m'
YELLOW='\033[1;33m'
NC='\033[0m'

echo -e "${BLUE}=== Building anAntaDigital for Android ===${NC}"

# Check environment
check_environment() {
    echo "Checking Android build environment..."
    
    if [ -z "$ANDROID_NDK" ]; then
        echo -e "${RED}ANDROID_NDK environment variable not set.${NC}"
        echo "Please set ANDROID_NDK to your Android NDK path:"
        echo "export ANDROID_NDK=/path/to/android-ndk"
        exit 1
    fi
    
    if [ ! -d "$ANDROID_NDK" ]; then
        echo -e "${RED}Android NDK directory not found: $ANDROID_NDK${NC}"
        exit 1
    fi
    
    echo -e "${GREEN}Android NDK found: $ANDROID_NDK${NC}"
    
    if ! command -v cmake >/dev/null 2>&1; then
        echo -e "${RED}CMake not found. Please install CMake first.${NC}"
        exit 1
    fi
    
    if ! command -v make >/dev/null 2>&1; then
        echo -e "${RED}Make not found. Please install Make first.${NC}"
        exit 1
    fi
}

# Build for specific architecture
build_arch() {
    local arch=$1
    local api_level=${2:-21}
    
    echo -e "${BLUE}Building for Android $arch (API $api_level)...${NC}"
    
    mkdir -p "build/android/${arch}"
    cd "build/android/${arch}"
    
    cmake ../../.. \
        -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_TOOLCHAIN_FILE="../../../cmake/toolchains/android.toolchain.cmake" \
        -DANDROID_ABI="$arch" \
        -DANDROID_API_LEVEL="$api_level" \
        -DANDROID_STL=c++_shared \
        -DBUILD_SHARED_LIBS=ON \
        -DBUILD_TESTS=OFF \
        -DBUILD_EXAMPLES=OFF \
        -DENABLE_QUANTUM_FEEDBACK=ON
    
    make -j$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)
    
    if [ $? -eq 0 ]; then
        echo -e "${GREEN}Android $arch build completed successfully!${NC}"
    else
        echo -e "${RED}Android $arch build failed!${NC}"
        return 1
    fi
    
    cd ../../..
}

# Build all architectures
build_all() {
    echo "Building for all Android architectures..."
    
    # Android architectures with their minimum API levels
    local archs=(
        "arm64-v8a:21"
        "armeabi-v7a:16"
        "x86:16"
        "x86_64:21"
    )
    
    for arch_info in "${archs[@]}"; do
        IFS=':' read -r arch api_level <<< "$arch_info"
        build_arch "$arch" "$api_level"
    done
    
    echo -e "${GREEN}All Android architectures built successfully!${NC}"
}

# Create Android library package
create_package() {
    echo "Creating Android library package..."
    
    mkdir -p "build/android/package"
    cd "build/android/package"
    
    # Create directory structure
    mkdir -p "libs"
    mkdir -p "include"
    
    # Copy libraries
    for arch in arm64-v8a armeabi-v7a x86 x86_64; do
        if [ -d "../${arch}" ]; then
            mkdir -p "libs/${arch}"
            cp "../${arch}/libanantadigital_core.so" "libs/${arch}/" 2>/dev/null || true
        fi
    done
    
    # Copy headers
    cp -r "../../../src/*.hpp" "include/" 2>/dev/null || true
    
    # Create Android.mk
    cat > "Android.mk" << 'EOF'
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := anantadigital_core
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libanantadigital_core.so
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/include
include $(PREBUILT_SHARED_LIBRARY)
EOF

    # Create Application.mk
    cat > "Application.mk" << 'EOF'
APP_ABI := arm64-v8a armeabi-v7a x86 x86_64
APP_PLATFORM := android-21
APP_STL := c++_shared
APP_CPPFLAGS += -std=c++17
EOF

    echo -e "${GREEN}Android package created in build/android/package/${NC}"
    cd ../../..
}

# Main execution
main() {
    check_environment
    build_all
    create_package
}

main "$@"
