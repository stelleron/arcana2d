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
        ma_context context;
    };

    InternalAudioEngine aEngine;

    // Callback for logging messages
    void audioLogCallback(void *pUserData, ma_uint32 level, const char *pMessage) {
        logger << "Audio(Internal): " << pMessage << endMessage;
    }


    // Audio context impl.
    void AudioContext::init() {
        ma_context_config ctxConfig = ma_context_config_init();
        ma_log_callback_init(audioLogCallback, NULL);   
    }

    void AudioContext::play() {
        
    }
}