#ifndef VERTEX_HPP
#define VERTEX_HPP

#include "utils/Vec.hpp"
#include "color/Color.hpp"

namespace conrast { namespace mesh {

struct Vertex
{
    utils::Vec3f position;
    utils::Vec3f normal;
    color::RGB8 color;
};

} }

#endif // VERTEX_HPP
