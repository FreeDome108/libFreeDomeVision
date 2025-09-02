#include "quantum_feedback_system.hpp"
#include <iostream>
#include <thread>
#include <chrono>

int main() {
    std::cout << "=== Quantum Acoustic Demo ===" << std::endl;
    
    try {
        AnantaDigital::Feedback::QuantumFeedbackSystem qfs(std::chrono::microseconds(50000), 0.7);
        std::cout << "Quantum feedback system initialized" << std::endl;
        
        // Simulate quantum acoustic processing
        qfs.initialize();
        std::cout << "Processing quantum acoustic signals..." << std::endl;
        
        // Simulate some processing time
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        
        std::cout << "Quantum acoustic processing completed" << std::endl;
        qfs.shutdown();
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
