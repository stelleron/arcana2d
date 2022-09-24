#ifndef ARCANA2D_FONT
    #define ARCANA2D_FONT

    namespace arcana {
        // Used to create a font object
        struct Font {
            private:
                int fontSize;
            public:
                // Constructor
                Font();
                Font(const char* path, int fontsize = 20);
                Font(unsigned char* data, size_t size, int fontsize = 20);
                // Destructor 
                ~Font();

                void load(const char* path, int fontsize = 20);
                void load(unsigned char* data, size_t size, int fontsize = 20);
                bool isLoaded(); // Check if the font has been loaded

        };
    }
#endif