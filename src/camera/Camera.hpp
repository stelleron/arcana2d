#ifndef ARCANA2D_CAMERA
    #define ARCANA2D_CAMERA
    // Includes
    #include "utils/Vector.hpp"

    namespace arcana {
        // Used to create a 2D camera
        class Camera {
            private:
                Vector2 dimensions; // Stores the camera dimensions
                Vector2 offset; // Camera offset
                float rotation; // Camera rotation
                float zoom; // Camera zoom
            public:
                // Constructor
                Camera();
                // Destructor 
                ~Camera();

                // Set the camera dimensions
                void setDim(int width, int height);
                // Set the zoom of the camera
                void setZoom(float zoom);

                // Get the projection matrix
                Mat4 getProjectionMatrix();
        };
    }
#endif