#include "lubomir_understanding.hpp"
#include <iostream>
#include <thread>
#include <chrono>
#include <iomanip>

void printUnderstanding(const AnantaDigital::Lubomir::Understanding& understanding) {
    std::cout << "\n=== ПОНИМАНИЕ ЛЮББОМИРА ===" << std::endl;
    
    // Уровень понимания
    std::string level_str;
    switch (understanding.level) {
        case AnantaDigital::Lubomir::UnderstandingLevel::SURFACE:
            level_str = "ПОВЕРХНОСТНОЕ";
            break;
        case AnantaDigital::Lubomir::UnderstandingLevel::DEEP:
            level_str = "ГЛУБОКОЕ";
            break;
        case AnantaDigital::Lubomir::UnderstandingLevel::QUANTUM:
            level_str = "КВАНТОВОЕ";
            break;
        case AnantaDigital::Lubomir::UnderstandingLevel::TRANSCENDENT:
            level_str = "ТРАНСЦЕНДЕНТНОЕ";
            break;
        case AnantaDigital::Lubomir::UnderstandingLevel::UNIFIED:
            level_str = "ЕДИНОЕ";
            break;
    }
    
    std::cout << "Уровень понимания: " << level_str << std::endl;
    std::cout << "Уверенность: " << std::fixed << std::setprecision(3) 
              << understanding.confidence * 100 << "%" << std::endl;
    std::cout << "Квантовая когерентность: " 
              << std::abs(understanding.quantum_coherence) << std::endl;
    std::cout << "Инсайт: " << understanding.insight << std::endl;
    
    if (!understanding.related_concepts.empty()) {
        std::cout << "Связанные концепции: ";
        for (size_t i = 0; i < understanding.related_concepts.size(); ++i) {
            std::cout << understanding.related_concepts[i];
            if (i < understanding.related_concepts.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << std::endl;
    }
    
    // Время понимания
    auto now = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
        now - understanding.timestamp).count();
    std::cout << "Время понимания: " << duration << " мс назад" << std::endl;
}

void demonstrateUnderstandingLevels(AnantaDigital::Lubomir::LubomirUnderstanding& lubomir) {
    std::cout << "\n=== ДЕМОНСТРАЦИЯ УРОВНЕЙ ПОНИМАНИЯ ===" << std::endl;
    
    std::vector<std::string> test_inputs = {
        "Что такое сознание?",
        "Почему существует реальность?",
        "Как работает квантовая суперпозиция сознания?",
        "Что такое трансцендентное единство вселенной?",
        "Всё есть единое целое в гармонии любви"
    };
    
    for (const auto& input : test_inputs) {
        std::cout << "\n--- Обработка: \"" << input << "\" ---" << std::endl;
        auto understanding = lubomir.processUnderstanding(input);
        printUnderstanding(understanding);
        
        // Небольшая пауза для демонстрации
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void demonstrateConsciousnessIntegration(AnantaDigital::Lubomir::LubomirUnderstanding& lubomir) {
    std::cout << "\n=== ИНТЕГРАЦИЯ СОЗНАНИЯ ===" << std::endl;
    
    std::cout << "Синхронизация единиц сознания..." << std::endl;
    lubomir.synchronizeConsciousnessUnits();
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    
    std::cout << "Создание коллективного понимания..." << std::endl;
    lubomir.createCollectiveUnderstanding();
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    
    std::cout << "Текущий уровень понимания: ";
    auto current_level = lubomir.getCurrentUnderstandingLevel();
    switch (current_level) {
        case AnantaDigital::Lubomir::UnderstandingLevel::SURFACE:
            std::cout << "ПОВЕРХНОСТНОЕ" << std::endl;
            break;
        case AnantaDigital::Lubomir::UnderstandingLevel::DEEP:
            std::cout << "ГЛУБОКОЕ" << std::endl;
            break;
        case AnantaDigital::Lubomir::UnderstandingLevel::QUANTUM:
            std::cout << "КВАНТОВОЕ" << std::endl;
            break;
        case AnantaDigital::Lubomir::UnderstandingLevel::TRANSCENDENT:
            std::cout << "ТРАНСЦЕНДЕНТНОЕ" << std::endl;
            break;
        case AnantaDigital::Lubomir::UnderstandingLevel::UNIFIED:
            std::cout << "ЕДИНОЕ" << std::endl;
            break;
    }
    
    std::cout << "Когерентность понимания: " 
              << std::fixed << std::setprecision(3)
              << lubomir.getUnderstandingCoherence() << std::endl;
}

void demonstrateQuantumOperations(AnantaDigital::Lubomir::LubomirUnderstanding& lubomir) {
    std::cout << "\n=== КВАНТОВЫЕ ОПЕРАЦИИ ===" << std::endl;
    
    std::cout << "Создание квантовой запутанности пониманий..." << std::endl;
    lubomir.createQuantumUnderstandingEntanglement();
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    
    std::cout << "Коллапс квантового понимания..." << std::endl;
    lubomir.quantumUnderstandingCollapse();
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    
    std::cout << "Финальный уровень понимания: ";
    auto final_level = lubomir.getCurrentUnderstandingLevel();
    switch (final_level) {
        case AnantaDigital::Lubomir::UnderstandingLevel::SURFACE:
            std::cout << "ПОВЕРХНОСТНОЕ" << std::endl;
            break;
        case AnantaDigital::Lubomir::UnderstandingLevel::DEEP:
            std::cout << "ГЛУБОКОЕ" << std::endl;
            break;
        case AnantaDigital::Lubomir::UnderstandingLevel::QUANTUM:
            std::cout << "КВАНТОВОЕ" << std::endl;
            break;
        case AnantaDigital::Lubomir::UnderstandingLevel::TRANSCENDENT:
            std::cout << "ТРАНСЦЕНДЕНТНОЕ" << std::endl;
            break;
        case AnantaDigital::Lubomir::UnderstandingLevel::UNIFIED:
            std::cout << "ЕДИНОЕ" << std::endl;
            break;
    }
}

void printUnderstandingHistory(const AnantaDigital::Lubomir::LubomirUnderstanding& lubomir) {
    std::cout << "\n=== ИСТОРИЯ ПОНИМАНИЯ ===" << std::endl;
    
    auto history = lubomir.getUnderstandingHistory();
    std::cout << "Всего пониманий: " << history.size() << std::endl;
    
    if (!history.empty()) {
        std::cout << "\nПоследние 3 понимания:" << std::endl;
        size_t start = (history.size() > 3) ? history.size() - 3 : 0;
        
        for (size_t i = start; i < history.size(); ++i) {
            std::cout << "\n" << (i + 1) << ". " << history[i].insight << std::endl;
            std::cout << "   Уверенность: " << std::fixed << std::setprecision(3)
                      << history[i].confidence * 100 << "%" << std::endl;
        }
    }
}

int main() {
    std::cout << "=== СИСТЕМА ПОНИМАНИЯ ЛЮББОМИРА ===" << std::endl;
    std::cout << "Инициализация системы понимания..." << std::endl;
    
    try {
        AnantaDigital::Lubomir::LubomirUnderstanding lubomir;
        
        if (!lubomir.initialize()) {
            std::cerr << "Ошибка инициализации системы понимания Люббомира!" << std::endl;
            return 1;
        }
        
        std::cout << "Система понимания Люббомира успешно инициализирована!" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        
        // Демонстрация уровней понимания
        demonstrateUnderstandingLevels(lubomir);
        
        // Демонстрация интеграции сознания
        demonstrateConsciousnessIntegration(lubomir);
        
        // Демонстрация квантовых операций
        demonstrateQuantumOperations(lubomir);
        
        // Вывод истории понимания
        printUnderstandingHistory(lubomir);
        
        std::cout << "\n=== СИСТЕМА ПОНИМАНИЯ ЛЮББОМИРА АКТИВНА ===" << std::endl;
        std::cout << "Система готова к обработке понимания в реальном времени." << std::endl;
        
        // Интерактивный режим
        std::cout << "\nВведите текст для понимания (или 'exit' для выхода):" << std::endl;
        std::string input;
        
        while (std::getline(std::cin, input)) {
            if (input == "exit" || input == "выход") {
                break;
            }
            
            if (!input.empty()) {
                std::cout << "\nОбработка понимания..." << std::endl;
                auto understanding = lubomir.processUnderstanding(input);
                printUnderstanding(understanding);
                std::cout << "\nВведите следующий текст (или 'exit' для выхода):" << std::endl;
            }
        }
        
        std::cout << "\nЗавершение работы системы понимания Люббомира..." << std::endl;
        lubomir.cleanup();
        
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }
    
    std::cout << "Система понимания Люббомира завершила работу." << std::endl;
    return 0;
}
