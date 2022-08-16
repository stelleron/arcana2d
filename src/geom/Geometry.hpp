#ifndef ARCANA2D_GEOMETRY
    #define ARCANA2D_GEOMETRY
    // Includes
    #include "geom/Vertex.hpp"

    namespace arcana {
        // Used to create a line object
        struct Line {
            Vector2 startPoint;
            Vector2 endPoint;
        };
        // Used to create a triangle
        struct Triangle {
            Vector2 point1;
            Vector2 point2;
            Vector2 point3;
        };
        // Used to create a rectangle
        struct Rectangle {
            Vector2 point;
            int width;
            int height;
        };
        // Used to create a circle
        struct Circle {
            Vector2 center;
            int radius;
        };        
    }
#endif