#ifndef ARCANA2D_VERTEX
    #define ARCANA2D_VERTEX
    // Includes
    #include <glm/glm.hpp>
    #include "utils/Color.hpp"

    // Macro defines
    #define VERTEX_FSIZE sizeof(float) * 8

    namespace arcana {
        // Namespace defines
        using Vector2 = glm::vec2;

        // Used to create a vertex object
        struct Vertex {
            Vector2 pos;
            Color color;
            Vector2 texCoords;

            // Constructor
            Vertex() {}
            Vertex(Vector2 pos, Color color);
            Vertex(Vector2 pos, Color color, Vector2 texCoords);
        };
    }
#endif