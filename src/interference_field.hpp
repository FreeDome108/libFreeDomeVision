#pragma once

#include <complex>
#include <vector>
#include <mutex>
#include <functional>
#include <chrono>

namespace AnantaDigital {

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
};

// Комплексное звуковое поле с квантовыми свойствами
struct QuantumSoundField {
    std::complex<double> amplitude;
    double phase;
    double frequency;
    enum class QuantumSoundState {
        COHERENT,           // Когерентное состояние
        SUPERPOSITION,      // Суперпозиция
        ENTANGLED,          // Запутанное состояние
        COLLAPSED           // Коллапсированное состояние
    } quantum_state;
    SphericalCoord position;
    std::chrono::high_resolution_clock::time_point timestamp;
    
    // Квантовая волновая функция
    std::function<std::complex<double>(double, double, double, double)> wave_function;
};

// Интерференционное поле
class InterferenceField {
private:
    InterferenceFieldType type_;
    std::vector<QuantumSoundField> source_fields_;
    SphericalCoord center_position_;
    double field_radius_;
    mutable std::mutex field_mutex_;

public:
    InterferenceField(InterferenceFieldType type, SphericalCoord center, double radius);
    
    // Добавить источник звукового поля
    void addSourceField(const QuantumSoundField& field);
    
    // Вычислить результирующую интерференцию в точке
    std::complex<double> calculateInterference(const SphericalCoord& position, double time) const;
    
    // Квантовая суперпозиция полей
    QuantumSoundField quantumSuperposition(const std::vector<QuantumSoundField>& fields) const;
    
    // Обновить поле с учетом квантовых эффектов
    void updateQuantumState(double dt);
    
    // Создать квантовую запутанность между полями
    void createQuantumEntanglement(size_t field1_idx, size_t field2_idx);
    
    // Получить тип поля
    InterferenceFieldType getType() const { return type_; }
    
    // Получить центр поля
    SphericalCoord getCenter() const { return center_position_; }
    
    // Получить радиус поля
    double getRadius() const { return field_radius_; }
};

} // namespace AnantaDigital
