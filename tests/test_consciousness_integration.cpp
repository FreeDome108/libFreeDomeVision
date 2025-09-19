#include "../src/consciousness_integration.hpp"
#include "../src/consciousness_hybrid.hpp"
#include <iostream>
#include <cassert>
#include <memory>

using namespace AnantaDigital::Integration;
using namespace AnantaDigital::Consciousness;

void test_initialization() {
    std::cout << "Testing ConsciousnessIntegration initialization..." << std::endl;
    ConsciousnessIntegration ci;
    assert(ci.initialize());
    ci.cleanup();
    std::cout << "ConsciousnessIntegration initialization test passed!" << std::endl;
}

void test_add_system() {
    std::cout << "Testing ConsciousnessIntegration add system..." << std::endl;
    ConsciousnessIntegration ci;
    ci.initialize();

    auto hybrid_system = std::make_unique<ConsciousnessHybrid>(0.5, 0.5);
    ci.addConsciousnessSystem(std::move(hybrid_system));

    // Not easy to assert addition directly, but we can check if integrated status changes
    assert(!ci.isIntegrated()); 

    ci.cleanup();
    std::cout << "ConsciousnessIntegration add system test passed!" << std::endl;
}

void test_synchronization_and_integration() {
    std::cout << "Testing ConsciousnessIntegration synchronization and integration..." << std::endl;
    ConsciousnessIntegration ci;
    ci.initialize();

    auto system1 = std::make_unique<ConsciousnessHybrid>(0.5, 0.5);
    auto system2 = std::make_unique<ConsciousnessHybrid>(0.6, 0.4);
    ci.addConsciousnessSystem(std::move(system1));
    ci.addConsciousnessSystem(std::move(system2));

    ci.synchronizeSystems();
    ci.createCollectiveConsciousness();

    assert(ci.isIntegrated());

    ci.cleanup();
    std::cout << "ConsciousnessIntegration synchronization and integration test passed!" << std::endl;
}

int main() {
    std::cout << "=== ConsciousnessIntegration Tests ===" << std::endl;

    try {
        test_initialization();
        test_add_system();
        test_synchronization_and_integration();

        std::cout << "All ConsciousnessIntegration tests passed successfully!" << std::endl;
        return 0;

    } catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Test failed with unknown exception" << std::endl;
        return 1;
    }
}
