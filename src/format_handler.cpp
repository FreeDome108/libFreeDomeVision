#include "format_handler.hpp"
#include <fstream>
#include <iostream>
#include <cstring>

namespace FreeDomeVision {

FormatHandler::FormatHandler() {
    // Инициализация обработчика форматов
}

FormatHandler::~FormatHandler() {
    // Очистка ресурсов
}

bool FormatHandler::loadVisualFile(const std::string& filename, VisualData& visualData) {
    std::string extension = getFileExtension(filename);
    
    if (extension == "png" || extension == "jpg" || extension == "jpeg") {
        return loadImage(filename, visualData);
    } else if (extension == "mp4" || extension == "avi" || extension == "mov") {
        return loadVideo(filename, visualData);
    } else if (extension == "zelim") {
        return loadZELIM(filename, visualData);
    } else if (extension == "boranko") {
        return loadBORANKO(filename, visualData);
    }
    
    return false;
}

bool FormatHandler::saveVisualFile(const std::string& filename, const VisualData& visualData) {
    std::string extension = getFileExtension(filename);
    
    if (extension == "png" || extension == "jpg" || extension == "jpeg") {
        return saveImage(filename, visualData);
    } else if (extension == "mp4" || extension == "avi" || extension == "mov") {
        return saveVideo(filename, visualData);
    } else if (extension == "zelim") {
        return saveZELIM(filename, visualData);
    } else if (extension == "boranko") {
        return saveBORANKO(filename, visualData);
    }
    
    return false;
}

std::string FormatHandler::getFileExtension(const std::string& filename) {
    size_t dotPos = filename.find_last_of('.');
    if (dotPos == std::string::npos) {
        return "";
    }
    
    std::string extension = filename.substr(dotPos + 1);
    std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);
    return extension;
}

bool FormatHandler::loadImage(const std::string& filename, VisualData& visualData) {
    // TODO: Реализовать загрузку изображений через stb_image или аналогичную библиотеку
    // Пока заглушка
    return false;
}

bool FormatHandler::saveImage(const std::string& filename, const VisualData& visualData) {
    // TODO: Реализовать сохранение изображений через stb_image или аналогичную библиотеку
    // Пока заглушка
    return false;
}

bool FormatHandler::loadVideo(const std::string& filename, VisualData& visualData) {
    // TODO: Реализовать загрузку видео через FFmpeg
    // Пока заглушка
    return false;
}

bool FormatHandler::saveVideo(const std::string& filename, const VisualData& visualData) {
    // TODO: Реализовать сохранение видео через FFmpeg
    // Пока заглушка
    return false;
}

bool FormatHandler::loadZELIM(const std::string& filename, VisualData& visualData) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        return false;
    }
    
    // Чтение ZELIM заголовка
    ZELIMHeader header;
    file.read(reinterpret_cast<char*>(&header), sizeof(ZELIMHeader));
    
    // Проверка формата ZELIM
    if (memcmp(header.magic, "ZELIM", 5) != 0) {
        return false;
    }
    
    visualData.width = header.width;
    visualData.height = header.height;
    visualData.depth = header.depth;
    visualData.frameCount = header.frameCount;
    visualData.fps = header.fps;
    
    // Загрузка квантовых данных
    visualData.quantumData.elementCount = header.quantumElements;
    visualData.quantumData.geometryType = static_cast<QuantumGeometryType>(header.geometryType);
    visualData.quantumData.quantumStates = header.quantumStates;
    
    // Чтение визуальных данных
    visualData.data.resize(header.dataSize);
    file.read(reinterpret_cast<char*>(visualData.data.data()), header.dataSize);
    
    return true;
}

bool FormatHandler::saveZELIM(const std::string& filename, const VisualData& visualData) {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        return false;
    }
    
    ZELIMHeader header;
    memcpy(header.magic, "ZELIM", 5);
    header.version = 1;
    header.width = visualData.width;
    header.height = visualData.height;
    header.depth = visualData.depth;
    header.frameCount = visualData.frameCount;
    header.fps = visualData.fps;
    header.dataSize = visualData.data.size();
    
    // Сохранение квантовых данных
    header.quantumElements = visualData.quantumData.elementCount;
    header.geometryType = static_cast<uint32_t>(visualData.quantumData.geometryType);
    header.quantumStates = visualData.quantumData.quantumStates;
    
    file.write(reinterpret_cast<const char*>(&header), sizeof(ZELIMHeader));
    file.write(reinterpret_cast<const char*>(visualData.data.data()), visualData.data.size());
    
    return true;
}

bool FormatHandler::loadBORANKO(const std::string& filename, VisualData& visualData) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        return false;
    }
    
    // Чтение BORANKO заголовка
    BORANKOHeader header;
    file.read(reinterpret_cast<char*>(&header), sizeof(BORANKOHeader));
    
    // Проверка формата BORANKO
    if (memcmp(header.magic, "BORANKO", 7) != 0) {
        return false;
    }
    
    visualData.width = header.width;
    visualData.height = header.height;
    visualData.depth = header.depth;
    visualData.frameCount = header.frameCount;
    visualData.fps = header.fps;
    
    // Загрузка данных Z-глубины
    visualData.zDepthData.enabled = header.zDepthEnabled;
    visualData.zDepthData.intensity = header.zDepthIntensity;
    visualData.zDepthData.quantumStereoscopy = header.quantumStereoscopy;
    
    // Чтение визуальных данных
    visualData.data.resize(header.dataSize);
    file.read(reinterpret_cast<char*>(visualData.data.data()), header.dataSize);
    
    // Чтение данных Z-глубины если включены
    if (visualData.zDepthData.enabled) {
        visualData.zDepthData.data.resize(header.zDepthSize);
        file.read(reinterpret_cast<char*>(visualData.zDepthData.data.data()), header.zDepthSize);
    }
    
    return true;
}

bool FormatHandler::saveBORANKO(const std::string& filename, const VisualData& visualData) {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        return false;
    }
    
    BORANKOHeader header;
    memcpy(header.magic, "BORANKO", 7);
    header.version = 1;
    header.width = visualData.width;
    header.height = visualData.height;
    header.depth = visualData.depth;
    header.frameCount = visualData.frameCount;
    header.fps = visualData.fps;
    header.dataSize = visualData.data.size();
    
    // Сохранение данных Z-глубины
    header.zDepthEnabled = visualData.zDepthData.enabled;
    header.zDepthIntensity = visualData.zDepthData.intensity;
    header.quantumStereoscopy = visualData.zDepthData.quantumStereoscopy;
    header.zDepthSize = visualData.zDepthData.enabled ? visualData.zDepthData.data.size() : 0;
    
    file.write(reinterpret_cast<const char*>(&header), sizeof(BORANKOHeader));
    file.write(reinterpret_cast<const char*>(visualData.data.data()), visualData.data.size());
    
    // Сохранение данных Z-глубины если включены
    if (visualData.zDepthData.enabled) {
        file.write(reinterpret_cast<const char*>(visualData.zDepthData.data.data()), visualData.zDepthData.data.size());
    }
    
    return true;
}

std::vector<std::string> FormatHandler::getSupportedFormats() const {
    return {"png", "jpg", "jpeg", "mp4", "avi", "mov", "zelim", "boranko"};
}

bool FormatHandler::isFormatSupported(const std::string& extension) const {
    auto supportedFormats = getSupportedFormats();
    std::string lowerExt = extension;
    std::transform(lowerExt.begin(), lowerExt.end(), lowerExt.begin(), ::tolower);
    
    return std::find(supportedFormats.begin(), supportedFormats.end(), lowerExt) != supportedFormats.end();
}

} // namespace FreeDomeVision
