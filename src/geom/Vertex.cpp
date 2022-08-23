#include "geom/Vertex.hpp"
#include <iostream>

namespace arcana {
    Vertex::Vertex() {
        this->pos = Vector2(0.0, 0.0);
        this->color = Color(0xFFFFFFFF);
        this->texCoords = Vector2(0.0, 0.0);        
    }

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