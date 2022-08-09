#ifndef ARCANA2D_VERTEX_BUFFER
    #define ARCANA2D_VERTEX_BUFFER
    // Includes
    #include "geom/Vertex.hpp"

    namespace arcana {
        // Used to create a vertex buffer with a fixed size
        struct VertexBuffer {
            Vertex* vArray;
            int size;

            // Constructors
            VertexBuffer();
            
            // Destructors
            ~VertexBuffer();
        };
    }
#endif