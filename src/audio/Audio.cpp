#include "audio/Audio.hpp"
#include "utils/Logger.hpp"
#include "res/Filesystem.hpp"
// WAV file loading 
#define DR_WAV_IMPLEMENTATION
#include "dr_wav.h"

namespace arcana {
    AudioContext::AudioContext() {
        // Use result to check that the engine has been initialised
        ma_result result;
        result = ma_engine_init(NULL, &engine);
        if (result != MA_SUCCESS) {
            LOG("Audio: Could not initialise the audio engine!");
            exit(1);
        }
    }

    AudioContext::~AudioContext() {
        ma_engine_uninit(&engine);
    }

    void AudioContext::update() {
        
    }

    Sound::Sound() {
        isInit = false;
    }

    Sound::~Sound() {
        if (isInit) {

        }
    }

    Sound::Sound(const char* path) {
        load(path);
    }
    
    Sound::Sound(unsigned char* data, size_t size, const char* extension) {
        load(data, size, extension);
    }

    void Sound::load(const char* path) {
        size_t fsize;
        unsigned char* data = filesystem::loadFileData(path, fsize);
        std::string extension = filesystem::getFileExtension(path);
        if (extension == "wav" || extension == "mp3")
            load(data, fsize, extension.c_str());
        else 
            LOG("Audio: Sound file not supported!");
        delete[] data;
    }

    void Sound::load(unsigned char* data, size_t size, const char* extension) {
        // First check extension type
        std::string extBuffer = extension;
        drwav wav;

    }
}