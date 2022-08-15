#include "gfx/RenderContext.hpp"
#include "utils/DebugOnly.hpp"

namespace arcana {
    float* fArray;

    // RENDER CONTEXT IMPL.
    RenderContext::RenderContext() {

    }

    RenderContext::~RenderContext() {

    }

    void RenderContext::init() {

    }

    void RenderContext::useDefault() {
        default_shader.setMat4("projection", curr_camera->getProjectionMatrix());
        default_shader.use();
    }

    void RenderContext::draw(VertexBuffer& buffer) {
        // First initialise the vertex array and buffer
        unsigned int VBO, VAO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        // Then bind all vertex objects
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        // And buffer the data
        fArray = buffer.getFloatArray();
        glBufferData(GL_ARRAY_BUFFER, buffer.getArraySize(), fArray, GL_STATIC_DRAW);

        // Now set vertex attribute pointers    
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);    

        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)8);
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // Then get the draw type
        RenderMode drawType = buffer.getRenderType();
        GLenum glDrawType;
        switch (drawType)
        {
            case Triangles: glDrawType = GL_TRIANGLES;
            default: break;
        }

        // Draw the buffer
        glDrawArrays(glDrawType, 0, buffer.getArraySize()/VERTEX_FSIZE);

        // Finally free all data
        glBindVertexArray(0);
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        delete[] fArray;
    }

    void RenderContext::setCurrentCamera(Camera* camera) {
        this->curr_camera = camera;
    }
}