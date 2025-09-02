#include "anantadigital_core.hpp"
#include <iostream>
#include <cmath>
#include <algorithm>
#include <chrono>

namespace AnantaDigital {

AnantaDigitalCore::AnantaDigitalCore(double dome_radius, double dome_height)
    : dome_radius_(dome_radius)
    , dome_height_(dome_height)
    , quantum_uncertainty_(0.1)
    , is_initialized_(false)
    , quantum_feedback_system_(std::make_unique<Feedback::QuantumFeedbackSystem>(44100.0, 0.7))
    , consciousness_hybrid_(std::make_unique<ConsciousnessHybrid>(0.6, 0.8))
    , consciousness_integration_(std::make_unique<ConsciousnessIntegration>(0.7, 0.9))
    , dome_resonator_(std::make_unique<DomeAcousticResonator>(dome_radius, dome_height))
{
    processing_buffer_.reserve(2048);
    output_buffer_.reserve(2048);
    
    // Initialize dome resonator with default material properties
    std::map<double, double> material_properties = {
        {20.0, 0.1},    // 20 Hz - low frequency absorption
        {200.0, 0.3},   // 200 Hz - mid frequency absorption
        {2000.0, 0.5},  // 2 kHz - high frequency absorption
        {20000.0, 0.7}  // 20 kHz - very high frequency absorption
    };
    dome_resonator_->setMaterialProperties(material_properties);
}

AnantaDigitalCore::~AnantaDigitalCore() = default;

void AnantaDigitalCore::processAudioSignal(const std::vector<double>& input_signal) {
    if (input_signal.empty()) return;
    
    auto start_time = std::chrono::high_resolution_clock::now();
    
    // Clear processing buffers
    processing_buffer_.clear();
    output_buffer_.clear();
    
    // Step 1: Quantum feedback processing
    quantum_feedback_system_->processQuantumFeedback(input_signal);
    auto quantum_signal = quantum_feedback_system_->getProcessedSignal();
    
    // Step 2: Consciousness hybrid processing
    consciousness_hybrid_->processConsciousness(input_signal);
    auto hybrid_signal = consciousness_hybrid_->getProcessedSignal();
    
    // Step 3: Consciousness integration
    consciousness_integration_->processConsciousness(quantum_signal);
    auto integrated_signal = consciousness_integration_->getIntegratedOutput();
    
    // Step 4: Interference field processing
    processInterferenceField(integrated_signal);
    
    // Step 5: Dome resonance processing
    processDomeResonance();
    
    // Step 6: Final output generation
    generateOutput();
    
    auto end_time = std::chrono::high_resolution_clock::now();
    auto processing_time = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    
    std::cout << "Audio processing completed in " << processing_time.count() << " microseconds" << std::endl;
}

void AnantaDigitalCore::processInterferenceField(const std::vector<double>& input_signal) {
    if (input_signal.empty()) return;
    
    // Create quantum sound fields for interference processing
    std::vector<QuantumSoundField> fields;
    fields.reserve(input_signal.size());
    
    for (size_t i = 0; i < input_signal.size(); ++i) {
        QuantumSoundField field;
        field.amplitude = std::complex<double>(input_signal[i], 0.0);
        field.phase = 2.0 * M_PI * i / 44100.0;
        field.frequency = 20.0 + (20000.0 - 20.0) * i / input_signal.size();
        field.quantum_state = QuantumSoundState::COHERENT;
        field.position = {dome_radius_ * 0.5, M_PI/4, 2.0 * M_PI * i / input_signal.size(), dome_height_ * 0.5};
        field.timestamp = std::chrono::high_resolution_clock::now();
        
        fields.push_back(field);
    }
    
    // Add fields to interference system
    for (const auto& field : fields) {
        // Create interference field if needed
        if (interference_fields_.empty()) {
            interference_fields_.push_back(std::make_unique<InterferenceField>(
                InterferenceFieldType::CONSTRUCTIVE, 
                SphericalCoord{dome_radius_ * 0.5, M_PI/4, 0, dome_height_ * 0.5}, 
                dome_radius_ * 0.25
            ));
        }
        interference_fields_[0]->addSourceField(field);
    }
    
    // Process interference
    if (!interference_fields_.empty()) {
        interference_fields_[0]->updateQuantumState(1.0 / 44100.0);
    }
}

void AnantaDigitalCore::processDomeResonance() {
    // Calculate eigen frequencies for the dome
    auto eigen_frequencies = dome_resonator_->calculateEigenFrequencies();
    
    // Process resonance effects
    for (double freq : eigen_frequencies) {
        double reverb_time = dome_resonator_->calculateReverbTime(freq);
        
        // Apply resonance enhancement based on reverb time
        if (reverb_time > 0.5) {
            // Strong resonance - enhance signal
            for (auto& sample : processing_buffer_) {
                sample *= (1.0 + 0.1 * std::exp(-freq / 1000.0));
            }
        }
    }
}

void AnantaDigitalCore::generateOutput() {
    if (processing_buffer_.empty()) return;
    
    output_buffer_.clear();
    output_buffer_.reserve(processing_buffer_.size());
    
    // Apply final processing and normalization
    double max_amplitude = 0.0;
    for (double sample : processing_buffer_) {
        max_amplitude = std::max(max_amplitude, std::abs(sample));
    }
    
    if (max_amplitude > 0.0) {
        double normalization_factor = 0.95 / max_amplitude;
        for (double sample : processing_buffer_) {
            output_buffer_.push_back(sample * normalization_factor);
        }
    } else {
        output_buffer_ = processing_buffer_;
    }
}

std::vector<double> AnantaDigitalCore::getProcessedSignal() const {
    return output_buffer_;
}

std::string AnantaDigitalCore::getVersion() const {
    return "2.1.0";
}

double AnantaDigitalCore::getSampleRate() const {
    return sample_rate_;
}

double AnantaDigitalCore::getDomeRadius() const {
    return dome_radius_;
}

double AnantaDigitalCore::getDomeHeight() const {
    return dome_height_;
}

void AnantaDigitalCore::setSampleRate(double sample_rate) {
    sample_rate_ = sample_rate;
    quantum_feedback_system_ = QuantumFeedbackSystem(sample_rate, 0.7);
}

void AnantaDigitalCore::setDomeDimensions(double radius, double height) {
    dome_radius_ = radius;
    dome_height_ = height;
    interference_field_ = InterferenceField(InterferenceFieldType::CONSTRUCTIVE, 
                                          {radius/2, M_PI/4, 0, height/2}, radius/4);
    dome_resonator_ = DomeAcousticResonator(radius, height);
}

void AnantaDigitalCore::reset() {
    processing_buffer_.clear();
    output_buffer_.clear();
    quantum_feedback_system_.reset();
    consciousness_hybrid_.reset();
    consciousness_integration_.reset();
}

// Static factory method
std::unique_ptr<AnantaDigitalCore> AnantaDigitalCore::create(double sample_rate, double dome_radius, double dome_height) {
    return std::make_unique<AnantaDigitalCore>(sample_rate, dome_radius, dome_height);
}

} // namespace AnantaDigital
