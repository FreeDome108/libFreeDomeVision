# anAntaDigital

Библиотека для квантовой акустической обработки и сознательной интеграции.

## Поддерживаемые платформы

- **Linux** - Ubuntu, Debian, CentOS, RHEL
- **macOS** - 10.14+ (Mojave и новее)
- **iOS** - 11.0+ (iPhone, iPad)
- **Android** - API 21+ (Android 5.0+)
- **Avrora** - AVR микроконтроллеры (ATmega328p)
- **Windows** - Windows 10/11, Visual Studio 2019+

## Требования

### Общие требования
- CMake 3.16+
- C++17 совместимый компилятор
- Threads библиотека

### Платформо-специфичные требования

#### Linux
- GCC 7+ или Clang 6+
- make, pkg-config

#### macOS
- Xcode Command Line Tools
- Clang (входит в Xcode)

#### iOS
- Xcode 12+
- iOS SDK 11.0+

#### Android
- Android NDK 25.2+
- CMake 3.16+
- Переменная окружения `ANDROID_NDK_HOME`

#### Avrora
- avr-gcc
- avr-g++

#### Windows
- Visual Studio 2019+ или MinGW-w64
- CMake 3.16+

## Быстрая сборка

### Сборка для всех платформ

```bash
# Сделать скрипт исполняемым
chmod +x build_all_platforms.sh

# Собрать для всех платформ
./build_all_platforms.sh

# Или для конкретной платформы
./build_all_platforms.sh linux
./build_all_platforms.sh macos
./build_all_platforms.sh ios
./build_all_platforms.sh android
./build_all_platforms.sh avrora
./build_all_platforms.sh windows
```

### Индивидуальные скрипты сборки

#### Linux
```bash
chmod +x build_linux.sh
./build_linux.sh
```

#### macOS
```bash
chmod +x build_macos.sh
./build_macos.sh
```

#### iOS
```bash
chmod +x build_ios.sh
./build_ios.sh
```

#### Android
```bash
chmod +x build_android.sh
./build_android.sh
```

#### Avrora
```bash
chmod +x build_avrora.sh
./build_avrora.sh
```

#### Windows
```cmd
build_windows.bat
```

## Ручная сборка с CMake

### Linux/macOS
```bash
mkdir build && cd build
cmake .. \
    -DCMAKE_BUILD_TYPE=Release \
    -DBUILD_SHARED_LIBS=ON \
    -DBUILD_TESTS=ON \
    -DBUILD_EXAMPLES=ON \
    -DENABLE_QUANTUM_FEEDBACK=ON
make -j$(nproc)
make test
sudo make install
```

### iOS
```bash
mkdir build_ios && cd build_ios
cmake .. \
    -DCMAKE_SYSTEM_NAME=iOS \
    -DCMAKE_OSX_DEPLOYMENT_TARGET=11.0 \
    -DCMAKE_OSX_ARCHITECTURES="arm64;x86_64" \
    -DBUILD_SHARED_LIBS=OFF \
    -DBUILD_TESTS=OFF \
    -DBUILD_EXAMPLES=OFF
make -j$(sysctl -n hw.ncpu)
```

### Android
```bash
mkdir build_android && cd build_android
cmake .. \
    -DCMAKE_SYSTEM_NAME=Android \
    -DCMAKE_SYSTEM_VERSION=21 \
    -DCMAKE_ANDROID_ARCH_ABI=arm64-v8a \
    -DCMAKE_ANDROID_NDK=$ANDROID_NDK_HOME \
    -DCMAKE_ANDROID_NDK_TOOLCHAIN_VERSION=clang
make -j$(nproc)
```

### Avrora
```bash
mkdir build_avrora && cd build_avrora
cmake .. \
    -DCMAKE_SYSTEM_NAME=Avrora \
    -DCMAKE_CXX_COMPILER=avr-g++ \
    -DCMAKE_C_COMPILER=avr-gcc \
    -DCMAKE_CXX_FLAGS="-mmcu=atmega328p -Os" \
    -DBUILD_SHARED_LIBS=OFF
make -j$(nproc)
```

## Структура проекта

```
anAntaDigital/
├── src/                    # Исходный код
│   ├── anantadigital_core.cpp
│   ├── quantum_feedback_system.cpp
│   ├── consciousness_hybrid.cpp
│   └── consciousness_integration.cpp
├── examples/               # Демо приложения
│   ├── anantadigital_demo.cpp
│   └── quantum_acoustic_demo.cpp
├── tests/                  # Тесты
│   ├── test_anantadigital_core.cpp
│   ├── test_quantum_feedback.cpp
│   └── test_consciousness.cpp
├── toolchains/             # Файлы инструментария
│   ├── android-toolchain.cmake
│   ├── ios-toolchain.cmake
│   └── avrora-toolchain.cmake
├── build_*.sh              # Скрипты сборки для Unix-систем
├── build_windows.bat       # Скрипт сборки для Windows
├── build_all_platforms.sh  # Универсальный скрипт сборки
└── CMakeLists.txt          # Основной файл CMake
```

## Опции сборки

| Опция | Описание | По умолчанию |
|-------|----------|--------------|
| `BUILD_SHARED_LIBS` | Сборка разделяемых библиотек | ON |
| `BUILD_TESTS` | Сборка тестов | ON |
| `BUILD_EXAMPLES` | Сборка примеров | ON |
| `ENABLE_QUANTUM_FEEDBACK` | Включить квантовую систему обратной связи | ON |
| `CMAKE_BUILD_TYPE` | Тип сборки (Debug/Release/RelWithDebInfo/MinSizeRel) | Release |

## Тестирование

```bash
# Запуск всех тестов
make test

# Или через CTest
ctest --output-on-failure

# Запуск конкретного теста
./anantadigital_tests
```

## Установка

```bash
# Установка в системную директорию
sudo make install

# Установка в пользовательскую директорию
cmake .. -DCMAKE_INSTALL_PREFIX=$HOME/.local
make install
```

## Использование в других проектах

### CMake
```cmake
find_package(anAntaDigital REQUIRED)
target_link_libraries(your_target anantadigital::anantadigital_core)
```

### pkg-config
```bash
pkg-config --cflags --libs anantadigital
```

## Устранение неполадок

### Ошибки компиляции
- Убедитесь, что используется C++17 совместимый компилятор
- Проверьте версию CMake (должна быть 3.16+)

### Android NDK не найден
```bash
export ANDROID_NDK_HOME=/path/to/your/android-ndk
```

### AVR инструменты не найдены
```bash
# Ubuntu/Debian
sudo apt-get install gcc-avr avr-libc

# macOS
brew install avr-gcc
```

### iOS сборка не работает
- Убедитесь, что Xcode установлен и обновлен
- Проверьте версию iOS SDK

## Лицензия

[Укажите вашу лицензию здесь]

## Поддержка

[Укажите контактную информацию для поддержки]
