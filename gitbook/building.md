## Сборка

### Быстрая сборка

```bash
# Сборка для текущей платформы
./build_all.sh

# Сборка для конкретной платформы
./build_all.sh linux
./build_all.sh macos
./build_all.sh ios
./build_all.sh android
./build_all.sh avrora

# Сборка для всех платформ (кроме Windows)
./build_all.sh all
```

### Детальная сборка

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
# Установите переменную ANDROID_NDK
export ANDROID_NDK=/path/to/android-ndk

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

### Ручная сборка с CMake

```bash
mkdir build
cd build

# Конфигурация
cmake .. \
    -DCMAKE_BUILD_TYPE=Release \
    -DBUILD_SHARED_LIBS=ON \
    -DBUILD_TESTS=ON \
    -DBUILD_EXAMPLES=ON \
    -DENABLE_QUANTUM_FEEDBACK=ON

# Сборка
make -j$(nproc)

# Тесты
make test

# Установка
sudo make install
```
