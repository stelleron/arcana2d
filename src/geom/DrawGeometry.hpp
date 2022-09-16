#ifndef ARCANA2D_DRAW_GEOMETRY
    #define ARCANA2D_DRAW_GEOMETRY
    // Includes
    #include "utils/Color.hpp"
    #include "geom/Geometry.hpp"

    namespace arcana {
        // Used to create a triangle with color
        struct DrawTriangle : public Triangle {
            Color color;
            DrawTriangle(const Triangle& triangle, const Color& color);
        };

        // Used to make drawable objects
        DrawTriangle makeDrawable(const Triangle triangle, const Color color);
    }
#endif