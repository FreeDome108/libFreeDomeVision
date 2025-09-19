#include "anantadigital_core.hpp"
#include <iostream>

namespace AnantaDigital {





// AnantaDigitalCore implementation
AnantaDigitalCore::AnantaDigitalCore(double radius, double height)
    : dome_radius_(radius)
    , dome_height_(height)
    , quantum_uncertainty_(0.1)
    , is_initialized_(false)
    , quantum_feedback_system_(std::make_unique<Feedback::QuantumFeedbackSystem>(std::chrono::microseconds(50000), 0.7))
    , consciousness_hybrid_(nullptr)
    , consciousness_integration_(nullptr)
    , dome_resonator_(std::make_unique<DomeAcousticResonator>(radius, height)) {
}

AnantaDigitalCore::~AnantaDigitalCore() = default;

bool AnantaDigitalCore::initialize() {
    if (is_initialized_) return true;
    
    // Initialize quantum feedback system
    if (quantum_feedback_system_) {
        // System is already initialized in constructor
        std::cout << "Quantum feedback system initialized" << std::endl;
    }
    
    // Initialize consciousness systems
    consciousness_hybrid_ = std::make_unique<Consciousness::ConsciousnessHybrid>();
    consciousness_integration_ = std::make_unique<Integration::ConsciousnessIntegration>();
    
    if (consciousness_hybrid_) {
        consciousness_hybrid_->initialize();
    }
    
    if (consciousness_integration_) {
        consciousness_integration_->initialize();
        // Add the hybrid system to integration
        consciousness_integration_->addConsciousnessSystem(std::move(consciousness_hybrid_));
    }
    
    // Initialize dome resonator
    std::map<double, double> material_properties = {
        {20.0, 0.1},    // 20 Hz - low frequency absorption
        {200.0, 0.3},   // 200 Hz - bass absorption
        {2000.0, 0.5},  // 2 kHz - mid frequency absorption
        {20000.0, 0.7}  // 20 kHz - very high frequency absorption
    };
    dome_resonator_->setMaterialProperties(material_properties);
    
    is_initialized_ = true;
    std::cout << "AnantaDigitalCore initialized successfully" << std::endl;
    
    return true;
}

void AnantaDigitalCore::shutdown() {
    if (!is_initialized_) return;
    
    // Shutdown quantum feedback system
    if (quantum_feedback_system_) {
        quantum_feedback_system_->reset();
    }
    
    // Shutdown consciousness systems
    if (consciousness_integration_) {
        consciousness_integration_->cleanup();
    }
    
    is_initialized_ = false;
    std::cout << "AnantaDigitalCore shutdown completed" << std::endl;
}

bool AnantaDigitalCore::isInitialized() const {
    return is_initialized_;
}

std::vector<double> AnantaDigitalCore::getProcessedSignal() const {
    return output_buffer_;
}

std::string AnantaDigitalCore::getVersion() const {
    return "2.1.0";
}

void AnantaDigitalCore::addInterferenceField(std::unique_ptr<InterferenceField> field) {
    std::lock_guard<std::mutex> lock(core_mutex_);
    if (field) {
        interference_fields_.push_back(std::move(field));
    }
}

void AnantaDigitalCore::removeInterferenceField(size_t field_index) {
    std::lock_guard<std::mutex> lock(core_mutex_);
    if (field_index < interference_fields_.size()) {
        interference_fields_.erase(interference_fields_.begin() + field_index);
    }
}

QuantumSoundField AnantaDigitalCore::createQuantumSoundField(double frequency, 
                                                           const SphericalCoord& position,
                                                           QuantumSoundState state) {
    QuantumSoundField field;
    field.amplitude = std::complex<double>(1.0, 0.0);
    field.frequency = frequency;
    field.phase = 0.0;
    field.quantum_state = state;
    field.position = position;
    field.timestamp = std::chrono::high_resolution_clock::now();
    
    // Создаем простую волновую функцию
    field.wave_function = [frequency](double r, double theta, double phi, double t) -> std::complex<double> {
        double phase = 2.0 * M_PI * frequency * t - 2.0 * M_PI * r / 343.0;
        return std::complex<double>(std::cos(phase), std::sin(phase));
    };
    
    return field;
}

void AnantaDigitalCore::processSoundField(const QuantumSoundField& input_field) {
    std::lock_guard<std::mutex> lock(core_mutex_);
    
    // Обрабатываем звуковое поле через квантовую систему обратной связи
    if (quantum_feedback_system_) {
        auto processed_amplitude = quantum_feedback_system_->processQuantumSignal(input_field.amplitude);
        
        QuantumSoundField processed_field = input_field;
        processed_field.amplitude = processed_amplitude;
        
        // Добавляем в карту звуковых полей
        sound_fields_[input_field.position] = processed_field;
    }
}

std::vector<QuantumSoundField> AnantaDigitalCore::getOutputFields() const {
    std::lock_guard<std::mutex> lock(core_mutex_);
    
    std::vector<QuantumSoundField> output_fields;
    for (const auto& pair : sound_fields_) {
        output_fields.push_back(pair.second);
    }
    
    return output_fields;
}

void AnantaDigitalCore::update(double dt) {
    std::lock_guard<std::mutex> lock(core_mutex_);
    
    // Обновляем интерференционные поля
    for (auto& field : interference_fields_) {
        if (field) {
            field->updateQuantumState(dt);
        }
    }
    
    // Обновляем системы сознания
    if (consciousness_integration_) {
        // Здесь можно добавить обновление интеграции сознания
    }
    
    // Обновляем купольный резонатор
    if (dome_resonator_) {
        // Резонатор не требует постоянного обновления
    }
}

void AnantaDigitalCore::processInterferenceField(const std::vector<double>& input_signal) {
    // Обрабатываем входной сигнал через интерференционные поля
    if (input_signal.empty()) return;
    
    // Создаем квантовое звуковое поле из входного сигнала
    double avg_frequency = 440.0; // Базовая частота
    SphericalCoord center_pos = {dome_radius_/2, M_PI/2, 0.0, dome_height_/2};
    
    QuantumSoundField input_field = createQuantumSoundField(avg_frequency, center_pos, QuantumSoundState::COHERENT);
    
    // Обрабатываем через систему
    processSoundField(input_field);
}

void AnantaDigitalCore::processDomeResonance() {
    if (!dome_resonator_) return;
    
    // Обрабатываем резонанс купола
    auto eigen_frequencies = dome_resonator_->calculateEigenFrequencies();
    
    // Создаем резонансные поля для каждой собственной частоты
    for (double freq : eigen_frequencies) {
        if (freq > 20.0 && freq < 20000.0) { // Только в слышимом диапазоне
            SphericalCoord pos = {dome_radius_/2, M_PI/2, 0.0, dome_height_/2};
            QuantumSoundField resonance_field = createQuantumSoundField(freq, pos, QuantumSoundState::COHERENT);
            processSoundField(resonance_field);
        }
    }
}

void AnantaDigitalCore::generateOutput() {
    // Генерируем выходной сигнал
    auto output_fields = getOutputFields();
    
    // Конвертируем в буфер для вывода
    output_buffer_.clear();
    output_buffer_.reserve(output_fields.size() * 1024);
    
    for (const auto& field : output_fields) {
        // Генерируем синусоидальный сигнал
        for (int i = 0; i < 1024; ++i) {
            double t = static_cast<double>(i) / 44100.0; // 44.1 kHz
            double sample = std::real(field.amplitude) * std::sin(2.0 * M_PI * field.frequency * t + field.phase);
            output_buffer_.push_back(sample);
        }
    }
}

void AnantaDigitalCore::processAudioSignal(const std::vector<double>& input_signal) {
    if (input_signal.empty()) return;
    
    // Обрабатываем аудио сигнал
    processInterferenceField(input_signal);
    processDomeResonance();
    generateOutput();
}

AnantaDigitalCore::SystemStatistics AnantaDigitalCore::getStatistics() const {
    std::lock_guard<std::mutex> lock(core_mutex_);
    
    SystemStatistics stats;
    stats.active_fields = interference_fields_.size();
    stats.entangled_pairs = 0; // Подсчет запутанных пар
    stats.coherence_ratio = 1.0; // Коэффициент когерентности
    stats.energy_efficiency = 0.8; // Энергетическая эффективность
    
    // Подсчитываем запутанные пары
    for (const auto& field : interference_fields_) {
        if (field) {
            // Здесь можно добавить логику подсчета запутанных пар
        }
    }
    
    return stats;
}

} // namespace AnantaDigital
