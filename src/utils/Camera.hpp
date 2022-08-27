#ifndef ARCANA2D_CAMERA
    #define ARCANA2D_CAMERA
    // Includes
    #include "utils/Vector.hpp"

    namespace arcana {
        // Used to create a 2D camera
        class Camera {
            private:
                Vector2 camera_dim; // Stores the camera dimensions
            public:
                // Constructor
                Camera();
                // Destructor 
                ~Camera();

                // Configure the camera to default settings
                void defaultSettings(int width, int height);

                // Get the projection matrix
                Mat4 getProjectionMatrix();

                // Resize the camera dimensions
                void resizeCamera(Vector2 new_dim);
        };
    }
#endif