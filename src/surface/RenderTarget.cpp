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


utils::Vec2i RenderTarget::convertScreenToRaster(utils::Vec2f screenPos) const {
    return {
        static_cast<int>((m_SIZE.x / 2) + screenPos.x * (m_SIZE.x / 2)),
        static_cast<int>((m_SIZE.y / 2) + screenPos.y * (m_SIZE.y / 2))
    };
}

utils::Vec2f RenderTarget::convertRasterToScreen(utils::Vec2i rasterPos) const {
    utils::Vec2f halfSize{ static_cast<float>(m_SIZE.x) * 0.5f, static_cast<float>(m_SIZE.y) * 0.5f };
    return {
        (static_cast<float>(rasterPos.x) - halfSize.x) / halfSize.x,
        (static_cast<float>(rasterPos.y) - halfSize.y) / halfSize.y
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
