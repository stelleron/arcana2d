#include "utils/Logger.hpp"
#include "gfx/VertexArray.hpp"


#define RENDER_TYPE_ASSERT(arg) if (rMode != arg) {ERROR("Error: Vertex buffer is not the correct type!"); return;}
#define BATCH_SPACE_ASSERT(start, value) if (!checkSpace(start, value)) {ERROR("Error: Vertex buffer does not have enough space!"); return;}
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
    }

    ElementBuffer::~ElementBuffer() {
        delete[] iArray;
    }

    size_t ElementBuffer::getSize() {
        return totalSize;
    }
 
    // VERTEX BUFFER IMPL.
    // NOTE: Size is the number of primitives
    VertexArray::VertexArray(RenderMode rMode, int vertexNum) {
        // First get the size of the primitive in vertices
        eBuffer = nullptr;
        switch (rMode)
        {
            case Lines: primSize = 2; break;
            case Triangles: primSize = 3; break;
            case Quads: primSize = 4; eBuffer = new ElementBuffer(rMode, vertexNum/primSize); break;
            default: break;
        }

        // Now allocate memory for the vertices
        vSize = vertexNum;
        vArray = new Vertex[vSize];

        // Save the render mode and set the vertex pointer to 0
        this->rMode = rMode;
    }

    VertexArray::~VertexArray() {
        if (eBuffer != nullptr) {
            delete eBuffer;
        }
        delete[] vArray;
    }

    void VertexArray::clear() {
        // First erase vertex data
        delete[] vArray;
        // Then reallocate them
        vArray = new Vertex[vSize];
    }

    bool VertexArray::checkSpace(int startIndex, int numVertices) {
        if (numVertices + startIndex <= vSize) {
            return true;
        }
        else {
            return false;
        }
    }

    size_t VertexArray::getArraySize() {
        return vSize * sizeof(Vertex);
    }

    Vertex* VertexArray::getVertexArray() {
        return vArray;
    }

    void VertexArray::add(const Triangle& triangle, int startIndex) {
        // First make sure that object has a compatiable type
        RENDER_TYPE_ASSERT(RenderMode::Triangles);

        // Then ensure that there is enough space for the primitive
        BATCH_SPACE_ASSERT(startIndex, 3);

        // Now time to add all of the vertices to the vertex array
        vArray[startIndex] = Vertex(triangle.point1);
        vArray[startIndex + 1] = Vertex(triangle.point2);
        vArray[startIndex + 2] = Vertex(triangle.point3);
    }

    void VertexArray::add(const DrawTriangle& triangle, int startIndex) {
        // First make sure that object has a compatiable type
        RENDER_TYPE_ASSERT(RenderMode::Triangles);

        // Then ensure that there is enough space for the primitive
        BATCH_SPACE_ASSERT(startIndex, 3);

        // Now time to add all of the vertices to the vertex array
        vArray[startIndex] = Vertex(triangle.point1, triangle.color);
        vArray[startIndex + 1] = Vertex(triangle.point2, triangle.color);
        vArray[startIndex + 2] = Vertex(triangle.point3, triangle.color);
    }

    void VertexArray::add(const Rectangle& rectangle, int startIndex) {
        // First make sure that object has a compatiable type
        RENDER_TYPE_ASSERT(RenderMode::Quads);

        // Then ensure that there is enough space for the primitive
        BATCH_SPACE_ASSERT(startIndex, 4);

        // Now time to add all of the vertices to the vertex array
        vArray[startIndex] = Vertex(Vector2(rectangle.point.x, rectangle.point.y));
        vArray[startIndex + 1] = Vertex(Vector2(rectangle.point.x + rectangle.width, rectangle.point.y));
        vArray[startIndex + 2] = Vertex(Vector2(rectangle.point.x, rectangle.point.y + rectangle.height));
        vArray[startIndex + 3] = Vertex(Vector2(rectangle.point.x + rectangle.width, rectangle.point.y + rectangle.height));
    }

    unsigned int* VertexArray::getIndexArray() {
        return eBuffer->iArray;
    }

    size_t VertexArray::getIndexArraySize() {
        return eBuffer->getSize();
    }

    Vertex& VertexArray::operator[](int index) {
        if (index >= vSize) {
            ERROR("Error: Index out of range!");
            exit(0);
        }
        return vArray[index];
    }

    Vertex VertexArray::operator[](int index) const {
        if (index >= vSize) {
            ERROR("Error: Index out of range!");
            exit(0);
        }
        return vArray[index];
    }
}