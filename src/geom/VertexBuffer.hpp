#ifndef ARCANA2D_VERTEX_BUFFER
    #define ARCANA2D_VERTEX_BUFFER
    // Includes
    #include "geom/Vertex.hpp"
    #include "geom/Geometry.hpp"

    namespace arcana {
        // Enum for draw modes
        enum RenderMode {
            Lines,
            Triangles,
            Quads
        };

        // Used to create a vertex buffer with a fixed size
        struct VertexBuffer {
            Vertex* vArray;

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

            // Used to add objects to the vertex buffer 
            VertexBuffer& operator<<(const Triangle& triangle);
        };
    }
#endif