#ifndef COLOR_HPP
#define COLOR_HPP

#include <stdint.h>
#include <unistd.h>

namespace conrast { namespace color {

class Color
{
public:
    Color();
    Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
    uint8_t operator[](size_t index);

public:
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;

    static Color Black;
};


}}

#endif // COLOR_HPP
