#ifndef ARCANA2D_COLOR
    #define ARCANA2D_COLOR
    
    // Macros
    #define COLOR_TO_FLOAT(color) (float)color.r/255, (float)color.g/255, (float)color.b/255, (float)color.a/255

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
#endif