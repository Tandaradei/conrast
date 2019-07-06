#include "Surface.hpp"

namespace conrast { namespace surface {

Surface::Surface(utils::Vec2i resolution)
	:m_resolution(resolution)
{}

void Surface::setResolution(utils::Vec2i resolution) {
	m_resolution = resolution;
}

utils::Vec2i Surface::getResolution() const {
	return m_resolution;
}

}}
