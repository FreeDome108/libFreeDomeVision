#include "consciousness_integration.hpp"
#include <iostream>
#include <cmath>
#include <algorithm>

namespace AnantaDigital {

ConsciousnessIntegration::ConsciousnessIntegration(double integration_threshold, double coherence_weight)
    : integration_threshold_(integration_threshold)
    , coherence_weight_(coherence_weight)
    , integration_level_(0.0)
    , coherence_factor_(0.0)
    , integration_buffer_()
    , coherence_buffer_()
    , integrated_signal_()
{
    integration_buffer_.reserve(1024);
    coherence_buffer_.reserve(1024);
    integrated_signal_.reserve(1024);
}

ConsciousnessIntegration::~ConsciousnessIntegration() = default;

void ConsciousnessIntegration::integrateConsciousness(const std::vector<double>& quantum_signal,
                                                   const std::vector<double>& hybrid_signal) {
    if (quantum_signal.empty() || hybrid_signal.empty()) return;
    
    // Calculate integration level
    integration_level_ = calculateIntegrationLevel(quantum_signal, hybrid_signal);
    
    // Calculate coherence factor
    coherence_factor_ = calculateCoherenceFactor(quantum_signal, hybrid_signal);
    
    // Process integration
    processIntegration(quantum_signal, hybrid_signal);
    
    // Apply coherence integration
    applyCoherenceIntegration();
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

void ConsciousnessIntegration::processIntegration(const std::vector<double>& quantum_signal,
                                                const std::vector<double>& hybrid_signal) {
    integration_buffer_.clear();
    integration_buffer_.reserve(quantum_signal.size());
    
    for (size_t i = 0; i < quantum_signal.size(); ++i) {
        // Weighted integration based on integration level
        double integrated_sample = (quantum_signal[i] * integration_level_) + 
                                 (hybrid_signal[i] * (1.0 - integration_level_));
        
        // Apply integration enhancement
        if (integration_level_ > integration_threshold_) {
            integrated_sample *= (1.0 + integration_level_ * 0.15);
        }
        
        integration_buffer_.push_back(integrated_sample);
    }
}

void ConsciousnessIntegration::applyCoherenceIntegration() {
    if (integration_buffer_.empty()) return;
    
    coherence_buffer_.clear();
    coherence_buffer_.reserve(integration_buffer_.size());
    
    for (size_t i = 0; i < integration_buffer_.size(); ++i) {
        double coherent_sample = integration_buffer_[i];
        
        // Apply coherence-based enhancement
        if (coherence_factor_ > 0.7) {
            // High coherence - enhance signal
            coherent_sample *= (1.0 + coherence_factor_ * 0.2);
            
            // Add coherence resonance
            double resonance = std::sin(2.0 * M_PI * i * coherence_factor_ / 50.0);
            coherent_sample += resonance * 0.05 * coherence_weight_;
        } else if (coherence_factor_ > 0.3) {
            // Medium coherence - moderate enhancement
            coherent_sample *= (1.0 + coherence_factor_ * 0.1);
        } else {
            // Low coherence - minimal enhancement
            coherent_sample *= (0.95 + coherence_factor_ * 0.05);
        }
        
        coherence_buffer_.push_back(coherent_sample);
    }
    
    // Final integration
    integrated_signal_.clear();
    integrated_signal_.reserve(coherence_buffer_.size());
    
    for (size_t i = 0; i < coherence_buffer_.size(); ++i) {
        double final_sample = coherence_buffer_[i];
        
        // Apply final integration effects
        if (integration_level_ > 0.8 && coherence_factor_ > 0.8) {
            // High integration and coherence - quantum consciousness effects
            double quantum_effect = std::cos(integration_level_ * M_PI * i / 100.0);
            final_sample += quantum_effect * 0.03 * coherence_weight_;
        }
        
        integrated_signal_.push_back(final_sample);
    }
}

std::vector<double> ConsciousnessIntegration::getIntegratedSignal() const {
    return integrated_signal_.empty() ? coherence_buffer_ : integrated_signal_;
}

double ConsciousnessIntegration::getIntegrationLevel() const {
    return integration_level_;
}

double ConsciousnessIntegration::getCoherenceFactor() const {
    return coherence_factor_;
}

void ConsciousnessIntegration::setIntegrationThreshold(double threshold) {
    integration_threshold_ = std::clamp(threshold, 0.0, 1.0);
}

void ConsciousnessIntegration::setCoherenceWeight(double weight) {
    coherence_weight_ = std::clamp(weight, 0.0, 1.0);
}

void ConsciousnessIntegration::reset() {
    integration_level_ = 0.0;
    coherence_factor_ = 0.0;
    integration_buffer_.clear();
    coherence_buffer_.clear();
    integrated_signal_.clear();
}

} // namespace AnantaDigital
