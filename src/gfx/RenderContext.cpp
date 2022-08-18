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

    void RenderContext::useShader() {
        curr_shader->setMat4("projection", curr_camera->getProjectionMatrix());
        curr_shader->use();
    }

    void RenderContext::draw(VertexBuffer& buffer) {
        // For drawing objects with an EBO
        if (buffer.rMode == RenderMode::Quads) {
            // First initialise the vertex array and buffer and EBO
            unsigned int VBO, VAO, EBO;
            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);
            glGenBuffers(1, &EBO);

            // Then bind all vertex objects
            glBindVertexArray(VAO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

            // And buffer the data
            fArray = buffer.getFloatArray();
            glBufferData(GL_ARRAY_BUFFER, buffer.getArraySize(), fArray, GL_STATIC_DRAW);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, buffer.eBuffer->getIndicesSize(), buffer.eBuffer->iArray, GL_STATIC_DRAW); 

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
                case Quads: glDrawType = GL_TRIANGLES;
                default: break;
            }

            // Draw the buffer
            useShader();
            glDrawElements(glDrawType, buffer.getArraySize()/VERTEX_FSIZE, GL_UNSIGNED_INT, 0);

            // Finally free all data
            glBindVertexArray(0);
            glDeleteVertexArrays(1, &VAO);
            glDeleteBuffers(1, &VBO);
            glDeleteBuffers(1, &EBO);
            delete[] fArray;
        }

        // For drawing objects without an EBO
        else {
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
            useShader();
            glDrawArrays(glDrawType, 0, buffer.getArraySize()/VERTEX_FSIZE);

            // Finally free all data
            glBindVertexArray(0);
            glDeleteVertexArrays(1, &VAO);
            glDeleteBuffers(1, &VBO);
            delete[] fArray;
        }
    }

    void RenderContext::draw(Sprite& sprite) {
        
    }

    void RenderContext::setCurrentCamera(Camera* camera) {
        this->curr_camera = camera;

    }

    void RenderContext::setCurrentShader(Shader* shader) {
        this->curr_shader = shader;
    }
}