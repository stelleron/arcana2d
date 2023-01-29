#include "audio/Audio.hpp"

// Includes
#ifdef __APPLE__
    #define MA_NO_RUNTIME_LINKING
#endif

#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"
#define DR_WAV_IMPLEMENTATION
#include "dr_wav.h"
#define DR_FLAC_IMPLEMENTATION
#define DR_FLAC_NO_WIN32_IO
#include "dr_flac.h"
#define DR_MP3_IMPLEMENTATION
#include "dr_mp3.h"


#include "utils/Logger.hpp"

namespace arcana {
    // Code for defining and creating an internal audio engine
    struct InternalAudioEngine {
        ma_result result;
        ma_engine engine;
    };

    InternalAudioEngine aEngine;


    // Audio context impl.
    void AudioContext::init() {
        ma_engine_init(NULL, &aEngine.engine);
        if (aEngine.result != MA_SUCCESS) {
            LOG("Audio: Failed to initialise the audio engine!");
        }
        else {
            LOG("Audio: Initialised the audio engine");
        }
    }

    void AudioContext::play() {
        ma_engine_play_sound(&aEngine.engine, "/Users/donti/Desktop/stelleron/arcana2d/cache/pickupCoin.wav", NULL);
    }
}