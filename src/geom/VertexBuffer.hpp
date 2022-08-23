#ifndef ARCANA2D_VERTEX_BUFFER
    #define ARCANA2D_VERTEX_BUFFER
    // Includes
    #include "geom/Vertex.hpp"
    #include "geom/Geometry.hpp"
    #include "geom/DrawGeometry.hpp"

    namespace arcana {
        // Enum for draw modes
        enum RenderMode {
            Points,
            Lines,
            Triangles,
            Quads,
            Circle
        };

        // Used to create a buffer to track elements 
        struct ElementBuffer {
            unsigned int* iArray; // List of indices
            int iSize; // Capacity of indices in the buffer
            int iPointer; // Points to the current indices
            int iValue; // Stores the current index value
            int numIndices; // Number of indices per object
            RenderMode rMode; // The render mode of the element buffer

            // Constructor
            ElementBuffer(RenderMode rMode, int size);
            // Destructor
            ~ElementBuffer();

            // Check space, returns True if space is available
            bool checkSpace();
            // Add an object to the indices array
            void add();
            // Get the size of indices array
            size_t getIndicesSize();
        };

        // Used to create a vertex array buffer with a fixed size
        struct VertexBuffer {
            Vertex* vArray; // List of vertices
            ElementBuffer* eBuffer; // Pointer to element buffer
            int vSize; // Number of vertices
            int vPointer; // The number of added vertices to the vertex array
            int primSize; // The size of the primitive
            RenderMode rMode; // Render mode

            // Constructor
            VertexBuffer(RenderMode rMode, int primNum);
            // Destructor
            ~VertexBuffer();

            // Check if there is space to add an object, returns True if available
            bool checkSpace(int numVertices);

            // Convert the vertex array into a float array (heap allocated)
            float* getFloatArray();
            // Get the size of the array
            size_t getArraySize();
            // Get the render type of the buffer 
            inline RenderMode getRenderType() {return rMode;} 

            // Used to add objects to the vertex buffer 
            void add(const Triangle& triangle);
            void add(const DrawTriangle& triangle);

            void add(const Rectangle& rectangle);
        };
    }
#endif