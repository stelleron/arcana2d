#ifndef ARCANA2D_DRAW_GEOM
    #define ARCANA2D_DRAW_GEOM
    // Includes
    #include "utils/Color.hpp"
    #include "geom/Geometry.hpp"

    namespace arcana {
        // Used to create a triangle with color
        struct DrawTriangle : public Triangle {
            Color color;
            DrawTriangle(const Triangle& triangle, const Color& color) {
                this->point1 = triangle.point1;
                this->point2 = triangle.point2;
                this->point3 = triangle.point3;
                this->color = color;
            }
        };

        // Used to make drawable objects
        DrawTriangle makeDrawable(const Triangle triangle, const Color color);
    }
#endif