## Примеры

```bash
# Сборка примеров
make examples

# Запуск демо
./examples/anantadigital_demo
./examples/quantum_acoustic_demo
./examples/audio_playback_demo
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
