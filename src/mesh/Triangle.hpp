#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include <array>

#include "Vertex.hpp"

namespace conrast { namespace mesh {

struct Triangle {
    std::array<Vertex, 3> vertices;
};

} }

#endif // TRIANGLE_HPP
