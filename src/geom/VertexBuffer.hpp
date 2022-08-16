#ifndef ARCANA2D_VERTEX_BUFFER
    #define ARCANA2D_VERTEX_BUFFER
    // Includes
    #include "geom/Vertex.hpp"
    #include "geom/Geometry.hpp"
    #include "geom/DrawGeom.hpp"

    namespace arcana {
        // Enum for draw modes
        enum RenderMode {
            Lines,
            Triangles,
            Quads
        };

        // Used to create a buffer to track elements 
        struct ElementBuffer {
            unsigned int* iArray; // List of indices

            int iSize; // Capacity of indices in the buffer
            int iPointer; // Points to the current indices
            int iValue; // Stores the current index value
            int numIndices; // Number of indices per object

            RenderMode rMode;

            // Constructor
            ElementBuffer(RenderMode rMode, int size);

            // Destructor
            ~ElementBuffer();

            // Check space
            bool checkSpace();

            // Add an object to the indices array
            void add();

            // Get the size of indices array
            size_t getIndicesSize();
        };

        // Used to create a vertex buffer with a fixed size
        struct VertexBuffer {
            Vertex* vArray;
            ElementBuffer* eBuffer; // Pointer to element buffer

            int vSize; // Number of vertices
            int vPointer; // The number of added vertices to the vertex array
            int primSize; // The size of the primitive

            RenderMode rMode;

            // Constructor
            VertexBuffer(RenderMode rMode, int size);
            
            // Destructor
            ~VertexBuffer();

            // Check if there is space to add an object
            bool checkSpace(int numVertices);

            // Convert the vertex array into a float array (heap allocated)
            float* getFloatArray();

            // Get the size of the array
            size_t getArraySize();

            // Get the render type of the buffer 
            inline RenderMode getRenderType() {return rMode;} 

            // Used to add objects to the vertex buffer 
            VertexBuffer& operator<<(const Triangle& triangle);
            VertexBuffer& operator<<(const DrawTriangle& triangle);

            VertexBuffer& operator<<(const Rectangle& rectangle);
        };
    }
#endif