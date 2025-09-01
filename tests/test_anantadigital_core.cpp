#include "anantadigital_core.hpp"
#include <cassert>
#include <iostream>

void test_core_initialization() {
    std::cout << "Testing core initialization..." << std::endl;
    
    anantadigital::Core core;
    assert(!core.isInitialized());
    
    core.initialize();
    assert(core.isInitialized());
    
    core.shutdown();
    assert(!core.isInitialized());
    
    std::cout << "Core initialization tests passed" << std::endl;
}

void test_core_version() {
    std::cout << "Testing core version..." << std::endl;
    
    anantadigital::Core core;
    std::string version = core.getVersion();
    assert(!version.empty());
    
    std::cout << "Core version: " << version << std::endl;
    std::cout << "Core version tests passed" << std::endl;
}

int main() {
    std::cout << "Running anAntaDigital Core tests..." << std::endl;
    
    try {
        test_core_initialization();
        test_core_version();
        
        std::cout << "All core tests passed!" << std::endl;
        return 0;
        
    } catch (const std::exception& e) {
        std::cerr << "Test failed: " << e.what() << std::endl;
        return 1;
    }
}
