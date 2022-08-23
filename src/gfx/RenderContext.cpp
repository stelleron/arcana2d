#include "gfx/RenderContext.hpp"
#include <iostream>

namespace arcana {
    float vertices[] = {
        0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 512.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
        512.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
        512.0f, 512.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,    
    };
    unsigned int indices[] = {  
        0, 1, 2, // first triangle
        1, 2, 3  // second triangle
    };

    Sprite sprite;

    // RENDER CONTEXT IMPL.
    RenderContext::RenderContext() {

    }

    RenderContext::~RenderContext() {
        glDeleteTextures(1, &defaultTextureID);
    }   

    void RenderContext::init() {
        // Create the default texture here
        unsigned char defaultTexture[4] = { 255, 255, 255, 255 }; 
        glGenTextures(1, &defaultTextureID); 
        glBindTexture(GL_TEXTURE_2D, defaultTextureID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);  
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);    
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);  
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, defaultTexture);
        glGenerateMipmap(GL_TEXTURE_2D);

        // Create the wall texture
        sprite.load("/Users/donti/Desktop/stelleron/arcana2d/cache/wall.jpg");
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
            float* fArray = buffer.getFloatArray();
            glBufferData(GL_ARRAY_BUFFER, buffer.getArraySize(), fArray, GL_STATIC_DRAW);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, buffer.getIndexArraySize(), buffer.getIndexArray(), GL_STATIC_DRAW); 

            // Now set vertex attribute pointers    
            setVertexAttributes();

            glBindBuffer(GL_ARRAY_BUFFER, defaultTextureID);

            // Then get the draw type
            RenderMode drawType = buffer.getRenderType();
            GLenum glDrawType;
            switch (drawType)
            {
                case Quads: glDrawType = GL_TRIANGLES;
                default: break;
            }

            // Draw the buffer
            glBindTexture(GL_TEXTURE_2D, defaultTextureID);
            useShader();
            glDrawElements(glDrawType, buffer.getArraySize()/VERTEX_FSIZE, GL_UNSIGNED_INT, 0);

            // Finally free all data
            glBindVertexArray(0);
            glBindTexture(GL_TEXTURE_2D, 0);
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
            float* fArray = buffer.getFloatArray();
            glBufferData(GL_ARRAY_BUFFER, buffer.getArraySize(), fArray, GL_STATIC_DRAW);

            // Now set vertex attribute pointers    
            setVertexAttributes();

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
            glBindTexture(GL_TEXTURE_2D, defaultTextureID);
            useShader();
            glDrawArrays(glDrawType, 0, buffer.getArraySize()/VERTEX_FSIZE);

            // Finally free all data
            glBindVertexArray(0);
            glBindTexture(GL_TEXTURE_2D, 0);
            glDeleteVertexArrays(1, &VAO);
            glDeleteBuffers(1, &VBO);
            delete[] fArray;
        }
    }

    void RenderContext::draw() {
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
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); 

            // Now set vertex attribute pointers    
            setVertexAttributes();

            // Draw the buffer
            glBindTexture(GL_TEXTURE_2D,sprite.getID());
            useShader();
            glBindVertexArray(VAO);      
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

            // Finally free all data
            glBindVertexArray(0);
            glBindTexture(GL_TEXTURE_2D, 0);
            glDeleteVertexArrays(1, &VAO);
            glDeleteBuffers(1, &VBO);
            glDeleteBuffers(1, &EBO);
    }

    void RenderContext::setCurrentCamera(Camera* camera) {
        this->curr_camera = camera;

    }

    void RenderContext::setCurrentShader(Shader* shader) {
        this->curr_shader = shader;
    }

    void RenderContext::setVertexAttributes() {
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);    

        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)8);
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)24);
        glEnableVertexAttribArray(2);        
    }
}