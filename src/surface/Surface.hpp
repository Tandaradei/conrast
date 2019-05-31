#ifndef SURFACE_HPP
#define SURFACE_HPP

#include <stdint.h>
#include <vector>

#include "render/RenderTarget.hpp"

namespace conrast { namespace surface {

class Surface : public render::RenderTarget
{
public:
    Surface(int width, int height);
    virtual ~Surface();
    virtual void display() const = 0;
};

}}
#endif // SURFACE_HPP
