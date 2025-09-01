#!/bin/bash

# macOS Build Script for anAntaDigital

set -e

# Colors for output
GREEN='\033[0;32m'
RED='\033[0;31m'
BLUE='\033[0;34m'
NC='\033[0m'

echo -e "${BLUE}=== Building anAntaDigital for macOS ===${NC}"

# Check dependencies
check_dependencies() {
    echo "Checking dependencies..."
    
    if ! command -v cmake >/dev/null 2>&1; then
        echo -e "${RED}CMake not found. Installing...${NC}"
        if command -v brew >/dev/null 2>&1; then
            brew install cmake
        else
            echo -e "${RED}Homebrew not found. Please install Homebrew first:${NC}"
            echo "/bin/bash -c \"\$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)\""
            echo "Then run: brew install cmake"
            exit 1
        fi
    fi
    
    if ! command -v make >/dev/null 2>&1; then
        echo -e "${RED}Make not found. Installing...${NC}"
        if command -v brew >/dev/null 2>&1; then
            brew install make
        fi
    fi
    
    # Check Xcode command line tools
    if ! command -v xcodebuild >/dev/null 2>&1; then
        echo -e "${RED}Xcode command line tools not found. Installing...${NC}"
        xcode-select --install
        echo "Please complete the Xcode installation and run this script again."
        exit 1
    fi
}

# Build function
build() {
    echo "Creating build directory..."
    mkdir -p build/macos
    cd build/macos
    
    echo "Configuring with CMake..."
    cmake ../.. \
        -DCMAKE_BUILD_TYPE=Release \
        -DBUILD_SHARED_LIBS=ON \
        -DBUILD_TESTS=ON \
        -DBUILD_EXAMPLES=ON \
        -DENABLE_QUANTUM_FEEDBACK=ON \
        -DCMAKE_OSX_ARCHITECTURES="x86_64;arm64" \
        -DCMAKE_INSTALL_PREFIX=/usr/local
    
    echo "Building..."
    make -j$(sysctl -n hw.ncpu)
    
    echo "Running tests..."
    make test
    
    echo "Installing..."
    sudo make install
    
    echo -e "${GREEN}macOS build completed successfully!${NC}"
}

# Main execution
main() {
    check_dependencies
    build
}

main "$@"
