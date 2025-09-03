#!/bin/bash

set -e

echo "=== anAntaDigital Universal Build Script ==="
echo "Detecting platform and building..."

# Detect platform
if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    PLATFORM="Linux"
elif [[ "$OSTYPE" == "darwin"* ]]; then
    PLATFORM="macOS"
elif [[ "$OSTYPE" == "cygwin" ]] || [[ "$OSTYPE" == "msys" ]] || [[ "$OSTYPE" == "win32" ]]; then
    PLATFORM="Windows"
else
    echo "Unknown platform: $OSTYPE"
    exit 1
fi

echo "Detected platform: $PLATFORM"

# Function to build for specific platform
build_for_platform() {
    local platform=$1
    echo "Building for $platform..."
    
    case $platform in
        "Linux")
            if [ -f "build_linux.sh" ]; then
                chmod +x build_linux.sh
                ./build_linux.sh
            else
                echo "Linux build script not found!"
                exit 1
            fi
            ;;
        "macOS")
            if [ -f "build_macos.sh" ]; then
                chmod +x build_macos.sh
                ./build_macos.sh
            else
                echo "macOS build script not found!"
                exit 1
            fi
            ;;
        "iOS")
            if [ -f "build_ios.sh" ]; then
                chmod +x build_ios.sh
                ./build_ios.sh
            else
                echo "iOS build script not found!"
                exit 1
            fi
            ;;
        "Android")
            if [ -f "build_android.sh" ]; then
                chmod +x build_android.sh
                ./build_android.sh
            else
                echo "Android build script not found!"
                exit 1
            fi
            ;;
        "Avrora")
            if [ -f "build_avrora.sh" ]; then
                chmod +x build_avrora.sh
                ./build_avrora.sh
            else
                echo "Avrora build script not found!"
                exit 1
            fi
            ;;
        "Windows")
            if [ -f "build_windows.bat" ]; then
                echo "Windows build script found. Please run manually:"
                echo "  build_windows.bat"
                exit 1
            else
                echo "Windows build script not found!"
                exit 1
            fi
            ;;
        *)
            echo "Unknown platform: $platform"
            exit 1
            ;;
    esac
}

# Main build logic
if [ $# -eq 0 ]; then
    # No arguments - build for current platform
    build_for_platform "$PLATFORM"
else
    # Build for specified platforms
    for platform in "$@"; do
        case $platform in
            "linux"|"Linux")
                build_for_platform "Linux"
                ;;
            "macos"|"macOS")
                build_for_platform "macOS"
                ;;
            "ios"|"iOS")
                build_for_platform "iOS"
                ;;
            "android"|"Android")
                build_for_platform "Android"
                ;;
            "avrora"|"Avrora")
                build_for_platform "Avrora"
                ;;
            "windows"|"Windows")
                build_for_platform "Windows"
                ;;
            "all")
                echo "Building for all platforms..."
                build_for_platform "Linux"
                build_for_platform "macOS"
                build_for_platform "iOS"
                build_for_platform "Android"
                build_for_platform "Avrora"
                echo "Note: Windows build must be run manually on Windows system"
                ;;
            *)
                echo "Unknown platform: $platform"
                echo "Supported platforms: linux, macos, ios, android, avrora, windows, all"
                exit 1
                ;;
        esac
    done
fi

echo "=== Build completed successfully! ==="





