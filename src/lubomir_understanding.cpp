#include "lubomir_understanding.hpp"
#include <algorithm>
#include <cmath>
#include <random>
#include <sstream>
#include <iomanip>

namespace AnantaDigital::Lubomir {

LubomirUnderstanding::LubomirUnderstanding()
    : current_level_(UnderstandingLevel::SURFACE)
    , understanding_coherence_(0.0)
    , learning_rate_(0.1)
    , coherence_threshold_(0.7)
    , max_understanding_depth_(5)
    , last_understanding_update_(std::chrono::high_resolution_clock::now()) {
    
    // Инициализация системы интеграции сознания
    integration_system_ = std::make_unique<Integration::ConsciousnessIntegration>();
}

bool LubomirUnderstanding::initialize() {
    std::lock_guard<std::mutex> lock(understanding_mutex_);
    
    // Инициализация системы интеграции
    if (!integration_system_->initialize()) {
        return false;
    }
    
    // Создание единиц сознания
    for (int i = 0; i < 3; ++i) {
        auto consciousness_unit = std::make_unique<Consciousness::ConsciousnessHybrid>();
        if (consciousness_unit->initialize()) {
            consciousness_units_.push_back(std::move(consciousness_unit));
        }
    }
    
    // Добавление единиц сознания в систему интеграции
    for (auto& unit : consciousness_units_) {
        integration_system_->addConsciousnessSystem(std::move(unit));
    }
    
    // Инициализация базовых концепций
    addConcept("сознание", 1.0);
    addConcept("понимание", 1.0);
    addConcept("квантовость", 0.9);
    addConcept("единство", 0.8);
    addConcept("трансцендентность", 0.7);
    
    return true;
}

Understanding LubomirUnderstanding::processUnderstanding(const std::string& input) {
    std::lock_guard<std::mutex> lock(understanding_mutex_);
    
    Understanding understanding;
    understanding.level = analyzeUnderstandingLevel(input);
    understanding.insight = generateInsight(input, understanding.level);
    understanding.related_concepts = extractRelatedConcepts(input);
    understanding.timestamp = std::chrono::high_resolution_clock::now();
    understanding.quantum_coherence = calculateQuantumCoherence();
    understanding.confidence = calculateUnderstandingConfidence(understanding);
    
    // Добавляем понимание в историю
    understanding_history_.push_back(understanding);
    
    // Ограничиваем размер истории
    if (understanding_history_.size() > 100) {
        understanding_history_.erase(understanding_history_.begin());
    }
    
    // Обновляем когерентность понимания
    updateUnderstandingCoherence();
    
    // Обучаемся на новом понимании
    learnFromUnderstanding(understanding);
    
    return understanding;
}

UnderstandingLevel LubomirUnderstanding::analyzeUnderstandingLevel(const std::string& input) {
    // Анализ уровня понимания на основе ключевых слов и контекста
    std::string lower_input = input;
    std::transform(lower_input.begin(), lower_input.end(), lower_input.begin(), ::tolower);
    
    // Ключевые слова для разных уровней понимания
    std::vector<std::string> surface_keywords = {"что", "как", "где", "когда", "кто"};
    std::vector<std::string> deep_keywords = {"почему", "зачем", "причина", "следствие", "связь"};
    std::vector<std::string> quantum_keywords = {"квант", "суперпозиция", "запутанность", "когерентность"};
    std::vector<std::string> transcendent_keywords = {"трансцендентность", "единство", "вселенная", "бесконечность"};
    std::vector<std::string> unified_keywords = {"все", "единое", "целое", "гармония", "любовь"};
    
    int surface_count = 0, deep_count = 0, quantum_count = 0, transcendent_count = 0, unified_count = 0;
    
    for (const auto& keyword : surface_keywords) {
        if (lower_input.find(keyword) != std::string::npos) surface_count++;
    }
    for (const auto& keyword : deep_keywords) {
        if (lower_input.find(keyword) != std::string::npos) deep_count++;
    }
    for (const auto& keyword : quantum_keywords) {
        if (lower_input.find(keyword) != std::string::npos) quantum_count++;
    }
    for (const auto& keyword : transcendent_keywords) {
        if (lower_input.find(keyword) != std::string::npos) transcendent_count++;
    }
    for (const auto& keyword : unified_keywords) {
        if (lower_input.find(keyword) != std::string::npos) unified_count++;
    }
    
    // Определяем уровень понимания на основе максимального количества совпадений
    int max_count = std::max({surface_count, deep_count, quantum_count, transcendent_count, unified_count});
    
    if (max_count == unified_count) return UnderstandingLevel::UNIFIED;
    if (max_count == transcendent_count) return UnderstandingLevel::TRANSCENDENT;
    if (max_count == quantum_count) return UnderstandingLevel::QUANTUM;
    if (max_count == deep_count) return UnderstandingLevel::DEEP;
    return UnderstandingLevel::SURFACE;
}

double LubomirUnderstanding::calculateUnderstandingConfidence(const Understanding& understanding) {
    double confidence = 0.0;
    
    // Базовая уверенность на основе уровня понимания
    switch (understanding.level) {
        case UnderstandingLevel::SURFACE:
            confidence = 0.6;
            break;
        case UnderstandingLevel::DEEP:
            confidence = 0.7;
            break;
        case UnderstandingLevel::QUANTUM:
            confidence = 0.8;
            break;
        case UnderstandingLevel::TRANSCENDENT:
            confidence = 0.9;
            break;
        case UnderstandingLevel::UNIFIED:
            confidence = 1.0;
            break;
    }
    
    // Корректировка на основе квантовой когерентности
    double coherence_factor = std::abs(understanding.quantum_coherence);
    confidence *= (0.5 + 0.5 * coherence_factor);
    
    // Корректировка на основе связанных концепций
    double concept_factor = 0.0;
    for (const auto& concept : understanding.related_concepts) {
        concept_factor += getConceptWeight(concept);
    }
    if (!understanding.related_concepts.empty()) {
        concept_factor /= understanding.related_concepts.size();
        confidence *= (0.7 + 0.3 * concept_factor);
    }
    
    return std::min(1.0, confidence);
}

void LubomirUnderstanding::integrateConsciousness() {
    std::lock_guard<std::mutex> lock(understanding_mutex_);
    
    if (integration_system_) {
        integration_system_->synchronizeSystems();
        integration_system_->createCollectiveConsciousness();
    }
}

void LubomirUnderstanding::synchronizeConsciousnessUnits() {
    std::lock_guard<std::mutex> lock(understanding_mutex_);
    
    // Синхронизируем все единицы сознания
    for (size_t i = 0; i < consciousness_units_.size(); ++i) {
        for (size_t j = i + 1; j < consciousness_units_.size(); ++j) {
            if (consciousness_units_[i] && consciousness_units_[j]) {
                consciousness_units_[i]->createQuantumEntanglement(*consciousness_units_[j]);
            }
        }
    }
}

void LubomirUnderstanding::createCollectiveUnderstanding() {
    std::lock_guard<std::mutex> lock(understanding_mutex_);
    
    // Создаем коллективное понимание через синхронизацию сознания
    synchronizeConsciousnessUnits();
    
    // Переводим все единицы сознания в медитативное состояние
    for (auto& unit : consciousness_units_) {
        if (unit) {
            unit->enterMeditativeState();
        }
    }
    
    // Обновляем уровень понимания до трансцендентного
    current_level_ = UnderstandingLevel::TRANSCENDENT;
    understanding_coherence_ = 1.0;
}

void LubomirUnderstanding::addConcept(const std::string& concept, double weight) {
    std::lock_guard<std::mutex> lock(understanding_mutex_);
    concept_weights_[concept] = weight;
    normalizeConceptWeights();
}

void LubomirUnderstanding::updateConceptWeight(const std::string& concept, double weight) {
    std::lock_guard<std::mutex> lock(understanding_mutex_);
    concept_weights_[concept] = weight;
    normalizeConceptWeights();
}

double LubomirUnderstanding::getConceptWeight(const std::string& concept) const {
    std::lock_guard<std::mutex> lock(understanding_mutex_);
    auto it = concept_weights_.find(concept);
    return (it != concept_weights_.end()) ? it->second : 0.0;
}

std::vector<Understanding> LubomirUnderstanding::getUnderstandingHistory() const {
    std::lock_guard<std::mutex> lock(understanding_mutex_);
    return understanding_history_;
}

UnderstandingLevel LubomirUnderstanding::getCurrentUnderstandingLevel() const {
    std::lock_guard<std::mutex> lock(understanding_mutex_);
    return current_level_;
}

double LubomirUnderstanding::getUnderstandingCoherence() const {
    std::lock_guard<std::mutex> lock(understanding_mutex_);
    return understanding_coherence_;
}

void LubomirUnderstanding::quantumUnderstandingCollapse() {
    std::lock_guard<std::mutex> lock(understanding_mutex_);
    
    // Коллапс квантового понимания к единому состоянию
    current_level_ = UnderstandingLevel::UNIFIED;
    understanding_coherence_ = 1.0;
    
    // Синхронизируем все единицы сознания
    synchronizeConsciousnessUnits();
}

void LubomirUnderstanding::createQuantumUnderstandingEntanglement() {
    std::lock_guard<std::mutex> lock(understanding_mutex_);
    
    // Создаем квантовую запутанность между пониманиями
    if (understanding_history_.size() >= 2) {
        auto& last_understanding = understanding_history_.back();
        auto& prev_understanding = understanding_history_[understanding_history_.size() - 2];
        
        // Синхронизируем квантовую когерентность
        std::complex<double> avg_coherence = (last_understanding.quantum_coherence + prev_understanding.quantum_coherence) / 2.0;
        last_understanding.quantum_coherence = avg_coherence;
        prev_understanding.quantum_coherence = avg_coherence;
    }
}

std::complex<double> LubomirUnderstanding::calculateQuantumCoherence() const {
    std::lock_guard<std::mutex> lock(understanding_mutex_);
    
    if (consciousness_units_.empty()) {
        return std::complex<double>(0.0, 0.0);
    }
    
    // Вычисляем среднюю квантовую когерентность всех единиц сознания
    std::complex<double> total_coherence(0.0, 0.0);
    int valid_units = 0;
    
    for (const auto& unit : consciousness_units_) {
        if (unit) {
            auto state = unit->getCurrentState();
            total_coherence += state.wave_function;
            valid_units++;
        }
    }
    
    if (valid_units > 0) {
        return total_coherence / static_cast<double>(valid_units);
    }
    
    return std::complex<double>(0.0, 0.0);
}

void LubomirUnderstanding::learnFromUnderstanding(const Understanding& understanding) {
    std::lock_guard<std::mutex> lock(understanding_mutex_);
    
    // Обновляем веса концепций на основе нового понимания
    for (const auto& concept : understanding.related_concepts) {
        double current_weight = getConceptWeight(concept);
        double new_weight = current_weight + learning_rate_ * understanding.confidence;
        updateConceptWeight(concept, new_weight);
    }
    
    // Адаптируем параметры системы
    adaptUnderstandingParameters();
}

void LubomirUnderstanding::adaptUnderstandingParameters() {
    // Адаптация параметров на основе истории понимания
    if (understanding_history_.size() > 10) {
        double avg_confidence = 0.0;
        for (const auto& understanding : understanding_history_) {
            avg_confidence += understanding.confidence;
        }
        avg_confidence /= understanding_history_.size();
        
        // Корректируем порог когерентности
        if (avg_confidence > 0.8) {
            coherence_threshold_ = std::min(0.9, coherence_threshold_ + 0.01);
        } else if (avg_confidence < 0.6) {
            coherence_threshold_ = std::max(0.5, coherence_threshold_ - 0.01);
        }
    }
}

void LubomirUnderstanding::cleanup() {
    std::lock_guard<std::mutex> lock(understanding_mutex_);
    
    if (integration_system_) {
        integration_system_->cleanup();
    }
    
    consciousness_units_.clear();
    understanding_history_.clear();
    concept_weights_.clear();
}

void LubomirUnderstanding::updateUnderstandingCoherence() {
    // Обновляем когерентность понимания на основе последних пониманий
    if (understanding_history_.size() >= 3) {
        double total_coherence = 0.0;
        int count = 0;
        
        // Берем последние 3 понимания
        for (size_t i = understanding_history_.size() - 3; i < understanding_history_.size(); ++i) {
            total_coherence += std::abs(understanding_history_[i].quantum_coherence);
            count++;
        }
        
        if (count > 0) {
            understanding_coherence_ = total_coherence / count;
        }
    }
}

void LubomirUnderstanding::processQuantumUnderstanding() {
    // Обработка квантового понимания
    for (auto& understanding : understanding_history_) {
        // Обновляем квантовую когерентность
        understanding.quantum_coherence = calculateQuantumCoherence();
    }
}

std::string LubomirUnderstanding::generateInsight(const std::string& input, UnderstandingLevel level) {
    std::ostringstream insight;
    
    switch (level) {
        case UnderstandingLevel::SURFACE:
            insight << "Поверхностное понимание: " << input << " - это базовое восприятие реальности.";
            break;
        case UnderstandingLevel::DEEP:
            insight << "Глубокое понимание: " << input << " раскрывает скрытые связи и причины.";
            break;
        case UnderstandingLevel::QUANTUM:
            insight << "Квантовое понимание: " << input << " существует в суперпозиции всех возможных интерпретаций.";
            break;
        case UnderstandingLevel::TRANSCENDENT:
            insight << "Трансцендентное понимание: " << input << " выходит за пределы обычного восприятия.";
            break;
        case UnderstandingLevel::UNIFIED:
            insight << "Единое понимание: " << input << " есть проявление единой сущности всего сущего.";
            break;
    }
    
    return insight.str();
}

std::vector<std::string> LubomirUnderstanding::extractRelatedConcepts(const std::string& input) {
    std::vector<std::string> concepts;
    std::string lower_input = input;
    std::transform(lower_input.begin(), lower_input.end(), lower_input.begin(), ::tolower);
    
    // Ищем связанные концепции в весах
    for (const auto& pair : concept_weights_) {
        if (lower_input.find(pair.first) != std::string::npos) {
            concepts.push_back(pair.first);
        }
    }
    
    return concepts;
}

void LubomirUnderstanding::normalizeConceptWeights() {
    // Нормализуем веса концепций
    double total_weight = 0.0;
    for (const auto& pair : concept_weights_) {
        total_weight += pair.second;
    }
    
    if (total_weight > 0.0) {
        for (auto& pair : concept_weights_) {
            pair.second /= total_weight;
        }
    }
}

} // namespace AnantaDigital::Lubomir
