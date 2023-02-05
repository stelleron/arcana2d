#include "res/Filesystem.hpp"
#include "audio/Audio.hpp"
#include "string.h"

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
#define STB_VORBIS_IMPLEMENTATION
#include "stb_vorbis.h"


#include "utils/Logger.hpp"

namespace arcana {

    // Code for defining and creating an internal audio engine
    struct InternalAudioEngine {
        ma_context context;
        ma_device device;
        ma_mutex mutex;
        bool isActive;

        InternalAudioEngine() {
            isActive = false;
        }

        ~InternalAudioEngine() {
            // For automatically de-initialising the audio engine if it was ever initialised
            if (isActive) {
                ma_mutex_uninit(&mutex);
                ma_device_uninit(&device);
                ma_context_uninit(&context);
            }
            LOG("Audio: Disposed audio engine!");
        }
    };

    InternalAudioEngine aEngine;

    // Callback for logging messages
    void audioLogCallback(void *pUserData, ma_uint32 level, const char *pMessage) {
        logger << "Audio(Internal): " << pMessage << endMessage;
    }

    // Callback for audio data
    void audioDataCallback(ma_device *pDevice, void *pFramesOut, const void *pFramesInput, ma_uint32 frameCount) {

    }


    // Audio context impl.
    void AudioContext::init() {
        // Initialise the audio context
        ma_context_config ctxConfig = ma_context_config_init();
        ma_log_callback_init(audioLogCallback, NULL);   
        ma_result result = ma_context_init(NULL, 0, &ctxConfig, &aEngine.context);
        if (result != MA_SUCCESS)
        {
            ERROR("Audio: Failed to initialize context");
            return;
        }

        // Then the device
        ma_device_config config = ma_device_config_init(ma_device_type_playback);
        config.dataCallback = audioDataCallback;
        config.playback.pDeviceID = NULL;
        

        result = ma_device_init(&aEngine.context, &config, &aEngine.device);
        if (result != MA_SUCCESS)
        {
            ERROR("Audio: Failed to initialize device");
            return;
        }

        // Start the device
        result = ma_device_start(&aEngine.device);
        if (result != MA_SUCCESS)
        {
            ERROR("Audio: Failed to start device");
            return;
        }

        // Initialising mutex to keep everything thread-safe
        result = ma_mutex_init(&aEngine.mutex);
        if (result != MA_SUCCESS)
        {
            ERROR("Audio: Failed to initialize mutex");
            return;
        }

        // Ready the audio engine
        aEngine.isActive = true;
        LOG("Audio: Initialised audio engine!");
    }

    void AudioContext::play() {
        
    }

    // Sound impl.
    Sound::Sound(const char* path) {
        load(path);
    }

    Sound::Sound(unsigned char* data, size_t size, const char* ftype) {
        load(data, size, ftype);
    }

    void Sound::load(const char* path) {
        size_t fsize;
        unsigned char* data = filesystem::loadFileData(path, fsize);
        load(data, fsize, filesystem::getFileExtension(path).c_str());
    }

    void Sound::load(unsigned char* data, size_t size, const char* ftype) {
        if (strcmp(ftype, "wav") == 0) {
            drwav wav = { 0 };
            bool success = drwav_init_memory(&wav, data, size, NULL);
            if (success) {
                
            }
            else {
                ERROR("Audio: Failed to load .wav file!")
            }
            drwav_uninit(&wav);
        }
    }

    Sound::~Sound() {

    }
}