#include "audio/Audio.hpp"

// Includes
#ifdef __APPLE__
    #define MA_NO_RUNTIME_LINKING
#endif
#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"

#include "utils/Logger.hpp"

ma_result result;
ma_engine engine;

namespace arcana {
    void AudioContext::init() {
        ma_engine_init(NULL, &engine);
        if (result != MA_SUCCESS) {
            LOG("Audio: Failed to initialise the audio engine!");
        }
        else {
            LOG("Audio: Initialised the audio engine");
        }
    }

    void AudioContext::play() {
        ma_engine_play_sound(&engine, "/Users/donti/Desktop/stelleron/arcana2d/cache/pickupCoin.wav", NULL);
    }
}