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

    void drawPixel(utils::Vec2i rasterPos, color::RGB8 color);

    void clear(color::RGB8 color);

    utils::Vec2i getSize() const;

protected:
    const utils::Vec2i m_SIZE;
    std::vector<color::RGB8> m_pixels;
};

} }

#endif // RENDERTARGET_HPP
