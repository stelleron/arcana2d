#ifndef ARCANA2D_RANDOM
    #define ARCANA2D_RANDOM
    namespace arcana {
        // Used to generate randon numbers
        class Random {
            private:
                static unsigned int seed;
            public:
                // Generate a random number between the two given numbers
                static int generateNum(int min, int max);
                // Set a seed
                static void setSeed(unsigned int nSeed);
        };
    }
#endif