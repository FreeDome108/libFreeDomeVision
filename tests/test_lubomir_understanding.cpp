#include "../src/lubomir_understanding.hpp"
#include <iostream>
#include <cassert>
#include <cmath>
#include <string>

using namespace AnantaDigital::Lubomir;

void test_initialization() {
    std::cout << "Testing LubomirUnderstanding initialization..." << std::endl;
    LubomirUnderstanding lu;
    assert(lu.initialize());
    lu.cleanup();
    std::cout << "LubomirUnderstanding initialization test passed!" << std::endl;
}

void test_concept_management() {
    std::cout << "Testing LubomirUnderstanding concept management..." << std::endl;
    LubomirUnderstanding lu;
    lu.initialize();

    std::string concept = "test_concept";
    double initial_weight = 0.5;
    lu.addConcept(concept, initial_weight);
    assert(std::abs(lu.getConceptWeight(concept) - initial_weight) < 1e-6);

    double updated_weight = 0.8;
    lu.updateConceptWeight(concept, updated_weight);
    assert(std::abs(lu.getConceptWeight(concept) - updated_weight) < 1e-6);
    
    lu.cleanup();
    std::cout << "LubomirUnderstanding concept management test passed!" << std::endl;
}

void test_understanding_processing() {
    std::cout << "Testing LubomirUnderstanding processing..." << std::endl;
    LubomirUnderstanding lu;
    lu.initialize();
    lu.addConcept("test");
    lu.addConcept("input");

    std::string input = "This is a test input for processing.";
    Understanding result = lu.processUnderstanding(input);

    assert(result.confidence > 0.0);
    assert(!result.insight.empty());
    assert(!result.related_concepts.empty());
    assert(result.level >= UnderstandingLevel::SURFACE);

    lu.cleanup();
    std::cout << "LubomirUnderstanding processing test passed!" << std::endl;
}


int main() {
    std::cout << "=== LubomirUnderstanding Tests ===" << std::endl;

    try {
        test_initialization();
        test_concept_management();
        test_understanding_processing();

        std::cout << "All LubomirUnderstanding tests passed successfully!" << std::endl;
        return 0;

    } catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Test failed with unknown exception" << std::endl;
        return 1;
    }
}
