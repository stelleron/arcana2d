#include "utils/Color.hpp"
namespace arcana {
    Color::Color() {

    }

    Color::Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    }
}