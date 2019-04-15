#ifndef SURFACE_HPP
#define SURFACE_HPP

#include <stdint.h>
#include <vector>

#include "../color/Color.hpp"
#include "../mesh/Vertex.hpp"

namespace conrast { namespace surface {

class Surface
{
public:
    Surface(int width, int height);
    void drawPixel(utils::Vec2i rasterPos, float depth, color::Color color);
    utils::Vec2i convertScreenToRaster(utils::Vec2f screen_pos) const;

    void clear(color::Color color);
    virtual void display() const = 0;

    utils::Vec2i getSize() const;

protected:
    struct DepthPixel {
        color::Color color = color::Color::Black;
        float depth = 10000.0f;
    };
    const utils::Vec2i m_SIZE;
    std::vector<DepthPixel> m_pixels;

};

}}
#endif // SURFACE_HPP
