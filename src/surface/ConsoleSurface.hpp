#ifndef CONSOLESURFACE_HPP
#define CONSOLESURFACE_HPP

#include "surface/Surface.hpp"


namespace conrast { namespace surface {

class ConsoleSurface : public Surface
{
public:
    ConsoleSurface(uint16_t width, uint16_t height);
    virtual void display() const override;

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
