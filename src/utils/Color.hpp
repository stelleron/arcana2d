#ifndef ARCANA2D_COLOR
    #define ARCANA2D_COLOR
    
    // Macros
    #define FLOAT_REP(color) (float)color/255
    #define COLOR_TO_FLOAT(color) FLOAT_REP(color.r), FLOAT_REP(color.g), FLOAT_REP(color.b), FLOAT_REP(color.a)

    namespace arcana {
        // Used to create a color object
        struct Color {
            unsigned char r;
            unsigned char g;
            unsigned char b;
            unsigned char a;

            // Constructor options
            Color();
            Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
        };
    }

    // Color constants
    #define WHITE arcana::Color(255, 255, 255, 255)
    #define RED arcana::Color(255, 0, 0, 255)
    #define GREEN arcana::Color(0, 255, 0, 255)
    #define BLUE arcana::Color(0, 0, 255, 255)

    #ifdef DEBUG
        // Output color values
        #include <utils/DebugOnly.hpp>
        #define DEBUG_COLOR(col) LOG("(" << (int)color.r << ", " << (int)color.g << ", " << (int)color.b << ", " << (int)color.a << ")")
        #define DEBUG_COLOR_FLOAT(col) LOG("(" << FLOAT_REP(color.r) << ", " << FLOAT_REP(color.g) << ", " << FLOAT_REP(color.b) << ", " << FLOAT_REP(color.a) << ")")
    #else  
        #define DEBUG_COLOR(col)    
        #define DEBUG_COLOR_FLOAT(col)
    #endif
#endif