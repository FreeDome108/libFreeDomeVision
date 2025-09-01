# anAntaDigital Multi-Platform Makefile

.PHONY: help all clean linux macos ios android avrora windows

# Default target
help:
	@echo "anAntaDigital Multi-Platform Build System"
	@echo "=========================================="
	@echo ""
	@echo "Available targets:"
	@echo "  all      - Build for all platforms (if possible)"
	@echo "  linux    - Build for Linux"
	@echo "  macos    - Build for macOS"
	@echo "  ios      - Build for iOS"
	@echo "  android  - Build for Android (requires ANDROID_NDK)"
	@echo "  avrora   - Build for Avrora/AVR"
	@echo "  windows  - Build for Windows (cross-compilation)"
	@echo "  clean    - Clean all build directories"
	@echo "  help     - Show this help message"
	@echo ""
	@echo "Examples:"
	@echo "  make linux          # Build for Linux"
	@echo "  make android        # Build for Android"
	@echo "  make all            # Build for all platforms"
	@echo ""
	@echo "Environment variables:"
	@echo "  ANDROID_NDK         - Path to Android NDK (required for Android builds)"

# Build for all platforms
all: linux macos ios android avrora windows

# Build for Linux
linux:
	@echo "Building for Linux..."
	@./build_scripts/build_linux.sh

# Build for macOS
macos:
	@echo "Building for macOS..."
	@./build_scripts/build_macos.sh

# Build for iOS
ios:
	@echo "Building for iOS..."
	@./build_scripts/build_ios.sh

# Build for Android
android:
	@echo "Building for Android..."
	@if [ -z "$$ANDROID_NDK" ]; then \
		echo "Error: ANDROID_NDK environment variable not set"; \
		echo "Please set ANDROID_NDK to your Android NDK path:"; \
		echo "export ANDROID_NDK=/path/to/android-ndk"; \
		exit 1; \
	fi
	@./build_scripts/build_android.sh

# Build for Avrora/AVR
avrora:
	@echo "Building for Avrora/AVR..."
	@./build_scripts/build_avrora.sh

# Build for Windows
windows:
	@echo "Building for Windows..."
	@./build_scripts/build_windows.sh

# Clean all build directories
clean:
	@echo "Cleaning build directories..."
	@rm -rf build/
	@echo "Clean completed."

# Quick build for current platform
current: 
	@echo "Building for current platform..."
	@./build_scripts/build_all_platforms.sh

# Install dependencies (Linux)
install-deps-linux:
	@echo "Installing Linux dependencies..."
	@if command -v apt-get >/dev/null 2>&1; then \
		sudo apt-get update && sudo apt-get install -y cmake build-essential; \
	elif command -v yum >/dev/null 2>&1; then \
		sudo yum install -y cmake gcc-c++ make; \
	elif command -v dnf >/dev/null 2>&1; then \
		sudo dnf install -y cmake gcc-c++ make; \
	elif command -v pacman >/dev/null 2>&1; then \
		sudo pacman -S --noconfirm cmake base-devel; \
	else \
		echo "Package manager not supported. Please install dependencies manually."; \
		exit 1; \
	fi

# Install dependencies (macOS)
install-deps-macos:
	@echo "Installing macOS dependencies..."
	@if command -v brew >/dev/null 2>&1; then \
		brew install cmake make; \
	else \
		echo "Homebrew not found. Please install Homebrew first:"; \
		echo "/bin/bash -c \"\$$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)\""; \
		exit 1; \
	fi
	@echo "Installing Xcode command line tools..."
	@xcode-select --install

# Install dependencies (Android)
install-deps-android:
	@echo "Android NDK is required for Android builds."
	@echo "Please download and install Android NDK from:"
	@echo "https://developer.android.com/ndk"
	@echo ""
	@echo "Then set the ANDROID_NDK environment variable:"
	@echo "export ANDROID_NDK=/path/to/android-ndk"

# Install dependencies (AVR)
install-deps-avr:
	@echo "Installing AVR toolchain..."
	@if command -v apt-get >/dev/null 2>&1; then \
		sudo apt-get update && sudo apt-get install -y gcc-avr avr-libc avrdude; \
	elif command -v yum >/dev/null 2>&1; then \
		sudo yum install -y avr-gcc avr-libc avrdude; \
	elif command -v dnf >/dev/null 2>&1; then \
		sudo dnf install -y avr-gcc avr-libc avrdude; \
	elif command -v pacman >/dev/null 2>&1; then \
		sudo pacman -S --noconfirm avr-gcc avr-libc avrdude; \
	elif command -v brew >/dev/null 2>&1; then \
		brew install avr-gcc avr-libc avrdude; \
	else \
		echo "Package manager not supported. Please install AVR toolchain manually."; \
		exit 1; \
	fi

# Install dependencies (Windows cross-compilation)
install-deps-windows:
	@echo "Installing Windows cross-compilation dependencies..."
	@if command -v apt-get >/dev/null 2>&1; then \
		sudo apt-get update && sudo apt-get install -y mingw-w64; \
	elif command -v yum >/dev/null 2>&1; then \
		sudo yum install -y mingw64-gcc mingw64-gcc-c++; \
	elif command -v dnf >/dev/null 2>&1; then \
		sudo dnf install -y mingw64-gcc mingw64-gcc-c++; \
	elif command -v pacman >/dev/null 2>&1; then \
		sudo pacman -S --noconfirm mingw-w64-gcc; \
	elif command -v brew >/dev/null 2>&1; then \
		brew install mingw-w64; \
	else \
		echo "Package manager not supported. Please install MinGW-w64 manually."; \
		exit 1; \
	fi

# Install all dependencies
install-deps: install-deps-linux install-deps-macos install-deps-android install-deps-avr install-deps-windows

# Check build environment
check-env:
	@echo "Checking build environment..."
	@echo "CMake: $(shell command -v cmake 2>/dev/null || echo 'NOT FOUND')"
	@echo "Make: $(shell command -v make 2>/dev/null || echo 'NOT FOUND')"
	@echo "GCC: $(shell command -v gcc 2>/dev/null || echo 'NOT FOUND')"
	@echo "Clang: $(shell command -v clang 2>/dev/null || echo 'NOT FOUND')"
	@echo "AVR-GCC: $(shell command -v avr-gcc 2>/dev/null || echo 'NOT FOUND')"
	@echo "MinGW: $(shell command -v x86_64-w64-mingw32-gcc 2>/dev/null || echo 'NOT FOUND')"
	@if [ -n "$$ANDROID_NDK" ]; then \
		echo "Android NDK: $$ANDROID_NDK"; \
	else \
		echo "Android NDK: NOT SET"; \
	fi
