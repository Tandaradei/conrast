#ifndef CONSOLESURFACE_HPP
#define CONSOLESURFACE_HPP

#include "surface/Surface.hpp"


namespace conrast { namespace surface {

class ConsoleSurface : public Surface
{
public:
    ConsoleSurface(utils::Vec2i resolution);
    virtual void display(const render::RenderTarget& renderTarget) const override;

private:
    struct AsciiColor {
        enum class Dimming {
          Dim,
          Normal,
          Bright
        };
        Dimming dimming;
        uint8_t value;
		AsciiColor(color::RGB8 color);
    };
    void showPixel(color::RGB8 color) const;
};

} }
#endif // CONSOLESURFACE_HPP
