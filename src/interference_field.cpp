#include "anantadigital_core.hpp"
#include <cmath>
#include <algorithm>

namespace AnantaDigital {

InterferenceField::InterferenceField(InterferenceFieldType type, SphericalCoord center, double radius)
    : type_(type), center_position_(center), field_radius_(radius) {
}

void InterferenceField::addSourceField(const QuantumSoundField& field) {
    std::lock_guard<std::mutex> lock(field_mutex_);
    source_fields_.push_back(field);
}

std::complex<double> InterferenceField::calculateInterference(const SphericalCoord& position, double time) const {
    std::lock_guard<std::mutex> lock(field_mutex_);
    
    if (source_fields_.empty()) {
        return std::complex<double>(0.0, 0.0);
    }
    
    std::complex<double> total_interference(0.0, 0.0);
    
    for (const auto& field : source_fields_) {
        // Простая модель интерференции
        double distance = std::sqrt(
            std::pow(position.r - field.position.r, 2) +
            std::pow(position.theta - field.position.theta, 2) +
            std::pow(position.phi - field.position.phi, 2)
        );
        
        double phase_delay = 2.0 * M_PI * field.frequency * time - distance / 343.0; // 343 m/s - скорость звука
        
        std::complex<double> field_contribution = field.amplitude * std::exp(std::complex<double>(0, phase_delay));
        
        switch (type_) {
            case InterferenceFieldType::CONSTRUCTIVE:
                total_interference += field_contribution;
                break;
            case InterferenceFieldType::DESTRUCTIVE:
                total_interference -= field_contribution;
                break;
            case InterferenceFieldType::PHASE_MODULATED:
                total_interference += field_contribution * std::exp(std::complex<double>(0, phase_delay * 0.5));
                break;
            case InterferenceFieldType::AMPLITUDE_MODULATED:
                total_interference += field_contribution * (1.0 + 0.3 * std::sin(2.0 * M_PI * 10.0 * time));
                break;
            case InterferenceFieldType::QUANTUM_ENTANGLED:
                total_interference += field_contribution * std::exp(std::complex<double>(0, phase_delay * 2.0));
                break;
        }
    }
    
    return total_interference;
}

QuantumSoundField InterferenceField::quantumSuperposition(const std::vector<QuantumSoundField>& fields) const {
    if (fields.empty()) {
        return QuantumSoundField{};
    }
    
    QuantumSoundField superposition = fields[0];
    superposition.amplitude = std::complex<double>(0.0, 0.0);
    superposition.quantum_state = QuantumSoundState::SUPERPOSITION;
    
    for (const auto& field : fields) {
        superposition.amplitude += field.amplitude;
        superposition.frequency = (superposition.frequency + field.frequency) / 2.0;
    }
    
    return superposition;
}

void InterferenceField::updateQuantumState(double dt) {
    std::lock_guard<std::mutex> lock(field_mutex_);
    
    for (auto& field : source_fields_) {
        // Обновление квантового состояния
        if (field.quantum_state == QuantumSoundState::COHERENT) {
            // Небольшая случайность для моделирования квантовых флуктуаций
            double random_phase = (static_cast<double>(rand()) / RAND_MAX) * 0.1;
            field.phase += random_phase;
        }
    }
}

void InterferenceField::createQuantumEntanglement(size_t field1_idx, size_t field2_idx) {
    std::lock_guard<std::mutex> lock(field_mutex_);
    
    if (field1_idx < source_fields_.size() && field2_idx < source_fields_.size()) {
        source_fields_[field1_idx].quantum_state = QuantumSoundState::ENTANGLED;
        source_fields_[field2_idx].quantum_state = QuantumSoundState::ENTANGLED;
    }
}

} // namespace AnantaDigital
