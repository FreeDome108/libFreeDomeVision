#include "interference_field.hpp"
#include <algorithm>
#include <numeric>
#include <cmath>

namespace AnantaDigital {

InterferenceField::InterferenceField(InterferenceFieldType type, SphericalCoord center, double radius)
    : type_(type)
    , center_position_(center)
    , field_radius_(radius) {
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
    
    for (const auto& source : source_fields_) {
        // Вычисляем расстояние от источника до точки наблюдения
        double distance = calculateDistance(source.position, position);
        
        // Вычисляем фазовую задержку
        auto phase_delay = calculatePhaseDelay(distance, source.frequency, time);
        
        // Применяем амплитуду и фазу
        std::complex<double> field_contribution = source.amplitude * phase_delay;
        
        // Применяем затухание с расстоянием
        double attenuation = 1.0 / (1.0 + distance * 0.1);
        field_contribution *= attenuation;
        
        // Добавляем к общей интерференции
        total_interference += field_contribution;
    }
    
    // Применяем тип интерференции
    return applyInterferenceType(total_interference, type_);
}

QuantumSoundField InterferenceField::quantumSuperposition(const std::vector<QuantumSoundField>& fields) const {
    if (fields.empty()) {
        return QuantumSoundField{};
    }
    
    QuantumSoundField result;
    result.quantum_state = QuantumSoundState::SUPERPOSITION;
    result.timestamp = std::chrono::high_resolution_clock::now();
    
    // Вычисляем средневзвешенную позицию
    double total_weight = 0.0;
    SphericalCoord avg_position{0.0, 0.0, 0.0, 0.0};
    
    for (const auto& field : fields) {
        double weight = std::abs(field.amplitude);
        total_weight += weight;
        
        avg_position.r += field.position.r * weight;
        avg_position.theta += field.position.theta * weight;
        avg_position.phi += field.position.phi * weight;
        avg_position.height += field.position.height * weight;
    }
    
    if (total_weight > 0.0) {
        avg_position.r /= total_weight;
        avg_position.theta /= total_weight;
        avg_position.phi /= total_weight;
        avg_position.height /= total_weight;
    }
    
    result.position = avg_position;
    
    // Вычисляем суперпозицию амплитуд
    std::complex<double> total_amplitude(0.0, 0.0);
    double total_frequency = 0.0;
    
    for (const auto& field : fields) {
        total_amplitude += field.amplitude;
        total_frequency += field.frequency;
    }
    
    result.amplitude = total_amplitude / static_cast<double>(fields.size());
    result.frequency = total_frequency / static_cast<double>(fields.size());
    result.phase = std::arg(result.amplitude);
    
    return result;
}

void InterferenceField::updateQuantumState(double dt) {
    std::lock_guard<std::mutex> lock(field_mutex_);
    
    for (auto& field : source_fields_) {
        // Обновляем квантовое состояние
        switch (field.quantum_state) {
            case QuantumSoundState::COHERENT:
                // Когерентное состояние остается стабильным
                break;
                
            case QuantumSoundState::SUPERPOSITION:
                // Суперпозиция может коллапсировать
                if (std::rand() % 100 < 5) { // 5% вероятность коллапса
                    field.quantum_state = QuantumSoundState::COLLAPSED;
                }
                break;
                
            case QuantumSoundState::ENTANGLED:
                // Запутанное состояние может распутаться
                if (std::rand() % 100 < 2) { // 2% вероятность распутывания
                    field.quantum_state = QuantumSoundState::COHERENT;
                }
                break;
                
            case QuantumSoundState::COLLAPSED:
                // Коллапсированное состояние может вернуться к когерентному
                if (std::rand() % 100 < 10) { // 10% вероятность восстановления
                    field.quantum_state = QuantumSoundState::COHERENT;
                }
                break;
        }
        
        // Обновляем временную метку
        field.timestamp = std::chrono::high_resolution_clock::now();
    }
}

void InterferenceField::createQuantumEntanglement(size_t field1_idx, size_t field2_idx) {
    std::lock_guard<std::mutex> lock(field_mutex_);
    
    if (field1_idx >= source_fields_.size() || field2_idx >= source_fields_.size() || 
        field1_idx == field2_idx) {
        return;
    }
    
    // Создаем квантовую запутанность между полями
    source_fields_[field1_idx].quantum_state = QuantumSoundState::ENTANGLED;
    source_fields_[field2_idx].quantum_state = QuantumSoundState::ENTANGLED;
    
    // Синхронизируем фазы
    double avg_phase = (source_fields_[field1_idx].phase + source_fields_[field2_idx].phase) / 2.0;
    source_fields_[field1_idx].phase = avg_phase;
    source_fields_[field2_idx].phase = avg_phase;
}

void InterferenceField::removeSourceField(size_t index) {
    std::lock_guard<std::mutex> lock(field_mutex_);
    
    if (index < source_fields_.size()) {
        source_fields_.erase(source_fields_.begin() + index);
    }
}

void InterferenceField::clearSourceFields() {
    std::lock_guard<std::mutex> lock(field_mutex_);
    source_fields_.clear();
}

double InterferenceField::calculateDistance(const SphericalCoord& pos1, const SphericalCoord& pos2) const {
    // Преобразуем сферические координаты в декартовы для вычисления расстояния
    double x1 = pos1.r * std::sin(pos1.theta) * std::cos(pos1.phi);
    double y1 = pos1.r * std::sin(pos1.theta) * std::sin(pos1.phi);
    double z1 = pos1.r * std::cos(pos1.theta) + pos1.height;
    
    double x2 = pos2.r * std::sin(pos2.theta) * std::cos(pos2.phi);
    double y2 = pos2.r * std::sin(pos2.theta) * std::sin(pos2.phi);
    double z2 = pos2.r * std::cos(pos2.theta) + pos2.height;
    
    double dx = x2 - x1;
    double dy = y2 - y1;
    double dz = z2 - z1;
    
    return std::sqrt(dx*dx + dy*dy + dz*dz);
}

std::complex<double> InterferenceField::calculatePhaseDelay(double distance, double frequency, double time) const {
    // Вычисляем фазовую задержку с учетом времени распространения
    double phase = 2.0 * M_PI * frequency * (time - distance / 343.0); // 343 м/с - скорость звука
    return std::complex<double>(std::cos(phase), std::sin(phase));
}

std::complex<double> InterferenceField::applyInterferenceType(const std::complex<double>& signal, InterferenceFieldType type) const {
    switch (type) {
        case InterferenceFieldType::CONSTRUCTIVE:
            return signal; // Конструктивная интерференция - без изменений
            
        case InterferenceFieldType::DESTRUCTIVE:
            return -signal; // Деструктивная интерференция - инверсия фазы
            
        case InterferenceFieldType::PHASE_MODULATED:
            // Фазово-модулированная интерференция
            {
                double phase_mod = std::sin(std::arg(signal) * 2.0);
                return signal * std::complex<double>(std::cos(phase_mod), std::sin(phase_mod));
            }
            
        case InterferenceFieldType::AMPLITUDE_MODULATED:
            // Амплитудно-модулированная интерференция
            {
                double amp_mod = (1.0 + std::sin(std::arg(signal))) / 2.0;
                return signal * amp_mod;
            }
            
        case InterferenceFieldType::QUANTUM_ENTANGLED:
            // Квантово-запутанная интерференция
            {
                double quantum_factor = std::abs(signal) * std::cos(std::arg(signal));
                return signal * quantum_factor;
            }
            
        default:
            return signal;
    }
}

} // namespace AnantaDigital