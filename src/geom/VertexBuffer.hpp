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
            int capacity; // The total number of objects the buffer has been designed for
            int pointer; // The number of objects actually being stored by the vertex buffer
            size_t totalSize;

            // Constructor
            ElementBuffer(RenderMode rMode, int size);
            // Destructor 
            ~ElementBuffer();

            // Setters/getters
            void addPointer();
            size_t getSize();
        };
        
        // Used to create a vertex array buffer with a fixed size
        struct VertexBuffer {
            private:
                ElementBuffer* eBuffer; // Pointer to element buffer
                Vertex* vArray; // List of vertices
                int vSize; // Number of vertices
                int vPointer; // The number of added vertices to the vertex array
                int primSize; // The size of the primitive
                RenderMode rMode; // Render mode
            public:
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
                // Get the index array
                unsigned int* getIndexArray();
                // Get the size of the index array
                size_t getIndexArraySize();
                // Set an induvidual vertex with the array operator
                Vertex& operator[](int index);
                // Get an induvidual vertex with the array operator
                Vertex operator[](int index) const;

                // Used to add objects to the vertex buffer 
                void add(const Triangle& triangle);
                void add(const DrawTriangle& triangle);

                void add(const Rectangle& rectangle);
        };
    }
#endif