#include "RenderTarget.hpp"

#include <cmath>

namespace conrast { namespace render {

RenderTarget::RenderTarget(int width, int height)
    : m_SIZE({width, height})
{
    m_pixels.resize(static_cast<size_t>(m_SIZE.x * m_SIZE.y));
}


void RenderTarget::drawPixel(utils::Vec2i rasterPos, color::RGB8 color) {
    if(rasterPos.x < 0 || rasterPos.x >= m_SIZE.x || rasterPos.y < 0 || rasterPos.y >= m_SIZE.y) {
        return;
    }
    m_pixels[static_cast<size_t>(rasterPos.y * m_SIZE.x + rasterPos.x)] = color;
}


void RenderTarget::clear(color::RGB8 color) {
    for(auto& pixel: m_pixels) {
        pixel= color;
    }
}


utils::Vec2i RenderTarget::getSize() const {
    return m_SIZE;
}

} }
