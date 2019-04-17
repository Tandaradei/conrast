#include "RenderTarget.hpp"

#include <cmath>

namespace conrast { namespace surface {

RenderTarget::RenderTarget(int width, int height)
    : m_SIZE({width, height})
{
    m_pixels.resize(m_SIZE.x * m_SIZE.y);
}


void RenderTarget::drawPixel(utils::Vec2i rasterPos, float depth, color::Color color) {
    if(rasterPos.x < 0 || rasterPos.x >= m_SIZE.x || rasterPos.y < 0 || rasterPos.y >= m_SIZE.y) {
        return;
    }
    auto& pixel = m_pixels[rasterPos.y * m_SIZE.x + rasterPos.x];
    if(depth <= pixel.depth) {
        m_pixels[rasterPos.y * m_SIZE.x + rasterPos.x] = { color, depth };
    }
}


utils::Vec2i RenderTarget::convertScreenToRaster(utils::Vec2f screen_pos) const {
    return {
        static_cast<int>((m_SIZE.x / 2) + screen_pos.x * (m_SIZE.x / 2)),
        static_cast<int>((m_SIZE.y / 2) + screen_pos.y * (m_SIZE.y / 2))
    };
}

void RenderTarget::clear(color::Color color) {
    for(auto& pixel: m_pixels) {
        pixel.color = color;
        pixel.depth = 10000.0f;
    }
}


utils::Vec2i RenderTarget::getSize() const {
    return m_SIZE;
}

} }
