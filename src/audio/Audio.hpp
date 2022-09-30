#ifndef ARCANA2D_AUDIO
    #define ARCANA2D_AUDIO
    #include "miniaudio.h"

    namespace arcana {
        // Typedef Miniaudio structs
        typedef ma_engine AudioEngine;
        typedef ma_sound MASound;

        // Used to create an audio context that plays sounds and music
        struct AudioContext {
            private:
                AudioEngine engine;
            public:
                // Constructor
                AudioContext();
                // Destructor
                ~AudioContext();
                void update(); // Update the audio device
        };

        // Used to store a sound
        struct Sound {
            private:
                MASound sound;
                bool isInit;
            public:
                // Constructor
                Sound();
                Sound(const char* path);
                Sound(unsigned char* data, size_t size, const char* extension);
                // Destructor
                ~Sound();

                // Loading functions
                void load(const char* path);
                void load(unsigned char* data, size_t size, const char* extension);
                bool isLoaded(); // Check if the sound has been loaded
        };
    }
#endif