# anAntaDigital

Квантовая акустическая система сознания для купольных пространств.

## Описание

anAntaDigital - это библиотека для создания квантовых интерференционных полей в купольных акустических пространствах. Система интегрирует квантовую механику, акустику и сознание для создания уникальных звуковых переживаний.

## Возможности

- **Квантовые интерференционные поля** - создание сложных звуковых паттернов
- **Купольные акустические резонаторы** - оптимизация акустики для купольных пространств
- **Гибридная система сознания** - интеграция квантовых состояний сознания
- **Кросс-платформенность** - поддержка Linux, macOS, iOS, Android, Avrora, Windows

## Требования

### Общие требования
- CMake 3.16 или выше
- C++17 совместимый компилятор
- pthread (для Linux/macOS)

### Платформо-специфичные требования

#### Linux
- GCC 7+ или Clang 5+
- libportaudio-dev
- libsndfile1-dev

#### macOS
- Xcode Command Line Tools
- Homebrew (для зависимостей)
- portaudio
- sndfile

#### iOS
- Xcode 12+
- iOS SDK 11.0+

#### Android
- Android NDK r21+
- CMake 3.18+

#### Avrora
- AVR-GCC
- AVR-LIBC

#### Windows
- Visual Studio 2019+ или MinGW-w64
- CMake 3.16+

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

## Структура проекта

```
anAntaDigital/
├── src/                    # Исходный код
│   ├── anantadigital_core.cpp
│   ├── anantadigital_core.hpp
│   ├── quantum_feedback_system.cpp
│   ├── quantum_feedback_system.hpp
│   ├── consciousness_hybrid.cpp
│   ├── consciousness_hybrid.hpp
│   ├── consciousness_integration.cpp
│   ├── consciousness_integration.hpp
│   ├── interference_field.cpp
│   ├── interference_field.hpp
│   ├── dome_acoustic_resonator.cpp
│   └── dome_acoustic_resonator.hpp
├── examples/               # Примеры использования
├── tests/                  # Тесты
├── cmake/                  # CMake конфигурация
├── build_*.sh             # Скрипты сборки для Unix-систем
├── build_windows.bat      # Скрипт сборки для Windows
├── build_all.sh           # Универсальный скрипт сборки
└── CMakeLists.txt         # Основной CMake файл
```

## Использование

### C++ API

```cpp
#include <anantadigital/anantadigital_core.hpp>

// Инициализация системы
AnantaDigital::InterferenceField field(
    AnantaDigital::InterferenceFieldType::CONSTRUCTIVE,
    {10.0, M_PI/2, 0.0, 5.0}, // сферические координаты
    5.0 // радиус поля
);

// Добавление источника звука
AnantaDigital::QuantumSoundField source;
source.amplitude = std::complex<double>(1.0, 0.0);
source.frequency = 440.0; // 440 Hz
source.position = {5.0, M_PI/4, M_PI/2, 2.5};

field.addSourceField(source);

// Вычисление интерференции
auto interference = field.calculateInterference(
    {8.0, M_PI/3, M_PI/4, 3.0}, // точка наблюдения
    0.0 // время
);
```

### C API

```c
#include <anantadigital_core.h>

// Инициализация
anantadigital_initialize();

// Создание интерференционного поля
void* field = anantadigital_create_interference_field(
    0, // CONSTRUCTIVE
    10.0, 1.57, 0.0, 5.0, // r, theta, phi, height
    5.0 // radius
);

// Очистка
anantadigital_shutdown();
```

## Тестирование

```bash
# Запуск всех тестов
make test

# Запуск конкретного теста
./tests/anantadigital_tests
```

## Примеры

```bash
# Сборка примеров
make examples

# Запуск демо
./examples/anantadigital_demo
./examples/quantum_acoustic_demo
./examples/audio_playback_demo
```

## Установка

После успешной сборки библиотека устанавливается в системные директории:

- **Linux/macOS**: `/usr/local/lib` и `/usr/local/include/anantadigital`
- **Windows**: `install/lib` и `install/include/anantadigital`
- **iOS/Android**: `build_*/install/*/lib` и `build_*/install/*/include/anantadigital`

## Лицензия

[Укажите вашу лицензию здесь]

## Поддержка

Для получения поддержки создайте issue в репозитории или свяжитесь с командой разработки.

## Вклад в проект

Мы приветствуем вклад в развитие проекта! Пожалуйста, создайте pull request или обсудите изменения в issue.

## История версий

- **2.1.0** - Текущая версия с поддержкой всех платформ
- **2.0.0** - Переход на C++17 и новая архитектура
- **1.0.0** - Первая стабильная версия
