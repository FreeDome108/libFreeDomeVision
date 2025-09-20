#ifndef FORMAT_HANDLER_HPP
#define FORMAT_HANDLER_HPP

#include <string>
#include <vector>
#include <cstring>
#include <algorithm>

namespace FreeDomeVision {

// Типы квантовой геометрии
enum class QuantumGeometryType {
    SPHERICAL = 0,
    TOROIDAL = 1,
    ICOSAHEDRAL = 2,
    FRACTAL = 3,
    HOLOGRAPHIC = 4,
    QUANTUM_LATTICE = 5
};

// Структура для хранения визуальных данных
struct VisualData {
    std::vector<uint8_t> data;
    uint32_t width;
    uint32_t height;
    uint32_t depth;
    uint32_t frameCount;
    float fps;
    
    // Квантовые данные для ZELIM формата
    struct QuantumData {
        uint32_t elementCount;
        QuantumGeometryType geometryType;
        uint32_t quantumStates;
    } quantumData;
    
    // Данные Z-глубины для BORANKO формата
    struct ZDepthData {
        bool enabled;
        float intensity;
        bool quantumStereoscopy;
        std::vector<uint8_t> data;
    } zDepthData;
    
    VisualData() : width(1920), height(1080), depth(0), frameCount(1), fps(30.0f) {
        quantumData.elementCount = 108;
        quantumData.geometryType = QuantumGeometryType::SPHERICAL;
        quantumData.quantumStates = 4;
        
        zDepthData.enabled = false;
        zDepthData.intensity = 0.5f;
        zDepthData.quantumStereoscopy = false;
    }
};

// ZELIM заголовок (3D квантовый визуальный формат)
struct ZELIMHeader {
    char magic[5];          // "ZELIM"
    uint32_t version;       // Версия формата
    uint32_t width;         // Ширина
    uint32_t height;        // Высота
    uint32_t depth;         // Глубина
    uint32_t frameCount;    // Количество кадров
    float fps;             // Кадров в секунду
    uint32_t dataSize;      // Размер визуальных данных
    
    // Квантовые данные
    uint32_t quantumElements; // Количество квантовых элементов
    uint32_t geometryType;    // Тип геометрии
    uint32_t quantumStates;   // Квантовые состояния
};

// BORANKO заголовок (2D графика с Z-глубиной)
struct BORANKOHeader {
    char magic[7];          // "BORANKO"
    uint32_t version;       // Версия формата
    uint32_t width;         // Ширина
    uint32_t height;        // Высота
    uint32_t depth;         // Глубина
    uint32_t frameCount;    // Количество кадров
    float fps;             // Кадров в секунду
    uint32_t dataSize;      // Размер визуальных данных
    
    // Данные Z-глубины
    bool zDepthEnabled;      // Включена ли Z-глубина
    float zDepthIntensity;   // Интенсивность Z-глубины
    bool quantumStereoscopy; // Квантовая стереоскопия
    uint32_t zDepthSize;     // Размер данных Z-глубины
};

class FormatHandler {
public:
    FormatHandler();
    ~FormatHandler();
    
    // Основные методы загрузки и сохранения
    bool loadVisualFile(const std::string& filename, VisualData& visualData);
    bool saveVisualFile(const std::string& filename, const VisualData& visualData);
    
    // Утилиты
    std::string getFileExtension(const std::string& filename);
    std::vector<std::string> getSupportedFormats() const;
    bool isFormatSupported(const std::string& extension) const;
    
private:
    // Методы для конкретных форматов
    bool loadImage(const std::string& filename, VisualData& visualData);
    bool saveImage(const std::string& filename, const VisualData& visualData);
    
    bool loadVideo(const std::string& filename, VisualData& visualData);
    bool saveVideo(const std::string& filename, const VisualData& visualData);
    
    bool loadZELIM(const std::string& filename, VisualData& visualData);
    bool saveZELIM(const std::string& filename, const VisualData& visualData);
    
    bool loadBORANKO(const std::string& filename, VisualData& visualData);
    bool saveBORANKO(const std::string& filename, const VisualData& visualData);
};

} // namespace FreeDomeVision

#endif // FORMAT_HANDLER_HPP
