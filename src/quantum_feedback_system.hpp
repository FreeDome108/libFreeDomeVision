#pragma once

#include <complex>
#include <vector>
#include <chrono>
#include <functional>
#include <mutex>

namespace AnantaDigital::Feedback {

// Квантовая система обратной связи
class QuantumFeedbackSystem {
private:
    std::chrono::microseconds feedback_delay_;
    double coherence_threshold_;
    std::vector<std::complex<double>> feedback_buffer_;
    mutable std::mutex feedback_mutex_;
    std::chrono::high_resolution_clock::time_point last_feedback_;

public:
    QuantumFeedbackSystem(std::chrono::microseconds delay, double threshold);
    
    // Обработка квантового сигнала
    std::complex<double> processQuantumSignal(const std::complex<double>& input);
    
    // Получение обратной связи
    std::vector<std::complex<double>> getFeedback() const;
    
    // Установка параметров
    void setFeedbackDelay(std::chrono::microseconds delay);
    void setCoherenceThreshold(double threshold);
    
    // Получение параметров
    std::chrono::microseconds getFeedbackDelay() const { return feedback_delay_; }
    double getCoherenceThreshold() const { return coherence_threshold_; }
    
    // Сброс системы
    void reset();
    
    // Проверка когерентности
    bool isCoherent() const;
};

} // namespace AnantaDigital::Feedback
