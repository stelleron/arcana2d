#ifndef ARCANA2D_RANDOM
    #define ARCANA2D_RANDOM
    namespace arcana {
        // Used to generate random numbers
        class Random {
            private:
                unsigned int seed;
            public:
                // Constructor
                Random();
                Random(unsigned int seed);
                // Generate a random number between the two given numbers
                int generateNum(int min, int max);
                // Set a seed
                void setSeed(unsigned int nSeed);
        };
    }
#endif