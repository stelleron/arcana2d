#include "utils/Color.hpp"
#include <tgmath.h>

namespace arcana {
    Color::Color() {
        r = 0;
        g = 0;
        b = 0;
        a = 0;
    }


    Color::Color(unsigned char r, unsigned char g, unsigned char b) {
        this->r = r;
        this->g = g;
        this->b = b;
        a = 255;
    }

    Color::Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    }

    Color::Color(float r_normal, float g_normal, float b_normal) {
        this->r = (unsigned char)(r_normal * 255.0f);
        this->g = (unsigned char)(g_normal * 255.0f);
        this->b = (unsigned char)(b_normal * 255.0f);
        this->a = 255;
    }

    Color::Color(float r_normal, float g_normal, float b_normal, float a_normal) {
        this->r = (unsigned char)(r_normal * 255.0f);
        this->g = (unsigned char)(g_normal * 255.0f);
        this->b = (unsigned char)(b_normal * 255.0f);
        this->a = (unsigned char)(a_normal * 255.0f);
    }

    Color::Color(int hexValue) {
        r = (unsigned char)(hexValue >> 24) & 0xFF;
        g = (unsigned char)(hexValue >> 16) & 0xFF;
        b = (unsigned char)(hexValue >> 8) & 0xFF;
        a = (unsigned char)hexValue & 0xFF;
    }

    Color Color::HSV(float h, float s, float v) {
        unsigned char r,g,b;

        // Red channel
        float k = fmodf((5.0f + h/60.0f), 6);
        float t = 4.0f - k;
        k = (t < k)? t : k;
        k = (k < 1)? k : 1;
        k = (k > 0)? k : 0;
        r = (unsigned char)((v - v*s*k)*255.0f);

        // Green channel
        k = fmodf((3.0f + h/60.0f), 6);
        t = 4.0f - k;
        k = (t < k)? t : k;
        k = (k < 1)? k : 1;
        k = (k > 0)? k : 0;
        g = (unsigned char)((v - v*s*k)*255.0f);

        // Blue channel
        k = fmodf((1.0f + h/60.0f), 6);
        t = 4.0f - k;
        k = (t < k)? t : k;
        k = (k < 1)? k : 1;
        k = (k > 0)? k : 0;
        b = (unsigned char)((v - v*s*k)*255.0f);

        return Color(r,g,b);
    }

    Color Color::HSVA(float h, float s, float v, unsigned char a) {
        unsigned char r,g,b;

        // Red channel
        float k = fmodf((5.0f + h/60.0f), 6);
        float t = 4.0f - k;
        k = (t < k)? t : k;
        k = (k < 1)? k : 1;
        k = (k > 0)? k : 0;
        r = (unsigned char)((v - v*s*k)*255.0f);

        // Green channel
        k = fmodf((3.0f + h/60.0f), 6);
        t = 4.0f - k;
        k = (t < k)? t : k;
        k = (k < 1)? k : 1;
        k = (k > 0)? k : 0;
        g = (unsigned char)((v - v*s*k)*255.0f);

        // Blue channel
        k = fmodf((1.0f + h/60.0f), 6);
        t = 4.0f - k;
        k = (t < k)? t : k;
        k = (k < 1)? k : 1;
        k = (k > 0)? k : 0;
        b = (unsigned char)((v - v*s*k)*255.0f);

        return Color(r,g,b,a);
    }

    Color Color::RGB(unsigned char r, unsigned char g, unsigned char b) {
        return Color(r,g,b);
    }

    Color Color::RGBA(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
        return Color(r,g,b,a);
    }
}