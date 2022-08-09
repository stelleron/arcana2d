#include "geom/VertexBuffer.hpp"
#include "utils/DebugOnly.hpp"

#define RENDER_TYPE_ASSERT(arg) if (rMode != arg) {LOG("Incorrect type!");  return *this;}

namespace arcana {
    // VERTEX BUFFER IMPL.
    // NOTE: Size is the number of primitives
    VertexBuffer::VertexBuffer(RenderMode rMode, int size) {
        // First get the size of the primitive in vertices
        switch (rMode)
        {
            case Lines: primSize = 2;
            case Triangles: primSize = 3;
            case Quads: primSize = 4;
            default: break;
        }

        // Now allocate memory for the vertices
        vSize = size * primSize;
        vArray = new Vertex[vSize];

        // Save the render mode and set the vertex pointer to 0
        this->rMode = rMode;
        vPointer = 0;
    }

    VertexBuffer::~VertexBuffer() {
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

    VertexBuffer& VertexBuffer::operator<<(const Triangle& triangle) {
        // First make sure that object has a compatiable type
        RENDER_TYPE_ASSERT(RenderMode::Triangles);

        // Then ensure that there is enough space for the primitive
        if (!checkSpace(3)) {
            LOG("Not enough space!");
            return *this;
        }

        // Now time to add all of the vertices to the vertex array
        vArray[vPointer] =

        // Return the 'this' pointer
        return *this;
    }
}