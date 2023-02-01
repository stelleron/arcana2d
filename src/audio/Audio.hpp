#ifndef ARCANA2D_AUDIO
    #define ARCANA2D_AUDIO
    namespace arcana {
        // Used to create an audio context for playing audio
        struct AudioContext {
            void init();
            void play();
        };

        // Used to implement a sound class
        class Sound {
            private:


            public:
                Sound(const char* path);
                Sound(unsigned char* data, size_t size, const char* ftype);
                ~Sound();

                void load(const char* path);
                void load(unsigned char* data, size_t size, const char* ftype);
        };
    }
#endif