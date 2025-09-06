#include "consciousness_integration.hpp"
#include <algorithm>

namespace AnantaDigital::Integration {

ConsciousnessIntegration::ConsciousnessIntegration() 
    : is_integrated_(false) {
}

bool ConsciousnessIntegration::initialize() {
    std::lock_guard<std::mutex> lock(integration_mutex_);
    
    // Инициализация системы интеграции
    is_integrated_ = true;
    
    return true;
}

void ConsciousnessIntegration::addConsciousnessSystem(std::unique_ptr<Consciousness::ConsciousnessHybrid> system) {
    std::lock_guard<std::mutex> lock(integration_mutex_);
    
    if (system) {
        consciousness_systems_.push_back(std::move(system));
    }
}

void ConsciousnessIntegration::synchronizeSystems() {
    std::lock_guard<std::mutex> lock(integration_mutex_);
    
    if (consciousness_systems_.size() < 2) {
        return; // Нужно минимум 2 системы для синхронизации
    }
    
    // Синхронизируем все системы сознания
    for (size_t i = 0; i < consciousness_systems_.size(); ++i) {
        for (size_t j = i + 1; j < consciousness_systems_.size(); ++j) {
            if (consciousness_systems_[i] && consciousness_systems_[j]) {
                // Создаем квантовую запутанность между системами
                consciousness_systems_[i]->createQuantumEntanglement(*consciousness_systems_[j]);
            }
        }
    }
}

void ConsciousnessIntegration::createCollectiveConsciousness() {
    std::lock_guard<std::mutex> lock(integration_mutex_);
    
    if (consciousness_systems_.empty()) {
        return;
    }
    
    // Создаем коллективное сознание путем синхронизации всех систем
    synchronizeSystems();
    
    // Дополнительная обработка для создания коллективного эффекта
    for (auto& system : consciousness_systems_) {
        if (system) {
            // Переводим все системы в медитативное состояние для коллективного эффекта
            system->enterMeditativeState();
        }
    }
}

bool ConsciousnessIntegration::isIntegrated() const {
    std::lock_guard<std::mutex> lock(const_cast<std::mutex&>(integration_mutex_));
    return is_integrated_;
}

void ConsciousnessIntegration::cleanup() {
    std::lock_guard<std::mutex> lock(integration_mutex_);
    
    // Очищаем все системы сознания
    for (auto& system : consciousness_systems_) {
        if (system) {
            system->cleanup();
        }
    }
    
    consciousness_systems_.clear();
    is_integrated_ = false;
}

} // namespace AnantaDigital::Integration