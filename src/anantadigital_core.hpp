#pragma once

#include <complex>
#include <vector>
#include <memory>
#include <functional>
#include <map>
#include <mutex>
#include <thread>
#include <chrono>
#include "quantum_feedback_system.hpp"
#include "consciousness_hybrid.hpp"
#include "consciousness_integration.hpp"
#include "interference_field.hpp"
#include "dome_acoustic_resonator.hpp"

// Forward declarations
namespace AnantaDigital::Feedback {
    class QuantumFeedbackSystem;
}

namespace AnantaDigital {

    // Квантовые состояния звуковых частиц
    enum class QuantumSoundState {
        COHERENT,           // Когерентное состояние
        SUPERPOSITION,      // Суперпозиция
        ENTANGLED,          // Запутанное состояние
        COLLAPSED           // Коллапсированное состояние
    };

    // Типы интерференционных полей
    enum class InterferenceFieldType {
        CONSTRUCTIVE,       // Конструктивная интерференция
        DESTRUCTIVE,        // Деструктивная интерференция
        PHASE_MODULATED,    // Фазово-модулированная
        AMPLITUDE_MODULATED,// Амплитудно-модулированная
        QUANTUM_ENTANGLED   // Квантово-запутанная
    };

    // 3D координаты в купольном пространстве
    struct SphericalCoord {
        double r;       // радиус
        double theta;   // полярный угол (0-π)
        double phi;     // азимутальный угол (0-2π)
        double height;  // высота в куполе
        
        // Оператор сравнения для использования в std::map
        bool operator<(const SphericalCoord& other) const {
            if (r != other.r) return r < other.r;
            if (theta != other.theta) return theta < other.theta;
            if (phi != other.phi) return phi < other.phi;
            return height < other.height;
        }
        
        bool operator==(const SphericalCoord& other) const {
            return r == other.r && theta == other.theta && phi == other.phi && height == other.height;
        }
    };

    // Комплексное звуковое поле с квантовыми свойствами
    struct QuantumSoundField {
        std::complex<double> amplitude;
        double phase;
        double frequency;
        QuantumSoundState quantum_state;
        SphericalCoord position;
        std::chrono::high_resolution_clock::time_point timestamp;
        
        // Квантовая волновая функция
        std::function<std::complex<double>(double, double, double, double)> wave_function;
    };

    // Forward declarations
    class InterferenceField;
    class DomeAcousticResonator;

    // Основной класс AnantaDigital
    class AnantaDigitalCore {
    private:
        std::vector<std::unique_ptr<InterferenceField>> interference_fields_;
        std::unique_ptr<DomeAcousticResonator> dome_resonator_;
        std::map<SphericalCoord, QuantumSoundField> sound_fields_;
        mutable std::mutex core_mutex_;
        
        // Параметры системы
        double dome_radius_;
        double dome_height_;
        double quantum_uncertainty_;
        bool is_initialized_;
        
        // Системы обработки
        std::unique_ptr<Feedback::QuantumFeedbackSystem> quantum_feedback_system_;
        std::unique_ptr<Consciousness::ConsciousnessHybrid> consciousness_hybrid_;
        std::unique_ptr<Integration::ConsciousnessIntegration> consciousness_integration_;
        
        // Буферы обработки
        std::vector<double> processing_buffer_;
        std::vector<double> output_buffer_;

    public:
        AnantaDigitalCore(double radius, double height);
        ~AnantaDigitalCore();
        
        // Инициализация системы
        bool initialize();
        void shutdown();
        bool isInitialized() const;
        
        // Управление интерференционными полями
        void addInterferenceField(std::unique_ptr<InterferenceField> field);
        void removeInterferenceField(size_t field_index);
        
        // Создание квантовых звуковых полей
        QuantumSoundField createQuantumSoundField(double frequency, 
                                                  const SphericalCoord& position,
                                                  QuantumSoundState state);
        
        // Обработка звукового поля
        void processSoundField(const QuantumSoundField& input_field);
        
        // Получение результирующего звукового поля
        std::vector<QuantumSoundField> getOutputFields() const;
        
        // Получение обработанного сигнала
        std::vector<double> getProcessedSignal() const;
        
        // Обновление системы
        void update(double dt);
        
        // Внутренние методы
        void processInterferenceField(const std::vector<double>& input_signal);
        void processDomeResonance();
        void generateOutput();
        
        // Обработка аудио сигнала
        void processAudioSignal(const std::vector<double>& input_signal);
        
        // Получение версии
        std::string getVersion() const;
        
        // Получение статистики системы
        struct SystemStatistics {
            size_t active_fields;
            size_t entangled_pairs;
            double coherence_ratio;
            double energy_efficiency;
        };
        
        SystemStatistics getStatistics() const;
    };

} // namespace AnantaDigital
