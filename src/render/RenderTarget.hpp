#ifndef RENDERTARGET_HPP
#define RENDERTARGET_HPP

#include <vector>

#include "utils/Vec.hpp"
#include "color/Color.hpp"

namespace conrast { namespace render {

class RenderTarget
{
public:
    RenderTarget(int width, int height);

    void drawPixel(utils::Vec2i rasterPos, color::Color color);

    void clear(color::Color color);

    utils::Vec2i getSize() const;

protected:
    const utils::Vec2i m_SIZE;
    std::vector<color::Color> m_pixels;
};

} }

#endif // RENDERTARGET_HPP
