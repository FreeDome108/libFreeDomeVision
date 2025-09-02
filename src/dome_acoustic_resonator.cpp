#include "anantadigital_core.hpp"
#include <cmath>
#include <algorithm>

namespace AnantaDigital {

DomeAcousticResonator::DomeAcousticResonator(double radius, double height)
    : dome_radius_(radius), dome_height_(height) {
    
    // Вычисляем базовые резонансные частоты для купола
    // Используем формулу для сферического резонатора
    double speed_of_sound = 343.0; // м/с
    
    // Основные моды резонанса
    resonant_frequencies_.push_back(speed_of_sound / (2.0 * dome_radius_)); // Основная мода
    resonant_frequencies_.push_back(speed_of_sound / dome_radius_); // Вторая гармоника
    resonant_frequencies_.push_back(1.5 * speed_of_sound / dome_radius_); // Третья гармоника
    
    // Высотные моды
    if (dome_height_ > 0) {
        resonant_frequencies_.push_back(speed_of_sound / (2.0 * dome_height_));
        resonant_frequencies_.push_back(speed_of_sound / dome_height_);
    }
    
    // Сортируем частоты
    std::sort(resonant_frequencies_.begin(), resonant_frequencies_.end());
}

std::vector<double> DomeAcousticResonator::calculateEigenFrequencies() const {
    return resonant_frequencies_;
}

void DomeAcousticResonator::setMaterialProperties(const std::map<double, double>& properties) {
    acoustic_properties_ = properties;
}

double DomeAcousticResonator::calculateReverbTime(double frequency) const {
    // Базовое время реверберации для купола
    double base_reverb_time = 2.0; // секунды
    
    // Корректировка на основе частоты
    if (frequency < 100.0) {
        // Низкие частоты - больше реверберации
        base_reverb_time *= 1.5;
    } else if (frequency > 5000.0) {
        // Высокие частоты - меньше реверберации
        base_reverb_time *= 0.7;
    }
    
    // Корректировка на основе свойств материала
    auto it = acoustic_properties_.lower_bound(frequency);
    if (it != acoustic_properties_.end()) {
        double absorption_coefficient = it->second;
        // Чем больше коэффициент поглощения, тем меньше время реверберации
        base_reverb_time *= (1.0 - absorption_coefficient);
    }
    
    // Минимальное время реверберации
    return std::max(base_reverb_time, 0.1);
}

void DomeAcousticResonator::optimizeFrequencyResponse(const std::vector<double>& target_frequencies) {
    // Простая оптимизация - добавляем недостающие частоты
    for (double target_freq : target_frequencies) {
        bool found = false;
        for (double existing_freq : resonant_frequencies_) {
            if (std::abs(target_freq - existing_freq) < 1.0) {
                found = true;
                break;
            }
        }
        
        if (!found) {
            resonant_frequencies_.push_back(target_freq);
        }
    }
    
    // Сортируем обновленный список
    std::sort(resonant_frequencies_.begin(), resonant_frequencies_.end());
}

} // namespace AnantaDigital
