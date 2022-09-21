#include <glad/glad.h>
#include "context/RenderContext.hpp"
#include "geom/Vertex.hpp"
#include "utils/Logger.hpp"

#define MAX_BATCH_SIZE 8000
#define DRAW_OBJECT(type, vnum, obj) do { \
    RenderMode rmode = rBatch.vertexArray.getRenderType(); \
    if (rmode == type && rBatch.vertexArray.checkSpace(rBatch.vertexPointer, vnum) && currentTextureID == defaultTextureID) { \
        rBatch.add(obj); \
    } \
    else { \
        if (rmode != None) { \
            draw(rBatch.vertexArray); \
        } \
        currentTextureID = defaultTextureID; \
        rBatch.vertexArray.reset(type, MAX_BATCH_SIZE); \
        rBatch.vertexPointer = 0; \
        rBatch.add(obj); \
    } \
} while (false); \

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

    void RenderContext::RenderBatch::add(Sprite& sprite) {
        Texture* tex = sprite.getTexturePtr();
        vertexArray[vertexPointer] = Vertex({sprite.pos.x, sprite.pos.y, sprite.z}, sprite.color);
        vertexArray[vertexPointer + 1] = Vertex({sprite.pos.x + (tex->width * sprite.scale.x), sprite.pos.y, sprite.z}, sprite.color, {1.0f, 0.0f});
        vertexArray[vertexPointer + 2] = Vertex({sprite.pos.x, sprite.pos.y + (tex->height * sprite.scale.y), sprite.z}, sprite.color, {0.0f, 1.0f});
        vertexArray[vertexPointer + 3] = Vertex({sprite.pos.x + (tex->width * sprite.scale.x), sprite.pos.y + (tex->height * sprite.scale.y), sprite.z}, sprite.color, {1.0f, 1.0f});
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
        currentTextureID = defaultTextureID;
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
            glBindTexture(GL_TEXTURE_2D, currentTextureID);
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
            glBindTexture(GL_TEXTURE_2D, currentTextureID);
            glBindVertexArray(defaultVAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
            glDrawArrays(drawType, 0, vArray.getNumVertices());
        }
        
    }

    void RenderContext::draw(const Point& point) {
        DRAW_OBJECT(Points, 2, point);
    }

    void RenderContext::draw(const DrawPoint& point) {
        DRAW_OBJECT(Points, 2, point);
    }

    void RenderContext::draw(const Line& line) {
        DRAW_OBJECT(Lines, 2, line);
    }

    void RenderContext::draw(const DrawLine& line) {
        DRAW_OBJECT(Lines, 2, line);
    }

    void RenderContext::draw(const Triangle& triangle) {
        DRAW_OBJECT(Triangles, 3, triangle);
    }

    void RenderContext::draw(const DrawTriangle& triangle) {
        DRAW_OBJECT(Triangles, 3, triangle);
    }

    void RenderContext::draw(const Rectangle& rectangle) {
        DRAW_OBJECT(Quads, 4, rectangle);
    }

    void RenderContext::draw(const Quadrilateral& quad) {
        DRAW_OBJECT(Quads, 4, quad);
    }

    void RenderContext::draw(const DrawQuad& quad) {
        DRAW_OBJECT(Quads, 4, quad);
    }

    void RenderContext::draw(const Circle& circle) {
        DRAW_OBJECT(Circles, 37, circle);
    }

    void RenderContext::draw(const DrawCircle& circle) {
        DRAW_OBJECT(Circles, 37, circle);
    }

    void RenderContext::draw(Sprite& sprite) {
        Texture* tex = sprite.getTexturePtr();
        RenderMode rmode = rBatch.vertexArray.getRenderType(); 
        if (rmode == Quads && rBatch.vertexArray.checkSpace(rBatch.vertexPointer, 4) && currentTextureID == tex->id) { 
            rBatch.add(sprite); 
        } 
        else { 
            if (rmode != None) { 
                draw(rBatch.vertexArray); 
            } 
            currentTextureID = tex->id; 
            rBatch.vertexArray.reset(Quads, MAX_BATCH_SIZE); 
            rBatch.vertexPointer = 0; 
            rBatch.add(sprite); 
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

