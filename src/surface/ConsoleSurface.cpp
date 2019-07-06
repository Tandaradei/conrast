#include "ConsoleSurface.hpp"

#include <iostream>
#include <algorithm>
#include <string>

namespace conrast { namespace surface {

ConsoleSurface::ConsoleSurface(utils::Vec2i resolution)
	:Surface(resolution)
{}


void ConsoleSurface::display(const render::RenderTarget& renderTarget) const {
	const auto size = renderTarget.getSize();
	const utils::Vec2f resolutionScaling = utils::Vec2f{
		static_cast<float>(size.x) / static_cast<float>(m_resolution.x),
		static_cast<float>(size.y) / static_cast<float>(m_resolution.y)
	};

    auto drawHorizontalLine = [=](){
        std::cout << "\033[0m";
        for(int i = 0; i < m_resolution.x + 2; i++) {
            std::cout << "-";
        }
        std::cout << '\n';
    };

    drawHorizontalLine();
    unsigned int x = 0;
	const auto& pixels = renderTarget.getPixels();
	for (float y = 0.0f; y < static_cast<float>(m_resolution.y); y += 1.0f) {
		std::cout << "\033[0m|";
		for (float x = 0.0f; x < static_cast<float>(m_resolution.x); x += 1.0f) {
			size_t pixelIndex = static_cast<size_t>(y * resolutionScaling.y) * size.x +static_cast<size_t>(x * resolutionScaling.x);
			showPixel(pixels[pixelIndex]);
		}
		std::cout << "\033[0m|\n";
	}

    drawHorizontalLine();
}


ConsoleSurface::AsciiColor::AsciiColor(color::RGB8 color) :
	dimming(Dimming::Normal),
	value(30) 
{
	value += color.r > 0.5f ? 1 : 0;
	value += color.g > 0.5f ? 2 : 0;
	value += color.b > 0.5f ? 4 : 0;
	float shade = std::max(color.r, std::max(color.g, color.b));
	if (shade < 255 / 3) {
		dimming = Dimming::Dim;
	}
	else if (shade < 2 * 255 / 3) {
		dimming = Dimming::Normal;
	}
	else {
		dimming = Dimming::Bright;
	}
}


void ConsoleSurface::showPixel(color::RGB8 color) const {
    AsciiColor asciiColor(color);
    std::string format = "\033[0;";
    switch (asciiColor.dimming) {
        case AsciiColor::Dimming::Dim: format += "2;"; break;
        case AsciiColor::Dimming::Bright: format += "1;"; break;
        default: break;
    }
    format += std::to_string(asciiColor.value) + "m";
#ifdef _WIN32
    std::cout << format << static_cast<char>(219);
#else
	std::cout << format << "\u2588";
#endif
}

}}
