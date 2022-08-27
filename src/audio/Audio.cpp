#include "audio/Audio.hpp"
#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"
#include "utils/Logger.hpp"

namespace arcana {
    ma_engine engine;
    ma_result result;
    AudioContext::AudioContext() {
        result = ma_engine_init(NULL, &engine);
        if (result != MA_SUCCESS) {
            LOG("Failed to initialize audio engine.");
        }
    }

    AudioContext::~AudioContext() {
        ma_engine_uninit(&engine);
    }

    void AudioContext::playSound(const char* soundpath) {
        ma_engine_play_sound(&engine, soundpath, NULL);
    }
}