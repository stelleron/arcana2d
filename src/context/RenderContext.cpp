#include <glad/glad.h>
#include "context/RenderContext.hpp"
#include "geom/Vertex.hpp"
#include "utils/Logger.hpp"

#define MAX_BATCH_SIZE 8000

namespace arcana {
    // RENDER BATCH IMPL.
    RenderContext::RenderBatch::RenderBatch() {
        vertexPointer = 0;
    }

    RenderContext::RenderBatch::~RenderBatch() {

    }

    void RenderContext::RenderBatch::add(const Point& point) {
        vertexArray.add(point, vertexPointer);
        vertexPointer += 2;
    }

    void RenderContext::RenderBatch::add(const DrawPoint& point) {
        vertexArray.add(point, vertexPointer);
        vertexPointer += 2;
    }

    void RenderContext::RenderBatch::add(const Line& line) {
        vertexArray.add(line, vertexPointer);
        vertexPointer += 2;
    }

    void RenderContext::RenderBatch::add(const DrawLine& line) {
        vertexArray.add(line, vertexPointer);
        vertexPointer += 2;
    }

    void RenderContext::RenderBatch::add(const Triangle& triangle) {
        vertexArray.add(triangle, vertexPointer);
        vertexPointer += 3;
    }

    void RenderContext::RenderBatch::add(const DrawTriangle& triangle) {
        vertexArray.add(triangle, vertexPointer);
        vertexPointer += 3;
    }

    void RenderContext::RenderBatch::add(const Rectangle& rectangle) {
        vertexArray.add(rectangle, vertexPointer);
        vertexPointer += 4;
    }

    void RenderContext::RenderBatch::add(const Quadrilateral& quad) {
        vertexArray.add(quad, vertexPointer);
        vertexPointer += 4;
    }

    void RenderContext::RenderBatch::add(const DrawQuad& quad) {
        vertexArray.add(quad, vertexPointer);
        vertexPointer += 4;
    }

    void RenderContext::RenderBatch::add(const Circle& circle) {
        vertexArray.add(circle, vertexPointer);
        vertexPointer += 37;
    }

    void RenderContext::RenderBatch::add(const DrawCircle& circle) {
        vertexArray.add(circle, vertexPointer);
        vertexPointer += 37;
    }

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
        if (rMode == None) {
            ERROR("Error: Cannot draw a vertex array with type None!");
        }
        else if (rMode == Quads || rMode == Circles) {
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
            glDrawArrays(drawType, 0, vArray.getNumVertices());
        }
        
    }

    void RenderContext::draw(const Point& point) {
        RenderMode rmode = rBatch.vertexArray.getRenderType();
        if (rmode == Points && rBatch.vertexArray.checkSpace(rBatch.vertexPointer, 2)) {
            rBatch.add(point);
        }
        else {
            if (rmode != None) {
                draw(rBatch.vertexArray);
            }
            rBatch.vertexArray.reset(Points, MAX_BATCH_SIZE);
            rBatch.vertexPointer = 0;
            rBatch.add(point);
        }
    }

    void RenderContext::draw(const DrawPoint& point) {
        RenderMode rmode = rBatch.vertexArray.getRenderType();
        if (rmode == Points && rBatch.vertexArray.checkSpace(rBatch.vertexPointer, 2)) {
            rBatch.add(point);
        }
        else {
            if (rmode != None) {
                draw(rBatch.vertexArray);
            }
            rBatch.vertexArray.reset(Points, MAX_BATCH_SIZE);
            rBatch.vertexPointer = 0;
            rBatch.add(point);
        }
    }

    void RenderContext::draw(const Line& line) {
        RenderMode rmode = rBatch.vertexArray.getRenderType();
        if (rmode == Lines && rBatch.vertexArray.checkSpace(rBatch.vertexPointer, 2)) {
            rBatch.add(line);
        }
        else {
            if (rmode != None) {
                draw(rBatch.vertexArray);
            }
            rBatch.vertexArray.reset(Lines, MAX_BATCH_SIZE);
            rBatch.vertexPointer = 0;
            rBatch.add(line);
        }
    }

    void RenderContext::draw(const DrawLine& line) {
        RenderMode rmode = rBatch.vertexArray.getRenderType();
        if (rmode == Lines && rBatch.vertexArray.checkSpace(rBatch.vertexPointer, 2)) {
            rBatch.add(line);
        }
        else {
            if (rmode != None) {
                draw(rBatch.vertexArray);
            }
            rBatch.vertexArray.reset(Lines, MAX_BATCH_SIZE);
            rBatch.vertexPointer = 0;
            rBatch.add(line);
        }
    }

    void RenderContext::draw(const Triangle& triangle) {
        RenderMode rmode = rBatch.vertexArray.getRenderType();
        if (rmode == Triangles && rBatch.vertexArray.checkSpace(rBatch.vertexPointer, 3)) {
            rBatch.add(triangle);
        }
        else {
            if (rmode != None) {
                draw(rBatch.vertexArray);
            }
            rBatch.vertexArray.reset(Triangles, MAX_BATCH_SIZE);
            rBatch.vertexPointer = 0;
            rBatch.add(triangle);
        }
    }

    void RenderContext::draw(const DrawTriangle& triangle) {
        RenderMode rmode = rBatch.vertexArray.getRenderType();
        if (rmode == Triangles && rBatch.vertexArray.checkSpace(rBatch.vertexPointer, 3)) {
            rBatch.add(triangle);
        }
        else {
            if (rmode != None) {
                draw(rBatch.vertexArray);
            }
            rBatch.vertexArray.reset(Triangles, MAX_BATCH_SIZE);
            rBatch.vertexPointer = 0;
            rBatch.add(triangle);
        }
    }

    void RenderContext::draw(const Rectangle& rectangle) {
        RenderMode rmode = rBatch.vertexArray.getRenderType();
        if (rmode == Quads && rBatch.vertexArray.checkSpace(rBatch.vertexPointer, 4)) {
            rBatch.add(rectangle);
        }
        else {
            if (rmode != None) {
                draw(rBatch.vertexArray);
            }
            rBatch.vertexArray.reset(Quads, MAX_BATCH_SIZE);
            rBatch.vertexPointer = 0;
            rBatch.add(rectangle);
        }
    }

    void RenderContext::draw(const Quadrilateral& quad) {
        RenderMode rmode = rBatch.vertexArray.getRenderType();
        if (rmode == Quads && rBatch.vertexArray.checkSpace(rBatch.vertexPointer, 4)) {
            rBatch.add(quad);
        }
        else {
            if (rmode != None) {
                draw(rBatch.vertexArray);
            }
            rBatch.vertexArray.reset(Quads, MAX_BATCH_SIZE);
            rBatch.vertexPointer = 0;
            rBatch.add(quad);
        }
    }

    void RenderContext::draw(const DrawQuad& quad) {
        RenderMode rmode = rBatch.vertexArray.getRenderType();
        if (rmode == Quads && rBatch.vertexArray.checkSpace(rBatch.vertexPointer, 4)) {
            rBatch.add(quad);
        }
        else {
            if (rmode != None) {
                draw(rBatch.vertexArray);
            }
            rBatch.vertexArray.reset(Quads, MAX_BATCH_SIZE);
            rBatch.vertexPointer = 0;
            rBatch.add(quad);
        }
    }

    void RenderContext::draw(const Circle& circle) {
        RenderMode rmode = rBatch.vertexArray.getRenderType();
        if (rmode == Circles && rBatch.vertexArray.checkSpace(rBatch.vertexPointer, 37)) {
            rBatch.add(circle);
        }
        else {
            if (rmode != None) {
                draw(rBatch.vertexArray);
            }
            rBatch.vertexArray.reset(Circles, MAX_BATCH_SIZE);
            rBatch.vertexPointer = 0;
            rBatch.add(circle);
        }
    }

    void RenderContext::draw(const DrawCircle& circle) {
        RenderMode rmode = rBatch.vertexArray.getRenderType();
        if (rmode == Circles && rBatch.vertexArray.checkSpace(rBatch.vertexPointer, 37)) {
            rBatch.add(circle);
        }
        else {
            drawBatch();
            rBatch.vertexArray.reset(Circles, MAX_BATCH_SIZE);
            rBatch.vertexPointer = 0;
            rBatch.add(circle);
        }
    }

    void RenderContext::drawBatch() {
        // Reset the draw batch
        RenderMode rmode = rBatch.vertexArray.getRenderType();
        if (rmode != None) {
            draw(rBatch.vertexArray);
        }
        rBatch.vertexArray.reset();
        rBatch.vertexPointer = 0;
    }
}

