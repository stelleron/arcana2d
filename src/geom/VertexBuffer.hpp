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
            unsigned int* iArray;
            size_t totalSize;

            // Constructor
            ElementBuffer(RenderMode rMode, int size);
            // Destructor 
            ~ElementBuffer();

            // Setters/getters
            size_t getSize();
        };
        
        // Used to create a vertex array buffer with a fixed size
        struct VertexBuffer {
            private:
                ElementBuffer* eBuffer; // Pointer to element buffer
                Vertex* vArray; // List of vertices
                int vSize; // Number of vertices
                int primSize; // The size of the primitive
                RenderMode rMode; // Render mode
            public:
                // Constructor
                VertexBuffer(RenderMode rMode, int vertexNum);
                // Destructor
                ~VertexBuffer();

                // Check if there is space to add an object, returns True if available
                bool checkSpace(int startIndex, int numVertices);

                // Convert the vertex array into a float array (heap allocated)
                float* getFloatArray();
                // Get the size of the array
                size_t getArraySize();
                // Get the render type of the buffer 
                inline RenderMode getRenderType() {return rMode;}
                // Get the index array
                unsigned int* getIndexArray();
                // Get the size of the index array
                size_t getIndexArraySize();
                // Set an induvidual vertex with the array operator
                Vertex& operator[](int index);
                // Get an induvidual vertex with the array operator
                Vertex operator[](int index) const;

                // Used to add objects to the vertex buffer 
                void add(const Triangle& triangle, int startIndex);
                void add(const DrawTriangle& triangle, int startIndex);

                void add(const Rectangle& rectangle, int startIndex);
        };
    }
#endif