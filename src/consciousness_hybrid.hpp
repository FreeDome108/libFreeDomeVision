#pragma once

#include <vector>
#include <random>

namespace AnantaDigital {

enum class HybridState {
    UNCONSCIOUS,
    PARTIALLY_CONSCIOUS,
    CONSCIOUS
};

class ConsciousnessHybrid {
public:
    ConsciousnessHybrid(double consciousness_threshold = 0.6, double hybrid_factor = 0.8);
    ~ConsciousnessHybrid();

    // Process consciousness signal
    void processConsciousness(const std::vector<double>& input_signal);

    // Get processed signal
    std::vector<double> getProcessedSignal() const;

    // Get consciousness level
    double getConsciousnessLevel() const;

    // Get hybrid state
    HybridState getHybridState() const;

    // Configuration
    void setConsciousnessThreshold(double threshold);
    void setHybridFactor(double factor);

    // Reset system
    void reset();
    
    // Get consciousness threshold
    double getConsciousnessThreshold() const;
    
    // Get hybrid factor
    double getHybridFactor() const;

private:
    double consciousness_threshold_;
    double hybrid_factor_;
    double consciousness_level_;
    HybridState hybrid_state_;
    
    std::vector<double> consciousness_buffer_;
    std::vector<double> hybrid_processor_;
    std::mt19937 random_generator_;

    // Internal processing methods
    double calculateConsciousnessLevel(const std::vector<double>& signal);
    void updateHybridState();
    void processConsciousnessSignal(const std::vector<double>& input_signal);
    void applyHybridProcessing();
};

} // namespace AnantaDigital
