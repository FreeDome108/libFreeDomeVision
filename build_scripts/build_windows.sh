#!/bin/bash

# Windows Cross-Compilation Build Script for anAntaDigital

set -e

# Colors for output
GREEN='\033[0;32m'
RED='\033[0;31m'
BLUE='\033[0;34m'
YELLOW='\033[1;33m'
NC='\033[0m'

echo -e "${BLUE}=== Building anAntaDigital for Windows (Cross-Compilation) ===${NC}"

# Check environment
check_environment() {
    echo "Checking Windows cross-compilation environment..."
    
    if ! command -v x86_64-w64-mingw32-gcc >/dev/null 2>&1; then
        echo -e "${RED}MinGW-w64 cross-compiler not found. Installing...${NC}"
        if command -v apt-get >/dev/null 2>&1; then
            sudo apt-get update && sudo apt-get install -y mingw-w64
        elif command -v yum >/dev/null 2>&1; then
            sudo yum install -y mingw64-gcc mingw64-gcc-c++
        elif command -v dnf >/dev/null 2>&1; then
            sudo dnf install -y mingw64-gcc mingw64-gcc-c++
        elif command -v pacman >/dev/null 2>&1; then
            sudo pacman -S --noconfirm mingw-w64-gcc
        elif command -v brew >/dev/null 2>&1; then
            brew install mingw-w64
        else
            echo -e "${RED}Package manager not supported. Please install MinGW-w64 manually:${NC}"
            echo "1. Ubuntu/Debian: sudo apt-get install mingw-w64"
            echo "2. CentOS/RHEL: sudo yum install mingw64-gcc mingw64-gcc-c++"
            echo "3. Arch Linux: sudo pacman -S mingw-w64-gcc"
            echo "4. macOS: brew install mingw-w64"
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
    
    echo -e "${GREEN}Windows cross-compilation environment ready!${NC}"
}

# Build for Windows
build_windows() {
    echo -e "${BLUE}Building for Windows...${NC}"
    
    mkdir -p "build/windows"
    cd "build/windows"
    
    cmake ../.. \
        -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_TOOLCHAIN_FILE="../../cmake/toolchains/windows-mingw.toolchain.cmake" \
        -DBUILD_SHARED_LIBS=ON \
        -DBUILD_TESTS=OFF \
        -DBUILD_EXAMPLES=OFF \
        -DENABLE_QUANTUM_FEEDBACK=ON
    
    make -j$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)
    
    if [ $? -eq 0 ]; then
        echo -e "${GREEN}Windows build completed successfully!${NC}"
        
        # Create Windows package
        create_windows_package
    else
        echo -e "${RED}Windows build failed!${NC}"
        return 1
    fi
    
    cd ../..
}

# Create Windows package
create_windows_package() {
    echo "Creating Windows package..."
    
    mkdir -p "package"
    cd "package"
    
    # Create directory structure
    mkdir -p "bin"
    mkdir -p "lib"
    mkdir -p "include"
    mkdir -p "docs"
    
    # Copy libraries
    if [ -f "../libanantadigital_core.dll" ]; then
        cp "../libanantadigital_core.dll" "bin/"
    fi
    
    if [ -f "../libanantadigital_core.dll.a" ]; then
        cp "../libanantadigital_core.dll.a" "lib/"
    fi
    
    # Copy headers
    cp -r "../../src/*.hpp" "include/" 2>/dev/null || true
    
    # Copy documentation
    cp -r "../../docs/*" "docs/" 2>/dev/null || true
    
    # Create Windows batch file for testing
    cat > "test.bat" << 'EOF'
@echo off
echo Testing anAntaDigital for Windows...
if exist "bin\anantadigital_demo.exe" (
    echo Running demo...
    bin\anantadigital_demo.exe
) else (
    echo Demo executable not found.
)
pause
EOF

    # Create Windows installer script (NSIS)
    cat > "installer.nsi" << 'EOF'
!include "MUI2.nsh"

Name "anAntaDigital"
OutFile "anAntaDigital-Setup.exe"
InstallDir "$PROGRAMFILES\anAntaDigital"
RequestExecutionLevel admin

!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_PAGE_FINISH

!insertmacro MUI_LANGUAGE "English"

Section "anAntaDigital Core" SecCore
    SetOutPath "$INSTDIR"
    File /r "bin\*"
    File /r "lib\*"
    File /r "include\*"
    File /r "docs\*"
    
    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\anAntaDigital" \
                     "DisplayName" "anAntaDigital"
    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\anAntaDigital" \
                     "UninstallString" "$INSTDIR\uninstall.exe"
    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\anAntaDigital" \
                     "DisplayIcon" "$INSTDIR\bin\anantadigital_demo.exe"
    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\anAntaDigital" \
                     "Publisher" "AnantaDigital"
    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\anAntaDigital" \
                     "DisplayVersion" "2.1.0"
    
    WriteUninstaller "$INSTDIR\uninstall.exe"
SectionEnd

Section "Uninstall"
    Delete "$INSTDIR\uninstall.exe"
    RMDir /r "$INSTDIR"
    
    DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\anAntaDigital"
SectionEnd
EOF

    # Create README
    cat > "README.txt" << 'EOF'
anAntaDigital for Windows
========================

This package contains pre-built binaries and libraries for Windows.

## Contents

- bin/     - Executables and DLLs
- lib/     - Import libraries
- include/ - Header files
- docs/    - Documentation

## Installation

1. Run anAntaDigital-Setup.exe as Administrator
2. Follow the installation wizard
3. The library will be installed to Program Files

## Development

To use in your project:

1. Add include/ to your include paths
2. Link against lib/anantadigital_core.dll.a
3. Ensure bin/anantadigital_core.dll is in your PATH or executable directory

## Testing

Run test.bat to test the installation.

## Building from Source

To build from source on Linux/macOS:

```bash
cmake -DCMAKE_TOOLCHAIN_FILE=cmake/toolchains/windows-mingw.toolchain.cmake ..
make
```

## Requirements

- Windows 7 or later
- Visual C++ Redistributable (if using shared libraries)
EOF

    echo -e "${GREEN}Windows package created in build/windows/package/${NC}"
    cd ..
}

# Main execution
main() {
    check_environment
    build_windows
}

main "$@"
