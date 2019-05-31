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
        AsciiColor(color::Color color) :
        dimming(Dimming::Normal),
        value(30) {
            value += color.r > 0.5f ? 1 : 0;
            value += color.g > 0.5f ? 2 : 0;
            value += color.b > 0.5f ? 4 : 0;
            float shade = std::max(color.r, std::max(color.g, color.b));
            if(shade < 0.33f) {
                dimming = Dimming::Dim;
            }
            else if(shade < 0.67f) {
                dimming = Dimming::Normal;
            }
            else {
                dimming = Dimming::Bright;
            }
        }
    };
    void showPixel(color::Color color) const;
};

} }
#endif // CONSOLESURFACE_HPP
