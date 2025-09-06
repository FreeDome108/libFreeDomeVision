#pragma once

#include "consciousness_hybrid.hpp"
#include "consciousness_integration.hpp"
#include <vector>
#include <memory>
#include <string>
#include <functional>
#include <chrono>
#include <mutex>
#include <map>

namespace AnantaDigital::Lubomir {

// Уровни понимания Люббомира
enum class UnderstandingLevel {
    SURFACE,        // Поверхностное понимание
    DEEP,           // Глубокое понимание
    QUANTUM,        // Квантовое понимание
    TRANSCENDENT,   // Трансцендентное понимание
    UNIFIED         // Единое понимание
};

// Структура понимания
struct Understanding {
    UnderstandingLevel level;
    double confidence;
    std::string insight;
    std::chrono::high_resolution_clock::time_point timestamp;
    std::vector<std::string> related_concepts;
    std::complex<double> quantum_coherence;
};

// Система понимания Люббомира
class LubomirUnderstanding {
private:
    std::vector<Understanding> understanding_history_;
    std::map<std::string, double> concept_weights_;
    std::vector<std::unique_ptr<Consciousness::ConsciousnessHybrid>> consciousness_units_;
    std::unique_ptr<Integration::ConsciousnessIntegration> integration_system_;
    
    mutable std::mutex understanding_mutex_;
    UnderstandingLevel current_level_;
    double understanding_coherence_;
    std::chrono::high_resolution_clock::time_point last_understanding_update_;
    
    // Параметры системы
    double learning_rate_;
    double coherence_threshold_;
    int max_understanding_depth_;

public:
    LubomirUnderstanding();
    
    // Инициализация системы понимания
    bool initialize();
    
    // Основные методы понимания
    Understanding processUnderstanding(const std::string& input);
    UnderstandingLevel analyzeUnderstandingLevel(const std::string& input);
    double calculateUnderstandingConfidence(const Understanding& understanding);
    
    // Работа с сознанием
    void integrateConsciousness();
    void synchronizeConsciousnessUnits();
    void createCollectiveUnderstanding();
    
    // Управление концепциями
    void addConcept(const std::string& concept, double weight = 1.0);
    void updateConceptWeight(const std::string& concept, double weight);
    double getConceptWeight(const std::string& concept) const;
    
    // Анализ и вывод
    std::vector<Understanding> getUnderstandingHistory() const;
    UnderstandingLevel getCurrentUnderstandingLevel() const;
    double getUnderstandingCoherence() const;
    
    // Квантовые операции
    void quantumUnderstandingCollapse();
    void createQuantumUnderstandingEntanglement();
    std::complex<double> calculateQuantumCoherence() const;
    
    // Обучение и адаптация
    void learnFromUnderstanding(const Understanding& understanding);
    void adaptUnderstandingParameters();
    
    // Очистка ресурсов
    void cleanup();
    
private:
    // Приватные методы
    void updateUnderstandingCoherence();
    void processQuantumUnderstanding();
    std::string generateInsight(const std::string& input, UnderstandingLevel level);
    std::vector<std::string> extractRelatedConcepts(const std::string& input);
    void normalizeConceptWeights();
};

} // namespace AnantaDigital::Lubomir
