#ifndef ARCANA2D_RENDER_CONTEXT
    #define ARCANA2D_RENDER_CONTEXT
    // Includes
    #include "gfx/Shader.hpp"
    #include "geom/VertexBuffer.hpp"
    #include "utils/Camera.hpp"

    namespace arcana {
        // Used to create a render context to draw objects
        class RenderContext {
            private:
                Shader default_shader; // Stores the default shader
                Camera* curr_camera; // Stores the current camera
            public:
                // Constructor
                RenderContext();

                // Destructor
                ~RenderContext();

                // Used to initialise the renderer
                void init();

                // Use the default shader
                void useDefault();

                // Draw functions
                void draw(VertexBuffer& buffer);

                // Set the current camera
                void setCurrentCamera(Camera* camera);
        };
    }
#endif