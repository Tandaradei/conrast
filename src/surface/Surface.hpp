#ifndef SURFACE_HPP
#define SURFACE_HPP

#include <stdint.h>
#include <vector>

#include "render/RenderTarget.hpp"

namespace conrast { namespace surface {

class Surface
{
public:
	Surface(utils::Vec2i resolution);
    virtual void display(const render::RenderTarget& renderTarget) const = 0;

	void setResolution(utils::Vec2i resolution);
	utils::Vec2i getResolution() const;
protected:
	utils::Vec2i m_resolution;
};

}}
#endif // SURFACE_HPP
