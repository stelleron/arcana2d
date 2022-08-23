#include "geom/VertexBuffer.hpp"
#include <iostream>

#define RENDER_TYPE_ASSERT(arg) if (rMode != arg) {return;}
#define BATCH_SPACE_ASSERT(arg) if (!checkSpace(arg)) {return;}
#define V_MULTIPLY(arg) (x * VERTEX_SIZE)

namespace arcana {
    // ELEMENT BUFFER IMPL.
    ElementBuffer::ElementBuffer(RenderMode rMode, int size) {
        totalSize = 0;
        int iVal = 0;
        switch (rMode)
        {
            case Quads: 
                // If the mode is Quads, store six times the given size of indices, and auto generate
                iArray = new unsigned int[size * 6];
                totalSize = sizeof(unsigned int) * size * 6;
                for (int x = 0; x < size; x++) {
                    iArray[x * 6] = iVal;
                    iArray[x * 6 + 1] = iVal + 1;
                    iArray[x * 6 + 2] = iVal + 2;
                    iArray[x * 6 + 3] = iVal + 1;
                    iArray[x * 6 + 4] = iVal + 2;
                    iArray[x * 6 + 5] = iVal + 3;
                    iVal = iVal + 4;
                }
                break;
            default: break;
        }
        capacity = size;
        pointer = 0;
    }

    ElementBuffer::~ElementBuffer() {
        delete[] iArray;
    }

    void ElementBuffer::addPointer() {
        if (capacity > pointer) {
            pointer++;
        }
    }

    size_t ElementBuffer::getSize() {
        return totalSize;
    }
 
    // VERTEX BUFFER IMPL.
    // NOTE: Size is the number of primitives
    VertexBuffer::VertexBuffer(RenderMode rMode, int primNum) {
        // First get the size of the primitive in vertices
        eBuffer = nullptr;
        switch (rMode)
        {
            case Lines: primSize = 2; break;
            case Triangles: primSize = 3; break;
            case Quads: primSize = 4; eBuffer = new ElementBuffer(rMode, primNum); break;
            default: break;
        }

        // Now allocate memory for the vertices
        vSize = primNum * primSize;
        vArray = new Vertex[vSize];

        // Save the render mode and set the vertex pointer to 0
        this->rMode = rMode;
        vPointer = 0;
    }

    VertexBuffer::~VertexBuffer() {
        if (eBuffer != nullptr) {
            delete eBuffer;
        }
        delete[] vArray;
    }

    bool VertexBuffer::checkSpace(int numVertices) {
        if (numVertices + vPointer <= vSize) {
            return true;
        }
        else {
            return false;
        }
    }

    size_t VertexBuffer::getArraySize() {
        return vPointer * VERTEX_FSIZE;
    }

    float* VertexBuffer::getFloatArray() {
        // First create a float array
        float* fArray = new float[getArraySize()/sizeof(float)];

        // Now copy all vertex data into the float array
        for (int x = 0; x < vPointer; x++) {
            fArray[V_MULTIPLY(x)] = vArray[x].pos.x;
            fArray[V_MULTIPLY(x) + 1] = vArray[x].pos.y;
            fArray[V_MULTIPLY(x) + 2] = vArray[x].pos.z;
            fArray[V_MULTIPLY(x) + 3] = FLOAT_REP(vArray[x].color.r);
            fArray[V_MULTIPLY(x) + 4] = FLOAT_REP(vArray[x].color.g);
            fArray[V_MULTIPLY(x) + 5] = FLOAT_REP(vArray[x].color.b);
            fArray[V_MULTIPLY(x) + 6] = FLOAT_REP(vArray[x].color.a);
            fArray[V_MULTIPLY(x) + 7] = vArray[x].texCoords.x;
            fArray[V_MULTIPLY(x) + 8] = vArray[x].texCoords.y;
        }

        // And return the array
        return fArray;
    }

    void VertexBuffer::add(const Triangle& triangle) {
        // First make sure that object has a compatiable type
        RENDER_TYPE_ASSERT(RenderMode::Triangles);

        // Then ensure that there is enough space for the primitive
        BATCH_SPACE_ASSERT(3);

        // Now time to add all of the vertices to the vertex array
        vArray[vPointer] = Vertex(triangle.point1);
        vArray[vPointer + 1] = Vertex(triangle.point2);
        vArray[vPointer + 2] = Vertex(triangle.point3);
        vPointer += 3;
    }

    void VertexBuffer::add(const DrawTriangle& triangle) {
        // First make sure that object has a compatiable type
        RENDER_TYPE_ASSERT(RenderMode::Triangles);

        // Then ensure that there is enough space for the primitive
        BATCH_SPACE_ASSERT(3);

        // Now time to add all of the vertices to the vertex array
        vArray[vPointer] = Vertex(triangle.point1, triangle.color);
        vArray[vPointer + 1] = Vertex(triangle.point2, triangle.color);
        vArray[vPointer + 2] = Vertex(triangle.point3, triangle.color);
        vPointer += 3;
    }

    void VertexBuffer::add(const Rectangle& rectangle) {
        // First make sure that object has a compatiable type
        RENDER_TYPE_ASSERT(RenderMode::Quads);

        // Then ensure that there is enough space for the primitive
        BATCH_SPACE_ASSERT(4);

        // Now time to add all of the vertices to the vertex array
        vArray[vPointer] = Vertex(Vector2(rectangle.point.x, rectangle.point.y));
        vArray[vPointer + 1] = Vertex(Vector2(rectangle.point.x + rectangle.width, rectangle.point.y));
        vArray[vPointer + 2] = Vertex(Vector2(rectangle.point.x, rectangle.point.y + rectangle.height));
        vArray[vPointer + 3] = Vertex(Vector2(rectangle.point.x + rectangle.width, rectangle.point.y + rectangle.height));
        vPointer += 4;
        eBuffer->addPointer();
    }

    unsigned int* VertexBuffer::getIndexArray() {
        return eBuffer->iArray;
    }

    size_t VertexBuffer::getIndexArraySize() {
        return eBuffer->getSize();
    }
}