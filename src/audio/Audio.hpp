#ifndef ARCANA2D_AUDIO
    #define ARCANA2D_AUDIO
    namespace arcana {
        // Used to create an audio context for playing audio
        struct AudioContext {
            void init();
            void play();
        };
    }
#endif