#include "format_handler.hpp"
#include "gpu_processor.hpp"
#include <iostream>
#include <string>

using namespace FreeDomeVision;

int main() {
    std::cout << "=== FreeDomeVision Format & GPU Demo ===" << std::endl;
    
    // Создание обработчика форматов
    FormatHandler formatHandler;
    
    // Получение поддерживаемых форматов
    auto supportedFormats = formatHandler.getSupportedFormats();
    std::cout << "Поддерживаемые форматы: ";
    for (const auto& format : supportedFormats) {
        std::cout << format << " ";
    }
    std::cout << std::endl;
    
    // Создание тестовых визуальных данных
    VisualData testVisual;
    testVisual.width = 1920;
    testVisual.height = 1080;
    testVisual.depth = 0;
    testVisual.frameCount = 1;
    testVisual.fps = 30.0f;
    
    // Установка квантовых данных для ZELIM
    testVisual.quantumData.elementCount = 108;
    testVisual.quantumData.geometryType = QuantumGeometryType::SPHERICAL;
    testVisual.quantumData.quantumStates = 4;
    
    // Установка данных Z-глубины для BORANKO
    testVisual.zDepthData.enabled = true;
    testVisual.zDepthData.intensity = 0.8f;
    testVisual.zDepthData.quantumStereoscopy = true;
    
    // Создание тестовых визуальных данных (градиент)
    size_t dataSize = testVisual.width * testVisual.height * 3; // RGB
    testVisual.data.resize(dataSize);
    
    // Заполнение градиентом
    for (uint32_t y = 0; y < testVisual.height; ++y) {
        for (uint32_t x = 0; x < testVisual.width; ++x) {
            size_t index = (y * testVisual.width + x) * 3;
            
            // RGB градиент
            testVisual.data[index] = static_cast<uint8_t>((x * 255) / testVisual.width);     // R
            testVisual.data[index + 1] = static_cast<uint8_t>((y * 255) / testVisual.height); // G
            testVisual.data[index + 2] = static_cast<uint8_t>((x + y) * 255) / (testVisual.width + testVisual.height); // B
        }
    }
    
    // Создание данных Z-глубины
    if (testVisual.zDepthData.enabled) {
        size_t zDataSize = testVisual.width * testVisual.height;
        testVisual.zDepthData.data.resize(zDataSize);
        
        for (uint32_t y = 0; y < testVisual.height; ++y) {
            for (uint32_t x = 0; x < testVisual.width; ++x) {
                size_t index = y * testVisual.width + x;
                // Z-глубина как расстояние от центра
                float centerX = testVisual.width / 2.0f;
                float centerY = testVisual.height / 2.0f;
                float distance = sqrt((x - centerX) * (x - centerX) + (y - centerY) * (y - centerY));
                float maxDistance = sqrt(centerX * centerX + centerY * centerY);
                testVisual.zDepthData.data[index] = static_cast<uint8_t>(255 * (1.0f - distance / maxDistance));
            }
        }
    }
    
    // Сохранение в различных форматах
    std::cout << "\n--- Сохранение визуальных файлов ---" << std::endl;
    
    if (formatHandler.saveVisualFile("test.zelim", testVisual)) {
        std::cout << "✓ ZELIM файл сохранен" << std::endl;
    } else {
        std::cout << "✗ Ошибка сохранения ZELIM файла" << std::endl;
    }
    
    if (formatHandler.saveVisualFile("test.boranko", testVisual)) {
        std::cout << "✓ BORANKO файл сохранен" << std::endl;
    } else {
        std::cout << "✗ Ошибка сохранения BORANKO файла" << std::endl;
    }
    
    // Загрузка визуальных файлов
    std::cout << "\n--- Загрузка визуальных файлов ---" << std::endl;
    
    VisualData loadedVisual;
    if (formatHandler.loadVisualFile("test.zelim", loadedVisual)) {
        std::cout << "✓ ZELIM файл загружен" << std::endl;
        std::cout << "  Разрешение: " << loadedVisual.width << "x" << loadedVisual.height << std::endl;
        std::cout << "  Квантовые элементы: " << loadedVisual.quantumData.elementCount << std::endl;
        std::cout << "  Тип геометрии: ";
        switch (loadedVisual.quantumData.geometryType) {
            case QuantumGeometryType::SPHERICAL: std::cout << "Сферическая"; break;
            case QuantumGeometryType::TOROIDAL: std::cout << "Тороидальная"; break;
            case QuantumGeometryType::ICOSAHEDRAL: std::cout << "Икосаэдрическая"; break;
            case QuantumGeometryType::FRACTAL: std::cout << "Фрактальная"; break;
            case QuantumGeometryType::HOLOGRAPHIC: std::cout << "Голографическая"; break;
            case QuantumGeometryType::QUANTUM_LATTICE: std::cout << "Квантовая решетка"; break;
        }
        std::cout << std::endl;
        std::cout << "  Квантовые состояния: " << loadedVisual.quantumData.quantumStates << std::endl;
    } else {
        std::cout << "✗ Ошибка загрузки ZELIM файла" << std::endl;
    }
    
    if (formatHandler.loadVisualFile("test.boranko", loadedVisual)) {
        std::cout << "✓ BORANKO файл загружен" << std::endl;
        std::cout << "  Разрешение: " << loadedVisual.width << "x" << loadedVisual.height << std::endl;
        std::cout << "  Z-глубина включена: " << (loadedVisual.zDepthData.enabled ? "Да" : "Нет") << std::endl;
        if (loadedVisual.zDepthData.enabled) {
            std::cout << "  Интенсивность Z-глубины: " << loadedVisual.zDepthData.intensity << std::endl;
            std::cout << "  Квантовая стереоскопия: " << (loadedVisual.zDepthData.quantumStereoscopy ? "Да" : "Нет") << std::endl;
        }
    } else {
        std::cout << "✗ Ошибка загрузки BORANKO файла" << std::endl;
    }
    
    // GPU обработка
    std::cout << "\n--- GPU обработка ---" << std::endl;
    
    GPUProcessor gpuProcessor;
    
    // Попытка инициализации различных GPU
    std::vector<GPUType> gpuTypes = {
        GPUType::NVIDIA,
        GPUType::AMD,
        GPUType::INTEL,
        GPUType::APPLE,
        GPUType::SOFTWARE
    };
    
    bool gpuInitialized = false;
    for (const auto& gpuType : gpuTypes) {
        if (gpuProcessor.initialize(gpuType)) {
            std::cout << "✓ GPU инициализирован: ";
            switch (gpuType) {
                case GPUType::NVIDIA: std::cout << "NVIDIA"; break;
                case GPUType::AMD: std::cout << "AMD"; break;
                case GPUType::INTEL: std::cout << "Intel"; break;
                case GPUType::APPLE: std::cout << "Apple"; break;
                case GPUType::SOFTWARE: std::cout << "Software"; break;
            }
            std::cout << std::endl;
            gpuInitialized = true;
            break;
        }
    }
    
    if (!gpuInitialized) {
        std::cout << "✗ Не удалось инициализировать GPU" << std::endl;
        return 1;
    }
    
    // Тестирование различных режимов обработки
    std::cout << "\n--- Тестирование режимов обработки ---" << std::endl;
    
    VisualData processedVisual;
    std::vector<ProcessingMode> processingModes = {
        ProcessingMode::QUANTUM_INTERFERENCE,
        ProcessingMode::HOLOGRAPHIC_PROJECTION,
        ProcessingMode::CONSCIOUSNESS_HYBRID,
        ProcessingMode::LUBOMIR_UNDERSTANDING
    };
    
    for (const auto& mode : processingModes) {
        if (gpuProcessor.processVisual(testVisual, processedVisual, mode)) {
            std::cout << "✓ Обработка завершена: ";
            switch (mode) {
                case ProcessingMode::QUANTUM_INTERFERENCE:
                    std::cout << "Квантовая интерференция"; break;
                case ProcessingMode::HOLOGRAPHIC_PROJECTION:
                    std::cout << "Голографическая проекция"; break;
                case ProcessingMode::CONSCIOUSNESS_HYBRID:
                    std::cout << "Сознательная гибридная система"; break;
                case ProcessingMode::LUBOMIR_UNDERSTANDING:
                    std::cout << "Понимание Lubomir"; break;
            }
            std::cout << std::endl;
        } else {
            std::cout << "✗ Ошибка обработки" << std::endl;
        }
    }
    
    // Сохранение обработанного визуального контента
    if (formatHandler.saveVisualFile("processed.zelim", processedVisual)) {
        std::cout << "✓ Обработанный визуальный контент сохранен в processed.zelim" << std::endl;
    }
    
    std::cout << "\n=== Демо завершено ===" << std::endl;
    return 0;
}
