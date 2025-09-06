#pragma once

#include "anantadigital_types.hpp"
#include <vector>
#include <memory>
#include <mutex>
#include <complex>
#include <cmath>

namespace AnantaDigital {

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
    
    // Геттеры
    InterferenceFieldType getType() const { return type_; }
    SphericalCoord getCenter() const { return center_position_; }
    double getRadius() const { return field_radius_; }
    size_t getSourceFieldCount() const { return source_fields_.size(); }
    
    // Удалить источник поля
    void removeSourceField(size_t index);
    
    // Очистить все источники
    void clearSourceFields();
    
private:
    // Приватные методы
    double calculateDistance(const SphericalCoord& pos1, const SphericalCoord& pos2) const;
    std::complex<double> calculatePhaseDelay(double distance, double frequency, double time) const;
    std::complex<double> applyInterferenceType(const std::complex<double>& signal, InterferenceFieldType type) const;
};

} // namespace AnantaDigital