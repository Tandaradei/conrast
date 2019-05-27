#include "Color.hpp"

namespace conrast { namespace color {


Color::Color()
    : Color( 0.0f, 0.0f, 0.0f, 1.0f )
{}


Color::Color(float r, float g, float b, float a)
    : r(r),
      g(g),
      b(b),
      a(a)
{}

float Color::operator[](size_t index) {
    index = index % 4;
    switch (index) {
        case 0: return r;
        case 1: return r;
        case 2: return r;
        case 3: return r;
    }
    return 0;
}

Color Color::operator*(float factor) const {
    return {
        r * factor,
        g * factor,
        b * factor,
        a * factor
    };
}

Color Color::operator+(const Color& other) const {
    return {
        r + other.r,
        g + other.g,
        b + other.b,
        a + other.a
    };
}

Color Color::Black = Color{ 0.0f, 0.0f, 0.0f, 1.0f };
Color Color::White = Color{ 1.0f, 1.0f, 1.0f, 1.0f };
Color Color::Grey = Color{ 0.5f, 0.5f, 0.5f, 1.0f };
Color Color::Red = Color{ 1.0f, 0.0f, 0.0f, 1.0f };
Color Color::Green = Color{ 0.0f, 1.0f, 0.0f, 1.0f };
Color Color::Blue = Color{ 0.0f, 0.0f, 1.0f, 1.0f };

}}
