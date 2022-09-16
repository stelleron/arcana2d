#ifndef ARCANA2D_RENDER_CONTEXT
    #define ARCANA2D_RENDER_CONTEXT

    #include "camera/Camera.hpp"
    #include "gfx/Shader.hpp"

    namespace arcana {
        // Creates the render context
        class RenderContext {
            private:
                Shader* currShader;
                Camera* currCamera;
                unsigned int defaultTextureID;

                void setVertexAttributes();
                void useShader();
            public:
                // Constructor
                RenderContext();
                // Destructor
                ~RenderContext();
                void init();
                void setCurrentCamera(Camera& camera) {currCamera = &camera;}
                void setCurrentShader(Shader& shader) {currShader = &shader;}
                void draw();
        };
    }

#endif