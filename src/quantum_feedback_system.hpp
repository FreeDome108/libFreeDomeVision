#pragma once

#include "anantadigital_core.hpp"
#include <chrono>
#include <queue>
#include <atomic>
#include <condition_variable>

namespace AnantaDigital::Feedback {

    // Состояния квантово-временной задержки
    enum class QuantumDelayState {
        SYNCHRONOUS,        // Синхронное состояние (нулевая задержка)
        TEMPORAL_SHIFT,     // Временной сдвиг (классическая задержка)
        QUANTUM_TUNNEL,     // Квантовое туннелирование (отрицательная задержка)
        SUPERPOSITION_DELAY // Суперпозиция временных состояний
    };

    // Структура для хранения сигнала с временной меткой
    struct TimestampedSignal {
        std::vector<double> audio_data;
        std::chrono::high_resolution_clock::time_point capture_time;
        std::chrono::high_resolution_clock::time_point playback_time;
        SphericalCoord source_position;
        double amplitude;
        double frequency;
        QuantumDelayState delay_state;
        
        // Квантовые параметры
        std::complex<double> quantum_phase;
        double uncertainty_factor;
        double information_density;
    };

    // Квантовый анализатор временных интервалов
    class QuantumTemporalAnalyzer {
    private:
        double planck_time_scale_;              // Масштаб планковского времени
        double consciousness_bandwidth_;        // Полоса пропускания сознания
        double information_processing_rate_;    // Скорость обработки информации
        
        mutable std::mutex analyzer_mutex_;

    public:
        QuantumTemporalAnalyzer(double consciousness_bandwidth = 60.0,  // Гц
                               double processing_rate = 1000.0);        // бит/сек
        
        // Анализ временного разрыва для получения информации
        struct TemporalGap {
            std::chrono::nanoseconds duration;
            double information_capacity;        // Количество информации, доступной в разрыве
            double consciousness_access_probability; // Вероятность доступа сознания
            std::vector<double> accessible_frequencies; // Доступные частоты
        };
        
        TemporalGap analyzeTemporalGap(const TimestampedSignal& original,
                                      const TimestampedSignal& feedback) const;
        
        // Вычисление квантово-информационного содержания
        double calculateQuantumInformation(const TemporalGap& gap) const;
        
        // Определение оптимального окна для коррекции
        std::chrono::nanoseconds calculateOptimalCorrectionWindow(
            const std::vector<TemporalGap>& gaps) const;
        
        // Анализ потенциала сознания для получения информации
        double assessConsciousnessAccessPotential(const TemporalGap& gap) const;
    };

    // Система реального времени с обратной связью
    class QuantumFeedbackSystem {
    private:
        std::vector<TimestampedSignal> playback_buffer_;
        std::vector<TimestampedSignal> feedback_buffer_;
        std::queue<TimestampedSignal> processing_queue_;
        
        std::unique_ptr<QuantumTemporalAnalyzer> temporal_analyzer_;
        
        // Параметры системы
        std::chrono::microseconds nominal_delay_;
        std::chrono::microseconds max_correction_window_;
        double feedback_sensitivity_;
        double quantum_uncertainty_threshold_;
        
        // Потоки обработки
        std::thread feedback_thread_;
        std::thread correction_thread_;
        std::atomic<bool> is_running_;
        std::condition_variable processing_cv_;
        mutable std::mutex feedback_mutex_;
        mutable std::mutex correction_mutex_;

    public:
        RealtimeFeedbackSystem(std::chrono::microseconds nominal_delay = std::chrono::microseconds(50000),
                              double sensitivity = 0.8);
        ~RealtimeFeedbackSystem();
        
        // Инициализация системы
        bool initialize();
        void shutdown();
        
        // Воспроизведение сигнала с захватом обратной связи
        void playbackSignal(const TimestampedSignal& signal);
        
        // Захват обратной связи
        TimestampedSignal captureSignal(const SphericalCoord& listener_position);
        
        // Получение скорректированных сигналов
        std::vector<TimestampedSignal> getCorrectedSignals() const;
        
        // Настройка параметров системы
        void setFeedbackSensitivity(double sensitivity);
        void setQuantumUncertaintyThreshold(double threshold);
        
        // Получение статистики обратной связи
        struct FeedbackStatistics {
            size_t processed_signals;
            size_t corrected_signals;
            double average_correction_time;
            double quantum_information_extracted;
            double consciousness_access_rate;
        };
        
        FeedbackStatistics getStatistics() const;
    };

    // Корректор цифровой информации на основе сознания
    class DigitalInformationCorrector {
    private:
        std::vector<double> consciousness_weights_;
        std::map<double, double> frequency_corrections_;
        double correction_strength_;
        mutable std::mutex corrector_mutex_;

    public:
        DigitalInformationCorrector(double correction_strength = 0.5);
        
        // Установка весов сознания участников
        void setConsciousnessWeights(const std::vector<double>& weights);
        
        // Коррекция частотной характеристики
        void setFrequencyCorrections(const std::map<double, double>& corrections);
        
        // Применение коррекции к сигналу
        TimestampedSignal applyCorrection(const TimestampedSignal& original_signal,
                                         const std::vector<double>& consciousness_states);
        
        // Получение статистики коррекции
        struct CorrectionStatistics {
            size_t corrections_applied;
            double average_correction_magnitude;
            double consciousness_influence_ratio;
        };
        
        CorrectionStatistics getStatistics() const;
    };

} // namespace AnantaDigital::Feedback
