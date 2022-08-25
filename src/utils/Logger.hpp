#ifndef ARCANA2D_LOGGER
    #define ARCANA2D_LOGGER
    // If ARCANA_DEBUG is defined, define a logging function
    #ifdef ARCANA_DEBUG
        #include <iostream>
        #define LOG(arg) std::cout << arg << std::endl;
    #else
        #define LOG(arg)
    #endif
#endif