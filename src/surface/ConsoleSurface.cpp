#include "ConsoleSurface.hpp"

#include <iostream>

namespace conrast { namespace surface {

ConsoleSurface::ConsoleSurface(uint16_t width, uint16_t height)
    : Surface(width, height)
{}


void ConsoleSurface::display() const {
    auto drawHorizontalLine = [=](){
        for(int i = 0; i < m_SIZE.x + 2; i++) {
            std::cout << "-";
        }
        std::cout << '\n';
    };

    drawHorizontalLine();
    int x = 0;
    for (auto pixel : m_pixels) {
        if(x == 0) {
            std::cout << "|";
        }
        std::cout << mapPixel(pixel);
        if(++x >= m_SIZE.x) {
            std::cout << "|\n";
            x = 0;
        }
    }
    drawHorizontalLine();
}


char ConsoleSurface::mapPixel(color::Color color) const {
    // Map color to shade value of range [0, 1]
    float shade = (color.r + color.g + color.b) / 3.0f;

    if (shade < 0.05f) {
        return ' ';
    }
    else if (shade < 0.25f) {
        return '-';
    }
    else if (shade < 0.5f) {
        return '+';
    }
    else if (shade < 0.75f) {
        return '%';
    }
    return '#';

}

}}
