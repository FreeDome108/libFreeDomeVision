#include "quantum_feedback_system.hpp"
#include <iostream>
#include <cmath>
#include <algorithm>

namespace AnantaDigital {

Feedback::QuantumFeedbackSystem::QuantumFeedbackSystem(std::chrono::microseconds nominal_delay, double sensitivity)
    : nominal_delay_(nominal_delay)
    , max_correction_window_(std::chrono::microseconds(100000))
    , feedback_sensitivity_(sensitivity)
    , quantum_uncertainty_threshold_(0.1)
    , sample_rate_(44100.0)
    , quantum_threshold_(0.7)
    , coherence_factor_(1.0)
    , entanglement_strength_(0.0)
    , quantum_state_(QuantumState::COHERENT)
    , feedback_buffer_()
    , quantum_oscillator_()
{
    feedback_buffer_.reserve(1024);
    quantum_oscillator_.reserve(256);
}

Feedback::QuantumFeedbackSystem::~QuantumFeedbackSystem() = default;

void Feedback::QuantumFeedbackSystem::processQuantumFeedback(const std::vector<double>& input_signal) {
    if (input_signal.empty()) return;
    
    // Analyze quantum coherence
    double coherence = calculateCoherence(input_signal);
    coherence_factor_ = std::clamp(coherence, 0.0, 1.0);
    
    // Update quantum state
    updateQuantumState();
    
    // Generate quantum feedback
    generateQuantumFeedback(input_signal);
    
    // Apply quantum corrections
    applyQuantumCorrections();
}

double Feedback::QuantumFeedbackSystem::calculateCoherence(const std::vector<double>& signal) {
    if (signal.size() < 2) return 1.0;
    
    double sum = 0.0;
    double sum_sq = 0.0;
    double cross_correlation = 0.0;
    
    for (size_t i = 0; i < signal.size(); ++i) {
        sum += signal[i];
        sum_sq += signal[i] * signal[i];
        
        if (i > 0) {
            cross_correlation += signal[i] * signal[i-1];
        }
    }
    
    double mean = sum / signal.size();
    double variance = (sum_sq / signal.size()) - (mean * mean);
    
    if (variance <= 0.0) return 1.0;
    
    double normalized_correlation = cross_correlation / (signal.size() - 1);
    double coherence = std::abs(normalized_correlation) / std::sqrt(variance);
    
    return std::clamp(coherence, 0.0, 1.0);
}

void Feedback::QuantumFeedbackSystem::updateQuantumState() {
    if (coherence_factor_ > quantum_threshold_) {
        if (quantum_state_ != QuantumState::COHERENT) {
            quantum_state_ = QuantumState::COHERENT;
            std::cout << "Quantum state: COHERENT (coherence: " << coherence_factor_ << ")" << std::endl;
        }
    } else if (coherence_factor_ > quantum_threshold_ * 0.5) {
        if (quantum_state_ != QuantumState::PARTIALLY_COHERENT) {
            quantum_state_ = QuantumState::PARTIALLY_COHERENT;
            std::cout << "Quantum state: PARTIALLY_COHERENT (coherence: " << coherence_factor_ << ")" << std::endl;
        }
    } else {
        if (quantum_state_ != QuantumState::INCOHERENT) {
            quantum_state_ = QuantumState::INCOHERENT;
            std::cout << "Quantum state: INCOHERENT (coherence: " << coherence_factor_ << ")" << std::endl;
        }
    }
}

void Feedback::QuantumFeedbackSystem::generateQuantumFeedback(const std::vector<double>& input_signal) {
    feedback_buffer_.clear();
    feedback_buffer_.reserve(input_signal.size());
    
    for (double sample : input_signal) {
        // Apply quantum feedback based on coherence
        double feedback_sample = sample;
        
        if (quantum_state_ == QuantumState::COHERENT) {
            // Enhance coherent signals
            feedback_sample *= (1.0 + coherence_factor_ * 0.1);
        } else if (quantum_state_ == QuantumState::PARTIALLY_COHERENT) {
            // Moderate enhancement
            feedback_sample *= (1.0 + coherence_factor_ * 0.05);
        } else {
            // Reduce incoherent signals
            feedback_sample *= (0.8 + coherence_factor_ * 0.2);
        }
        
        feedback_buffer_.push_back(feedback_sample);
    }
}

void Feedback::QuantumFeedbackSystem::applyQuantumCorrections() {
    if (feedback_buffer_.empty()) return;
    
    // Apply quantum corrections based on entanglement strength
    for (auto& sample : feedback_buffer_) {
        if (entanglement_strength_ > 0.5) {
            // Strong entanglement - enhance signal
            sample *= (1.0 + entanglement_strength_ * 0.2);
        } else {
            // Weak entanglement - moderate enhancement
            sample *= (1.0 + entanglement_strength_ * 0.1);
        }
    }
}

std::vector<double> Feedback::QuantumFeedbackSystem::getProcessedSignal() const {
    return feedback_buffer_;
}



std::vector<double> Feedback::QuantumFeedbackSystem::getProcessedSignal() const {
    return quantum_oscillator_.empty() ? feedback_buffer_ : quantum_oscillator_;
}

double Feedback::QuantumFeedbackSystem::getCoherenceFactor() const {
    return coherence_factor_;
}

Feedback::QuantumFeedbackSystem::QuantumState Feedback::QuantumFeedbackSystem::getQuantumState() const {
    return quantum_state_;
}

void Feedback::QuantumFeedbackSystem::setQuantumThreshold(double threshold) {
    quantum_threshold_ = std::clamp(threshold, 0.0, 1.0);
}

void Feedback::QuantumFeedbackSystem::setEntanglementStrength(double strength) {
    entanglement_strength_ = std::clamp(strength, 0.0, 1.0);
}

void Feedback::QuantumFeedbackSystem::reset() {
    coherence_factor_ = 1.0;
    entanglement_strength_ = 0.0;
    quantum_state_ = QuantumState::COHERENT;
    feedback_buffer_.clear();
    quantum_oscillator_.clear();
}

} // namespace AnantaDigital
