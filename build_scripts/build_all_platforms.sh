#!/bin/bash

# FreeDome Vision Multi-Platform Build Script
# Supports: Linux, macOS, iOS, Android, Avrora, Windows

set -e

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Build directory
BUILD_DIR="build"
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_DIR="$(dirname "$SCRIPT_DIR")"

echo -e "${BLUE}=== FreeDome Vision Multi-Platform Build Script ===${NC}"
echo -e "${BLUE}Project Directory: ${PROJECT_DIR}${NC}"

# Function to print colored output
print_status() {
    echo -e "${GREEN}[INFO]${NC} $1"
}

print_warning() {
    echo -e "${YELLOW}[WARNING]${NC} $1"
}

print_error() {
    echo -e "${RED}[ERROR]${NC} $1"
}

# Function to check if command exists
command_exists() {
    command -v "$1" >/dev/null 2>&1
}

# Function to detect OS
detect_os() {
    case "$(uname -s)" in
        Linux*)     echo "linux";;
        Darwin*)    echo "macos";;
        CYGWIN*|MINGW*|MSYS*) echo "windows";;
        *)          echo "unknown";;
    esac
}

# Function to build for Linux
build_linux() {
    print_status "Building for Linux..."
    
    if ! command_exists cmake; then
        print_error "CMake not found. Please install CMake first."
        return 1
    fi
    
    mkdir -p "${BUILD_DIR}/linux"
    cd "${BUILD_DIR}/linux"
    
    cmake "${PROJECT_DIR}" \
        -DCMAKE_BUILD_TYPE=Release \
        -DBUILD_SHARED_LIBS=ON \
        -DBUILD_TESTS=ON \
        -DBUILD_EXAMPLES=ON \
        -DENABLE_QUANTUM_FEEDBACK=ON
    
    make -j$(nproc)
    
    if [ $? -eq 0 ]; then
        print_status "Linux build completed successfully!"
    else
        print_error "Linux build failed!"
        return 1
    fi
    
    cd "${PROJECT_DIR}"
}

# Function to build for macOS
build_macos() {
    print_status "Building for macOS..."
    
    if ! command_exists cmake; then
        print_error "CMake not found. Please install CMake first."
        return 1
    fi
    
    mkdir -p "${BUILD_DIR}/macos"
    cd "${BUILD_DIR}/macos"
    
    cmake "${PROJECT_DIR}" \
        -DCMAKE_BUILD_TYPE=Release \
        -DBUILD_SHARED_LIBS=ON \
        -DBUILD_TESTS=ON \
        -DBUILD_EXAMPLES=ON \
        -DENABLE_QUANTUM_FEEDBACK=ON \
        -DCMAKE_OSX_ARCHITECTURES="x86_64;arm64"
    
    make -j$(sysctl -n hw.ncpu)
    
    if [ $? -eq 0 ]; then
        print_status "macOS build completed successfully!"
    else
        print_error "macOS build failed!"
        return 1
    fi
    
    cd "${PROJECT_DIR}"
}

# Function to build for iOS
build_ios() {
    print_status "Building for iOS..."
    
    if ! command_exists xcodebuild; then
        print_error "Xcode not found. Please install Xcode first."
        return 1
    fi
    
    mkdir -p "${BUILD_DIR}/ios"
    cd "${BUILD_DIR}/ios"
    
    # iOS Simulator
    cmake "${PROJECT_DIR}" \
        -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_SYSTEM_NAME=iOS \
        -DCMAKE_OSX_DEPLOYMENT_TARGET=12.0 \
        -DCMAKE_OSX_ARCHITECTURES="arm64;x86_64" \
        -DCMAKE_OSX_SYSROOT=iphonesimulator \
        -DBUILD_SHARED_LIBS=OFF \
        -DBUILD_TESTS=OFF \
        -DBUILD_EXAMPLES=OFF \
        -DENABLE_QUANTUM_FEEDBACK=ON
    
    make -j$(sysctl -n hw.ncpu)
    
    if [ $? -eq 0 ]; then
        print_status "iOS Simulator build completed successfully!"
    else
        print_error "iOS Simulator build failed!"
        return 1
    fi
    
    cd "${PROJECT_DIR}"
}

# Function to build for Android
build_android() {
    print_status "Building for Android..."
    
    if [ -z "$ANDROID_NDK" ]; then
        print_error "ANDROID_NDK environment variable not set. Please set it to your Android NDK path."
        return 1
    fi
    
    if ! command_exists cmake; then
        print_error "CMake not found. Please install CMake first."
        return 1
    fi
    
    # Android architectures
    ANDROID_ARCHS=("arm64-v8a" "armeabi-v7a" "x86" "x86_64")
    
    for arch in "${ANDROID_ARCHS[@]}"; do
        print_status "Building for Android $arch..."
        
        mkdir -p "${BUILD_DIR}/android/${arch}"
        cd "${BUILD_DIR}/android/${arch}"
        
        cmake "${PROJECT_DIR}" \
            -DCMAKE_BUILD_TYPE=Release \
            -DCMAKE_SYSTEM_NAME=Android \
            -DCMAKE_SYSTEM_VERSION=21 \
            -DCMAKE_ANDROID_ARCH_ABI="$arch" \
            -DCMAKE_ANDROID_NDK="$ANDROID_NDK" \
            -DCMAKE_ANDROID_STL=c++_shared \
            -DBUILD_SHARED_LIBS=ON \
            -DBUILD_TESTS=OFF \
            -DBUILD_EXAMPLES=OFF \
            -DENABLE_QUANTUM_FEEDBACK=ON
        
        make -j$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)
        
        if [ $? -eq 0 ]; then
            print_status "Android $arch build completed successfully!"
        else
            print_error "Android $arch build failed!"
            return 1
        fi
        
        cd "${PROJECT_DIR}"
    done
}

# Function to build for Avrora
build_avrora() {
    print_status "Building for Avrora..."
    
    if ! command_exists avr-gcc; then
        print_warning "AVR-GCC not found. Skipping Avrora build."
        return 0
    fi
    
    mkdir -p "${BUILD_DIR}/avrora"
    cd "${BUILD_DIR}/avrora"
    
    # Avrora-specific flags
    cmake "${PROJECT_DIR}" \
        -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_SYSTEM_NAME=Generic \
        -DCMAKE_SYSTEM_PROCESSOR=avr \
        -DCMAKE_C_COMPILER=avr-gcc \
        -DCMAKE_CXX_COMPILER=avr-g++ \
        -DCMAKE_C_FLAGS="-mmcu=atmega328p -Os" \
        -DCMAKE_CXX_FLAGS="-mmcu=atmega328p -Os" \
        -DBUILD_SHARED_LIBS=OFF \
        -DBUILD_TESTS=OFF \
        -DBUILD_EXAMPLES=OFF \
        -DENABLE_QUANTUM_FEEDBACK=OFF
    
    make -j$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)
    
    if [ $? -eq 0 ]; then
        print_status "Avrora build completed successfully!"
    else
        print_error "Avrora build failed!"
        return 1
    fi
    
    cd "${PROJECT_DIR}"
}

# Function to build for Windows (cross-compilation)
build_windows() {
    print_status "Building for Windows (cross-compilation)..."
    
    if ! command_exists x86_64-w64-mingw32-gcc; then
        print_warning "MinGW-w64 cross-compiler not found. Skipping Windows build."
        return 0
    fi
    
    mkdir -p "${BUILD_DIR}/windows"
    cd "${BUILD_DIR}/windows"
    
    cmake "${PROJECT_DIR}" \
        -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_SYSTEM_NAME=Windows \
        -DCMAKE_C_COMPILER=x86_64-w64-mingw32-gcc \
        -DCMAKE_CXX_COMPILER=x86_64-w64-mingw32-g++ \
        -DCMAKE_RC_COMPILER=x86_64-w64-mingw32-windres \
        -DBUILD_SHARED_LIBS=ON \
        -DBUILD_TESTS=OFF \
        -DBUILD_EXAMPLES=OFF \
        -DENABLE_QUANTUM_FEEDBACK=ON
    
    make -j$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)
    
    if [ $? -eq 0 ]; then
        print_status "Windows build completed successfully!"
    else
        print_error "Windows build failed!"
        return 1
    fi
    
    cd "${PROJECT_DIR}"
}

# Main build function
main() {
    local current_os=$(detect_os)
    
    print_status "Detected OS: $current_os"
    
    # Create build directory
    mkdir -p "${BUILD_DIR}"
    
    # Build for current platform
    case "$current_os" in
        "linux")
            build_linux
            ;;
        "macos")
            build_macos
            build_ios
            ;;
        "windows")
            build_windows
            ;;
        *)
            print_error "Unsupported OS: $current_os"
            exit 1
            ;;
    esac
    
    # Cross-compilation builds
    if [ "$current_os" = "linux" ] || [ "$current_os" = "macos" ]; then
        build_android
        build_avrora
        build_windows
    fi
    
    print_status "All platform builds completed!"
}

# Run main function
main "$@"
