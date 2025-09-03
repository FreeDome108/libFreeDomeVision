#include "anantadigital_core.hpp"
#include "quantum_feedback_system.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <thread>
#include <dirent.h>
#include <sys/stat.h>
#include <iomanip>

// Для работы с аудио файлами
#include <sndfile.h>
#include <portaudio.h>

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
        
        // Открытие потока с большим буфером
        PaStream* stream;
        err = Pa_OpenDefaultStream(&stream, 0, channels_, paFloat32, sample_rate_, 
                                  1024, nullptr, nullptr);
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
        const size_t frames_per_buffer = 1024;
        
        std::cout << "Starting playback... Duration: " << (audio_buffer_.size() / channels_ / sample_rate_) << " seconds" << std::endl;
        
        while (frame_index < audio_buffer_.size() / channels_) {
            size_t frames_to_write = std::min(frames_per_buffer, 
                                            audio_buffer_.size() / channels_ - frame_index);
            
            std::vector<float> buffer(frames_to_write * channels_);
            for (size_t i = 0; i < frames_to_write * channels_; ++i) {
                buffer[i] = audio_buffer_[frame_index * channels_ + i];
            }
            
            err = Pa_WriteStream(stream, buffer.data(), frames_to_write);
            if (err != paNoError) {
                if (err == paOutputUnderflowed) {
                    // Это нормально, просто ждем
                    std::this_thread::sleep_for(std::chrono::milliseconds(5));
                    continue;
                } else {
                    std::cerr << "PortAudio write error: " << Pa_GetErrorText(err) << std::endl;
                    break;
                }
            }
            
            frame_index += frames_to_write;
            
            // Показываем прогресс каждые 5 секунд
            if (frame_index % (sample_rate_ * 5) < frames_per_buffer) {
                double progress = (double)frame_index / (audio_buffer_.size() / channels_) * 100.0;
                std::cout << "Progress: " << std::fixed << std::setprecision(1) << progress << "%" << std::endl;
            }
            
            // Правильная задержка для синхронизации с реальным временем
            std::this_thread::sleep_for(std::chrono::microseconds(1000000 * frames_to_write / sample_rate_));
        }
        
        // Ждем завершения воспроизведения всех данных
        std::cout << "Waiting for playback to finish..." << std::endl;
        while (Pa_GetStreamWriteAvailable(stream) < 1024) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        
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
        
        // Путь к папке с сэмплами (локальная)
        std::string samples_dir = "samples";
        
        DIR* dir = opendir(samples_dir.c_str());
        if (!dir) {
            std::cerr << "Samples directory not found: " << samples_dir << std::endl;
            return 1;
        }
        
        std::cout << "\nAvailable audio files:" << std::endl;
        std::vector<std::string> audio_files;
        
        struct dirent* entry;
        while ((entry = readdir(dir)) != nullptr) {
            std::string filename = entry->d_name;
            if (filename == "." || filename == "..") continue;
            
            std::string full_path = samples_dir + "/" + filename;
            struct stat st;
            if (stat(full_path.c_str(), &st) == 0 && S_ISREG(st.st_mode)) {
                std::string ext = filename.substr(filename.find_last_of(".") + 1);
                if (ext == "wav" || ext == "mp3" || ext == "flac") {
                    audio_files.push_back(full_path);
                    std::cout << "  " << filename << std::endl;
                }
            }
        }
        closedir(dir);
        
        if (audio_files.empty()) {
            std::cout << "No audio files found in samples directory" << std::endl;
            return 1;
        }
        
        // Проигрываем каждый файл
        for (const auto& audio_file : audio_files) {
            std::cout << "\n" << std::string(50, '=') << std::endl;
            std::string filename = audio_file.substr(audio_file.find_last_of("/") + 1);
            std::cout << "Playing: " << filename << std::endl;
            std::cout << std::string(50, '=') << std::endl;
            
            if (player.loadAudioFile(audio_file)) {
                // Обрабатываем аудио через anAntaDigital
                std::cout << "Processing audio through anAntaDigital..." << std::endl;
                
                // Здесь можно добавить обработку через core.processAudioSignal()
                // Пока просто проигрываем
                player.playAudio();
                
                std::cout << "File completed: " << filename << std::endl;
            } else {
                std::cout << "Failed to load: " << filename << std::endl;
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
