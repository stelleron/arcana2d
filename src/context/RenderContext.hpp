#ifndef ARCANA2D_RENDER_CONTEXT
    #define ARCANA2D_RENDER_CONTEXT

    #include "camera/Camera.hpp"
    #include "gfx/Shader.hpp"
    #include "gfx/VertexArray.hpp"


    namespace arcana {
        // Creates the render context
        class RenderContext {
            private:
                Shader* currShader;
                Camera* currCamera;
                unsigned int defaultTextureID;
                unsigned int defaultVBO;
                unsigned int defaultVAO;

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

                // Draw functions
                void draw(VertexArray& vArray);
        };
    }

#endif