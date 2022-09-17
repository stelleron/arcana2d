#ifndef ARCANA2D_DRAW_GEOMETRY
    #define ARCANA2D_DRAW_GEOMETRY
    // Includes
    #include "utils/Color.hpp"
    #include "geom/Geometry.hpp"

    namespace arcana {
        // Used to create a triangle with color
        struct DrawTriangle : public Triangle {
            Color color;
            float z;
            DrawTriangle(const Triangle& triangle, const Color& color);
            DrawTriangle(const Triangle& triangle, const Color& color, float z);
        };

        // Used to make drawable objects
        namespace drawable
        {
            DrawTriangle make(const Triangle triangle, const Color color);
            DrawTriangle make(const Triangle triangle, const Color color, const float z);
        }
    }
#endif