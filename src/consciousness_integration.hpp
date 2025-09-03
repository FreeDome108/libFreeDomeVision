#pragma once

#include "consciousness_hybrid.hpp"
#include <vector>
#include <memory>
#include <mutex>

namespace AnantaDigital::Integration {

// Система интеграции сознания
class ConsciousnessIntegration {
private:
    std::vector<std::unique_ptr<Consciousness::ConsciousnessHybrid>> consciousness_systems_;
    std::mutex integration_mutex_;
    bool is_integrated_;

public:
    ConsciousnessIntegration();
    
    // Инициализация интеграции
    bool initialize();
    
    // Добавление системы сознания
    void addConsciousnessSystem(std::unique_ptr<Consciousness::ConsciousnessHybrid> system);
    
    // Синхронизация всех систем
    void synchronizeSystems();
    
    // Создание коллективного сознания
    void createCollectiveConsciousness();
    
    // Получение статуса интеграции
    bool isIntegrated() const;
    
    // Очистка ресурсов
    void cleanup();
};

} // namespace AnantaDigital::Integration
