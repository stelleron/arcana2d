#include "geom/Vertex.hpp"

namespace arcana {
    Vertex::Vertex(Vector2 pos, Color color) {
        this->pos = pos;
        this->color = color;
        this->texCoords = Vector2(0.0, 0.0);
    }

    Vertex::Vertex(Vector2 pos, Color color, Vector2 texCoords) {
        this->pos = pos;
        this->color = color;
        this->texCoords = texCoords;
    }
}