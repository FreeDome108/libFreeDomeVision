#pragma once

#include <vector>
#include <map>
#include <memory>

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
    
    // Получить акустическое свойство для частоты
    double getAcousticProperty(double frequency) const;
    
    // Установить акустическое свойство для частоты
    void setAcousticProperty(double frequency, double property);
    
    // Получить радиус купола
    double getRadius() const { return dome_radius_; }
    
    // Получить высоту купола
    double getHeight() const { return dome_height_; }
    
    // Получить все резонансные частоты
    const std::vector<double>& getResonantFrequencies() const { return resonant_frequencies_; }
    
    // Обновить геометрию купола
    void updateGeometry(double radius, double height);
    
    // Оптимизировать акустические свойства
    void optimizeAcousticProperties();
};

} // namespace AnantaDigital
