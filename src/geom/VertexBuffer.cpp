#include "geom/VertexBuffer.hpp"
#include "utils/DebugOnly.hpp"

#define RENDER_TYPE_ASSERT(arg) if (rMode != arg) {LOG("Incorrect type!");  return *this;}
#define BATCH_SPACE_ASSERT(arg) if (!checkSpace(arg)) {LOG("Not enough space!"); return *this;}
#define TIMES_EIGHT(arg) (x * 8)

namespace arcana {
    // ELEMENT BUFFER IMPL.
    ElementBuffer::ElementBuffer(RenderMode rMode, int size) {
        this->rMode = rMode;
        iPointer = 0;
        iValue = 0;

        switch (rMode)
        {
            case RenderMode::Quads:
                numIndices = 6; // 6 indices per quad
                break;
            default: break;
        }

        iSize = numIndices * size; 
        iArray = new unsigned int[iSize];
    }

    ElementBuffer::~ElementBuffer() {
        delete[] iArray;
    }

    bool ElementBuffer::checkSpace() {
        if (iPointer + numIndices <= iSize) {
            return true;
        }
        else {
            return false;
        }
    }

    void ElementBuffer::add() {
        if (!checkSpace()) {
            LOG("Not enough space!");
            return;
        }

        switch (rMode)
        {
            case RenderMode::Quads:
                iArray[iPointer] = iValue;
                iArray[iPointer + 1] = iValue + 1;
                iArray[iPointer + 2] = iValue + 2;
                iArray[iPointer + 3] = iValue + 1;
                iArray[iPointer + 4] = iValue + 2;
                iArray[iPointer + 5] = iValue + 3;
                iPointer += 6;
                iValue += 4;
                break;
            default:
                break;
        }
    }

    size_t ElementBuffer::getIndicesSize() {
        return sizeof(unsigned int) * iPointer;
    }

 
    // VERTEX BUFFER IMPL.
    // NOTE: Size is the number of primitives
    VertexBuffer::VertexBuffer(RenderMode rMode, int size) {
        // First get the size of the primitive in vertices
        eBuffer = nullptr;
        switch (rMode)
        {
            case Lines: primSize = 2; break;
            case Triangles: primSize = 3; break;
            case Quads: primSize = 4; eBuffer = new ElementBuffer(rMode, size); break;
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
            fArray[TIMES_EIGHT(x)] = vArray[x].pos.x;
            fArray[TIMES_EIGHT(x) + 1] = vArray[x].pos.y;
            fArray[TIMES_EIGHT(x) + 2] = FLOAT_REP(vArray[x].color.r);
            fArray[TIMES_EIGHT(x) + 3] = FLOAT_REP(vArray[x].color.g);
            fArray[TIMES_EIGHT(x) + 4] = FLOAT_REP(vArray[x].color.b);
            fArray[TIMES_EIGHT(x) + 5] = FLOAT_REP(vArray[x].color.a);
            fArray[TIMES_EIGHT(x) + 6] = vArray[x].texCoords.x;
            fArray[TIMES_EIGHT(x) + 7] = vArray[x].texCoords.y;
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

    VertexBuffer& VertexBuffer::operator<<(const Rectangle& rectangle) {
        // First make sure that object has a compatiable type
        RENDER_TYPE_ASSERT(RenderMode::Quads);

        // Then ensure that there is enough space for the primitive
        BATCH_SPACE_ASSERT(4);

        // And for the element buffer
        if (!eBuffer->checkSpace()) {
            return *this;
        }

        // Now time to add all of the vertices to the vertex array
        vArray[vPointer] = Vertex(Vector2(rectangle.point.x, rectangle.point.y), RED);
        vArray[vPointer + 1] = Vertex(Vector2(rectangle.point.x + rectangle.width, rectangle.point.y), BLUE);
        vArray[vPointer + 2] = Vertex(Vector2(rectangle.point.x, rectangle.point.y + rectangle.height), BLUE);
        vArray[vPointer + 3] = Vertex(Vector2(rectangle.point.x + rectangle.width, rectangle.point.y + rectangle.height), GREEN);

        eBuffer->add();
        vPointer += 4;

        // Return the 'this' pointer
        return *this;        
    }
}