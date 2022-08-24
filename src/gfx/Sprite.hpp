#ifndef ARCANA2D_SPRITE
    #define ARCANA2D_SPRITE
    

    namespace arcana {
        // Used to create a sprite
        class Sprite {
            private:
                unsigned int id;  
                int width;
                int height;

                bool is_init;

            public:
                // Constructor
                Sprite();
                Sprite(const char* path);

                // Load the sprite
                void load(const char* path);
                // Get the ID of the sprite
                inline unsigned int getID() {return id;}

                // Destructor
                ~Sprite();
        };
    }
#endif