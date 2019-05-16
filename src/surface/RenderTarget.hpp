#ifndef RENDERTARGET_HPP
#define RENDERTARGET_HPP

#include <vector>

#include "utils/Vec.hpp"
#include "color/Color.hpp"

namespace conrast { namespace surface {

class RenderTarget
{
public:
    RenderTarget(int width, int height);

    void drawPixel(utils::Vec2i rasterPos, float depth, color::Color color);
    utils::Vec2i convertScreenToRaster(utils::Vec2f screenPos) const;
    utils::Vec2f convertRasterToScreen(utils::Vec2i rasterPos) const;

    void clear(color::Color color);

    utils::Vec2i getSize() const;

protected:
    struct DepthPixel {
        color::Color color = color::Color::Black;
        float depth = 10000.0f;
    };
    const utils::Vec2i m_SIZE;
    std::vector<DepthPixel> m_pixels;
};

} }

#endif // RENDERTARGET_HPP
