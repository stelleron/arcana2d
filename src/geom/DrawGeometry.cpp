#include "geom/DrawGeometry.hpp"

namespace arcana {            
    DrawTriangle::DrawTriangle(const Triangle& triangle, const Color& color) {
        this->point1 = triangle.point1;
        this->point2 = triangle.point2;
        this->point3 = triangle.point3;
        this->color = color;
        this->z = 0.0f;
    }

    DrawTriangle::DrawTriangle(const Triangle& triangle, const Color& color, float z) {
        this->point1 = triangle.point1;
        this->point2 = triangle.point2;
        this->point3 = triangle.point3;
        this->color = color;
        this->z = z;
    }
    
    namespace drawable {
        DrawTriangle make(const Triangle triangle, const Color color) {
            return DrawTriangle(triangle, color);
        }  
        DrawTriangle make(const Triangle triangle, const Color color, const float z) {
            return DrawTriangle(triangle, color, z);
        }   
    }
}