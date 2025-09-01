#!/bin/bash

# Linux Build Script for anAntaDigital

set -e

# Colors for output
GREEN='\033[0;32m'
RED='\033[0;31m'
BLUE='\033[0;34m'
NC='\033[0m'

echo -e "${BLUE}=== Building anAntaDigital for Linux ===${NC}"

# Check dependencies
check_dependencies() {
    echo "Checking dependencies..."
    
    if ! command -v cmake >/dev/null 2>&1; then
        echo -e "${RED}CMake not found. Installing...${NC}"
        if command -v apt-get >/dev/null 2>&1; then
            sudo apt-get update && sudo apt-get install -y cmake build-essential
        elif command -v yum >/dev/null 2>&1; then
            sudo yum install -y cmake gcc-c++ make
        elif command -v dnf >/dev/null 2>&1; then
            sudo dnf install -y cmake gcc-c++ make
        elif command -v pacman >/dev/null 2>&1; then
            sudo pacman -S --noconfirm cmake base-devel
        else
            echo -e "${RED}Package manager not supported. Please install CMake manually.${NC}"
            exit 1
        fi
    fi
    
    if ! command -v make >/dev/null 2>&1; then
        echo -e "${RED}Make not found. Installing...${NC}"
        if command -v apt-get >/dev/null 2>&1; then
            sudo apt-get install -y build-essential
        elif command -v yum >/dev/null 2>&1; then
            sudo yum install -y make
        elif command -v dnf >/dev/null 2>&1; then
            sudo dnf install -y make
        elif command -v pacman >/dev/null 2>&1; then
            sudo pacman -S --noconfirm base-devel
        fi
    fi
}

# Build function
build() {
    echo "Creating build directory..."
    mkdir -p build/linux
    cd build/linux
    
    echo "Configuring with CMake..."
    cmake ../.. \
        -DCMAKE_BUILD_TYPE=Release \
        -DBUILD_SHARED_LIBS=ON \
        -DBUILD_TESTS=ON \
        -DBUILD_EXAMPLES=ON \
        -DENABLE_QUANTUM_FEEDBACK=ON \
        -DCMAKE_INSTALL_PREFIX=/usr/local
    
    echo "Building..."
    make -j$(nproc)
    
    echo "Running tests..."
    make test
    
    echo "Installing..."
    sudo make install
    
    echo -e "${GREEN}Linux build completed successfully!${NC}"
}

# Main execution
main() {
    check_dependencies
    build
}

main "$@"
