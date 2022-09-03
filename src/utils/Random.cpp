#include <cstdlib>
#include "utils/Random.hpp"

namespace arcana {
    unsigned int Random::seed = 1;
    int Random::generateNum(int min, int max) {
        // Make sure that max is greater than min. Else swap them around
        int nMax, nMin;
        if (min > max) {
            nMax = min;
            nMin = max;
        }
        else {
            nMax = max;
            nMin = min;
        }
        return (rand()%(abs(max - min) + 1) + min);
    }

    void Random::setSeed(unsigned int nSeed) {
        seed = nSeed;
        srand(seed);
    }
}