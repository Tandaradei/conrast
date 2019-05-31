#ifndef IMAGESURFACE_HPP
#define IMAGESURFACE_HPP

#include "surface/Surface.hpp"


namespace conrast { namespace surface {

class ImageSurface : public Surface
{
public:
    ImageSurface(uint16_t width, uint16_t height);
    virtual void display() const override;
};

} }
#endif // CONSOLESURFACE_HPP
