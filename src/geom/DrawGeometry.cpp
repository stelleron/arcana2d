#include "geom/DrawGeometry.hpp"

namespace arcana {            
    DrawTriangle::DrawTriangle(const Triangle& triangle, const Color& color) {
        this->point1 = triangle.point1;
        this->point2 = triangle.point2;
        this->point3 = triangle.point3;
        this->color = color;
    }
    
    DrawTriangle makeDrawable(const Triangle triangle, const Color color) {
        return DrawTriangle(triangle, color);
    }    
}