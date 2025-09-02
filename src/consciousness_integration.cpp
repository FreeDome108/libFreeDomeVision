#include "consciousness_integration.hpp"
#include <iostream>
#include <cmath>
#include <algorithm>

namespace AnantaDigital {

ConsciousnessIntegration::ConsciousnessIntegration(double karmic_weight, double mercy_capacity)
    : karmic_weight_(karmic_weight)
    , mercy_capacity_(mercy_capacity)
    , initialized_(false)
    , integration_buffer_()
    , coherence_buffer_()
    , integrated_signal_()
    , integration_level_(0.0)
    , coherence_factor_(0.0)
{
    integration_buffer_.reserve(1024);
    coherence_buffer_.reserve(1024);
    integrated_signal_.reserve(1024);
}



void ConsciousnessIntegration::processConsciousness(const std::vector<double>& input_signal) {
    if (input_signal.empty()) return;
    
    // Calculate integration level
    integration_level_ = calculateIntegrationLevel(input_signal, input_signal);
    
    // Calculate coherence factor
    coherence_factor_ = calculateCoherenceFactor(input_signal, input_signal);
    
    // Process integration
    processIntegration(input_signal, input_signal);
    
    // Apply coherence integration
    applyCoherenceIntegration();
}

std::vector<double> ConsciousnessIntegration::getIntegratedOutput() const {
    return integrated_signal_;
}

void ConsciousnessIntegration::processIntegration(const std::vector<double>& quantum_signal,
                                               const std::vector<double>& hybrid_signal) {
    if (quantum_signal.empty() || hybrid_signal.empty()) return;
    
    integrated_signal_.clear();
    integrated_signal_.reserve(std::min(quantum_signal.size(), hybrid_signal.size()));
    
    size_t min_size = std::min(quantum_signal.size(), hybrid_signal.size());
    for (size_t i = 0; i < min_size; ++i) {
        double integrated_sample = (quantum_signal[i] * karmic_weight_ + 
                                  hybrid_signal[i] * mercy_capacity_) / 2.0;
        integrated_signal_.push_back(integrated_sample);
    }
}

void ConsciousnessIntegration::applyCoherenceIntegration() {
    if (integrated_signal_.empty()) return;
    
    // Apply coherence-based integration
    for (auto& sample : integrated_signal_) {
        sample *= (1.0 + coherence_factor_ * 0.1);
    }
}

double ConsciousnessIntegration::calculateIntegrationLevel(const std::vector<double>& signal1,
                                                        const std::vector<double>& signal2) {
    if (signal1.size() != signal2.size() || signal1.empty()) return 0.0;
    
    double correlation = 0.0;
    double sum1 = 0.0, sum2 = 0.0;
    double sum1_sq = 0.0, sum2_sq = 0.0;
    double sum_product = 0.0;
    
    for (size_t i = 0; i < signal1.size(); ++i) {
        sum1 += signal1[i];
        sum2 += signal2[i];
        sum1_sq += signal1[i] * signal1[i];
        sum2_sq += signal2[i] * signal2[i];
        sum_product += signal1[i] * signal2[i];
    }
    
    double n = static_cast<double>(signal1.size());
    double mean1 = sum1 / n;
    double mean2 = sum2 / n;
    
    double var1 = (sum1_sq / n) - (mean1 * mean1);
    double var2 = (sum2_sq / n) - (mean2 * mean2);
    
    if (var1 <= 0.0 || var2 <= 0.0) return 0.0;
    
    double covariance = (sum_product / n) - (mean1 * mean2);
    double correlation_coeff = covariance / std::sqrt(var1 * var2);
    
    return std::clamp((correlation_coeff + 1.0) / 2.0, 0.0, 1.0);
}

double ConsciousnessIntegration::calculateCoherenceFactor(const std::vector<double>& signal1,
                                                        const std::vector<double>& signal2) {
    if (signal1.size() != signal2.size() || signal1.empty()) return 0.0;
    
    double phase_coherence = 0.0;
    double amplitude_coherence = 0.0;
    
    for (size_t i = 1; i < signal1.size(); ++i) {
        // Phase coherence
        double phase1 = std::atan2(signal1[i], signal1[i-1]);
        double phase2 = std::atan2(signal2[i], signal2[i-1]);
        double phase_diff = std::abs(phase1 - phase2);
        
        if (phase_diff > M_PI) {
            phase_diff = 2.0 * M_PI - phase_diff;
        }
        
        phase_coherence += (M_PI - phase_diff) / M_PI;
        
        // Amplitude coherence
        double amp1 = std::abs(signal1[i] - signal1[i-1]);
        double amp2 = std::abs(signal2[i] - signal2[i-1]);
        
        if (amp1 > 0.0 && amp2 > 0.0) {
            double amp_ratio = std::min(amp1, amp2) / std::max(amp1, amp2);
            amplitude_coherence += amp_ratio;
        }
    }
    
    phase_coherence /= (signal1.size() - 1);
    amplitude_coherence /= (signal1.size() - 1);
    
    return (phase_coherence * 0.6) + (amplitude_coherence * 0.4);
}



double ConsciousnessIntegration::getKarmicWeight() const {
    return karmic_weight_;
}

double ConsciousnessIntegration::getMercyCapacity() const {
    return mercy_capacity_;
}

void ConsciousnessIntegration::setKarmicWeight(double weight) {
    karmic_weight_ = std::clamp(weight, 0.0, 1.0);
}

void ConsciousnessIntegration::setMercyCapacity(double capacity) {
    mercy_capacity_ = std::clamp(capacity, 0.0, 1.0);
}

void ConsciousnessIntegration::initialize() {
    initialized_ = true;
}

void ConsciousnessIntegration::shutdown() {
    initialized_ = false;
}

} // namespace AnantaDigital
