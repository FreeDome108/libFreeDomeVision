#!/bin/bash

# iOS Build Script for anAntaDigital

set -e

# Colors for output
GREEN='\033[0;32m'
RED='\033[0;31m'
BLUE='\033[0;34m'
YELLOW='\033[1;33m'
NC='\033[0m'

echo -e "${BLUE}=== Building anAntaDigital for iOS ===${NC}"

# Check environment
check_environment() {
    echo "Checking iOS build environment..."
    
    if ! command -v xcodebuild >/dev/null 2>&1; then
        echo -e "${RED}Xcode not found. Please install Xcode first.${NC}"
        exit 1
    fi
    
    if ! command -v cmake >/dev/null 2>&1; then
        echo -e "${RED}CMake not found. Installing...${NC}"
        if command -v brew >/dev/null 2>&1; then
            brew install cmake
        else
            echo -e "${RED}Homebrew not found. Please install CMake manually.${NC}"
            exit 1
        fi
    fi
    
    if ! command -v make >/dev/null 2>&1; then
        echo -e "${RED}Make not found. Installing...${NC}"
        if command -v brew >/dev/null 2>&1; then
            brew install make
        fi
    fi
    
    echo -e "${GREEN}iOS build environment ready!${NC}"
}

# Build for iOS device
build_ios_device() {
    echo -e "${BLUE}Building for iOS device...${NC}"
    
    mkdir -p "build/ios/device"
    cd "build/ios/device"
    
    cmake ../../.. \
        -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_TOOLCHAIN_FILE="../../../cmake/toolchains/ios.toolchain.cmake" \
        -DIOS_PLATFORM=iphoneos \
        -DIOS_ARCHITECTURES="arm64" \
        -DIOS_DEPLOYMENT_TARGET=12.0 \
        -DBUILD_SHARED_LIBS=OFF \
        -DBUILD_TESTS=OFF \
        -DBUILD_EXAMPLES=OFF \
        -DENABLE_QUANTUM_FEEDBACK=ON
    
    make -j$(sysctl -n hw.ncpu)
    
    if [ $? -eq 0 ]; then
        echo -e "${GREEN}iOS device build completed successfully!${NC}"
    else
        echo -e "${RED}iOS device build failed!${NC}"
        return 1
    fi
    
    cd ../../..
}

# Build for iOS simulator
build_ios_simulator() {
    echo -e "${BLUE}Building for iOS simulator...${NC}"
    
    mkdir -p "build/ios/simulator"
    cd "build/ios/simulator"
    
    cmake ../../.. \
        -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_TOOLCHAIN_FILE="../../../cmake/toolchains/ios.toolchain.cmake" \
        -DIOS_PLATFORM=iphonesimulator \
        -DIOS_ARCHITECTURES="arm64;x86_64" \
        -DIOS_DEPLOYMENT_TARGET=12.0 \
        -DBUILD_SHARED_LIBS=OFF \
        -DBUILD_TESTS=OFF \
        -DBUILD_EXAMPLES=OFF \
        -DENABLE_QUANTUM_FEEDBACK=ON
    
    make -j$(sysctl -n hw.ncpu)
    
    if [ $? -eq 0 ]; then
        echo -e "${GREEN}iOS simulator build completed successfully!${NC}"
    else
        echo -e "${RED}iOS simulator build failed!${NC}"
        return 1
    fi
    
    cd ../../..
}

# Create universal library
create_universal_lib() {
    echo "Creating universal library..."
    
    mkdir -p "build/ios/universal"
    cd "build/ios/universal"
    
    # Create universal library directory
    mkdir -p "lib"
    
    # Create universal library using lipo
    if [ -f "../../device/libanantadigital_core.a" ] && [ -f "../../simulator/libanantadigital_core.a" ]; then
        lipo -create \
            "../../device/libanantadigital_core.a" \
            "../../simulator/libanantadigital_core.a" \
            -output "lib/libanantadigital_core.a"
        
        echo -e "${GREEN}Universal library created successfully!${NC}"
    else
        echo -e "${YELLOW}Warning: Could not create universal library - missing device or simulator libraries${NC}"
    fi
    
    # Copy headers
    mkdir -p "include"
    cp -r "../../../src/*.hpp" "include/" 2>/dev/null || true
    
    cd ../../..
}

# Create iOS framework
create_framework() {
    echo "Creating iOS framework..."
    
    mkdir -p "build/ios/framework"
    cd "build/ios/framework"
    
    # Create framework structure
    mkdir -p "anAntaDigital.framework"
    mkdir -p "anAntaDigital.framework/Headers"
    mkdir -p "anAntaDigital.framework/Modules"
    
    # Copy universal library
    if [ -f "../universal/lib/libanantadigital_core.a" ]; then
        cp "../universal/lib/libanantadigital_core.a" "anAntaDigital.framework/anAntaDigital"
    fi
    
    # Copy headers
    cp -r "../universal/include/*.hpp" "anAntaDigital.framework/Headers/" 2>/dev/null || true
    
    # Create Info.plist
    cat > "anAntaDigital.framework/Info.plist" << 'EOF'
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
<plist version="1.0">
<dict>
    <key>CFBundleDevelopmentRegion</key>
    <string>en</string>
    <key>CFBundleExecutable</key>
    <string>anAntaDigital</string>
    <key>CFBundleIdentifier</key>
    <string>com.anantadigital.anAntaDigital</string>
    <key>CFBundleInfoDictionaryVersion</key>
    <string>6.0</string>
    <key>CFBundleName</key>
    <string>anAntaDigital</string>
    <key>CFBundlePackageType</key>
    <string>FMWK</string>
    <key>CFBundleShortVersionString</key>
    <string>2.1.0</string>
    <key>CFBundleVersion</key>
    <string>2.1.0</string>
    <key>MinimumOSVersion</key>
    <string>12.0</string>
</dict>
</plist>
EOF

    # Create module.modulemap
    cat > "anAntaDigital.framework/Modules/module.modulemap" << 'EOF'
framework module anAntaDigital {
  umbrella header "anantadigital_core.hpp"
  
  export *
  module * { export * }
}
EOF

    echo -e "${GREEN}iOS framework created successfully!${NC}"
    cd ../../..
}

# Main execution
main() {
    check_environment
    build_ios_device
    build_ios_simulator
    create_universal_lib
    create_framework
}

main "$@"
