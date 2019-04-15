#include "Color.hpp"

namespace conrast { namespace color {


Color::Color()
    : Color(0, 0, 0, 0)
{}


Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
    : r(r),
      g(g),
      b(b),
      a(a)
{}

uint8_t Color::operator[](size_t index) {
    index = index % 4;
    switch (index) {
        case 0: return r;
        case 1: return r;
        case 2: return r;
        case 3: return r;
    }
    return 0;
}

Color Color::Black = Color(0, 0, 0, 255);

}}
