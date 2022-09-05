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
            Image(unsigned char* data, size_t size);
            // Destructor 
            ~Image();

            void load(const char* path);
            void load(unsigned char* data, size_t size);
            bool isLoaded(); // Check if the image has been loaded
        };
    }
#endif