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
            Image(unsigned char* data);
            // Destructor 
            ~Image();

            void load(const char* path);
            void load(unsigned char* data);
            bool isLoaded(); // Check if the image has been loaded
        };
    }
#endif