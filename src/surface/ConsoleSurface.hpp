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
    char mapPixel(color::Color color) const;
};

} }
#endif // CONSOLESURFACE_HPP
