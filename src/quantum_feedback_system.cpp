#include "quantum_feedback_system.hpp"
#include <algorithm>
#include <cmath>
#include <random>

namespace AnantaDigital::Feedback {

QuantumFeedbackSystem::QuantumFeedbackSystem(std::chrono::microseconds delay, double threshold)
    : feedback_delay_(delay)
    , coherence_threshold_(threshold)
    , last_feedback_(std::chrono::high_resolution_clock::now()) {
    feedback_buffer_.reserve(1024); // Предварительное выделение памяти
}

std::complex<double> QuantumFeedbackSystem::processQuantumSignal(const std::complex<double>& input) {
    std::lock_guard<std::mutex> lock(feedback_mutex_);
    
    auto now = std::chrono::high_resolution_clock::now();
    auto time_since_last = std::chrono::duration_cast<std::chrono::microseconds>(now - last_feedback_);
    
    // Проверяем, прошло ли достаточно времени для обратной связи
    if (time_since_last >= feedback_delay_) {
        // Вычисляем сигнал обратной связи
        auto feedback_signal = calculateFeedbackSignal(input);
        
        // Применяем квантовую коррекцию
        auto corrected_signal = applyQuantumCorrection(input, feedback_signal);
        
        // Добавляем в буфер обратной связи
        feedback_buffer_.push_back(feedback_signal);
        
        // Ограничиваем размер буфера
        if (feedback_buffer_.size() > 1024) {
            feedback_buffer_.erase(feedback_buffer_.begin());
        }
        
        last_feedback_ = now;
        return corrected_signal;
    }
    
    // Если время не пришло, возвращаем исходный сигнал
    return input;
}

std::vector<std::complex<double>> QuantumFeedbackSystem::getFeedback() const {
    std::lock_guard<std::mutex> lock(feedback_mutex_);
    return feedback_buffer_;
}

void QuantumFeedbackSystem::setFeedbackDelay(std::chrono::microseconds delay) {
    std::lock_guard<std::mutex> lock(feedback_mutex_);
    feedback_delay_ = delay;
}

void QuantumFeedbackSystem::setCoherenceThreshold(double threshold) {
    std::lock_guard<std::mutex> lock(feedback_mutex_);
    coherence_threshold_ = std::max(0.0, std::min(1.0, threshold));
}

void QuantumFeedbackSystem::reset() {
    std::lock_guard<std::mutex> lock(feedback_mutex_);
    feedback_buffer_.clear();
    last_feedback_ = std::chrono::high_resolution_clock::now();
}

bool QuantumFeedbackSystem::isCoherent() const {
    std::lock_guard<std::mutex> lock(feedback_mutex_);
    
    if (feedback_buffer_.empty()) {
        return true; // Пустой буфер считается когерентным
    }
    
    // Вычисляем дисперсию фазы
    double phase_variance = calculatePhaseVariance();
    
    // Проверяем когерентность
    return phase_variance < coherence_threshold_;
}

std::complex<double> QuantumFeedbackSystem::calculateFeedbackSignal(const std::complex<double>& input) const {
    // Простая модель квантовой обратной связи
    // Основана на принципах квантовой механики
    
    double amplitude = std::abs(input);
    double phase = std::arg(input);
    
    // Квантовая неопределенность
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::normal_distribution<double> noise(0.0, 0.1);
    
    double quantum_noise = noise(gen);
    
    // Вычисляем обратную связь с учетом квантовых эффектов
    double feedback_amplitude = amplitude * (1.0 + quantum_noise);
    double feedback_phase = phase + quantum_noise * 0.1;
    
    return std::polar(feedback_amplitude, feedback_phase);
}

std::complex<double> QuantumFeedbackSystem::applyQuantumCorrection(const std::complex<double>& input, 
                                                                  const std::complex<double>& feedback) const {
    // Применяем квантовую коррекцию к входному сигналу
    
    double input_amp = std::abs(input);
    double input_phase = std::arg(input);
    
    double feedback_amp = std::abs(feedback);
    double feedback_phase = std::arg(feedback);
    
    // Квантовая коррекция амплитуды
    double corrected_amp = input_amp * (1.0 - 0.1 * (feedback_amp - input_amp) / input_amp);
    corrected_amp = std::max(0.0, corrected_amp); // Не может быть отрицательной
    
    // Квантовая коррекция фазы
    double phase_diff = feedback_phase - input_phase;
    double corrected_phase = input_phase + 0.1 * phase_diff;
    
    return std::polar(corrected_amp, corrected_phase);
}

double QuantumFeedbackSystem::calculatePhaseVariance() const {
    if (feedback_buffer_.size() < 2) {
        return 0.0;
    }
    
    // Вычисляем среднюю фазу
    double mean_phase = 0.0;
    for (const auto& signal : feedback_buffer_) {
        mean_phase += std::arg(signal);
    }
    mean_phase /= feedback_buffer_.size();
    
    // Вычисляем дисперсию фазы
    double variance = 0.0;
    for (const auto& signal : feedback_buffer_) {
        double phase_diff = std::arg(signal) - mean_phase;
        // Нормализуем разность фаз к [-π, π]
        while (phase_diff > M_PI) phase_diff -= 2.0 * M_PI;
        while (phase_diff < -M_PI) phase_diff += 2.0 * M_PI;
        
        variance += phase_diff * phase_diff;
    }
    variance /= feedback_buffer_.size();
    
    return variance;
}

} // namespace AnantaDigital::Feedback