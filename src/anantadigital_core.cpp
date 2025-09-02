#include "anantadigital_core.hpp"
#include <cmath>
#include <algorithm>
#include <stdexcept>
#include <iostream>

namespace AnantaDigital {

// InterferenceField implementation
InterferenceField::InterferenceField(InterferenceFieldType type, SphericalCoord center, double radius)
    : type_(type), center_position_(center), field_radius_(radius) {
}

void InterferenceField::addSourceField(const QuantumSoundField& field) {
    std::lock_guard<std::mutex> lock(field_mutex_);
    source_fields_.push_back(field);
}

std::complex<double> InterferenceField::calculateInterference(const SphericalCoord& position, double time) const {
    std::lock_guard<std::mutex> lock(field_mutex_);
    
    if (source_fields_.empty()) {
        return std::complex<double>(0.0, 0.0);
    }
    
    std::complex<double> total_field(0.0, 0.0);
    
    for (const auto& source : source_fields_) {
        // Calculate distance from source to position
        double dx = position.r * sin(position.theta) * cos(position.phi) - 
                   source.position.r * sin(source.position.theta) * cos(source.position.phi);
        double dy = position.r * sin(position.theta) * sin(position.phi) - 
                   source.position.r * sin(source.position.theta) * sin(source.position.phi);
        double dz = position.r * cos(position.theta) - 
                   source.position.r * cos(source.position.theta);
        
        double distance = std::sqrt(dx*dx + dy*dy + dz*dz);
        
        // Calculate phase delay
        double phase_delay = 2.0 * M_PI * source.frequency * distance / 343.0; // 343 m/s speed of sound
        
        // Add contribution from this source
        total_field += source.amplitude * std::exp(std::complex<double>(0.0, -phase_delay));
    }
    
    return total_field;
}

QuantumSoundField InterferenceField::quantumSuperposition(const std::vector<QuantumSoundField>& fields) const {
    if (fields.empty()) {
        throw std::runtime_error("Cannot create superposition of empty field set");
    }
    
    QuantumSoundField result = fields[0];
    result.quantum_state = QuantumSoundState::SUPERPOSITION;
    
    // Simple superposition - average of all fields
    std::complex<double> avg_amplitude(0.0, 0.0);
    double avg_frequency = 0.0;
    
    for (const auto& field : fields) {
        avg_amplitude += field.amplitude;
        avg_frequency += field.frequency;
    }
    
    result.amplitude = avg_amplitude / static_cast<double>(fields.size());
    result.frequency = avg_frequency / static_cast<double>(fields.size());
    
    return result;
}

void InterferenceField::updateQuantumState(double dt) {
    std::lock_guard<std::mutex> lock(field_mutex_);
    
    for (auto& field : source_fields_) {
        // Simulate quantum decoherence
        if (field.quantum_state == QuantumSoundState::COHERENT) {
            // Random chance of state change
            if (static_cast<double>(rand()) / RAND_MAX < 0.01 * dt) {
                field.quantum_state = QuantumSoundState::SUPERPOSITION;
            }
        }
    }
}

void InterferenceField::createQuantumEntanglement(size_t field1_idx, size_t field2_idx) {
    std::lock_guard<std::mutex> lock(field_mutex_);
    
    if (field1_idx >= source_fields_.size() || field2_idx >= source_fields_.size()) {
        throw std::out_of_range("Field index out of range");
    }
    
    source_fields_[field1_idx].quantum_state = QuantumSoundState::ENTANGLED;
    source_fields_[field2_idx].quantum_state = QuantumSoundState::ENTANGLED;
}

// DomeAcousticResonator implementation
DomeAcousticResonator::DomeAcousticResonator(double radius, double height)
    : dome_radius_(radius), dome_height_(height) {
    
    // Initialize with some basic resonant frequencies
    resonant_frequencies_ = {50.0, 100.0, 200.0, 400.0, 800.0, 1600.0};
    
    // Initialize acoustic properties
    acoustic_properties_[50.0] = 0.8;
    acoustic_properties_[100.0] = 0.9;
    acoustic_properties_[200.0] = 0.95;
    acoustic_properties_[400.0] = 0.9;
    acoustic_properties_[800.0] = 0.85;
    acoustic_properties_[1600.0] = 0.7;
}

std::vector<double> DomeAcousticResonator::calculateEigenFrequencies() const {
    std::vector<double> eigen_freqs;
    
    // Calculate eigenfrequencies based on dome geometry
    // Using simplified spherical harmonics model
    for (int n = 1; n <= 6; ++n) {
        for (int m = 0; m <= n; ++m) {
            double freq = 343.0 * std::sqrt(n * (n + 1)) / (2.0 * M_PI * dome_radius_);
            eigen_freqs.push_back(freq);
        }
    }
    
    // Sort and remove duplicates
    std::sort(eigen_freqs.begin(), eigen_freqs.end());
    eigen_freqs.erase(std::unique(eigen_freqs.begin(), eigen_freqs.end()), eigen_freqs.end());
    
    return eigen_freqs;
}





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
