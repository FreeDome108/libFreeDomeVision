#include "anantadigital_core.hpp"
#include "quantum_feedback_system.hpp"
#include <iostream>

int main() {
    std::cout << "=== anAntaDigital Demo ===" << std::endl;
    
    try {
        // Initialize core system
        AnantaDigital::AnantaDigitalCore core(10.0, 5.0);
        std::cout << "Core system initialized successfully" << std::endl;
        
        // Initialize quantum feedback system
        AnantaDigital::Feedback::QuantumFeedbackSystem qfs(std::chrono::microseconds(50000), 0.7);
        std::cout << "Quantum feedback system initialized" << std::endl;
        
        // Demonstrate basic functionality
        bool init_result = core.initialize();
        std::cout << "System status: " << (init_result ? "OK" : "ERROR") << std::endl;
        
        // Cleanup
        core.shutdown();
        std::cout << "Demo completed successfully" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
