#include "dome_acoustic_resonator.hpp"
#include <algorithm>
#include <cmath>

namespace AnantaDigital {

DomeAcousticResonator::DomeAcousticResonator(double radius, double height)
    : dome_radius_(radius)
    , dome_height_(height) {
    // Вычисляем собственные частоты при создании
    resonant_frequencies_ = calculateEigenFrequencies();
}

std::vector<double> DomeAcousticResonator::calculateEigenFrequencies() const {
    std::vector<double> frequencies;
    
    // Скорость звука в воздухе (м/с)
    const double speed_of_sound = 343.0;
    
    // Вычисляем собственные частоты для сферического купола
    // Используем приближение для сферических гармоник
    
    // Основные моды (n=0, m=0,1,2...)
    for (int n = 0; n <= 10; ++n) {
        for (int m = 0; m <= n; ++m) {
            double freq = calculateDomeEigenFrequency(n, m);
            if (freq > 20.0 && freq < 20000.0) { // Только в слышимом диапазоне
                frequencies.push_back(freq);
            }
        }
    }
    
    // Сортируем по частоте
    std::sort(frequencies.begin(), frequencies.end());
    
    return frequencies;
}

void DomeAcousticResonator::setMaterialProperties(const std::map<double, double>& properties) {
    acoustic_properties_ = properties;
}

void DomeAcousticResonator::setAcousticProperty(double frequency, double absorption) {
    acoustic_properties_[frequency] = absorption;
}

double DomeAcousticResonator::getAcousticProperty(double frequency) const {
    // Ищем ближайшую частоту
    auto it = acoustic_properties_.lower_bound(frequency);
    
    if (it == acoustic_properties_.end()) {
        // Если частота больше максимальной, возвращаем последнее значение
        if (!acoustic_properties_.empty()) {
            return acoustic_properties_.rbegin()->second;
        }
        return 0.1; // Значение по умолчанию
    }
    
    if (it == acoustic_properties_.begin()) {
        return it->second;
    }
    
    // Интерполяция между ближайшими значениями
    auto prev_it = std::prev(it);
    double freq1 = prev_it->first;
    double freq2 = it->first;
    double abs1 = prev_it->second;
    double abs2 = it->second;
    
    double ratio = (frequency - freq1) / (freq2 - freq1);
    return abs1 + ratio * (abs2 - abs1);
}

double DomeAcousticResonator::calculateReverbTime(double frequency) const {
    // Формула Сабина для времени реверберации
    double volume = calculateVolume();
    double surface_area = calculateSurfaceArea();
    double absorption = getAcousticProperty(frequency);
    
    if (absorption <= 0.0) {
        absorption = 0.1; // Минимальное поглощение
    }
    
    // Время реверберации по формуле Сабина
    double reverb_time = 0.161 * volume / (surface_area * absorption);
    
    return reverb_time;
}

void DomeAcousticResonator::optimizeFrequencyResponse(const std::vector<double>& target_frequencies) {
    // Простая оптимизация - устанавливаем оптимальные значения поглощения
    // для целевых частот
    
    for (double freq : target_frequencies) {
        // Оптимальное поглощение зависит от частоты
        double optimal_absorption;
        
        if (freq < 200.0) {
            // Низкие частоты - меньше поглощения для лучшего баса
            optimal_absorption = 0.2;
        } else if (freq < 2000.0) {
            // Средние частоты - умеренное поглощение
            optimal_absorption = 0.4;
        } else {
            // Высокие частоты - больше поглощения для четкости
            optimal_absorption = 0.6;
        }
        
        setAcousticProperty(freq, optimal_absorption);
    }
    
    // Пересчитываем резонансные частоты
    resonant_frequencies_ = calculateEigenFrequencies();
}

double DomeAcousticResonator::calculateVolume() const {
    // Объем сферического сегмента (купола)
    double h = dome_height_;
    double r = dome_radius_;
    
    // Если высота больше радиуса, это полусфера
    if (h >= r) {
        return (2.0 / 3.0) * M_PI * r * r * r;
    }
    
    // Иначе это сферический сегмент
    double volume = M_PI * h * h * (3.0 * r - h) / 3.0;
    return volume;
}

double DomeAcousticResonator::calculateSurfaceArea() const {
    // Площадь поверхности сферического сегмента
    double h = dome_height_;
    double r = dome_radius_;
    
    // Если высота больше радиуса, это полусфера
    if (h >= r) {
        return 2.0 * M_PI * r * r;
    }
    
    // Иначе это сферический сегмент
    double surface_area = 2.0 * M_PI * r * h;
    return surface_area;
}

double DomeAcousticResonator::calculateDomeEigenFrequency(int n, int m) const {
    // Собственные частоты сферического купола
    // Используем приближение для сферических гармоник
    
    const double speed_of_sound = 343.0;
    
    // Для сферического купола собственные частоты определяются как:
    // f_nm = (c / (2π)) * sqrt(n(n+1)) / R
    // где c - скорость звука, n - радиальное квантовое число, R - радиус
    
    double frequency = (speed_of_sound / (2.0 * M_PI)) * std::sqrt(n * (n + 1.0)) / dome_radius_;
    
    // Добавляем поправку для высоты купола
    double height_factor = 1.0 + (dome_height_ / dome_radius_) * 0.1;
    frequency *= height_factor;
    
    return frequency;
}

double DomeAcousticResonator::calculateSphericalHarmonic(int l, int m, double theta, double phi) const {
    // Вычисление сферических гармоник (упрощенная версия)
    // Это используется для более точного расчета собственных частот
    
    if (l == 0 && m == 0) {
        return 1.0 / std::sqrt(4.0 * M_PI);
    }
    
    // Упрощенная версия - возвращаем базовое значение
    return std::cos(m * phi) * std::sin(theta);
}

double DomeAcousticResonator::calculateAcousticImpedance(double frequency) const {
    // Акустический импеданс материала
    double absorption = getAcousticProperty(frequency);
    
    // Простая модель импеданса
    double impedance = 1.0 / (1.0 + absorption);
    
    return impedance;
}

} // namespace AnantaDigital