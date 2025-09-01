#include "quantum_feedback_system.hpp"
#include <iostream>
#include <cmath>
#include <algorithm>

namespace AnantaDigital {

QuantumFeedbackSystem::QuantumFeedbackSystem(double sample_rate, double quantum_threshold)
    : sample_rate_(sample_rate)
    , quantum_threshold_(quantum_threshold)
    , coherence_factor_(1.0)
    , entanglement_strength_(0.0)
    , quantum_state_(QuantumState::COHERENT)
    , feedback_buffer_()
    , quantum_oscillator_()
{
    feedback_buffer_.reserve(1024);
    quantum_oscillator_.reserve(256);
}

QuantumFeedbackSystem::~QuantumFeedbackSystem() = default;

void QuantumFeedbackSystem::processQuantumFeedback(const std::vector<double>& input_signal) {
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

double QuantumFeedbackSystem::calculateCoherence(const std::vector<double>& signal) {
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

void QuantumFeedbackSystem::updateQuantumState() {
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

void QuantumFeedbackSystem::generateQuantumFeedback(const std::vector<double>& input_signal) {
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

void QuantumFeedbackSystem::applyQuantumCorrections() {
    if (feedback_buffer_.empty()) return;
    
    // Apply quantum oscillator corrections
    quantum_oscillator_.clear();
    quantum_oscillator_.reserve(feedback_buffer_.size());
    
    for (size_t i = 0; i < feedback_buffer_.size(); ++i) {
        double corrected_sample = feedback_buffer_[i];
        
        // Apply quantum oscillator effects
        double oscillator_phase = 2.0 * M_PI * i / sample_rate_;
        double oscillator_correction = std::sin(oscillator_phase * coherence_factor_);
        
        corrected_sample += oscillator_correction * 0.01 * entanglement_strength_;
        
        quantum_oscillator_.push_back(corrected_sample);
    }
}

std::vector<double> QuantumFeedbackSystem::getProcessedSignal() const {
    return quantum_oscillator_.empty() ? feedback_buffer_ : quantum_oscillator_;
}

double QuantumFeedbackSystem::getCoherenceFactor() const {
    return coherence_factor_;
}

QuantumFeedbackSystem::QuantumState QuantumFeedbackSystem::getQuantumState() const {
    return quantum_state_;
}

void QuantumFeedbackSystem::setQuantumThreshold(double threshold) {
    quantum_threshold_ = std::clamp(threshold, 0.0, 1.0);
}

void QuantumFeedbackSystem::setEntanglementStrength(double strength) {
    entanglement_strength_ = std::clamp(strength, 0.0, 1.0);
}

void QuantumFeedbackSystem::reset() {
    coherence_factor_ = 1.0;
    entanglement_strength_ = 0.0;
    quantum_state_ = QuantumState::COHERENT;
    feedback_buffer_.clear();
    quantum_oscillator_.clear();
}

} // namespace AnantaDigital
