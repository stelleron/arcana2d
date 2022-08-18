#ifndef ARCANA2D_RENDER_CONTEXT
    #define ARCANA2D_RENDER_CONTEXT
    // Includes
    #include "gfx/Shader.hpp"
    #include "geom/VertexBuffer.hpp"
    #include "gfx/Sprite.hpp"
    #include "utils/Camera.hpp"

    namespace arcana {
        // Used to create a render context to draw objects
        class RenderContext {
            private:
                Shader* curr_shader; // Stores the current shader
                Camera* curr_camera; // Stores the current camera
            public:
                // Constructor
                RenderContext();

                // Destructor
                ~RenderContext();

                // Used to initialise the renderer
                void init();

                // Use the shader after setting some uniforms
                void useShader();

                // Draw functions
                void draw(VertexBuffer& buffer);

                // Sprite drawing functions
                void draw(Sprite& sprite); // Default draw

                // Set the current camera
                void setCurrentCamera(Camera* camera);

                // Set the current shader
                void setCurrentShader(Shader* shader);
        };
    }
#endif