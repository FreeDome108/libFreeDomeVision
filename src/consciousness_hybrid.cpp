#include "consciousness_hybrid.hpp"
#include <algorithm>
#include <cmath>
#include <random>

namespace AnantaDigital::Consciousness {

ConsciousnessHybrid::ConsciousnessHybrid() {
    // Инициализация квантового сознания
    consciousness_.wave_function = std::complex<double>(1.0, 0.0);
    consciousness_.state = ConsciousnessState::AWARE;
    consciousness_.coherence_time = 1.0;
    consciousness_.last_update = std::chrono::high_resolution_clock::now();
    
    // Инициализация амплитуд состояний
    consciousness_.state_amplitudes.resize(5); // 5 состояний сознания
    consciousness_.state_amplitudes[0] = std::complex<double>(1.0, 0.0); // AWARE
    consciousness_.state_amplitudes[1] = std::complex<double>(0.0, 0.0); // MEDITATIVE
    consciousness_.state_amplitudes[2] = std::complex<double>(0.0, 0.0); // QUANTUM_FLUX
    consciousness_.state_amplitudes[3] = std::complex<double>(0.0, 0.0); // COHERENT
    consciousness_.state_amplitudes[4] = std::complex<double>(0.0, 0.0); // ENTANGLED
}

bool ConsciousnessHybrid::initialize() {
    std::lock_guard<std::mutex> lock(consciousness_mutex_);
    
    // Нормализуем амплитуды состояний
    normalizeStateAmplitudes();
    
    return true;
}

void ConsciousnessHybrid::updateQuantumState(double dt) {
    std::lock_guard<std::mutex> lock(consciousness_mutex_);
    
    // Обновляем суперпозицию состояний
    updateStateSuperposition(dt);
    
    // Обновляем время когерентности
    consciousness_.coherence_time -= dt * 0.1;
    consciousness_.coherence_time = std::max(0.0, consciousness_.coherence_time);
    
    // Обновляем временную метку
    consciousness_.last_update = std::chrono::high_resolution_clock::now();
    
    // Уведомляем наблюдателей
    notifyObservers();
}

void ConsciousnessHybrid::enterMeditativeState() {
    std::lock_guard<std::mutex> lock(consciousness_mutex_);
    
    // Переход в медитативное состояние
    consciousness_.state = ConsciousnessState::MEDITATIVE;
    
    // Обновляем амплитуды состояний
    consciousness_.state_amplitudes[0] = std::complex<double>(0.2, 0.0); // AWARE
    consciousness_.state_amplitudes[1] = std::complex<double>(0.8, 0.0); // MEDITATIVE
    consciousness_.state_amplitudes[2] = std::complex<double>(0.0, 0.0); // QUANTUM_FLUX
    consciousness_.state_amplitudes[3] = std::complex<double>(0.0, 0.0); // COHERENT
    consciousness_.state_amplitudes[4] = std::complex<double>(0.0, 0.0); // ENTANGLED
    
    // Нормализуем
    normalizeStateAmplitudes();
    
    // Увеличиваем время когерентности
    consciousness_.coherence_time = 2.0;
}

void ConsciousnessHybrid::createQuantumEntanglement(ConsciousnessHybrid& other) {
    std::lock_guard<std::mutex> lock1(consciousness_mutex_);
    std::lock_guard<std::mutex> lock2(other.consciousness_mutex_);
    
    // Создаем квантовую запутанность между двумя системами сознания
    consciousness_.state = ConsciousnessState::ENTANGLED;
    other.consciousness_.state = ConsciousnessState::ENTANGLED;
    
    // Синхронизируем волновые функции
    std::complex<double> avg_wave_function = (consciousness_.wave_function + other.consciousness_.wave_function) / 2.0;
    consciousness_.wave_function = avg_wave_function;
    other.consciousness_.wave_function = avg_wave_function;
    
    // Синхронизируем амплитуды состояний
    for (size_t i = 0; i < consciousness_.state_amplitudes.size(); ++i) {
        std::complex<double> avg_amplitude = (consciousness_.state_amplitudes[i] + other.consciousness_.state_amplitudes[i]) / 2.0;
        consciousness_.state_amplitudes[i] = avg_amplitude;
        other.consciousness_.state_amplitudes[i] = avg_amplitude;
    }
    
    // Нормализуем обе системы
    normalizeStateAmplitudes();
    other.normalizeStateAmplitudes();
}

QuantumConsciousness ConsciousnessHybrid::getCurrentState() const {
    std::lock_guard<std::mutex> lock(consciousness_mutex_);
    return consciousness_;
}

void ConsciousnessHybrid::addObserver(std::function<void(const QuantumConsciousness&)> observer) {
    std::lock_guard<std::mutex> lock(consciousness_mutex_);
    observers_.push_back(observer);
}

void ConsciousnessHybrid::cleanup() {
    std::lock_guard<std::mutex> lock(consciousness_mutex_);
    observers_.clear();
}

void ConsciousnessHybrid::updateStateSuperposition(double dt) {
    // Обновляем суперпозицию состояний с учетом квантовых флуктуаций
    
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::normal_distribution<double> noise(0.0, 0.01);
    
    // Добавляем квантовые флуктуации
    for (auto& amplitude : consciousness_.state_amplitudes) {
        double real_noise = noise(gen);
        double imag_noise = noise(gen);
        amplitude += std::complex<double>(real_noise, imag_noise) * dt;
    }
    
    // Нормализуем амплитуды
    normalizeStateAmplitudes();
    
    // Определяем доминирующее состояние
    double max_probability = 0.0;
    int dominant_state = 0;
    
    for (size_t i = 0; i < consciousness_.state_amplitudes.size(); ++i) {
        double probability = std::norm(consciousness_.state_amplitudes[i]);
        if (probability > max_probability) {
            max_probability = probability;
            dominant_state = static_cast<int>(i);
        }
    }
    
    // Обновляем состояние сознания
    consciousness_.state = static_cast<ConsciousnessState>(dominant_state);
    
    // Обновляем волновую функцию
    consciousness_.wave_function = consciousness_.state_amplitudes[dominant_state];
}

void ConsciousnessHybrid::normalizeStateAmplitudes() {
    // Нормализуем амплитуды состояний (сумма квадратов модулей = 1)
    double total_probability = 0.0;
    
    for (const auto& amplitude : consciousness_.state_amplitudes) {
        total_probability += std::norm(amplitude);
    }
    
    if (total_probability > 0.0) {
        double normalization_factor = 1.0 / std::sqrt(total_probability);
        for (auto& amplitude : consciousness_.state_amplitudes) {
            amplitude *= normalization_factor;
        }
    }
}

void ConsciousnessHybrid::collapseToState() {
    // Коллапс квантовой суперпозиции к одному состоянию
    
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<double> dist(0.0, 1.0);
    
    double random_value = dist(gen);
    double cumulative_probability = 0.0;
    
    for (size_t i = 0; i < consciousness_.state_amplitudes.size(); ++i) {
        cumulative_probability += std::norm(consciousness_.state_amplitudes[i]);
        if (random_value <= cumulative_probability) {
            // Коллапс к состоянию i
            consciousness_.state = static_cast<ConsciousnessState>(i);
            consciousness_.wave_function = consciousness_.state_amplitudes[i];
            
            // Обнуляем все остальные амплитуды
            for (size_t j = 0; j < consciousness_.state_amplitudes.size(); ++j) {
                if (j != i) {
                    consciousness_.state_amplitudes[j] = std::complex<double>(0.0, 0.0);
                }
            }
            break;
        }
    }
}

void ConsciousnessHybrid::notifyObservers() {
    // Уведомляем всех наблюдателей об изменении состояния
    for (const auto& observer : observers_) {
        try {
            observer(consciousness_);
        } catch (const std::exception& e) {
            // Игнорируем ошибки в наблюдателях
        }
    }
}

} // namespace AnantaDigital::Consciousness