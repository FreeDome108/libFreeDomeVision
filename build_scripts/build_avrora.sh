#!/bin/bash

# Avrora/AVR Build Script for anAntaDigital

set -e

# Colors for output
GREEN='\033[0;32m'
RED='\033[0;31m'
BLUE='\033[0;34m'
YELLOW='\033[1;33m'
NC='\033[0m'

echo -e "${BLUE}=== Building anAntaDigital for Avrora/AVR ===${NC}"

# Check environment
check_environment() {
    echo "Checking Avrora/AVR build environment..."
    
    if ! command -v avr-gcc >/dev/null 2>&1; then
        echo -e "${RED}AVR-GCC not found. Installing...${NC}"
        if command -v apt-get >/dev/null 2>&1; then
            sudo apt-get update && sudo apt-get install -y gcc-avr avr-libc avrdude
        elif command -v yum >/dev/null 2>&1; then
            sudo yum install -y avr-gcc avr-libc avrdude
        elif command -v dnf >/dev/null 2>&1; then
            sudo dnf install -y avr-gcc avr-libc avrdude
        elif command -v pacman >/dev/null 2>&1; then
            sudo pacman -S --noconfirm avr-gcc avr-libc avrdude
        elif command -v brew >/dev/null 2>&1; then
            brew install avr-gcc avr-libc avrdude
        else
            echo -e "${RED}Package manager not supported. Please install AVR toolchain manually:${NC}"
            echo "1. Install AVR-GCC: https://www.nongnu.org/avr-libc/"
            echo "2. Install AVRDUDE: https://www.nongnu.org/avrdude/"
            exit 1
        fi
    fi
    
    if ! command -v cmake >/dev/null 2>&1; then
        echo -e "${RED}CMake not found. Installing...${NC}"
        if command -v apt-get >/dev/null 2>&1; then
            sudo apt-get install -y cmake
        elif command -v yum >/dev/null 2>&1; then
            sudo yum install -y cmake
        elif command -v dnf >/dev/null 2>&1; then
            sudo dnf install -y cmake
        elif command -v pacman >/dev/null 2>&1; then
            sudo pacman -S --noconfirm cmake
        elif command -v brew >/dev/null 2>&1; then
            brew install cmake
        fi
    fi
    
    if ! command -v make >/dev/null 2>&1; then
        echo -e "${RED}Make not found. Installing...${NC}"
        if command -v apt-get >/dev/null 2>&1; then
            sudo apt-get install -y make
        elif command -v yum >/dev/null 2>&1; then
            sudo yum install -y make
        elif command -v dnf >/dev/null 2>&1; then
            sudo dnf install -y make
        elif command -v pacman >/dev/null 2>&1; then
            sudo pacman -S --noconfirm make
        elif command -v brew >/dev/null 2>&1; then
            brew install make
        fi
    fi
    
    echo -e "${GREEN}Avrora/AVR build environment ready!${NC}"
}

# Build for specific AVR microcontroller
build_avr() {
    local mcu=$1
    local freq=${2:-16000000}
    local programmer=${3:-usbasp}
    
    echo -e "${BLUE}Building for AVR $mcu at ${freq}Hz...${NC}"
    
    mkdir -p "build/avrora/${mcu}"
    cd "build/avrora/${mcu}"
    
    cmake ../../.. \
        -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_TOOLCHAIN_FILE="../../../cmake/toolchains/avrora.toolchain.cmake" \
        -DAVR_MCU="$mcu" \
        -DAVR_FREQ="$freq" \
        -DAVR_PROGRAMMER="$programmer" \
        -DBUILD_SHARED_LIBS=OFF \
        -DBUILD_TESTS=OFF \
        -DBUILD_EXAMPLES=OFF \
        -DENABLE_QUANTUM_FEEDBACK=OFF
    
    make -j$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)
    
    if [ $? -eq 0 ]; then
        echo -e "${GREEN}AVR $mcu build completed successfully!${NC}"
        
        # Create hex file
        if [ -f "anantadigital_core" ]; then
            avr-objcopy -O ihex -R .eeprom anantadigital_core anantadigital_core.hex
            echo -e "${GREEN}Hex file created: anantadigital_core.hex${NC}"
        fi
        
        # Show size information
        if command -v avr-size >/dev/null 2>&1; then
            echo "Memory usage:"
            avr-size -C --mcu=${mcu} anantadigital_core
        fi
    else
        echo -e "${RED}AVR $mcu build failed!${NC}"
        return 1
    fi
    
    cd ../../..
}

# Build for all common AVR microcontrollers
build_all_avr() {
    echo "Building for all common AVR microcontrollers..."
    
    # Common AVR microcontrollers with their frequencies
    local avrs=(
        "atmega328p:16000000:usbasp"
        "atmega2560:16000000:usbasp"
        "atmega128:16000000:usbasp"
        "attiny85:8000000:usbasp"
        "attiny13:1200000:usbasp"
    )
    
    for avr_info in "${avrs[@]}"; do
        IFS=':' read -r mcu freq programmer <<< "$avr_info"
        build_avr "$mcu" "$freq" "$programmer"
    done
    
    echo -e "${GREEN}All AVR microcontrollers built successfully!${NC}"
}

# Create Avrora package
create_package() {
    echo "Creating Avrora package..."
    
    mkdir -p "build/avrora/package"
    cd "build/avrora/package"
    
    # Create directory structure
    mkdir -p "bin"
    mkdir -p "hex"
    mkdir -p "include"
    mkdir -p "docs"
    
    # Copy binaries and hex files
    for mcu_dir in ../*/; do
        if [ -d "$mcu_dir" ] && [ "$mcu_dir" != "../package/" ]; then
            mcu_name=$(basename "$mcu_dir")
            mkdir -p "bin/${mcu_name}"
            mkdir -p "hex/${mcu_name}"
            
            # Copy binary
            if [ -f "${mcu_dir}anantadigital_core" ]; then
                cp "${mcu_dir}anantadigital_core" "bin/${mcu_name}/"
            fi
            
            # Copy hex file
            if [ -f "${mcu_dir}anantadigital_core.hex" ]; then
                cp "${mcu_dir}anantadigital_core.hex" "hex/${mcu_name}/"
            fi
        fi
    done
    
    # Copy headers
    cp -r "../../../src/*.hpp" "include/" 2>/dev/null || true
    
    # Copy documentation
    cp -r "../../../docs/*" "docs/" 2>/dev/null || true
    
    # Create README
    cat > "README.md" << 'EOF'
# anAntaDigital for Avrora/AVR

This package contains pre-built binaries and hex files for various AVR microcontrollers.

## Supported Microcontrollers

- ATmega328P (Arduino Uno)
- ATmega2560 (Arduino Mega)
- ATmega128
- ATtiny85
- ATtiny13

## Usage

### Binary Files
Binary files are located in the `bin/` directory, organized by microcontroller.

### Hex Files
Hex files are located in the `hex/` directory and can be uploaded using AVRDUDE:

```bash
avrdude -c [programmer] -p [mcu] -U flash:w:[hexfile]:i
```

### Headers
Include files are located in the `include/` directory.

## Building from Source

To build for a specific microcontroller:

```bash
cmake -DCMAKE_TOOLCHAIN_FILE=cmake/toolchains/avrora.toolchain.cmake \
      -DAVR_MCU=[mcu] -DAVR_FREQ=[frequency] ..
make
```

## Requirements

- AVR-GCC toolchain
- CMake 3.16+
- Make
EOF

    echo -e "${GREEN}Avrora package created in build/avrora/package/${NC}"
    cd ../../..
}

# Main execution
main() {
    check_environment
    build_all_avr
    create_package
}

main "$@"
