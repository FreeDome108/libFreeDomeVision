#include <iostream>
#include <cassert>
#include <cmath>
#include "../src/anantadigital_core.hpp"

using namespace AnantaDigital;

void test_dome_resonator() {
    std::cout << "Testing DomeAcousticResonator..." << std::endl;
    
    DomeAcousticResonator resonator(5.0, 3.0);
    
    // Test basic properties
    assert(resonator.getRadius() == 5.0);
    assert(resonator.getHeight() == 3.0);
    
    // Test eigen frequencies
    auto eigen_freqs = resonator.calculateEigenFrequencies();
    assert(!eigen_freqs.empty());
    
    // Test acoustic properties
    resonator.setAcousticProperty(100.0, 0.8);
    assert(std::abs(resonator.getAcousticProperty(100.0) - 0.8) < 1e-6);
    
    std::cout << "DomeAcousticResonator tests passed!" << std::endl;
}

void test_interference_field() {
    std::cout << "Testing InterferenceField..." << std::endl;
    
    SphericalCoord center{2.0, M_PI/2, 0.0, 1.0};
    InterferenceField field(InterferenceFieldType::CONSTRUCTIVE, center, 2.0);
    
    // Test basic properties
    assert(field.getType() == InterferenceFieldType::CONSTRUCTIVE);
    assert(field.getCenter().r == 2.0);
    assert(field.getRadius() == 2.0);
    
    // Test adding source field
    QuantumSoundField source;
    source.amplitude = std::complex<double>(1.0, 0.0);
    source.frequency = 440.0;
    source.position = {1.0, M_PI/4, 0.0, 0.5};
    source.quantum_state = QuantumSoundState::COHERENT;
    
    field.addSourceField(source);
    
    // Test interference calculation
    SphericalCoord obs_point{3.0, M_PI/3, M_PI/4, 1.5};
    auto interference = field.calculateInterference(obs_point, 0.0);
    
    // Should have some interference (not zero)
    assert(std::abs(interference) > 0.0);
    
    std::cout << "InterferenceField tests passed!" << std::endl;
}

void test_quantum_sound_field() {
    std::cout << "Testing QuantumSoundField..." << std::endl;
    
    QuantumSoundField field;
    field.amplitude = std::complex<double>(2.0, 1.0);
    field.frequency = 880.0;
    field.phase = M_PI/4;
    field.position = {1.0, M_PI/2, M_PI, 0.5};
    field.quantum_state = QuantumSoundState::SUPERPOSITION;
    
    // Test properties
    assert(std::abs(field.amplitude.real() - 2.0) < 1e-6);
    assert(std::abs(field.amplitude.imag() - 1.0) < 1e-6);
    assert(std::abs(field.frequency - 880.0) < 1e-6);
    assert(std::abs(field.phase - M_PI/4) < 1e-6);
    assert(field.quantum_state == QuantumSoundState::SUPERPOSITION);
    
    std::cout << "QuantumSoundField tests passed!" << std::endl;
}

int main() {
    std::cout << "=== anAntaDigital Core Tests ===" << std::endl;
    
    try {
        test_dome_resonator();
        test_interference_field();
        test_quantum_sound_field();
        
        std::cout << "All tests passed successfully!" << std::endl;
        return 0;
        
    } catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Test failed with unknown exception" << std::endl;
        return 1;
    }
}
