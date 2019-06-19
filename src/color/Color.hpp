#ifndef COLOR_HPP
#define COLOR_HPP

#include <stdint.h>
#ifndef _WIN32
#include <unistd.h>
#endif

namespace conrast { namespace color {

class RGB32f;

class RGB8 {
public:
    RGB8();
    RGB8(uint8_t r, uint8_t g, uint8_t b);
    RGB8(RGB32f color);

    uint8_t operator[](size_t index);
public:
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

class RGB32f {
public:
    RGB32f();
    RGB32f(float r, float g, float b);
    RGB32f(RGB8 color);
    RGB32f operator*(float factor) const;
    RGB32f& operator*=(float factor);
    RGB32f operator+(const RGB32f& other) const;

    float operator[](size_t index);
public:
    float r;
    float g;
    float b;
};


static const RGB8 Black = { 0, 0, 0};
static const RGB8 White = { 255, 255, 255 };
static const RGB8 Grey = { 127, 127, 127 };
static const RGB8 Red = { 255, 0, 0 };
static const RGB8 Green = { 0, 255, 0 };
static const RGB8 Blue = { 0, 0, 255 };


}}

#endif // COLOR_HPP
