#ifndef ARCANA2D_IMAGE
    #define ARCANA2D_IMAGE
    namespace arcana {
        // Struct for loading images
        struct Image {
            unsigned char* data;
            int width;
            int height;
            int colorChannels;

            // Constructor
            Image();
            Image(const char* path);
            // Destructor 
            ~Image();

            void load(const char* path);
            bool isLoaded();
        };
    }
#endif