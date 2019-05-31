#include "ConsoleSurface.hpp"

#include <iostream>

namespace conrast { namespace surface {

ConsoleSurface::ConsoleSurface(uint16_t width, uint16_t height)
    : Surface(width, height)
{}


void ConsoleSurface::display() const {
    auto drawHorizontalLine = [=](){
        std::cout << "\033[0m";
        for(int i = 0; i < m_SIZE.x + 2; i++) {
            std::cout << "-";
        }
        std::cout << '\n';
    };

    drawHorizontalLine();
    int x = 0;
    for (auto pixel : m_pixels) {
        if(x == 0) {
            std::cout << "\033[0m|";
        }
        showPixel(pixel);
        if(++x >= m_SIZE.x) {
            std::cout << "\033[0m|\n";
            x = 0;
        }
    }
    drawHorizontalLine();
}


void ConsoleSurface::showPixel(color::Color color) const {
    AsciiColor asciiColor(color);
    std::string format = "\033[0;";
    switch (asciiColor.dimming) {
        case AsciiColor::Dimming::Dim: format += "2;"; break;
        case AsciiColor::Dimming::Bright: format += "1;"; break;
        default: break;
    }
    format += std::to_string(asciiColor.value) + "m";
    std::cout << format << "\u2588";
}

}}
