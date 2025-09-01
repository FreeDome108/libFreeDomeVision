#include "consciousness_hybrid.hpp"
#include <cassert>
#include <iostream>

void test_consciousness_hybrid() {
    std::cout << "Testing consciousness hybrid system..." << std::endl;
    
    anantadigital::ConsciousnessHybrid ch;
    assert(!ch.isActive());
    
    ch.activate();
    assert(ch.isActive());
    
    ch.deactivate();
    assert(!ch.isActive());
    
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
