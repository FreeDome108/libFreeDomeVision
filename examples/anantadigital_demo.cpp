#include "anantadigital_core.hpp"
#include "quantum_feedback_system.hpp"
#include <iostream>

int main() {
    std::cout << "=== anAntaDigital Demo ===" << std::endl;
    
    try {
        // Initialize core system
        anantadigital::Core core;
        std::cout << "Core system initialized successfully" << std::endl;
        
        // Initialize quantum feedback system
        anantadigital::QuantumFeedbackSystem qfs;
        std::cout << "Quantum feedback system initialized" << std::endl;
        
        // Demonstrate basic functionality
        core.initialize();
        std::cout << "System status: " << (core.isInitialized() ? "OK" : "ERROR") << std::endl;
        
        // Cleanup
        core.shutdown();
        std::cout << "Demo completed successfully" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
