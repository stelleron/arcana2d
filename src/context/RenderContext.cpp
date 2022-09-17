#include <glad/glad.h>
#include "context/RenderContext.hpp"
#include "geom/Vertex.hpp"


namespace arcana {
    // RENDER CONTEXT IMPL.
    RenderContext::RenderContext() {
        
    }

    RenderContext::~RenderContext() {
        glDeleteVertexArrays(1, &defaultVAO);
        glDeleteBuffers(1, &defaultVBO);
        glDeleteTextures(1, &defaultTextureID);
        glDeleteBuffers(1, &defaultEBO);
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
        glGenVertexArrays(1, &defaultVAO);
        glGenBuffers(1, &defaultVBO);
        glGenBuffers(1, &defaultEBO);
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

    void RenderContext::draw(VertexArray& vArray) {
        RenderMode rMode = vArray.getRenderType();
        if (rMode == Quads || rMode == Circles) {
            // Bind all vertex objects
            glBindVertexArray(defaultVAO);
            glBindBuffer(GL_ARRAY_BUFFER, defaultVBO); 
            glBufferData(GL_ARRAY_BUFFER, vArray.getArraySize(), vArray.getVertexArray(), GL_STATIC_DRAW);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, defaultEBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, vArray.getIndexArraySize(), vArray.getIndexArray(), GL_STATIC_DRAW);
            setVertexAttributes();
            glBindBuffer(GL_ARRAY_BUFFER, 0);  
            GLenum drawType;
            switch (rMode) {
                case Circles: drawType = GL_TRIANGLES; break;
                case Quads: drawType = GL_TRIANGLES; break;
                default: break;
            }

            useShader();
            glBindTexture(GL_TEXTURE_2D, defaultTextureID);
            glBindVertexArray(defaultVAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
            glDrawElements(drawType, vArray.getIndexArraySize()/sizeof(unsigned int), GL_UNSIGNED_INT, 0);
        }
        else {
            // Bind all vertex objects
            glBindVertexArray(defaultVAO);
            glBindBuffer(GL_ARRAY_BUFFER, defaultVBO); 
            glBufferData(GL_ARRAY_BUFFER, vArray.getArraySize(), vArray.getVertexArray(), GL_STATIC_DRAW);
            setVertexAttributes();
            glBindBuffer(GL_ARRAY_BUFFER, 0);  
            GLenum drawType;
            switch (rMode) {
                case Points: drawType = GL_LINES; break;
                case Lines: drawType = GL_LINES; break;
                case Triangles: drawType = GL_TRIANGLES; break;
                default: break;
            }

            useShader();
            glBindTexture(GL_TEXTURE_2D, defaultTextureID);
            glBindVertexArray(defaultVAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
            glDrawArrays(drawType, 0, vArray.getArraySize()/sizeof(Vertex));
        }
        
    }
}

