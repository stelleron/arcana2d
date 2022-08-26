#ifndef ARCANA2D_AUDIO
    #define ARCANA2D_AUDIO

    namespace arcana {
        // Used to create the audio context
        class AudioContext {
            public:
                // Constructor
                AudioContext();
                // Destructor
                ~AudioContext();

                // Play a sound
                void playSound(const char* soundpath);
        };
    }
#endif