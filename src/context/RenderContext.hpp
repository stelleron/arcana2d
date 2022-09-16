#ifndef ARCANA2D_RENDER_CONTEXT
    #define ARCANA2D_RENDER_CONTEXT

    #include "camera/Camera.hpp"
    namespace arcana {
        // Creates the render context
        class RenderContext {
            private:
                Camera* currCamera;
            public:
                // Constructor
                RenderContext();
                // Destructor
                ~RenderContext();

                void draw();
                void setCurrentCamera(Camera& camera) {currCamera = &camera;}
        };
    }

#endif