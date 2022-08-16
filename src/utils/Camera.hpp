#ifndef ARCANA2D_CAMERA
    #define ARCANA2D_CAMERA
    // Includes
    #include <glm/glm.hpp>
    #include <geom/Vertex.hpp>

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
                glm::mat4 getProjectionMatrix();
        };
    }
#endif