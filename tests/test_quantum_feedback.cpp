#include "quantum_feedback_system.hpp"
#include <cassert>
#include <iostream>

void test_quantum_feedback_initialization() {
    std::cout << "Testing quantum feedback initialization..." << std::endl;
    
    anantadigital::QuantumFeedbackSystem qfs;
    assert(!qfs.isInitialized());
    
    qfs.initialize();
    assert(qfs.isInitialized());
    
    qfs.shutdown();
    assert(!qfs.isInitialized());
    
    std::cout << "Quantum feedback initialization tests passed" << std::endl;
}

void test_quantum_feedback_processing() {
    std::cout << "Testing quantum feedback processing..." << std::endl;
    
    anantadigital::QuantumFeedbackSystem qfs;
    qfs.initialize();
    
    // Test basic processing
    bool result = qfs.processQuantumSignal(1.0);
    assert(result);
    
    qfs.shutdown();
    std::cout << "Quantum feedback processing tests passed" << std::endl;
}

int main() {
    std::cout << "Running Quantum Feedback tests..." << std::endl;
    
    try {
        test_quantum_feedback_initialization();
        test_quantum_feedback_processing();
        
        std::cout << "All quantum feedback tests passed!" << std::endl;
        return 0;
        
    } catch (const std::exception& e) {
        std::cerr << "Test failed: " << e.what() << std::endl;
        return 1;
    }
}
