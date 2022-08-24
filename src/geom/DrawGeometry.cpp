#include "geom/DrawGeometry.hpp"

namespace arcana {            
    DrawTriangle::DrawTriangle(const Triangle& triangle, const Color& color) {
        this->point1 = triangle.point1;
        this->point2 = triangle.point2;
        this->point3 = triangle.point3;
        this->color = color;
        this->z_value = 0.0f;
    }

    DrawTriangle::DrawTriangle(const Triangle& triangle, const Color& color, const float& z_value) {
        this->point1 = triangle.point1;
        this->point2 = triangle.point2;
        this->point3 = triangle.point3;
        this->color = color;
        this->z_value = z_value;
    }
    
    
    DrawTriangle makeDrawable(const Triangle triangle, const Color color) {
        return DrawTriangle(triangle, color);
    }

    DrawTriangle makeDrawable(const Triangle triangle, const Color color, const float z_value) {
        return DrawTriangle(triangle, color, z_value);
    }     
}