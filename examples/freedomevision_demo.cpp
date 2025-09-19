#include <iostream>
#include <cmath>
#include "../src/anantadigital_core.hpp"

using namespace AnantaDigital;

int main() {
    std::cout << "=== anAntaDigital Demo ===" << std::endl;
    
    try {
        // Создание купольного резонатора
        DomeAcousticResonator resonator(10.0, 5.0);
        std::cout << "Created dome resonator: radius=" << resonator.getRadius() 
                  << "m, height=" << resonator.getHeight() << "m" << std::endl;
        
        // Вычисление собственных частот
        auto eigen_freqs = resonator.calculateEigenFrequencies();
        std::cout << "Eigen frequencies: ";
        for (size_t i = 0; i < std::min(eigen_freqs.size(), size_t(5)); ++i) {
            std::cout << eigen_freqs[i] << " Hz ";
        }
        std::cout << "..." << std::endl;
        
        // Создание интерференционного поля
        SphericalCoord center{5.0, M_PI/2, 0.0, 2.5};
        InterferenceField field(InterferenceFieldType::CONSTRUCTIVE, center, 3.0);
        std::cout << "Created interference field at center: r=" << center.r 
                  << ", theta=" << center.theta << ", phi=" << center.phi << std::endl;
        
        // Добавление источника звука
        QuantumSoundField source;
        source.amplitude = std::complex<double>(1.0, 0.0);
        source.frequency = 440.0; // 440 Hz
        source.position = {3.0, M_PI/4, M_PI/2, 1.5};
        source.quantum_state = QuantumSoundState::COHERENT;
        
        field.addSourceField(source);
        std::cout << "Added sound source: " << source.frequency << " Hz at position "
                  << source.position.r << ", " << source.position.theta << ", " 
                  << source.position.phi << std::endl;
        
        // Вычисление интерференции в точке
        SphericalCoord observation_point{7.0, M_PI/3, M_PI/4, 3.0};
        auto interference = field.calculateInterference(observation_point, 0.0);
        
        std::cout << "Interference at observation point: "
                  << "amplitude=" << std::abs(interference) 
                  << ", phase=" << std::arg(interference) << std::endl;
        
        // Обновление квантового состояния
        field.updateQuantumState(0.1);
        std::cout << "Updated quantum state" << std::endl;
        
        std::cout << "Demo completed successfully!" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
