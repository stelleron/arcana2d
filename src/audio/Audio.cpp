#include "audio/Audio.hpp"
#include "utils/Logger.hpp"

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

    }
}