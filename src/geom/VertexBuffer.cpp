#include "geom/VertexBuffer.hpp"
#include "utils/DebugOnly.hpp"

#define RENDER_TYPE_ASSERT(arg) if (rMode != arg) {LOG("Incorrect type!");  return *this;}
#define BATCH_SPACE_ASSERT(arg) if (!checkSpace(arg)) {LOG("Not enough space!"); return *this;}
#define TIMES_SIX(arg) (x * 6)

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

    size_t VertexBuffer::getArraySize() {
        return vPointer * VERTEX_FSIZE;
    }

    float* VertexBuffer::getFloatArray() {
        // First create a float array
        float* fArray = new float[getArraySize()/sizeof(float)];

        // Now copy all vertex data into the float array
        for (int x = 0; x < vPointer; x++) {
            LOG("Vertex number " << x + 1);
            fArray[TIMES_SIX(x)] = vArray[x].pos.x;
            fArray[TIMES_SIX(x) + 1] = vArray[x].pos.y;
            fArray[TIMES_SIX(x) + 2] = FLOAT_REP(vArray[x].color.r);
            fArray[TIMES_SIX(x) + 3] = FLOAT_REP(vArray[x].color.g);
            fArray[TIMES_SIX(x) + 4] = FLOAT_REP(vArray[x].color.b);
            fArray[TIMES_SIX(x) + 5] = FLOAT_REP(vArray[x].color.a);
        }

        // And return the array
        return fArray;
    }

    VertexBuffer& VertexBuffer::operator<<(const Triangle& triangle) {
        // First make sure that object has a compatiable type
        RENDER_TYPE_ASSERT(RenderMode::Triangles);

        // Then ensure that there is enough space for the primitive
        BATCH_SPACE_ASSERT(3);

        // Now time to add all of the vertices to the vertex array
        vArray[vPointer] = Vertex(triangle.point1, RED);
        vArray[vPointer + 1] = Vertex(triangle.point2, BLUE);
        vArray[vPointer + 2] = Vertex(triangle.point3, GREEN);
        vPointer += 3;

        // Return the 'this' pointer
        return *this;
    }

    VertexBuffer& VertexBuffer::operator<<(const DrawTriangle& triangle) {
        // First make sure that object has a compatiable type
        RENDER_TYPE_ASSERT(RenderMode::Triangles);

        // Then ensure that there is enough space for the primitive
        BATCH_SPACE_ASSERT(3);

        // Now time to add all of the vertices to the vertex array
        vArray[vPointer] = Vertex(triangle.point1, triangle.color);
        vArray[vPointer + 1] = Vertex(triangle.point2, triangle.color);
        vArray[vPointer + 2] = Vertex(triangle.point3, triangle.color);
        vPointer += 3;

        // Return the 'this' pointer
        return *this;
    }
}