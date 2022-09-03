#ifndef ARCANA2D_LOGGER
    #define ARCANA2D_LOGGER
    // If ENABLE_ARCANA_LOGGER is defined, define a logging function
    #ifdef ENABLE_ARCANA_LOGGER
        #include <iostream>
        #define LOG(arg) std::cout << arg << std::endl;
    #else
        #define LOG(arg) 
    #endif
#endif