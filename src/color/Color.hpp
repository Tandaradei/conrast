#ifndef COLOR_HPP
#define COLOR_HPP

#include <stdint.h>
#include <unistd.h>

namespace conrast { namespace color {

class Color
{
public:
    Color();
    Color(float r, float g, float b, float a);
    float operator[](size_t index);

    Color operator*(float factor) const;
    Color operator+(const Color& other) const;

public:
    float r;
    float g;
    float b;
    float a;

    static Color Black;
};


}}

#endif // COLOR_HPP
