# anAntaDigital Multi-Platform Build Guide

This guide covers building anAntaDigital for multiple platforms including Linux, macOS, iOS, Android, Avrora/AVR, and Windows.

## Supported Platforms

- **Linux** - Native build with GCC/Clang
- **macOS** - Native build with Xcode/Clang
- **iOS** - Cross-compilation for iOS devices and simulator
- **Android** - Cross-compilation for Android NDK
- **Avrora/AVR** - Embedded systems and microcontrollers
- **Windows** - Cross-compilation from Linux/macOS

## Prerequisites

### Common Requirements
- CMake 3.16 or higher
- Make or Ninja build system
- C++17 compatible compiler

### Platform-Specific Requirements

#### Linux
```bash
# Ubuntu/Debian
sudo apt-get install cmake build-essential

# CentOS/RHEL
sudo yum install cmake gcc-c++ make

# Arch Linux
sudo pacman -S cmake base-devel
```

#### macOS
```bash
# Install Homebrew first
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# Install dependencies
brew install cmake make

# Install Xcode command line tools
xcode-select --install
```

#### Android
- Android NDK (set `ANDROID_NDK` environment variable)
- CMake 3.16+
- Make

#### Avrora/AVR
```bash
# Ubuntu/Debian
sudo apt-get install gcc-avr avr-libc avrdude

# macOS
brew install avr-gcc avr-libc avrdude
```

#### Windows (Cross-compilation)
```bash
# Ubuntu/Debian
sudo apt-get install mingw-w64

# macOS
brew install mingw-w64
```

## Quick Start

### Build for Current Platform
```bash
# Make scripts executable
chmod +x build_scripts/*.sh

# Build for current platform
./build_scripts/build_all_platforms.sh
```

### Build for Specific Platform

#### Linux
```bash
./build_scripts/build_linux.sh
```

#### macOS
```bash
./build_scripts/build_macos.sh
```

#### iOS
```bash
./build_scripts/build_ios.sh
```

#### Android
```bash
export ANDROID_NDK=/path/to/android-ndk
./build_scripts/build_android.sh
```

#### Avrora/AVR
```bash
./build_scripts/build_avrora.sh
```

#### Windows
```bash
./build_scripts/build_windows.sh
```

## Manual Build Instructions

### Linux
```bash
mkdir build/linux && cd build/linux
cmake ../.. \
    -DCMAKE_BUILD_TYPE=Release \
    -DBUILD_SHARED_LIBS=ON \
    -DBUILD_TESTS=ON \
    -DBUILD_EXAMPLES=ON \
    -DENABLE_QUANTUM_FEEDBACK=ON
make -j$(nproc)
```

### macOS
```bash
mkdir build/macos && cd build/macos
cmake ../.. \
    -DCMAKE_BUILD_TYPE=Release \
    -DBUILD_SHARED_LIBS=ON \
    -DBUILD_TESTS=ON \
    -DBUILD_EXAMPLES=ON \
    -DENABLE_QUANTUM_FEEDBACK=ON \
    -DCMAKE_OSX_ARCHITECTURES="x86_64;arm64"
make -j$(sysctl -n hw.ncpu)
```

### iOS
```bash
mkdir build/ios && cd build/ios
cmake ../.. \
    -DCMAKE_TOOLCHAIN_FILE=../cmake/toolchains/ios.toolchain.cmake \
    -DIOS_PLATFORM=iphoneos \
    -DIOS_ARCHITECTURES="arm64" \
    -DIOS_DEPLOYMENT_TARGET=12.0
make -j$(sysctl -n hw.ncpu)
```

### Android
```bash
mkdir build/android && cd build/android
cmake ../.. \
    -DCMAKE_TOOLCHAIN_FILE=../cmake/toolchains/android.toolchain.cmake \
    -DANDROID_ABI=arm64-v8a \
    -DANDROID_API_LEVEL=21
make -j$(nproc)
```

### Avrora/AVR
```bash
mkdir build/avrora && cd build/avrora
cmake ../.. \
    -DCMAKE_TOOLCHAIN_FILE=../cmake/toolchains/avrora.toolchain.cmake \
    -DAVR_MCU=atmega328p \
    -DAVR_FREQ=16000000
make -j$(nproc)
```

### Windows
```bash
mkdir build/windows && cd build/windows
cmake ../.. \
    -DCMAKE_TOOLCHAIN_FILE=../cmake/toolchains/windows-mingw.toolchain.cmake
make -j$(nproc)
```

## Build Options

### CMake Options
- `BUILD_SHARED_LIBS` - Build shared libraries (default: ON)
- `BUILD_TESTS` - Build test suite (default: ON)
- `BUILD_EXAMPLES` - Build example applications (default: ON)
- `ENABLE_QUANTUM_FEEDBACK` - Enable quantum feedback system (default: ON)

### Platform-Specific Options

#### Android
- `ANDROID_ABI` - Target architecture (arm64-v8a, armeabi-v7a, x86, x86_64)
- `ANDROID_API_LEVEL` - Minimum API level (default: 21)
- `ANDROID_STL` - STL implementation (c++_shared, c++_static)

#### iOS
- `IOS_PLATFORM` - Target platform (iphoneos, iphonesimulator)
- `IOS_ARCHITECTURES` - Target architectures (arm64, x86_64)
- `IOS_DEPLOYMENT_TARGET` - Minimum iOS version (default: 12.0)

#### Avrora/AVR
- `AVR_MCU` - Microcontroller type (default: atmega328p)
- `AVR_FREQ` - Operating frequency in Hz (default: 16000000)
- `AVR_PROGRAMMER` - Programmer type (default: usbasp)

## Output Structure

After building, the following structure will be created:

```
build/
├── linux/           # Linux binaries and libraries
├── macos/           # macOS binaries and libraries
├── ios/             # iOS frameworks and libraries
│   ├── device/      # Device-specific builds
│   ├── simulator/   # Simulator builds
│   ├── universal/   # Universal libraries
│   └── framework/   # iOS framework
├── android/         # Android libraries by architecture
│   ├── arm64-v8a/
│   ├── armeabi-v7a/
│   ├── x86/
│   ├── x86_64/
│   └── package/     # Android library package
├── avrora/          # AVR microcontroller builds
│   ├── atmega328p/
│   ├── atmega2560/
│   └── package/     # AVR package
└── windows/         # Windows cross-compiled binaries
    └── package/     # Windows package
```

## Package Contents

### Linux/macOS
- Shared libraries (.so/.dylib)
- Static libraries (.a)
- Header files
- Example executables
- Test executables

### iOS
- Universal static library (.a)
- iOS framework bundle
- Header files
- Module map

### Android
- Shared libraries (.so) for each architecture
- Header files
- Android.mk and Application.mk files
- Ready-to-use library package

### Avrora/AVR
- Binary files for each microcontroller
- Hex files for programming
- Header files
- Documentation

### Windows
- DLL and import libraries
- Header files
- Documentation
- NSIS installer script

## Troubleshooting

### Common Issues

#### CMake Not Found
```bash
# Install CMake
# Ubuntu/Debian
sudo apt-get install cmake

# macOS
brew install cmake
```

#### Compiler Not Found
```bash
# Check if compiler is in PATH
which gcc
which clang

# Install build tools
# Ubuntu/Debian
sudo apt-get install build-essential

# macOS
xcode-select --install
```

#### Android NDK Issues
```bash
# Set ANDROID_NDK environment variable
export ANDROID_NDK=/path/to/android-ndk

# Verify NDK path
ls $ANDROID_NDK
```

#### AVR Toolchain Issues
```bash
# Install AVR toolchain
# Ubuntu/Debian
sudo apt-get install gcc-avr avr-libc avrdude

# Verify installation
avr-gcc --version
```

### Platform-Specific Issues

#### iOS Build Fails
- Ensure Xcode is properly installed
- Check iOS deployment target compatibility
- Verify architecture settings

#### Android Build Fails
- Check ANDROID_NDK path
- Verify API level compatibility
- Ensure target architecture is supported

#### AVR Build Fails
- Check AVR-GCC installation
- Verify microcontroller type
- Check frequency settings

## Advanced Configuration

### Custom Toolchains
You can create custom toolchain files by modifying the existing ones in `cmake/toolchains/`.

### Cross-Compilation
For advanced cross-compilation scenarios, modify the toolchain files or create new ones.

### CI/CD Integration
The build scripts can be integrated into CI/CD pipelines by calling the appropriate platform-specific scripts.

## Contributing

When adding new platforms or modifying build configurations:

1. Update the main build script
2. Create platform-specific build script
3. Add appropriate toolchain file
4. Update this documentation
5. Test on target platform

## License

This build system is part of the anAntaDigital project and follows the same license terms.
