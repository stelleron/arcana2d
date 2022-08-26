#include "audio/Audio.hpp"
#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"

namespace arcana {
    ma_engine engine;
    AudioContext::AudioContext() {
        ma_engine_init(NULL, &engine);
    }

    AudioContext::~AudioContext() {
        ma_engine_uninit(&engine);
    }

    void AudioContext::playSound(const char* soundpath) {
        ma_engine_play_sound(&engine, soundpath, NULL);
    }
}