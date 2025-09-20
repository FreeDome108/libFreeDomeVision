#ifndef GPU_PROCESSOR_HPP
#define GPU_PROCESSOR_HPP

#include "format_handler.hpp"
#include <memory>

namespace FreeDomeVision {

// Типы GPU
enum class GPUType {
    NVIDIA,
    AMD,
    INTEL,
    APPLE,
    SOFTWARE
};

// Режимы обработки
enum class ProcessingMode {
    QUANTUM_INTERFERENCE,    // Квантовая интерференция
    HOLOGRAPHIC_PROJECTION,  // Голографическая проекция
    CONSCIOUSNESS_HYBRID,    // Сознательная гибридная система
    LUBOMIR_UNDERSTANDING    // Понимание Lubomir
};

class GPUProcessor {
public:
    GPUProcessor();
    ~GPUProcessor();
    
    // Инициализация
    bool initialize(GPUType gpuType);
    
    // Основная обработка
    bool processVisual(const VisualData& input, VisualData& output, ProcessingMode mode);
    
    // Специализированная обработка
    bool processQuantumInterference(const VisualData& input, VisualData& output);
    bool processHolographicProjection(const VisualData& input, VisualData& output);
    bool processConsciousnessHybrid(const VisualData& input, VisualData& output);
    bool processLubomirUnderstanding(const VisualData& input, VisualData& output);
    
    // Утилиты
    void cleanup();
    bool isInitialized() const;
    GPUType getGPUType() const;
    
private:
    bool initialized_;
    GPUType gpuType_;
    void* gpuContext_; // Указатель на GPU контекст
    
    // CUDA реализации
    bool processQuantumInterferenceCUDA(const VisualData& input, VisualData& output);
    bool processHolographicProjectionCUDA(const VisualData& input, VisualData& output);
    bool processConsciousnessHybridCUDA(const VisualData& input, VisualData& output);
    bool processLubomirUnderstandingCUDA(const VisualData& input, VisualData& output);
    
    // OpenCL реализации
    bool processQuantumInterferenceOpenCL(const VisualData& input, VisualData& output);
    bool processHolographicProjectionOpenCL(const VisualData& input, VisualData& output);
    bool processConsciousnessHybridOpenCL(const VisualData& input, VisualData& output);
    bool processLubomirUnderstandingOpenCL(const VisualData& input, VisualData& output);
    
    // Metal реализации (macOS)
    bool processQuantumInterferenceMetal(const VisualData& input, VisualData& output);
    bool processHolographicProjectionMetal(const VisualData& input, VisualData& output);
    bool processConsciousnessHybridMetal(const VisualData& input, VisualData& output);
    bool processLubomirUnderstandingMetal(const VisualData& input, VisualData& output);
    
    // Программные реализации (fallback)
    bool processQuantumInterferenceSoftware(const VisualData& input, VisualData& output);
    bool processHolographicProjectionSoftware(const VisualData& input, VisualData& output);
    bool processConsciousnessHybridSoftware(const VisualData& input, VisualData& output);
    bool processLubomirUnderstandingSoftware(const VisualData& input, VisualData& output);
    
    // Инициализация конкретных GPU
    bool initializeCUDA();
    bool initializeOpenCL();
    bool initializeMetal();
    bool initializeSoftware();
};

} // namespace FreeDomeVision

#endif // GPU_PROCESSOR_HPP
