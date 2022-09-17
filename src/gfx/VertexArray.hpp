#ifndef ARCANA2D_VERTEX_ARRAY
    #define ARCANA2D_VERTEX_ARRAY
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
            Circles
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
        struct VertexArray {
            private:
                ElementBuffer* eBuffer; // Pointer to element buffer
                Vertex* vArray; // List of vertices
                int vSize; // Number of vertices
                int primSize; // The size of the primitive
                RenderMode rMode; // Render mode
            public:
                // Constructor
                VertexArray(RenderMode rMode, int vertexNum);
                // Destructor
                ~VertexArray();

                // Check if there is space to add an object, returns True if available
                bool checkSpace(int startIndex, int numVertices);

                // Clear the vertex buffer
                void clear();

                // Get vertex array
                Vertex* getVertexArray();
                // Get the size of the vertex array
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
                void add(const Point& point, int startIndex);
                void add(const DrawPoint& point, int startIndex);

                void add(const Line& line, int startIndex);
                void add(const DrawLine& line, int startIndex);

                void add(const Triangle& triangle, int startIndex);
                void add(const DrawTriangle& triangle, int startIndex);

                void add(const Rectangle& rectangle, int startIndex);
                void add(const Quadrilateral& quad, int startIndex);
                void add(const DrawQuad& quad, int startIndex);

                void add(const Circle& circle, int startIndex);
                void add(const DrawCircle& circle, int startIndex);
        };
    }
#endif