#include "geom/DrawGeom.hpp"

namespace arcana {
    DrawTriangle makeDrawable(const Triangle triangle, const Color color) {
        return DrawTriangle(triangle, color);
    }    
}