#include "consciousness_hybrid.hpp"
#include <iostream>
#include <cmath>
#include <algorithm>
#include <random>

namespace AnantaDigital {

ConsciousnessHybrid::ConsciousnessHybrid(double consciousness_threshold, double hybrid_factor)
    : consciousness_threshold_(consciousness_threshold)
    , hybrid_factor_(hybrid_factor)
    , consciousness_level_(0.0)
    , hybrid_state_(HybridState::UNCONSCIOUS)
    , consciousness_buffer_()
    , hybrid_processor_()
    , random_generator_(std::random_device{}())
{
    consciousness_buffer_.reserve(512);
    hybrid_processor_.reserve(256);
}

ConsciousnessHybrid::~ConsciousnessHybrid() = default;

void ConsciousnessHybrid::processConsciousness(const std::vector<double>& input_signal) {
    if (input_signal.empty()) return;
    
    // Analyze consciousness level
    consciousness_level_ = calculateConsciousnessLevel(input_signal);
    
    // Update hybrid state
    updateHybridState();
    
    // Process consciousness
    processConsciousnessSignal(input_signal);
    
    // Apply hybrid processing
    applyHybridProcessing();
}

double ConsciousnessHybrid::calculateConsciousnessLevel(const std::vector<double>& signal) {
    if (signal.size() < 10) return 0.0;
    
    // Calculate complexity as a measure of consciousness
    double complexity = 0.0;
    double entropy = 0.0;
    
    // Frequency domain analysis
    std::vector<double> frequencies;
    frequencies.reserve(signal.size() / 2);
    
    for (size_t i = 1; i < signal.size(); ++i) {
        double freq = std::abs(signal[i] - signal[i-1]);
        frequencies.push_back(freq);
    }
    
    // Calculate entropy
    std::sort(frequencies.begin(), frequencies.end());
    for (size_t i = 0; i < frequencies.size(); ++i) {
        if (frequencies[i] > 0.0) {
            double p = static_cast<double>(i + 1) / frequencies.size();
            entropy -= p * std::log2(p);
        }
    }
    
    // Calculate complexity based on entropy and signal variation
    double variation = 0.0;
    for (size_t i = 1; i < signal.size(); ++i) {
        variation += std::abs(signal[i] - signal[i-1]);
    }
    variation /= signal.size();
    
    complexity = (entropy * 0.7) + (variation * 0.3);
    
    return std::clamp(complexity / 10.0, 0.0, 1.0);
}

void ConsciousnessHybrid::updateHybridState() {
    if (consciousness_level_ > consciousness_threshold_) {
        if (hybrid_state_ != HybridState::CONSCIOUS) {
            hybrid_state_ = HybridState::CONSCIOUS;
            std::cout << "Hybrid state: CONSCIOUS (level: " << consciousness_level_ << ")" << std::endl;
        }
    } else if (consciousness_level_ > consciousness_threshold_ * 0.5) {
        if (hybrid_state_ != HybridState::PARTIALLY_CONSCIOUS) {
            hybrid_state_ = HybridState::PARTIALLY_CONSCIOUS;
            std::cout << "Hybrid state: PARTIALLY_CONSCIOUS (level: " << consciousness_level_ << ")" << std::endl;
        }
    } else {
        if (hybrid_state_ != HybridState::UNCONSCIOUS) {
            hybrid_state_ = HybridState::UNCONSCIOUS;
            std::cout << "Hybrid state: UNCONSCIOUS (level: " << consciousness_level_ << ")" << std::endl;
        }
    }
}

void ConsciousnessHybrid::processConsciousnessSignal(const std::vector<double>& input_signal) {
    consciousness_buffer_.clear();
    consciousness_buffer_.reserve(input_signal.size());
    
    for (double sample : input_signal) {
        // Apply consciousness-based processing
        double processed_sample = sample;
        
        if (hybrid_state_ == HybridState::CONSCIOUS) {
            // Full consciousness processing
            processed_sample *= (1.0 + consciousness_level_ * 0.2);
            processed_sample += std::sin(consciousness_level_ * M_PI) * 0.1;
        } else if (hybrid_state_ == HybridState::PARTIALLY_CONSCIOUS) {
            // Partial consciousness processing
            processed_sample *= (1.0 + consciousness_level_ * 0.1);
        } else {
            // Unconscious processing - minimal changes
            processed_sample *= (0.9 + consciousness_level_ * 0.1);
        }
        
        consciousness_buffer_.push_back(processed_sample);
    }
}

void ConsciousnessHybrid::applyHybridProcessing() {
    if (consciousness_buffer_.empty()) return;
    
    hybrid_processor_.clear();
    hybrid_processor_.reserve(consciousness_buffer_.size());
    
    std::uniform_real_distribution<double> noise_dist(-0.01, 0.01);
    
    for (size_t i = 0; i < consciousness_buffer_.size(); ++i) {
        double hybrid_sample = consciousness_buffer_[i];
        
        // Apply hybrid consciousness effects
        if (hybrid_state_ == HybridState::CONSCIOUS) {
            // Add conscious awareness patterns
            double awareness_pattern = std::sin(2.0 * M_PI * i * consciousness_level_ / 100.0);
            hybrid_sample += awareness_pattern * 0.05 * hybrid_factor_;
            
            // Add quantum consciousness effects
            double quantum_effect = std::cos(consciousness_level_ * M_PI * i / 50.0);
            hybrid_sample += quantum_effect * 0.03 * hybrid_factor_;
        }
        
        // Add subtle noise for consciousness realism
        hybrid_sample += noise_dist(random_generator_) * consciousness_level_;
        
        hybrid_processor_.push_back(hybrid_sample);
    }
}

std::vector<double> ConsciousnessHybrid::getProcessedSignal() const {
    return hybrid_processor_.empty() ? consciousness_buffer_ : hybrid_processor_;
}

double ConsciousnessHybrid::getConsciousnessLevel() const {
    return consciousness_level_;
}

ConsciousnessHybrid::HybridState ConsciousnessHybrid::getHybridState() const {
    return hybrid_state_;
}

void ConsciousnessHybrid::setConsciousnessThreshold(double threshold) {
    consciousness_threshold_ = std::clamp(threshold, 0.0, 1.0);
}

void ConsciousnessHybrid::setHybridFactor(double factor) {
    hybrid_factor_ = std::clamp(factor, 0.0, 1.0);
}

void ConsciousnessHybrid::reset() {
    consciousness_level_ = 0.0;
    hybrid_state_ = HybridState::UNCONSCIOUS;
    consciousness_buffer_.clear();
    hybrid_processor_.clear();
}

} // namespace AnantaDigital
