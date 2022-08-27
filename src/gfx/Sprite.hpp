#ifndef ARCANA2D_SPRITE
    #define ARCANA2D_SPRITE

    #include "res/Image.hpp"
    #include "utils/Vector.hpp"

    namespace arcana {
        // Used to create a sprite
        class Sprite {
            private:
                unsigned int id; 
                bool is_init;

            public:
                // Properties
                Vector2 pos; 
                int width;
                int height;

                // Constructor
                Sprite();
                Sprite(const char* path);
                Sprite(const Image& image);

                // Load the sprite
                void load(const char* path);
                void load(const Image& image);
                // Get the ID of the sprite
                inline unsigned int getID() {return id;}

                // Destructor
                ~Sprite();
        };
    }
#endif