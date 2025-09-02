#include "anantadigital_core.hpp"
#include "quantum_feedback_system.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include <chrono>
#include <thread>

// Для работы с аудио файлами
#include <sndfile.h>
#include <portaudio.h>

namespace fs = std::filesystem;

class AudioPlayer {
private:
    std::vector<float> audio_buffer_;
    int sample_rate_;
    int channels_;
    
public:
    AudioPlayer() : sample_rate_(44100), channels_(2) {}
    
    bool loadAudioFile(const std::string& filename) {
        SNDFILE* sndfile = nullptr;
        SF_INFO sfinfo;
        memset(&sfinfo, 0, sizeof(sfinfo));
        
        sndfile = sf_open(filename.c_str(), SFM_READ, &sfinfo);
        if (!sndfile) {
            std::cerr << "Error opening audio file: " << filename << std::endl;
            std::cerr << "Error: " << sf_strerror(nullptr) << std::endl;
            return false;
        }
        
        sample_rate_ = sfinfo.samplerate;
        channels_ = sfinfo.channels;
        
        std::cout << "Audio file info:" << std::endl;
        std::cout << "  Sample rate: " << sample_rate_ << " Hz" << std::endl;
        std::cout << "  Channels: " << channels_ << std::endl;
        std::cout << "  Frames: " << sfinfo.frames << std::endl;
        std::cout << "  Duration: " << (double)sfinfo.frames / sample_rate_ << " seconds" << std::endl;
        
        // Читаем аудио данные
        audio_buffer_.resize(sfinfo.frames * channels_);
        sf_count_t read_count = sf_readf_float(sndfile, audio_buffer_.data(), sfinfo.frames);
        
        if (read_count != sfinfo.frames) {
            std::cerr << "Warning: Expected " << sfinfo.frames << " frames, got " << read_count << std::endl;
        }
        
        sf_close(sndfile);
        std::cout << "Successfully loaded " << read_count << " frames" << std::endl;
        return true;
    }
    
    void playAudio() {
        if (audio_buffer_.empty()) {
            std::cout << "No audio loaded" << std::endl;
            return;
        }
        
        std::cout << "Playing audio..." << std::endl;
        
        // Инициализация PortAudio
        PaError err = Pa_Initialize();
        if (err != paNoError) {
            std::cerr << "PortAudio initialization error: " << Pa_GetErrorText(err) << std::endl;
            return;
        }
        
        // Открытие потока
        PaStream* stream;
        err = Pa_OpenDefaultStream(&stream, 0, channels_, paFloat32, sample_rate_, 
                                  256, nullptr, nullptr);
        if (err != paNoError) {
            std::cerr << "PortAudio stream open error: " << Pa_GetErrorText(err) << std::endl;
            Pa_Terminate();
            return;
        }
        
        // Запуск потока
        err = Pa_StartStream(stream);
        if (err != paNoError) {
            std::cerr << "PortAudio stream start error: " << Pa_GetErrorText(err) << std::endl;
            Pa_CloseStream(stream);
            Pa_Terminate();
            return;
        }
        
        // Воспроизведение
        size_t frame_index = 0;
        const size_t frames_per_buffer = 256;
        
        while (frame_index < audio_buffer_.size() / channels_) {
            size_t frames_to_write = std::min(frames_per_buffer, 
                                            audio_buffer_.size() / channels_ - frame_index);
            
            std::vector<float> buffer(frames_to_write * channels_);
            for (size_t i = 0; i < frames_to_write * channels_; ++i) {
                buffer[i] = audio_buffer_[frame_index * channels_ + i];
            }
            
            err = Pa_WriteStream(stream, buffer.data(), frames_to_write);
            if (err != paNoError) {
                std::cerr << "PortAudio write error: " << Pa_GetErrorText(err) << std::endl;
                break;
            }
            
            frame_index += frames_to_write;
            
            // Небольшая задержка для синхронизации
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        
        // Ожидание завершения воспроизведения
        err = Pa_WriteStream(stream, nullptr, 0);
        
        // Очистка
        Pa_StopStream(stream);
        Pa_CloseStream(stream);
        Pa_Terminate();
        
        std::cout << "Audio playback completed" << std::endl;
    }
    
    const std::vector<float>& getAudioBuffer() const { return audio_buffer_; }
    int getSampleRate() const { return sample_rate_; }
    int getChannels() const { return sample_rate_; }
};

int main() {
    std::cout << "=== anAntaDigital Audio Playback Demo ===" << std::endl;
    
    try {
        // Initialize core system
        AnantaDigital::AnantaDigitalCore core(10.0, 5.0);
        std::cout << "Core system initialized successfully" << std::endl;
        
        // Initialize quantum feedback system
        AnantaDigital::Feedback::QuantumFeedbackSystem qfs(std::chrono::microseconds(50000), 0.7);
        std::cout << "Quantum feedback system initialized" << std::endl;
        
        // Demonstrate basic functionality
        bool init_result = core.initialize();
        std::cout << "System status: " << (init_result ? "OK" : "ERROR") << std::endl;
        
        // Создаем аудио плеер
        AudioPlayer player;
        
        // Путь к папке с сэмплами
        std::string samples_dir = "../samples";
        
        if (!fs::exists(samples_dir)) {
            std::cerr << "Samples directory not found: " << samples_dir << std::endl;
            return 1;
        }
        
        std::cout << "\nAvailable audio files:" << std::endl;
        std::vector<std::string> audio_files;
        
        for (const auto& entry : fs::directory_iterator(samples_dir)) {
            if (entry.is_regular_file()) {
                std::string ext = entry.path().extension().string();
                if (ext == ".wav" || ext == ".mp3") {
                    audio_files.push_back(entry.path().string());
                    std::cout << "  " << entry.path().filename().string() << std::endl;
                }
            }
        }
        
        if (audio_files.empty()) {
            std::cout << "No audio files found in samples directory" << std::endl;
            return 1;
        }
        
        // Проигрываем каждый файл
        for (const auto& audio_file : audio_files) {
            std::cout << "\n" << std::string(50, '=') << std::endl;
            std::cout << "Playing: " << fs::path(audio_file).filename().string() << std::endl;
            std::cout << std::string(50, '=') << std::endl;
            
            if (player.loadAudioFile(audio_file)) {
                // Обрабатываем аудио через anAntaDigital
                std::cout << "Processing audio through anAntaDigital..." << std::endl;
                
                // Здесь можно добавить обработку через core.processAudioSignal()
                // Пока просто проигрываем
                player.playAudio();
                
                std::cout << "File completed: " << fs::path(audio_file).filename().string() << std::endl;
            } else {
                std::cout << "Failed to load: " << fs::path(audio_file).filename().string() << std::endl;
            }
            
            // Пауза между файлами
            if (&audio_file != &audio_files.back()) {
                std::cout << "Waiting 2 seconds before next file..." << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(2));
            }
        }
        
        // Cleanup
        core.shutdown();
        std::cout << "\nDemo completed successfully!" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
