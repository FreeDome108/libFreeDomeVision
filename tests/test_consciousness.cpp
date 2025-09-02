#include "consciousness_hybrid.hpp"
#include <cassert>
#include <iostream>

void test_consciousness_hybrid() {
    std::cout << "Testing consciousness hybrid system..." << std::endl;
    
    AnantaDigital::ConsciousnessHybrid ch(0.6, 0.8);
    
    // Test consciousness processing
    std::vector<double> test_signal = {0.5, 0.7, 0.3, 0.9};
    ch.processConsciousness(test_signal);
    
    auto processed_signal = ch.getProcessedSignal();
    assert(!processed_signal.empty());
    
    std::cout << "Consciousness hybrid tests passed" << std::endl;
}

int main() {
    std::cout << "Running Consciousness tests..." << std::endl;
    
    try {
        test_consciousness_hybrid();
        
        std::cout << "All consciousness tests passed!" << std::endl;
        return 0;
        
    } catch (const std::exception& e) {
        std::cerr << "Test failed: " << e.what() << std::endl;
        return 1;
    }
}
