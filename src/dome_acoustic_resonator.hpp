#pragma once

#include <vector>
#include <map>
#include <cmath>

namespace AnantaDigital {

// Акустический резонатор для купола
class DomeAcousticResonator {
private:
    double dome_radius_;
    double dome_height_;
    std::vector<double> resonant_frequencies_;
    std::map<double, double> acoustic_properties_;

public:
    DomeAcousticResonator(double radius, double height);
    
    // Вычислить собственные частоты купола
    std::vector<double> calculateEigenFrequencies() const;
    
    // Моделирование акустических свойств материалов
    void setMaterialProperties(const std::map<double, double>& properties);
    void setAcousticProperty(double frequency, double absorption);
    double getAcousticProperty(double frequency) const;
    
    // Вычислить время реверберации
    double calculateReverbTime(double frequency) const;
    
    // Оптимизация частотной характеристики
    void optimizeFrequencyResponse(const std::vector<double>& target_frequencies);
    
    // Геттеры
    double getRadius() const { return dome_radius_; }
    double getHeight() const { return dome_height_; }
    
    // Вычислить объем купола
    double calculateVolume() const;
    
    // Вычислить площадь поверхности
    double calculateSurfaceArea() const;
    
    // Получить резонансные частоты
    const std::vector<double>& getResonantFrequencies() const { return resonant_frequencies_; }
    
private:
    // Приватные методы
    double calculateDomeEigenFrequency(int n, int m) const;
    double calculateSphericalHarmonic(int l, int m, double theta, double phi) const;
    double calculateAcousticImpedance(double frequency) const;
};

} // namespace AnantaDigital