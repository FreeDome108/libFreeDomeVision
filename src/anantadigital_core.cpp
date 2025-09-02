#include "anantadigital_core.hpp"
#include <iostream>

namespace AnantaDigital {





// AnantaDigitalCore implementation
AnantaDigitalCore::AnantaDigitalCore(double radius, double height)
    : dome_radius_(radius)
    , dome_height_(height)
    , quantum_uncertainty_(0.1)
    , is_initialized_(false)
    , quantum_feedback_system_(std::make_unique<Feedback::QuantumFeedbackSystem>(std::chrono::microseconds(50000), 0.7))
    , consciousness_hybrid_(nullptr)
    , consciousness_integration_(nullptr)
    , dome_resonator_(std::make_unique<DomeAcousticResonator>(radius, height)) {
}

AnantaDigitalCore::~AnantaDigitalCore() = default;

bool AnantaDigitalCore::initialize() {
    if (is_initialized_) return true;
    
    // Initialize quantum feedback system
    quantum_feedback_system_->initialize();
    
    // Initialize consciousness systems (simplified)
    // consciousness_hybrid_->initialize();
    // consciousness_integration_->initialize();
    
    // Initialize dome resonator
    std::map<double, double> material_properties = {
        {20.0, 0.1},    // 20 Hz - low frequency absorption
        {200.0, 0.3},   // 200 Hz - bass absorption
        {2000.0, 0.5},  // 2 kHz - mid frequency absorption
        {20000.0, 0.7}  // 20 kHz - very high frequency absorption
    };
    dome_resonator_->setMaterialProperties(material_properties);
    
    is_initialized_ = true;
    std::cout << "AnantaDigitalCore initialized successfully" << std::endl;
    
    return true;
}

void AnantaDigitalCore::shutdown() {
    if (!is_initialized_) return;
    
    // Shutdown quantum feedback system
    quantum_feedback_system_->shutdown();
    
    // Shutdown consciousness systems (simplified)
    // consciousness_hybrid_->shutdown();
    // consciousness_integration_->shutdown();
    
    is_initialized_ = false;
    std::cout << "AnantaDigitalCore shutdown completed" << std::endl;
}

bool AnantaDigitalCore::isInitialized() const {
    return is_initialized_;
}

std::vector<double> AnantaDigitalCore::getProcessedSignal() const {
    return output_buffer_;
}

std::string AnantaDigitalCore::getVersion() const {
    return "2.1.0";
}

} // namespace AnantaDigital
