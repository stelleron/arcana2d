#ifndef ARCANA2D_RESOURCE
    #define ARCANA2D_RESOURCE
    namespace arcana {
        // Namespace for loading images
        struct Image {
            unsigned char* data;
            int width;
            int height;
            int colorChannels;

            // Constructor
            Image(const char* path);

            // Destructor 
            ~Image();
        };
    }
#endif