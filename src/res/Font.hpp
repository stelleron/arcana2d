#ifndef ARCANA2D_FONT
    #define ARCANA2D_FONT
    #define DEFAULT_FONT_SIZE 32
    #include "geom/Geometry.hpp"
    #include "gfx/Sprite.hpp"
    namespace arcana {
        // Used to create a font object
        struct Font {
            private:
                int fontSize;
                Rectangle* fontRecs;
            public:
                Texture fontTex;
                // Constructor
                Font();
                Font(const char* path, int fontsize = DEFAULT_FONT_SIZE);
                Font(unsigned char* data, size_t size, int fontsize = DEFAULT_FONT_SIZE);
                // Destructor 
                ~Font();

                void load(const char* path, int fontsize = DEFAULT_FONT_SIZE);
                void load(unsigned char* data, size_t size, int fontsize = DEFAULT_FONT_SIZE);
                bool isLoaded(); // Check if the font has been loaded

        };
    }
#endif