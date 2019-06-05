#include "Color.hpp"

namespace conrast { namespace color {


RGB8::RGB8()
    : r(0), g(0), b(0)
{}

RGB8::RGB8(uint8_t r, uint8_t g, uint8_t b)
    : r(r), g(g), b(b)
{}

RGB8::RGB8(RGB32f color)
    : r(static_cast<uint8_t>(color.r * 255.0f)),
      g(static_cast<uint8_t>(color.g * 255.0f)),
      b(static_cast<uint8_t>(color.b * 255.0f))
{}

uint8_t RGB8::operator[](size_t index) {
    index = index % 3;
    switch (index) {
        case 0: return r;
        case 1: return g;
        case 2: return b;
        default: return 0; // not reachable, suppress warning
    }
}

RGB32f::RGB32f()
    : RGB32f( 0.0f, 0.0f, 0.0f )
{}


RGB32f::RGB32f(float r, float g, float b)
    : r(r),
      g(g),
      b(b)
{}

RGB32f::RGB32f(RGB8 color)
    : r(static_cast<float>(color.r) / 255.0f),
      g(static_cast<float>(color.g) / 255.0f),
      b(static_cast<float>(color.b) / 255.0f)
{}

float RGB32f::operator[](size_t index) {
    index = index % 3;
    switch (index) {
        case 0: return r;
        case 1: return g;
        case 2: return b;
        default: return 0.0f; // not reachable, suppress warning
    }
}

RGB32f RGB32f::operator*(float factor) const {
    return {
        r * factor,
        g * factor,
        b * factor
    };
}

RGB32f& RGB32f::operator*=(float factor) {
    r *= factor;
    g *= factor;
    b *= factor;
    return *this;
}

RGB32f RGB32f::operator+(const RGB32f& other) const {
    return {
        r + other.r,
        g + other.g,
        b + other.b
    };
}

}}
