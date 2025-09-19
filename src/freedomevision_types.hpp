#pragma once

#include <complex>
#include <vector>
#include <memory>
#include <functional>
#include <map>
#include <mutex>
#include <thread>
#include <chrono>

namespace AnantaDigital {

    // Квантовые состояния звуковых частиц
    enum class QuantumSoundState {
        COHERENT,           // Когерентное состояние
        SUPERPOSITION,      // Суперпозиция
        ENTANGLED,          // Запутанное состояние
        COLLAPSED           // Коллапсированное состояние
    };

    // Типы интерференционных полей
    enum class InterferenceFieldType {
        CONSTRUCTIVE,       // Конструктивная интерференция
        DESTRUCTIVE,        // Деструктивная интерференция
        PHASE_MODULATED,    // Фазово-модулированная
        AMPLITUDE_MODULATED,// Амплитудно-модулированная
        QUANTUM_ENTANGLED   // Квантово-запутанная
    };

    // 3D координаты в купольном пространстве
    struct SphericalCoord {
        double r;       // радиус
        double theta;   // полярный угол (0-π)
        double phi;     // азимутальный угол (0-2π)
        double height;  // высота в куполе
        
        // Оператор сравнения для использования в std::map
        bool operator<(const SphericalCoord& other) const {
            if (r != other.r) return r < other.r;
            if (theta != other.theta) return theta < other.theta;
            if (phi != other.phi) return phi < other.phi;
            return height < other.height;
        }
        
        bool operator==(const SphericalCoord& other) const {
            return r == other.r && theta == other.theta && phi == other.phi && height == other.height;
        }
    };

    // Комплексное звуковое поле с квантовыми свойствами
    struct QuantumSoundField {
        std::complex<double> amplitude;
        double phase;
        double frequency;
        QuantumSoundState quantum_state;
        SphericalCoord position;
        std::chrono::high_resolution_clock::time_point timestamp;
        
        // Квантовая волновая функция
        std::function<std::complex<double>(double, double, double, double)> wave_function;
    };

} // namespace AnantaDigital
