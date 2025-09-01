#!/bin/bash

# Build script for anAntaDigital on all supported platforms
# Usage: ./build_all_platforms.sh [platform]

set -e

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Function to print colored output
print_status() {
    echo -e "${BLUE}[INFO]${NC} $1"
}

print_success() {
    echo -e "${GREEN}[SUCCESS]${NC} $1"
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

# Function to build for Linux
build_linux() {
    print_status "Building for Linux..."
    
    mkdir -p build_linux
    cd build_linux
    
    cmake .. \
        -DCMAKE_BUILD_TYPE=Release \
        -DBUILD_SHARED_LIBS=ON \
        -DBUILD_TESTS=ON \
        -DBUILD_EXAMPLES=ON \
        -DENABLE_QUANTUM_FEEDBACK=ON
    
    make -j$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)
    
    if [ $? -eq 0 ]; then
        print_success "Linux build completed successfully!"
        if [ "$RUN_TESTS" = "true" ]; then
            print_status "Running Linux tests..."
            make test
        fi
    else
        print_error "Linux build failed!"
        return 1
    fi
    
    cd ..
}

# Function to build for macOS
build_macos() {
    print_status "Building for macOS..."
    
    mkdir -p build_macos
    cd build_macos
    
    cmake .. \
        -DCMAKE_BUILD_TYPE=Release \
        -DBUILD_SHARED_LIBS=ON \
        -DBUILD_TESTS=ON \
        -DBUILD_EXAMPLES=ON \
        -DENABLE_QUANTUM_FEEDBACK=ON \
        -DCMAKE_OSX_DEPLOYMENT_TARGET=10.14
    
    make -j$(sysctl -n hw.ncpu 2>/dev/null || echo 4)
    
    if [ $? -eq 0 ]; then
        print_success "macOS build completed successfully!"
        if [ "$RUN_TESTS" = "true" ]; then
            print_status "Running macOS tests..."
            make test
        fi
    else
        print_error "macOS build failed!"
        return 1
    fi
    
    cd ..
}

# Function to build for iOS
build_ios() {
    print_status "Building for iOS..."
    
    mkdir -p build_ios
    cd build_ios
    
    cmake .. \
        -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_SYSTEM_NAME=iOS \
        -DCMAKE_OSX_DEPLOYMENT_TARGET=11.0 \
        -DCMAKE_OSX_ARCHITECTURES="arm64;x86_64" \
        -DCMAKE_XCODE_ATTRIBUTE_ONLY_ACTIVE_ARCH=NO \
        -DCMAKE_XCODE_ATTRIBUTE_ENABLE_BITCODE=NO \
        -DCMAKE_XCODE_ATTRIBUTE_VALIDATE_PRODUCT=YES \
        -DBUILD_SHARED_LIBS=OFF \
        -DBUILD_TESTS=OFF \
        -DBUILD_EXAMPLES=OFF \
        -DENABLE_QUANTUM_FEEDBACK=ON
    
    make -j$(sysctl -n hw.ncpu 2>/dev/null || echo 4)
    
    if [ $? -eq 0 ]; then
        print_success "iOS build completed successfully!"
    else
        print_error "iOS build failed!"
        return 1
    fi
    
    cd ..
}

# Function to build for Android
build_android() {
    print_status "Building for Android..."
    
    # Check for Android NDK
    ANDROID_NDK="${ANDROID_NDK_HOME:-$HOME/Android/Sdk/ndk/25.2.9519653}"
    
    if [ ! -d "$ANDROID_NDK" ]; then
        print_warning "Android NDK not found at $ANDROID_NDK"
        print_warning "Skipping Android build. Set ANDROID_NDK_HOME environment variable."
        return 0
    fi
    
    mkdir -p build_android
    cd build_android
    
    cmake .. \
        -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_SYSTEM_NAME=Android \
        -DCMAKE_SYSTEM_VERSION=21 \
        -DCMAKE_ANDROID_ARCH_ABI=arm64-v8a \
        -DCMAKE_ANDROID_NDK=${ANDROID_NDK} \
        -DCMAKE_ANDROID_NDK_TOOLCHAIN_VERSION=clang \
        -DCMAKE_ANDROID_STL_TYPE=c++_shared \
        -DBUILD_SHARED_LIBS=ON \
        -DBUILD_TESTS=OFF \
        -DBUILD_EXAMPLES=OFF \
        -DENABLE_QUANTUM_FEEDBACK=ON
    
    make -j$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)
    
    if [ $? -eq 0 ]; then
        print_success "Android build completed successfully!"
    else
        print_error "Android build failed!"
        return 1
    fi
    
    cd ..
}

# Function to build for Avrora
build_avrora() {
    print_status "Building for Avrora..."
    
    # Check for AVR tools
    if ! command_exists avr-gcc || ! command_exists avr-g++; then
        print_warning "AVR tools not found. Skipping Avrora build."
        print_warning "Install avr-gcc and avr-g++ to build for Avrora."
        return 0
    fi
    
    mkdir -p build_avrora
    cd build_avrora
    
    cmake .. \
        -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_SYSTEM_NAME=Avrora \
        -DCMAKE_CXX_COMPILER=avr-g++ \
        -DCMAKE_C_COMPILER=avr-gcc \
        -DCMAKE_CXX_FLAGS="-mmcu=atmega328p -Os -Wall -Wextra" \
        -DCMAKE_C_FLAGS="-mmcu=atmega328p -Os -Wall -Wextra" \
        -DBUILD_SHARED_LIBS=OFF \
        -DBUILD_TESTS=OFF \
        -DBUILD_EXAMPLES=OFF \
        -DENABLE_QUANTUM_FEEDBACK=ON
    
    make -j$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)
    
    if [ $? -eq 0 ]; then
        print_success "Avrora build completed successfully!"
    else
        print_error "Avrora build failed!"
        return 1
    fi
    
    cd ..
}

# Function to build for Windows (using cross-compilation if possible)
build_windows() {
    print_status "Building for Windows..."
    
    # Check if we're on Windows
    if [[ "$OSTYPE" == "msys" || "$OSTYPE" == "cygwin" ]]; then
        print_status "Building natively on Windows..."
        
        mkdir -p build_windows
        cd build_windows
        
        cmake .. \
            -DCMAKE_BUILD_TYPE=Release \
            -DBUILD_SHARED_LIBS=ON \
            -DBUILD_TESTS=ON \
            -DBUILD_EXAMPLES=ON \
            -DENABLE_QUANTUM_FEEDBACK=ON
        
        cmake --build . --config Release --parallel
        
        if [ $? -eq 0 ]; then
            print_success "Windows build completed successfully!"
            if [ "$RUN_TESTS" = "true" ]; then
                print_status "Running Windows tests..."
                ctest --output-on-failure
            fi
        else
            print_error "Windows build failed!"
            return 1
        fi
        
        cd ..
    else
        print_warning "Cross-compilation to Windows not implemented yet."
        print_warning "Use build_windows.bat on a Windows machine."
        return 0
    fi
}

# Function to build for all platforms
build_all() {
    print_status "Building for all supported platforms..."
    
    local failed_builds=()
    
    # Build for each platform
    if build_linux; then
        print_success "Linux build successful"
    else
        failed_builds+=("Linux")
    fi
    
    if build_macos; then
        print_success "macOS build successful"
    else
        failed_builds+=("macOS")
    fi
    
    if build_ios; then
        print_success "iOS build successful"
    else
        failed_builds+=("iOS")
    fi
    
    if build_android; then
        print_success "Android build successful"
    else
        failed_builds+=("Android")
    fi
    
    if build_avrora; then
        print_success "Avrora build successful"
    else
        failed_builds+=("Avrora")
    fi
    
    if build_windows; then
        print_success "Windows build successful"
    else
        failed_builds+=("Windows")
    fi
    
    # Summary
    if [ ${#failed_builds[@]} -eq 0 ]; then
        print_success "All platform builds completed successfully!"
    else
        print_warning "Some builds failed: ${failed_builds[*]}"
        return 1
    fi
}

# Main script
main() {
    print_status "Starting anAntaDigital build process..."
    
    # Parse command line arguments
    RUN_TESTS="true"
    PLATFORM=""
    
    while [[ $# -gt 0 ]]; do
        case $1 in
            --no-tests)
                RUN_TESTS="false"
                shift
                ;;
            --platform)
                PLATFORM="$2"
                shift 2
                ;;
            -h|--help)
                echo "Usage: $0 [OPTIONS]"
                echo "Options:"
                echo "  --no-tests           Skip running tests after build"
                echo "  --platform PLATFORM  Build only for specific platform"
                echo "  -h, --help          Show this help message"
                echo ""
                echo "Supported platforms:"
                echo "  linux, macos, ios, android, avrora, windows, all"
                exit 0
                ;;
            *)
                PLATFORM="$1"
                shift
                ;;
        esac
    done
    
    # Check if we're in the right directory
    if [ ! -f "CMakeLists.txt" ]; then
        print_error "CMakeLists.txt not found. Please run this script from the anAntaDigital directory."
        exit 1
    fi
    
    # Build based on platform
    case "$PLATFORM" in
        "linux")
            build_linux
            ;;
        "macos")
            build_macos
            ;;
        "ios")
            build_ios
            ;;
        "android")
            build_android
            ;;
        "avrora")
            build_avrora
            ;;
        "windows")
            build_windows
            ;;
        "all"|"")
            build_all
            ;;
        *)
            print_error "Unknown platform: $PLATFORM"
            print_status "Supported platforms: linux, macos, ios, android, avrora, windows, all"
            exit 1
            ;;
    esac
    
    print_success "Build process completed!"
}

# Run main function
main "$@"
