#include <glad/glad.h>
#include "context/RenderContext.hpp"
#include "geom/Vertex.hpp"


namespace arcana {
    unsigned int VBO, VAO;
    Vertex vertices[] = {
        Vertex(Vector3(150.0f, 50.0f, 25.0f),  Color(255, 0, 0, 255)),
        Vertex(Vector3(50.0f, 150.0f, 25.0f),  Color(0, 255, 0, 255)),  
        Vertex(Vector3(150.0f, 150.0f, 25.0f), Color(0, 0, 255, 255))  
    }; 

    // RENDER CONTEXT IMPL.
    RenderContext::RenderContext() {
        
    }

    RenderContext::~RenderContext() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
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
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        // Then bind all vertex objects
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO); 
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        setVertexAttributes();
        glBindBuffer(GL_ARRAY_BUFFER, 0);  
    }

    void RenderContext::setVertexAttributes() {
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)12);
        glEnableVertexAttribArray(1);  
         
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)16);
        glEnableVertexAttribArray(2);
    }

    void RenderContext::useShader() {
        currShader->setMat4("projection", currCamera->getProjectionMatrix());
        currShader->use();
    }

    void RenderContext::draw() {
        useShader();
        glBindTexture(GL_TEXTURE_2D, defaultTextureID);
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }
}

