#pragma once

#include "anantadigital_types.hpp"
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
