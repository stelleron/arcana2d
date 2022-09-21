#ifndef ARCANA2D_RENDER_CONTEXT
    #define ARCANA2D_RENDER_CONTEXT

    #include "camera/Camera.hpp"
    #include "gfx/Shader.hpp"
    #include "gfx/VertexArray.hpp"


    namespace arcana {
        // Creates the render context
        class RenderContext {
            // Creates an internal render batch
            struct RenderBatch {
                VertexArray vertexArray;
                int vertexPointer;

                RenderBatch();
                ~RenderBatch();

                // Used to add objects to the render batch
                void add(const Point& point);
                void add(const DrawPoint& point);

                void add(const Line& line);
                void add(const DrawLine& line);

                void add(const Triangle& triangle);
                void add(const DrawTriangle& triangle);

                void add(const Rectangle& rectangle);
                void add(const Quadrilateral& quad);
                void add(const DrawQuad& quad);

                void add(const Circle& circle);
                void add(const DrawCircle& circle);
            };

            private:
                Shader* currShader;
                Camera* currCamera;
                RenderBatch rBatch;

                unsigned int defaultVBO;
                unsigned int defaultVAO;
                unsigned int defaultEBO;
                unsigned int defaultTextureID;
                unsigned int currentTextureID;

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

                // Used to add objects to the render batch
                void draw(const Point& point);
                void draw(const DrawPoint& point);

                void draw(const Line& line);
                void draw(const DrawLine& line);

                void draw(const Triangle& triangle);
                void draw(const DrawTriangle& triangle);

                void draw(const Rectangle& rectangle);
                void draw(const Quadrilateral& quad);
                void draw(const DrawQuad& quad);

                void draw(const Circle& circle);
                void draw(const DrawCircle& circle);

                void drawBatch();
        };
    }

#endif