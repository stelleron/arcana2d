#ifndef ARCANA2D_RENDER_CONTEXT
    #define ARCANA2D_RENDER_CONTEXT
    // Includes
    #include "gfx/Shader.hpp"

    namespace arcana {
        // Used to create a render context to draw objects
        class RenderContext {
            private:
                Shader default_shader;
            public:
                // Constructor
                RenderContext();

                // Destructor
                ~RenderContext();

                //  Used to initialise the renderer
                void init();

                // Use the default shader
                void useDefault();
        };
    }
#endif